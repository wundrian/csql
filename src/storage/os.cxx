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
#include <math.h>
#include <os.h>
#include <Debug.h>

caddr_t os::mmap(caddr_t addr, size_t len, int prot, int flags, int fildes, off_t off)
{
    return ((caddr_t)::mmap(addr,len,prot,flags,fildes,off));
}

int os::munmap(caddr_t addr, size_t len)
{
    return ::munmap(addr, len);
}


shared_memory_id os::shm_create(shared_memory_key key, size_t size, int flag)
{
    return ::shmget(key, size, IPC_CREAT | IPC_EXCL | flag);
    //return ::shmget(key, size, IPC_CREAT | flag);
}

shared_memory_id os::shm_open(shared_memory_key key, size_t size, int flag)
{
    return ::shmget(key, size, flag);
}
int os::shmctl(int shmid, int cmd)
{
    return ::shmctl(shmid, cmd, NULL);
}

void*  os::shm_attach(shared_memory_id id, const void *ptr, int flag)
{
    return ::shmat(id, ptr, flag);
}

int os::shm_detach (void* addr)
{
    return ::shmdt((char*)addr);
}

double os::floor(double val)
{
    return ::floor(val);
}

int os::gettimeofday(struct timeval *tp)
{
    int retval;
    retval=::gettimeofday(tp, NULL);
    return retval;
}

struct tm* os::localtime(long *secs)
{
    return ::localtime(secs);
}

pid_t os::getpid()
{
    return ::getpid();
}
pthread_t os::getthrid()
{
    return ::pthread_self();
}




int os::openFile(const char *name, FileOpenMode flags, size_t size)
{
    int retval = -1;
    //mode_t mode = S_IRWXU | S_IRGRP | S_IWGRP ;
    mode_t mode = (mode_t)0755 ;
    retval=::open(name, flags, mode);
    if (0 == size)
        return retval;
    os::lseek(retval, size-1, SEEK_SET);
    char *buf = (char*)" ";
    os::write(retval, buf, 1);
    return retval;
}

int os::closeFile(int fd)
{
    return ::close(fd);
}

off_t os::lseek(int fildes, off_t offset, int whence)
{
    return ::lseek(fildes, offset, whence);
}

size_t os::write(int fildes, char *buf, size_t size)
{
    return ::write(fildes, buf, size);
}

int os::msync(caddr_t addr, size_t len, int flags)
{
    return ::msync(addr, len, flags);
}
int os::fsync(int fildes)
{
    return ::fsync(fildes);
}

char* os::encrypt(const char *key, const char *salt)
{
    return ::crypt(key, salt);
}

void* os::memset(void *src, int c, size_t size)
{
    return::memset(src, c, size);
}

void* os::memcpy(void *src, const void *dest, size_t size)
{
    return ::memcpy(src, dest, size);
}

int os::memcmp(const void *s1, const void *s2, size_t size)
{
    return ::memcmp(s1, s2, size);
}
sighandler_t os::signal(int signum, sighandler_t handler)
{
    return ::signal(signum, handler);
}

size_t os::alignLong(size_t size)
{
    return ((size - 1) | (sizeof(long) - 1)) + 1;
}

size_t os::align(size_t size)
{
    //Calls alignLong
    return ((size - 1) | (sizeof(long) - 1)) + 1;
}

int os::select(int nfds, fd_set *readfds, fd_set *writefds,
                 fd_set *exceptfds, struct timeval * timeout)
{
    return ::select(nfds, readfds, writefds, exceptfds, timeout);
}
int os::sleep(int secs)
{ 
    return ::sleep(secs);
}
int os::usleep(int msecs)
{ 
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = msecs;
    os::select(0,0,0,0, &timeout);
    return 0;
}



char* os::getenv(const char *envVarName)
{
    char *retVal;
    retVal = ::getenv(envVarName);
    return retVal;
}

int os::setenv(const char *envVarName, const char *value)
{
    return ::setenv(envVarName, value,1);
}

int os::kill(pid_t pid, int sig)
{
    return ::kill(pid, sig);
}
bool os::atobool(char *value)
{
    if (strlen(value) ==3 && strncasecmp(value,"YES",3)==0) return true;
    else if (strlen(value) ==2 && strncasecmp(value,"NO", 2)==0) return false;
    else if (strlen(value) ==4 && strncasecmp(value,"true",4)==0) return true;
    else if (strlen(value) ==5 && strncasecmp(value,"false",5)==0) return false;
    return false;
}
pid_t os::createProcess(const char* cmdName, const char *arg0, ...)
{
    pid_t pid;
    pid = ::vfork();
    if (pid == (pid_t) -1 )
    {
        printf("Process creation failed\n");
        return -1;
    }
    if (pid >0)
    {
        //return for parent
        return pid;
    }
    va_list ap;
    va_start(ap,arg0);

    const char *argv[5];

    argv[0]=cmdName;
    argv[1]=arg0;

    argv[2]=NULL;
    int i = 2;
    while(argv[i++]=va_arg(ap,char *));
    switch(i){
        case 2:
            pid=::execl(argv[0],argv[1]);break;
        case 3:
            pid=::execl(argv[0],argv[1],argv[2]);break;
        case 4:
            pid=::execl(argv[0],argv[1],argv[2],argv[3]);break;
        case 5:
            pid=::execl(argv[0],argv[1],argv[2],argv[3],argv[4]);break;
        default:
            printf("only three options allowed\n");
            pid=-1;break;
    }
    if (pid < 0)
        printf("Exec failed\n");
    return pid;

}
pid_t os::fork()
{
    return ::fork();
}
size_t os::send(int fd, const void *buf, size_t len, int flags)
{
    return ::send(fd, buf, len, flags);
}
size_t os::recv(int fd, void *buf, size_t len, int flags)
{
    return ::recv(fd, buf, len, flags);
}
int os::gethostname(char *hostname, size_t len)
{
    return ::gethostname(hostname, len);
}
int os::strmatch(char *pattern, char *str)
{
    return ::fnmatch(pattern, str, 0);
}
