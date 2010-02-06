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
    openRedoFile();
}
DbRetVal FileSend::openRedoFile()
{
    char fileName[MAX_FILE_LEN];
    sprintf(fileName, "%s/csql.db.cur", Conf::config.getDbFile());
    int durableMode = Conf::config.getDurableMode();
    switch(durableMode) {
        case 1:
        case 2:
            fdRedoLog = os::openFileForAppend(fileName, O_CREAT);
            break;
        case 3:
            fdRedoLog = os::openFileForAppend(fileName, O_CREAT|O_SYNC);
            break;
        case 4:
#ifdef SOLARIS
            fdRedoLog = os::openFileForAppend(fileName, O_CREAT|O_DSYNC);
#else
            fdRedoLog = os::openFileForAppend(fileName, O_CREAT|O_DIRECT);
#endif
            break;
        default:
            fdRedoLog = os::openFileForAppend(fileName, O_CREAT);
            break;
    }
    if (-1 == fdRedoLog) {
        printError(ErrSysInternal, "Unable to open redo log file");
        return ErrSysInternal;
    }
    return OK;
}

FileSend::~FileSend() 
{ 
    if (fdRedoLog > 0) os::closeFile(fdRedoLog); 
    fdRedoLog = -1; 
}

DbRetVal FileSend::prepare(int txnId, int stmtId, int len, char *stmt, char *tblName) 
{
    if (fdRedoLog < 0) return ErrBadArg;
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
        ret = os::lockFile(fdRedoLog);
        if (-1 == ret) {
            ::free(buf);
            printError(ErrLockTimeOut,"Unable to get exclusive lock on redo log file");
            return ErrLockTimeOut;
        }
    }
    ret = os::write(fdRedoLog, buf, datalen);     
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
        ::free(buf);
        return ErrOS; 
    }
    ::free(buf);
    return OK;
};

DbRetVal FileSend::commit(int len, void *data)
{
    if (fdRedoLog < 0) return ErrBadArg;
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
DbRetVal FileSend::free(int txnId, int stmtId)
{
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
    bool firstTime = false;
retry:
    if (Conf::config.getDurableMode() != 1) {
        int ret = os::lockFile(fdRedoLog);
        if (-1 == ret) {
            ::free(msg);
            printError(ErrLockTimeOut,"Unable to get exclusive lock on redo log file");
            return ErrLockTimeOut;
        }
    }
    int ret = os::write(fdRedoLog, msg, buflen);
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
        ::free(msg);
        return ErrOS;
    }
    ::free(msg);
    return OK;
}
OfflineLog::OfflineLog()
{
    openOfflineLogFile();
}
DbRetVal OfflineLog::openOfflineLogFile()
{
    char fileName[MAX_FILE_LEN];
    int fileCounter = 0;
    int fileSize = 0;
    createMmapFileForMetadata();   
    int offlineLogFileSize = Conf::config.getOfflineLogFileSize();
    sprintf(fileName, "%s/offlineLogFile.%d", 
                                        Conf::config.getDbFile(), fileCounter);
    while (true) {
        if ((::access(fileName, F_OK) == 0) && 
                (fileSize = os::getFileSize(fileName)) >= offlineLogFileSize) { 
            fileCounter++;
            sprintf(fileName, "%s/offlineLogFile.%d", 
                                        Conf::config.getDbFile(), fileCounter); 
        } else break;
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
    return OK;
}

OfflineLog::~OfflineLog() 
{ 
    if (fdOfflineLog > 0) os::closeFile(fdOfflineLog); 
    fdOfflineLog = -1; 
}

DbRetVal OfflineLog::prepare(int txnId, int stId, int len, char *stmt, char*tn)
{
    if (fdOfflineLog < 0) return ErrBadArg;
    //The following structure needs strlen after stmt id for traversal in 
    //redolog file unlike msg queue structure where string is the last element 
    //and is not a continuous piece of memory.
    // for len + txnId + msg type + stmtId + tableName + stmtstrlen + 
    // stmtstring
    int datalen = os::align(5 * sizeof(int) + len); 
    char *buf = (char*) malloc(datalen);
    char *msg = buf;
    //Note:: msg type is taken as -ve as we need to differentiate between 
    //statement id and logtype during recovery.
    *(int*) msg = -1;
    if (strlen(stmt) > 6 && ( strncasecmp(stmt,"CREATE", 6) == 0 || 
                                            strncasecmp(stmt,"DROP", 4) == 0 ))
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
            printError(ErrLockTimeOut,
                              "Unable to get exclusive lock on redo log file");
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
    return OK;
}

DbRetVal OfflineLog::commit(int len, void *data)
{
    if (fdOfflineLog < 0) return ErrBadArg;
    char *dat=(char*)data - sizeof(int);
    *(int*)dat = -2; //type 2->commit
    bool firstTime = true;
retry:
    if (Conf::config.getDurableMode() != 1) {
        int ret = os::lockFile(fdOfflineLog);
        if (-1 == ret) {
            printError(ErrLockTimeOut,
                             "Unable to get exclusive lock on redo log file");
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
    return OK;
}

DbRetVal OfflineLog::free(int txnId, int stId)
{
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
            printError(ErrLockTimeOut,
                             "Unable to get exclusive lock on redo log file");
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
    return OK;
}

DbRetVal OfflineLog::createMmapFileForMetadata()
{
    int fd = -1;
    char mmapFile[128];
    sprintf(mmapFile, "%s/offlineLogFile.dat", Conf::config.getDbFile());
    int size = sizeof(int) + sizeof(long); 
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


