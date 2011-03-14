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

void* os::mmap(void* addr, size_t len, int prot, int flags, file_desc fildes, off_t off)
{
#ifdef WINNT
	HANDLE hFile = ::CreateFileMapping(fildes, 
		NULL, prot, 0, off, NULL);
	if (hFile == NULL)
	{
		 printf("unable to do mmap\n");
		 return NULL;
	}
	return  ::MapViewOfFileEx(hFile, FILE_MAP_WRITE, 0, 0, off, addr);
#elif defined	SOLARIS
    return ((void*)::mmap((char*)addr,len,prot,flags,fildes,off));
#else
    return ((void*)::mmap(addr,len,prot,flags,fildes,off));
#endif
}

int os::munmap(caddr_t addr, size_t len)
{
#ifdef WINNT
	return ::UnmapViewOfFile(addr);
#else
    return ::munmap(addr, len);
#endif
}

int os::atexit(void (*exitHndlr)(void))
{
    return ::atexit(exitHndlr);
}

shared_memory_id os::shm_create(shared_memory_key key, size_t size, int flag)
{
#ifdef WINNT
	char fName[MAX_FILE_PATH_LEN];
	sprintf(fName, "SHM_ID_%d", key);
	HANDLE hFile = ::CreateFileMapping(INVALID_HANDLE_VALUE, 
		NULL, PAGE_READWRITE, 0, size, NULL);
	if (hFile == NULL)
	{
		 printf("unable to do shm_create\n");
		 return -1;
	}
	return key;
#else
    return ::shmget(key, size, IPC_CREAT | IPC_EXCL | flag);
#endif
}

shared_memory_id os::shm_open(shared_memory_key key, size_t size, int flag)
{
#ifdef WINNT
	return shm_create(key, size, flag);
#else
    return ::shmget(key, size, flag);
#endif
}
int os::shmctl(int shmid, int cmd)
{
#ifdef WINNT
	printf("WINDOWS shm_open not implemented\n");
	return 0;
#else
    return ::shmctl(shmid, cmd, NULL);
#endif
}
int os::shm_remove(int shmid)
{
#ifdef WINNT
	printf("WINDOWS shmremove not implemented\n");
	return 0;
#else
    return ::shmctl(shmid, IPC_RMID, NULL);
#endif
}

void*  os::shm_attach(shared_memory_id id, const void *ptr, int flag)
{
#ifdef WINNT
	char fName[MAX_FILE_PATH_LEN];
	sprintf(fName, "SHM_ID_%d", id);
	HANDLE hFile = ::OpenFileMapping(FILE_MAP_ALL_ACCESS,false, fName);
	if (hFile == NULL)
	{
		 printf("unable to do mmap\n");
		 return NULL;
	}
	return  ::MapViewOfFileEx(hFile, FILE_MAP_WRITE, 0, 0, 0, (void*)ptr);
#else
    return ::shmat(id, ptr, flag);
#endif
}

int os::shm_detach (void* addr)
{
#ifdef WINNT
	return ::UnmapViewOfFile(addr);
#else
    return ::shmdt((char*)addr);
#endif
}

int os::gettimeofday(struct timeval *tp)
{
    int retval=0;
#ifdef WINNT
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    GetSystemTimeAsFileTime(&ft);
 
    // The GetSystemTimeAsFileTime returns the number of 100 nanosecond 
    // intervals since Jan 1, 1601 in a structure. Copy the high bits to 
    // the 64 bit tmpres, shift it left by 32 then or in the low 32 bits.
    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;
 
    // Convert to microseconds by dividing by 10
    tmpres /= 10;
 
    // The Unix epoch starts on Jan 1 1970.  Need to subtract the difference 
    // in seconds from Jan 1 1601.
    tmpres -= DELTA_EPOCH_IN_MICROSECS;
 
    // Finally change microseconds to seconds and place in the seconds value. 
    // The modulus picks up the microseconds.
    tp->tv_sec = (long)(tmpres / 1000000UL);
    tp->tv_usec = (long)(tmpres % 1000000UL);
#else
	retval=::gettimeofday(tp, NULL);
#endif
	return retval;
}

struct tm* os::localtime(long *secs)
{
#ifdef SOLARIS
    return (struct tm*) ::localtime(secs);
#elif defined WINNT
    return ::localtime((const time_t*)secs);
#else
    return ::localtime(secs);
#endif
}
int os::open(const char *name, FileOpenMode flags, size_t size)
{
    int retval = -1;
    mode_t oldMode = umask(0000);
    mode_t mode = (mode_t)0644 ;
    retval=::open(name, flags, mode);
    umask(oldMode);
    if (0 == size)
        return (int) retval;
    os::lseek(retval, size-1, SEEK_SET);
    char *buf = (char*)" ";
    os::write(retval, buf, 1);
    return (int) retval;
}
int os::close(int fd)
{
	return ::close(fd);
}

file_desc os::openFile(const char *name, FileOpenMode flags, size_t size)
{

#ifdef WINNT
	HANDLE hFile = CreateFile(name, GENERIC_READ | GENERIC_WRITE,
                       FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) 
    { 
        printf("Unable to open file %s \n", name);
        return (file_desc) -1;
    }
	if (0 == size)
        return (file_desc) hFile;
    mode_t mode = (mode_t)0644 ;
    int retval=::open(name, flags, mode);
    os::lseek(retval, size-1, SEEK_SET);
    char *buf = (char*)" ";
    os::write(retval, buf, 1);
	::close(retval);
    return (file_desc) retval;
#else
    int retval = -1;
    //mode_t mode = S_IRWXU | S_IRGRP | S_IWGRP ;
    mode_t oldMode = umask(0000);
    mode_t mode = (mode_t)0644 ;
    retval=::open(name, flags, mode);
    umask(oldMode);
    if (0 == size)
        return (file_desc) retval;
    os::lseek(retval, size-1, SEEK_SET);
    char *buf = (char*)" ";
    os::write(retval, buf, 1);
    return (file_desc) retval;
#endif
}
int os::openFileForAppend(const char *name, int flag)
{
    mode_t mode = (mode_t)0644 ;
    int flags = flag | O_WRONLY|O_APPEND;
    return  ::open(name, flags, mode);
}

int os::closeFile(file_desc fd)
{
#ifdef WINNT
	return ::CloseHandle(fd);
#else
    return ::close(fd);
#endif
}
int os::lockFile(int fd)
{
#ifdef SOLARIS
    //TODO
	printf("SOLARIS lockFile not implemented\n");
    return 0;
#elif defined WINNT
	printf("WINDOWS lockFile not implemented\n");
    return 0;
#else
    return flock(fd, LOCK_EX);
#endif
}
int os::unlockFile(int fd)
{
#ifdef SOLARIS
	printf("Solaris unlockFile not implemented\n");
    //TODO
    return 0;
#elif defined WINNT
	printf("WINDOWS unlockFile not implemented\n");
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
#ifdef WINNT
	printf("WINDOWS msync not implemented\n");
	return 1;
#else
	return ::msync(addr, len, flags);
#endif
}
int os::fsync(int fildes)
{
#ifdef WINNT
	printf("WINDOWS fsync not implemented\n");
	return 0;
#else
    return ::fsync(fildes);
#endif
}

char* os::encrypt(const char *key, const char *salt)
{
#ifdef WINNT
	printf("WINDOWS encrypt not implemented\n");
	return (char*)key;
#else
    return ::crypt(key, salt);
#endif
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
#ifdef WINNT
	printf("WINDOWS signal not implemented\n");
	return NULL;
#else
	return ::signal(signum, handler);
#endif
}

int os::select(int nfds, fd_set *readfds, fd_set *writefds,
                 fd_set *exceptfds, struct timeval * timeout)
{
    return ::select(nfds, readfds, writefds, exceptfds, timeout);
}
int os::sleep(int secs)
{ 
#ifdef WINNT
    ::Sleep(secs *1000);
	return 0;
#else
    return ::sleep(secs);
#endif
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
#elif defined WINNT
	printf("WINDOWS setenv not implemented \n");
	return 0;
#else
    return ::setenv(envVarName, value,1);
#endif
}

int os::kill(pid_t pid, int sig)
{
#ifdef WINNT
	printf("WINDOWS kill not implemented\n");
	return 0;
#else
	return ::kill(pid, sig);
#endif
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
#if defined WINNT
	printf("WINDOWS: createProcess implemented partially\n");
	STARTUPINFO sinfo;
    PROCESS_INFORMATION pinfo;
    ZeroMemory( &sinfo, sizeof(sinfo) );
    sinfo.cb = sizeof(sinfo);
    ZeroMemory( &pinfo, sizeof(pinfo) );

    if (!::CreateProcess(cmdName, NULL, NULL, NULL, FALSE, 0, NULL, NULL,
        &sinfo, &pinfo))
    {
        return -1;
    }
	return (pid_t)pinfo.dwProcessId;
#else
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
#endif
}
pid_t os::fork()
{
#if defined WINNT
	printf("WINDOWS: fork not implemented\n");
	return 0;
#else
    return ::fork();
#endif
}
size_t os::send(int fd, const void *buf, size_t len, int flags)
{
    size_t totalLen = len;
    size_t nbytes = ::send(fd, (char*)buf, len, flags);
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
    size_t nbytes = ::recv(fd, (char*)buf, len, flags);
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
#if defined WINNT
	printf("WINDOWS: strmatch not implemented\n");
	return 0;
#else
	return ::fnmatch(pattern, str, 0);
#endif
}

int os::msgget(key_t key, int oflag) 
{
#if defined WINNT
	printf("WINDOWS: msgget not implemented\n");
	return 0;
#else
    return ::msgget(key, oflag | IPC_CREAT);
#endif
}

int os::msgsnd(int msqid, const void *ptr, size_t len, int flag) 
{
#if defined WINNT
	printf("WINDOWS: msgsnd not implemented\n");
	return 0;
#else
    return ::msgsnd(msqid, ptr, len, flag);
#endif
}

int os::msgrcv(int msqid, void *ptr, size_t len, long type, int flag) 
{
#if defined WINNT
	printf("WINDOWS: msgrcv not implemented\n");
	return 0;
#else
    return ::msgrcv(msqid, ptr, len, type, flag);
#endif
};

int os::msgctl(int msqid, int cmd, struct msqid_ds *buff)
{
#if defined WINNT
	printf("WINDOWS: msgctl not implemented\n");
	return 0;
#else
    return ::msgctl(msqid, cmd, buff);
#endif
}
bool os::fileExists(char *fileName)
{
#if defined WINNT
	int ret = _access(fileName, 04);
	if (0 == ret) return true; else return false;
#else
    int ret = access(fileName, R_OK);
    if (0 == ret) return true; else return false;
#endif
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
#if defined WINNT
	printf("WINDOWS: getNoOfProcessors not implemented\n");
	return 1;
#else
    return ::sysconf(_SC_NPROCESSORS_ONLN);
#endif
}
mode_t os::umask(mode_t mask)
{
    return::umask(mask);
}
int os::fdatasync(file_desc fd)
{
#ifdef FreeBSD
    return ::fsync(fd);
#elif defined WINNT
	printf("WINDOWS: fdatasync not implemented\n");
	return 0;
#else
    return ::fdatasync(fd);
#endif
}
pid_t os::getpid()
{
#ifdef WINNT
    return ::GetCurrentThreadId();
#else
	return ::getpid();
#endif   
}
pthread_t os::getthrid()
{
#ifdef WINNT
    return ::GetCurrentThreadId();
#else
	return ::pthread_self();
#endif   
}

int os::truncate(const char* filename)
{
#ifdef WINNT
    int fh, result=0;
    if (fh = ::_open(filename, _O_RDWR) == 0)
    {
       result = _chsize(fh, 0);
	   ::_close(fh);
    }
	return result;
#else
	return ::truncate(filename, 0);
#endif   
}
 
void* os::dlsym(LHANDLE hdl, char *fname)
{
#ifdef WINNT
	return ::GetProcAddress(hdl, fname);
#else
	return ::dlsym(hdl, fname);
#endif
}

