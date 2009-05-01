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
#ifndef OS_H
#define OS_H
#include<build.h>

#if defined(solaris) || defined(LINUX)

#include <stdio.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/errno.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <math.h>
#include <signal.h>
#include <ctype.h>
#include <sys/socket.h>
#include <fnmatch.h>
#include <execinfo.h>
#if defined(solaris)
    #include <sys/varargs.h>
#endif
#if defined(LINUX)
    #include <sys/time.h>
    #include <stdarg.h>
#endif
typedef void (*sighandler_t)(int);

enum FileOpenMode
{
    fileOpenReadOnly = O_RDONLY,
    fileOpenWriteOnly = O_WRONLY,
    fileOpenReadWrite = O_RDWR,
    fileOpenAppend = O_APPEND |O_RDWR,
    fileOpenCreat = O_CREAT |O_RDWR,
    // If set and fileOpenExcl is set, the
    // open will fail if the file already exists.
    fileOpenExcl = O_EXCL,
    fileOpenTrunc = O_TRUNC
};

enum MapProtMode
{
    mapProtRead = PROT_READ,
    mapProtWrite = PROT_WRITE,
    mapProcExec = PROT_EXEC,
    mapProcNone = PROT_NONE
};

enum MapMode
{
    mapShared = MAP_SHARED,
    mapPrivate = MAP_PRIVATE,
    mapFixed = MAP_FIXED,
    // Interpret address exactly.
    mapNoReserve = MAP_NORESERVE,
    // Don't reserver swap space.

    //mapAlign = MAP_ALIGN,
    //for msync system call
    mapSync = MS_SYNC ,
    mapASync = MS_ASYNC

};

#define MAX_FILE_LEN 1024
#define IDENTIFIER_LENGTH 64
#define ERROR_STRING_LENGTH 128
#define DEFAULT_VALUE_BUF_LENGTH 32
#define SYSTEMDB "SYSTEMDB"
#define DBAUSER "root"
#define DBAPASS "manager"
#define LOCK_BUCKET_SIZE 2048
#define MAX_CHUNKS 20
#define PAGE_SIZE Conf::config.getPageSize()
#define MAX_MUTEX_PER_THREAD 3
#define MAX_THREADS_PER_PROCESS 30
#define MAX_FILE_PATH_LEN 1024
#define CHUNK_NAME_LEN 64

#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))
#define BITSET(x,y) ((x) & (BIT(y))) 


typedef key_t shared_memory_key;
typedef int   shared_memory_id;

#endif


class os
{
    public:
    static caddr_t mmap(caddr_t addr, size_t len, int prot, int flags, int fildes, off_t off);
    static int munmap(caddr_t addr, size_t len);
    static int openFile(const char *name, FileOpenMode flags, size_t size);
    static int closeFile(int fd);
    static off_t lseek(int fildes, off_t offset, int whence);
    static size_t write(int fildes, char *buf, size_t size);
    static int msync(caddr_t addr, size_t len, int flags);
    static int fsync(int fildes);
    inline static size_t alignLong(size_t size)
        { return ((size - 1) | (sizeof(long) - 1)) + 1;}
    inline static size_t align(size_t size)
        { return ((size - 1) | (sizeof(long) - 1)) + 1;}
    static char*  encrypt(const char * key, const char *salt);
    static void* memset(void *src, int c, size_t size);
    static void* memcpy(void *src, const void *dest, size_t size);
    static int   memcmp(const void *s1, const void *s2, size_t size);
    static int select(int nfds, fd_set *readfds, fd_set *writefds,
                      fd_set *exceptfds, struct timeval * timeout);
    
    static int usleep(int microsecs);
    static int sleep(int secs);
    static shared_memory_id shm_create(shared_memory_key key, size_t size, int flag);
    static shared_memory_id shm_open(shared_memory_key key, size_t size, int flag);
    static void*  shm_attach(shared_memory_id id, const void *ptr, int flag);
    static int shm_detach (void*);
    static int shmctl(int shmid, int cmd);
    inline static double floor(double val)
        { return ::floor(val); }
    static sighandler_t signal(int signum, sighandler_t handler);

    static int gettimeofday(struct timeval *tp);
    static struct tm* localtime(long *secs);
    static pid_t getpid()
       { return ::getpid(); }
    static pthread_t getthrid()
       { return ::pthread_self(); }
    static char* getenv(const char *envVarName);
    static int setenv(const char *envVarName, const char *value);

    static int kill(pid_t pid, int sig);
    static bool atobool(char *value);
    static pid_t createProcess(const char* cmdName, const char *arg0, ...);
    static pid_t fork();
    static size_t send(int fd, const void *buf, size_t len, int flags);
    static size_t recv(int fd, void *buf, size_t len, int flags);
    static int gethostname(char *hostname, size_t len);
    static int strmatch(char *pattern, char *str);
};

#endif
