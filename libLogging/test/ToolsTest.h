#ifndef _TOOLS_TEST_H_INCLUDED_
#define _TOOLS_TEST_H_INCLUDED_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

class ToolsTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(ToolsTest);
        CPPUNIT_TEST(testRtrim);
        CPPUNIT_TEST(testLtrim);
        CPPUNIT_TEST(testTrim);
        CPPUNIT_TEST(testTrimCopy);
        CPPUNIT_TEST(testStartsWith);
        CPPUNIT_TEST(testEndsWith);
        CPPUNIT_TEST(testFileExists);
        CPPUNIT_TEST(testSplit);
        CPPUNIT_TEST_SUITE_END();

        void testRtrim();
        void testLtrim();
        void testTrim();
        void testTrimCopy();
        void testStartsWith();
        void testEndsWith();
        void testFileExists();
        void testSplit();
};

#endif // _TOOLS_TEST_H_INCLUDED_
