/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef MUTEX_H
#define MUTEX_H
#include<os.h>
typedef unsigned int Lock;
class Mutex
{
    int noOfRead;
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
    int tryLock(int tries=0, int waitmsecs=0,bool share=false);
    int getLock(int procSlot, bool procAccount=true,bool share=false);
    int releaseLock(int procSlot, bool procAccount=true,bool share=false);
    int destroy();
    int recoverMutex();
    static int CASL(long *ptr, long oldVal, long newVal);
    static int CAS(int *ptr, int oldVal, int newVal);
};

#endif
