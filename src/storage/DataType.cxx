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
#include<Debug.h>
//#include<Config.h>
#define SmallestValJulDate (1721426)
#if defined(SOLARIS)
#undef _TIME_H
#endif


Date::Date(int year, int month, int day)
    { YMDToJulian(year, month, day, julianDate); }
int Date::set(int year, int month, int day)
    { return YMDToJulian(year,month,day,julianDate); }
int Date::get(int &year, int &month, int &day) const
    { return julianToYMD(julianDate,year,month,day); }

int Date::parseFrom(const char *s) {
    int month,day,year;
    int count;char *p;
    if(strcmp(s,"now")==0 || strcmp(s,"NOW")==0){
       time_t cnow = ::time(NULL);
#if defined(SOLARIS) && defined(REMOTE_SOLARIS)
       struct std::tm *tmval =  (struct std::tm*) localtime(&cnow);
       return set(year=tmval->tm_year+1900, month=tmval->tm_mon+1, day=tmval->tm_mday);
#else
       struct tm *tmval = localtime(&cnow);
       return set(year=tmval->tm_year+1900,month=tmval->tm_mon+1,day=tmval->tm_mday);
#endif
    }
    else{
	 p=(char*)s;
	 while(*p!='\0'){
	   if(*p=='-'){
	      count = sscanf(s,"%d-%d-%d",&year,&month,&day);
	      break;
	   }
	   if(*p=='/'){
	     count = sscanf(s,"%d/%d/%d",&year,&month,&day);
	     break;
	   }
	   p++;
	 }
         if (count < 3) return -1;
         if (year < 100) year += 1900;
         if (!isValidDate(year, month, day))
         return -1;
         return set(year,month,day);
   }
}

void Date::changeToCsqlFormat(char *src)
{
    char dst[10]="";
    char *srcPtr = src;
    char *dstPtr = dst;
    dst[0]='\0';
    srcPtr = src + 7;
    strncpy(dstPtr, srcPtr, 4);
    dst[4] = '-';
    dstPtr = &dst[5]; 
    srcPtr = src + 3;
    if(strncasecmp(srcPtr,"JAN",3) == 0) strncpy(dstPtr, "01", 2);
    else if(strncasecmp(srcPtr,"FEB",3)== 0) strncpy(dstPtr, "02", 2);
    else if(strncasecmp(srcPtr,"MAR",3)== 0) strncpy(dstPtr, "03", 2);
    else if(strncasecmp(srcPtr,"APR",3)== 0) strncpy(dstPtr, "04", 2);
    else if(strncasecmp(srcPtr,"MAY",3)== 0) strncpy(dstPtr, "05", 2);
    else if(strncasecmp(srcPtr,"JUN",3)== 0) strncpy(dstPtr, "06", 2);
    else if(strncasecmp(srcPtr,"JUL",3)== 0) strncpy(dstPtr, "07", 2);
    else if(strncasecmp(srcPtr,"AUG",3)== 0) strncpy(dstPtr, "08", 2);
    else if(strncasecmp(srcPtr,"SEP",3)== 0) strncpy(dstPtr, "09", 2);
    else if(strncasecmp(srcPtr,"OCT",3)== 0) strncpy(dstPtr, "10", 2);
    else if(strncasecmp(srcPtr,"NOV",3)== 0) strncpy(dstPtr, "11", 2);
    else if(strncasecmp(srcPtr,"DEC",3)== 0) strncpy(dstPtr, "12", 2);
    dst[7]='-';   
    dstPtr = &dst[8]; 
    strncpy(dstPtr, src, 2);
    dst[10] = '\0';
    strcpy(src, dst);
    return;
}   
void Date::addDay(int noOfDays)
{
   julianDate = julianDate + noOfDays;
}
void Date::subDay(int noOfDays)
{
   julianDate = julianDate - noOfDays;
}

void Date::addMonth(int noOfMons)
{
   int year, month, day;
   get(year,month,day);
   month += noOfMons;
   year += (month /12);
   month %= 12;
   set(year,month,day);
}
void Date::subMonth(int noOfMons)
{
   int year, month, day;
   get(year,month,day);
   if(noOfMons>12)
   {
       year -= (noOfMons/12);
   }
   month -= (noOfMons%12);
   if(month<0){
       year -= 1;
       month += 12;
   }
   set(year,month,day);
}
void Date::addYear(int noOfYrs )
{
   int year, month, day;
   get(year,month,day);
   year += noOfYrs;
   set(year,month,day);
}

void Date::subYear(int noOfYrs )
{
   int year, month, day;
   get(year,month,day);
   year -= noOfYrs;
   set(year,month,day);
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
   
    if (year  < 1 || year  > 9999) return false;
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

int Time::addSec(int secs)
{
    timeVal += (secs *10000);
    int quit = timeVal /864000000;
    if(0==quit) return 0;
    timeVal %= 864000000;
    return quit;
}

int Time::subSec(int secs)
{
    timeVal -= (secs *10000);
    int quit = timeVal /864000000;
    if(0==quit) return 0;
    timeVal %= 864000000;
    return quit;
}
int Time::addMin(int mins)
{
    timeVal += (mins * 60 * 10000);
    int quit = timeVal /864000000;
    if(0==quit) return 0;
    timeVal %= 864000000;
    return quit;
}
int Time::subMin(int mins)
{
    timeVal -= (mins * 60 * 10000);
    int quit = timeVal /864000000;
    if(0==quit) return 0;
    timeVal %= 864000000;
    return quit;
}
int Time::addHour(int hours)
{
    timeVal += (hours* 60 * 60 * 10000);
    int quit = timeVal /864000000;
    if(0==quit) return 0;
    timeVal %= 864000000;
    return quit;
}
int Time::subHour(int hours)
{
   timeVal -= (hours* 60 * 60 * 10000);
   int quit = timeVal /864000000;
   if(timeVal < 0) {
      quit += -1;
      if(quit<0)   timeVal += ( 864000000 * quit *(-1) );
      else timeVal +=864000000;
   }
   if(0==quit) return 0;
   timeVal %= 864000000;
   return quit;
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
    int count;char *p;
    if(strcmp(s,"now")==0 || strcmp(s,"NOW")==0){
       time_t cnow = ::time(NULL);
#if defined(SOLARIS) && defined(REMOTE_SOLARIS)
       struct std::tm *tmval =  (struct std::tm*) localtime(&cnow);
       return set(hours=tmval->tm_hour,mins=tmval->tm_min,secs=tmval->tm_sec);
#else
       struct tm *tmval = localtime(&cnow);
       return set(hours=tmval->tm_hour,mins=tmval->tm_min,secs=tmval->tm_sec);
#endif
    }
    else{
       count = sscanf(s,"%d:%d:%d",&hours,&mins,&secs);
       if (count < 2) return -1;
       if (count == 2) secs = 0;

       if (!isValidTime(hours,mins,secs))
       return -1;
       return set(hours,mins,secs);
   }
}
int TimeStamp::parseFrom(const char *s) {
    int hours,mins,secs;
    int month,day,year;
    int count;char *p;
    if(strcmp(s,"now")==0 || strcmp(s,"NOW")==0){
         time_t cnow = ::time(NULL);
#if defined(SOLARIS) && defined(REMOTE_SOLARIS)
         struct std::tm *tmval =  (struct std::tm*) localtime(&cnow);
         setDate(year=tmval->tm_year+1900,month=tmval->tm_mon+1,day=tmval->tm_mday);
	 return setTime(hours=tmval->tm_hour,mins=tmval->tm_min,secs=tmval->tm_sec);
#else
         struct tm *tmval = localtime(&cnow);
         setDate(year=tmval->tm_year+1900,month=tmval->tm_mon+1,day=tmval->tm_mday);
	 return setTime(hours=tmval->tm_hour,mins=tmval->tm_min,secs=tmval->tm_sec);
#endif
    }
    else{
    p=(char*)s;
    while(*p!='\0'){
      if(*p=='-'){
       count = sscanf(s,"%d-%d-%d %d:%d:%d",&year,&month,&day, &hours, &mins, &secs);
       break;
      }
      if(*p=='/'){
        count = sscanf(s,"%d/%d/%d %d:%d:%d",&year,&month,&day, &hours, &mins, &secs);
        break;
      }
      p++;
    }
    if (count < 5) return -1;
    if (count == 5) secs = 0;
    if (year < 100) year += 1900;

    if (!date.isValidDate(year, month, day))
        return -1;

    setDate(year,month,day);


    if (!time.isValidTime(hours,mins,secs))
        return -1;
    return setTime(hours,mins,secs);
    }
}
void TimeStamp::addHour(int hours )
{
   int day = time.addHour(hours);
   if(day!=0){ date.addDay(day);}
}

void TimeStamp::subHour(int hours )
{
   int day = time.subHour(hours);
   if(day!=0){ date.subDay(day);}
}

void TimeStamp::addMin(int noOfMins )
{
   int day = time.addMin(noOfMins);
   if(day!=0){ date.addDay(day);}
}

void TimeStamp::subMin(int noOfMins)
{
   int day = time.subMin(noOfMins);
   if(day!=0) {date.subDay(day);}
}
void TimeStamp::addSec(int noOfSecs)
{
   int day = time.addSec(noOfSecs);
   if(day!=0){ date.addDay(day);}
}
void TimeStamp::subSec(int noOfSecs)
{
    int day = time.subSec(noOfSecs);
    if(day!=0){ date.subDay(day);}
}

int TimeStamp::secDiff(TimeStamp &ts)
{
  int day1= date.getCalDay();
  int day2= Date(ts).getCalDay();
  int sec1= time.getCalSec();
  int sec2= Time(ts).getCalSec();
  return (((day1*24*60*60)+sec1) - ((day2*24*60*60)+sec2));
}
int TimeStamp::minDiff(TimeStamp &ts)
{
  int day1= date.getCalDay();
  int day2= Date(ts).getCalDay();
  int sec1= time.getCalSec();
  int sec2= Time(ts).getCalSec();
  int secdiff = (((day1*24*60*60)+sec1) - ((day2*24*60*60)+sec2));

  return (secdiff/60);
}

int TimeStamp::hourDiff(TimeStamp &ts)
{
   int day1= date.getCalDay();
   int day2= Date(ts).getCalDay();
   int sec1= time.getCalSec();
   int sec2= Time(ts).getCalSec();
   int secdiff = (((day1*24*60*60)+sec1) - ((day2*24*60*60)+sec2));
   return (secdiff/3600);
}

int TimeStamp::dayDiff(TimeStamp &ts)
{
   int day1= date.getCalDay();
   int day2= Date(ts).getCalDay();
   int sec1= time.getCalSec();
   int sec2= Time(ts).getCalSec();
   int secdiff = (((day1*24*60*60)+sec1) - ((day2*24*60*60)+sec2));
   return (secdiff/(3600*24));

}

int TimeStamp::monthDiff(TimeStamp &ts)
{
   int day1= date.getCalDay();
   int day2= Date(ts).getCalDay();
   int sec1= time.getCalSec();
   int sec2= Time(ts).getCalSec();
   int secdiff = (((day1*24*60*60)+sec1) - ((day2*24*60*60)+sec2));
   return (secdiff/(3600*24*30));

}
int TimeStamp::yearDiff(TimeStamp &ts)
{
   int day1= date.getCalDay();
   int day2= Date(ts).getCalDay();
   int sec1= time.getCalSec();
   int sec2= Time(ts).getCalSec();
   int secdiff = (((day1*24*60*60)+sec1) - ((day2*24*60*60)+sec2));
   return (secdiff/(3600*24*30*12));
}
void TimeStamp::changeToCsqlFormat(char *src)
{
    char dst[20];
    char *srcPtr = src;
    char *dstPtr = dst;
    dst[0]='\0';
    srcPtr = src + 7;
    strncpy(dstPtr, srcPtr, 4);
    dst[4] = '-';
    dstPtr = &dst[5]; 
    srcPtr = src + 3;
    if(strncasecmp(srcPtr,"JAN",3) == 0) strncpy(dstPtr, "01", 2);
    else if(strncasecmp(srcPtr,"FEB",3)== 0) strncpy(dstPtr, "02", 2);
    else if(strncasecmp(srcPtr,"MAR",3)== 0) strncpy(dstPtr, "03", 2);
    else if(strncasecmp(srcPtr,"APR",3)== 0) strncpy(dstPtr, "04", 2);
    else if(strncasecmp(srcPtr,"MAY",3)== 0) strncpy(dstPtr, "05", 2);
    else if(strncasecmp(srcPtr,"JUN",3)== 0) strncpy(dstPtr, "06", 2);
    else if(strncasecmp(srcPtr,"JUL",3)== 0) strncpy(dstPtr, "07", 2);
    else if(strncasecmp(srcPtr,"AUG",3)== 0) strncpy(dstPtr, "08", 2);
    else if(strncasecmp(srcPtr,"SEP",3)== 0) strncpy(dstPtr, "09", 2);
    else if(strncasecmp(srcPtr,"OCT",3)== 0) strncpy(dstPtr, "10", 2);
    else if(strncasecmp(srcPtr,"NOV",3)== 0) strncpy(dstPtr, "11", 2);
    else if(strncasecmp(srcPtr,"DEC",3)== 0) strncpy(dstPtr, "12", 2);
    dst[7]='-';   
    dstPtr = &dst[8]; 
    strncpy(dstPtr, src, 2);
    dstPtr = &dst[10];
    srcPtr = src + 11;
    strncpy(dstPtr, srcPtr, 9);
    dst[19]='\0';
    strcpy(src, dst);
    return;
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
    { return d1.date != d2.date || d1.time != d2.time; }

DataType AllDataType::getCsqlTypeFromFunctionType(FunctionType type)
{
    switch(type)
    {
        case DATEDIFF: return typeDate;
        case DATEADDWITHYEAR:
        case DATEADDWITHMON:
        case DATEADDWITHDAY:
        case DATESUBWITHYEAR:
        case DATESUBWITHMON:
        case DATESUBWITHDAY:
        case TIMEDIFF: return typeTime;
        case TIMEADDWITHHOUR:
        case TIMEADDWITHMIN:
        case TIMEADDWITHSEC:
        case TIMESUBWITHHOUR:
        case TIMESUBWITHMIN:
        case TIMESUBWITHSEC: return typeInt;
        case TIMESTAMPADDWITHYEAR:
        case TIMESTAMPADDWITHMON:
        case TIMESTAMPADDWITHDAY:
        case TIMESTAMPSUBWITHYEAR:
        case TIMESTAMPSUBWITHMON:
        case TIMESTAMPSUBWITHDAY:
        case TIMESTAMPADDWITHHOUR:
        case TIMESTAMPADDWITHMIN:
        case TIMESTAMPADDWITHSEC:
        case TIMESTAMPSUBWITHHOUR:
        case TIMESTAMPSUBWITHMIN:
        case TIMESTAMPSUBWITHSEC: return typeInt;
        case TIMESTAMPDIFFYEAR:
        case TIMESTAMPDIFFMON:
        case TIMESTAMPDIFFDAY:
        case TIMESTAMPDIFFHOUR:
        case TIMESTAMPDIFFMIN:
        case TIMESTAMPDIFFSEC: return typeTimeStamp;
        case EXTRACTYEARFROMDAY:
        case EXTRACTMONFROMDAY:
        case EXTRACTDAYFROMDAY:return typeDate;
        case EXTRACTHOURFROMTIME:
        case EXTRACTMINFROMTIME:
        case EXTRACTSECFROMTIME: return typeTime;
        case EXTRACTYEARFROMTIMESTAMP:
        case EXTRACTMONFROMTIMESTAMP:
        case EXTRACTDAYFROMTIMESTAMP:
        case EXTRACTHOURFROMTIMESTAMP:
        case EXTRACTMINFROMTIMESTAMP:
        case EXTRACTSECFROMTIMESTAMP: return typeTimeStamp;
        default: return typeInt;
    }
}
DataType AllDataType::getCsqlTypeFromFunctionTypeForComparision(FunctionType type)
{
    switch(type)
    {
        case DATEDIFF: return typeInt;
        case DATEADDWITHYEAR: return typeDate;
        case DATEADDWITHMON: return typeDate;
        case DATEADDWITHDAY: return typeDate;
        case DATESUBWITHYEAR: return typeDate;
        case DATESUBWITHMON: return typeDate;
        case DATESUBWITHDAY: return typeDate;
        case TIMEDIFF: return typeInt;
        case TIMEADDWITHHOUR: return typeTime;
        case TIMEADDWITHMIN: return typeTime;
        case TIMEADDWITHSEC: return typeTime;
        case TIMESUBWITHHOUR: return typeTime;
        case TIMESUBWITHMIN: return typeTime;
        case TIMESUBWITHSEC: return typeTime;
        case TIMESTAMPADDWITHYEAR: return typeTimeStamp;
        case TIMESTAMPADDWITHMON: return typeTimeStamp;
        case TIMESTAMPADDWITHDAY: return typeTimeStamp;
        case TIMESTAMPSUBWITHYEAR: return typeTimeStamp;
        case TIMESTAMPSUBWITHMON: return typeTimeStamp;
        case TIMESTAMPSUBWITHDAY: return typeTimeStamp;
        case TIMESTAMPADDWITHHOUR:  return typeTimeStamp;
        case TIMESTAMPADDWITHMIN: return typeTimeStamp;
        case TIMESTAMPADDWITHSEC: return typeTimeStamp;
        case TIMESTAMPSUBWITHHOUR:  return typeTimeStamp;
        case TIMESTAMPSUBWITHMIN: return typeTimeStamp;
        case TIMESTAMPSUBWITHSEC: return typeTimeStamp;
        case TIMESTAMPDIFFYEAR:
        case TIMESTAMPDIFFMON:
        case TIMESTAMPDIFFDAY:
        case TIMESTAMPDIFFHOUR:
        case TIMESTAMPDIFFMIN:
        case TIMESTAMPDIFFSEC:
        case EXTRACTYEARFROMDAY:
        case EXTRACTMONFROMDAY:
        case EXTRACTDAYFROMDAY:
        case EXTRACTHOURFROMTIME:
        case EXTRACTMINFROMTIME:
        case EXTRACTSECFROMTIME:
        case EXTRACTYEARFROMTIMESTAMP:
        case EXTRACTMONFROMTIMESTAMP:
        case EXTRACTDAYFROMTIMESTAMP:
        case EXTRACTHOURFROMTIMESTAMP:
        case EXTRACTMINFROMTIMESTAMP:
        case EXTRACTSECFROMTIMESTAMP:return typeInt;
        default: return typeInt;
    }

}

char* AllDataType::getSQLString(DataType type)
{
    switch(type)
    {
        case typeInt: return "INT";
        case typeLong: return "INT";
        case typeLongLong: return "BIGINT";
        case typeShort: return "SMALLINT";
        case typeByteInt: return "TINYINT";
        case typeDouble: return "REAL";
        case typeFloat: return "FLOAT";
        case typeDate: return "DATE";
        case typeTime: return "TIME";
        case typeTimeStamp: return "TIMESTAMP";
        case typeString: return "CHAR";
        case typeVarchar: return "VARCHAR";
        case typeBinary: return "BINARY";
        default: return "UNKNOWN";
    }
}


SQLSMALLINT AllDataType::convertToSQLType(DataType type)
{
    switch(type)
    {
        case typeInt:
            return SQL_INTEGER;
        case typeLong:
            return SQL_INTEGER;
        case typeLongLong:
            //TODO
            return SQL_BIGINT;
        case typeShort:
            return SQL_SMALLINT;
        case typeByteInt:
            //TODO
            return SQL_INTEGER;
        case typeDouble:
            return SQL_DOUBLE;
        case typeFloat:
            return SQL_REAL;
        case typeDecimal:
            //TODO
            return SQL_INTEGER;
        case typeDate:
            return SQL_TYPE_DATE;
        case typeTime:
           return SQL_TYPE_TIME;
        case typeTimeStamp:
           return SQL_TYPE_TIMESTAMP;
        case typeString:
            return SQL_CHAR;
        case typeBinary:
            return SQL_BINARY;
        case typeVarchar:
            return SQL_VARCHAR;
    }
    return SQL_INTEGER;
}
SQLSMALLINT AllDataType::convertToCSQLSQLType(DataType type)
{
    switch(type)
    {
        case typeInt:
            return SQL_INTEGER;
        case typeLong:
            return SQL_INTEGER;
        case typeLongLong:
            //TODO
            return SQL_BIGINT;
        case typeShort:
            return SQL_SMALLINT;
        case typeByteInt:
            //TODO
            return SQL_TINYINT;
        case typeDouble:
            return SQL_DOUBLE;
        case typeFloat:
            return SQL_REAL;
        case typeDecimal:
            //TODO
            return SQL_INTEGER;
        case typeDate:
            return SQL_TYPE_DATE;
        case typeTime:
           return SQL_TYPE_TIME;
        case typeTimeStamp:
           return SQL_TYPE_TIMESTAMP;
        case typeString:
            return SQL_CHAR;
        case typeBinary:
            return SQL_BINARY;
        case typeVarchar:
            return SQL_VARCHAR;
    }
    return SQL_INTEGER;
}

SQLSMALLINT AllDataType::convertToSQL_C_Type(DataType type,TDBInfo tdbname)
{
    switch(type)
    {
        case typeInt:
            return SQL_C_SLONG;
        case typeLong:
            return SQL_C_SLONG;
        case typeLongLong:
        {
            if(tdbname == postgres)
                return SQL_C_CHAR;
            else
                return SQL_C_SBIGINT;
        }
        case typeShort:
            return SQL_C_SSHORT;
        case typeByteInt:
            return SQL_C_STINYINT;
        case typeDouble:
            return SQL_C_DOUBLE;
        case typeFloat:
            return SQL_C_FLOAT;
        case typeDecimal:
            //TODO
            return SQL_INTEGER;
        case typeDate:
            return SQL_C_TYPE_DATE;
        case typeTime:
           return SQL_C_TYPE_TIME;
        case typeTimeStamp:
           return SQL_C_TYPE_TIMESTAMP;
        case typeVarchar:
        case typeString:
            return SQL_C_CHAR;
        case typeBinary:
            return SQL_C_BINARY;
    }
    return SQL_C_SLONG;
}

DataType  AllDataType::convertFromSQLType(SQLSMALLINT type,int length,int scale,TDBInfo tdbname)
{
    if(tdbname==postgres)
    {
       switch(type)
       {
            case SQL_INTEGER :
                return typeInt;
            case  SQL_SMALLINT:
                return typeShort;
            case  SQL_BIGINT:
                return typeLongLong;
            case  SQL_FLOAT:
            case  SQL_DOUBLE:
                return typeDouble;
            case  SQL_REAL:
                return typeFloat;
            case SQL_TYPE_DATE:
                return typeDate;
            case SQL_TYPE_TIME :
               return typeTime;
            case SQL_TYPE_TIMESTAMP :
               return typeTimeStamp;
            case SQL_CHAR:
               return typeString;
            case SQL_LONGVARCHAR:
               return typeString;
            case SQL_VARCHAR:
               return typeVarchar;
            case SQL_BINARY:
               return typeBinary;
       }
       return typeInt;
    } 
    switch(type)
    {
        case  SQL_TINYINT:
            return typeByteInt;
        case SQL_INTEGER :
            return typeInt;
        case  SQL_SMALLINT:
            return typeShort;
        case  SQL_BIGINT:
            return typeLongLong;
        case  SQL_DOUBLE:
            return typeDouble;
        case  SQL_FLOAT:
        case  SQL_REAL:
            return typeFloat;
        case SQL_TYPE_DATE:
            return typeDate;
        case SQL_TYPE_TIME :
           return typeTime;
        case SQL_TYPE_TIMESTAMP :
           return typeTimeStamp;
        case SQL_CHAR:
            return typeString;
        case SQL_LONGVARCHAR:
            return typeString;
        case SQL_VARCHAR:
            return typeVarchar;
        case SQL_BINARY:
            return typeBinary;
    }
    return typeInt;
}
void AllDataType::subVal(void* dest, void *src, DataType type)
{
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)dest - *(int*)src;
            break;
        case typeLong:
            *(long*)dest = *(long*)dest - *(long*)src;
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)dest - *(long long*)src;
            break;
        case typeShort:
            *(short*)dest = *(short*)dest - *(short*)src;
            break;
        case typeByteInt:
            *(char*)dest = *(char*)dest - *(char*)src;
            break;
        case typeDouble:
            *(double*)dest = *(double*)dest - *(double*)src;
            break;
        case typeFloat:
            *(float*)dest = *(float*)dest - *(float*)src;
            break;
        case typeDecimal:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:
             break;
     }
     return;
}
void AllDataType::mulVal(void* dest, void *src, DataType type)
{
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)dest * (*(int*)src);
            break;
        case typeLong:
            *(long*)dest = *(long*)dest * (*(long*)src);
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)dest * (*(long long*)src);
            break;
        case typeShort:
            *(short*)dest = *(short*)dest * (*(short*)src);
            break;
        case typeByteInt:
            *(char*)dest = *(char*)dest * (*(char*)src);
            break;
        case typeDouble:
            *(double*)dest = *(double*)dest * (*(double*)src);
            break;
        case typeFloat:
            *(float*)dest = *(float*)dest * (*(float*)src);
            break;
        case typeDecimal:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:
             break;
    }
    return;
}   
void AllDataType::mudVal(void* dest, void *src, DataType type)
{
    if (type == typeInt)
    {
        *(int*)dest = *(int*)dest % (*(int*)src);
        return;
    }
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)dest % (*(int*)src);
            break;
        case typeLong:
            *(long*)dest = *(long*)dest % (*(long*)src);
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)dest % (*(long long*)src);
            break;
        case typeShort:
            *(short*)dest = *(short*)dest % (*(short*)src);
            break;
        case typeByteInt:
            *(char*)dest = *(char*)dest % (*(char*)src);
            break;
        case typeDouble:
            *(double*)dest = *(long long*)dest % (*(long long*)src);
            break;
        case typeFloat:
            *(float*)dest = *(int*)dest % (*(int*)src);
            break;
        case typeDecimal:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:
             break;
    }
    return;
}
void AllDataType::divVal(void* dest, void *src, DataType type)
{
    if (type == typeInt)
    {
        *(int*)dest = *(int*)dest / (*(int*)src);
        return;
    }
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)dest / (*(int*)src);
            break;
        case typeLong:
            *(long*)dest = *(long*)dest / (*(long*)src);
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)dest / (*(long long*)src);
            break;
        case typeShort:
            *(short*)dest = *(short*)dest / (*(short*)src);
            break;
        case typeByteInt:
            *(char*)dest = *(char*)dest / (*(char*)src);
            break;
        case typeDouble:
            *(double*)dest = *(double *)dest / (*(double*)src);
            break;
        case typeFloat:
            *(float*)dest = *(float*)dest / (*(float*)src);
            break;
        case typeDecimal:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:
             break;
    }
    return;
}
void AllDataType::divVal(double* dest, int src, DataType type)
{
    switch(type)
    {
        case typeInt:     
        case typeLong:     
        case typeLongLong: 
        case typeShort: 
        case typeByteInt: 
        case typeDouble: 
        case typeFloat:
        case typeDecimal:
            *dest = *dest / src;
            break;
            //TODO::for porting
        case typeDate:
        case typeTime:
        case typeTimeStamp:
		case typeBinary:
        default:
             break;
     }
     return;
}

void AllDataType::increment(void* dest, void *src, DataType type)
{
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)src + 1;
            break;
        case typeLong:
            *(long*)dest = *(long*)src + 1;
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)src + 1;
            break;
        case typeByteInt:
            *(char*)dest = *(char*)src + 1;
            break;
        case typeShort:
            *(short*)dest = *(short*)src + 1;
            break;
        case typeDouble:
            *(double*)dest = *(double*)src + 1;
            break;
        case typeFloat:
            *(float*)dest = *(float*)src+ 1;
            break;
        default:
             break;
     }
}

bool AllDataType::isValueZero(void *src, DataType type)
{
    switch(type)
    {
        case typeInt:
            if (*(int*)src == 0) return true;
            else return false;
        case typeLong:
            if (*(int*)src == 0) return true;
            else return false;
        case typeLongLong:
            if (*(int*)src == 0) return true;
            else return false;
        case typeShort:
            if (*(int*)src == 0) return true;
            else return false;
        case typeDouble:
            if (*(int*)src == 0) return true;
            else return false;
        case typeFloat:
            if (*(int*)src == 0) return true;
            else return false;
        default:
             break;
     }
     return false;
}

bool AllDataType::compareIntVal(void* src1, void *src2, ComparisionOp op)
{
    printf("This function should never be called by anyone\n");
    if (OpEquals == op) {
        if (*(int*)src1 == *(int*)src2) return true;
        else return false;
    }else if (OpGreaterThan == op) {
        if (*(int*)src1 > *(int*)src2) return true;
        else return false;
    }else if (OpLessThan == op) {
        if (*(int*)src1 < *(int*)src2) return true;
        else return false;
    }else if (OpLessThanEquals == op) {
        if (*(int*)src1 <= *(int*)src2) return true;
        else return false;
    }else if (OpGreaterThanEquals == op) {
        if (*(int*)src1 >= *(int*)src2) return true;
        else return false;
    }else if (OpNotEquals == op) {
        if (*(int*)src1 != *(int*)src2) return true;
        else return false;
    }
    return false;
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
    if (OpEquals == op) {
        if (strcmp((char*)src1, (char*)src2) ==0) return true;
            else return false;
    }else if (OpGreaterThan == op) {
        if (strcmp((char*)src1, (char*)src2) >0) return true;
        else return false;
    }else if (OpLessThan == op) {
        if (strcmp((char*)src1, (char*)src2) <0 ) return true;
        else return false;
    }else if (OpLessThanEquals == op) {
       // printf("Illegal Operator:Not Supported for String\n");
       // return false;
       if (strcmp((char*)src1, (char*)src2)<= 0) return true;
       else return false;
    }else if (OpGreaterThanEquals == op) {
    //    printf("Illegal Operator:Not Supported for String\n");
    //    return false;
        if (strcmp((char*)src1, (char*)src2) >=0) return true;
        else return false;
    }else if (OpNotEquals == op) {
        if (strcmp((char*)src1, (char*)src2) != 0) return true;
        else return false;
    }else if (OpLike == op) {
        return !os::strmatch((char*)src2, (char*)src1);
    }
    printf("Illegeal Operator:Not supported for String\n");
    return false;
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
        case typeVarchar:
        case typeString:
            if (length == 0 ) return NULL;
            dest = malloc(length);
            break;
        case typeBinary:
	    if (length == 0 || length > 512) return NULL;
	    dest = malloc(length);
	     memset(dest, 0, length);
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

void  AllDataType::memoryset(void *value,DataType type)
{
    switch(type)
    {
        case typeInt:
            value= ::memset(value, 0, sizeof(int));
            break;
        case typeLong:
            value = ::memset(value, 0, sizeof(long));
            break;
        case typeLongLong:
            value =::memset(value, 0, sizeof(long long));
            break;
        case typeShort:
            value = ::memset(value, 0, sizeof(short));
            break;
        case typeByteInt:
            value = ::memset(value, 0, sizeof(char));
            break;
        case typeDouble:
            value = ::memset(value, 0, sizeof(double));
            break;
        case typeFloat:
            value = ::memset(value, 0, sizeof(float));
            break;
        case typeDecimal:
            break;
        case typeString:
        case typeVarchar:
             *(char*)value = '\0';
            //if (length == 0 ) return NULL;
            //dest = malloc(length);
            break;
        case typeBinary:
                 /*   if (length == 0 || length > 256 ) return NULL;
                        
                        memset(dest, 0, length);*/
                        break;
        case typeDate:
            value = ::memset(value, 0, sizeof(Date));
            break;
        case typeTime:
            value = ::memset(value, 0, sizeof(Time));
            break;
        case typeTimeStamp:
            value = ::memset(value, 0, sizeof(TimeStamp));
            break;
        defalut:
            break;
    }
}


DbRetVal AllDataType::strToValue(void* dest, char *src, DataType type, int length)
{
    Date date;
    Time time;
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
            sscanf( src, "%hhd",  &val);
            *(char*)dest = *(char *)&val;
            break; }
        case typeDouble: {
            double val;
            sscanf( src, "%lg",  &val);
            *(double*)dest = val;
            break; }
        case typeFloat: {
            float val;
            sscanf( src, "%f",  &val);
            *(float*)dest = val;
            break; }
        case typeDecimal:
            //TODO::for porting
        case typeString: 
        case typeVarchar: {
                strncpy((char*)dest, (char*)src, length);
                char *d =(char*)dest;
                d[length-1] = '\0'; 
                break;}
        case typeDate: {
            int d,m,y,res=0;
            if (strlen(src) == 11) {
                if ( src[6] == '-' || src[6] == '/' ) {
                    Date::changeToCsqlFormat(src);
                }
            }
	        res = sscanf( src, "%d-%d-%d", &y, &m, &d );
            if( res != 3 )
                res = sscanf( src, "%d/%d/%d", &y, &m, &d );
            if (strcmp(src,"now")==0 || strcmp(src,"NOW")==0){
	            Date *dt = (Date*) dest;
	            dt->parseFrom((char*)src);
	            break;
	        }
	        if( res != 3 )
            {
                fprintf(stderr,"Error reading date. yyyy{-/}mm{-/}dd is the valid format.");
                d=m=y=0;
            }
            /* Looking up at ranges of year-month-day */
            if(!date.isValidDate(y, m, d)){
                fprintf(stderr,"Error reading date. The value \"%d-%d-%d\" is inappropriate.",y,m,d);
                d=m=y=0;
            }
            Date dateObj(y,m,d);
            *(Date*)dest = dateObj;
            break; }
        case typeTime: {
            int h,m,s,res=0;
	    res = sscanf( src, "%d:%d:%d", &h, &m, &s );
            if(strcmp(src,"now")==0 || strcmp(src,"NOW")==0){
	         Time *dt = (Time*) dest;
	         dt->parseFrom((char*)src);
	         break;
	    }
	    if( res != 3 )
            {
                fprintf(stderr, "Error reading time, hh:mm:ss is the valid format.");
                h=m=s=0;
            }
            /* validate time */
            if(!time.isValidTime(h, m, s)){
                fprintf(stderr,"Error reading Time. The value \"%d-%d-%d\" is inappropriate.",h,m,s);
                h=m=s=0;
            }
	    Time timeObj(h,m,s);
            *(Time*)dest = timeObj;
            break; }
        case typeTimeStamp: {
            int d,m,y, h,mn,s, res=0;
            bool isNow = ( strcasecmp(src,"now")==0 );
            if(!isNow && isalpha(int(src[5]))) {
                TimeStamp::changeToCsqlFormat(src);
            }
	        res = sscanf( src, "%d-%d-%d %d:%d:%d", &y, &m, &d, &h, &mn, &s );
            if( res != 6 )
                res = sscanf( src, "%d-%d-%d, %d:%d:%d", &y, &m, &d, &h, &mn, &s );
            if( res != 6 )
                res = sscanf( src, "%d/%d/%d %d:%d:%d", &y, &m, &d, &h, &mn, &s );
            if( res != 6 )
                res = sscanf( src, "%d/%d/%d, %d:%d:%d", &y, &m, &d, &h, &mn, &s );
            
	    if(isNow){
	    	    TimeStamp *dt = (TimeStamp*) dest;
		        dt->parseFrom((char*)src);
		        break;
            }	    
	        if ( res != 6 )
            {
                fprintf(stderr, "Error reading timestamp, yyyy{-/}mm{-/}dd[,] hh:mm:ss is the valid format.");
                d=m=y=h=mn=s=0;
            }
             /* Looking up at 'YY-MM-DD' */
            if(!date.isValidDate(y, m, d)){
                fprintf(stderr,"Error reading date. The value \"%d-%d-%d\" is inappropriate.",y,m,d);
                d=m=y=h=mn=s=0;
            }
            /* Looking up at 'Hour-Min-Sec' */
            if(!time.isValidTime(h, m, s)){
                fprintf(stderr,"Error reading Time. The value \"%d-%d-%d\" is inappropriate.",h,m,s);
                d=m=y=h=mn=s=0;
            }
            TimeStamp timeStampObj(y,m,d,h,mn,s);
            *(TimeStamp*)dest = timeStampObj;
            break; }
        case typeBinary: {
            memset ((void *) dest, 0, length);
            unsigned char c = 0;
            const char *str = (const char *)src;
            int i=0;
            i = strlen(src)-1;
            if( i > (length*2)-1 ){ i = (length*2)-1 ; }         
            bool evenlegth=false;
            if(i%2){ evenlegth=true;}   
            unsigned char *val = (unsigned char *)dest+(length-1);
            while (i >= 0) {
                c = str[i]; 
               if (!isxdigit((int)c)) {
                   printError(ErrBadArg, "Invalid hexadecimal value");
                   return ErrBadArg;
               }
               if (c <= '9') c -= '0';
               else if (c >= 'a') c = c - 'a' + 10;
               else c = c - 'A' + 10;
               if(evenlegth)
               {
                   if ((i+1) % 2) { *val = *val | (c<<4); val--;}
                   else { *val = c; }
               }else{
                   if (i % 2) { *val = *val | (c<<4);   val--;}
                   else { *val = c; }
               }
               i--;
            }
            break;
        }
        default:
            break;
        }
	return OK;
}


void AllDataType::convert(DataType srcType, void *src, 
                          DataType destType, void *dest, int length)
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
        case typeVarchar:
        case typeString:     convertToString(dest, src, srcType); break;
        case typeBinary:     convertToBinary(dest, src, srcType,length); break;
        case typeDate:       convertToDate(dest, src, srcType); break;
        case typeTime:       convertToTime(dest, src, srcType); break;
        case typeTimeStamp:  convertToTimeStamp(dest, src, srcType); break;
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
        case typeVarchar:
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
        case typeVarchar:
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
        case typeVarchar:
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
        case typeVarchar: 
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
        case typeVarchar:
        case typeString:     sscanf((const char*)src, "%hhd", (char*) dest); break;

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
        case typeVarchar:
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
        case typeVarchar:
        case typeString:     sscanf((const char*)src, "%lf", (double*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(double *)dest = (double) 0;
    }
}

void AllDataType::convertToString( void* dest, void* src, DataType srcType, int length,TDBInfo tdbname )
{
    switch(srcType)
    {
        case typeInt:
        {
            Util::itoa(*(int*)src, (char*)dest);
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
            sprintf ((char *)dest, "%hhd", *(char *)src); 
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
        case typeVarchar:
        case typeString:
        {
            strcpy((char*)dest, (char*)src);
            break;
        }
        case typeDate:
        {
            Date* dt = (Date*)src;
            sprintf((char*) dest, "%d/%d/%d", dt->year(),dt->month(), dt->dayOfMonth());
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
            sprintf((char*)dest, "%d/%d/%d %d:%d:%d.%d", tm->year(),tm->month(), tm->dayOfMonth(), tm->hours(),tm->minutes(), tm->seconds(), 0 );
            break;
        }
        case typeBinary:
        {
            unsigned char *c = (unsigned char *) src;
            unsigned char *str = (unsigned char *) dest;
            unsigned char p = 0;
            int i = 0;
            while (i < length) {
                p = *c >> 4;
                if (p < 10) sprintf ((char *)str++, "%c", '0' + p);
                else sprintf((char *)str++, "%c", 'A' + p - 10);
                p = *c & 0xF;
                if (p < 10) sprintf ((char *)str++, "%c", '0' + p);
                else sprintf((char *)str++, "%c", 'A' + p - 10);
                i++; c++;
            }
            break;
        }

        default: ((char*)dest)[0] = '\0';
    }

}
void AllDataType::convertToDate( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:
        case typeLong:
        case typeLongLong:
        case typeShort:
        case typeByteInt:
        case typeFloat:
        case typeDouble:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeVarchar:
        case typeString:
        {
            Date *dt = (Date*) dest;
            dt->parseFrom((char*)src);
            break;
        }
        default: ((char*)dest)[0] = '\0';
    }
}

void AllDataType::convertToTime( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:
        case typeLong:
        case typeLongLong:
        case typeShort:
        case typeByteInt:
        case typeFloat:
        case typeDouble:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeVarchar:
        case typeString:
        {
            Time *dt = (Time*) dest;
            dt->parseFrom((char*)src);
            break;
        }
        default: ((char*)dest)[0] = '\0';
    }
}

void AllDataType::convertToTimeStamp( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:
        case typeLong:
        case typeLongLong:
        case typeShort:
        case typeByteInt:
        case typeFloat:
        case typeDouble:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeVarchar:
        case typeString:
        {
            TimeStamp *dt = (TimeStamp*) dest;
            dt->parseFrom((char*)src);
            break;
        }
        default: ((char*)dest)[0] = '\0';
    }
}

void AllDataType::convertToBinary(void *dest, void *src, DataType srcType, int length)
{
    switch(srcType)
    {
        case typeString:
        {
            memset ((void *) dest, 0, length);
            unsigned char c = 0;
            const char *str = (const char *)src;
            int i=0;
            i = strlen((char*)src)-1;
            if( i > (length*2)-1 ){ i = (length*2)-1 ; }
            bool evenlegth=false;
            if(i%2){ evenlegth=true;}
            unsigned char *val = (unsigned char *)dest+(length-1);
            while (i >= 0) {
                c = str[i];
               if (c <= '9') c -= '0';
               else if (c >= 'a') c = c - 'a' + 10;
               else c = c - 'A' + 10;
               if(evenlegth)
               {
                   if ((i+1) % 2) { *val = *val | (c<<4); val--;}
                   else { *val = c; }
               }else{
                   if (i % 2) { *val = *val | (c<<4);   val--;}
                   else { *val = c; }
               }
               i--;
            }
           break;
        }
    }
}
int AllDataType::printVal(void* src, DataType srcType, int length,int dbFlag )
{ 
    //dbFlag is the database flag 0:mysql (default), 1:postgres
    int count = 0;
    switch(srcType)
    {
        case typeInt:
        {
            count = printf ("%d", *(int *)src); 
            break;
        }
        case typeLong:
        {
            count = printf ("%ld", *(long *)src);
            break;
        }
        case typeLongLong:
        {
            if(1 == dbFlag){  
                long long temp = 0; 
                convertToLongLong((void*)&temp, src,typeString); 
                count = printf ("%lld", temp );
            }
            else count = printf ("%lld", *(long long *)src); 
            break;
        }
        case typeShort:
        {
            count = printf("%hd", *(short *)src); 
            break;
        }
        case typeByteInt:
        {
            count = printf("%hhd", *(char *)src); 
            break;
        }

        case typeFloat:
        {
            count = printf("%f", *(float *)src);
            break;
        }
        case typeDouble:
        {
            if (*(double*)src > 9999999999999999.0F)
                count = printf("%g", *(double *)src); 
            else
                count = printf("%lf", *(double *)src); 
            break;
        }

        case typeString:
        case typeVarchar:
        {
            count = printf("%s", (char*)src);
            break;
        }
        case typeDate:
        {
            Date* dt = (Date*)src;
            count = printf("%d/%d/%d", dt->year(),
                                  dt->month(), dt->dayOfMonth());
            break;
        }
        case typeTime:
        {
            Time* tm = (Time*)src;
            count = printf("%d:%d:%d.%d", tm->hours(), tm->minutes(), tm->seconds(), 0);
            break;
        }
        case typeTimeStamp:
        {
            TimeStamp* tm = (TimeStamp*)src;
            count = printf("%d/%d/%d %d:%d:%d.%d", tm->year(),
                                tm->month(), tm->dayOfMonth(), tm->hours(),
                                tm->minutes(), tm->seconds(), 0 );
            break;
        }
        case typeBinary:
        {
            unsigned char *c = (unsigned char *) src;
            unsigned char p = 0;
            int i = 0;
            bool isDigitFound=false;
            while (i < length) {
                p = *c >> 4;
                if(('0'+p)!='0'|| isDigitFound){
                    if (p < 10) printf ("%c", '0' + p);
                    else printf("%c", 'A' + p - 10);
                    isDigitFound=true;
                }
                p = *c & 0xF;
                if(('0'+p)!='0' || isDigitFound){
                    if (p < 10) printf ("%c", '0' + p);
                    else printf("%c", 'A' + p - 10);
                    isDigitFound=true;
                }
                i++; c++;
            }
            count = length * 2;
            break;
        }
        default: { printf("DataType not supported\n"); break; }
    }
    return count;
}
