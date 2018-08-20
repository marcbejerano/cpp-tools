#ifndef _CONFIGURATION_TEST_H_INCLUDED_
#define _CONFIGURATION_TEST_H_INCLUDED_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

class ConfigurationTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(ConfigurationTest);
        CPPUNIT_TEST(testCtor);
        CPPUNIT_TEST(testCtorCopy);
        CPPUNIT_TEST(testCtorString);
        CPPUNIT_TEST(testCtorIstream);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testHasSection);
        CPPUNIT_TEST(testSections);
        CPPUNIT_TEST(testGetProperty);
        CPPUNIT_TEST(testGetProperty2);
        CPPUNIT_TEST(testSetProperty);
        CPPUNIT_TEST(testSetProperty2);
        CPPUNIT_TEST(testGetProperties);
        CPPUNIT_TEST(testSetProperties);
        CPPUNIT_TEST(testLoadString);
        CPPUNIT_TEST(testLoadStream);
        CPPUNIT_TEST(testStoreString);
        CPPUNIT_TEST(testStoreStream);
        CPPUNIT_TEST_SUITE_END();

        void testCtor();
        void testCtorCopy();
        void testCtorString();
        void testCtorIstream();
        void testAssignment();
        void testHasSection();
        void testSections();
        void testGetProperty();
        void testGetProperty2();
        void testSetProperty();
        void testSetProperty2();
        void testGetProperties();
        void testSetProperties();
        void testLoadString();
        void testLoadStream();
        void testStoreString();
        void testStoreStream();

};

#endif // _CONFIGURATION_TEST_H_INCLUDED_
