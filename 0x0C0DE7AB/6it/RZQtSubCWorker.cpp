#include "RZQtSubCWorker.h"

#include <QThread>
#include <QCoreApplication>
#include <QString>
#include <QDebug>

#include <string>
extern "C"
{
#include "6IT.h"
#include "SubCRT.h"
}

static RZQtSubCWorker *_worker;

static int source_offset = 0; // hack crz: move this into a state object with the source string

int source_seek(void *context, int offset)
{
    source_offset = offset;
    return 1;
}

int source_get_char(void *context, char *c)
{
    *c = *((char const *)context + source_offset);

    if (!*c) return 0;

    ++source_offset;

    return 1;
}

static int runProgram()
{
}

static void _run_print_string(char const *s)
{
    _worker->run_print_string(s);
}

static void _compiler_print_string(char const *s)
{
    _worker->compiler_print_string(s);
}

RZQtSubCWorker::RZQtSubCWorker()
{
    _worker = this;

    construct_6IOS(&_Bios, 0);
    _Bios.print_string = _compiler_print_string;

    m_environment = construct_environment();
    m_environment.output_string = _Bios.print_string;
    m_environment.input_line = _Bios.read_line;
    m_environment.read_next_char = source_get_char;
    m_environment.read_seek = source_seek;

    struct machine_config_t config;
    construct_default_H6VM_config(&config);
    construct_H6VM(&m_machine, &m_machine, config);

    construct_6IL(&m_machine.processor, &m_machine);
    construct_6EV(&m_machine.evaluator, &m_machine);
    construct_6YM(&m_machine.downcompiler, &m_machine);
    construct_SubC(&m_compiler, &m_machine);

    m_compiler.verbosity = 0;
    m_compiler.scanner->verbosity = 0;
    m_machine.downcompiler.verbosity = 0;
    m_machine.evaluator.verbosity = 0;
    m_machine.verbosity = 0;

    m_machine.bind_environment(&m_machine, &m_environment);
    m_machine.bind_compiler(&m_machine, &m_compiler);
    m_machine.bind_processor(&m_machine, &m_machine.processor);
    m_machine.bind_evaluator(&m_machine, &m_machine.evaluator);
    m_machine.bind_downcompiler(&m_machine, &m_machine.downcompiler);
}

RZQtSubCWorker::~RZQtSubCWorker()
{
    m_machine.destruct(&m_machine);
    m_compiler.destruct(&m_compiler);
}

void RZQtSubCWorker::compiler_print_string(const char *s)
{
    emit compilerConsoleOutput(QString(s), m_signalId++);
}

void RZQtSubCWorker::run_print_string(const char *s)
{
    qDebug(s);

    emit runConsoleOutput(QString(s), m_signalId++);
}

void RZQtSubCWorker::compile()
{
    m_environment.output_string = _compiler_print_string;

    emit compilationWillStart();

    m_machine.printf(&m_machine, "Compiling...\n");

    auto src = m_sourceCode.toStdString();
    m_environment.context = (void *)src.c_str();

    if (CATCH(&m_compiler.scanner->exception))
    {
        qDebug("scanner fault");
        emit compilationDidFail();
        return;
    }

    source_offset = 0;
    m_machine.new_program(&m_machine);
    bind_SubCRT(&m_machine);

    //m_machine.environment->context = (void *)source.c_str();
    if (!m_compiler.compile(&m_compiler))
    {
        qDebug("could not compile source");
        emit compilationDidFail();
        return;
    }

    m_machine.debugger.print_state(&m_machine.debugger);
    m_machine.printf(&m_machine, "--------------------------------------------\n");
    m_machine.printf(&m_machine, "Downcompiling...\n");
    m_machine.downcompiler.downcompile(&m_machine.downcompiler);
    m_machine.printf(&m_machine, "--------------------------------------------\n");
    m_machine.debugger.print_state(&m_machine.debugger);

    m_machine.printf(&m_machine, "Compilation complete\n");

    emit compilationDidFinish();
}

void RZQtSubCWorker::setSource(const QString &source)
{
    m_sourceCode = source;

    emit sourceChanged();
}

void RZQtSubCWorker::run()
{
    _Bios.print_string = _run_print_string;
    m_environment.output_string = _run_print_string;

    emit runWillStart();

    if (CATCH(&m_machine.exception))
    {
        m_machine.printf(&m_machine, "virtual machine fault occured during compilation\n");
        emit runDidFail();
        return;
    }

    _FRAME(&m_machine)->evaluator_program_counter = -1;
#ifdef _6IT_SUPPORT_INTERRUPTS
    _CLEAR_IRQF(&m_machine);
#endif

    struct callable_unit_t *si = m_machine.find_callable_unit(&m_machine, "static");
    _SET_PC(_REGS(&m_machine), si->entry_point_program_counter);

    m_machine.execute(&m_machine);

    struct callable_unit_t *cu = m_machine.find_callable_unit(&m_machine, "main");
    if (!cu)
    {
        m_machine.printf(&m_machine, "main() entry point not found\n");
        emit runDidFail();
        return;
    }

    // crz: this is used by non-threaded vm
    m_machine.number_of_threads = 1; // hack crz

    _SET_PC(_REGS(&m_machine), cu->entry_point_program_counter);
    _FRAME(&m_machine)->entry_ip = _REG_CS(_REGS(&m_machine)) + cu->entry_point_program_counter;
    _FRAME(&m_machine)->callable_unit_idx = cu->idx;

    _Bios.get_current_time_ms(&m_machine.execution_start_ms);
    m_machine.pause_ms = 0;

    int end_ms;
    if (CATCH(&m_machine.exception))
    {
        _Bios.get_current_time_ms(&end_ms);
        int d = end_ms - m_machine.execution_start_ms - m_machine.pause_ms;
        m_machine.printf(&m_machine, "virtual machine fault occured after %d seconds, %d milliseconds\n", d / 1000, d % 1000);
        emit runDidFail();
        return;
    }

    m_machine.execute(&m_machine);
    _Bios.get_current_time_ms(&end_ms);

    int rv = POP_INT(&m_machine);

    int d = end_ms - m_machine.execution_start_ms - m_machine.pause_ms;
    m_machine.printf(&m_machine, "main() returned %d after %d seconds, %d milliseconds\n", rv, d / 1000, d % 1000);

    m_machine.printf(&m_machine, "Run complete\n");

    emit runDidFinish();
}
