#ifndef _PATTERNLAYOUT_TEST_H_INCLUDED_
#define _PATTERNLAYOUT_TEST_H_INCLUDED_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

class LayoutTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(LayoutTest);
        CPPUNIT_TEST(testCtor);
        CPPUNIT_TEST(testFormat);
        CPPUNIT_TEST_SUITE_END();

        void testCtor();
        void testFormat();
};

class PatternLayoutTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(PatternLayoutTest);
        CPPUNIT_TEST(testCtor);
        CPPUNIT_TEST(testCtorCopy);
        CPPUNIT_TEST(testCtorArgs);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testFormat);
        CPPUNIT_TEST(testGetPattern);
        CPPUNIT_TEST(testSetPattern);
        CPPUNIT_TEST_SUITE_END();

        void testCtor();
        void testCtorCopy();
        void testCtorArgs();
        void testAssignment();
        void testFormat();
        void testGetPattern();
        void testSetPattern();
};

#endif // _PATTERNLAYOUT_TEST_H_INCLUDED_
