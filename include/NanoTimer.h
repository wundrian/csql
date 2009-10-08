/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
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
    long long sum() { return total; }
    long long min() { return min_; }
    long long max() { return max_; }
};

#endif
