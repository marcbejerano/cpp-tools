#include "LogFactoryTest.h"
#include <LogFactory>

using namespace hslib;

void LogFactoryTest::testGetLogger()
{
    LogFactory& factory = LogFactory::getInstance();
    Logger& logger = factory.getLogger("root");
    CPPUNIT_ASSERT("rootLogger" == logger.getName());
    logger = factory.getLogger("rootXX");
    CPPUNIT_ASSERT("rootLogger" == logger.getName());
    logger = factory.getLogger("LogFactoryTest");
    CPPUNIT_ASSERT("LogFactoryTest" == logger.getName());
    CPPUNIT_ASSERT(logger.getMinimumLevel() == Level::INFO);
    logger.log("This is a test");
    logger.log(LOGGING_EVENT(Level::OFF,   "testing OFF"));
    logger.log(LOGGING_EVENT(Level::FATAL, "testing FATAL"));
    logger.log(LOGGING_EVENT(Level::ERROR, "testing ERROR"));
    logger.log(LOGGING_EVENT(Level::WARN,  "testing WARN"));
    logger.log(LOGGING_EVENT(Level::INFO,  "testing INFO"));
    logger.log(LOGGING_EVENT(Level::DEBUG, "testing DEBUG"));
    logger.log(LOGGING_EVENT(Level::TRACE, "testing TRACE"));
    logger.log(LOGGING_EVENT(Level::ALL,   "testing ALL"));
}

