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
#if defined(sparc) || defined(i686) || defined (x86_64)
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
#if defined(sparc) || defined(i686) || defined (x86_64)
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
    init();
    if (strlen(mname) > 19 ) return 0;
    strcpy(name, mname);
    return 0;

}

#if defined(sparc) || defined(i686) || defined (x86_64)
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
#if defined(LINUX) 
    int*  lw;
    int   res;
    lw = (int*)lock;
    if (*lock == 1) return 1;
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

#elif defined (SOLARIS)
    Lock res;
    res = atomic_cas_32((unsigned*)lock, 0, 1);
    return (res);
#endif
}
#endif
int Mutex::tryShareLock(int tryTimes, int waitmsecs,bool share, bool isDelete)
{
    int ret=0;
    int oldValue = (int)lock;
    if (oldValue >= 0  && share){
        ret = CAS((int*)&lock, oldValue, oldValue+1);
    }else if ((oldValue == 1 && isDelete ) || ( !share && oldValue == 0) ){
        ret = CAS((int*)&lock, oldValue, -1);
    }else { ret = 1;} 
    if (0 == ret) return 0; 
    int tries = 1;
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = waitmsecs;
    if (tryTimes == 0 && waitmsecs == 0)
    {
        timeout.tv_sec = Conf::config.getMutexSecs();
        timeout.tv_usec = Conf::config.getMutexUSecs();
        tryTimes = Conf::config.getMutexRetries();
    }
    int cnt=0;
    while (tries < tryTimes)
    {
#if defined(sparc) || defined(i686) || defined (x86_64)
    if (Conf::config.getNoOfProcessors() >1) {
        cnt=0;
        while(true) {
            oldValue = (int)lock;
            if (oldValue >= 0  && share) {
                ret = CAS((int*)&lock, oldValue, oldValue+1);
            }else if ((oldValue == 1 && isDelete ) || (!share && oldValue == 0) ) {
                ret = CAS((int*)&lock, oldValue, -1);
            }else { ret = 1; }
         
            if(0 == ret ) return 0;
            cnt++;
            if (cnt == tryTimes * 100) break;
         }
    }else {
            oldValue = (int)lock;
            if (oldValue >= 0  && share) {
                ret = CAS((int*)&lock, oldValue, oldValue+1);
            }else if ((oldValue == 1 && isDelete ) || (!share && oldValue == 0) ){
                ret = CAS((int*)&lock, oldValue, -1);
            } else { ret =1;}
            if(ret==0) return 0;
    }
#else
    ret = pthread_mutex_trylock(&mutex_);
    if (EBUSY  != ret) return 0;

#endif
        os::select(0, 0, 0, 0, &timeout);
        tries++;
    }
    printError(ErrLockTimeOut, "Unable to get the mutex %s, tried %d times", name,tries);
    return 1;
}

int Mutex::tryLock(int tryTimes, int waitmsecs)
{
    if (TSL(&lock) == 0) 
    {
        return 0; 
    }
    int tries = 1;
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
    int cnt=0;
    while (tries < tryTimes)
    {
#if defined(sparc) || defined(i686) || defined (x86_64)
    if (Conf::config.getNoOfProcessors() >1) {
        cnt=0;
        while(true) {
            if (TSL(&lock) == 0) 
            {
               return 0; 
            }
            cnt++;
            if (cnt == tryTimes * 100) break;
        }
    }else {
        if (TSL(&lock) == 0)  return 0; 
    }
#else
    ret = pthread_mutex_trylock(&mutex_);
    if (EBUSY  != ret) return 0;

#endif
        os::select(0, 0, 0, 0, &timeout);
        tries++;
    }
    printError(ErrLockTimeOut, "Unable to get the mutex %s, val:%d tried %d times", name, lock, tries);
    return 1;
}

int Mutex::getLock(int procSlot, bool procAccount)
{
    int ret=0;
#if defined(sparc) || defined(i686) || defined (x86_64)
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
#if defined(sparc) || defined(i686) || defined (x86_64)
    /*int *lw = &lock;
    if (*lw == 0) return 0;
    __asm__ __volatile__("movl $0, %%eax; xchgl (%%ecx), %%eax" :
                      "=m" (*lw) :
                      "ecx" (lw) :
                      "eax");   
    */
    lock = 0;
    //TEMP::PRABA:TODO::CHANGE IT TO CAS
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

int Mutex::getShareLock(int procSlot, bool procAccount)
{
    int ret=0;
#if defined(sparc) || defined(i686) || defined (x86_64)
    ret = tryShareLock(0,0,true,false);
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

int Mutex::getExclusiveLock(int procSlot, bool procAccount, bool isDelete)
{
    int ret=0;
#if defined(sparc) || defined(i686) || defined (x86_64)
    ret = tryShareLock(0,0,false,isDelete);
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

int Mutex::releaseShareLock(int procSlot, bool procAccount)
{
    int ret=0;
#if defined(sparc) || defined(i686) || defined (x86_64)
    int oldValue  = (int)lock;
    if( oldValue > 1)
    { 
        ret = CAS((int*)&lock, oldValue, oldValue-1 );
    }
    if( oldValue == 1 || oldValue == -1 )
    {
        ret = CAS((int*)&lock, oldValue, 0 );   
    }
    if( ret != 0)
    {
        int tries = 1;
        struct timeval timeout;
        timeout.tv_sec = Conf::config.getMutexSecs();
        timeout.tv_usec = Conf::config.getMutexUSecs();
        int tryTimes = Conf::config.getMutexRetries();
        while (tries < tryTimes)
        {
             oldValue = (int)lock;
             if( oldValue > 1){
                 ret = CAS((int*)&lock, oldValue, (*(int*)&lock)-1 );
                 if(ret == 0) break;
             }
             if( oldValue == 1 || oldValue == -1 )
             {
                  ret = CAS((int*)&lock, oldValue, 0 );
                  if(ret == 0) break;
             }
             tries++; 
        }
    }
#else
    ret = pthread_mutex_unlock(&mutex_);
#endif
    if (ret == 0 && procAccount )
    {
        ProcessManager::removeMutex(this, procSlot);
        return ret;
    }
    else
        return 1;
}

int Mutex::destroy()
{
#if defined(sparc) || defined(i686) || defined (x86_64)
#else
    return pthread_mutex_destroy(&mutex_);
#endif
    return 0;
}

int Mutex::recoverMutex()
{
    int ret=0;
#if defined(sparc) || defined(i686) || defined (x86_64)
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
    return ret;
}

int Mutex::CASL(long *ptr, long oldVal, long newVal)
{
#ifdef SOLARIS
#if defined(__sparcv9) || defined(x86_64) || defined (__x86_64)
    unsigned long res = atomic_cas_64((unsigned long*)ptr, 
                             (unsigned long) oldVal, (unsigned long) newVal);
    if (res == oldVal) return 0; else return 1;
#else 
    return CAS((int*)ptr, (int)oldVal, (int)newVal);
#endif
#endif
#ifdef LINUX
#ifdef x86_64
        long result;
        __asm__ __volatile__ ("lock; cmpxchgq %q2, %1"
                        : "=a" (result), "=m" (*ptr)
                        : "r" (newVal), "m" (*ptr), "0" (oldVal));
        if (result == oldVal) return 0;

        struct timeval timeout;
        timeout.tv_sec=0;
        timeout.tv_usec=1000;
        os::select(0,0,0,0, &timeout);
        __asm__ __volatile__ ("lock; cmpxchgq %q2, %1"
                        : "=a" (result), "=m" (*ptr)
                        : "r" (newVal), "m" (*ptr), "0" (oldVal));

        //if (result) return 0;  else {printf("DEBUG::CAS Fails %d-\n", result); return 1; }
        if (result == oldVal) return 0;  else return 1;
#else
        return CAS((int*)ptr, (int)oldVal, (int)newVal);
#endif
#endif

}
int Mutex::CAS(int *ptr, int oldVal, int newVal)
{
#ifdef LINUX
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
#else //for solaris
    unsigned int ret;
    ret = atomic_cas_32((unsigned int*)ptr, (unsigned int) oldVal, 
                        (unsigned int) newVal);
    if (ret == oldVal) return 0; else return 1;
#endif
}
