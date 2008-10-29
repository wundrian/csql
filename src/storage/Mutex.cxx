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
#include <os.h>
#include <Mutex.h>
#include <Debug.h>
#include <NanoTimer.h>
#include <Config.h>
#include <Process.h>
Mutex::Mutex()
{
#if defined(sparc) || defined(i686)
    lock =0;
#else
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&mutex_, &attr);
#endif
}

int Mutex::init()
{
#if defined(sparc) || defined(i686)
    lock = 0;
#else
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    int ret = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    printf("pthread_mutexattr_setpshared Returned %d\n", ret);
    pthread_mutex_init(&mutex_, &attr);
    pthread_mutexattr_destroy(&attr);
#endif
    return 0;
}
int Mutex::init(char *mname)
{
    if (strlen(mname) > 19 ) return 0;
    init();
    strcpy(name, mname);
    return 0;

}

#if defined(sparc) || defined(i686)
int TSL(Lock *lock)
{
/*
    if (lock == 0) {
       __asm("mov  $1, %eax");
       __asm("mov 20(%ebp), %edx");
       __asm("xchg %eax, (%edx)");
       __asm("test %eax %eax");
       __asm("jnz .L1000"); 
       return 0;
    } else
    {
        __asm(".L1000:");
        return 1;
    }
*/
/*Was Working in linux
        char oldval;
        __asm__ __volatile__(
                "xchgb %b0,%1"
                :"=q" (oldval), "=m" (lock)
                :"0" (0) : "memory");

        return oldval > 0;
*/
#if defined(i686)
    int*  lw;
    int   res;
    lw = (int*)lock;
    if (*lock == 1) return 1;
    /* In assembly we use the so-called AT & T syntax where
    the order of operands is inverted compared to the ordinary Intel
    syntax. The 'l' after the mnemonics denotes a 32-bit operation.
    The line after the code tells which values come out of the asm
    code, and the second line tells the input to the asm code. */

    /* This assembly compiles only with -O2 option, and not with -g option. Version1
    __asm__ __volatile__(
        "movl $1, %%eax; xchgl (%%ecx), %%eax" 
        : "=eax" (res), "=m" (*lw) 
        : "ecx" (lw));
    */

     /* This assembly takes lot of time for test/performance/DMLTest. Version2
     __asm__ __volatile__(
	"movl %1, %0; xchgl %0, %2" 
	: "=r" (res), "=r" (lock) 
        : "r" (lock));
     */
    

    // This assembly is Version3. Working fine for now
    __asm__ __volatile__(
        "xchgl %0, %1 \n\t"
        : "=r"(res), "=m"(*lock)
        : "0"(1), "m"(*lock)
        : "memory"); 

    //fprintf(stderr,"after asm %d ret %d\n", *lock, res);

    return(res);

#elif defined (sparc)
    Lock res;
    __asm__ __volatile__("ldstub  [%2], %0    \n"
       "=r"(res), "+m"(*lock)
       "r"(lock)
       "memory");
     return (int) res;
#endif
}
#endif

int Mutex::tryLock(int tryTimes, int waitmsecs)
{
    int tries = 0;
    int ret = 0;
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = waitmsecs;
    if (tryTimes == 0 && waitmsecs == 0)
    {
        timeout.tv_sec = Conf::config.getMutexSecs();
        timeout.tv_usec = Conf::config.getMutexUSecs();
        tryTimes = Conf::config.getMutexRetries();
    }
    while (tries < tryTimes)
    {
#if defined(sparc) || defined(i686)
    if (TSL(&lock) == 0) 
    {
        return 0; 
    }
#else
    ret = pthread_mutex_trylock(&mutex_);
    if (EBUSY  != ret) return 0;

#endif
        os::select(0, 0, 0, 0, &timeout);
        tries++;
    }
    printError(ErrLockTimeOut, "Unable to get the mutex , tried %d times", tries);
    return 1;
}


int Mutex::getLock(int procSlot, bool procAccount)
{
    int ret=0;
#if defined(sparc) || defined(i686)
    ret = tryLock();
    //add it to the has_ of the ThreadInfo
    if (ret ==0 && procAccount) ProcessManager::addMutex(this, procSlot);

    return ret;
#else
    ret = pthread_mutex_lock(&mutex_);
#endif
    if (ret == 0) return 0;
    else
        return 1;
}

int Mutex::releaseLock(int procSlot, bool procAccount)
{
    int ret=0;
#if defined(sparc) || defined(i686)
    /*int *lw = &lock;
    if (*lw == 0) return 0;
    __asm__ __volatile__("movl $0, %%eax; xchgl (%%ecx), %%eax" :
                      "=m" (*lw) :
                      "ecx" (lw) :
                      "eax");   
    */
    lock = 0;
#else
    ret = pthread_mutex_unlock(&mutex_);
#endif
    if (ret == 0 && procAccount) 
    {
        ProcessManager::removeMutex(this, procSlot);
        return ret;
    }
    else
        return 1;
}

int Mutex::destroy()
{
#if defined(sparc) || defined(i686)
#else
    return pthread_mutex_destroy(&mutex_);
#endif
    return 0;
}