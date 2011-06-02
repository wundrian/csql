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
#include <SqlLogStatement.h>
#include <SqlOdbcStatement.h>
#include <SqlFactory.h>
#include <SqlConnection.h>
#include <SqlStatement.h>
#include <CSql.h>
#include <CacheTableLoader.h>

#define STMTBUCKETS 	dsnThrInfo->stmtBuckets
#define CSQLCONNECT		dsnThrInfo->csqlcon
#define	TRDBCONNECT 	dsnThrInfo->targetcon
#define CACHELIST		dsnThrInfo->cacheTableList
#define DSN				dsnThrInfo->dsn
#define TSELSTMT		dsnThrInfo->targetSelStmt
#define TDELSTMT		dsnThrInfo->targetDelStmt
#define TABLENAME_ARRAY	dsnThrInfo->tableName
#define PKID_ARRAY		dsnThrInfo->pkid
#define OPERATION_ARRAY	dsnThrInfo->operation
#define CACHEID_ARRAY	dsnThrInfo->cacheid
#define AUTOID_ARRAY	dsnThrInfo->autoid

#define PKID		PKID_ARRAY[row]
#define OPERATION	OPERATION_ARRAY[row]
#define CACHEID		CACHEID_ARRAY[row]
#define AUTOID		AUTOID_ARRAY[row]

typedef class CachedTableStmtNode
{
    public:
    char tableName[IDENTIFIER_LENGTH];
    AbsSqlStatement *adptStmt;
    AbsSqlStatement *insStmt;
    AbsSqlStatement *delStmt;
    CachedTableStmtNode(const char *tname, AbsSqlStatement *ast, AbsSqlStatement *ist) 
    { 
        strcpy(tableName, tname); adptStmt = ast; 
        insStmt = ist; delStmt = NULL;
    }
    CachedTableStmtNode(const char *tname, AbsSqlStatement *dst) 
    {
        strcpy(tableName, tname); adptStmt = NULL; 
        insStmt = NULL; delStmt = dst;
    }
    ~CachedTableStmtNode()
    { 
        if (insStmt) { insStmt->free(); delete insStmt; }
        if (delStmt) { delStmt->free(); delete delStmt; }
        if (adptStmt) { adptStmt->free(); delete adptStmt; }
    }
} CTStmtNode;

int insert(char *table, int pkid, void *thrInfo);
int remove(char *table, int pkid, void *thrInfo);
int getRecordsFromTargetDb(void *thrInfo);
void createCacheTableList(AbsSqlConnection *tcon, List *cacheTableList);
DbRetVal getPKFieldName(char *tblName,char *fldName, List *cacheTableList);
DbRetVal getCacheField(char *tblName,char *fldName, List *cacheTableList);
DbRetVal getCacheProjField(char *tblName,char *fielflist, List *cacheTableList);
DbRetVal getCacheCondition(char *tblName,char *condition, List *cacheTableList);
void *fillBindBuffer(TDBInfo tName, DataType type, void *valBuf, int length=0);
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

void addToHashTable(char *tableName, AbsSqlStatement *adHdl, AbsSqlStatement *insHdl, void *stmtBuckets)
{
    unsigned int hval = Util::hashString(tableName);
    int bucketNo = hval % STMT_BUCKET_SIZE;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    CTStmtNode *node = new CTStmtNode(tableName, adHdl, insHdl);
    stmtBucket->bucketList.append(node);
    return;
}

void addToHashTable(char *tableName, AbsSqlStatement *delHdl, void *stmtBuckets)
{
    unsigned int hval = Util::hashString(tableName);
    int bucketNo = hval % STMT_BUCKET_SIZE;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    CTStmtNode *node = new CTStmtNode(tableName, delHdl);
    stmtBucket->bucketList.append(node);
    return;
}

void removeFromHashTable(char *tableName, void *stmtBuckets)
{
    unsigned int hval = Util::hashString(tableName);
    int bucketNo = hval % STMT_BUCKET_SIZE;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    CTStmtNode *node = NULL, *delNode = NULL;
    ListIterator it = stmtBucket->bucketList.getIterator();
    while(it.hasElement()) {
        node = (CTStmtNode *) it.nextElement();
        if(strcmp(node->tableName, tableName) == 0) { delNode = node; break; }
    }
    it.reset();
    if (delNode != NULL) {
       stmtBucket->bucketList.remove(delNode);
       delete delNode;
    }
    return;
}

CTStmtNode *getStmtFromHashTable(char *tableName, void *stmtBuckets)
{
    unsigned int hval = Util::hashString(tableName);
    int bucketNo = hval % STMT_BUCKET_SIZE;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    if (stmtBucket == NULL) return NULL;
    CTStmtNode *node = NULL;
    ListIterator it = stmtBucket->bucketList.getIterator();
    while(it.hasElement()) {
        node = (CTStmtNode *) it.nextElement();
        if(strcmp(node->tableName, tableName) == 0) return node; 
    }
    return NULL;
}

void freeAllStmtHandles(void *stmtBuckets)
{
    if (NULL == stmtBuckets) return;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    CTStmtNode *node = NULL;
    for (int i=0; i <STMT_BUCKET_SIZE; i++)
    {
        StmtBucket *stmtBucket = &buck[i];
        if (stmtBucket == NULL) continue;
        ListIterator it = stmtBucket->bucketList.getIterator();
        while(it.hasElement()) {
            node = (CTStmtNode *)it.nextElement();
            delete node;
        }
        stmtBucket->bucketList.reset();
    }
    ::free(stmtBuckets);
}

//MultiDSN Section
class DsnThrInput
{
    public:
    char dsn[IDENTIFIER_LENGTH]; 
    char tdb[IDENTIFIER_LENGTH];  
    char uname[IDENTIFIER_LENGTH]; 
    char pname[IDENTIFIER_LENGTH]; 
    void *stmtBuckets;
    AbsSqlConnection *csqlcon;
    AbsSqlConnection *targetcon;
    AbsSqlStatement *targetSelStmt;
    AbsSqlStatement *targetDelStmt;
    List cacheTableList;
    //Arrays for result set fetch
    char **tableName;
    int *pkid;
    int *operation;
    int *cacheid;
    int *autoid;
    DsnThrInput *next;
    DsnThrInput() 
    { 
       dsn[0]='\0'; tdb[0]='\0'; uname[0]='\0'; pname[0]='\0'; next = NULL; 
       stmtBuckets = NULL; cacheTableList.init(); 
       csqlcon = NULL; targetcon = NULL; 
       targetSelStmt = NULL; targetDelStmt = NULL;
       tableName = NULL; pkid = NULL; operation = NULL; cacheid = NULL;
       autoid = NULL;
    }
    ~DsnThrInput()
    {  
        if (tableName) free(tableName);
        if (pkid) free(pkid);
        if (operation) free(operation);
        if (cacheid) free(cacheid);
        if (autoid) free(autoid);
    }
};

void *startThread(void *p);// Function is used for Thread
DsnThrInput **multiDsnArray;

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

    Conf::config.readAllValues(os::getenv("CSQL_CONFIG_FILE"));

    DbRetVal rv=OK;

    // Reading "csqlds.conf file"
    FILE *fp = NULL;
    fp = fopen(Conf::config.getDsConfigFile(),"r");
    if(fp==NULL){
        printError(ErrSysInit,"csqlds.conf file does not exist");
        exit(1);
    }
    struct DsnThrInput *head=NULL, *pnode=NULL;
    
    char dsnname[IDENTIFIER_LENGTH];dsnname[0]='\0';
    char tdbname[IDENTIFIER_LENGTH];tdbname[0] = '\0';
    char username[IDENTIFIER_LENGTH];username[0]='\0';
    char password[IDENTIFIER_LENGTH];password[0]='\0';
    int  totalDsn=0;

    // Populate the List
    while (!feof(fp)) {
        int inputItems = fscanf(fp,"%s %s %s %s\n",
                                           dsnname,username,password,tdbname);
        if (inputItems != 4) {
            printError(ErrNotExists, "No Entry found in csqlds.conf file");
            return 1;
        }
        DsnThrInput *dsnThrInput = new DsnThrInput();
        totalDsn++;
        strcpy(dsnThrInput->dsn,dsnname);
        strcpy(dsnThrInput->uname,username);
        strcpy(dsnThrInput->pname,password);
        strcpy(dsnThrInput->tdb,tdbname);
        dsnThrInput->next=NULL;

        if(pnode==NULL) {head=dsnThrInput; pnode=dsnThrInput;}
        else { pnode->next=dsnThrInput; pnode=pnode->next; }
    }
    fclose(fp);

    bool singleThread = (totalDsn == 1);
    
    pthread_t *thrId = NULL;
    
    pnode=head;
    
    if (!singleThread) { 
        thrId =new pthread_t [totalDsn];
        multiDsnArray = (DsnThrInput **) 
                                     malloc (sizeof(DsnThrInput *) * totalDsn);
        for (int i = 0; i < totalDsn; i++) {
            multiDsnArray[i] = pnode;
            pthread_create(&thrId[i], NULL, &startThread, multiDsnArray[i]);
            pnode=pnode->next;
        } 
        // Pthread_join     
        for(int i=0; i<totalDsn; i++) pthread_join(thrId[i], NULL);
    } else {
        startThread(pnode);
    }
   
    printf("Cache Server Exiting\n");
    if (!singleThread) {
        for (int i = 0; i < totalDsn; i++) delete multiDsnArray[i];
        free (multiDsnArray);
        delete [] thrId;
    } else { if (pnode) delete pnode; }
    return 0;
}

// Function for THreads
void *startThread(void *thrInfo)
{
    DsnThrInput *dsnThrInfo = (DsnThrInput *)thrInfo;
    STMTBUCKETS = malloc (STMT_BUCKET_SIZE * sizeof(StmtBucket));
    memset(STMTBUCKETS, 0, STMT_BUCKET_SIZE * sizeof(StmtBucket));
    DbRetVal rv = OK;   
    CSQLCONNECT = SqlFactory::createConnection(CSqlLog);
    SqlLogConnection *logConn = (SqlLogConnection *) CSQLCONNECT;
    logConn->setNoMsgLog(true);
    rv = CSQLCONNECT->connect(I_USER, I_PASS);
    if (rv != OK) return NULL;
    TRDBCONNECT = SqlFactory::createConnection(CSqlAdapter);
    SqlOdbcConnection *dsn = (SqlOdbcConnection*) TRDBCONNECT;
    dsn->setDsName(DSN);//line added
    struct timeval timeout, tval;
    timeout.tv_sec = Conf::config.getCacheWaitSecs();
    timeout.tv_usec = 0;
    CACHELIST.init();
reconnect:
    while(!srvStop) {
        rv = TRDBCONNECT->connect(I_USER, I_PASS);
        if (rv != OK) {
            printError(ErrSysInternal, "Unable to connect to target database:%s", DSN);
            tval.tv_sec = timeout.tv_sec;
            tval.tv_usec = timeout.tv_usec;
            os::select(0, 0, 0, 0, &tval);
        } else break;
        if (srvStop) { 
            CSQLCONNECT->disconnect(); delete CSQLCONNECT; 
            TRDBCONNECT->disconnect(); delete TRDBCONNECT; 
            return NULL;
        }
    }
    if (srvStop) {
        CSQLCONNECT->disconnect(); delete CSQLCONNECT;
        TRDBCONNECT->disconnect(); delete TRDBCONNECT;
        return NULL;
    }
    if (!Conf::config.useCache())
    {
        printError(ErrSysInternal, "Cache is set to OFF in csql.conf file\n");
        CSQLCONNECT->disconnect(); delete CSQLCONNECT;
        TRDBCONNECT->disconnect(); delete TRDBCONNECT;
        return NULL;
    }

    int ret = 0;
    struct stat ofstatus,nfstatus;
    ret=stat(Conf::config.getTableConfigFile(),&ofstatus);
    createCacheTableList(TRDBCONNECT, &CACHELIST);
    while(!srvStop)
    {
        tval.tv_sec = timeout.tv_sec;
        tval.tv_usec = timeout.tv_usec;
        ret = os::select(0, 0, 0, 0, &tval);
        printf("Checking for cache updates\n");
        if (srvStop) break;
        ret=stat(Conf::config.getTableConfigFile(),&nfstatus);
        if(ofstatus.st_mtime != nfstatus.st_mtime)
        {
            ListIterator it = CACHELIST.getIterator();
            while (it.hasElement()) delete it.nextElement();
            CACHELIST.reset();
            createCacheTableList(TRDBCONNECT, &CACHELIST);
            ofstatus.st_mtime = nfstatus.st_mtime;
        }
        if((ret = getRecordsFromTargetDb(thrInfo)) == 1) {
            if (srvStop) break;
            TRDBCONNECT->disconnect();
            ListIterator it = CACHELIST.getIterator();
            while (it.hasElement()) delete it.nextElement();
            CACHELIST.reset();
            goto reconnect;
        }
    }
     
    freeAllStmtHandles(STMTBUCKETS);
    TRDBCONNECT->disconnect(); delete TRDBCONNECT;
    CSQLCONNECT->disconnect(); 
    delete CSQLCONNECT;
    
    ListIterator it = CACHELIST.getIterator();
    while (it.hasElement()) delete it.nextElement();
    CACHELIST.reset();
    return NULL;
}

int getRecordsFromTargetDb(void *thrInfo) 
{
    DsnThrInput *dsnThrInfo = (DsnThrInput *)thrInfo;
    int rows =0;
    DbRetVal rv = OK;
    int ret =0;
    char StmtStr[1024];
    int cacheId = Conf::config.getSiteID();
    TSELSTMT = SqlFactory::createStatement(CSqlAdapter);
    TSELSTMT->setConnection(TRDBCONNECT);
    TDELSTMT = SqlFactory::createStatement(CSqlAdapter);
    TDELSTMT->setConnection(TRDBCONNECT);
    //rv = delstmt->prepare("DELETE from csql_log_int where id=?;");
    sprintf(StmtStr, "SELECT * FROM csql_log_int where cacheid = %d;", cacheId);
    
    SqlOdbcStatement *oselstmt = (SqlOdbcStatement *) TSELSTMT;
    rv = oselstmt->prepareForResultSet(StmtStr);
    if (rv != OK) {
        printError(ErrSysInternal, "Statement prepare failed. TDB may be down"); 
        return 1; 
    }
    
    int noOfRowsFetched = 0;
    int nLogRecords = Conf::config.getNoOfRowsToFetchFromTDB();
    if (TABLENAME_ARRAY == NULL) {
        TABLENAME_ARRAY = (char **) malloc(nLogRecords * IDENTIFIER_LENGTH);
        PKID_ARRAY = (int *) malloc(nLogRecords * sizeof(int));
        OPERATION_ARRAY = (int *) malloc(nLogRecords * sizeof(int));
        CACHEID_ARRAY = (int *) malloc(nLogRecords * sizeof(int));
        AUTOID_ARRAY = (int *) malloc(nLogRecords * sizeof(int));
    }
        memset(TABLENAME_ARRAY, 0, nLogRecords * IDENTIFIER_LENGTH);
        memset(PKID_ARRAY, 0, nLogRecords * sizeof(int));
        memset(OPERATION_ARRAY, 0, nLogRecords * sizeof(int));
        memset(CACHEID_ARRAY, 0, nLogRecords * sizeof(int));
        memset(AUTOID_ARRAY, 0, nLogRecords * sizeof(int));
    
    oselstmt->setResultSetInfo(nLogRecords);
    
    oselstmt->rsBindField(1, TABLENAME_ARRAY);
    oselstmt->rsBindField(2, PKID_ARRAY);
    oselstmt->rsBindField(3, OPERATION_ARRAY);
    oselstmt->rsBindField(4, CACHEID_ARRAY);
    oselstmt->rsBindField(5, AUTOID_ARRAY);

    sprintf(StmtStr, "DELETE from csql_log_int where id=?;");
    rv = TDELSTMT->prepare(StmtStr);
    if (rv != OK) {
        printError(ErrSysInternal, "Statement prepare failed. TDB may be down"); 
        TSELSTMT->free(); TDELSTMT->free(); delete TSELSTMT; delete TDELSTMT; 
        return 1;
    }
    int retVal =0; 
    TDBInfo tdbname = ((SqlOdbcConnection*)TRDBCONNECT)->getTrDbName();
    rv = TRDBCONNECT->beginTrans();
    rv = oselstmt->executeForResultSet();
    if (rv != OK) {
        printError(ErrSysInit, "Unable to execute stmt in target db");
        TRDBCONNECT->rollback();
        TSELSTMT->free(); TDELSTMT->free(); 
        delete TSELSTMT; delete TDELSTMT;
        return 1;
    }
    bool found = false;
    do {
        rv = oselstmt->fetchScroll(&noOfRowsFetched);
        int row = 0;
        /* display each row */
        for (row = 0; row < noOfRowsFetched; row++) {
            char *tblName = (char *) TABLENAME_ARRAY + IDENTIFIER_LENGTH * row; 
            /*printf( "Row %d>", row );
            printf( " %s <>", tblName);
            printf( " %d <>", PKID);
            printf( " %d <>", OPERATION);
            printf( " %d <>", CACHEID);
            printf( " %d <>", AUTOID);
            printf( "\n" ); */
            Util::trimEnd(tblName);
            logFiner(Conf::logger, "Row value is Table:%s PK:%d OP:%d CID:%d\n", tblName, PKID, OPERATION, CACHEID);
       
            if (OPERATION == 2) { //DELETE 
                retVal = remove(tblName,PKID, thrInfo); 
                logFinest(Conf::logger, "DELETE %s %d", tblName, PKID);
            } //DELETE
            else {
                retVal = insert(tblName, PKID, thrInfo);
                logFinest(Conf::logger, "INSERT %s %d", tblName, PKID);

            } 
            if (retVal) ret =2;
            TDELSTMT->setIntParam(1, AUTOID);
            rv = TDELSTMT->execute(rows);
            if (rv != OK) {
                printError(ErrSysInternal, "Log record table:%s PK:%d RowID:%d not deleted from the target db %d\n", tblName, PKID, AUTOID, rv);
                TRDBCONNECT->rollback();
                break;
            }            
        }    
    } while (rv == OK && noOfRowsFetched == nLogRecords);
    TSELSTMT->close(); 
    TDELSTMT->close();
    TRDBCONNECT->commit();
    TSELSTMT->free(); TDELSTMT->free(); delete TSELSTMT; delete TDELSTMT;
    return ret;   
}

int insert(char *tablename, int pkid, void *thrInfo)
{
    DsnThrInput *dsnThrInfo = (DsnThrInput *)thrInfo;
    DbRetVal rv = OK;
    List fNameList;
    AbsSqlStatement *astmt = NULL;
    SqlOdbcStatement *ostmt = NULL;
    AbsSqlStatement *istmt = NULL;
    SqlStatement *sqlstmt = NULL;
    TDBInfo tdbname = ((SqlOdbcConnection*)TRDBCONNECT)->getTrDbName();
    CTStmtNode *node = getStmtFromHashTable(tablename, STMTBUCKETS);
    if ((node == NULL) || (node && node->insStmt == NULL)) {
        astmt = SqlFactory::createStatement(CSqlAdapter);
        astmt->setConnection(TRDBCONNECT);
        istmt = SqlFactory::createStatement(CSqlLog);
        istmt->setConnection(CSQLCONNECT);
        sqlstmt = (SqlStatement *) istmt->getInnerStatement();
        char insStmt[1024];
        char pkfieldname[128]; pkfieldname[0]='\0';
        DbRetVal rv=getCacheField(tablename, pkfieldname, &CACHELIST);
        if (rv!=OK) {
            rv = getPKFieldName(tablename, pkfieldname, &CACHELIST);
            if (rv != OK) {
            }
        }
        //Util::str_tolower(pkfieldname);
        char fieldlist[IDENTIFIER_LENGTH];
        char condition[IDENTIFIER_LENGTH];
        char sbuf[1024];
        rv=getCacheProjField(tablename,fieldlist, &CACHELIST);
        if(rv!=OK){
            rv=getCacheCondition(tablename,condition, &CACHELIST);
            if(rv!=OK){
                sprintf(sbuf, "SELECT * FROM %s where %s = ?;", tablename, pkfieldname);
            } else {
                sprintf(sbuf, "SELECT * FROM %s where %s = ? and %s ;", tablename, pkfieldname, condition);
            }
        } else {
            rv=getCacheCondition(tablename,condition, &CACHELIST);
            if(rv!=OK){
                sprintf(sbuf, "SELECT %s FROM %s where %s = ?;",fieldlist,tablename, pkfieldname);
            }     else {
                sprintf(sbuf, "SELECT %s FROM %s where %s = ? and %s;",fieldlist,tablename, pkfieldname, condition);
            }
        }
        //TODO::get the primary key field name from the table interface. need to implement it
        //printf("Select String from adapter\n: *****%s\n", sbuf);
        rv = astmt->prepare(sbuf);
        if (rv != OK) return 2;
        char *ptr = insStmt;
        sprintf(ptr,"INSERT INTO %s VALUES(", tablename); ptr += strlen(ptr);
        bool firstFld = true;
        fNameList = sqlstmt->getFieldNameList(tablename, rv);
        int noOfFields = fNameList.size();
        while (noOfFields--) {
            if (firstFld) {
                firstFld = false;
                sprintf(ptr,"?", tablename); ptr += strlen(ptr);
            } else {
                sprintf(ptr, ",?"); ptr += strlen(ptr);
            }
        }
        sprintf(ptr, ");"); ptr += strlen(ptr);
        //printf("ins stmt: '%s'\n", insStmt); 
        rv = istmt->prepare(insStmt);
        if (rv != OK) { return 2; }
        if(node == NULL) addToHashTable(tablename, astmt, istmt, STMTBUCKETS);
        else { 
            node->adptStmt = astmt; 
            node->insStmt = istmt; 
        }
    } else {
        istmt = node->insStmt;
        astmt = node->adptStmt;
        sqlstmt = (SqlStatement *) istmt->getInnerStatement();
        fNameList = sqlstmt->getFieldNameList(tablename, rv);
    }
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
        valBuf = AllDataType::alloc(info->type, info->length);
        os::memset(valBuf,0,info->length);
        bBuf = (BindBuffer *) SqlStatement::fillBindBuffer(tdbname, info->type, valBuf, info->length);
        valBufList.append(bBuf);
        dType[fcount] = info->type;
        buf[fcount] = bBuf->csql;
        astmt->bindField(fcount+1, buf[fcount]);
        fcount++;
    }
    delete info;
    int rows=0;
    astmt->setIntParam(1, pkid);
    int retValue = astmt->execute(rows);
    if (retValue && rows != 1) {
        printError(ErrSysInit, "Unable to execute statement at target db\n"); 
        return ErrSysInit; 
    }
    ListIterator bindIter = valBufList.getIterator();
    if (astmt->fetch() != NULL) {
        ostmt = (SqlOdbcStatement *) astmt;
        ostmt->setNullInfo(istmt);
        if(tdbname == postgres){
            for (int i=0; i < fcount; i++) { 
               if(dType[i] == typeString) Util::trimRight((char *)buf[i]);
            }
        }
        //setXXXParams to be called here
        int pos = 1;
        while (bindIter.hasElement()) {
            bBuf = (BindBuffer *) bindIter.nextElement();
            SqlStatement::setParamValues(istmt, pos++, bBuf->type, 
                                                     bBuf->length, bBuf->csql);
        }
        CSQLCONNECT->beginTrans();
        int rows = 0;
        rv = istmt->execute(rows);
        if (rv != OK) { 
            printf ("execute failed \n"); 
            //printf(" STMT: %s\n",insStmt);
            return 3; 
        }
        CSQLCONNECT->commit();      
        //printf("successfully inserted value with pkid = %d\n", pkid);
        //Note:insert may fail if the record is inserted from this cache
    }
    astmt->close();
    //for (int i=0; i < fcount; i++) free(buf[i]); 
    ListIterator iter = valBufList.getIterator();
    while (iter.hasElement()){
        bBuf = (BindBuffer*) iter.nextElement();
        delete bBuf;
    }
    valBufList.reset();
    iter = fNameList.getIterator();
    while (iter.hasElement()) delete iter.nextElement();
    fNameList.reset();

    return 0;
}
int remove(char *tablename, int pkid, void *thrInfo)
{
    DsnThrInput *dsnThrInfo = (DsnThrInput *)thrInfo;
    DbRetVal rv = OK;
    List fNameList;
    SqlOdbcStatement *ostmt = NULL;
    AbsSqlStatement *dstmt = NULL;
    SqlStatement *sqlstmt = NULL;
    TDBInfo tdbname = ((SqlOdbcConnection*)TRDBCONNECT)->getTrDbName();
    CTStmtNode *node = getStmtFromHashTable(tablename, STMTBUCKETS);
    if (node == NULL || (node && node->delStmt == NULL)) {
        dstmt = SqlFactory::createStatement(CSqlLog);
        dstmt->setConnection(CSQLCONNECT);
        sqlstmt = (SqlStatement *) dstmt->getInnerStatement();
        char delStmt[1024];
        char pkfieldname[128]; pkfieldname[0]='\0';
        DbRetVal rv=getCacheField(tablename, pkfieldname, &CACHELIST);
        if (rv!=OK) {
            rv = getPKFieldName(tablename, pkfieldname, &CACHELIST);
            if (rv != OK) {
            }
        }
        Util::str_tolower(pkfieldname);
        sprintf(delStmt, "DELETE FROM %s where %s = ?;", tablename, pkfieldname);
        //printf("Delete stmt: %s\n", delStmt);
        rv = dstmt->prepare(delStmt);
        if (rv != OK) return 2; 
        if (node == NULL) addToHashTable(tablename, dstmt, STMTBUCKETS);
        else { node->delStmt = dstmt; } 
    } else { dstmt = node->delStmt; }
    dstmt->setIntParam(1, pkid);
        
    rv = CSQLCONNECT->beginTrans();
    if (rv != OK) return 2;
    int  rows = 0;
    //printf("DEBUG: pkid = %d\n", pkid);
    rv = dstmt->execute(rows);
    if (rv != OK || rows !=1)  
    {
        CSQLCONNECT->rollback();
         //printf("DEBUG: delete stmt execute failed in csql = %d\n", rv);
//        printError(ErrSysInternal, "Delete failed for stmt %s\n", delStmt);
        return 3;
    }
    rv = CSQLCONNECT->commit();
    return 0;
}

void createCacheTableList(AbsSqlConnection *tcon, List *cacheTableList)
{
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(tcon);
    SqlOdbcStatement *ostmt = (SqlOdbcStatement*) stmt;
    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "csqltable.conf file does not exist");
        fclose(fp);
    }
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];
    char pkfield[IDENTIFIER_LENGTH];

    int mode;
    while(!feof(fp))
    {
        pkfield[0]='\0';
        int items = fscanf(fp,"%d %s %s %s %s %s \n",&mode,tablename,fieldname,condition,field,dsnName);
        if (items != 6) break;
        CacheTableInfo *cacheTable=new CacheTableInfo();
        cacheTable->setTableName(tablename);
        cacheTable->setFieldName(fieldname);
        cacheTable->setProjFieldList(field);
        cacheTable->setCondition(condition);
        ostmt->getPrimaryKeyFieldName(tablename, pkfield);
        cacheTable->setPKField(pkfield);
        cacheTableList->append(cacheTable);
    }
   // printf("Table %s is not cached\n",tabname);
    fclose(fp);
    delete stmt;
}

DbRetVal getCacheCondition(char *tblName,char *condition, List *cacheTableList)
{
    ListIterator iter=cacheTableList->getIterator();
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

DbRetVal getCacheProjField(char *tblName,char *fieldlist, List *cacheTableList)
{
    ListIterator iter=cacheTableList->getIterator();
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
DbRetVal getCacheField(char *tblName,char *fldName, List *cacheTableList)
{
    ListIterator iter=cacheTableList->getIterator();
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

DbRetVal getPKFieldName(char *tblName, char *pkFldName, List *cacheTableList)
{
    ListIterator iter=cacheTableList->getIterator();
    CacheTableInfo  *cacheTable;
    while(iter.hasElement())
    {
        cacheTable=(CacheTableInfo*)iter.nextElement();
        if(strcmp(cacheTable->getTableName(),tblName)==0){
            strcpy(pkFldName, cacheTable->getPKFieldName());
            return OK;
        }
    }
    return ErrNotExists;
}

/*
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
            if( tdbName == postgres || tdbName == oracle )
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
        case typeVarchar:
        case typeString:
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
}*/
