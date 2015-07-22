#pragma once

#include "gmock/gmock.h"
using namespace ::testing;

#define RZ_QTEST_GMOCK_APPLESS_MAIN(TestObject) \
int main(int argc, char *argv[]) \
{ \
    ::testing::GTEST_FLAG(throw_on_failure) = true; \
    ::testing::InitGoogleMock(&argc, argv); \
    \
    TestObject tc; \
    QTEST_SET_MAIN_SOURCE_PATH \
    return QTest::qExec(&tc, argc, argv); \
}

#define RZ_QTEST_GMOCK_MAIN(TestObject) \
QT_BEGIN_NAMESPACE \
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS \
QT_END_NAMESPACE \
int main(int argc, char *argv[]) \
{ \
    ::testing::GTEST_FLAG(throw_on_failure) = true; \
    ::testing::InitGoogleMock(&argc, argv); \
    \
    QApplication app(argc, argv); \
    app.setAttribute(Qt::AA_Use96Dpi, true); \
    QTEST_DISABLE_KEYPAD_NAVIGATION \
    QTEST_ADD_GPU_BLACKLIST_SUPPORT \
    TestObject tc; \
    QTEST_SET_MAIN_SOURCE_PATH \
    return QTest::qExec(&tc, argc, argv); \
}

namespace rz
{
    template <class T>
    class sut_builder
    {
    public:
        T &build()
        {
            setup_buildee();
            return m_buildee;
        }

    protected:
        virtual void setup_buildee() = 0;

        T m_buildee;
    };
}

#define RZTHROWS(CODE, EXCEPTION) \
    bool result {false}; \
    try \
    { \
        (CODE); \
    } \
    catch(EXCEPTION)\
    { \
        result = true; \
    } \
    QVERIFY(result)

#define RZTHROWS2(CODE, EXCEPTION, MESSAGE) \
    bool result {false}; \
    try \
    { \
        (CODE); \
    } \
    catch(EXCEPTION)\
    { \
        result = true; \
    } \
    QVERIFY2(result, (MESSAGE))
