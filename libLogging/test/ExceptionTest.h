#ifndef _EXCEPTION_TEST_H_INCLUDED_
#define _EXCEPTION_TEST_H_INCLUDED_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

class ExceptionTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(ExceptionTest);
        CPPUNIT_TEST(testCtor);
        CPPUNIT_TEST(testCtorArgs);
        CPPUNIT_TEST(testCtorCopy);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testGetMessage);
        CPPUNIT_TEST(testSetMessage);
        CPPUNIT_TEST_SUITE_END();

        void testCtor();
        void testCtorArgs();
        void testCtorCopy();
        void testAssignment();
        void testGetMessage();
        void testSetMessage();
};

#endif // _EXCEPTION_TEST_H_INCLUDED_
