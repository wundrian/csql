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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <os.h>
#include <SqlLogConnection.h>
#include <CSql.h>

FileSend::FileSend()
{
    fdRedoLog = -1;
    fdStmtLog = -1;
    openRedoFile();
}
DbRetVal FileSend::openRedoFile()
{
    if (fdRedoLog > 0) os::closeFile(fdRedoLog); 
    if (fdStmtLog > 0) os::closeFile(fdStmtLog); 
    char fileName[MAX_FILE_LEN];
    char stmtFileName[MAX_FILE_LEN];
    sprintf(fileName, "%s/csql.db.cur", Conf::config.getDbFile());
    sprintf(stmtFileName, "%s/csql.db.stmt", Conf::config.getDbFile());
    int durableMode = Conf::config.getDurableMode();
    switch(durableMode) {
        case 1:
        case 2:
            fdRedoLog = os::openFileForAppend(fileName, O_CREAT);
            fdStmtLog = os::openFileForAppend(stmtFileName, O_CREAT);
            break;
        case 3:
            fdRedoLog = os::openFileForAppend(fileName, O_CREAT|O_SYNC);
            fdStmtLog = os::openFileForAppend(stmtFileName, O_CREAT|O_SYNC);
            break;
        case 4:
#ifdef SOLARIS
            fdRedoLog = os::openFileForAppend(fileName, O_CREAT|O_DSYNC);
            fdStmtLog = os::openFileForAppend(stmtFileName, O_CREAT|O_DSYNC);
#else
            fdRedoLog = os::openFileForAppend(fileName, O_CREAT|O_DIRECT);
            fdStmtLog = os::openFileForAppend(stmtFileName, O_CREAT|O_DIRECT);
#endif
            break;
        default:
            fdRedoLog = os::openFileForAppend(fileName, O_CREAT);
            fdStmtLog = os::openFileForAppend(stmtFileName, O_CREAT);
            break;
    }
    if (-1 == fdRedoLog || -1 == fdStmtLog) {
        printError(ErrSysInternal, "Unable to open redo log file");
        return ErrSysInternal;
    }
    return OK;
}

FileSend::~FileSend() { 
    if (fdRedoLog > 0) os::closeFile(fdRedoLog); 
    if (fdStmtLog > 0) os::closeFile(fdStmtLog); 
    fdRedoLog = -1; 
    fdStmtLog = -1;
}

DbRetVal FileSend::prepare(int txnId, int stmtId, int len, char *stmt, 
                           char *tblName, bool hasParam) 
{
    if (fdRedoLog < 0) {
       printError(ErrBadArg, "Redo Log file not opened");
       return ErrBadArg;
    }
    if (fdStmtLog < 0) {
       printError(ErrBadArg, "Redo Stmt Log file not opened");
       return ErrBadArg;
    }
    int fd =fdRedoLog;
    if (hasParam) fd=fdStmtLog;
    //The following structure needs strlen after stmt id for traversal in 
    //redolog file unlike msg queue structure where string is the last element 
    //and is not a continuous piece of memory.
    int datalen = os::align(5 * sizeof(int) + len); // for len + txnId + msg type + stmtId + tableName + stmtstrlen + stmtstring
    char *buf = (char*) malloc(datalen);
    char *msg = buf;
    //Note:: msg type is taken as -ve as we need to differentiate between 
    //statement id and logtype during recovery.
    *(int*) msg = -1;
    if (strlen(stmt) > 6 && ( strncasecmp(stmt,"CREATE", 6) == 0 || strncasecmp(stmt,"DROP", 4) == 0 ))
        *(int*)msg = -4; //means prepare and execute the stmt
    msg = msg+sizeof(int);
    *(int *)msg = datalen;
    msg = msg+sizeof(int);
    *(int *)msg = txnId;
    msg = msg+sizeof(int);
    *(int *)msg = stmtId;
    msg = msg+ sizeof(int);
    *(int *)msg = os::align(len);
    msg = msg+ sizeof(int);
    msg[len-1] = '\0';
    strcpy(msg, stmt);
    int ret =0;
    bool firstTime=true;
retry:
    if (Conf::config.getDurableMode() != 1) {
        ret = os::lockFile(fd);
        if (-1 == ret) {
            ::free(buf);
            printError(ErrLockTimeOut,"Unable to get exclusive lock on redo log file");
            return ErrLockTimeOut;
        }
    }
    ret = os::write(fd, buf, datalen);     
    if (Conf::config.getDurableMode() != 1) {
        os::unlockFile(fd); 
    }
    if (-1 == ret) { 
        DbRetVal rv = openRedoFile();
        if (hasParam) fd=fdStmtLog; else fd=fdRedoLog;
        if (OK == rv) {
            logFine(Conf::logger, "Reopening redo log file");
            if(firstTime) { firstTime = false; goto retry; }
        }
        printError(ErrOS, "Unable to write undo log");
        ::free(buf);
        return ErrOS; 
    }
    ::free(buf);
    return OK;
};

DbRetVal FileSend::commit(int len, void *data)
{
    if (fdRedoLog < 0) {
       printError(ErrBadArg, "Redo Log file not opened");
       return ErrBadArg;
    }
    char *dat=(char*)data - sizeof(int);
    *(int*)dat = -2; //type 2->commit
    bool firstTime = true;
retry:
    if (Conf::config.getDurableMode() != 1) {
        int ret = os::lockFile(fdRedoLog);
        if (-1 == ret) {
            printError(ErrLockTimeOut,"Unable to get exclusive lock on redo log file");
            return ErrLockTimeOut;
        }
    }
    int ret = os::write(fdRedoLog, dat, len+sizeof(int));     
    if (Conf::config.getDurableMode() != 1) {
        os::unlockFile(fdRedoLog); 
    }
    if (-1 == ret) {
        DbRetVal rv = openRedoFile();
        if (OK == rv) {
            logFine(Conf::logger, "Reopening redo log file");
            if(firstTime) { firstTime = false; goto retry; }
        }
        printError(ErrOS, "Unable to write undo log");
        return ErrOS;
    }
    return OK;
}
DbRetVal FileSend::free(int txnId, int stmtId, bool hasParam)
{
    if (fdRedoLog < 0) {
       printError(ErrBadArg, "Redo Log file not opened");
       return ErrBadArg;
    }
    if (fdStmtLog < 0) {
       printError(ErrBadArg, "Redo Stmt Log file not opened");
       return ErrBadArg;
    }
    int fd =fdRedoLog;
    int buflen =  4 *sizeof(int);
    char *msg = (char *) malloc(buflen);
    char *ptr = msg;
    *(int*)ptr = -3;
    ptr += sizeof(int);
    *(int *)ptr = 3 * sizeof(int); // for len + txnId + stmtId
    ptr += sizeof(int);
    *(int *)ptr = txnId;
    ptr += sizeof(int);
    *(int *)ptr = stmtId;
    printDebug(DM_SqlLog, "stmtID sent = %d\n", *(int *)ptr);
    bool firstTime = true;
retry:
    if (Conf::config.getDurableMode() != 1) {
        int ret = os::lockFile(fd);
        if (-1 == ret) {
            ::free(msg);
            printError(ErrLockTimeOut,"Unable to get exclusive lock on redo log file");
            return ErrLockTimeOut;
        }
    }
    int ret = os::write(fd, msg, buflen);
    if (Conf::config.getDurableMode() != 1) {
        os::unlockFile(fd); 
    }
    if (-1 == ret) {
        DbRetVal rv = openRedoFile();
        if (hasParam) fd=fdStmtLog; else fd=fdRedoLog;
        if (OK == rv) {
            logFine(Conf::logger, "Reopening redo log file");
            if(firstTime) { firstTime = false; goto retry; }
        }
        printError(ErrOS, "Unable to write undo log");
        ::free(msg);
        return ErrOS;
    }
    if (!hasParam) {
        //For non parameterized stmts , no need to write in stmt log
        ::free(msg);
        return OK;
    }
    fd=fdStmtLog;
retry1:
    if (Conf::config.getDurableMode() != 1) {
        int ret = os::lockFile(fd);
        if (-1 == ret) {
            ::free(msg);
            printError(ErrLockTimeOut,"Unable to get exclusive lock on redo log file");
            return ErrLockTimeOut;
        }
    }

    ret = os::write(fd, msg, buflen);
    if (Conf::config.getDurableMode() != 1) {
        os::unlockFile(fd); 
    }
    if (-1 == ret) {
        DbRetVal rv = openRedoFile();
        if (OK == rv) {
            logFine(Conf::logger, "Reopening redo log file");
            if(firstTime) { firstTime = false; goto retry1; }
        }
        printError(ErrOS, "Unable to write undo log");
        ::free(msg);
        return ErrOS;
    }
    ::free(msg);
    return OK;
}

OfflineLog::OfflineLog()
{
    fdOfflineLog = -1; 
    metadata = NULL;
    createMetadataFile();   
    openOfflineLogFile();
}

DbRetVal OfflineLog::openOfflineLogFile()
{
    char fileName[MAX_FILE_LEN];
    int offlineLogFileSize = Conf::config.getOfflineLogFileSize();
    fileSize = 0;
    if (metadata == NULL) {
        metadata = openMetadataFile();
        if (metadata == NULL) {
            printError(ErrOS, "Unable to open Metadata file");
            return ErrOS;
        }
    }
    char *ptr = (char *) metadata;
    sprintf(fileName, "%s/offlineLogFile.%d", 
                                        Conf::config.getDbFile(), *(int *)ptr);
    int ret = 0;
    if ( ((ret = ::access(fileName, F_OK)) == 0) &&  
              ((fileSize = os::getFileSize(fileName)) >= offlineLogFileSize) ) 
        sprintf(fileName, "%s/offlineLogFile.%d",
                                    Conf::config.getDbFile(), ++(*(int *)ptr)); 
    else if (ret == 0) 
        sprintf(fileName, "%s/offlineLogFile.%d", Conf::config.getDbFile(), 
                                                                  *(int *)ptr); 
    else {
        sprintf(fileName, "%s/offlineLogFile.0", Conf::config.getDbFile());
        *(int *) ptr = 0;
    }
    int durableMode = Conf::config.getDurableMode();
    switch(durableMode) {
        case 1:
        case 2:
            fdOfflineLog = os::openFileForAppend(fileName, O_CREAT);
            break;
        case 3:
            fdOfflineLog = os::openFileForAppend(fileName, O_CREAT|O_SYNC);
            break;
        case 4:
#ifdef SOLARIS
            fdOfflineLog = os::openFileForAppend(fileName, O_CREAT|O_DSYNC);
#else
            fdOfflineLog = os::openFileForAppend(fileName, O_CREAT|O_DIRECT);
#endif
            break;
        default:
            fdOfflineLog = os::openFileForAppend(fileName, O_CREAT);
            break;
    }
    if (-1 == fdOfflineLog) {
        printError(ErrSysInternal, "Unable to open redo log file");
        return ErrSysInternal;
    }
    ret = msync(metadata, sizeof(int), MS_SYNC);
    if (ret) {
        printError(ErrOS, "Unable to sync file index to metadata file.");
        return ErrOS;
    }
    return OK;
}

OfflineLog::~OfflineLog() 
{ 
    if (fdOfflineLog > 0) os::closeFile(fdOfflineLog); 
    fdOfflineLog = -1; 
}

DbRetVal OfflineLog::prepare(int txnId, int stId, int len, char *stmt, 
                             char*tn, bool hasParam)
{
    if (fdOfflineLog < 0) return ErrBadArg;
    DbRetVal rv = OK;
    if (fileSize > Conf::config.getOfflineLogFileSize())
    {
        rv = openOfflineLogFile();
        if (rv != OK) return rv;
    }
    //The following structure needs strlen after stmt id for traversal in 
    //redolog file unlike msg queue structure where string is the last element 
    //and is not a continuous piece of memory.
    int datalen = os::align(5 * sizeof(int) + len); // for len + txnId + msg type + stmtId + tableName + stmtstrlen + stmtstring
    char *buf = (char*) malloc(datalen);
    char *msg = buf;
    //Note:: msg type is taken as -ve as we need to differentiate between 
    //statement id and logtype during recovery.
    *(int*) msg = -1;
    if (strlen(stmt) > 6 && ( strncasecmp(stmt,"CREATE", 6) == 0 || strncasecmp(stmt,"DROP", 4) == 0 ))
        *(int*)msg = -4; //means prepare and execute the stmt
    msg = msg+sizeof(int);
    *(int *)msg = datalen;
    msg = msg+sizeof(int);
    *(int *)msg = txnId;
    msg = msg+sizeof(int);
    *(int *)msg = stId;
    msg = msg+ sizeof(int);
    *(int *)msg = os::align(len);
    msg = msg+ sizeof(int);
    msg[len-1] = '\0';
    strcpy(msg, stmt);
    int ret =0;
    bool firstTime=true;
retry:
    if (Conf::config.getDurableMode() != 1) {
        ret = os::lockFile(fdOfflineLog);
        if (-1 == ret) {
            ::free(buf);
            printError(ErrLockTimeOut,"Unable to get exclusive lock on redo log file");
            return ErrLockTimeOut;
        }
    }
    ret = os::write(fdOfflineLog, buf, datalen);
    if (Conf::config.getDurableMode() != 1) {
        os::unlockFile(fdOfflineLog);
    }
    if (-1 == ret) {
        DbRetVal rv = openOfflineLogFile();
        if (OK == rv) {
            logFine(Conf::logger, "Reopening redo log file");
            if(firstTime) { firstTime = false; goto retry; }
        }
        printError(ErrOS, "Unable to write undo log");
        ::free(buf);
        return ErrOS;
    }
    ::free(buf);
    fileSize += datalen;
    return OK;
}
DbRetVal OfflineLog::commit(int len, void *data)
{
    if (fdOfflineLog < 0) return ErrBadArg;
    DbRetVal rv = OK;
    if (fileSize > Conf::config.getOfflineLogFileSize())
    {
        rv = openOfflineLogFile();
        if (rv != OK) return rv;
    }
    char *dat=(char*)data - sizeof(int);
    *(int*)dat = -2; //type 2->commit
    bool firstTime = true;
retry:
    if (Conf::config.getDurableMode() != 1) {
        int ret = os::lockFile(fdOfflineLog);
        if (-1 == ret) {
            printError(ErrLockTimeOut,"Unable to get exclusive lock on redo log file");
            return ErrLockTimeOut;
        }
    }
    int ret = os::write(fdOfflineLog, dat, len+sizeof(int));
    if (Conf::config.getDurableMode() != 1) {
        os::unlockFile(fdOfflineLog);
    }
    if (-1 == ret) {
        DbRetVal rv = openOfflineLogFile();
        if (OK == rv) {
            logFine(Conf::logger, "Reopening redo log file");
            if(firstTime) { firstTime = false; goto retry; }
        }
        printError(ErrOS, "Unable to write undo log");
        return ErrOS;
    }
    fileSize += len+sizeof(int);
    return OK;
}
DbRetVal OfflineLog::free(int txnId, int stId, bool hasParam)
{
    if (fdOfflineLog < 0) return ErrBadArg;
    DbRetVal rv = OK;
    if (fileSize > Conf::config.getOfflineLogFileSize())
    {
        rv = openOfflineLogFile();
        if (rv != OK) return rv;
    }
    int buflen =  4 *sizeof(int);
    char *msg = (char *) malloc(buflen);
    char *ptr = msg;
    *(int*)ptr = -3;
    ptr += sizeof(int);
    *(int *)ptr = 3 * sizeof(int); // for len + txnId + stmtId
    ptr += sizeof(int);
    *(int *)ptr = txnId;
    ptr += sizeof(int);
    *(int *)ptr = stId;
    printDebug(DM_SqlLog, "stmtID sent = %d\n", *(int *)ptr);
    bool firstTime = false;
retry:
    if (Conf::config.getDurableMode() != 1) {
        int ret = os::lockFile(fdOfflineLog);
        if (-1 == ret) {
            ::free(msg);
            printError(ErrLockTimeOut,"Unable to get exclusive lock on redo log file");
            return ErrLockTimeOut;
        }
    }
    int ret = os::write(fdOfflineLog, msg, buflen);
    if (Conf::config.getDurableMode() != 1) {
        os::unlockFile(fdOfflineLog);
    }
    if (-1 == ret) {
        DbRetVal rv = openOfflineLogFile();
        if (OK == rv) {
            logFine(Conf::logger, "Reopening redo log file");
            if(firstTime) { firstTime = false; goto retry; }
        }
        printError(ErrOS, "Unable to write undo log");
        ::free(msg);
        return ErrOS;
    }
    ::free(msg);
    fileSize += buflen;
    return OK;
}

DbRetVal OfflineLog::createMetadataFile()
{
    int fd = -1;
    char mmapFile[128];
    sprintf(mmapFile, "%s/offlineLogFile.dat", Conf::config.getDbFile());
    int size = sizeof(int); 
    // int for offlineLogFile index + long for committed TxnID
    char buffer[size];
    if (::access(mmapFile, F_OK) == 0) return OK;
    else {
        fd = ::open(mmapFile, O_CREAT | O_RDWR, 0664);
        if (fd == -1) {
            printError(ErrOS, "Unable to create '%s'file to mmap", mmapFile);
            return ErrOS;
        }
        memset(buffer, 0, size);
        int sz = ::write(fd, buffer, size);
        if (sz != size) {
            printError(ErrOS, "Unable to initialize mmap file %s", mmapFile);
            return ErrOS;
        }
        ::close(fd);
    }
    return OK;
}

void *OfflineLog::openMetadataFile() 
{
    char mmapFile[128];
    int size = sizeof(int) + sizeof(long);
    sprintf(mmapFile, "%s/offlineLogFile.dat", Conf::config.getDbFile());
    int fd = ::open(mmapFile, O_RDWR, 0666);
    if (fd == -1) {
        printError(ErrOS, "Unable to open Mmap file %s", mmapFile);
        return NULL;
    }
    metadata = os::mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (metadata == NULL) {
        printError(ErrOS, "Unable to map the file %s to memory", mmapFile);
        return NULL;
    }
    return metadata;
}
