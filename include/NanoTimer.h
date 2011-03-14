/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef NANO_TIMER_H
#define NANO_TIMER_H
#include<os.h>
#include<time.h>
#include<limits.h>
class DllExport NanoTimer 
{
    long long max_, min_, total, count, last_;
#ifdef WINNT
	unsigned __int64 begin, end;
#else
	struct timespec begin;
    struct timespec end;
#endif
    public:
    NanoTimer() {  reset(); }
    void reset() {  max_ = 0; min_ = LONG_MAX; total =0; count = 0; last_ =0; }
    void start()
    {
        count++;
#ifdef WINNT
        FILETIME ft;
        begin = 0;
        GetSystemTimeAsFileTime(&ft);
        // The GetSystemTimeAsFileTime returns the number of 100 nanosecond 
        // intervals since Jan 1, 1601 in a structure. Copy the high bits to 
        // the 64 bit tmpres, shift it left by 32 then or in the low 32 bits.
        begin |= ft.dwHighDateTime;
        begin <<= 32;
        begin |= ft.dwLowDateTime;
#else
		clock_gettime(CLOCK_REALTIME, &begin);
#endif
    }
    void stop()
    {
#ifdef WINNT
        FILETIME ft;
        end = 0;
        GetSystemTimeAsFileTime(&ft);
        // The GetSystemTimeAsFileTime returns the number of 100 nanosecond 
        // intervals since Jan 1, 1601 in a structure. Copy the high bits to 
        // the 64 bit tmpres, shift it left by 32 then or in the low 32 bits.
        end |= ft.dwHighDateTime;
        end <<= 32;
        end |= ft.dwLowDateTime;
		last_ = end - begin;
#else
        clock_gettime(CLOCK_REALTIME, &end);
        long long secs = end.tv_sec-begin.tv_sec;
        long long nano = end.tv_nsec-begin.tv_nsec;
        last_ = (secs*1000000000)+nano;
#endif
        total += last_;
        if ( max_ < last_ ) max_ = last_;
        if ( min_ > last_ ) min_ = last_;
    }
    long long last() { return last_; }
    long long avg() { return total/count; }
    long long sum() { return total; }
    long long minc() { return min_; }
    long long maxc() { return max_; }
};

#endif
