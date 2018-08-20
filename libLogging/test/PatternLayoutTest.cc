#include "PatternLayoutTest.h"
#include <PatternLayout>
#include <Event>
#include <LoggingEvent>
#include <Tools>

using namespace hslib;

void LayoutTest::testCtor()
{
    Layout layout;
}

void LayoutTest::testFormat()
{
    Layout layout;
    Event event("because");
    CPPUNIT_ASSERT("because" == layout.format(event));
}

void PatternLayoutTest::testCtor()
{
    PatternLayout layout;
}

void PatternLayoutTest::testCtorCopy()
{
    PatternLayout layoutA("AAA");
    PatternLayout layoutB(layoutA);
    CPPUNIT_ASSERT(layoutB.getPattern() == "AAA");
}

void PatternLayoutTest::testCtorArgs()
{
    PatternLayout layoutA("AAA");
    CPPUNIT_ASSERT(layoutA.getPattern() == "AAA");
}

void PatternLayoutTest::testAssignment()
{
    PatternLayout layoutA("AAA");
    PatternLayout layoutB = layoutA;
    CPPUNIT_ASSERT(layoutB.getPattern() == "AAA");
}

void PatternLayoutTest::testFormat()
{
    PatternLayout layout; // %m%n
    LoggingEvent event(LOGGING_EVENT(Level::DEBUG, "cause"));
    CPPUNIT_ASSERT("cause\n" == layout.format(event));

    layout.setPattern("[%6p] %F(%L) %C::%M - %m%n");
    std::string expected = "[DEBUG ] PatternLayoutTest.cc(49) PatternLayoutTest::testFormat - cause\n";
    std::string result = layout.format(event);
    CPPUNIT_ASSERT(expected == result);

    layout.setPattern("[%-8p]");
    expected = "[   DEBUG]";
    result = layout.format(event);
    CPPUNIT_ASSERT(expected == result);

    layout.setPattern("%d [%6p] %F(%L) %C::%M - %m%n");
    result = layout.format(event);
}

void PatternLayoutTest::testGetPattern()
{
    PatternLayout layoutA("AAA");
    CPPUNIT_ASSERT(layoutA.getPattern() == "AAA");
}

void PatternLayoutTest::testSetPattern()
{
    PatternLayout layoutA("AAA");
    CPPUNIT_ASSERT(layoutA.getPattern() == "AAA");
    layoutA.setPattern("BBB");
    CPPUNIT_ASSERT(layoutA.getPattern() == "BBB");
}

