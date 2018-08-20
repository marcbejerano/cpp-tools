#include "datetime.h"

const std::string Time::toString(const std::string format) const
{
    const struct tm* local = ::localtime(&data);
    int hours = local->tm_hour;
    int minutes = local->tm_min;
    int seconds = local->tm_sec;
    int yday = local->tm_yday;

    hours += (yday * 24);
    std::cout << "yday:" << yday << " H:" << hours << " M:" << minutes << " S:" << seconds << std::endl;
    return "";
}

