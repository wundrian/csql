/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef OS_H
#define OS_H
#include<build.h>

#if defined(SOLARIS) || defined(LINUX) || defined(FreeBSD)

#include <stdio.h>
#include <sys/mman.h>
#include <sys/msg.h>
#include <sys/shm.h>
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
#include <limits.h>
#include <sys/socket.h>
#include <fnmatch.h>
#include <sys/time.h>
#include <stdarg.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/file.h>
#include <sys/wait.h>
#if defined(SOLARIS)
    #include <sys/varargs.h>
    #include <crypt.h>
    #include <errno.h>
    #include <sys/atomic.h>
    #include <timecsql.h>
    #include <ucontext.h>
    //extern int errno;
#endif
#if defined(LINUX)
    #include <execinfo.h>
    #include <ifaddrs.h>
    #include <sys/errno.h>
    #include <crypt.h>
#endif
#if defined(FreeBSD)
    #include <sys/errno.h>
#endif

typedef void (*sighandler_t)(int);

enum FileOpenMode
{
    fileOpenReadOnly = O_RDONLY,
    fileOpenWriteOnly = O_WRONLY,
    fileOpenReadWrite = O_RDWR,
    fileOpenAppend = O_CREAT| O_APPEND |O_RDWR,
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

#define SQL_STMT_LEN 8192
#define MAX_FILE_LEN 1024
#define IDENTIFIER_LENGTH 64
#define ERROR_STRING_LENGTH 128
#define DEFAULT_VALUE_BUF_LENGTH 32
#define STATE_LENGTH 8
#define SYSTEMDB "SYSTEMDB"
#define DBAUSER "root"
#define DBAPASS "manager"
#define I_USER "i@1r4D_f$_a"
#define I_PASS "a_$f_D4r1@i"
#define DEFAULT_CONFIG_FILE "/etc/csql/csql.conf"
#define LOCK_BUCKET_SIZE 2048
#define STMT_BUCKET_SIZE 1023
#define MAX_CHUNKS 20
#define PAGE_SIZE Conf::config.getPageSize()
#define MAX_MUTEX_PER_THREAD 4
#define MAX_THREADS_PER_PROCESS 30
#define MAX_FILE_PATH_LEN 1024
#define CHUNK_NAME_LEN 64
#define LOG_ROLLOVER_SIZE 20*1024*1024
#define SIGCSQL1 SIGUSR1

#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))
#define BITSET(x,y) ((x) & (BIT(y))) 


typedef key_t shared_memory_key;
typedef int   shared_memory_id;
#if defined(__sparcv9)
    typedef long InUse;
#else
    typedef int InUse;
#endif

#endif

class os
{
    public:
    static void* mmap(void* addr, size_t len, int prot, int flags, int fildes, off_t off);
    static int munmap(caddr_t addr, size_t len);
    static int openFile(const char *name, FileOpenMode flags, size_t size);
    static int closeFile(int fd);
    static int lockFile(int fd);
    static int unlockFile(int fd);
    static off_t lseek(int fildes, off_t offset, int whence);
    static int openFileForAppend(const char* fname, int flags);
    static int getFileSize(const char* fname);
    static size_t write(int fildes, char *buf, size_t size);
    static int msync(caddr_t addr, size_t len, int flags);
    static int fsync(int fildes);
    inline static size_t alignLong(size_t size)
        { return ((size - 1) | (sizeof(long) - 1)) + 1;}
    inline static size_t align(size_t size)
        { return ((size - 1) | (sizeof(InUse) - 1)) + 1;}
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
    static pid_t createProcess(const char* cmdName, const char *arg0);
    static pid_t fork();
    static size_t send(int fd, const void *buf, size_t len, int flags);
    static size_t recv(int fd, void *buf, size_t len, int flags);
    static int gethostname(char *hostname, size_t len);
    static int strmatch(char *pattern, char *str);
    static int msgget(key_t key, int oflag);
    static int msgsnd(int msqid, const void *ptr, size_t len, int flag);
    static ssize_t msgrcv(int msqid, void *ptr, size_t len, long type, int flag);
    static int msgctl(int msqid, int cmd, struct msqid_ds *buff);
    static int isValidIP(char ipstr[] );
    static bool fileExists(char *fileName);
    static char* strcasestr(char *s1, const char *s2);
    static int getNoOfProcessors();
    static mode_t umask(mode_t mask);
    static int fdatasync(int fd);
};

#endif
