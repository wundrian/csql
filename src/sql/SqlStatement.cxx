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
#include <Statement.h>
#include <SqlStatement.h>
#include <dmllex.h>

char *lexInput;
extern ParsedData *parsedData;

int yyparse ();

SqlStatement::~SqlStatement()
{
    if (isPrepd) { free(); isPrepd = false; }
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

DbRetVal SqlStatement::prepare(char *stmtstr)
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
        logFine(Conf::logger,"GOT STMT FROM CACHE: %s %x", stmtstr, cachedStmt);
        return OK;
    }
    // take mutex here
    DatabaseManager *dbMgr = sqlCon->getConnObject().getDatabaseManager();
    Database *sysdb = ((DatabaseManagerImpl *)dbMgr)->sysDb();
    int tries = Conf::config.getMutexRetries();
    struct timeval timeout;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();

    while (true) {
        rv = sysdb->getPrepareStmtMutex();    
        if (rv == OK) break;
        tries--;
        if (tries == 0) {
            printError(rv, 
                        "Unable to get prepare statement mutex after %d tries", Conf::config.getMutexRetries()); 
            return rv;
        }
        os::select(0, 0, 0, 0, &timeout);
    } 
        
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
        //yyrestart(yyin);
        sysdb->releasePrepareStmtMutex();    
        return ErrSyntaxError;
    }
    stmt = StatementFactory::getStatement(parsedData);
    stmt->setDbMgr(dbMgr);
    if( parsedData->getStmtType() == UserStatement)
    {
        UserManager* userMgr = sqlCon->getConnObject().getUserManager();
        UserTblStatement *ustmt = (UserTblStatement *)stmt;
        ustmt->setUserManager(userMgr,sqlCon->getConnObject().getUserName());      
    }
    rv = stmt->resolve();
    if (rv != OK)
    {
        free();
        parsedData = NULL;
        //yyrestart(yyin);
        sysdb->releasePrepareStmtMutex();    
        return rv;
    }
    parsedData = NULL;
    //yyrestart(yyin);
    sysdb->releasePrepareStmtMutex();    
    logFine(Conf::logger,"PREPARE: %s %x", stmtstr, stmt);
    isPrepd = true;
    if (stmt->noOfParamFields()>0) { 
        isCachedStmt = true; 
        sqlCon->addToCache(this, stmtstr); 
        return OK;
    }
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
    return stmt->noOfParamFields();
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
        return OK;
    }
    delete stmt;
    stmt = NULL;
    pData.reset();
    isPrepd = false;
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
List SqlStatement::getAllTableNames(DbRetVal &ret)
{
    DatabaseManager *dbMgr = NULL;
    List tbNmList;
    dbMgr=sqlCon->getConnObject().getDatabaseManager();
    int rv = ret;
    if(dbMgr != NULL)
    tbNmList = dbMgr->getAllTableNames(&rv);
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
List SqlStatement::getFieldNameList(const char *tblName)
{
    DatabaseManager *dbMgr = sqlCon->getConnObject().getDatabaseManager();
    Table *table = dbMgr->openTable(tblName);
    List fldNameList = table->getFieldNameList();
    dbMgr->closeTable(table);
    return fldNameList;
}
DbRetVal SqlStatement::getFieldInfo(const char *tblName, const char *fldName, FieldInfo *&info)
{
    DatabaseManager *dbMgr = sqlCon->getConnObject().getDatabaseManager();
    Table *table = dbMgr->openTable(tblName);
    DbRetVal rv = table->getFieldInfo(fldName, info);
    dbMgr->closeTable(table);
    return OK;
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

//-------------------------------------------------------------------
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
    strcpy(node->sqlString, stmtString);
    cachedStmts.append(node);
    logFiner(Conf::logger, "Statement added To Cache %x\n", node->sqlStmt);
    return ;
}
SqlConnection::~SqlConnection()
{
    innerConn = NULL;
    ListIterator iter = cachedStmts.getIterator();
    while (iter.hasElement()) {
        CachedStmtNode* node = (CachedStmtNode*) iter.nextElement();
        free(node->sqlString);
        node->sqlStmt->setCachedStmt(false);
        node->sqlStmt->free();
        delete node->sqlStmt;
        delete node;
    }
    cachedStmts.reset();
    if (isConnOpen) disconnect();
}

