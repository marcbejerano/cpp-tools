#include "ConfigurationTest.h"
#include <Configuration>

using namespace hslib;

static const std::string TEST_CONFIG = "nosection=1234\ndata=hello world\n\n[section 9]\nufos=are real";

void ConfigurationTest::testCtor()
{
    Configuration config;
}

void ConfigurationTest::testCtorCopy()
{
    Configuration config(TEST_CONFIG);
    Configuration copy(config);
    CPPUNIT_ASSERT(copy.getProperty("data", "NOT THERE") == "hello world");
    CPPUNIT_ASSERT(copy.getProperty("section 9", "ufos", "NOT THERE") == "are real");
}

void ConfigurationTest::testCtorString()
{
    Configuration config(TEST_CONFIG);
    CPPUNIT_ASSERT(config.getProperty("data", "NOT THERE") == "hello world");
    CPPUNIT_ASSERT(config.getProperty("section 9", "ufos", "NOT THERE") == "are real");
}

void ConfigurationTest::testCtorIstream()
{
    std::stringstream ss(TEST_CONFIG);
    Configuration config(ss);
    CPPUNIT_ASSERT(config.getProperty("data", "NOT THERE") == "hello world");
    CPPUNIT_ASSERT(config.getProperty("section 9", "ufos", "NOT THERE") == "are real");
}

void ConfigurationTest::testAssignment()
{
    Configuration config(TEST_CONFIG);
    Configuration copy = config;
    CPPUNIT_ASSERT(copy.getProperty("data", "NOT THERE") == "hello world");
    CPPUNIT_ASSERT(copy.getProperty("section 9", "ufos", "NOT THERE") == "are real");
}

void ConfigurationTest::testHasSection()
{
    Configuration config;
    config.setProperty("key", "value");
    config.setProperty("display.settings", "width", "1920");
    config.setProperty("display.settings", "height", "1080");
    CPPUNIT_ASSERT(config.hasSection(Configuration::DEFAULT_SECTION));
    CPPUNIT_ASSERT(config.hasSection("display.settings"));
    CPPUNIT_ASSERT(!config.hasSection("not there"));
}

void ConfigurationTest::testSections()
{
    Configuration config;
    config.setProperty("key", "value");
    config.setProperty("display.settings", "width", "1920");
    config.setProperty("display.settings", "height", "1080");
    std::set<std::string> sections = config.sections();
    CPPUNIT_ASSERT(sections.size() == 2);
    // the default section counts as a "section"
}

void ConfigurationTest::testGetProperty()
{
    Configuration config;
    config.setProperty("key", "value");
    CPPUNIT_ASSERT(config.getProperty("key", "NOT THERE") == "value");
    CPPUNIT_ASSERT(config.getProperty("foo", "NOT THERE") == "NOT THERE");
}

void ConfigurationTest::testGetProperty2()
{
    Configuration config;
    config.setProperty("section1", "key", "value");
    CPPUNIT_ASSERT(config.getProperty("section1", "key", "NOT THERE") == "value");
    CPPUNIT_ASSERT(config.getProperty("section1", "foo", "NOT THERE") == "NOT THERE");
}

void ConfigurationTest::testSetProperty()
{
    Configuration config;
    config.setProperty("section1", "key", "value");
    CPPUNIT_ASSERT(config.getProperty("section1", "key", "NOT THERE") == "value");
    CPPUNIT_ASSERT(config.getProperty("section1", "foo", "NOT THERE") == "NOT THERE");
}

void ConfigurationTest::testSetProperty2()
{
    Configuration config;
    config.setProperty("section1", "key", "value");
    CPPUNIT_ASSERT(config.getProperty("section1", "key", "NOT THERE") == "value");
    CPPUNIT_ASSERT(config.getProperty("section1", "foo", "NOT THERE") == "NOT THERE");
}

void ConfigurationTest::testGetProperties()
{
    Configuration config;
    config.setProperty("key", "value");
    config.setProperty("display.settings", "width", "1920");
    config.setProperty("display.settings", "height", "1080");
    CPPUNIT_ASSERT(config.hasSection(Configuration::DEFAULT_SECTION));
    CPPUNIT_ASSERT(config.hasSection("display.settings"));
    CPPUNIT_ASSERT(!config.hasSection("not there"));
    
    Properties propsA = config.getProperties();
    CPPUNIT_ASSERT(propsA.getProperty("key") == "value");
    Properties propsB = config.getProperties("display.settings");
    CPPUNIT_ASSERT(propsB.getProperty("width") == "1920");
}

void ConfigurationTest::testSetProperties()
{
    Configuration config;
    Properties props;
    props.setProperty("aaa", "1234");
    props.setProperty("bbb", "5678");
    config.setProperties(props);
    CPPUNIT_ASSERT(config.getProperty("bbb", "NOT THERE") == "5678");
    CPPUNIT_ASSERT(config.getProperty("aaa", "NOT THERE") == "1234");

    config.setProperties("section 8", props);
    CPPUNIT_ASSERT(config.getProperty("section 8", "bbb", "NOT THERE") == "5678");
    CPPUNIT_ASSERT(config.getProperty("section 8", "aaa", "NOT THERE") == "1234");
}

void ConfigurationTest::testLoadString()
{
    Configuration config;
    config.load(TEST_CONFIG);
    CPPUNIT_ASSERT(config.getProperty("section 9", "ufos", "NOT THERE") == "are real");
}

void ConfigurationTest::testLoadStream()
{
    Configuration config;
    std::stringstream ss;
    ss << TEST_CONFIG;
    config.load(ss);
    CPPUNIT_ASSERT(config.getProperty("section 9", "ufos", "NOT THERE") == "are real");
}

void ConfigurationTest::testStoreString()
{
    Configuration config;
    config.setProperty("key", "value");
    config.setProperty("display.settings", "width", "1920");
    config.setProperty("display.settings", "height", "1080");
    CPPUNIT_ASSERT(config.getProperty("display.settings", "width", "0") == "1920");
    std::string data;
    config.store(data);
    const std::string expected = "key=value\n\n[display.settings]\nheight=1080\nwidth=1920\n";
    CPPUNIT_ASSERT(expected == data);
}

void ConfigurationTest::testStoreStream()
{
    Configuration config;
    config.setProperty("key", "value");
    config.setProperty("display.settings", "width", "1920");
    config.setProperty("display.settings", "height", "1080");
    CPPUNIT_ASSERT(config.getProperty("display.settings", "width", "0") == "1920");
    std::stringstream ss;
    config.store(ss);

    const std::string expected = "key=value\n\n[display.settings]\nheight=1080\nwidth=1920\n";
    CPPUNIT_ASSERT(expected == ss.str());
}

