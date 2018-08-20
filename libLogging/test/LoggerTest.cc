#include "LoggerTest.h"
#include <Logger>
#include <sstream>

using namespace hslib;

class StringBufferAppender : public Appender
{
    private:
        std::stringstream buffer;
    public:
        StringBufferAppender() : Appender(), buffer() { }
        StringBufferAppender(const StringBufferAppender& copy) : Appender(copy), buffer() { }
        virtual const size_t log(const LoggingEvent& event) {
            PatternLayout p(getLayout());
            const std::string formatted = p.format(event);
            buffer << formatted;
            return formatted.length();
        }
        const std::string str() { return buffer.str(); }
};


void LoggerTest::testCtorArgs()
{
    Logger logger("testCtorArgs");
}

void LoggerTest::testCtorCopy()
{
    Logger logger("testCtorCopy");
    Logger copy(logger);
    CPPUNIT_ASSERT("testCtorCopy" == copy.getName());
}

void LoggerTest::testAssignment()
{
    Logger logger("testAssignment");
    Logger copy = logger;
    CPPUNIT_ASSERT("testAssignment" == logger.getName());
}

void LoggerTest::testGetName()
{
    Logger logger("testGetName");
    CPPUNIT_ASSERT("testGetName" == logger.getName());
}

void LoggerTest::testGetMinimumLevel()
{
    Logger logger("testGetMinimumLevel");
    CPPUNIT_ASSERT(Level::INFO  == logger.getMinimumLevel());
}

void LoggerTest::testSetMinimumLevel()
{
    Logger logger("testGetMinimumLevel");
    CPPUNIT_ASSERT(Level::INFO  == logger.getMinimumLevel());
    logger.setMinimumLevel(Level::FATAL);
    CPPUNIT_ASSERT(Level::FATAL  == logger.getMinimumLevel());
}

void LoggerTest::testAddAppender()
{
    StringBufferAppender ap;
    Logger logger("testAddAppender");
    std::list<Appender*> a = logger.getAppenders();
    CPPUNIT_ASSERT(a.size() == 0);
    logger.addAppender(&ap);
    a = logger.getAppenders();
    CPPUNIT_ASSERT(a.size() == 1);
}

void LoggerTest::testGetAppenders()
{
    StringBufferAppender ap;
    Logger logger("testGetAppenders");
    std::list<Appender*> a = logger.getAppenders();
    CPPUNIT_ASSERT(a.size() == 0);
    logger.addAppender(&ap);
    a = logger.getAppenders();
    CPPUNIT_ASSERT(a.size() == 1);
}

void LoggerTest::testLog()
{
    StringBufferAppender ap;
    Logger logger("testLog");
    logger.addAppender(&ap);
    LoggingEvent event = LOGGING_EVENT(Level::INFO, "test");
    logger.log(event);
    CPPUNIT_ASSERT("test\n" == ap.str());
}

void LoggerTest::testOpLevel()
{
    Logger logger("testOpLevel");
    CPPUNIT_ASSERT(Level::INFO  == logger.getMinimumLevel());
    logger << Level::FATAL;
    CPPUNIT_ASSERT(Level::FATAL  == logger.getMinimumLevel());
}

void LoggerTest::testOpLoggingEvent()
{
    StringBufferAppender ap;
    Logger logger("testLog");
    logger.addAppender(&ap);
    LoggingEvent event = LOGGING_EVENT(Level::INFO, "test");
    logger << Level::TRACE << event;
    CPPUNIT_ASSERT(ap.str().empty());
    logger << Level::OFF << event;
    CPPUNIT_ASSERT("test\n" == ap.str());
}

