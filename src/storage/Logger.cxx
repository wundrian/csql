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
#include<Config.h>
Logger  Conf::logger;
int Logger::createLogRecord(LogLevel level, char* filename,
                              int lineNo, char* message, char **buffer)
{
    char    tempBuffer[25];
    struct timeval timeStamp;
    os::gettimeofday(&timeStamp);
    struct tm*      tempTm = os::localtime(&timeStamp.tv_sec);
#if defined(SOLARIS) && defined(REMOTE_SOLARIS)
    strftime(tempBuffer, 25, "%d/%m/%Y %H:%M:%S", (struct std::tm*) tempTm);
#else
    strftime(tempBuffer, 25, "%d/%m/%Y %H:%M:%S", tempTm);
#endif
    snprintf(*buffer, MAX_TRACE_LOG_LENGTH, "%s.%6d:%5d:%10lu:%s:%d:%s\n",
        tempBuffer, timeStamp.tv_usec,
        os::getpid(),
        os::getthrid(),
        filename, lineNo,
        message);
    return 0;
}
void Logger::rollOverIfRequired()
{
    char *fileName = Conf::config.getLogFile();
    int fileSize = os::getFileSize(fileName);
    if (fileSize < LOG_ROLLOVER_SIZE) return ;
    char cmd[MAX_FILE_LEN];
    int ret =0;
    int tries=0, totalTries=Conf::config.getMutexRetries();
    while (tries < totalTries) {
        ret = os::lockFile(fdLog);
        if (ret ==0) break;
        os::usleep(10000);
        tries++;
    }
    if (tries == totalTries)
    {
        printError(ErrLockTimeOut,"Unable to lock log file for rollover %d",fdLog);
        return ;
    }

    time_t cnow = ::time(NULL);
#ifdef SOLARIS
    struct std::tm *tmval = localtime(&cnow);
#else
    struct tm *tmval = localtime(&cnow);
#endif
    sprintf(cmd, "cp %s %s.%d-%d-%d:%d:%d:%d", fileName, fileName, 
                  tmval->tm_year+1900,
                  tmval->tm_mon+1, tmval->tm_mday, tmval->tm_hour, 
                  tmval->tm_min, tmval->tm_sec);
    ret = system(cmd);
    if (ret != 0) {
        printError(ErrWarning, "Unable to rollover the log file");
    }else {
       os::truncate(fileName);
    }
    os::unlockFile(fdLog);
    return;
}

int Logger::log(LogLevel level, char* filename,
                  int lineNo, char *format, ...)
{
    int configLevel =  Conf::config.getLogLevel();
    if (LogOff == configLevel) return 0;
    int ret =0;
    if (level <= configLevel )
    {
        rollOverIfRequired();
        va_list ap;
        char mesgBuf[1024]; 
        va_start(ap, format);

        int err = ::vsnprintf(mesgBuf, sizeof(mesgBuf), format,ap);
        if(err < 0) {
            return err;
        } 
        char *buffer = new char[MAX_TRACE_LOG_LENGTH];
        createLogRecord(level, filename, lineNo, mesgBuf, &buffer);
        int tries=0, totalTries=Conf::config.getMutexRetries();
        while (tries < totalTries) {
            ret = os::lockFile(fdLog);
            if (ret ==0) break;
            if (ret !=0 && errno == EBADF) {
                fdLog = os::open(filename, fileOpenAppend,0);
                if (fdLog == -1)
                {
                    printError(ErrSysInit,"Unable to open log file");
                    delete[] buffer;
                    return ErrSysInit;
                }
            }
            os::usleep(10000);
            tries++;
        }
        if (tries == totalTries)
        {
            printError(ErrLockTimeOut,"Unable to lock log file %d", ret);
            delete[] buffer;
            return -1;
        }        
        int bytesWritten = os::write(fdLog, buffer, strlen(buffer));
        if (bytesWritten != strlen(buffer))
        {
            printError(ErrSysInternal, "Unable to write log entry");
            ret = -1;
        }
        os::unlockFile(fdLog);
        delete[] buffer;
    }
    return ret;
}

DbRetVal Logger::startLogger(char *filename, bool isCreate)
{
    configLevel= (LogLevel) Conf::config.getLogLevel();
    if (LogOff == configLevel) return OK;
    char cmd[MAX_FILE_LEN];
    int ret =0;
    if (isCreate)
    {
       if (os::fileExists(filename)) {
          //move the existing log file with timestamp and create new file
          time_t cnow = ::time(NULL);
#ifdef SOLARIS
          struct std::tm *tmval = localtime(&cnow);
#else
          struct tm *tmval = localtime(&cnow);
#endif
          sprintf(cmd, "cp %s %s.%d-%d-%d:%d:%d:%d", filename, filename, 
                     tmval->tm_year+1900,
                     tmval->tm_mon+1, tmval->tm_mday, tmval->tm_hour, 
                     tmval->tm_min, tmval->tm_sec);
          ret = system(cmd);
          if (ret != 0) {
            printError(ErrWarning, "Unable to copy old log file");
          }
          os::truncate(filename);
       }
    }
    fdLog = os::open(filename, fileOpenAppend,0);
    if (fdLog == -1)
    {
        printError(ErrSysInit,"Unable to open log file");
        return ErrSysInit;
    }
    return OK;
}

void Logger::stopLogger()
{
    if (configLevel == 0) return ;
    os::close(fdLog);
}
