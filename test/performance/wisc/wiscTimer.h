
#ifndef _WISCTIMER_H_
#define _WISCTIMER_H_


#include <sys/times.h>
#include <sys/time.h>

enum wiscTimeType { wiscWallTime, wiscResTime, wiscUserTime, wiscSysTime };

class wiscTimer {

private:
    double tickVal;

    int count;
    double sumWallX;
    double sumWallX2;
    double sumUserX;
    double sumUserX2;
    double sumKernX;
    double sumKernX2;
    double sumResX;
    double sumResX2;

    int in_time;

    struct timeval startTval;
    struct tms startTmsval;

public:

    wiscTimer ();
    int resetTimer ();
    int startTimer ();
    int stopTimer ();

    int numIters ();

    double avgTime (wiscTimeType);
    double stddevTime (wiscTimeType);
};

#endif /* _WISCTIMER_H_ */

