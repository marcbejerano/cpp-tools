#ifndef _LEVEL_TEST_H_INCLUDED_
#define _LEVEL_TEST_H_INCLUDED_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

class StandardLevelTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(StandardLevelTest);
        CPPUNIT_TEST(testCtor);
        CPPUNIT_TEST(testCtorArgs);
        CPPUNIT_TEST(testCtorCopy);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testIntLevel);
        CPPUNIT_TEST(testGetStandardLevel);
        CPPUNIT_TEST_SUITE_END();

        void testCtor();
        void testCtorArgs();
        void testCtorCopy();
        void testAssignment();
        void testIntLevel();
        void testGetStandardLevel();
};

class LevelTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(LevelTest);
        CPPUNIT_TEST(testCtor);
        CPPUNIT_TEST(testCtorArgs);
        CPPUNIT_TEST(testCtorCopy);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testClone);
        CPPUNIT_TEST(testCompareTo);
        CPPUNIT_TEST(testEquals);
        CPPUNIT_TEST(testHashCode);
        CPPUNIT_TEST(testIntLevel);
        CPPUNIT_TEST(testIsInRange);
        CPPUNIT_TEST(testIsLessSpecificThan);
        CPPUNIT_TEST(testIsMoreSpecificThan);
        CPPUNIT_TEST(testName);
        CPPUNIT_TEST(testToString);
        CPPUNIT_TEST(testGetStandardLevel);
        CPPUNIT_TEST(testForName);
        CPPUNIT_TEST(testGetLevel);
        CPPUNIT_TEST(testToLevel);
        CPPUNIT_TEST_SUITE_END();

        void testCtor();
        void testCtorArgs();
        void testCtorCopy();
        void testAssignment();
        void testClone();
        void testCompareTo();
        void testEquals();
        void testHashCode();
        void testIntLevel();
        void testIsInRange();
        void testIsLessSpecificThan();
        void testIsMoreSpecificThan();
        void testName();
        void testToString();
        void testGetStandardLevel();
        void testForName();
        void testGetLevel();
        void testToLevel();
};

#endif // _LEVEL_TEST_H_INCLUDED_

