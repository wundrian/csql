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
#include <AbsSqlConnection.h>
#include <AbsSqlStatement.h>
#include <SqlLogConnection.h>
#include <SqlOdbcStatement.h>
#include <SqlFactory.h>
#include <SqlConnection.h>
#include <SqlStatement.h>
#include <CSql.h>
#include <CacheTableLoader.h>

// List which keeps all DS Information.
struct MultiThreadDSN 
{
    char dsn[IDENTIFIER_LENGTH];
    char user[IDENTIFIER_LENGTH];
    char pwd[IDENTIFIER_LENGTH];
    char tdb[IDENTIFIER_LENGTH];
    struct MultiThreadDSN *next;
};

int insert(char *table, long long pkid, AbsSqlConnection *targetconn, SqlStatement *sqlstmt, AbsSqlStatement *csqlstmt, AbsSqlConnection *csqlcon);
int remove(char *table, long long pkid, AbsSqlConnection *targetconn, AbsSqlStatement *csqlstmt,AbsSqlConnection *csqlcon);
int getRecordsFromTargetDb(AbsSqlConnection *targetconn, AbsSqlConnection *csqlcon,AbsSqlStatement *csqlstmt, SqlConnection *con, SqlStatement *sqlstmt);
void createCacheTableList();
DbRetVal getCacheField(char *tblName,char *fldName);
DbRetVal getCacheProjField(char *tblName,char *fielflist);
DbRetVal getCacheCondition(char *tblName,char *condition);
void setParamValues(AbsSqlStatement *stmt, int parampos, DataType type, int length, char *value);
void *fillBindBuffer(TDBInfo tName, DataType type, void *valBuf, int length=0);
List cacheTableList;
int srvStop =0;
static void sigTermHandler(int sig)
{
    printf("Received signal %d\nStopping the server\n", sig);
    srvStop = 1;
}

void printUsage()
{
   printf("Usage: csqlcacheserver \n");
   printf("Description: Start the csql caching server.\n");
   return;
}

AbsSqlConnection *csqlcon = NULL;   


//MultiDSN Section
class MultiDsnThread
{
    public:
    char ds[IDENTIFIER_LENGTH]; 
    char targetDb[IDENTIFIER_LENGTH];  
    char userName[IDENTIFIER_LENGTH]; 
    char pwdName[IDENTIFIER_LENGTH]; 
    MultiDsnThread() { ds[0]='\0'; targetDb[0]='\0'; userName[0]='\0'; pwdName[0]='\0';}
};

void *startThread(void *p);// Function is used for Thread
MultiDsnThread **multiDsnInput;


int main(int argc, char **argv)
{
    int c = 0, opt = 0;
    while ((c = getopt(argc, argv, "?")) != EOF) 
    {
        switch (c)
        {
            case '?' : { opt = 10; break; } //print help 
            default: opt=10; 

        }
    }//while options

    if (opt == 10) {
        printUsage();
        return 0;
    }

    os::signal(SIGINT, sigTermHandler);
    os::signal(SIGTERM, sigTermHandler);
    DbRetVal rv=OK;
    csqlcon = SqlFactory::createConnection(CSqlLog);
    SqlLogConnection *logConn = (SqlLogConnection *) csqlcon;
    logConn->setNoMsgLog(true);
    rv = csqlcon->connect(I_USER, I_PASS);
    if (rv != OK) {
        printError(ErrSysInternal, "Unable to connect to CSQL");
        return 1;
    }
    
    // Reading "csqlds.conf file"
    FILE *fp = NULL;
    fp = fopen(Conf::config.getDsConfigFile(),"r");
    if(fp==NULL){
        printError(ErrSysInit,"csqlds.conf file does not exist");
        csqlcon->disconnect();
        return 1;
    }
    struct MultiThreadDSN *head=NULL, *pnode=NULL;
    
    char dsnname[IDENTIFIER_LENGTH];dsnname[0]='\0';
    char tdbname[IDENTIFIER_LENGTH];tdbname[0] = '\0';
    char username[IDENTIFIER_LENGTH];username[0]='\0';
    char password[IDENTIFIER_LENGTH];password[0]='\0';
    int  totalDsn=0;

   // Populate the List
    while(!feof(fp)){
        struct MultiThreadDSN *multiDsn = new struct MultiThreadDSN;
        fscanf(fp,"%s %s %s %s\n",dsnname,username,password,tdbname);
        totalDsn++;
        strcpy(multiDsn->dsn,dsnname);
        strcpy(multiDsn->user,username);
        strcpy(multiDsn->pwd,password);
        strcpy(multiDsn->tdb,tdbname);
        multiDsn->next=NULL;

        if(pnode==NULL) {head=multiDsn; pnode=multiDsn;}
        else { pnode->next=multiDsn; pnode=pnode->next; }
    }
    fclose(fp);
    if (totalDsn == 1)
    {
        
        MultiDsnThread *info = new MultiDsnThread();
        strcpy(info->ds,pnode->dsn);
        strcpy(info->targetDb,pnode->tdb);
        strcpy(info->userName,pnode->user);
        strcpy(info->pwdName,pnode->pwd);
        startThread(info);
        printf("Cache Server Exiting\n");
        cacheTableList.reset();
        csqlcon->disconnect();
        return 0;
    }


        
    // Declare number of thread
    pthread_t *thrId =new pthread_t [totalDsn];
    multiDsnInput = (MultiDsnThread **) malloc (sizeof(MultiDsnThread *) * totalDsn);
    int i=0, status;
    
    //Traversing the list 
    pnode=head;
    while(pnode != NULL){
        multiDsnInput[i] = new MultiDsnThread();
        strcpy(multiDsnInput[i]->ds,pnode->dsn);
        strcpy(multiDsnInput[i]->targetDb,pnode->tdb);
        strcpy(multiDsnInput[i]->userName,pnode->user);
        strcpy(multiDsnInput[i]->pwdName,pnode->pwd);
      
        //pthread_create 
        pthread_create(&thrId[i], NULL, &startThread, multiDsnInput[i]);
        i++;
        pnode=pnode->next;
     }

     // Pthread_join     
     for(int j=0; j<totalDsn; j++){
         pthread_join(thrId[j], NULL);
     }
        
    printf("Cache Server Exiting\n");
    cacheTableList.reset();
    csqlcon->disconnect();
    // targetconn->disconnect();
    // printf("Out of main\n");
    delete[]thrId;
    return 0;
    
}

// Function for THreads
void *startThread(void *thrInfo)
{
    DbRetVal rv = OK;   
    AbsSqlConnection *targetconn;
    //AbsSqlConnection *csqlcon = NULL;
    AbsSqlStatement *csqlstmt = NULL;
    SqlConnection *con = NULL;
    SqlStatement *sqlstmt = NULL;

    
    MultiDsnThread *multiDsnInput = (MultiDsnThread *)thrInfo;
/*  csqlcon = SqlFactory::createConnection(CSqlLog);
    SqlLogConnection *logConn = (SqlLogConnection *) csqlcon;
    logConn->setNoMsgLog(true);
    rv = csqlcon->connect(I_USER, I_PASS);
    if (rv != OK) return NULL;
*/
    targetconn = SqlFactory::createConnection(CSqlAdapter);
    SqlOdbcConnection *dsnAda = (SqlOdbcConnection*)targetconn;
    dsnAda->setDsn(multiDsnInput->ds);//line added

    struct timeval timeout, tval;
    timeout.tv_sec = Conf::config.getCacheWaitSecs();
    timeout.tv_usec = 0;
reconnect:
    while(!srvStop) {
      rv = targetconn->connect(I_USER, I_PASS);
      if (rv != OK) {
         printError(ErrSysInternal, "Unable to connect to target database:%s", multiDsnInput->ds);
        tval.tv_sec = timeout.tv_sec;
        tval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &tval);
      } else break;
      if (srvStop) return NULL;
    }
    if (srvStop) return NULL;

    if (!Conf::config.useCache())
    {
        printf("Cache is set to OFF in csql.conf file\n");
        return NULL;
    }
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(targetconn);
    csqlstmt = SqlFactory::createStatement(CSqlLog); 
    csqlstmt->setConnection(csqlcon);

    int ret = 0;
    struct stat ofstatus,nfstatus;
    ret=stat(Conf::config.getTableConfigFile(),&ofstatus);
    timeout.tv_sec = Conf::config.getCacheWaitSecs();
    timeout.tv_usec = 0;
    createCacheTableList();
    while(!srvStop)
    {
        tval.tv_sec = timeout.tv_sec;
        tval.tv_usec = timeout.tv_usec;
        ret = os::select(0, 0, 0, 0, &tval);
        printf("Checking for cache updates\n");
        ret=stat(Conf::config.getTableConfigFile(),&nfstatus);
        if(ofstatus.st_mtime != nfstatus.st_mtime)
        {
            cacheTableList.reset();
            createCacheTableList();
            ofstatus.st_mtime = nfstatus.st_mtime;
        }
        if((ret = getRecordsFromTargetDb( targetconn, csqlcon, csqlstmt, con, sqlstmt )) == 1)  {
            if (srvStop) break;
            targetconn->disconnect();
            goto reconnect;
        }
    }

   //printf("Cache Server Exiting\n");
   //cacheTableList.reset();
   //csqlcon->disconnect();
    targetconn->disconnect();
    return NULL;
}

int getRecordsFromTargetDb(AbsSqlConnection *targetconn, AbsSqlConnection *csqlcon,AbsSqlStatement *csqlstmt, SqlConnection *con, SqlStatement *sqlstmt)
{
    long long pkid=0;
    char tablename[64];
    long long op=0, id=0,cId=0;
    int caId=0;
    int rows =0;
    DbRetVal rv = OK;
    int ret =0;
    char StmtStr[1024];
    caId =Conf::config.getSiteID();
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(targetconn);
    AbsSqlStatement *delstmt = SqlFactory::createStatement(CSqlAdapter);
    delstmt->setConnection(targetconn);
    //rv = delstmt->prepare("DELETE from csql_log_int where id=?;");
    sprintf(StmtStr, "SELECT * FROM csql_log_int where cacheid = %d;", caId);
    rv = stmt->prepare(StmtStr);
    if (rv != OK) {printf("Stmt prepare failed\n"); return 1; }
    stmt->bindField(1, tablename);
    stmt->bindField(2, &pkid);
    stmt->bindField(3, &op);
    stmt->bindField(4, &cId);
    stmt->bindField(5, &id);

    con = (SqlConnection *) csqlcon->getInnerConnection();
    sqlstmt = (SqlStatement *)csqlstmt->getInnerStatement();
    sqlstmt->setSqlConnection(con);

    sprintf(StmtStr, "DELETE from csql_log_int where id=?;");
    rv = delstmt->prepare(StmtStr);
    if (rv != OK) {
        stmt->free();
        delstmt->free();
        delete stmt;
        delete delstmt;
        printError(ErrSysInternal, "Statement prepare failed. TDB may be down");
        return 1;
    }
    int retVal =0; 
    while(true){
        rv = targetconn->beginTrans();
        rv = stmt->execute(rows);
        if (rv != OK) {
            printError(ErrSysInit, "Unable to execute stmt in target db");
            targetconn->rollback();
            stmt->free();
            delstmt->free();
            delete stmt;
            delete delstmt;
            return 1;
        }
        bool found = false;
        while ( stmt->fetch() != NULL) 
        {
            Util::trimEnd(tablename);
            logFiner(Conf::logger, "Row value is Table:%s PK:%lld OP:%lld CID:%lld\n", tablename, pkid, op,cId);

            if (op == 2) { //DELETE 
                retVal = remove(tablename,pkid, targetconn, csqlstmt, csqlcon); 
            } //DELETE
            else {
                retVal = insert(tablename, pkid, targetconn, sqlstmt, csqlstmt, csqlcon);
             } 
        //targetconn->commit();
        //rv = targetconn->beginTrans();
            if (retVal) ret =2;
            delstmt->setIntParam(1, id);
            rv = delstmt->execute(rows);
            if (rv != OK) {
                    printf("log record not deleted from the target db %d\n", rv);
                targetconn->rollback();
                break;
            }            
            rv = targetconn->commit();
            rv = targetconn->beginTrans();
            found=true;
        } 
        stmt->close();
        delstmt->close();
        if(!found) break;
    }
    targetconn->rollback();
    stmt->free();
    delstmt->free();
    delete stmt;
    delete delstmt;
    return ret;   
}

int insert(char *tablename, long long pkid, AbsSqlConnection *targetconn, SqlStatement *sqlstmt, AbsSqlStatement *csqlstmt, AbsSqlConnection *csqlcon)
{
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(targetconn);
    TDBInfo tdbname = ((SqlOdbcConnection*)targetconn)->getTrDbName();
    SqlOdbcStatement *ostmt = (SqlOdbcStatement*) stmt;
    char insStmt[1024];
    char pkfieldname[128];
    DbRetVal rv=getCacheField(tablename, pkfieldname);
    if(rv!=OK){
        ostmt->getPrimaryKeyFieldName(tablename, pkfieldname);
    }
    //Util::str_tolower(pkfieldname);
    char fieldlist[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char sbuf[1024];
    rv=getCacheProjField(tablename,fieldlist);
    if(rv!=OK){
        rv=getCacheCondition(tablename,condition);
        if(rv!=OK){
            sprintf(sbuf, "SELECT * FROM %s where %s = %lld;", tablename, pkfieldname, pkid);
        } else {
            sprintf(sbuf, "SELECT * FROM %s where %s = %lld and %s ;", tablename, pkfieldname, pkid,condition);
        }
    } else {
        rv=getCacheCondition(tablename,condition);
        if(rv!=OK){
            sprintf(sbuf, "SELECT %s FROM %s where %s = %lld;",fieldlist,tablename, pkfieldname, pkid);
        } else {
            sprintf(sbuf, "SELECT %s FROM %s where %s = %lld and %s;",fieldlist,tablename, pkfieldname, pkid,condition);
        }
    }
    //TODO::get the primary key field name from the table interface. need to implement it
    //printf("InsertString: %s\n", sbuf);
    rv = stmt->prepare(sbuf);
    if (rv != OK) return 2;

    char *ptr = insStmt;
    sprintf(ptr,"INSERT INTO %s VALUES(", tablename);
    ptr += strlen(ptr);
    bool firstFld = true;
    List fNameList = sqlstmt->getFieldNameList(tablename);
    int noOfFields = fNameList.size();
    while (noOfFields--) {
        if (firstFld) {
            firstFld = false;
            sprintf(ptr,"?", tablename);
            ptr += strlen(ptr);
        } else {
            sprintf(ptr, ",?");
            ptr += strlen(ptr);
        }
    }
    sprintf(ptr, ");");
    ptr += strlen(ptr);
    //printf("insert stmt: '%s'\n", insStmt);
    
    rv = csqlstmt->prepare(insStmt);
    if (rv != OK) { return 2; }
    List valBufList;
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    int fcount =0; void *valBuf; int fieldsize=0;
    void *buf[128];//TODO:resticts to support only 128 fields in table
    for (int i=0; i < 128; i++) buf[i]= NULL;
    DataType dType[128];
    Identifier *elem = NULL;
    BindBuffer *bBuf = NULL;
    while (fNameIter.hasElement()) {
        elem = (Identifier*) fNameIter.nextElement();
        sqlstmt->getFieldInfo(tablename, (const char*)elem->name, info);
        valBuf = AllDataType::alloc(info->type, info->length+1);
        os::memset(valBuf,0,info->length);
        bBuf = (BindBuffer *) fillBindBuffer(tdbname, info->type, valBuf, info->length);
if (info->type == typeString) {
}
        valBufList.append(bBuf);
        dType[fcount] = info->type;
        buf[fcount] = valBuf;
        stmt->bindField(fcount+1, buf[fcount]);
        fcount++;
    }
    delete info;
    int rows=0;
    int retValue = stmt->execute(rows);
    if (retValue && rows != 1) {
        printError(ErrSysInit, "Unable to execute statement at target db\n"); 
        return ErrSysInit; 
    }
    ListIterator bindIter = valBufList.getIterator();
    if (stmt->fetch() != NULL) {
        ostmt->setNullInfo(csqlstmt);
        if(tdbname == postgres){
            for (int i=0; i < fcount; i++) { 
               if(dType[i] == typeString) Util::trimRight((char *)buf[i]);
            }
        }
        //setXXXParams to be called here
        int pos = 1;
        while (bindIter.hasElement()) {
            bBuf = (BindBuffer *) bindIter.nextElement();
            setParamValues(csqlstmt, pos++, bBuf->type, bBuf->length,
                                                          (char *)bBuf->csql);
        }
        csqlcon->beginTrans();
        int rows = 0;
        rv = csqlstmt->execute(rows);
        if (rv != OK) { 
            printf ("execute failed \n"); 
            printf(" STMT: %s\n",insStmt);
            return 3; 
        }
        csqlcon->commit();      
        //printf("successfully inserted value with pkid = %d\n", pkid);
        //Note:insert may fail if the record is inserted from this cache
    }
    //for (int i=0; i < fcount; i++) free(buf[i]); 
    ListIterator iter = valBufList.getIterator();
    while (iter.hasElement()){
        bBuf = (BindBuffer*) iter.nextElement();
if (bBuf->type == typeString)
        //printf("Values %x %x \n", bBuf->csql, bBuf->targetdb);
        delete bBuf;
    }
   
    stmt->free();
    delete stmt;
    return 0;
}
int remove(char *tablename, long long pkid, AbsSqlConnection *targetconn, AbsSqlStatement *csqlstmt,AbsSqlConnection *csqlcon)
{
    DbRetVal rv = OK;
    char delStmt[1024];
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(targetconn);
    SqlOdbcStatement *ostmt = (SqlOdbcStatement*) stmt;
    char pkfieldname[128];
    rv=getCacheField(tablename, pkfieldname);
    if(rv!=OK){
        ostmt->getPrimaryKeyFieldName(tablename, pkfieldname);
    }
    Util::str_tolower(pkfieldname);
    stmt->close();
    stmt->free();
    delete stmt;
    sprintf(delStmt, "DELETE FROM %s where %s = %d", tablename, pkfieldname, pkid);
    //printf("delStmt is %s\n", delStmt);
    rv = csqlstmt->prepare(delStmt);
    if (rv != OK) { return 2; }
    rv = csqlcon->beginTrans();
    if (rv != OK) return 2;
    int rows = 0;
    rv = csqlstmt->execute(rows);
    if (rv != OK || rows !=1)  
    {
        csqlcon->rollback();
        printf("Delete failed for stmt %s\n", delStmt);
        return 3;
    }
    rv = csqlcon->commit();
    
    return 0;
}

void createCacheTableList()
{
    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "cachetable.conf file does not exist");
        fclose(fp);
    }
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];

    int mode;
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %s %s %s \n",&mode,tablename,fieldname,condition,field,dsnName);
        CacheTableInfo  *cacheTable=new CacheTableInfo();
        cacheTable->setTableName(tablename);
        cacheTable->setFieldName(fieldname);
        cacheTable->setProjFieldList(field);
        cacheTable->setCondition(condition);
        cacheTableList.append(cacheTable);
    }
   // printf("Table %s is not cached\n",tabname);
    fclose(fp);
   
}

DbRetVal getCacheCondition(char *tblName,char *condition)
{
    ListIterator iter=cacheTableList.getIterator();
    CacheTableInfo  *cacheTable;
    while(iter.hasElement())
    {
        cacheTable=(CacheTableInfo*)iter.nextElement();
        if(strcmp(cacheTable->getTableName(),tblName)==0){
            if(strcmp(cacheTable->getCondition(),"NULL")!=0)
            {
                strcpy(condition,cacheTable->getCondition());
                return OK;
            }
        }
    }
    return ErrNotExists;
}

DbRetVal getCacheProjField(char *tblName,char *fieldlist)
{
    ListIterator iter=cacheTableList.getIterator();
    CacheTableInfo  *cacheTable;
    while(iter.hasElement())
    {
        cacheTable=(CacheTableInfo*)iter.nextElement();
        if(strcmp(cacheTable->getTableName(),tblName)==0){
            if(strcmp(cacheTable->getProjFieldList(),"NULL")!=0)
            {
                strcpy(fieldlist,cacheTable->getProjFieldList());
                return OK;
            }
        }
    }
    return ErrNotExists;
}
DbRetVal getCacheField(char *tblName,char *fldName)
{
    ListIterator iter=cacheTableList.getIterator();
    CacheTableInfo  *cacheTable;
    while(iter.hasElement())    
    {
        cacheTable=(CacheTableInfo*)iter.nextElement();
        if(strcmp(cacheTable->getTableName(),tblName)==0){
            if(strcmp(cacheTable->getFieldName(),"NULL")!=0)
            {
                strcpy(fldName,cacheTable->getFieldName());
		return OK;
            }
        }
            
    }
    return ErrNotExists;
}

void setParamValues(AbsSqlStatement *stmt, int parampos, DataType type, int length, char *value)
{
    switch(type)
    {
        case typeInt:
            stmt->setIntParam(parampos, *(int*)value);
            break;
        case typeLong:
            stmt->setLongParam(parampos, *(long*)value);
            break;
        case typeLongLong:
            stmt->setLongLongParam(parampos, *(long long*)value);
            break;
        case typeShort:
            stmt->setShortParam(parampos, *(short*)value);
            break;
        case typeByteInt:
            stmt->setByteIntParam(parampos, *(char*)value);
            break;
        case typeDouble:
            stmt->setDoubleParam(parampos, *(double*)value);
            break;
        case typeFloat:
            stmt->setFloatParam(parampos, *(float*)value);
            break;
        case typeDate:
            stmt->setDateParam(parampos, *(Date*)value);
            break;
        case typeTime:
            stmt->setTimeParam(parampos, *(Time*)value);
            break;
        case typeTimeStamp:
            stmt->setTimeStampParam(parampos, *(TimeStamp*)value);
            break;
        case typeString:
            {
                char *d =(char*)value;
                d[length-1] = '\0';
                stmt->setStringParam(parampos, (char*)value);
                break;
            }
        case typeBinary:
            stmt->setBinaryParam(parampos, (char *) value, length);
            break;
    }
    return;
}

void *fillBindBuffer(TDBInfo tdbName, DataType type, void *valBuf, int length)
{
    BindBuffer *bBuf = NULL;
    switch(type) 
    {
        case typeDate:
            bBuf = new BindBuffer();
            bBuf->csql = valBuf;
            bBuf->type = typeDate;
            bBuf->length = sizeof(DATE_STRUCT);
            bBuf->targetdb = malloc(bBuf->length);
            memset(bBuf->targetdb, 0, bBuf->length);
            valBuf = bBuf->targetdb;
            break;
        case typeTime:
            bBuf = new BindBuffer();
            bBuf->csql = valBuf;
            bBuf->type = typeTime;
            bBuf->length = sizeof(TIME_STRUCT);
            bBuf->targetdb = malloc(bBuf->length);
            memset(bBuf->targetdb, 0, bBuf->length);
            valBuf = bBuf->targetdb;
            break;
        case typeTimeStamp:
            bBuf = new BindBuffer();
            bBuf->csql = valBuf;
            bBuf->type = typeTimeStamp;
            bBuf->length = sizeof(TIMESTAMP_STRUCT);
            bBuf->targetdb = malloc(bBuf->length);
            memset(bBuf->targetdb, 0, bBuf->length);
            valBuf = bBuf->targetdb;
            break;
        case typeLongLong:
        {
            if( tdbName == postgres )
            {
                bBuf = new BindBuffer();
                bBuf->type = typeLongLong;
                bBuf->length = 40;
                bBuf->csql = valBuf;
                bBuf->targetdb = AllDataType::alloc(typeString,bBuf->length);
                memset(bBuf->targetdb, 0, bBuf->length);
                valBuf = bBuf->targetdb;
                break;
            }else
            {
                bBuf = new BindBuffer();
                bBuf->type = type;
                bBuf->csql = valBuf;
                bBuf->length = length;
                break;
            }
        }
        case typeString:
            if( tdbName == postgres )
            {
                bBuf = new BindBuffer();
                bBuf->type = typeString;
                bBuf->csql = valBuf;
                bBuf->length = length+1;
                break;
            }
        default:
            bBuf = new BindBuffer();
            bBuf->type = type;
            bBuf->csql = valBuf;
            bBuf->length = length;
            break;
    }
    return bBuf;
}
