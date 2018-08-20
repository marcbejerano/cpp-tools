#include <Logger>

using namespace hslib;

Logger& Logger::log(const std::string& message)
{
    for (auto ix = appenders.begin(); ix != appenders.end(); ++ix) {
        Appender* appender = *ix;
        appender->log(LoggingEvent(message));
    }
    return *this;
}

Logger& Logger::log(const LoggingEvent& event)
{
    if (getMinimumLevel().isMoreSpecificThan(event.getLevel())) {
        for (auto ix = appenders.begin(); ix != appenders.end(); ++ix) {
            Appender* appender = *ix;
            appender->log(event);
        }
    }
    return *this;
}

