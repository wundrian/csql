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
#include<Debug.h>
int Logger::createLogRecord(LogLevel level, char* filename,
                              int lineNo, char* message, char **buffer)
{
    char    tempBuffer[25];
    struct timeval timeStamp;
    os::gettimeofday(&timeStamp);
    struct tm*      tempTm = os::localtime(&timeStamp.tv_sec);
    strftime(tempBuffer, 25, "%d/%m/%Y %H:%M:%S.", tempTm);
    snprintf(*buffer, MAX_TRACE_LOG_LENGTH, "%s::%s:%d::%s::%d::%d::%lu::%s\n",
        levelNames[level], tempBuffer, timeStamp.tv_usec,
        filename, lineNo,
        os::getpid(),
        os::getthrid(),
        message);
    return 0;
}

//TODO::Multiple files: If it exceeeds some configured size, it rolls over to
//next with suffix like file.1, file.2, ...
int Logger::log(LogLevel level, char* filename,
                  int lineNo, char *format, ...)
{
    if (LogOff == configLevel) return 0;
    if (level <= configLevel )
    {
        va_list ap;
        char mesgBuf[1024]; 
        va_start(ap, format);

        int err = ::vsnprintf(mesgBuf, sizeof(mesgBuf), format,ap);
        if(err < 0) {
            return err;
        } 
        char *buffer = new char[MAX_TRACE_LOG_LENGTH];
        createLogRecord(level, filename, lineNo, mesgBuf, &buffer);
        //TODO::There is some issue in locking. Need to look into this and then
        //uncomment the below lines
        //int ret = mutex_.tryLock(5, 100000);
        int ret = 0;
        if (ret != 0)
        {
            printError(ErrLockTimeOut,"Unable to acquire logger Mutex");
            delete[] buffer;
            return -1;
        }        
        os::write(fdLog, buffer, strlen(buffer));
        os::fsync(fdLog);
        //mutex_.releaseLock();
        delete[] buffer;
    }
    return 0;
}

DbRetVal Logger::startLogger(char *filename, bool isCreate)
{
    char file[256];
    int i =0;
    if (isCreate) 
    {
        while (true)
        {
            sprintf(file, "%s.%d", filename, i);
            //check if file exists. If not create it
            if (::access(file, F_OK) != 0 ) break;
            i++;
        }
        fdLog = os::openFile(file, fileOpenCreat,0);
    }
    else
    {
        int newlyCreatedID =0;
        while (true)
        {
            sprintf(file, "%s.%d", filename, i);
            //check if file exists. If not create it
            if (::access(file, F_OK) != 0 ) break;
            newlyCreatedID = i;
            i++;
        }
        sprintf(file, "%s.%d", filename, newlyCreatedID );
        fdLog = os::openFile(file, fileOpenAppend,0);
    }
    if (fdLog == -1)
    {
        printError(ErrSysInit,"Unable to create log file. Check whether server started\n");
        return ErrSysInit;
    }
    //TODO::get this value from configuration file
    configLevel= LogFinest;
    return OK;
}

void Logger::stopLogger()
{
    os::closeFile(fdLog);
}
