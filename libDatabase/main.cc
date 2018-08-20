#include "variant.h"
#include "datetime.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
#if 0
    Variant v('a');
    Variant v2(1.23);

    cout << v.toChar() << endl;
    cout << v2.toDouble() << endl;
    cout << v2.toInt() << endl;
    cout << v.toString() << endl << v2.toString() << endl;

    // Date, Time, DateTime, Timestamp data types
    time_t now = ::time(NULL);
    struct tm* tm_ = localtime(&now);
    char buffer[128] = {0};
    ::strftime(buffer, sizeof(buffer), "%F %T", tm_);
    cout << buffer << endl;
    
    struct tm old = { 1, 2, 113, 0, 0, -6, 0, 0, 0 };
    Time timeB(old);
    cout << timeB.toString() << endl;
    time_t old_time = ::mktime(&old);
    tm_ = localtime(&old_time);
    ::strftime(buffer, sizeof(buffer), "%F %T", tm_);
    cout << buffer << endl;

    time_t timer_time = 0L;
    tm_ = localtime(&timer_time);
    ::strftime(buffer, sizeof(buffer), "%F %T", tm_);
    cout << buffer << endl;

    // update Variant to handle time data types
    // database record
    // property system using variants
    // Table, Column, Row
    // Connection
#endif


    struct timespec ts;
    int rc = clock_gettime(CLOCK_MONOTONIC, &ts);
    size_t hours = ts.tv_sec / 60 / 60;
    size_t minutes = (ts.tv_sec - (hours * 3600)) / 60;
    size_t seconds = (ts.tv_sec - (hours * 3600) - (minutes * 60));
    cout << (hours<10?"0":"") << hours
         << ":"
         << (minutes<10?"0":"") << minutes
         << ":"
         << (seconds<10?"0":"") << seconds
         << "."
         << ts.tv_nsec << endl;
    return 0;
}

