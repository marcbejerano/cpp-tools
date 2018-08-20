#ifndef _LOGGER_TEST_H_INCLUDED_
#define _LOGGER_TEST_H_INCLUDED_


#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

class LoggerTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(LoggerTest);
        CPPUNIT_TEST(testCtorArgs);
        CPPUNIT_TEST(testCtorCopy);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testGetName);
        CPPUNIT_TEST(testGetMinimumLevel);
        CPPUNIT_TEST(testSetMinimumLevel);
        CPPUNIT_TEST(testAddAppender);
        CPPUNIT_TEST(testGetAppenders);
        CPPUNIT_TEST(testLog);
        CPPUNIT_TEST(testOpLevel);
        CPPUNIT_TEST(testOpLoggingEvent);
        CPPUNIT_TEST_SUITE_END();

        void testCtorArgs();
        void testCtorCopy();
        void testAssignment();
        void testGetName();
        void testGetMinimumLevel();
        void testSetMinimumLevel();
        void testAddAppender();
        void testGetAppenders();
        void testLog();
        void testOpLevel();
        void testOpLoggingEvent();
};

#endif // _LOGGER_TEST_H_INCLUDED_
