/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef MUTEX_H
#define MUTEX_H
#include<os.h>
typedef int Lock;
class DllExport Mutex
{

    #if defined(sparc) || defined(i686) || defined (x86_64)
    volatile Lock lock;
    #else
    pthread_mutex_t mutex_;
    #endif
    public:
    char name[20];
    int pSlot;
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
    static int CASGen(volatile void *ptr, InUse oldVal, InUse newVal);
    static int CASL(volatile long *ptr, long oldVal, long newVal);
    static int CAS(volatile int *ptr, int oldVal, int newVal);
    int getLockVal(){ return lock; }
    void print() {
        printf("<MUTEX name=%s lock=%d pslot=%d> </MUTEX>\n", name, lock,pSlot);
    }
};

#endif
