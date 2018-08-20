#ifndef _HSLIB_LOGGER_H_INCLUDED_
#define _HSLIB_LOGGER_H_INCLUDED_

#include <Appender>
#include <Level>
#include <LoggingEvent>
#include <list>

namespace hslib {

    //! Event logger
    /**
     * Event Logger
     */
    class Logger
    {
        private:
            /** Name of this logger */
            std::string name;
            /** Minimum severity level */
            Level minimumLevel;
            /** Collection of appenders */
            std::list<Appender*> appenders;
        public:
            /**
             * Parameter constructor.
             * \param name Name of this logger
             * \param level Minimum severity level for this logger.
             */
            Logger(const std::string& name, const Level& level = Level::INFO)
                : name(name), minimumLevel(level), appenders()
            { }
            /**
             * Copy constructor.
             * \param copy Logger object to copy.
             */
            Logger(const Logger& copy) : name(copy.name), minimumLevel(copy.minimumLevel), appenders()
            { appenders.assign(copy.appenders.begin(), copy.appenders.end()); }
            /**
             * Assignment operator.
             * \param copy Logger object to copy.
             * \return Reference to this object.
             */
            Logger& operator=(const Logger& copy) {
                name = copy.name;
                minimumLevel = copy.minimumLevel;
                appenders.assign(copy.appenders.begin(), copy.appenders.end());
                return *this;
            }
            /**
             * Return the name of this logger.
             * \return Name of this logger.
             */
            const std::string getName() const { return name; }
            /**
             * Return the minimum severity level for this logger.
             * \return Minimum severity level.
             */
            const Level getMinimumLevel() const { return minimumLevel; }
            /**
             * Set the minimum severity level for this logger.
             * \param level Severity level.
             * \return Reference to this object.
             */
            Logger& setMinimumLevel(const Level& level) { minimumLevel = level; return *this; }
            /**
             * Add an appender to this loggers list of appenders. When an event is
             * logged then each appender processes the logging event.
             * \param appender Pointer to an appender.
             * \return Reference to this object.
             */
            Logger& addAppender(Appender* appender) { appenders.push_back(appender); return *this; }
            /**
             * Return the collection of appenders for this logger.
             * \return Collection of appenders.
             */
            std::list<Appender*> getAppenders() { return appenders; }
            /**
             * Log the given logging event to all of this logger's appenders.
             * \param message Logging message
             * \return Reference to this object.
             */
            Logger& log(const std::string& message);
            /**
             * Log the given logging event to all of this logger's appenders.
             * \param event Logging event
             * \return Reference to this object.
             */
            Logger& log(const LoggingEvent& event);
            /**
             * Set the minimum logging severity level
             * \param level Severity level
             * \return Reference to this object.
             */
            Logger& operator<<(const Level& level) { minimumLevel = level; return *this; }
            /**
             * Log the given logging event to all of this logger's appenders. This
             * method just calls log() with the given logging event. This method and
             * the one above it (level) are designed to be used as follows:<br/>
             * <pre>
             * Logger logger(...)
             * logger << Level::DEBUG << event;
             * </pre>
             * \param event Logging event.
             * \return Reference to this object.
             */
            Logger& operator<<(const LoggingEvent& event) { log(event); return *this; }
    };

} // hslib

#endif // _HSLIB_LOGGER_H_INCLUDED_
