#include <Appender>
#include <Tools>
#include <iostream>
#include <fstream>

using namespace hslib;

std::mutex Appender::lock;

const size_t ConsoleAppender::log(const LoggingEvent& event)
{
    PatternLayout p = getLayout();
    std::string text = p.format(event);

    size_t bytes_written = 0;
    if (getMinimumLevel().isMoreSpecificThan(event.getLevel())) {
        lock.lock();
        if (event.getLevel().isMoreSpecificThan(Level::ERROR))
            std::cerr << text;
        else
            std::cout << text;
        bytes_written = text.length();
        lock.unlock();
    }
    return bytes_written;
}

const size_t FileAppender::log(const LoggingEvent& event)
{
    PatternLayout p = getLayout();
    std::string text = p.format(event);

    size_t bytes_written = 0;
    if (getMinimumLevel().isMoreSpecificThan(event.getLevel())) {
        lock.lock();
        std::ofstream out(getFilename(), std::ofstream::out | std::ofstream::app);
        out << text;
        out.close();
        bytes_written = text.length();
        lock.unlock();
    }
    return bytes_written;
}

