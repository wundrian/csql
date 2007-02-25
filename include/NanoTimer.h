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
#ifndef NANO_TIMER_H
#define NANO_TIMER_H
#include<time.h>
#include<limits.h>
class NanoTimer 
{
    long long max_, min_, total, count, last_;
    struct timespec begin;
    struct timespec end;

    public:
    NanoTimer() {  reset(); }
    void reset() {  max_ = 0; min_ = LONG_MAX; total =0; count = 0; last_ =0; }
    void start()
    {
        count++;
        clock_gettime(CLOCK_REALTIME, &begin);
    }
    void stop()
    {
        clock_gettime(CLOCK_REALTIME, &end);
        long long secs = end.tv_sec-begin.tv_sec;
        long long nano = end.tv_nsec-begin.tv_nsec;
        last_ = (secs*1000000000)+nano;
        total += last_;
        if ( max_ < last_ ) max_ = last_;
        if ( min_ > last_ ) min_ = last_;
    }
    long long last() { return last_; }
    long long avg() { return total/count; }
    long long min() { return min_; }
    long long max() { return max_; }
};

#endif
