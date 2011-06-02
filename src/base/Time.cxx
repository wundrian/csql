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


#define MAX_VALID_SECONDS (60 * 60 * 24 -1)
Time::Time(int hours, int mins, int secs, int usec)
    { set(hours,mins,secs, usec); }

int Time::set(int hours, int mins, int secs, int usec) {
    if((hours | mins | secs | usec) < 0) 
    { 
        timeVal = -1; 
        return -1; 
    }
    if(hours >= 24 | mins >= 60 | secs >= 62)
    { 
        timeVal = -1; 
        return -1; 
    }
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
    int day=hours/24;
    hours%=24;
    timeVal += (hours* 60 * 60 * 10000);
    int quit = day+(timeVal /864000000);
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

       if (!isValidTime(hours,mins,secs)) return -1;
       return set(hours,mins,secs);
   }
}
