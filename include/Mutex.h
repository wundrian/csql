/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef MUTEX_H
#define MUTEX_H
#include<os.h>
typedef int Lock;
class Mutex
{

    #if defined(sparc) || defined(i686) || defined (x86_64)
    Lock lock;
    #else
    pthread_mutex_t mutex_;
    #endif
    public:
    char name[20];
    Mutex();
    int init();
    int init(char *name);
    int tryLock(int tries=0, int waitmsecs=0);
    int getLock(int procSlot, bool procAccount=true);
    int releaseLock(int procSlot, bool procAccount=true);
    int tryShareLock(int tries=0, int waitmsecs=0,bool share=false,bool upgrade=false);
    int getShareLock(int procSlot, bool procAccount=true);
    int getExclusiveLock(int procSlot, bool procAccount=true,bool upgrade=false);
    int releaseShareLock(int procSlot, bool procAccount=true);
    int destroy();
    int recoverMutex();
    static int CASL(long *ptr, long oldVal, long newVal);
    static int CAS(int *ptr, int oldVal, int newVal);
    int getLockVal(){ return lock; }
    void print() {
        printf("Mutex: %d %s\n", lock, name);
    }
};

#endif
