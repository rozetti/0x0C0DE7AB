#include "rz_qtest.h"

#include <QString>
#include <QtTest>

#include "RZQtIDELeftGutterWidgetLine.h"

class RZQtIDELeftGutterWidgetLineTest : public QObject
{
    Q_OBJECT

public:
    RZQtIDELeftGutterWidgetLineTest();

private Q_SLOTS:

    void testText_lineZero_throws()
    {
        RZTHROWS2(RZQtIDELeftGutterWidgetLine(0),
                  std::runtime_error, "line(0) did not throw");
    }

    void testCtor_setsCorrectLineNumber()
    {
        RZQtIDELeftGutterWidgetLine line(42);

        QCOMPARE(line.number(), 42);
    }

    void testText_lineOne_textReturnsCorrectLineNumber()
    {
        RZQtIDELeftGutterWidgetLine line(1729);

        QCOMPARE(line.text(), QString("1729"));
    }

    void testText_manyLines_returnCorrectLineNumber()
    {
        for (int i = 1; i < 10; ++i)
        {
            RZQtIDELeftGutterWidgetLine line(i);

            QCOMPARE(line.text(), QString::number(i));
        }
    }

    void testHasBreakpoint_notSet_returnsCorrectValue()
    {
        RZQtIDELeftGutterWidgetLine line;

        QCOMPARE(line.hasBreakpoint(), false);
    }

    void testHasBreakpoint_set_returnsCorrectValue()
    {
        RZQtIDELeftGutterWidgetLine line;
        line.setBreakpoint();
        QCOMPARE(line.hasBreakpoint(), true);
    }

    void testHasBreakpoint_clear_returnsCorrectValue()
    {
        RZQtIDELeftGutterWidgetLine line;
        line.setBreakpoint();
        QCOMPARE(line.hasBreakpoint(), true);
        line.clearBreakpoint();
        QCOMPARE(line.hasBreakpoint(), false);
    }

    void testIsCurrent_default_isNotSet()
    {
        RZQtIDELeftGutterWidgetLine line;

        QCOMPARE(line.isCurrent(), false);
    }

    void testIsCurrent_set_returnsCorrectValue()
    {
        RZQtIDELeftGutterWidgetLine line;
        line.setIsCurrent();
        QCOMPARE(line.isCurrent(), true);
    }

    void testIsCurrent_clear_returnsCorrectValue()
    {
        RZQtIDELeftGutterWidgetLine line;
        line.setIsCurrent();
        QCOMPARE(line.isCurrent(), true);
        line.clearIsCurrent();
        QCOMPARE(line.isCurrent(), false);
    }

    void testSetNumber_setsCorrectLineNumber()
    {
        RZQtIDELeftGutterWidgetLine line;

        line.setNumber(42);

        QCOMPARE(line.number(), 42);
    }
};

RZQtIDELeftGutterWidgetLineTest::RZQtIDELeftGutterWidgetLineTest()
{
}

RZ_QTEST_GMOCK_APPLESS_MAIN(RZQtIDELeftGutterWidgetLineTest)

#include "RZQtIDELeftGutterWidgetLineTest.moc"
