#ifndef _HSLIB_DATETIME_H_INCLUDED_
#define _HSLIB_DATETIME_H_INCLUDED_

#include <iostream>
#include <string>
#include <time.h>

class Time {
    private:
        time_t data;
    public:
        Time() : data(::time(NULL)) { }
        Time(const Time& copy) : data(copy.data) { }
        Time(struct tm& _tm) : data(::mktime(&_tm)) { }
        Time(const time_t t) : data(t) { }

        Time& operator=(const Time& copy) { data = copy.data; return *this; }
        Time& operator=(struct tm& _tm) { data = ::mktime(&_tm); return *this; }
        Time& operator=(const time_t t) { data = t; return *this; }

        const std::string toString(const std::string format = "%T") const;
    // operator -(Time)
    // operator +(Time)
    // toString(fmt)
    //
    // operator ==  != ---> !==
    // operator >   <= ---> !>
    // operator >=  <  ---> !>=
    // addSeconds   subSeconds ---> addSeconds(-val)
    // addMinutes   subMinutes ---> addMinutes(-val)
    // addHours     subHours ---> addHours(-val)
};

class Date {
    // ctor
    // ctor(copy)
    // ctor(struct tm&)
    // ctor(time_t)
    // operator =(copy)
    // operator =(struct tm&)
    // operator =(time_t)
    // operator -(Date)
    // operator +(Date)
    // toString(fmt)
    //
    // operator ==  != ---> !==
    // operator >   <= ---> !>
    // operator >=  <  ---> !>=
    // addDays      subDays ---> addDays(-val)
    // addMonths    subMonths ---> addMonths(-val)
    // addYears     subYears ---> addYears(-val)
};

class DateTime {
    // ctor
    // ctor(copy)
    // ctor(struct tm&)
    // ctor(time_t)
    // operator =(copy)
    // operator =(struct tm&)
    // operator =(time_t)
    // operator -(DateTime)
    // operator +(DateTime)
    // toString(fmt)
    //
    // operator ==  != ---> !==
    // operator >   <= ---> !>
    // operator >=  <  ---> !>=
    // addSeconds   subSeconds ---> addSeconds(-val)
    // addMinutes   subMinutes ---> addMinutes(-val)
    // addHours     subHours ---> addHours(-val)
    // addDays      subDays ---> addDays(-val)
    // addMonths    subMonths ---> addMonths(-val)
    // addYears     subYears ---> addYears(-val)
};

#endif // _HSLIB_DATETIME_H_INCLUDED_
