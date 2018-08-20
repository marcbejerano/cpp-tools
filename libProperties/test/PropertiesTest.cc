#include "PropertiesTest.h"
#include <Properties>
#include <iostream>
#include <sstream>

using namespace hslib;

// For the load/load2 tests
static const std::string PROPERTIES = "# comment               \n\
                                       abc=123                 \n\
                                       def.ghi = this is a test\n\
                                       colon:separated         \n\
                                       \n\
                                       mixed=:this is mixed    \n\
                                       \n\
                                       ! another comment       \n\
                                       key=value,            \\\n\
                                       multiline";
static const std::string PROPERTIES_OUT = "abc=123\ncolon=separated\ndef.ghi=this is a test\nkey=value,multiline\nmixed=:this is mixed\n";

void PropertiesTest::testCtor()
{
    Properties props;
}

void PropertiesTest::testCtorCopy()
{
    Properties propsA;
    propsA.setProperty("foo", "bar");
    Properties propsB(propsA);
    CPPUNIT_ASSERT("bar" == propsB.getProperty("foo", "not-bar"));
}

void PropertiesTest::testAssignment()
{
    Properties propsA;
    propsA.setProperty("foo", "bar");
    Properties propsB = propsA;
    CPPUNIT_ASSERT("bar" == propsB.getProperty("foo", "not-bar"));
}

void PropertiesTest::testSetProperty()
{
    Properties propsA;
    propsA.setProperty("foo", "bar");
    CPPUNIT_ASSERT("bar" == propsA.getProperty("foo", "not-bar"));
    propsA.setProperty("foo", "bar2");
    CPPUNIT_ASSERT("bar2" == propsA.getProperty("foo", "not-bar"));
}

void PropertiesTest::testGetProperty()
{
    Properties propsA;
    propsA.setProperty("foo", "bar");
    CPPUNIT_ASSERT("bar" == propsA.getProperty("foo", "not-bar"));
    CPPUNIT_ASSERT("not-bar" == propsA.getProperty("bar", "not-bar"));
}

void PropertiesTest::testKeys()
{
    Properties props;
    props.setProperty("aaa", "12345");
    props.setProperty("bbb", "67890");
    std::set<std::string> keys = props.keys();
    CPPUNIT_ASSERT(keys.find("aaa") != keys.end());
    CPPUNIT_ASSERT(keys.find("bbb") != keys.end());
}

void PropertiesTest::testLoad()
{
    Properties props;
    props.load(PROPERTIES);
    CPPUNIT_ASSERT("123" == props.getProperty("abc"));
    CPPUNIT_ASSERT("this is a test" == props.getProperty("def.ghi"));
    CPPUNIT_ASSERT("separated" == props.getProperty("colon"));
    CPPUNIT_ASSERT(":this is mixed" == props.getProperty("mixed"));
    CPPUNIT_ASSERT("value,multiline" == props.getProperty("key"));
}

void PropertiesTest::testLoad2()
{
    std::stringstream ss;
    ss.str(PROPERTIES);
    Properties props;
    props.load(ss);
    CPPUNIT_ASSERT("123" == props.getProperty("abc"));
    CPPUNIT_ASSERT("this is a test" == props.getProperty("def.ghi"));
    CPPUNIT_ASSERT("separated" == props.getProperty("colon"));
    CPPUNIT_ASSERT(":this is mixed" == props.getProperty("mixed"));
    CPPUNIT_ASSERT("value,multiline" == props.getProperty("key"));
}

void PropertiesTest::testStore()
{
    Properties props;
    props.load(PROPERTIES);
    std::string result;
    props.store(result);
    CPPUNIT_ASSERT(PROPERTIES_OUT == result);
}

void PropertiesTest::testStore2()
{
    Properties props;
    props.load(PROPERTIES);
    std::stringstream buffer;
    props.store(buffer);
    CPPUNIT_ASSERT(PROPERTIES_OUT == buffer.str());
}

