/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
  ***************************************************************************/
#include<os.h>
#include<DataType.h>

#define SmallestValJulDate (1721426)

Date::Date(int year, int month, int day)
    { YMDToJulian(year, month, day, julianDate); }
int Date::set(int year, int month, int day)
    { return YMDToJulian(year,month,day,julianDate); }
int Date::get(int &year, int &month, int &day) const
    { return julianToYMD(julianDate,year,month,day); }

int Date::parseFrom(const char *s) {
    int month,day,year;
    int count;
    count = sscanf(s,"%d/%d/%d",&month,&day,&year);
    if (count < 3) return -1;

    if (year < 100) year += 1900;

    if (!isValidDate(year, month, day))
        return -1;

    return set(year,month,day);
}

int Date::dayOfMonth() const {
    int year, month, day;
    get(year,month,day);
    return day;
}
int Date::month() const {
    int year, month, day;
    get(year,month,day);
    return month;
}
int Date::year() const {
    int year, month, day;
    get(year,month,day);
    return year;
}

int Date::dayOfWeek() const { return dayOfWeek(julianDate); }

const char *Date::dayOfWeekName() const
    { return dayOfWeekName(dayOfWeek(julianDate)); }

const char *Date::dayOfWeekAbbr() const
    { return dayOfWeekAbbr(dayOfWeek(julianDate)); }

static const char *day_names[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};
static const char *day_abbrs[] = {
    "Sun",    "Mon",    "Tue",     "Wed",       "Thu",      "Fri",    "Sat"
};

static const char *month_names[] = {
    "January", "February", "March",     "April",   "May",      "June",
    "July",    "August",   "September", "October", "November", "December"
};
static const char *month_abbrs[] = {
    "Jan",     "Feb",      "Mar",      "Apr",     "May",      "Jun",
    "Jul",     "Aug",      "Sep",      "Oct",     "Nov",      "Dec"
};


static int daysBeforeMonth[] = {
0,  31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
};
static int days_per_month[] = {
    31, 28, 31,  30,   31, 30,  31,  31,  30,  31,  30,  31
};

const char * Date::dayOfWeekName(int day)
    { return (day < 1 || day > 7) ? 0 : day_names[day-1]; }

const char * Date::dayOfWeekAbbr(int day)
    { return (day < 1 || day > 7) ? 0 : day_abbrs[day-1]; }

const char * Date::monthName() const { return monthName(month()); }
const char * Date::monthAbbr() const { return monthAbbr(month()); }
const char * Date::monthName(int month)
    { return (month < 1 || month > 12) ? 0 : month_names[month-1]; }
const char * Date::monthAbbr(int month)
    { return (month < 1 || month > 12) ? 0 : month_abbrs[month-1]; }
Date operator+(const Date &d1, int days)
    { return Date(d1.julianDate + days); }
Date operator+(int days, const Date &d1)
    { return Date(d1.julianDate + days); }
Date operator-(const Date &d1, int days)
    { return Date(d1.julianDate - days); }

int operator-(const Date &d1, const Date& d2)
    { return d1.julianDate - d2.julianDate; }

int operator<(const Date &d1 ,const Date &d2 )
    { return d1.julianDate < d2.julianDate; }
int operator>(const Date &d1 ,const Date &d2 )
    { return d1.julianDate > d2.julianDate; }
int operator<=(const Date &d1 ,const Date &d2 )
    { return d1.julianDate <= d2.julianDate; }
int operator>=(const Date &d1 ,const Date &d2 )
    { return d1.julianDate >= d2.julianDate; }
int operator==(const Date &d1 ,const Date &d2 )
    { return d1.julianDate == d2.julianDate; }
int operator!=(const Date &d1 ,const Date &d2 )
    { return d1.julianDate != d2.julianDate; }

bool Date::isValid() const
    { return julianDate >= SmallestValJulDate; }

bool Date::isLeapYear(int year)
{
    return (year % 400 == 0) || ((year % 4 == 0) && !(year % 100 == 0));
}

int Date::dayOfYear() const {
    int year,month,day;
    get(year,month,day);
    int tmp = daysBeforeMonth[month-1];
    if (month >= 3 && isLeapYear(year))
        tmp++;
    return tmp + day;
}

int Date::daysInMonth(int month, int year) {
    --month;
    int tmp = days_per_month[month];
    if (month == 1 && isLeapYear(year)) tmp++;
    return tmp;
}

bool Date::isValidDate(int year, int month, int day) {
    if (year  < 1 || year  > 10000) return false;
    if (month < 1 || month > 12) return false;
    return (day >= 1) && (day <= daysInMonth(month,year));
}

// Algorithm Author: Robert G. Tantzen
int Date::YMDToJulian(int year, int mon, int day, JulianRep &jul) {
    if (!isValidDate(year, mon, day))
        { jul = (JulianRep)0; return -1; }

    // year, month, day are assumed to be valid
    int m = mon, d = day, y = year;
    int c, ya, j;

    if (m > 2) m -= 3;
    else { m += 9; --y; }
    c = y/100;
    ya = y - (100 * c);
    j = (146097*c)/4 + (1461*ya)/4 + (153*m+2)/5 + d + 1721119;
    jul = (JulianRep)j;
    return 0;
}

// Julian date converter. Takes a julian date (the number of days since some
// distant epoch or other), and returns month, day of month, and year in
// integer references.
// Algorithm Author: Robert G. Tantzen
int Date::dayOfWeek(JulianRep jul) {
    return (int)((jul+1)%7+1);
}

int Date::julianToYMD(JulianRep jul, int &year, int &month, int &day) {
    int j = jul;
    int d, m, y;

    if (j < SmallestValJulDate)
        { year = month = day = 0; return -1; }

    j -= 1721119;
    y = (4 * j - 1)/146097;
    j = 4 * j - 1 - 146097 * y;
    d = j/4;
    j = (4 * d + 3)/1461;
    d = 4 * d + 3 - 1461 * j;
    d = (d + 4)/4;
    m = (5 * d - 3)/153;
    d = 5 * d - 3 - 153 * m;
    d = (d + 5) / 5;
    y = 100 * y + j;
    if (m < 10) m += 3;
    else { m -= 9; ++y; }
    month = m;
    day = d;
    year = y;
    return 0;
}

#define MAX_VALID_SECONDS (60 * 60 * 24 -1)
Time::Time(int hours, int mins, int secs, int usec)
    { set(hours,mins,secs, usec); }

int Time::set(int hours, int mins, int secs, int usec) {
        if((hours | mins | secs | usec) < 0) { timeVal = -1; return -1; }
        if(hours >= 24 | mins >= 60 | secs >= 62)
                { timeVal = -1; return -1; }
        timeVal = secs + mins * 60 + hours * 3600;
        timeVal *= 10000;
        if(usec) timeVal += usec/100;
        return 0;
}

int Time::get(int &hours, int &mins, int &secs) const {
    if (timeVal < 0) return -1;
    int s = timeVal/10000;
    secs = s % 60;
    s /= 60;
    mins = s % 60;
    s /= 60;
    hours = s;
    return 0;
}

int Time::seconds() const { return (timeVal/10000) % 60; }
int Time::minutes() const { return (timeVal /(60*10000)) % 60; }
int Time::hours() const   { return timeVal / (3600*10000); }
int Time::msec() const { return (timeVal % 10000) / 10; }
int Time::usec() const { return (timeVal % 10000) * 100; }

int Time::setMsec(int ms) {
        if(ms < 0 || ms >= 1000) return -1;
        timeVal = timeVal+(10*ms);
    return 0;
}
int Time::setUsec(int us) {
        if(us < 0 || us >= 1000000) return -1;
        timeVal = timeVal +us/100;
    return 0;
}

bool Time::isValid() const
    { return timeVal >= 0 && timeVal <= (10000*(MAX_VALID_SECONDS+1)-1); }

bool Time::isValidTime(int hours, int mins, int secs) {
    return (hours >= 0 && hours < 24) &&
           (mins >= 0 && mins < 60) &&
           (secs >= 0 && secs < 60);
}

Time operator+(const Time &t1, int seconds)
    { return Time(t1.timeVal + seconds*10000); }
Time operator+(int seconds, const Time &t1)
    { return Time(t1.timeVal + seconds*10000); }
Time operator-(const Time &t1, int seconds)
    { return Time(t1.timeVal - seconds*10000); }

int operator-(const Time &t1, const Time& t2)
    { return (t1.timeVal - t2.timeVal)/10000; }

int operator<(const Time &t1 ,const Time &t2 )
    { return t1.timeVal < t2.timeVal; }
int operator>(const Time &t1 ,const Time &t2 )
    { return t1.timeVal > t2.timeVal; }
int operator<=(const Time &t1 ,const Time &t2 )
    { return t1.timeVal <= t2.timeVal; }
int operator>=(const Time &t1 ,const Time &t2 )
    { return t1.timeVal >= t2.timeVal; }
int operator==(const Time &t1 ,const Time &t2 )
    { return t1.timeVal == t2.timeVal; }
int operator!=(const Time &t1 ,const Time &t2 )
    { return t1.timeVal != t2.timeVal; }

int Time::parseFrom(const char *s) {
    int hours,mins,secs;
    int count;
    count = sscanf(s,"%d:%d:%d",&hours,&mins,&secs);
    if (count < 2) return -1;
    if (count == 2) secs = 0;

    if (!isValidTime(hours,mins,secs))
        return -1;
    return set(hours,mins,secs);
}

int operator< (const TimeStamp &d1,  const TimeStamp &d2)
    { return (d1.date != d2.date) ? d1.date < d2.date : d1.time < d2.time; }
int operator> (const TimeStamp &d1,  const TimeStamp &d2)
    { return (d1.date != d2.date) ? d1.date > d2.date : d1.time > d2.time; }
int operator<=(const TimeStamp &d1, const TimeStamp &d2)
    { return (d1.date != d2.date) ? d1.date < d2.date : d1.time <= d2.time; }
int operator>=(const TimeStamp &d1, const TimeStamp &d2)
    { return (d1.date != d2.date) ? d1.date > d2.date : d1.time >= d2.time; }
int operator==(const TimeStamp &d1, const TimeStamp &d2)
    { return d1.date == d2.date && d1.time == d2.time; }
int operator!=(const TimeStamp &d1, const TimeStamp &d2)
    { return d1.date != d2.date && d1.time != d2.time; }


long AllDataType::size(DataType type)
{
    long size = 0;
    switch(type)
    {
        case typeInt:
            size = sizeof(int);
            break;
        case typeLong:
            size = sizeof(long);
            break;
        case typeLongLong:
            size = sizeof(long long);
            break;
        case typeShort:
            size = sizeof(short);
            break;
        case typeByteInt:
            size = sizeof(char);
            break;
        case typeDouble:
            size = sizeof(double);
            break;
        case typeFloat:
            size = sizeof(float);
            break;
        case typeDecimal:
            //TODO::for porting
            //fldDef.length_ = sizeof(long double);
            break;
        case typeDate:
            size = sizeof(Date);
            break;
        case typeTime:
            size = sizeof(Time);
            break;
        case typeTimeStamp:
            size = sizeof(TimeStamp);
            break;
        default:
            size  = 0;
            break;
    }
    return size;
}

void AllDataType::copyVal(void* dest, void *src, DataType type, int length)
{
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)src;
            break;
        case typeLong:
            *(long*)dest = *(long*)src;
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)src;
            break;
        case typeShort:
            *(short*)dest = *(short*)src;
            break;
        case typeByteInt:
            *(char*)dest = *(char*)src;
            break;
        case typeDouble:
            *(double*)dest = *(double*)src;
            break;
        case typeFloat:
            *(float*)dest = *(float*)src;
            break;
        case typeDecimal:
            //TODO::for porting
        case typeDate:
            *(Date*)dest = *(Date*)src;
            break;
        case typeTime:
            *(Time*)dest = *(Time*)src;
            break;
        case typeTimeStamp:
            *(TimeStamp*)dest = *(TimeStamp*)src;
            break;
        case typeString: 
            {
                strncpy((char*)dest, (char*)src, length);
                char *d =(char*)dest;
                d[length-1] = '\0';
                break;
            }
        case typeBinary:
            os::memcpy((char*)dest, (char*)src, length);
            break;
        default:
            break;
        }
}

bool AllDataType::compareVal(void *val1, void *val2, ComparisionOp op,
                             DataType type, long length)
{
    bool result = false;
        switch(type)
        {
       case typeInt:
           result = AllDataType::compareIntVal(val1, val2, op );
           break;
       case typeLong:
           result = AllDataType::compareLongVal(val1, val2, op);
           break;
       case typeLongLong:
           result = AllDataType::compareLongLongVal(val1, val2, op);
           break;
       case typeShort:
           result = AllDataType::compareShortVal(val1, val2, op);
           break;
       case typeByteInt:
           result = AllDataType::compareByteIntVal(val1, val2, op);
           break;
       case typeDouble:
           result = AllDataType::compareDoubleVal(val1, val2, op);
           break;
       case typeFloat:
           result = AllDataType::compareFloatVal(val1, val2, op);
           break;
       case typeDecimal:
           //TODO::for porting
           break;
       case typeDate:
           result = AllDataType::compareDateVal(val1, val2, op);
           break;
       case typeTime:
           result = AllDataType::compareTimeVal(val1, val2, op);
           break;
       case typeTimeStamp:
           result = AllDataType::compareTimeStampVal(val1, val2, op);
           break;
       case typeString:
           result = AllDataType::compareStringVal(val1, val2, op);
           break;
       case typeBinary:
           result = AllDataType::compareBinaryVal(val1, val2, op, length);
           break;
    }
    return result;
}

bool AllDataType::compareIntVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(int*)src1 == *(int*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(int*)src1 != *(int*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(int*)src1 < *(int*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(int*)src1 <= *(int*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(int*)src1 > *(int*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(int*)src1 >= *(int*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareLongVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(long*)src1 == *(long*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(long*)src1 != *(long*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(long*)src1 < *(long*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(long*)src1 <= *(long*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(long*)src1 > *(long*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(long*)src1 >= *(long*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareLongLongVal(void* src1, void *src2,
                                      ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(long long*)src1 == *(long long*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(long long*)src1 != *(long long*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(long long*)src1 < *(long long*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(long long*)src1 <= *(long long*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(long long*)src1 > *(long long*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(long long*)src1 >= *(long long*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareShortVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(short*)src1 == *(short*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(short*)src1 != *(short*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(short*)src1 < *(short*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(short*)src1 <= *(short*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(short*)src1 > *(short*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(short*)src1 >= *(short*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareByteIntVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(ByteInt*)src1 == *(ByteInt*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(ByteInt*)src1 != *(ByteInt*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(ByteInt*)src1 < *(ByteInt*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(ByteInt*)src1 <= *(ByteInt*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(ByteInt*)src1 > *(ByteInt*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(ByteInt*)src1 >= *(ByteInt*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareDoubleVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(double*)src1 == *(double*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(double*)src1 != *(double*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(double*)src1 < *(double*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(double*)src1 <= *(double*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(double*)src1 > *(double*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(double*)src1 >= *(double*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareFloatVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(float*)src1 == *(float*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(float*)src1 != *(float*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(float*)src1 < *(float*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(float*)src1 <= *(float*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(float*)src1 > *(float*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(float*)src1 >= *(float*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareDateVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(Date*)src1 == *(Date*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(Date*)src1 != *(Date*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(Date*)src1 < *(Date*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(Date*)src1 <= *(Date*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(Date*)src1 > *(Date*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(Date*)src1 >= *(Date*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareTimeVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(Time*)src1 == *(Time*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(Time*)src1 != *(Time*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(Time*)src1 < *(Time*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(Time*)src1 <= *(Time*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(Time*)src1 > *(Time*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(Time*)src1 >= *(Time*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareTimeStampVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(TimeStamp*)src1 == *(TimeStamp*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(TimeStamp*)src1 != *(TimeStamp*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(TimeStamp*)src1 < *(TimeStamp*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(TimeStamp*)src1 <= *(TimeStamp*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(TimeStamp*)src1 > *(TimeStamp*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(TimeStamp*)src1 >= *(TimeStamp*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareStringVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    int ret = strcmp((char*)src1, (char*)src2);
    switch(op)
    {
        case OpEquals:
            if (ret == 0 ) result= true; else result = false;
            break;
        case OpNotEquals:
            if (ret != 0 ) result= true; else result = false;
            break;
        case OpLessThan:
            if (ret < 0 ) result= true; else result = false;
            break;
        case OpLessThanEquals:
            printf("Illegal Operator:Not Supported for String\n");
            break;
        case OpGreaterThan:
            if (ret > 0 ) result= true; else result = false;
            break;
        case OpGreaterThanEquals:
            printf("Illegal Operator:Not Supported for String\n");
            break;
   }
   return result;
}

bool AllDataType::compareBinaryVal(void* src1, void *src2,
                                 ComparisionOp op, int length)
{
    bool result = false;
    int ret = os::memcmp(src1, src2, length);
    switch(op)
    {
        case OpEquals:
            if (ret == 0 ) result= true; else result = false;
            break;
        case OpNotEquals:
            if (ret != 0 ) result= true; else result = false;
            break;
        case OpLessThan:
            if (ret < 0 ) result= true; else result = false;
            break;
        case OpLessThanEquals:
            printf("Illegal Operator:Not Supported for Binary\n");
            break;
        case OpGreaterThan:
            if (ret > 0 ) result= true; else result = false;
            break;
        case OpGreaterThanEquals:
            printf("Illegal Operator:Not Supported for Binary\n");
            break;
   }
   return result;
}



ComparisionOp AllDataType::getComparisionOperator(char *str)
{
    ComparisionOp op;
    if (strcmp(str, "<=") == 0)
        op = OpLessThanEquals;
    else if (strcmp(str, ">=") == 0)
        op = OpGreaterThanEquals;
    else if (strcmp(str, "<") == 0)
        op = OpLessThan;
    else if (strcmp(str, ">") == 0)
        op = OpGreaterThan;
    else if (strcmp(str, "=") == 0)
        op = OpEquals;
    else if (strcmp(str, "!=") == 0)
        op = OpNotEquals;
    else
        op = OpInvalidComparisionOp;
    return op;
}

void* AllDataType::alloc(DataType type, int length)
{
    void *dest;
    switch(type)
    {
        case typeInt:
            dest = malloc(sizeof(int));
            break;
        case typeLong:
            dest = malloc(sizeof(long));
            break;
        case typeLongLong:
            dest = malloc(sizeof(long long));
            break;
        case typeShort:
            dest = malloc(sizeof(short));
            break;
        case typeByteInt:
            dest = malloc(sizeof(char));
            break;
        case typeDouble:
            dest = malloc(sizeof(double));
            break;
        case typeFloat:
            dest = malloc(sizeof(float));
            break;
        case typeDecimal:
            //TODO::for porting
            //fldDef.length_ = sizeof(long double);
            break;
        case typeString:
            if (length == 0 ) return NULL;
            dest = malloc(length);
            break;
        case typeDate:
            dest = malloc(sizeof(Date));
            break;
        case typeTime:
            dest = malloc(sizeof(Time));
            break;
        case typeTimeStamp:
            dest = malloc(sizeof(TimeStamp));
            break;
    }
    return dest;
}
void AllDataType::strToValue(void* dest, char *src, DataType type, int length)
{
    switch(type)
    {
        case typeInt: {
            int val;
            sscanf( src, "%d",  &val);
            *(int*)dest = val;
            break; }
        case typeLong: {
            long val;
            sscanf( src, "%ld",  &val);
            *(long*)dest = val;
            break; }
        case typeLongLong: {
            long long val;
            sscanf( src, "%lld",  &val);
            *(long long*)dest = val;
            break; }
        case typeShort: {
            short val;
            sscanf( src, "%hd",  &val);
            *(short*)dest = val;
            break; }
        case typeByteInt: {
            char val;
            sscanf( src, "%c",  &val);
            *(char*)dest = val;
            break; }
        case typeDouble: {
            double val;
            sscanf( src, "%g",  &val);
            *(double*)dest = val;
            break; }
        case typeFloat: {
            float val;
            sscanf( src, "%f",  &val);
            *(float*)dest = val;
            break; }
        case typeDecimal:
            //TODO::for porting
        case typeString: {
                strncpy((char*)dest, (char*)src, length);
                char *d =(char*)dest;
                d[length-1] = '\0'; 
                break;}
        case typeDate: {
            int d,m,y,res=0;
            res = sscanf( src, "%d-%d-%d", &d, &m, &y );
            if( res != 3 )
                 res = sscanf( src, "%d/%d/%d", &d, &m, &y );
            if( res != 3 )
            {
           fprintf(stderr,"Error reading date. dd{-/}mm{-/}yyyy is the valid format.");
                d=m=y=0;
            }
            Date dateObj(y,m,d);
            *(Date*)dest = dateObj;
            break; }
        case typeTime: {
            int h,m,s,res=0;
            res = sscanf( src, "%d:%d:%d", &h, &m, &s );
            if( res != 3 )
            {
                fprintf(stderr, "Error reading time, hh:mm:ss is the valid format.");
                h=m=s=0;
            }
            Time timeObj(h,m,s);
            *(Time*)dest = timeObj;
            break; }
        case typeTimeStamp: {
            int d,m,y, h,mn,s, res=0;
            res = sscanf( src, "%d-%d-%d %d:%d:%d", &d, &m, &y, &h, &mn, &s );
            if( res != 6 )
                res = sscanf( src, "%d/%d/%d %d:%d:%d", &d, &m, &y, &h, &mn, &s );
            if( res != 6 )
                res = sscanf( src, "%d/%d/%d, %d:%d:%d", &d, &m, &y, &h, &mn, &s );
            if( res != 6 )
            {
                fprintf(stderr, "Error reading timestamp, dd{-/}mm{-/}yyyy[,] hh:mm:ss is the valid format.");
                d=m=y=h=mn=s=0;
            }
            TimeStamp timeStampObj(y,m,d,h,mn,s);
            *(TimeStamp*)dest = timeStampObj;
            break; }
        default:
            break;
        }
}


void AllDataType::convert(DataType srcType, void *src, 
                          DataType destType, void *dest)
{
    switch ((DataType) destType )
    {
        case typeInt:        convertToInt(dest, src, srcType); break;
        case typeLong:       convertToLong(dest, src, srcType); break;
        case typeLongLong:   convertToLongLong(dest, src, srcType); break;
        case typeShort:      convertToShort(dest, src, srcType); break;
        case typeByteInt:    convertToByteInt(dest, src, srcType); break;

        case typeFloat:      convertToFloat(dest, src, srcType); break;
        case typeDouble:     convertToDouble(dest, src, srcType); break;

        //TODO 
        case typeDecimal:    convertToDouble(dest, src, srcType); break;

        case typeString:     convertToString(dest, src, srcType); break;

        case typeBinary:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        default: return;
    }
}

void AllDataType::convertToInt( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(int *)dest = *(int *)src; break;
        case typeLong:       *(int *)dest =(int) *(long *)src; break;
        case typeLongLong:   *(int *)dest =(int) *(long long *)src; break;
        case typeShort:      *(int *)dest =(int) *(short *)src; break;
        case typeByteInt:    *(int *)dest =(int) *(char *)src; break;

        case typeFloat:      *(int *)dest = (int) *(float *)src; break;
        case typeDouble:     *(int *)dest =(int) *(double *)src; break;

        case typeString:     sscanf((const char*)src, "%d", (int*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(int *)dest = (int) 0;
    }
}

void AllDataType::convertToLong( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(long *)dest =(long) *(int *)src; break;
        case typeLong:       *(long *)dest = *(long *)src; break;
        case typeLongLong:   *(long *)dest =(long) *(long long *)src; break;
        case typeShort:      *(long *)dest =(long) *(short *)src; break;
        case typeByteInt:    *(long *)dest =(long) *(char *)src; break;

        case typeFloat:      *(long *)dest = (long) *(float *)src; break;
        case typeDouble:     *(long *)dest =(long) *(double *)src; break;

        case typeString:     sscanf((const char*)src, "%ld", (long*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(long *)dest = (long) 0;
    }
}


void AllDataType::convertToLongLong( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(long long *)dest =(long long) *(int *)src; break;
        case typeLong:       *(long long *)dest = (long long) *(long *)src; break;
        case typeLongLong:   *(long long *)dest = *(long long *)src; break;
        case typeShort:      *(long long *)dest =(long long) *(short *)src; break;
        case typeByteInt:    *(long long *)dest =(long long) *(char *)src; break;

        case typeFloat:      *(long long *)dest = (long long) *(float *)src; break;
        case typeDouble:     *(long long *)dest =(long long) *(double *)src; break;

        case typeString:     sscanf((const char*)src, "%lld", (long long*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(long long *)dest = (long long) 0;
    }
}

void AllDataType::convertToShort( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(short*)dest =(short) *(int*)src; break;
        case typeLong:       *(short*)dest = (short) *(long*)src; break;
        case typeLongLong:   *(short*)dest = (short) *(long long*)src; break;
        case typeShort:      *(short*)dest = *(short*)src; break;
        case typeByteInt:    *(short*)dest =(short) *(char *)src; break;

        case typeFloat:      *(short*)dest = (short) *(float *)src; break;
        case typeDouble:     *(short*)dest =(short) *(double *)src; break;

        case typeString:     sscanf((const char*)src, "%hd", (short*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(short*)dest = (short) 0;
    }
}

void AllDataType::convertToByteInt( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(char*)dest = (char) *(int*)src; break;
        case typeLong:       *(char*)dest = (char) *(long*)src; break;
        case typeLongLong:   *(char*)dest = (char) *(long long*)src; break;
        case typeShort:      *(char*)dest = (char) *(short*)src; break;
        case typeByteInt:    *(char*)dest = *(char *)src; break;

        case typeFloat:      *(char*)dest = (char) *(float *)src; break;
        case typeDouble:     *(char*)dest =(char) *(double *)src; break;

        case typeString:     sscanf((const char*)src, "%c", (char*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(char*)dest = (char) 0;
    }
}

void AllDataType::convertToFloat( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(float *)dest =(float) *(int *)src; break;
        case typeLong:       *(float *)dest =(float) *(long *)src; break;
        case typeLongLong:   *(float *)dest =(float) *(long long *)src; break;
        case typeShort:      *(float *)dest =(float) *(short *)src; break;
        case typeByteInt:    *(float *)dest =(float) *(char *)src; break;

        case typeFloat:      *(float *)dest = *(float *)src; break;
        case typeDouble:     *(float *)dest =(float) *(double *)src; break;

        case typeString:     sscanf((const char*)src, "%f", (float*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(float *)dest = (float) 0;
    }
}

void AllDataType::convertToDouble( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(double *)dest =(double) *(int *)src; break;
        case typeLong:       *(double *)dest =(double) *(long *)src; break;
        case typeLongLong:   *(double *)dest =(double) *(long long *)src; break;
        case typeShort:      *(double *)dest =(double) *(short *)src; break;
        case typeByteInt:    *(double *)dest =(double) *(char *)src; break;

        case typeFloat:      *(double *)dest =(double) *(float *)src; break;
        case typeDouble:     *(double *)dest = *(double *)src; break;

        case typeString:     sscanf((const char*)src, "%lf", (double*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(double *)dest = (double) 0;
    }
}

void AllDataType::convertToString( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:
        {
            sprintf ((char *)dest, "%d", *(int *)src); 
            break;
        }
        case typeLong:
        {
            sprintf ((char *)dest, "%ld", *(long *)src);
            break;
        }
        case typeLongLong:
        {
            sprintf ((char *)dest, "%lld", *(long long *)src); 
            break;
        }
        case typeShort:
        {
            sprintf ((char *)dest, "%hd", *(short *)src); 
            break;
        }
        case typeByteInt:
        {
            sprintf ((char *)dest, "%hd", *(char *)src); 
            break;
        }

        case typeFloat:
        {
            sprintf ((char *)dest, "%f", *(float *)src);
            break;
        }
        case typeDouble:
        {
            sprintf ((char *) dest, "%lf", *(double *)src); 
            break;
        }

        case typeString:
        {
            strcpy((char*)dest, (char*)src);
            break;
        }
        case typeDate:
        {
            Date* dt = (Date*)src;
            sprintf((char*) dest, "%d/%d/%d", dt->dayOfMonth(),
                                  dt->month(), dt->year());
            break;
        }
        case typeTime:
        {
            Time* tm = (Time*)src;
            sprintf((char*)dest,"%d:%d:%d.%d", tm->hours(), tm->minutes(), tm->seconds(), 0);
            break;
        }
        case typeTimeStamp:
        {
            TimeStamp* tm = (TimeStamp*)src;
            sprintf((char*)dest, "%d/%d/%d %d:%d:%d.%d", tm->dayOfMonth(),
                                tm->month(), tm->year(), tm->hours(),
                                tm->minutes(), tm->seconds(), 0 );
            break;
        }
        default: ((char*)dest)[0] = '\0';
    }

}

void AllDataType::printVal(void* src, DataType srcType, int length )
{
    switch(srcType)
    {
        case typeInt:
        {
            printf ("%d\t", *(int *)src); 
            break;
        }
        case typeLong:
        {
            printf ("%ld\t", *(long *)src);
            break;
        }
        case typeLongLong:
        {
            printf ("%lld\t", *(long long *)src); 
            break;
        }
        case typeShort:
        {
            printf("%hd\t", *(short *)src); 
            break;
        }
        case typeByteInt:
        {
            printf("%hd\t", *(char *)src); 
            break;
        }

        case typeFloat:
        {
            printf("%f\t", *(float *)src);
            break;
        }
        case typeDouble:
        {
            printf("%lf\t", *(double *)src); 
            break;
        }

        case typeString:
        {
            printf("%s\t", (char*)src);
            break;
        }
        case typeDate:
        {
            Date* dt = (Date*)src;
            printf("%d/%d/%d\t", dt->dayOfMonth(),
                                  dt->month(), dt->year());
            break;
        }
        case typeTime:
        {
            Time* tm = (Time*)src;
            printf("%d:%d:%d.%d\t", tm->hours(), tm->minutes(), tm->seconds(), 0);
            break;
        }
        case typeTimeStamp:
        {
            TimeStamp* tm = (TimeStamp*)src;
            printf("%d/%d/%d %d:%d:%d.%d\t", tm->dayOfMonth(),
                                tm->month(), tm->year(), tm->hours(),
                                tm->minutes(), tm->seconds(), 0 );
            break;
        }
        default: { printf("DataType not supported\n"); break; }
    }

}



