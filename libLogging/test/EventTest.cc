#include "EventTest.h"
#include <Event>
#include <LoggingEvent>
#include <ctime>
#include <iostream>

using namespace hslib;

// If you move this code then you will need to update the
// LoggingEventTest::testLineNumber() method below with the
// new line number.
class LoggingEventTester
{
    public:
        LoggingEventTester() { }
        const std::string fileName() { LoggingEvent e = LOGGING_EVENT0("fileName"); return e.getFileName(); }
        const std::string className() { LoggingEvent e = LOGGING_EVENT0("className"); return e.getClassName(); }
        const std::string methodName() { LoggingEvent e = LOGGING_EVENT0("methodName"); return e.getMethodName(); }
        size_t lineNumber() { LoggingEvent e = LOGGING_EVENT0("lineNumber"); return e.getLineNumber(); }
};

void EventTest::testCtor()
{
    Event event;
}

void EventTest::testCtorCopy()
{
    Event eventA("ABC");
    Event eventB(eventA);
    CPPUNIT_ASSERT(eventB.getCause() == "ABC");
}

void EventTest::testCtorArgs()
{
    Event event("ABC");
    CPPUNIT_ASSERT(event.getCause() == "ABC");
    Event eventB("ABC", Level::FATAL);
    CPPUNIT_ASSERT(eventB.getLevel() == Level::FATAL);
}

void EventTest::testAssignment()
{
    Event eventA("ABC");
    Event eventB = eventA;
    CPPUNIT_ASSERT(eventB.getCause() == "ABC");
}

void EventTest::testGetCause()
{
    Event event("ABC");
    CPPUNIT_ASSERT(event.getCause() == "ABC");
}

void EventTest::testSetCause()
{
    Event event("ABC");
    CPPUNIT_ASSERT(event.getCause() == "ABC");
    event.setCause("XYZ");
    CPPUNIT_ASSERT(event.getCause() == "XYZ");
}

void EventTest::testGetTimestamp()
{
    Event event;
    time_t now = time(NULL);
    //CPPUNIT_ASSERT(event.getTimestamp() > 0L && event.getTimestamp() <= now);
}

void EventTest::testGetLevel()
{
    Event event("ABC", Level::FATAL);
    CPPUNIT_ASSERT(event.getLevel() == Level::FATAL);
}

void LoggingEventTest::testCtor()
{
    LoggingEvent event;
}

void LoggingEventTest::testCtorCopy()
{
    LoggingEvent eventA("test");
    LoggingEvent eventB(eventA);
    CPPUNIT_ASSERT(eventB.getCause() == "test");
}

void LoggingEventTest::testCtorArgs()
{
    LoggingEvent event("cause");
    CPPUNIT_ASSERT("cause" == event.getCause());
}

void LoggingEventTest::testCtorArgs2()
{
    LoggingEvent event("cause", "file", "class", "method", 12345);
    CPPUNIT_ASSERT(12345 == event.getLineNumber());
    CPPUNIT_ASSERT("cause" == event.getCause());
}

void LoggingEventTest::testAssignment()
{
    LoggingEvent eventA("cause", "file", "class", "method", 12345);
    LoggingEvent eventB = eventA;
    CPPUNIT_ASSERT(12345 == eventA.getLineNumber());
    CPPUNIT_ASSERT("cause" == eventA.getCause());
}

void LoggingEventTest::testGetFileName()
{
    LoggingEventTester test;
    CPPUNIT_ASSERT("EventTest.cc" == test.fileName());
}

void LoggingEventTest::testGetClassName()
{
    LoggingEventTester test;
    CPPUNIT_ASSERT("LoggingEventTester" == test.className());
}

void LoggingEventTest::testGetMethodName()
{
    LoggingEventTester test;
    CPPUNIT_ASSERT("methodName" == test.methodName());
}

void LoggingEventTest::testGetLineNumber()
{
    LoggingEventTester test;
    CPPUNIT_ASSERT(19 == test.lineNumber());
}

