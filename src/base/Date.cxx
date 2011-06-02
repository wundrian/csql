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
   if(month > 12){
     year += (month /12);
     month %= 12;
   }
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

