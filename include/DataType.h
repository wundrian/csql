/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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
#ifndef DATATYPE_H
#define DATATYPE_H
//USER EXPOSED

//#include<os.h>
typedef int JulianRep;

enum DataType {
   typeInt         =  0,
   typeLong        =  1,
   typeLongLong    =  2,
   typeShort       =  3,
   typeByteInt     =  4,

   typeDouble      =  10,
   typeFloat       =  11,
   typeDecimal     =  12,

   typeDate        =  20,
   typeTime        =  21,
   typeTimeStamp   =  22,

   typeString      =  30,
   typeBinary      =  31,

   typeULong       =  99,
   typeUnknown     =  100
};

enum ComparisionOp {
    OpEquals = 0,
    OpNotEquals,
    OpLessThan,
    OpLessThanEquals,
    OpGreaterThan,
    OpGreaterThanEquals
};
enum LogicalOp {
    OpAnd = 0,
    OpOr,
    OpNot
};
class AllDataType
{
    public:
    static long size(DataType type);
    static void copyVal(void* dest, void *src, DataType type);

    static bool compareVal(void *src1, void *src2, ComparisionOp op,
                           DataType type, long length = 0);
    static bool compareIntVal(void* src1, void* src2, ComparisionOp op);
    static bool compareLongVal(void* src1, void* src2, ComparisionOp op);
    static bool compareLongLongVal(void* src1, void* src2, ComparisionOp op);
    static bool compareShortVal(void* src1, void* src2, ComparisionOp op);
    static bool compareByteIntVal(void* src1, void* src2, ComparisionOp op);
    static bool compareDoubleVal(void* src1, void* src2, ComparisionOp op);
    static bool compareFloatVal(void* src1, void* src2, ComparisionOp op);
    static bool compareDateVal(void* src1, void* src2, ComparisionOp op);
    static bool compareTimeVal(void* src1, void* src2, ComparisionOp op);
    static bool compareTimeStampVal(void* src1, void* src2, ComparisionOp op);
    static bool compareStringVal(void* src1, void* src2, ComparisionOp op);
    static bool compareBinaryVal(void* src1, void* src2,
                                 ComparisionOp op, int length);


};


// 8 bit integer
class ByteInt {

    public:
    ByteInt() { }
    ByteInt(const ByteInt &v) { val = v.val; }
    ByteInt(char v) { val = v; }
    operator int() const { return (int) val; }
    char operator=(ByteInt v)   { return val = v.val; }
    char operator=(char v)          { return val = v; }
    char operator+=(ByteInt v)  { return val += v.val; }
    char operator+=(char v)         { return val += v; }
    char operator-=(ByteInt v)  { return val -= v.val; }
    char operator-=(char v)         { return val -= v; }
    char operator*=(ByteInt v)  { return val *= v.val; }
    char operator*=(char v)         { return val *= v; }
    char operator/=(ByteInt v)  { return val /= v.val; }
    char operator/=(char v)         { return val /= v; }
    char operator%=(ByteInt v)  { return val %= v.val; }
    char operator%=(char v)         { return val %= v; }
    char operator<<=(ByteInt v) { return val <<= v.val; }
    char operator<<=(char v)        { return val <<= v; }
    char operator>>=(ByteInt v) { return val >>= v.val; }
    char operator>>=(char v)        { return val >>= v; }
    char operator&=(ByteInt v)  { return val &= v.val; }
    char operator&=(char v)         { return val &= v; }
    char operator|=(ByteInt v)  { return val |= v.val; }
    char operator|=(char v)         { return val |= v; }
    char operator^=(ByteInt v)  { return val ^= v.val; }
    char operator^=(char v)         { return val ^= v; }
    char operator++()               { return val++; }
    char operator--()               { return val--; }

    private:
    signed char val;
};



class Date {  // The class a user would declare to hold date

    public:
    Date() {julianDate = 0;}
    Date(JulianRep julian) : julianDate(julian) {}
    Date(int year, int month, int day);
    Date(const Date &d2) { julianDate = d2.julianDate; }
    Date& operator=(const Date& d2)
        { julianDate=d2.julianDate; return *this; }

    int set(int year, int month, int day);
    int set(const struct tm *tmptr);
    int get(int &year, int &month, int &day) const;

    bool isValid() const;
    void setNull() { julianDate = 0;}

    int dayOfWeek() const;
    const char *dayOfWeekName() const;
    const char *dayOfWeekAbbr() const;
    static const char *dayOfWeekName(int day); // 0--> Sunday
    static const char *dayOfWeekAbbr(int day);
    static int dayOfWeek(JulianRep juldate);

    int dayOfMonth() const;
    int dayOfYear() const;

    int month() const;
    const char *monthName() const;
    const char *monthAbbr() const;
    static const char *monthName(int month);
    static const char *monthAbbr(int month);


    int parseFrom(const char *s);

    Date &operator++() { julianDate++; return *this; }
    Date &operator--() { julianDate--; return *this; }

    Date &operator+=(int days) { julianDate += days; return *this;}
    Date &operator-=(int days) { julianDate -= days; return *this;}

    int year() const;

    static bool isValidDate(int year, int month, int day);

    friend Date  operator+(const Date &d1, int days);
    friend Date  operator+(int days, const Date &d1);
    friend Date  operator-(const Date &d1, int days);
    friend int  operator-(const Date &d1, const Date & d2);
    friend int  operator<(const Date &d1 ,const Date &d2);
    friend int  operator>(const Date &d1 ,const Date &d2);
    friend int  operator<=(const Date &d1 ,const Date &d2);
    friend int  operator>=(const Date &d1 ,const Date &d2);
    friend int  operator==(const Date &d1 ,const Date &d2);
    friend int  operator!=(const Date &d1 ,const Date &d2);

    static bool isLeapYear(int year);
    static int daysInMonth(int month, int year);
    static int YMDToJulian(int year,int mon,int day, JulianRep &julian);
    static int julianToYMD(JulianRep julian,int &year,int &month,int &day);

    private:
    JulianRep julianDate;



};

class Time {  // The class a user would declare to hold time
    public:
    Time() {timeVal = 0;}
    Time(int hours, int mins, int secs, int usec = 0);
    Time(int totalSecs) : timeVal(totalSecs) {;}
    Time(const Time &d2) { timeVal = d2.timeVal; }
    Time& operator=(const Time& d2) { timeVal=d2.timeVal; return *this; }

    int set(int hours, int mins, int secs, int usec = 0);
    int get(int &hours, int &mins, int &secs) const;

    bool isValid() const;
    void setNull() { timeVal = -1;}

    int secondsSinceMidnight() const { return timeVal/10000;}
    int usec() const; // to nearest 100 of usec.
    int msec() const;
    int seconds() const;
    int minutes() const;
    int hours() const;
    int setMsec(int ms);
    int setUsec(int us);

    int parseFrom(const char *s);

    Time &operator++() { timeVal += 10000; return *this; }
    Time &operator--() { timeVal -= 10000; return *this; }

    Time &operator+=(int seconds) { timeVal += seconds*10000; return *this; }
    Time &operator-=(int seconds) { timeVal -= seconds*10000; return *this; }

    static bool isValidTime(int hours, int mins, int secs);

    friend Time operator+(const Time &t1, int seconds);
    friend Time operator+(int seconds, const Time &t1);
    friend Time operator-(const Time &t1, int seconds);
    friend int  operator-(const Time &t1, const Time& t2);
    friend int  operator<(const Time &t1 ,const Time &t2 );
    friend int  operator>(const Time &t1 ,const Time &t2 );
    friend int  operator<=(const Time &t1 ,const Time &t2 );
    friend int  operator>=(const Time &t1 ,const Time &t2 );
    friend int  operator==(const Time &t1 ,const Time &t2 );
    friend int  operator!=(const Time &t1 ,const Time &t2 );


    private:
    int timeVal;
};

class TimeStamp {

    public:
    TimeStamp() {}
    TimeStamp(int year, int month, int day, int hour, int minute, int sec, int usec = 0) :
        date(year, month, day), time(hour, minute, sec, usec) { }
    TimeStamp(const TimeStamp &ts)
    { date = ts.date; time = ts.time; }
    TimeStamp(const Date &d, Time &t) : date(d), time(t) {}


    TimeStamp& operator=(const TimeStamp& d2)
        { date=d2.date; time = d2.time; return *this; }


    int getDate(int &year, int &month, int &day)
         { return date.get(year, month, day); }
    void getDate(Date &newDate) const
         { newDate = date; }
    int setDate(int year, int month, int day)
         { return date.set(year, month, day); }
    void setDate(const Date &newDate)
         { date = newDate; }
    operator Date() { return date; }
    operator Time() { return time; }

    int getTime(int &hours, int &mins, int &secs) const
         { return time.get(hours, mins, secs); }
    void getTime(Time &newTime) const
         { newTime = time; }
    int setTime(int hours, int mins, int secs, int usec = 0)
         { return time.set(hours, mins, secs, usec); }
    void setTime(const Time &newTime)
         { time = newTime; }

    bool isValid() const { return date.isValid() && time.isValid(); }
    void setNull() { date.setNull(); time.setNull(); }

    int dayOfWeek() const { return date.dayOfWeek(); }
    const char *dayOfWeekName() const { return date.dayOfWeekName(); }
    const char *dayOfWeekAbbr() const { return date.dayOfWeekAbbr(); }
    int dayOfMonth() const { return date.dayOfMonth(); }
    int dayOfYear() const { return date.dayOfYear(); }
    int month() const { return date.month(); }
    const char *monthName() const { return date.monthName(); }
    const char *monthAbbr() const { return date.monthAbbr(); }
    int year() const { return date.year(); }

    int secondsSinceMidnight() const { return time.secondsSinceMidnight(); }
    int seconds() const { return time.seconds(); }
    int minutes() const { return time.minutes(); }
    int hours() const { return time.hours(); }
    int msec() const { return time.msec(); }
    int usec() const { return time.usec(); }
    int setMsec(int ms) { return time.setMsec(ms) ; }
    int setUsec(int us) { return time.setUsec(us) ; }

    int parseDateFrom(const char *s) { return date.parseFrom(s); }
    int parseTimeFrom(const char *s) { return time.parseFrom(s); }

    friend int  operator<(const TimeStamp &d1, const TimeStamp &d2);
    friend int  operator>(const TimeStamp &d1, const TimeStamp &d2);
    friend int  operator<=(const TimeStamp &d1, const TimeStamp &d2);
    friend int  operator>=(const TimeStamp &d1, const TimeStamp &d2);
    friend int  operator==(const TimeStamp &d1, const TimeStamp &d2);
    friend int  operator!=(const TimeStamp &d1, const TimeStamp &d2);


    private:
    Date date;
    Time time;
};


#endif


