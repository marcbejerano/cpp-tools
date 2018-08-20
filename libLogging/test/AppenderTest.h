#ifndef _APPENDER_TEST_H_INCLUDED_
#define _APPENDER_TEST_H_INCLUDED_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

class AppenderTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(AppenderTest);
        CPPUNIT_TEST(testCtor);
        CPPUNIT_TEST(testCtorCopy);
        CPPUNIT_TEST(testCtorArgs);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testGetLayout);
        CPPUNIT_TEST(testSetLayout);
        CPPUNIT_TEST(testGetMinimumLevel);
        CPPUNIT_TEST(testSetMinimumLevel);
        CPPUNIT_TEST_SUITE_END();

        void testCtor();
        void testCtorCopy();
        void testCtorArgs();
        void testAssignment();
        void testGetLayout();
        void testSetLayout();
        void testGetMinimumLevel();
        void testSetMinimumLevel();
};

class ConsoleAppenderTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(ConsoleAppenderTest);
        CPPUNIT_TEST_SUITE_END();
};

#endif // _APPENDER_TEST_H_INCLUDED_
