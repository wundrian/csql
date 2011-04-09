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

int DebugDM_Alloc = 0;
int DebugDM_VarAlloc = 0;
int DebugDM_Lock = 0;
int DebugDM_Transaction = 0;
int DebugDM_UndoLog = 0;
int DebugDM_RedoLog = 0;
int DebugDM_Recovery = 0;
int DebugDM_Index = 0;
int DebugDM_HashIndex = 0;
int DebugDM_TreeIndex = 0;
int DebugDM_TrieIndex = 0;
int DebugDM_SystemDatabase = 0;
int DebugDM_Database = 0;
int DebugDM_Table = 0;
int DebugDM_Predicate = 0;
int DebugDM_TableIterator = 0;
int DebugDM_Process=0;
int DebugDM_Network=0;
int DebugDM_Gateway=0;
int DebugDM_Adapter=0;
int DebugDM_SqlLog=0;
int DebugDM_CacheServer=0;
int DebugDM_TEST=1;
int DebugDM_Warning=0;
int printStackTrace()
{
#ifdef LINUX
  void *array[10];
  size_t size = backtrace(array, 10);
  backtrace_symbols_fd(array, size, 2);
#endif
  return 0;
}

int printError1(DbRetVal val, char* fname, int lno, const char *format, ...)
{
    va_list ap;
    int fd = -1;
    char tempBuffer[25];
    struct timeval timeStamp;
    os::gettimeofday(&timeStamp);
    struct tm *tempTm = os::localtime(&timeStamp.tv_sec);
    char mesgBuf[1024];
#if defined(SOLARIS) && defined(REMOTE_SOLARIS)
    strftime(tempBuffer, 25, "%d/%m/%Y %H:%M:%S", (struct std::tm*) tempTm);
#else
    strftime(tempBuffer, 25, "%d/%m/%Y %H:%M:%S", tempTm);
#endif

    if (strncasecmp(Conf::config.getStderrFile(),"stderr", 6) == 0) fd = 2;
    else { 
        fd = os::openFileForAppend(Conf::config.getStderrFile(), O_CREAT);
        if (fd == -1) fd = 2;
    }

    snprintf(mesgBuf, MAX_TRACE_LOG_LENGTH, "%s.%6d:%5d:%10lu:%s:%d:",
         tempBuffer, timeStamp.tv_usec, os::getpid(), os::getthrid(), fname, lno);

    os::write(fd, mesgBuf, strlen(mesgBuf));
  
    va_start(ap, format);

    int err = ::vsnprintf(mesgBuf, sizeof(mesgBuf), format,ap);
    if (err < 0) { return err; } 
       
    os::write(fd, mesgBuf, strlen(mesgBuf));
    strcpy(mesgBuf,"\n");
    os::write(fd, mesgBuf, strlen(mesgBuf));
    //2->stderr
    return 0;
}

int printDebug1(int module, char *fname, int lno, const char *format, ...)
{
  switch(module) {
     case DM_Alloc: { if (!DebugDM_Alloc) return 1; break; }
     case DM_VarAlloc: { if (!DebugDM_VarAlloc) return 1; break; }
     case DM_Lock: { if (!DebugDM_Lock) return 1; break; }
     case DM_Transaction: { if (!DebugDM_Transaction) return 1; break; }
     case DM_UndoLog: { if (!DebugDM_UndoLog) return 1; break; }
     case DM_RedoLog: { if (!DebugDM_RedoLog) return 1; break; }
     case DM_Recovery: { if (!DebugDM_Recovery) return 1; break; }
     case DM_HashIndex: { if (!DebugDM_HashIndex) return 1; break; }
     case DM_TrieIndex: { if (!DebugDM_TrieIndex) return 1; break; }
     case DM_TreeIndex: { if (!DebugDM_TreeIndex) return 1; break; }
     case DM_SystemDatabase: { if (!DebugDM_SystemDatabase) return 1; break; }
     case DM_Database: { if (!DebugDM_Database) return 1; break; }
     case DM_Table: { if (!DebugDM_Table) return 1; break; }
     case DM_Iterator: { if (!DebugDM_TableIterator) return 1; break; }
     case DM_Predicate: { if (!DebugDM_Predicate) return 1; break; }
     case DM_Process: { if (!DebugDM_Process) return 1; break; }
     case DM_Network: { if (!DebugDM_Network) return 1; break; }
     case DM_Gateway: { if (!DebugDM_Gateway) return 1; break; }
     case DM_Adapter: { if (!DebugDM_Adapter) return 1; break; }
     case DM_SqlLog: { if (!DebugDM_SqlLog) return 1; break; }
     case DM_CacheServer: { if (!DebugDM_CacheServer) return 1; break; }
     case DM_TEST: { if (!DebugDM_TEST) return 1; break; }
     case DM_Warning: { if (!DebugDM_Warning) return 1; break; }

  }

  va_list ap;
  char mesgBuf[1024];

  sprintf(mesgBuf, "D:%s:%d:%lu:%s:%d:", moduleNames[module],
           os::getpid(), os::getthrid(), fname, lno);
  os::write(1, mesgBuf, strlen(mesgBuf));

  va_start(ap, format);

  int err = ::vsnprintf(mesgBuf, sizeof(mesgBuf), format,ap);
  if(err < 0) {
      return err;
  }
  os::write(1, mesgBuf, strlen(mesgBuf));
  strcpy(mesgBuf,"\n");
  os::write(1, mesgBuf, strlen(mesgBuf));
   //1->stdout
  return 0;
}
