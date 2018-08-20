#ifndef _PROPERTIES_TEST_H_INCLUDED_
#define _PROPERTIES_TEST_H_INCLUDED_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

class PropertiesTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(PropertiesTest);
        CPPUNIT_TEST(testCtor);
        CPPUNIT_TEST(testCtorCopy);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testSetProperty);
        CPPUNIT_TEST(testGetProperty);
        CPPUNIT_TEST(testKeys);
        CPPUNIT_TEST(testLoad);
        CPPUNIT_TEST(testLoad2);
        CPPUNIT_TEST(testStore);
        CPPUNIT_TEST(testStore2);
        CPPUNIT_TEST_SUITE_END();

        void testCtor();
        void testCtorCopy();
        void testAssignment();
        void testSetProperty();
        void testGetProperty();
        void testKeys();
        void testLoad();
        void testLoad2();
        void testStore();
        void testStore2();
};

#endif // _PROPERTIES_TEST_H_INCLUDED_
