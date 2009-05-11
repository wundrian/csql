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
#ifndef MUTEX_H
#define MUTEX_H
#include<os.h>
    #if defined(sparc)
    typedef unsigned char Lock;
    #elif defined (i686)  || defined(x86_64)
    typedef unsigned int Lock;
    #endif
class Mutex
{

    #if defined(sparc) || defined(i686) || defined(x86_64)
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
    int destroy();
    int recoverMutex();
    static int CAS(int *ptr, int oldVal, int newVal)
    {
        unsigned char ret;
        __asm__ __volatile__ (
                "  lock\n"
                "  cmpxchgl %2,%1\n"
                "  sete %0\n"
                : "=q" (ret), "=m" (*ptr)
                : "r" (newVal), "m" (*ptr), "a" (oldVal)
                : "memory");

        //above assembly returns 0 in case of failure
        if (ret) return 0;

        struct timeval timeout;
        timeout.tv_sec=0;
        timeout.tv_usec=1000;
        os::select(0,0,0,0, &timeout);
            __asm__ __volatile__ (
                "  lock\n"
                "  cmpxchgl %2,%1\n"
                "  sete %0\n"
                : "=q" (ret), "=m" (*ptr)
                : "r" (newVal), "m" (*ptr), "a" (oldVal)
                : "memory");
        //if (ret) return 0;  else {printf("DEBUG::CAS Fails %d-\n", ret); return 1; } 
        if (ret) return 0;  else return 1;

    }
    /*static int CASB(char *ptr, char oldVal, char newVal)
    {   
        unsigned char ret;
        __asm__ __volatile__ ("lock; cmpxchgb %b1, %2"
                               : "=a" (ret)
                               : "m" (*(ptr), "q" (newVal), "0" (oldVal)
                               : "memory");
        printf("Value of ret is %d\n", ret); 
        //above assembly returns 0 in case of failure
        if (ret) return 0;
        struct timeval timeout;
        timeout.tv_sec=0;
        timeout.tv_usec=500;
        os::select(0,0,0,0, &timeout);
        __asm__ __volatile__ ("lock; cmpxchgb %b1, %2"
                               : "=a" (ret)
                               : "m" (*(ptr), "q" (newVal), "0" (oldVal)
                               : "memory");
        if(!ret) { printf("DEBUG::CAS Fails\n"); return 1; } else return 0;
    }*/
};

#endif
