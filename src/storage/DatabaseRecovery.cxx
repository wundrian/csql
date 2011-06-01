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
#include<Database.h>
#include<os.h>
#include<CatalogTables.h>
#include<Transaction.h>
#include<Lock.h>
#include<Debug.h>
#include<Config.h>
#include<Process.h>
#include<HeapAllocator.h>

DbRetVal Database::writeDirtyPages(char *dataFile)
{
    int fd = os::open(dataFile, fileOpenCreat, 0);
    os::lseek(fd, 0, SEEK_SET);
    void *buf = (void *) metaData_;
    int sizeToWrite = os::alignLong(sizeof(DatabaseMetaData));
    size_t retSize = os::write(fd, (char*)buf, sizeToWrite);
    if (-1 == retSize)
    {
       printError(ErrWarning, "Warning:Unable to write metadata");
       return ErrSysInternal;
    }
    PageInfo *pageInfo = (PageInfo*) getFirstPage();
    long pageSize =PAGE_SIZE;
    int pagesWritten=0, writeOffset=0;
    long long totalBytesWritten=0;
    while(isValidAddress((char*) pageInfo))
    {
        if ( NULL == pageInfo ) break;
        if (pageInfo > getCurrentPage()) {
           char *a="0";
           os::lseek(fd, getMaxSize() -1, SEEK_SET);
           if ( -1 == os::write(fd, a, 1)) {
               printError(ErrSysInternal, "Unable to extend chkpt file");
               os::close(fd);
               return ErrSysInternal;
           }
           break;
        }
        if (BITSET(pageInfo->flags, IS_DIRTY)) {
            if (NULL == pageInfo->nextPageAfterMerge_)
                pageSize = PAGE_SIZE;
            else
                pageSize = (long)pageInfo->nextPageAfterMerge_ - (long)pageInfo;
            writeOffset = (long) pageInfo - (long) metaData_;
            ::lseek(fd, writeOffset, SEEK_SET);
            CLEARBIT(pageInfo->flags, IS_DIRTY);
            retSize = os::write(fd, (char*)pageInfo, pageSize);
            if ( -1  == retSize ) {
                printError(ErrSysInternal, "Unable to write dirty page %x", pageInfo);
                os::close(fd);
                return ErrSysInternal;
            }
            totalBytesWritten= totalBytesWritten + retSize;
            pagesWritten++;
        }
        if ( pageInfo->nextPageAfterMerge_ == NULL) {
           pageInfo = (PageInfo*)((char*)pageInfo + PAGE_SIZE);
        } else {
           pageInfo = (PageInfo*)pageInfo->nextPageAfterMerge_;
        }
    }
    //printf("Total Dirty pages written %d %lld\n", pagesWritten, totalBytesWritten);
    logFine(Conf::logger, "Total Dirty pages written %d\n", pagesWritten);
    os::close(fd);
    return OK;
}

DbRetVal Database::checkPoint()
{
    char dataFile[MAX_FILE_LEN];
    char cmd[MAX_FILE_LEN];
    char dbRedoFileName[MAX_FILE_LEN];
    sprintf(dbRedoFileName, "%s/csql.db.cur", Conf::config.getDbFile());
    if (!Conf::config.useMmap()) {
       // sprintf(dataFile, "%s/db.chkpt.data1", Conf::config.getDbFile());
        sprintf(dataFile, "%s/db.chkpt.data", Conf::config.getDbFile());
        FILE *fp = NULL;
        if (fp = fopen(dataFile, "r")) {
            fclose(fp);
            int ret = ::unlink(dataFile);
            if (ret != OK) {
                printError(ErrOS, "Unable to delete old chkpt file. Failure");
                return ErrOS;
            }
        }
        int fd = ::open(dataFile, O_WRONLY|O_CREAT, 0644);
        void *buf = (void *) metaData_;
        os::lseek(fd, 0, SEEK_SET);
        os::write(fd, (char*) buf, Conf::config.getMaxDbSize());
        os::close(fd);  
        sprintf(cmd, "cp -f %s/db.chkpt.data %s/db.chkpt.data1", Conf::config.getDbFile(), Conf::config.getDbFile());
        int ret = system(cmd);
        if (ret != 0) {
            printError(ErrOS, "Unable to take checkpoint back up file");
            return ErrOS;
        }
    } else {
        file_desc fd = getChkptfd();
        if (!os::fdatasync(fd)) { 
            logFine(Conf::logger, "fsync succedded"); 
        }
        filterAndRemoveStmtLogs();
        int ret = os::truncate(dbRedoFileName);
        if (ret != 0) {
            os::closeFile(fd);  
            printError(ErrSysInternal, "Unable to truncate redo log file");
            printError(ErrSysInternal, "Delete %s manually and restart the server", dbRedoFileName);
            return ErrOS;
        }
        //switch the checkpoint so that during recovery, fsynced checkpoint is
        //used during recovery if the below step(writeDirtyPages)
        //is not completed succesfully.
        if (Database::getCheckpointID() == 0)
            Database::setCheckpointID(1);
        else
            Database::setCheckpointID(0);

        int val=Database::getCheckpointID();

        sprintf(dataFile, "%s/db.chkpt.data%d", Conf::config.getDbFile(), val);
        DbRetVal rv = writeDirtyPages(dataFile);
        if (OK != rv)
        {
            printError(ErrSysInternal, "Unable to write dirty pages");
            os::closeFile(fd);  
            return rv;
        }

        //Note: do not change order, chkpt id should be switched only after 
        //all dirty pages are written to disk. otherwise(if server crashes
        //when it writes these dirty pages) recovery should use
        //mapped file as fsync is already done on that file.
        if (Database::getCheckpointID() == 0)
            Database::setCheckpointID(1);
        else
            Database::setCheckpointID(0);

        os::closeFile(fd);  
        return OK;
    }
    filterAndRemoveStmtLogs();
    int ret = os::truncate(dbRedoFileName);
    if (ret != 0) {
        printError(ErrSysInternal, "Unable to truncate redo log file. Delete and restart the server\n");
       return ErrOS;
    }
    return OK;
}
DbRetVal Database::filterAndRemoveStmtLogs()
{
    struct stat st;
    char fName[MAX_FILE_LEN];
    sprintf(fName, "%s/csql.db.stmt", Conf::config.getDbFile());
    file_desc fdRead = os::openFile(fName, fileOpenReadOnly,0);
    if ((file_desc)-1 == fdRead) { return OK; }
    if (::stat(fName, &st) == -1) {
        printError(ErrSysInternal, "Unable to retrieve stmt log file size");
        os::closeFile(fdRead);
        return ErrSysInternal;
    }
    if (st.st_size ==0) {
        os::closeFile(fdRead);
        return OK;
    }
   void *startAddr = os::mmap(NULL, st.st_size, mapProtRead, mapPrivate, fdRead, 0);
    if ((void*) MAP_FAILED == startAddr) {
        printError(ErrSysInternal, "Unable to mmap stmt log file\n");
        return ErrSysInternal;
    }
    sprintf(fName, "%s/csql.db.stmt1", Conf::config.getDbFile());
    int fd = os::openFileForAppend(fName, O_CREAT|O_TRUNC);
    char *iter = (char*)startAddr;
    char *logStart = NULL, *logEnd = NULL;
    int logType;
    int stmtID;
    int len =0, ret =0;
    int txnID, loglen;
    DbRetVal rv = OK;
    HashMap stmtMap;
    stmtMap.setKeySize(sizeof(int));
    //PASS-I load all prepare stmts and free them 
    while(true) {
        if (iter - (char*)startAddr >= st.st_size) break;
        logType = *(int*)iter;
        logStart = iter;
        if (logType == -1) { //prepare
            iter = iter + sizeof(int);
            len = *(int*) iter;
            iter = iter + 2 * sizeof(int);
            stmtID = *(int*)iter;
            stmtMap.insert(iter);
            iter = logStart+ len;
            ret =0;
        }
        else if(logType == -3) { //free
            iter = iter + sizeof(int);
            txnID = *(int*) iter; iter += sizeof(int);
            loglen = *(int*) iter; iter += sizeof(int);
            stmtID = *(int*)iter;
            stmtMap.remove(iter);
            iter = iter + sizeof(int);
        }else{
            printError(ErrSysInternal, "Stmt Redo log file corrupted: logType:%d", logType);
            rv = ErrSysInternal;
            break;
        }
    }
    //PASS-II take the prepared statements which are not freed into another backup file
    while(true) {
        if (iter - (char*)startAddr >= st.st_size) break;
        logType = *(int*)iter;
        logStart = iter;
        if (logType == -1) { //prepare
            iter = iter + sizeof(int);
            len = *(int*) iter;
            iter = iter + 2 * sizeof(int);
            stmtID = *(int*)iter;
            iter = logStart+ len;
            ret =0;
            if (stmtMap.find(&stmtID))
                ret = os::write(fd, logStart, len);
            if (-1 == ret) {
                printError(ErrSysInternal, "Unable to write statement logs");
            }
        }
        else if(logType == -3) { //free
            iter = logStart + 4 *sizeof(int);
            //neglet free stmt logs in this pass
        }else{
            printError(ErrSysInternal, "Stmt Redo log file corrupted: logType:%d", logType);
            rv = ErrSysInternal;
            break;
        }
    }

    os::close(fd);
    os::munmap((char*)startAddr, st.st_size);
    os::closeFile(fdRead);
    stmtMap.removeAll();
    char cmd[MAX_FILE_LEN *2];
    sprintf(cmd, "mv %s/csql.db.stmt1 %s/csql.db.stmt",
                  Conf::config.getDbFile(), Conf::config.getDbFile());
    ret = system(cmd);
    return rv;
}
int Database::getCheckpointID()
{
    int id=0;
    char curCkptFile[MAX_FILE_LEN];
    sprintf(curCkptFile, "%s/db.chkpt.cur", Conf::config.getDbFile());
    FILE *fp = fopen(curCkptFile, "r");
    if (NULL == fp) { setCheckpointID(0); return 0; }
    fscanf(fp, "%d", &id);
    fclose(fp);
    return id;
}
void Database::setCheckpointID(int id)
{
    char curCkptFile[MAX_FILE_LEN];
    sprintf(curCkptFile, "%s/db.chkpt.cur", Conf::config.getDbFile());
    FILE *fp = fopen(curCkptFile, "w");
    if (NULL == fp) { 
 
        printError(ErrSysInternal, "Unable to set checkpointID");
        return;
    }
    fprintf(fp, "%d", id);
    logFine(Conf::logger, "Current checkpoint set to %d", id);
    fclose(fp);
    return;
}


//used only by the user database not the system database
DbRetVal Database::recoverUserDB()
{
    char dataFile[MAX_FILE_LEN];
    char cmd[MAX_FILE_LEN];
    sprintf(dataFile, "%s/db.chkpt.data", Conf::config.getDbFile());
    int fd = os::open(dataFile, fileOpenReadOnly, 0);
    if (-1 == fd) { return OK; }
    void *buf = (void *) metaData_;
    int readbytes = read(fd, buf, Conf::config.getMaxDbSize());
    if (readbytes == -1) { os::close(fd); return ErrOS; }
    os::close(fd);
    return OK;
}

//used only by the system database 
DbRetVal Database::recoverSystemDB()
{
    char mapFile[MAX_FILE_LEN];
    sprintf(mapFile, "%s/db.chkpt.map", Conf::config.getDbFile());
    int fd = open(mapFile, O_RDONLY);
    if (-1 == fd) { return OK; }
    CatalogTableTABLE cTable(this);
    CatalogTableINDEX cIndex(this);
    struct Object buf;
    while (read(fd, &buf, sizeof(buf))) {
        if (buf.type == Tbl) {
            cTable.setChunkPtr(buf.name, buf.firstPage, buf.curPage);
        }
        else if (buf.type == hIdx || buf.type == tIdx) {
            cIndex.setChunkPtr(buf.name, buf.type, buf.bucketChunk, buf.firstPage, buf.curPage);
        }
    }
    return OK;
}

