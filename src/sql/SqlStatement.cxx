/**************************************************************************
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
#include <Statement.h>
#include <SqlStatement.h>
#include <dmllex.h>
#include <Recover.h>

char *lexInput;
extern ParsedData *parsedData;

int yyparse ();
bool SqlConnection::isInit = false;
#if (defined MMDB && defined EMBED)
bool SqlConnection::firstThread = false;
GlobalUniqueID SqlConnection::UID;
#endif
List SqlConnection::connList;

SqlStatement::~SqlStatement()
{
    if (sqlStmtString) { ::free(sqlStmtString); sqlStmtString=NULL;}
    if (isPrepd) { free(); isPrepd = false; }
}

void SqlStatement::setParamValues(AbsSqlStatement *sqlStmt, int parampos, DataType type, int length, void *value)
{
    switch(type)
    {
        case typeInt:
            sqlStmt->setIntParam(parampos, *(int*)value);
            break;
        case typeLong:
            sqlStmt->setLongParam(parampos, *(long*)value);
            break;
        case typeLongLong:
            sqlStmt->setLongLongParam(parampos, *(long long*)value);
            break;
        case typeShort:
            sqlStmt->setShortParam(parampos, *(short*)value);
            break;
        case typeByteInt:
            sqlStmt->setByteIntParam(parampos, *(char*)value);
            break;
        case typeDouble:
            sqlStmt->setDoubleParam(parampos, *(double*)value);
            break;
        case typeFloat:
            sqlStmt->setFloatParam(parampos, *(float*)value);
            break;
        case typeDate:
            sqlStmt->setDateParam(parampos, *(Date*)value);
            break;
        case typeTime:
            sqlStmt->setTimeParam(parampos, *(Time*)value);
            break;
        case typeTimeStamp:
            sqlStmt->setTimeStampParam(parampos, *(TimeStamp*)value);
            break;
        case typeVarchar:
        case typeString:
        {
            sqlStmt->setStringParam(parampos, (char*)value);
            break;
        }
        case typeBinary:
            sqlStmt->setBinaryParam(parampos, (char *) value, length);
            break;
        default:
            printf("unknown type\n");
            break;
    }
    return;
}

void *SqlStatement::fillBindBuffer(TDBInfo tdbName, DataType type, void *&valBuf, int length, int nRecords)
{
    BindBuffer *bBuf = NULL;
    switch(type)
    {
        case typeDate:
            bBuf = new BindBuffer();
            bBuf->csql = valBuf;
            bBuf->type = typeDate;
            bBuf->length = sizeof(DATE_STRUCT);
            bBuf->targetdb = malloc(nRecords * bBuf->length);
            memset(bBuf->targetdb, 0, nRecords * bBuf->length);
            valBuf = bBuf->targetdb;
            break;
        case typeTime:
            bBuf = new BindBuffer();
            bBuf->csql = valBuf;
            bBuf->type = typeTime;
            bBuf->length = sizeof(TIME_STRUCT);
            bBuf->targetdb = malloc(nRecords * bBuf->length);
            memset(bBuf->targetdb, 0, nRecords * bBuf->length);
            valBuf = bBuf->targetdb;
            break;
        case typeTimeStamp:
            bBuf = new BindBuffer();
            bBuf->csql = valBuf;
            bBuf->type = typeTimeStamp;
            bBuf->length = sizeof(TIMESTAMP_STRUCT);
            bBuf->targetdb = malloc(nRecords * bBuf->length);
            memset(bBuf->targetdb, 0, nRecords * bBuf->length);
            valBuf = bBuf->targetdb;
            break;
        case typeLongLong:
        {
            if( tdbName == postgres)
            {
                bBuf = new BindBuffer();
                bBuf->type = typeLongLong;
                bBuf->length = 40;
                bBuf->csql = valBuf;
                int size = nRecords*AllDataType::size(typeString,bBuf->length);
                bBuf->targetdb = malloc(size);
                memset(bBuf->targetdb, 0, size);
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
                bBuf->length = length;
                break;
            }
        default:
            bBuf = new BindBuffer();
            bBuf->type = type;
            bBuf->csql = valBuf;
            bBuf->length = length;
            break;
    }
    bBuf->nullData = (SQLLEN *) malloc(nRecords * sizeof(SQLLEN));
    for (int i = 0; i < nRecords; i++) bBuf->nullData[i] = SQL_NTS;
    return bBuf;
}


List SqlStatement::getTableNameList()
{
    return pData.getTableNameList();
}
SqlStatement::SqlStatement()
{
    innerStmt = NULL;
    sqlCon = NULL;
    stmt = NULL;
    isPrepd = false;
    isCachedStmt=false;
    isMgmtStatement = false;
    sqlStmtString = NULL;
    dontCache = false;
}
void SqlStatement::setConnection(AbsSqlConnection *conn)
{
    sqlCon = (SqlConnection*)conn;
    con = conn;

}
void SqlStatement::setSqlConnection(SqlConnection *conn)
{
    sqlCon = conn;
}

DbRetVal SqlStatement::executeDirect(char *str) 
{
    DbRetVal rv = OK;
    int rows = 0;
    rv = prepare(str);
    if (rv != OK) return rv;
    rv = execute(rows);
    if (rv != OK) return rv;
    return rv;
}

void SqlStatement::setStmtString(char *ststr)
{
    if (sqlStmtString) { ::free(sqlStmtString); sqlStmtString=NULL; }
    sqlStmtString = (char*) malloc(strlen(ststr)+1);
    strcpy(sqlStmtString, ststr);
}

DbRetVal SqlStatement::prepare() 
{ 
    return prepareInt(sqlStmtString); 
}

DbRetVal SqlStatement::prepare(char *stmtstr)
{
   if (sqlStmtString) { ::free(sqlStmtString); sqlStmtString=NULL;}
   sqlStmtString = (char*) malloc(strlen(stmtstr)+1);
   strcpy(sqlStmtString, stmtstr);
   return prepareInt(stmtstr);
}

DbRetVal SqlStatement::prepareInt(char *stmtstr)
{
    DbRetVal rv = OK;
    if (! sqlCon->isConnectionOpen()) {
        printError(ErrNotOpen, "Connection not open");
        return ErrNotOpen;
    }
    SqlStatement *cachedStmt = sqlCon->findInCache(stmtstr);
    if (cachedStmt)
    {
        *this = *cachedStmt;
        this->stmt->setParsedData(&this->pData);
        isCachedStmt=true;
        logFine(Conf::logger,"GOT STMT FROM CACHE: %s %x", stmtstr, cachedStmt);
        return OK;
    }
    // take mutex here
    int ret = ProcessManager::prepareMutex.tryLock(10, 1000);
    if (ret != 0)
    {
        printError(ErrLockTimeOut, "Unable to get prepare mutex");
        return ErrLockTimeOut;
    }

    DatabaseManager *dbMgr = sqlCon->getConnObject().getDatabaseManager();
    if (isPrepared()) free();
    lexInput = stmtstr;
    parsedData = &pData;

    yy_buffer_state *yy_buffer= yy_scan_string(stmtstr);
    int rc = yyparse();
    if (yy_buffer) yy_delete_buffer(yy_buffer);
    if (rc != 0) 
    {
        free();
        parsedData = NULL;
        ProcessManager::prepareMutex.releaseLock(-1, false);
        return ErrSyntaxError;
    }
    if( parsedData->getStmtType() == MgmtStatement)
    {
        isPrepd = true;
        parsedData = NULL;
        isMgmtStatement = true;
        ProcessManager::prepareMutex.releaseLock(-1, false);
        logFine(Conf::logger,"PREPARE: %s %x", stmtstr, stmt);
        return OK;
    }
    stmt = StatementFactory::getStatement(parsedData);
    stmt->setDbMgr(dbMgr);
    stmt->setUserManager(sqlCon->getConnObject().getUserManager(),
            sqlCon->getConnObject().getUserName());
    rv = stmt->resolve();
    if (rv != OK)
    {
        free();
        parsedData = NULL;
        ProcessManager::prepareMutex.releaseLock(-1, false);
        return rv;
    }
    isPrepd = true;
    if (!isCachedStmt && Conf::config.getStmtCacheSize() && !getDontCache()) {
        if (stmt->noOfParamFields() > 0) { 
            isCachedStmt = true; 
            sqlCon->addToCache(this, stmtstr); 
        } else if (Conf::config.useCacheNoParam()) {
            if (parsedData->getCacheWorthy()) {
                isCachedStmt = true; 
                sqlCon->addToCache(this, stmtstr); 
            }
        }
    } else { printf("stmtstring '%s' not cached\n", stmtstr); }
    parsedData = NULL;
    ProcessManager::prepareMutex.releaseLock(-1, false);
    return OK;
}

char*  SqlStatement::getTableName()
{
    return pData.getTableName();
}

bool SqlStatement::isSelect()
{
    if ((pData.getStmtType() == SelectStatement) || (pData.getStmtType() == MetaStatement)) return true;
    return false;
}

bool SqlStatement::isPrepared() { return isPrepd; }

DbRetVal SqlStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    if (! sqlCon->isConnectionOpen()) {
        printError(ErrNotOpen, "Connection not open");
        return ErrNotOpen;
    }
    if (! isPrepared()) {
        printError(ErrNotPrepared, "Statement Not Prepared");
        return ErrNotPrepared;
    }
    if( isMgmtStatement )
    {
        flushCacheStmt();
        logFiner(Conf::logger,"EXECUTE: %x", stmt);
        return OK;
    }
    rv = stmt->execute(rowsAffected);
    if (rv == ErrAlready  && pData.getStmtType() == SelectStatement )  
    { //if previous scan is not closed, close it
        SelStatement *selStmt = (SelStatement*) stmt; 
        selStmt->close(); 
        rv = stmt->execute(rowsAffected); 
    }
    logFiner(Conf::logger,"EXECUTE: %x", stmt);
    return rv;
}

void* SqlStatement::fetch()
{
    if (! sqlCon->isConnectionOpen()) {
        printError(ErrNotOpen, "Connection not open");
        return NULL;
    }
    if (! isPrepared()) {
        printError(ErrNotPrepared, "Statement Not Prepared");
        return NULL;
    }
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        return selStmt->fetch();
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *metaStmt = (MetadataStatement*) stmt; 
        return metaStmt->fetch();
    }
    else  { return NULL;}
}

void* SqlStatement::fetch(DbRetVal &rv)
{
    if (! sqlCon->isConnectionOpen()) {
        printError(ErrNotOpen, "Connection not open");
        rv = ErrNoConnection;
        return NULL; 
    }
    if (! isPrepared()) {
        printError(ErrNotPrepared, "Statement Not Prepared");
        return NULL;
    }
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        return selStmt->fetch(rv);
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *metaStmt = (MetadataStatement*) stmt; 
        return metaStmt->fetch(rv);
    }
    else  { return NULL;}
}

void* SqlStatement::fetchAndPrint(bool SQL)
{
    if (! sqlCon->isConnectionOpen()) {
        printError(ErrNotOpen, "Connection not open");
        return NULL;
    }
    if (! isPrepared()) {
        printError(ErrNotPrepared, "Statement Not Prepared");
        return NULL;
    }
    if (pData.getStmtType() != SelectStatement) return NULL;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return selStmt->fetchAndPrint(SQL);
}

DbRetVal SqlStatement::bindParam(int pos, void* value)
{
    DbRetVal rv = OK;
    rv = stmt->setParam(pos, value);
    return rv;
}

DbRetVal SqlStatement::bindField(int pos, void* value)
{
    DbRetVal rv = OK;
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        return selStmt->setBindField(pos, value);
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *metaStmt = (MetadataStatement*) stmt; 
        return metaStmt->setBindField(pos, value);
    }
    else  { return ErrBadCall;}
}
void* SqlStatement::next()
{
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        return( (void*) selStmt->next() );
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *metaStmt = (MetadataStatement*) stmt; 
        return( (void*) metaStmt->next() );
    }
    else  { return 0;}
}

bool SqlStatement::isFldNull(int pos)
{
    if (pData.getStmtType() != SelectStatement) return 0;
    SelStatement *selStmt = (SelStatement*) stmt;
    return (selStmt->isFldNull(pos));
}
bool SqlStatement::isFldNull(char *name)
{
    if (pData.getStmtType() != SelectStatement) return 0;
    SelStatement *selStmt = (SelStatement*) stmt;
    return (selStmt->isFldNull(name));
}
DbRetVal SqlStatement::close()
{
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        logFinest(Conf::logger,"CLOSE: %x", stmt);
        return selStmt->close();
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *selStmt = (MetadataStatement*) stmt; 
        logFinest(Conf::logger,"CLOSE: %x", stmt);
        return selStmt->close();
    }
    else  { return OK;}
}

void* SqlStatement::getParamValuePtr( int pos )
{
    //if (pData.getStmtType() != SelectStatement) return 0;
    DmlStatement *dmlStmt = (DmlStatement*) stmt;
    return( (void*) dmlStmt->getParamValuePtr( pos ) );
}

char* SqlStatement::getFieldName( int pos )
{
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        return( (char*) selStmt->getFieldName( pos ) );
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *selStmt = (MetadataStatement*) stmt; 
        return( (char*) selStmt->getFieldName( pos ) );
    }
    else  { return 0;}
}

DataType SqlStatement::getFieldType( int pos )
{
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        return( (DataType) selStmt->getFieldType( pos ) );
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *selStmt = (MetadataStatement*) stmt; 
        return( (DataType) selStmt->getFieldType( pos ) );
    }
    else  { return typeUnknown;}
}
int SqlStatement::getFieldLength( int pos )
{
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        return( (int) selStmt->getFieldLength( pos ) );
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *selStmt = (MetadataStatement*) stmt; 
        return( (int) selStmt->getFieldLength( pos ) );
    }
    else  { return 0;}
}

void* SqlStatement::getFieldValuePtr( int pos )
{
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        return( (void*) selStmt->getFieldValuePtr( pos ) );
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *selStmt = (MetadataStatement*) stmt; 
        return( (void*) selStmt->getFieldValuePtr( pos ) );
    }
    else  { return 0;}
}
void* SqlStatement::getFieldValuePtr( char *name )
{
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        return( (void*) selStmt->getFieldValuePtr( name ) );
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *selStmt = (MetadataStatement*) stmt; 
        return( (void*) selStmt->getFieldValuePtr( name ) );
    }
    else  { return NULL;}
}

int SqlStatement::noOfProjFields()
{
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        return selStmt->noOfProjFields();
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *selStmt = (MetadataStatement*) stmt; 
        return selStmt->noOfProjFields();
    }
    else  { return 0;}
}

void SqlStatement::getProjFieldType(int *data)
{
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt;
        return( selStmt->getProjFieldType(data) );
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *selStmt = (MetadataStatement*) stmt;
        return(  selStmt->getProjFieldType(data) );
    }
    

}

int SqlStatement::noOfParamFields()
{
    if (NULL == stmt) return 0;
    else return stmt->noOfParamFields();
}

DbRetVal SqlStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    DbRetVal rv = OK;
    if (pData.getStmtType() == SelectStatement ) {
        SelStatement *selStmt = (SelStatement*) stmt; 
        rv = selStmt->getProjFldInfo(projpos, fInfo);
    }
    else if(pData.getStmtType() == MetaStatement){
        MetadataStatement *selStmt = (MetadataStatement*) stmt; 
        rv = selStmt->getProjFldInfo(projpos, fInfo);
    } else  { return ErrBadCall;}
    return rv;
}

DbRetVal SqlStatement::getParamFldInfo (int parampos, FieldInfo *&fInfo)
{
    DbRetVal rv = OK;
    if (pData.getStmtType() ==SelectStatement ||
        pData.getStmtType() ==InsertStatement ||
        pData.getStmtType() ==UpdateStatement ||
        pData.getStmtType() ==DeleteStatement)
    {
 
        DmlStatement *dmlStmt = (DmlStatement*) stmt; 
        rv = dmlStmt->getParamFldInfo(parampos, fInfo);
    }
    return rv;
}

DbRetVal SqlStatement::free()
{
    logFinest(Conf::logger,"FREE: %x", stmt);
    if (isCachedStmt) {
        stmt=NULL;
        pData.init();
        isPrepd = false;
        if (sqlStmtString) {
            sqlCon->setStmtNotInUse(sqlStmtString);
            ::free(sqlStmtString); 
            sqlStmtString=NULL; 
        }
        isCachedStmt = false;
        return OK;
    }
    if(stmt) delete stmt;
    stmt = NULL;
    pData.reset();
    isMgmtStatement = false;
    isPrepd = false;
    isCachedStmt = false;
    if (sqlStmtString) { ::free(sqlStmtString); sqlStmtString=NULL; }
    return OK;
}

void SqlStatement::setNull(int pos)
{
    stmt->setNull(pos);
}
void SqlStatement::setShortParam(int paramPos, short value)
{
    stmt->setShortParam(paramPos, value);
}
void SqlStatement::setIntParam(int paramPos, int value)
{
    stmt->setIntParam(paramPos, value);
}
void SqlStatement::setLongParam(int paramPos, long value)
{
    stmt->setLongParam(paramPos, value);
}
void SqlStatement::setLongLongParam(int paramPos, long long value)
{
    stmt->setLongLongParam(paramPos, value);
}
void SqlStatement::setByteIntParam(int paramPos, ByteInt value)
{
    stmt->setByteIntParam(paramPos, value);
}
void SqlStatement::setFloatParam(int paramPos, float value)
{
    stmt->setFloatParam(paramPos, value);
}
void SqlStatement::setDoubleParam(int paramPos, double value)
{
    stmt->setDoubleParam(paramPos, value);
}
void SqlStatement::setStringParam(int paramPos, char *value)
{
    stmt->setStringParam(paramPos, value);
}
void SqlStatement::setDateParam(int paramPos, Date value)
{
    stmt->setDateParam(paramPos, value);
}
void SqlStatement::setTimeParam(int paramPos, Time value)
{
    stmt->setTimeParam(paramPos, value);
}
void SqlStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    stmt->setTimeStampParam(paramPos, value);
}
void SqlStatement::setBinaryParam(int paramPos, void *value, int length)
{
    stmt->setBinaryParam(paramPos, value, length);
}
int SqlStatement::getFldPos(char *name)
{
    return stmt->getFldPos(name);
}
long long SqlStatement::getLastInsertedVal(DbRetVal &rv)
{
   return stmt->getLastInsertedVal(rv);
}
List SqlStatement::getAllTableNames(DbRetVal &ret)
{
    DatabaseManager *dbMgr = NULL;
    List tbNmList;
    dbMgr=sqlCon->getConnObject().getDatabaseManager();
    int rv = ret;
    if(dbMgr != NULL) tbNmList = dbMgr->getAllTableNames(&rv);
    ret = (DbRetVal) rv;
    return tbNmList;
}

List SqlStatement::getAllUserNames(DbRetVal &ret)
{
    UserManager *urMgr = NULL;
    List urNmList;
    urMgr=sqlCon->getConnObject().getUserManager();
    int rv = ret;
    if(urMgr != NULL)
        urNmList = urMgr->getAllUserNames(&rv);
    ret = (DbRetVal) rv;
    return urNmList;
}
List SqlStatement::getFieldNameList(const char *tblName, DbRetVal &rv)
{
    List fldNameList;
    if (isPrepared()) {
        fldNameList = stmt->getFieldNameList(tblName, rv);
        return fldNameList;
    }
    DatabaseManager *dbMgr = sqlCon->getConnObject().getDatabaseManager();
    Table *table = dbMgr->openTable(tblName);
    if (NULL == table) {
        List dummyList;
        printError(ErrLockTimeOut, "Unable to open table %s", tblName);
        return dummyList;
    }
    fldNameList = table->getFieldNameList();
    dbMgr->closeTable(table);
    return fldNameList;
}
DbRetVal SqlStatement::getFieldInfo(const char *tblName, const char *fldName, FieldInfo *&info)
{
    DbRetVal rv = OK;
    if (isPrepared()) {
        rv = stmt->getFieldInfo(tblName, fldName, info);
        return rv;
    }
    DatabaseManager *dbMgr = sqlCon->getConnObject().getDatabaseManager();
    Table *table = dbMgr->openTable(tblName);
    if (NULL == table) {
        printError(ErrLockTimeOut, "Unable to open table %s", tblName);
        return ErrLockTimeOut;
    }
    rv = table->getFieldInfo(fldName, info);
    dbMgr->closeTable(table);
    return rv;
}
void SqlStatement::setLoading(bool flag)
{
    if (pData.getStmtType() == InsertStatement||
        pData.getStmtType() == UpdateStatement||
        pData.getStmtType() == DeleteStatement)
    {
        DmlStatement *dmlStmt = (DmlStatement*) stmt;
        dmlStmt->setLoading(flag);
    }
    return;
}

int SqlStatement::getNoOfPagesForTable(char *tblName)
{
    DatabaseManager *dbMgr = sqlCon->getConnObject().getDatabaseManager();
    DatabaseManagerImpl *dbMgrImpl = (DatabaseManagerImpl *)dbMgr;
    return dbMgrImpl->getNoOfPagesForTable(tblName);
}

DbRetVal SqlStatement::loadRecords(char *tblName, void *buf)
{
    DatabaseManager *dbMgr = sqlCon->getConnObject().getDatabaseManager();
    DatabaseManagerImpl *dbMgrImpl = (DatabaseManagerImpl *)dbMgr;
    return dbMgrImpl->loadRecords(tblName, (char *) buf);
}

DbRetVal SqlStatement::pasteRecords(char *tblName, void *buffer)
{
    DatabaseManager *dbMgr = sqlCon->getConnObject().getDatabaseManager();
    DatabaseManagerImpl *dbMgrImpl = (DatabaseManagerImpl *)dbMgr;
    return dbMgrImpl->pasteRecords(tblName, buffer);
}
void SqlStatement::flushCacheStmt()
{
    return sqlCon->flushCacheStmt();
}

void SqlStatement::resetStmtString() {
    sqlStmtString=NULL; 
}
//-------------------------------------------------------------------

static void sigTermHandler(int sig)
{
    ListIterator iter= SqlConnection::connList.getIterator();
    SqlConnection *conn = NULL;
    while (iter.hasElement())
    {
        conn = (SqlConnection*) iter.nextElement();
        conn->flushCacheStmt();
        if (conn->isConnectionOpen()) conn->disconnect(); 
    }
    exit(0);
}

DbRetVal SqlConnection::connect (char *user, char * pass) 
{
    DbRetVal ret = conn.open(user, pass);
    if (ret != OK) return ret;
    if (ret == OK) isConnOpen = true;
    if (!isInit) initialize();
    connList.append(this);
    DbRetVal rv = OK;
#if (defined MMDB && EMBED)
    os::signal(SIGINT, sigTermHandler);
    os::signal(SIGTERM, sigTermHandler);
    if (Conf::config.useDurability() && !firstThread) {
        Recovery recovery;
        rv = recovery.recoverCsqlDB(this);
        //rv = recoverCsqlDB(this);
        if (rv != OK) {
            printError(ErrSysInternal, "Recovery Failed");
            return rv;
        }
        firstThread = true;
    }
    rollback(); //for drop table execute in redo log
#endif
    return ret;
}

void SqlConnection::flushCacheStmt()
{
    ListIterator iter = cachedStmts.getIterator();
    while (iter.hasElement()) {
        CachedStmtNode* node = (CachedStmtNode*) iter.nextElement();
        //do not delete when the statement is currently in use.
        //otherwise it leads to illegal memory access when application 
        //calls any method on this statement
        if (node->inUse) continue;
        //if (node->inUse) node->inUse = 0;
        free(node->sqlString);
        node->sqlStmt->setCachedStmt(false);
        node->sqlStmt->free();
        delete node->sqlStmt;
        delete node;
    }
    cachedStmts.reset();
    return;
}

void SqlConnection::setStmtNotInUse(char *stmtstr)
{
    ListIterator iter = cachedStmts.getIterator();
    int inputStmtLen = strlen(stmtstr);
    CachedStmtNode *node = NULL;
    while ((node = (CachedStmtNode*)iter.nextElement()) != NULL)
    {
        if (node->stmtLength == inputStmtLen)
        {
           if (0 == strcmp(node->sqlString, stmtstr))
           {
               node->inUse =0;
               return;
           }
        }
    }

}
SqlStatement* SqlConnection::findInCache(char *stmtstr)
{
    ListIterator iter = cachedStmts.getIterator();
    int inputStmtLen = strlen(stmtstr);
    CachedStmtNode *node = NULL;
    while ((node = (CachedStmtNode*)iter.nextElement()) != NULL)
    {
        if (node->stmtLength == inputStmtLen)
        {
           if (0 == strcmp(node->sqlString, stmtstr))
           {
               logFiner(Conf::logger, "Statement Retrieved From Cache %x\n", 
                                      node->sqlStmt);
               node->hits++;
               node->inUse = 1;
               return node->sqlStmt;
           }
        }
    }
    return NULL;
}

void SqlConnection::addToCache(SqlStatement *sqlStmt, char* stmtString)
{
    SqlStatement *stmt = new SqlStatement();
    *stmt= *sqlStmt;
    CachedStmtNode *node = new CachedStmtNode();
    node->sqlStmt = stmt;
    node->stmtLength  = strlen(stmtString);
    node->sqlString = (char*)malloc(node->stmtLength+1);
    node->inUse=1;
    strcpy(node->sqlString, stmtString);
    if (cachedStmts.size() >= Conf::config.getStmtCacheSize())
    {
        removeLeastUsed();
    }
    node->sqlStmt->resetStmtString();
    cachedStmts.append(node);
    logFiner(Conf::logger, "Statement added To Cache %x\n", node->sqlStmt);
    logFinest(Conf::logger, "Statement added To Cache %s\n", node->sqlString);
    return ;
}

void SqlConnection::removeLeastUsed()
{
    ListIterator iter = cachedStmts.getIterator();
    CachedStmtNode *node = NULL, *toRemove =NULL;
    int lowHits = 0;
    bool firstCall = true;
    while((node = (CachedStmtNode*) iter.nextElement()) != NULL)
    {
        if (firstCall) { 
            firstCall = false; 
            lowHits = node->hits; 
            toRemove = node; //if cache size is 1
            continue; 
        }
        if (lowHits >= node->hits) toRemove = node;
    }
    cachedStmts.remove(toRemove);
    //TODO::check whether there is memory leak for list elements
    logFiner(Conf::logger, "Statement removed from Cache %x\n", toRemove->sqlStmt);
    logFinest(Conf::logger, "Statement removed from Cache %s\n", toRemove->sqlString);
    delete toRemove; toRemove = NULL;
    return;
}

SqlConnection::~SqlConnection()
{
    flushCacheStmt();
    if (isConnOpen) disconnect();
    innerConn = NULL;
}

static void sigUsr1Handler(int sig)
{
    ListIterator iter= SqlConnection::connList.getIterator();
    SqlConnection *conn = NULL;
    while (iter.hasElement())
    {
        conn = (SqlConnection*) iter.nextElement();
        conn->flushCacheStmt();
    }
    os::signal(SIGCSQL1, sigUsr1Handler);
    return;
}

static void exithandler(void)
{
    ListIterator iter= SqlConnection::connList.getIterator();
    SqlConnection *conn = NULL;
    while (iter.hasElement())
    {
        conn = (SqlConnection*) iter.nextElement();
        conn->flushCacheStmt();
        conn->disconnect();
    }
}
void SqlConnection::displayStmtCache()
{
    ListIterator iter = cachedStmts.getIterator();
    CachedStmtNode *node = NULL;
    printf("STATEMENT CACHE START \n");
    while ((node = (CachedStmtNode*)iter.nextElement()) != NULL)
    {
        node->display();
    }
    printf("STATEMENT CACHE END\n");
}

void SqlConnection::initialize()
{
    os::signal(SIGCSQL1, sigUsr1Handler);
#if (defined MMDB && defined EMBED)
    os::atexit(exithandler);
#endif
    isInit = true;
}
