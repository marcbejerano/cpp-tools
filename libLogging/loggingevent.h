#ifndef _HSLIB_LOGGINGEVENT_H_INCLUDED_
#define _HSLIB_LOGGINGEVENT_H_INCLUDED_

#include <Event>

namespace hslib {

    //! Logging Event
    /**
     * Logging event
     */
    class LoggingEvent : public Event
    {
        private:
            /** File name */
            std::string fileName;
            /** Class name */
            std::string className;
            /** Method name */
            std::string methodName;
            /** Line number */
            size_t lineNumber;
        public:
            /** 
             * Default constructor
             */
            LoggingEvent() : Event(), fileName(), className(), methodName(), lineNumber(0) { }
            /**
             * Copy constructor.
             * \param copy LoggingEvent object to copy.
             */
            LoggingEvent(const LoggingEvent& copy) : Event(copy), fileName(copy.fileName),
                className(copy.className), methodName(copy.methodName),
                lineNumber(copy.lineNumber)
            { }
            /**
             * Assignment operator.
             * \param copy LoggingEvent object to copy.
             * \return Reference to this object.
             */
            LoggingEvent& operator=(const LoggingEvent& copy) {
                Event::operator=(copy);
                this->fileName = copy.fileName;
                this->className = copy.className;
                this->methodName = copy.methodName;
                this->lineNumber = copy.lineNumber;
                return *this;
            }
            /**
             * Parameter constructor.
             * \param cause Cause of this event.
             * \param level Severity level of this event. Default value is Level::INFO.
             */
            LoggingEvent(const std::string& cause, const Level& level = Level::INFO) :
                Event(cause, level), fileName(), className(), methodName(), lineNumber(0)
            { }
            /**
             * Parameter constructor.
             * \param cause Cause of this event.
             * \param fileName File name
             * \param className Class name
             * \param methodName Method name
             * \param lineNumber Line number
             */
            LoggingEvent(const std::string& cause, const std::string& fileName,
                    const std::string& className, const std::string& methodName,
                    size_t lineNumber);
            /**
             * Parameter constructor.
             * \param cause Cause of this event.
             * \param level Severity level
             * \param fileName File name
             * \param className Class name
             * \param methodName Method name
             * \param lineNumber Line number
             */
            LoggingEvent(const std::string& cause, const Level& level, 
                    const std::string& fileName, const std::string& className,
                    const std::string& methodName, size_t lineNumber);
            /**
             * Return the filename
             * \return File name
             */
            const std::string getFileName() const { return fileName; }
            /**
             * Return the class name.
             * \return Class name.
             */
            const std::string getClassName() const { return className; }
            /**
             * Return the method name.
             * \return Method name.
             */
            const std::string getMethodName() const { return methodName; }
            /**
             * Return the line number.
             * \return Line number.
             */
            size_t getLineNumber() const { return lineNumber; }
    };

} // hslib

#define LOGGING_EVENT0(cause) LoggingEvent(cause, __FILE__, typeid(*this).name(), __func__, __LINE__)
#define LOGGING_EVENT(level, cause) LoggingEvent(cause, level, __FILE__, typeid(*this).name(), __func__, __LINE__)

#endif // _HSLIB_LOGGINGEVENT_H_INCLUDED_
