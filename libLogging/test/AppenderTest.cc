#include "AppenderTest.h"
#include <Appender>

using namespace hslib;

void AppenderTest::testCtor()
{
    ConsoleAppender appender;
}

void AppenderTest::testCtorCopy()
{
    ConsoleAppender appenderA;
    appenderA.setLayout(PatternLayout("%d %m%n"));
    ConsoleAppender appenderB(appenderA);
    CPPUNIT_ASSERT(appenderA.getLayout().getPattern() == appenderB.getLayout().getPattern());
}

void AppenderTest::testCtorArgs()
{
    ConsoleAppender appender(PatternLayout("%d %m%n"), Level::TRACE);
    CPPUNIT_ASSERT(appender.getLayout().getPattern() == "%d %m%n");
    CPPUNIT_ASSERT(appender.getMinimumLevel() == Level::TRACE);
}

void AppenderTest::testAssignment()
{
    ConsoleAppender appenderA;
    appenderA.setLayout(PatternLayout("%d %m%n"));
    ConsoleAppender appenderB = appenderA;
    CPPUNIT_ASSERT(appenderA.getLayout().getPattern() == appenderB.getLayout().getPattern());
}

void AppenderTest::testGetLayout()
{
    ConsoleAppender appender(PatternLayout("%d %m%n"), Level::TRACE);
    CPPUNIT_ASSERT(appender.getLayout().getPattern() == "%d %m%n");
}

void AppenderTest::testSetLayout()
{
    ConsoleAppender appender;
    appender.setLayout(PatternLayout("%d %m%n"));
    CPPUNIT_ASSERT(appender.getLayout().getPattern() == "%d %m%n");
}

void AppenderTest::testGetMinimumLevel()
{
    ConsoleAppender appender;
    CPPUNIT_ASSERT(appender.getMinimumLevel() == Level::INFO);
}

void AppenderTest::testSetMinimumLevel()
{
    ConsoleAppender appender;
    CPPUNIT_ASSERT(appender.getMinimumLevel() == Level::INFO);
    appender.setMinimumLevel(Level::ERROR);
    CPPUNIT_ASSERT(appender.getMinimumLevel() == Level::ERROR);
}

