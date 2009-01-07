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
#ifndef DEBUG_H
#define DEBUG_H
#include<ErrorType.h>
//#define DEBUG 1
extern int DebugDM_Alloc;
extern int DebugDM_VarAlloc;
extern int DebugDM_Lock;
extern int DebugDM_Transaction;
extern int DebugDM_UndoLog;
extern int DebugDM_RedoLog;
extern int DebugDM_Index;
extern int DebugDM_HashIndex;
extern int DebugDM_TreeIndex;
extern int DebugDM_SystemDatabase;
extern int DebugDM_Database;
extern int DebugDM_Table;
extern int DebugDM_Predicate;
extern int DebugDM_Iterator;
extern int DebugDM_Process;
extern int DebugDM_Network;
extern int DebugDM_Gateway;
extern int DebugDM_Adapter;
extern int DebugDM_SqlLog;


extern int printError1(DbRetVal val, char* fname, int lno, char *format, ...);

#define printError(a, ...) printError1(a, __FILE__, __LINE__, __VA_ARGS__)

enum DebugModule
{
    DM_Alloc = 0,
    DM_VarAlloc,
    DM_Lock,
    DM_Transaction,
    DM_UndoLog,
    DM_RedoLog,
    DM_Index,
    DM_HashIndex,
    DM_TreeIndex,
    DM_SystemDatabase,
    DM_Database,
    DM_Table,
    DM_Predicate,
    DM_Iterator,
    DM_Process,
    DM_Network,
    DM_Gateway,
    DM_Adapter,
    DM_SqlLog
};
static char moduleNames[][20] =
{
    "Alloc", "VariableAlloc", "Lock", "Trans", "UndoLog", "RedoLog", "Index",
    "HashIndex", "TreeIndex", "SysDb", "Db", "Table", "Predicate", "Iter", 
    "Procmgmt", "Network", "Gateway", "Adapter", "SqlLog"
};

extern int printDebug1(int module, char *fname, int lineno, char *format, ...);


#ifdef DEBUG
#define printDebug(a, ...) printDebug1(a, __FILE__, __LINE__, __VA_ARGS__)
#else
#define printDebug(...) ;
#endif

//Logging

#define MAX_TRACE_LOG_LENGTH 1024

enum LogLevel
{
    LogOff = 0,
    LogFine,
    LogFiner,
    LogFinest
};

static char     levelNames[][10] =
{
     "OFF", "FINE", "FINER", "FINEST"
};
#include<Mutex.h>
class Logger
{
    Mutex mutex_; //guard in case of multi threaded programs
    int fdLog;  //file descriptor
    LogLevel configLevel;   //configuration file setting is cached here.
    public:
    int log(LogLevel level, char* filename, int lineNo, char *format, ...);
    int createLogRecord(LogLevel level, char* filename, int lineNo, char* message, char **in);
    DbRetVal startLogger(char *filename, bool isCreate = false);
    void stopLogger();
};

//Global object
static Logger logger;

#define logFinest(logger, ...) \
{\
  (logger).log(LogFinest, __FILE__, __LINE__, __VA_ARGS__);\
};

#define logFiner(logger, ...) \
{\
  (logger).log(LogFiner, __FILE__, __LINE__, __VA_ARGS__);\
};

#define logFine(logger, ...) \
{\
  (logger).log(LogFine, __FILE__, __LINE__, __VA_ARGS__);\
};


#endif
