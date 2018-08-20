#ifndef _EVENT_TEST_H_INCLUDED_
#define _EVENT_TEST_H_INCLUDED_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

class EventTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(EventTest);
        CPPUNIT_TEST(testCtor);
        CPPUNIT_TEST(testCtorCopy);
        CPPUNIT_TEST(testCtorArgs);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testGetCause);
        CPPUNIT_TEST(testSetCause);
        CPPUNIT_TEST(testGetTimestamp);
        CPPUNIT_TEST(testGetLevel);
        CPPUNIT_TEST_SUITE_END();

        void testCtor();
        void testCtorCopy();
        void testCtorArgs();
        void testAssignment();
        void testGetCause();
        void testSetCause();
        void testGetTimestamp();
        void testGetLevel();
};

class LoggingEventTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(LoggingEventTest);
        CPPUNIT_TEST(testCtor);
        CPPUNIT_TEST(testCtorCopy);
        CPPUNIT_TEST(testCtorArgs);
        CPPUNIT_TEST(testCtorArgs2);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testGetFileName);
        CPPUNIT_TEST(testGetClassName);
        CPPUNIT_TEST(testGetMethodName);
        CPPUNIT_TEST(testGetLineNumber);
        CPPUNIT_TEST_SUITE_END();

        void testCtor();
        void testCtorCopy();
        void testCtorArgs();
        void testCtorArgs2();
        void testAssignment();
        void testGetFileName();
        void testGetClassName();
        void testGetMethodName();
        void testGetLineNumber();
};

#endif // _EVENT_TEST_H_INCLUDED_
