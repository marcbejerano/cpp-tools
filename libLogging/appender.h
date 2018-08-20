#ifndef _HSLIB_APPENDER_H_INCLUDED_
#define _HSLIB_APPENDER_H_INCLUDED_

#include <mutex>
#include <string>
#include <Level>
#include <LoggingEvent>
#include <PatternLayout>
#include <iostream>

namespace hslib {

    //! Logging output appender class
    /**
     * Generic appender. This class MUST be extended by a child class in order to
     * provide any actual functionality (due to the pure virtual method: log). The
     * lock mutex semaphore is provided for the use of child classes to control
     * resource usage and limit the possibility of data overwrite.
     */
    class Appender
    {
        private:
            /** Pattern layout for this appender */
            PatternLayout layout;
            /** Minimum logging level allowed by this appender */
            Level minLevel;
        protected:
            /** Mutex semaphore to resource locking */
            static std::mutex lock;
        public:
            /**
             * Default constructor.
             */
            Appender() : layout(), minLevel(Level::INFO) { }
            /**
             * Vritual destructor to satisfy expected deallocation behavior
             */
            virtual ~Appender() { }
            /**
             * Parameter constructor that takes a PatternLayout and a minimum
             * Level to limit which events get processed.
             * \param layout Pattern layout
             * \param level Minimum logging level
             */
            explicit Appender(const PatternLayout& layout, const Level& level = Level::INFO)
                : layout(layout), minLevel(level) { }
            /**
             * Copy constructor.
             * \param copy Appender to copy
             */
            Appender(const Appender& copy) : layout(copy.layout), minLevel(copy.minLevel) { }
            /**
             * Assignment operator.
             * \param copy Appender to copy
             * \return Refernce to this object.
             */
            Appender& operator=(const Appender& copy) {
                layout = copy.layout;
                minLevel = copy.minLevel;
                return *this;
            }
            /**
             * Process the given logging event.
             * \param event Logging event to process
             * \return Number of bytes processed.
             */
            virtual const size_t log(const LoggingEvent& event) = 0;
            /**
             * Return the current pattern layout.
             * \return Pattern layout.
             */
            const PatternLayout getLayout() const { return layout; }
            /**
             * Set the pattern layout.
             * \param layout Hte new pattern layout.
             * \return Reference to this object
             */
            Appender& setLayout(const PatternLayout& layout) { this->layout = layout; return *this; }
            /**
             * Return the minimum logging level allowed by this appender.
             * \return Minimum logging level.
             */
            const Level getMinimumLevel() const { return minLevel; }
            /**
             * Set the minimum logging level allowed by this appender. Any
             * events with a level that exceeds the granularity of the minimum
             * level will beignored.
             * \param level Minimum logging level
             * \return Reference to this object.
             */
            Appender& setMinimumLevel(const Level& level) { this->minLevel = level; return *this; }
    };

    //! Logging output appender class (Console)
    /**
     * Console appender. All output is sent to the console. If the severity level
     * if ERROR or higher then the output is sent to std::cerr else the output
     * will be sent to std::cout.
     */
    class ConsoleAppender : public Appender
    {
        public:
            /**
             * Default constructor
             */
            ConsoleAppender() : Appender() { }
            /**
             * Parameter constructor that takes a PatternLayout and a minimum
             * Level to limit which events get processed.
             * \param layout Pattern layout
             * \param level Minimum logging level
             */
            explicit ConsoleAppender(const PatternLayout& layout, const Level& level = Level::INFO)
                : Appender(layout, level) { }
            /**
             * Copy constructor.
             * \param copy Appender to copy
             */
            ConsoleAppender(const ConsoleAppender& copy) : Appender(copy) { }
            /**
             * Assignment operator.
             * \param copy Appender to copy
             * \return Refernce to this object.
             */
            ConsoleAppender& operator=(const ConsoleAppender& copy) {
                Appender::operator=(copy);
                return *this;
            }
            /**
             * Process the given logging event.
             * \param event Logging event to process
             * \return Number of bytes processed.
             */
            virtual const size_t log(const LoggingEvent& event);
    };

    //! Logging output appender class (Log file)
    /**
     * Standard file appender
     */
    class FileAppender : public Appender
    {
        private:
            /** Log file name */
            std::string filename;
            /** Append to file on initial object creation */
            bool append;
        public:
            /**
             * Default constructor.
             */
            FileAppender() : filename("log"), append(true) { }
            /**
             * Parameter constructor that takes a PatternLayout and a minimum
             * Level to limit which events get processed.
             * \param layout Pattern layout
             * \param level Minimum logging level
             */
            explicit FileAppender(const PatternLayout& layout, const Level& level = Level::INFO)
                : Appender(layout, level), filename("log"), append(true) { }
            /**
             * Copy constructor.
             * \param copy Appender to copy
             */
            FileAppender(const FileAppender& copy) : Appender(copy), filename(copy.filename), append(copy.append) { }
            /**
             * Assignment operator.
             * \param copy Appender to copy
             * \return Refernce to this object.
             */
            FileAppender& operator=(const FileAppender& copy) {
                Appender::operator=(copy);
                filename = copy.filename;
                append = copy.append;
                return *this;
            }
            /**
             * Return the filename (relative or absolute file path) of the log file.
             * \return Filename of the log file
             */
            const std::string getFilename() const { return filename; }
            /**
             * Set the name of the log file.
             * \param filename Name, relative path, or absolute path of the log file.
             * \return Reference to this object.
             */
            FileAppender& setFilename(const std::string& filename) { this->filename = filename; return *this; }
            /**
             * Return the state of the log file append flag.
             * \return Logfile append flag
             */
            const bool isAppend() const { return append; }
            /**
             * Set the state of the append file flag. If this is set to true then on
             * the first log item being written the log file, if existing, will be
             * appended to. If this is set to false then, upon first open, the log
             * file will be truncated.
             * \param append Append flag state
             * \return Reference to this object.
             */
            FileAppender& setAppend(bool append) { this->append = append; return *this; }
            /**
             * Process the given logging event.
             * \param event Logging event to process
             * \return Number of bytes processed.
             */
            virtual const size_t log(const LoggingEvent& event);
    };

} // hslib

#endif // _HSLIB_APPENDER_H_INCLUDED_
