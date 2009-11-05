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
#include <Debug.h>

void* os::mmap(void* addr, size_t len, int prot, int flags, int fildes, off_t off)
{
#ifdef SOLARIS
    return ((void*)::mmap((char*)addr,len,prot,flags,fildes,off));
#else
    return ((void*)::mmap(addr,len,prot,flags,fildes,off));
#endif
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

int os::gettimeofday(struct timeval *tp)
{
    int retval;
    retval=::gettimeofday(tp, NULL);
    return retval;
}

struct tm* os::localtime(long *secs)
{
#ifdef SOLARIS
    return (struct tm*) ::localtime(secs);
#else
    return ::localtime(secs);
#endif
}

int os::openFile(const char *name, FileOpenMode flags, size_t size)
{
    int retval = -1;
    //mode_t mode = S_IRWXU | S_IRGRP | S_IWGRP ;
    mode_t oldMode = umask(0000);
    mode_t mode = (mode_t)0644 ;
    retval=::open(name, flags, mode);
    umask(oldMode);
    if (0 == size)
        return retval;
    os::lseek(retval, size-1, SEEK_SET);
    char *buf = (char*)" ";
    os::write(retval, buf, 1);
    return retval;
}
int os::openFileForAppend(const char *name, int flag)
{
    mode_t mode = (mode_t)0644 ;
    int flags = flag | O_WRONLY|O_APPEND;
    return  ::open(name, flags, mode);
}

int os::closeFile(int fd)
{
    return ::close(fd);
}
int os::lockFile(int fd)
{
#ifdef SOLARIS
    //TODO
    return 0;
#else
    return flock(fd, LOCK_EX);
#endif
}
int os::unlockFile(int fd)
{
#ifdef SOLARIS
    //TODO
    return 0;
#else
    return ::flock(fd, LOCK_UN);
#endif
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
int os::getFileSize(const char *fileName)
{
    struct stat buf;
    stat(fileName, &buf);
    return buf.st_size;
}

char* os::getenv(const char *envVarName)
{
    char *retVal;
    retVal = ::getenv(envVarName);
    return retVal;
}

int os::setenv(const char *envVarName, const char *value)
{
#ifdef SOLARIS
    char str[IDENTIFIER_LENGTH*3];
    sprintf(str, "%s=%s", envVarName, value);
    return putenv(str);
#else
    return ::setenv(envVarName, value,1);
#endif
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
pid_t os::createProcess(const char* cmdName, const char* execName)
{
    pid_t pid;
    pid = ::fork();
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
    pid=::execl(cmdName,execName, NULL);
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
    size_t totalLen = len;
    size_t nbytes = ::send(fd, buf, len, flags);
    while (nbytes != -1 && nbytes != len) {
        len = len - nbytes;
        nbytes = ::send(fd, ((char *)buf)+nbytes, len, flags);
    }
    if (nbytes == -1) return -1;
    else return totalLen;       
}
size_t os::recv(int fd, void *buf, size_t len, int flags)
{
    size_t totalLen = len;
    size_t nbytes = ::recv(fd, buf, len, flags);
    if (!nbytes) return 0;
    while (nbytes != -1 && nbytes != len) {
        len = len - nbytes;
        nbytes = ::recv(fd, ((char *)buf)+nbytes, len, flags);
    }
    if (nbytes == -1) return -1;
    else return totalLen;
}
int os::gethostname(char *hostname, size_t len)
{
    return ::gethostname(hostname, len);
}
int os::strmatch(char *pattern, char *str)
{
    return ::fnmatch(pattern, str, 0);
}

int os::msgget(key_t key, int oflag) 
{
    return ::msgget(key, oflag | IPC_CREAT);
}

int os::msgsnd(int msqid, const void *ptr, size_t len, int flag) 
{
    return ::msgsnd(msqid, ptr, len, flag);
}

ssize_t os::msgrcv(int msqid, void *ptr, size_t len, long type, int flag) 
{
    return ::msgrcv(msqid, ptr, len, type, flag);
};

int os::msgctl(int msqid, int cmd, struct msqid_ds *buff)
{
    return ::msgctl(msqid, cmd, buff);
}
bool os::fileExists(char *fileName)
{
    int ret = access(fileName, R_OK);
    if (0 == ret) return true; else return false;
}
int os::isValidIP(char ipstr[] )
{
#if defined(LINUX)
    struct ifaddrs * ifAddrStruct=NULL;
    void * tmpAddrPtr=NULL;
    char  addressBuffer[100];
    int i=0;
    getifaddrs(&ifAddrStruct);

    while (ifAddrStruct!=NULL)
    {
            if (ifAddrStruct->ifa_addr->sa_family==AF_INET && strcmp(ifAddrStruct->ifa_name, "lo0")!=0)
            {
                tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
                inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, 100);
                if(strcmp(ipstr,addressBuffer) == 0)
                {
          //         printf("\nThe ip is matched %s and %s",ipstr,addressBuffer);
                    return 1;
                }
             //   printf("IP Address %s\n", inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, 100));
            }
            ifAddrStruct=ifAddrStruct->ifa_next;
    }
#endif
    return 0;
}
char* os::strcasestr(char *str1, const char *str2)
{
#if defined(LINUX)
    return ::strcasestr(str1, str2);
#else
    return ::strstr(str1, str2);
    /*
    int size=strlen(str1);
    char *tmpStr=new char[size];
    char *tmpStrPtr=NULL;
    strcpy(tmpStr, str1);
    tmpStrPtr=tmpStr;
    while(*tmpStrPtr != '\0')
    {
        *tmpStrPtr=::toupper(*tmpStrPtr);
        tmpStrPtr++;
    }
    char *subStrPtr = ::strstr(tmpStr, str2);
    delete []tmpStr;
    return subStrPtr;
    */
#endif
}
int os::getNoOfProcessors()
{
    return ::sysconf(_SC_NPROCESSORS_ONLN);
}
mode_t os::umask(mode_t mask)
{
    return::umask(mask);
}
int os::fdatasync(int fd)
{
#ifdef FreeBSD
    return ::fsync(fd);
#else
    return ::fdatasync(fd);
#endif
}

