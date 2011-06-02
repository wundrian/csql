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
#if defined(SOLARIS)
#undef _TIME_H
#endif

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

