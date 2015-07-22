#include "rz_qtest.h"

#include <QString>
#include <QtTest>
#include <QList>
#include <QVector>
#include <QTextDocument>
#include <QDebug>

#include <RZQtIDELeftGutterWidget.h>

class gutter_builder : public rz::sut_builder<RZQtIDELeftGutterWidget>
{
public:
    virtual void setup_buildee() override
    {
        m_document.setPlainText(m_plainText);
        m_buildee.changeDocument(&m_document);
    }

    gutter_builder &withOneLine() { m_plainText = "foo"; return *this; }
    gutter_builder &withTwoLines() { m_plainText = "foo\nbar"; return *this; }
    gutter_builder &withText(QString const &text) { m_plainText = text; return *this; }

private:
    QTextDocument m_document;
    QString m_plainText {""};
};

class RZQtIDELeftGutterWidgetTest : public QObject
{
    Q_OBJECT

public:
    RZQtIDELeftGutterWidgetTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testLines_noData_returnsEmptyLinesList()
    {
        RZQtIDELeftGutterWidget g;
        QCOMPARE(g.lines()->count(), 0);
    }

    void testLines_emptyDocument_returnsEmptyLinesList()
    {
        gutter_builder b;
        auto &g = b.build();
        QCOMPARE(g.lines()->count(), 0);
    }

    void testLines_multipleLineDocument_returnsCorrectNumberOfLines_data()
    {
        QTest::addColumn<QString>("plain_text");
        QTest::addColumn<int>("number_of_lines");
        QTest::newRow("0") << QString("") << 0;
        QTest::newRow("1") << QString("hello") << 1;
        QTest::newRow("2") << QString("hello\nworld") << 2;
        QTest::newRow("3") << QString("hello\nworld\nthree") << 3;
        QTest::newRow("4") << QString("hello\nworld\nthree\nfour") << 4;
    }

    void testLines_multipleLineDocument_returnsCorrectNumberOfLines()
    {
        QFETCH(QString, plain_text);
        QFETCH(int, number_of_lines);

        gutter_builder b;
        auto &sut = b.withText(plain_text).build();

        QCOMPARE(sut.lines()->count(), number_of_lines);
    }

    void testLines_multipleLineDocument_returnsLinesWithCorrectText_data()
    {
        QTest::addColumn<QString>("plain_text");
        QTest::addColumn<QVector<QString>>("text");
        QTest::newRow("0") << QString("") << QVector<QString> { };
        QTest::newRow("1") << QString("hello") << QVector<QString> { QString("1") };
        QTest::newRow("2") << QString("hello\nworld") << QVector<QString> { QString("1"), QString("2") };
        QTest::newRow("3") << QString("hello\nworld\nthree") <<
                              QVector<QString> { QString("1"), QString("2"), QString("3") };
        QTest::newRow("4") << QString("hello\nworld\nthree\nfour") <<
                              QVector<QString> { QString("1"), QString("2"), QString("3"), QString("4") };
    }

    void testLines_multipleLineDocument_returnsLinesWithCorrectText()
    {
        QFETCH(QString, plain_text);
        QFETCH(QVector<QString>, text);

        gutter_builder b;
        auto &g = b.withText(plain_text).build();
        auto lines = g.lines();

        QCOMPARE(lines->count(), text.count());

        for (int i = 0; i < text.count(); ++i)
        {
            QCOMPARE(lines->getLine(i + 1)->text(), text[i]);
        }
    }

    void testCurrentLine_singleLineDefault_isZero()
    {
        gutter_builder b;
        auto &sut = b.withOneLine().build();

        QCOMPARE(sut.currentLine(), 0);
    }

    void testCurrentLine_singleLineDefault_isNotCurrent()
    {
        gutter_builder b;
        auto &sut = b.withOneLine().build();

        QCOMPARE(sut.lines()->getLine(1)->isCurrent(), false);
    }

    void testCurrentLine_singleLineCurrent_isCurrent()
    {
        gutter_builder b;
        auto &sut = b.withOneLine().build();

        sut.setCurrentLine(1);

        QCOMPARE(sut.currentLine(), 1);
    }

    void testCurrentLine_secondLineCurrent_isCurrent()
    {
        gutter_builder b;
        auto &sut = b.withTwoLines().build();

        sut.setCurrentLine(2);

        QCOMPARE(sut.currentLine(), 2);
    }

    void testCurrentLine_secondLineCurrentAfterFirst_isCurrent()
    {
        gutter_builder b;
        auto &sut = b.withTwoLines().build();

        sut.setCurrentLine(1);
        sut.setCurrentLine(2);

        QCOMPARE(sut.currentLine(), 2);
    }

    void testSetCurrentLine_singleLine_isCorrectlySet()
    {
        gutter_builder b;
        auto &sut = b.withOneLine().build();
        sut.setCurrentLine(1);

        QCOMPARE(sut.lines()->getLine(1)->isCurrent(), true);
    }

    void testSetCurrentLine_secondLine_isCorrectlySet()
    {
        gutter_builder b;
        auto &sut = b.withTwoLines().build();
        sut.setCurrentLine(2);

        QCOMPARE(sut.lines()->getLine(2)->isCurrent(), true);
    }

    void testSetCurrentLine_twoLines_clearsPrevious()
    {
        gutter_builder b;
        auto &sut = b.withTwoLines().build();

        QVERIFY2(sut.lines()->getLine(1)->isCurrent() == false, "line 1 was initially current");
        QVERIFY2(sut.lines()->getLine(2)->isCurrent() == false, "line 2 was initially current");

        sut.setCurrentLine(2);

        QVERIFY2(sut.lines()->getLine(1)->isCurrent() == false, "line 1 was current after setting line 2");
        QVERIFY2(sut.lines()->getLine(2)->isCurrent() == true, "line 2 was not current after setting line 1");

        sut.setCurrentLine(1);

        QVERIFY2(sut.lines()->getLine(1)->isCurrent() == true, "line 1 was not current after setting line 1");
        QVERIFY2(sut.lines()->getLine(2)->isCurrent() == false, "line 2 was current after setting line 1");
    }

    void testSetCurrentLine_zero_throws()
    {
        gutter_builder b;
        auto &sut = b.withOneLine().build();

        RZTHROWS(sut.setCurrentLine(0), std::runtime_error);
    }

    void testCurrentLine_default_returnsZero()
    {
        gutter_builder b;
        auto &sut = b.withTwoLines().build();

        QCOMPARE(sut.currentLine(), 0);
    }

    void testCurrentLine_nonDefault_returnsCurrentLine()
    {
        gutter_builder b;
        auto &sut = b.withTwoLines().build();
        sut.setCurrentLine(2);

        QCOMPARE(sut.currentLine(), 2);
    }

    void testCurrentLine_afterChange_returnsCurrentLine()
    {
        gutter_builder b;
        auto &sut = b.withTwoLines().build();
        sut.setCurrentLine(2);
        sut.setCurrentLine(1);

        QCOMPARE(sut.currentLine(), 1);
    }

    void testClearCurrentLine_clearsCurrentLine()
    {
        gutter_builder b;
        auto &sut = b.withOneLine().build();
        sut.setCurrentLine(1);
        sut.clearCurrentLine();

        QCOMPARE(sut.currentLine(), 0);
    }
};

RZQtIDELeftGutterWidgetTest::RZQtIDELeftGutterWidgetTest()
{
}

void RZQtIDELeftGutterWidgetTest::initTestCase()
{
}

void RZQtIDELeftGutterWidgetTest::cleanupTestCase()
{
}

RZ_QTEST_GMOCK_MAIN(RZQtIDELeftGutterWidgetTest)

#include "RZQtIDELeftGutterWidgetTest.moc"
