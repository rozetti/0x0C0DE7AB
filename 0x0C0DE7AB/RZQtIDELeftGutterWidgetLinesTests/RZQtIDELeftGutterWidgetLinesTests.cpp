#include "rz_qtest.h"

#include <QString>
#include <QtTest>

#include <exception>

#include "RZQtIDELeftGutterWidgetLines.h"

class FakeFactory : public IRZQtIDEFactory
{
public:
    MOCK_CONST_METHOD0(createLeftGutterLine, IRZQtIDELeftGutterWidgetLine *());
};

class LineMock : public IRZQtIDELeftGutterWidgetLine
{
public:
    MOCK_CONST_METHOD0(text, QString());
    MOCK_METHOD1(setNumber, void(int));
    MOCK_CONST_METHOD0(number, int());
    MOCK_CONST_METHOD0(hasBreakpoint, bool());
    MOCK_METHOD0(setBreakpoint, void());
    MOCK_METHOD0(clearBreakpoint, void());
    MOCK_CONST_METHOD0(isCurrent, bool());
    MOCK_METHOD0(setIsCurrent, void());
    MOCK_METHOD0(clearIsCurrent, void());
};

class RZQtIDELeftGutterWidgetLinesTests : public QObject
{
    Q_OBJECT

public:
    RZQtIDELeftGutterWidgetLinesTests();

private Q_SLOTS:

    void testGutterLines_noData_hasZeroElements()
    {
        FakeFactory factory;
        RZQtIDELeftGutterWidgetLines lines(factory);

        QCOMPARE(lines.count(), 0);
    }

    void testGutterLines_appendLine_appendsALine()
    {
        FakeFactory factory;
        EXPECT_CALL(factory, createLeftGutterLine()).
                WillOnce(Return(new NiceMock<LineMock>()));

        RZQtIDELeftGutterWidgetLines lines(factory);

        lines.append();

        QCOMPARE(lines.count(), 1);
    }

    void testGutterLines_appendLine_setsNextLineNumber()
    {
        auto expected = new NiceMock<LineMock>();
        EXPECT_CALL(*expected, setNumber(1)).Times(1);

        FakeFactory factory;
        EXPECT_CALL(factory, createLeftGutterLine()).Times(1).
                WillOnce(Return(expected));

        RZQtIDELeftGutterWidgetLines lines(factory);

        lines.append();
    }

    void testGutterLines_getLineZero_throws()
    {
        NiceMock<FakeFactory> factory;

        RZQtIDELeftGutterWidgetLines lines(factory);

        RZTHROWS(lines.getLine(0), std::runtime_error);
    }

    void testGutterLines_getTheOnlyLine_getsTheLine()
    {
        auto expected = new NiceMock<LineMock>();

        NiceMock<FakeFactory> factory;
        ON_CALL(factory, createLeftGutterLine()).WillByDefault(Return(expected));

        RZQtIDELeftGutterWidgetLines lines(factory);

        lines.append();

        auto actual = lines.getLine(1);

        QCOMPARE(actual, expected);
    }

    void testGutterLines_appendSecondLine_setsCorrectLineNumber()
    {
        auto expected = new LineMock();
        EXPECT_CALL(*expected, setNumber(2)).Times(1);

        FakeFactory factory;
        EXPECT_CALL(factory, createLeftGutterLine()).Times(2).
                WillOnce(Return(new NiceMock<LineMock>())).
                WillOnce(Return(expected));

        RZQtIDELeftGutterWidgetLines lines(factory);

        lines.append();
        lines.append();
    }

    void testGutterLines_getSecondLine_getsTheLine()
    {
        auto expected = new NiceMock<LineMock>();

        FakeFactory factory;
        EXPECT_CALL(factory, createLeftGutterLine()).Times(2).
                WillOnce(Return(new NiceMock<LineMock>())).
                WillOnce(Return(expected));

        RZQtIDELeftGutterWidgetLines lines(factory);

        lines.append();
        lines.append();

        auto actual = lines.getLine(2);

        QCOMPARE(actual, expected);
    }

    void testClear_oneLine_removesTheLine()
    {
        FakeFactory factory;
        EXPECT_CALL(factory, createLeftGutterLine()).Times(1).
                WillOnce(Return(new NiceMock<LineMock>()));

        RZQtIDELeftGutterWidgetLines lines(factory);

        lines.append();
        lines.clear();

        QCOMPARE(lines.count(), 0);
    }
};

RZQtIDELeftGutterWidgetLinesTests::RZQtIDELeftGutterWidgetLinesTests()
{
}

RZ_QTEST_GMOCK_APPLESS_MAIN(RZQtIDELeftGutterWidgetLinesTests)

#include "RZQtIDELeftGutterWidgetLinesTests.moc"
