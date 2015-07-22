#pragma once

#include <QObject>

#include <QString>

extern "C" {
#include "6IT.h"
}

class RZQtSubCWorker : public QObject
{
    Q_OBJECT

public:
    RZQtSubCWorker();
    ~RZQtSubCWorker();
    void run_print_string(char const *s);
    void compiler_print_string(char const *s);

public slots:
    void run();
    void compile();
    void setSource(QString const &);

signals:
    void sourceChanged();

    void compilationWillStart();
    void compilationDidFinish();
    void compilationDidFail();

    void runWillStart();
    void runDidFinish();
    void runDidFail();

    void compilerConsoleOutput(QString const &s, int);
    void runConsoleOutput(QString const &s, int);

private:
    QString m_sourceCode;

    struct environment_t m_environment;
    struct machine_t m_machine;
    struct compiler_t m_compiler;

    int m_signalId {0};
};
