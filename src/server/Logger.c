/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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
    snprintf(*buffer, MAX_TRACE_LOG_LENGTH, "%s::%s:%d::%s::%d::%d::%d::%s\n",
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
        int ret = mutex_.tryLock();
        if (ret != 0)
        {
            printError(ErrLockTimeOut,"Unable to acquire logger Mutex");
            delete[] buffer;
            return -1;
        }        
        os::write(fdLog, buffer, strlen(buffer));
        os::fsync(fdLog);
        mutex_.releaseLock();
        delete[] buffer;
    }
    return 0;
}

DbRetVal Logger::startLogger(char *filename, bool isCreate)
{
    if (isCreate) 
        fdLog = os::openFile(filename, fileOpenCreat,0);
    else
        fdLog = os::openFile(filename, fileOpenAppend,0);
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
