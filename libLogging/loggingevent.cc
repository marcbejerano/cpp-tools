#include <LoggingEvent>
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

using namespace hslib;

LoggingEvent::LoggingEvent(const std::string& cause, const std::string& fileName,
        const std::string& className, const std::string& methodName,
        size_t lineNumber) :
    Event(cause), fileName(fileName), className(className),
    methodName(methodName), lineNumber(lineNumber)
{
    int status = -4;

    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(className.c_str(), NULL, NULL, &status),
            std::free
    };
    this->className = (status == 0 ? res.get() : className);
}

LoggingEvent::LoggingEvent(const std::string& cause, const Level& level,
        const std::string& fileName, const std::string& className,
        const std::string& methodName, size_t lineNumber) :
    Event(cause, level), fileName(fileName), className(className),
    methodName(methodName), lineNumber(lineNumber)
{
    int status = -4;

    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(className.c_str(), NULL, NULL, &status),
            std::free
    };
    this->className = (status == 0 ? res.get() : className);
}

