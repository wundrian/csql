
#include <stdio.h>
#include <unistd.h>
#include "wiscTimer.h"

wiscTimer::wiscTimer ()
{
    tickVal = (double) sysconf (_SC_CLK_TCK);

    this->resetTimer();
}

int wiscTimer::resetTimer ()
{
    in_time = 0;
    count = 0;
    sumWallX = 0.0;
    sumWallX2 = 0.0;
    sumUserX = 0.0;
    sumUserX2 = 0.0;
    sumKernX = 0.0;
    sumKernX2 = 0.0;

    return 0;
}

int wiscTimer::startTimer ()
{
    if (in_time) {
        fprintf (stderr, "Timer already started\n");
        return -1;
    }
    in_time = 1;

    gettimeofday (&startTval, NULL);
    times (&startTmsval);

    return 0;
}

int wiscTimer::stopTimer ()
{
    if (!in_time) {
        fprintf (stderr, "Timer NOT started\n");
        return -1;
    }
    in_time = 0;

    struct timeval endTval;
    struct tms endTmsval;

    gettimeofday (&endTval, NULL);
    times (&endTmsval);

    double kB, kA, uB, uA, dW;
    kB = ((double) startTmsval.tms_stime) / tickVal;
    kA = ((double) endTmsval.tms_stime) / tickVal;

    uB = ((double) startTmsval.tms_utime) / tickVal;
    uA = ((double) endTmsval.tms_utime) / tickVal;

    dW = ((double) (endTval.tv_sec - startTval.tv_sec)) * 1000.0 +
        ((double) (endTval.tv_usec - startTval.tv_usec)) / 1000.0;

    sumWallX += dW;
    sumWallX2 += dW * dW;

    double kX, uX;

    kX = kA - kB;
    uX = uA - uB;

    sumKernX += kX;
    sumKernX2 += kX * kX;

    sumUserX += uX;
    sumUserX2 += uX * uX;

    double rX;

    rX = kX + uX;
    sumResX += rX;
    sumResX2 += rX * rX;

    count++;

    return 0;
}

int wiscTimer::numIters ()
{
    return count;
}

double wiscTimer::avgTime (wiscTimeType timeType)
{
    if (count == 0)
        return 0.0;

    double Numer;

    switch (timeType) {
    case wiscWallTime:
        Numer = sumWallX;
        break;
    case wiscResTime:
        Numer = sumResX * 1000.0;
        break;
    case wiscUserTime:
        Numer = sumUserX * 1000.0;
        break;
    case wiscSysTime:
        Numer = sumKernX * 1000.0;
        break;
    }

    return (Numer / ((double) count));

}

double wiscTimer::stddevTime (wiscTimeType)
{
    return 0.0;
}


