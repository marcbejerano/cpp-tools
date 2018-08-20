#ifndef _LOGFACTORY_TEST_H_INCLUDED_
#define _LOGFACTORY_TEST_H_INCLUDED_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

class LogFactoryTest : public CppUnit::TestCase
{
    public:
        CPPUNIT_TEST_SUITE(LogFactoryTest);
        CPPUNIT_TEST(testGetLogger);
        CPPUNIT_TEST_SUITE_END();

        void testGetLogger();
};

#endif // _LOGFACTORY_TEST_H_INCLUDED_
