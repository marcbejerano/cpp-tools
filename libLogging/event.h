#ifndef _HSLIB_EVENT_H_INCLUDED_
#define _HSLIB_EVENT_H_INCLUDED_

#include <Level>
#include <string>
#include <ctime>

namespace hslib {

    //! General purpose event
    /**
     * General purpose event.
     */
    class Event
    {
        private:
            /** Cause of this event */
            std::string cause;
            /** Timestamp for this event */
            struct timespec ts;
            time_t timestamp;
            /** Severity level for this event */
            Level level;

        public:
            /**
             * Default constructor.
             */
            Event() : cause(), timestamp(time(NULL)), level(Level::INFO) { clock_gettime(CLOCK_MONOTONIC, &ts); }
            /**
             * Copy constructor.
             * \param copy Event object to copy.
             */
            Event(const Event& copy) : cause(copy.cause), ts(copy.ts), timestamp(copy.timestamp), level(copy.level) { }
            /**
             * Parameter constructor.
             * \param cause Cause of this event
             * \param level Severity level of this event.
             */
            explicit Event(const std::string& cause, const Level& level = Level::INFO) :
                cause(cause), timestamp(time(NULL)), level(level)
            {
                clock_gettime(CLOCK_MONOTONIC, &ts);
            }
            /**
             * Assignment operator.
             * \param copy Event object to copy.
             * \return Reference to this object.
             */
            Event& operator=(const Event& copy) {
                cause = copy.cause;
                ts = copy.ts;
                timestamp = copy.timestamp;
                level = copy.level;
                return *this;
            }
            /**
             * Return the cause of this event.
             * \return Cause of this event.
             */
            const std::string getCause() const { return cause; }
            /**
             * Set the cause of this event.
             * \param cause Cause of this event.
             * \return Reference to this object.
             */
            Event& setCause(const std::string& cause) { this->cause = cause; return *this; }

            const struct timespec& getTimespec() const { return ts; }
            /**
             * Return the timestamp for this event.
             * \return Timestamp for this event.
             */
            //const time_t getTimestamp() const { return timestamp; }
            /**
             * Return the severity level for this event.
             * \return Severity level.
             */
            Level getLevel() const { return level; }
    };
} // hslib

#endif // _HSLIB_EVENT_H_INCLUDED_
