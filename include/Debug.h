/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
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
extern int DebugDM_CacheServer;
extern int DebugDM_TEST;
extern int DebugDM_Warning;

int printStackTrace();
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
    DM_SqlLog,
    DM_CacheServer,
    DM_TEST,
    DM_Warning
};
static char moduleNames[][20] =
{
    "Alloc", "VariableAlloc", "Lock", "Trans", "UndoLog", "RedoLog", "Index",
    "HashIndex", "TreeIndex", "SysDb", "Db", "Table", "Predicate", "Iter", 
    "Procmgmt", "Network", "Gateway", "Adapter", "SqlLog",
    "CacheServer", "TEST", "Warning"
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
    int fdLog;  //file descriptor
    LogLevel configLevel;   //configuration file setting is cached here.
    void rollOverIfRequired();
    public:
    int log(LogLevel level, char* filename, int lineNo, char *format, ...);
    int createLogRecord(LogLevel level, char* filename, int lineNo, char* message, char **in);
    DbRetVal startLogger(char *filename, bool isCreate = false);
    void stopLogger();
};

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
