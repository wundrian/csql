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
#include <TableConfig.h>
#include <SqlNetworkHandler.h>
#include <AbsSqlConnection.h>
#include <SqlConnection.h>
#include <SqlOdbcConnection.h>
#include <AbsSqlStatement.h>
#include <SqlStatement.h>
#include <SqlOdbcStatement.h>
#include <SqlLogStatement.h>
#include <Parser.h>

bool SqlNetworkHandler::isSqlLogNeeded;
List SqlNetworkHandler::stmtList;
List SqlNetworkHandler::tableNameList;
AbsSqlConnection* SqlNetworkHandler::conn;
SqlApiImplType SqlNetworkHandler::type;
int SqlNetworkHandler::stmtID;
int SqlNetworkHandler::sockfd;

void *SqlNetworkHandler::process(PacketHeader &header, char *buffer)
{
    DbRetVal rv = OK;
    char *ptr = NULL;
    void *rpkt = NULL;
    switch(header.packetType)
    {
        case SQL_NW_PKT_CONNECT:
            rpkt = processSqlConnect(header, buffer);
            break;
        case SQL_NW_PKT_EXECDIRECT:
            rpkt = processSqlExecuteDirect(header, buffer);
            break;
        case SQL_NW_PKT_PREPARE:
            rpkt = processSqlPrepare(header, buffer);
            break;
        case SQL_NW_PKT_EXECUTE:
            rpkt = processSqlExecute(header, buffer);
            break;
        case SQL_NW_PKT_FETCH:
            rpkt = processSqlFetch(header);
            break;
        case SQL_NW_PKT_COMMIT:
            rpkt = processSqlCommit(header, buffer);
            break;
        case SQL_NW_PKT_ROLLBACK:
            rpkt = processSqlRollback(header, buffer);
            break;
        case SQL_NW_PKT_DISCONNECT:
            rpkt = processSqlDisconnect(header);
            break;
        case SQL_NW_PKT_FREE:
            rpkt = processSqlFree(header, buffer);
            break;
        case SQL_NW_PKT_SHOWTABLES:
            rpkt = processSqlShowTables(header, buffer);
            break;
        case SQL_NW_PKT_ISTABLEPRESENT:
            rpkt = processSqlIsTablePresent(header, buffer);
            break;
        case SQL_NW_PKT_GETRECORDS:
            rpkt =  processSqlLoadRecords(header, buffer);
            break;
        case SQL_NW_PKT_LASTAIVAL:
            rpkt = processSqlLastAutoIncrementVal(header);
            break;
    }
    if (rpkt != NULL) sendResponse(rpkt);
    return rpkt;
}

DbRetVal SqlNetworkHandler::sendResponse(void *rpkt)
{
    size_t numbytes = os::send(sockfd, rpkt, sizeof(ResponsePacket), 0);
    if (numbytes == -1) {
        printError(ErrOS, "Error writing to socket\n");
        closeConnection();
        exit(1);
    }
    return OK;
}

DbRetVal SqlNetworkHandler::closeConnection()
{
    conn->rollback();
    return conn->disconnect();
} 

void * SqlNetworkHandler::processSqlConnect(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    printDebug(DM_Network, "Processing CONNECT");
    SqlPacketConnect *pkt = new SqlPacketConnect();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    type = (SqlApiImplType) pkt->sqlApiImplType;
    isSqlLogNeeded = (Conf::config.useDurability() || (Conf::config.useCache() 
                               && Conf::config.getCacheMode() == ASYNC_MODE ));
    conn = createConnection(type);   
    char *ptr = (char *) &rpkt->retVal;
    DbRetVal rv=conn->connect(pkt->userName, pkt->passWord);
    if (rv != OK) {
        //*ptr = 0; 
        rpkt->errRetVal = rv;
        fillErrorString(rpkt);
        delete pkt;
        return rpkt;
    }
    if (rv == OK) { 
        //*ptr = 1; 
        rv = conn->beginTrans(); 
        delete pkt;
        return rpkt; 
    }
}

void * SqlNetworkHandler::processSqlDisconnect(PacketHeader &header)
{
    DbRetVal rv = conn->rollback();
    rv = conn->disconnect();
    ResponsePacket *rpkt = new ResponsePacket();
    char *ptr = (char *) &rpkt->retVal;
    //*ptr = 1;
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}

void* SqlNetworkHandler::processSqlExecuteDirect(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    rpkt->isSelect = false;
    char *retval = (char *) &rpkt->retVal;
    SqlPacketPrepare *pkt = new SqlPacketPrepare();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    printDebug(DM_Network, "EXECDIRECT %s\n", pkt->stmtString);
    AbsSqlStatement *sqlstmt = createStatement(type);
    sqlstmt->setConnection(conn);
    NetworkStmt *nwStmt = new NetworkStmt();
    nwStmt->stmtID = ++stmtID; 
    printDebug(DM_Network, "Statement string %s\n", pkt->stmtString);
    nwStmt->stmt = sqlstmt;
    DbRetVal rv = sqlstmt->executeDirect(pkt->stmtString);
    delete pkt;
    if (rv != OK)
    {
        printError(ErrSysInit, "ExecuteDirect failed\n");
        rpkt->errRetVal = rv;
        fillErrorString(rpkt);
        if (rpkt->errorString[0] == '\0') 
            strcpy(rpkt->errorString, "Prepare failed.");
        delete nwStmt;
        delete sqlstmt;
        return rpkt;
    }
  
    stmtList.append(nwStmt);
    rpkt->stmtID = nwStmt->stmtID;
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}

void* SqlNetworkHandler::processSqlPrepare(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    rpkt->isSelect = false;
    char *retval = (char *) &rpkt->retVal;
    SqlPacketPrepare *pkt = new SqlPacketPrepare();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    printDebug(DM_Network, "PREPARE %s\n", pkt->stmtString);
    AbsSqlStatement *sqlstmt = createStatement(type);
    sqlstmt->setConnection(conn);
    NetworkStmt *nwStmt = new NetworkStmt();
    nwStmt->stmtID = ++stmtID; 
    printDebug(DM_Network, "Statement string %s\n", pkt->stmtString);
    nwStmt->stmt = sqlstmt;
    DbRetVal rv = sqlstmt->prepare(pkt->stmtString);
    delete pkt;
    if (rv != OK)
    {
        printError(ErrSysInit, "statement prepare failed\n");
        rpkt->errRetVal = rv;
        fillErrorString(rpkt);
        if (rpkt->errorString[0] == '\0') 
            strcpy(rpkt->errorString, "Prepare failed.");
        delete nwStmt;
        delete sqlstmt;
        return rpkt;
    }
    //TODO: need to change retVal name
    ResultSetPlan plan = sqlstmt->getResultSetPlan();
    *retval = plan;
    
    int param = sqlstmt->noOfParamFields();
    int proj = sqlstmt->noOfProjFields();
    BindSqlField *bindField = NULL;
    BindSqlProjectField *projField = NULL;
    //populate paramList
    FieldInfo * fInfo = new FieldInfo();
    for (int i = 0; i < param; i++) {
        bindField = new BindSqlField();
        sqlstmt->getParamFldInfo(i + 1, fInfo);
        strcpy(bindField->fName, fInfo->fldName);
        bindField->type = fInfo->type;
        bindField->length = fInfo->length;
        bindField->offset = fInfo->offset;
        strcpy(bindField->defaultValueBuf, fInfo->defaultValueBuf);
        bindField->isNull = fInfo->isNull;
        bindField->isPrimary = fInfo->isPrimary;
        bindField->isDefault = fInfo->isDefault;
        bindField->isUnique = fInfo->isUnique;
        bindField->isUnique = fInfo->isUnique;
        //bindField->value = AllDataType::alloc(bindField->type, bindField->length);
        bindField->value = NULL;
        nwStmt->paramList.append(bindField);
    }
    delete fInfo; 
    FieldInfo *fldInfo = new FieldInfo();
    for (int i = 0; i < proj; i++) {
        projField = new BindSqlProjectField();
        sqlstmt->getProjFldInfo(i + 1, fldInfo);
        strcpy(projField->fName, fldInfo->fldName);
        projField->type = fldInfo->type;
        projField->length = fldInfo->length;
        projField->offset = fldInfo->offset;
        strcpy(projField->defaultValueBuf, fldInfo->defaultValueBuf);
        projField->aType = fldInfo->aType;
        projField->isNull = fldInfo->isNull;
        projField->isPrimary = fldInfo->isPrimary;
        projField->isDefault = fldInfo->isDefault;
        projField->isUnique = fldInfo->isUnique;
        projField->value = AllDataType::alloc(projField->type, projField->length);
        memset(projField->value, 0, projField->length);
        nwStmt->projList.append(projField);
    }
    delete fldInfo; 
    stmtList.append(nwStmt);
    if(sqlstmt->isSelect()) rpkt->isSelect = true;
    if (param) *(retval+2) = 1;
    if (proj) *(retval+3) = 1;
    rpkt->stmtID = nwStmt->stmtID;
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}

void * SqlNetworkHandler::processSqlExecute(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    char *retval = (char *) &rpkt->retVal;
    SqlPacketExecute *pkt = new SqlPacketExecute();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->setStatementList(stmtList);
    pkt->unmarshall();
    printDebug(DM_Network, "EXECUTE %d\n", pkt->stmtID);
    rpkt->stmtID = pkt->stmtID;
    ListIterator stmtIter = stmtList.getIterator();
    NetworkStmt *stmt;
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       //TODO::Also check the srcNetworkID
       if (stmt->stmtID == pkt->stmtID ) break;
    }
    AbsSqlStatement *sqlstmt = stmt->stmt;
    int rows = 0;
    char *nullInfo = NULL;
    if (pkt->noParams) nullInfo = pkt->getNullInfo();
    for (int i=0; i < pkt->noParams; i++) {
        BindSqlField *bindField = (BindSqlField *) stmt->paramList.get(i+1);
        if (nullInfo[i]) sqlstmt->setNull(i+1);
        else setParamValues(sqlstmt, i+1, bindField->type, bindField->length, (char *)bindField->value);
    }
    //SqlStatement *st = (SqlStatement *)sqlstmt;
    if(sqlstmt->isSelect()) { 
        int noProj = stmt->projList.size();
        for (int i=0; i < noProj; i++) {
            BindSqlProjectField *prjFld = (BindSqlProjectField *) stmt->projList.get(i+1);
            sqlstmt->bindField(i+1, prjFld->value);
        }
    }
    delete pkt;
    DbRetVal rv = sqlstmt->execute(rows);
    if (rv != OK) { 
        rpkt->errRetVal = rv;
        fillErrorString(rpkt);
        return rpkt; 
    }
    rpkt->rows = rows;
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}

void * SqlNetworkHandler::processSqlFetch(PacketHeader &header)
{
    ListIterator stmtIter = stmtList.getIterator();
    NetworkStmt *stmt;
    SqlPacketResultSet *rspkt = new SqlPacketResultSet();
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       //TODO::Also check srcNetworkID
       if (stmt->stmtID == header.stmtID ) break;
    }
    printDebug(DM_Network, "FETCH STMTID: %d", stmt->stmtID);
    AbsSqlStatement *sqlstmt = stmt->stmt;
    void *data=NULL;
    int len=1;
    DbRetVal rv = OK;
    if ((data = sqlstmt->fetch(rv)) != NULL && rv == OK) {
        len = 0;//means record is there
    }
    else if (data == NULL && rv == OK) {
        sqlstmt->close();
        len =1; //end of resultset
    }
    else { 
        len=2;//error
    }
    rspkt->noProjs = stmt->projList.size();
    // set null info for all the fetched field values in projection list
    int nullInfoLen = os::align(rspkt->noProjs);
    char *nullInfo = (char *) malloc(nullInfoLen);
    memset(nullInfo, 0, nullInfoLen);
    char *ptr = nullInfo;
    ListIterator it = stmt->projList.getIterator();
    while (it.hasElement()) {
        BindSqlProjectField *prjFld = (BindSqlProjectField *) it.nextElement();
        if (sqlstmt->isFldNull(prjFld->fName)) *ptr = 1;
        ptr++;
    }
    rspkt->setNullInfo(nullInfo);
    rspkt->setProjList(stmt->projList);
    rspkt->marshall();
    if (rv != OK) { printf("marshall failed\n"); }
    
    if(len == 0) len = rspkt->getBufferSize();
    int numbytes = os::send(sockfd, &len , 4, 0);
    if (len == 1 || len == 2) { delete rspkt; ::free (nullInfo); return NULL; }
    int dummy =0;
    //numbytes = os::recv(sockfd, &dummy, 4, 0);
    numbytes = os::send(sockfd,rspkt->getMarshalledBuffer(),  
                           rspkt->getBufferSize(), 0);
    delete rspkt;
    if (numbytes == -1) {
       printf("Error in sending the row to the client\n");
       ::free (nullInfo);
       sqlstmt->free();
       delete sqlstmt; sqlstmt= NULL;
       conn->disconnect();
       exit(1);
    }
    ::free (nullInfo);
    return NULL;
}

void * SqlNetworkHandler::processSqlFree(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    char *retval = (char *) &rpkt->retVal;
    SqlPacketFree *pkt = new SqlPacketFree();
    pkt->setBuffer(buffer);
    pkt->unmarshall();
    rpkt->stmtID = pkt->stmtID;
    ListIterator stmtIter = stmtList.getIterator();
    NetworkStmt *stmt = NULL;
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       //TODO::Also check teh srcNetworkID
       if (stmt->stmtID == pkt->stmtID ) break;
    }
    if (stmt == NULL)
    {
        printError(ErrWarning, "Statement already freed.");
        delete pkt;
        rpkt->errRetVal = ErrAlready;
        return rpkt;
    }
    AbsSqlStatement *sqlstmt = stmt->stmt;
    if (sqlstmt) sqlstmt->free();
    ListIterator itprm = stmt->paramList.getIterator();
    BindSqlField *fld = NULL;
    while((fld = (BindSqlField *) itprm.nextElement()) != NULL) {
        //if (fld->value) free(fld->value); memory never allocated for this
        delete fld;
    }
    stmt->paramList.reset();
    ListIterator itprj = stmt->projList.getIterator();
    BindSqlProjectField *pfld = NULL;
    while((pfld = (BindSqlProjectField *) itprj.nextElement()) != NULL) {
       if (pfld->value) free(pfld->value);
       delete pfld;       
    }
    stmt->projList.reset();
    delete stmt->stmt;
    stmt->stmt = NULL;
    stmtList.remove(stmt);
    delete stmt;
    stmt= NULL;
    delete pkt;
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}


void * SqlNetworkHandler::processSqlCommit(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    char *retval = (char *) &rpkt->retVal;
    DbRetVal rv = conn->commit();
    if (rv != OK) {
        rpkt->errRetVal = rv;
        strcpy(rpkt->errorString, "Commit failure\n");
        return rpkt;
    }
    rv = conn->beginTrans();
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}

void *SqlNetworkHandler::processSqlRollback(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    char *retval = (char *) &rpkt->retVal;
    DbRetVal rv = conn->rollback();
    if (rv != OK) {
        rpkt->errRetVal = rv;
        strcpy(rpkt->errorString, "Rollback failure\n");
        return rpkt;
    }
    rv = conn->beginTrans();
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}

void SqlNetworkHandler::setParamValues(AbsSqlStatement *stmt, int parampos, DataType type,
                    int length, char *value)
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
        case typeVarchar:
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

AbsSqlConnection * SqlNetworkHandler::createConnection(SqlApiImplType type)
{
    AbsSqlConnection *con = NULL;
    switch(type) {
        case CSqlNetwork:
            con = SqlFactory::createConnection(CSql);
            break;
        case CSqlNetworkAdapter:
            con = SqlFactory::createConnection(CSqlAdapter);
            break;
        case CSqlNetworkGateway:
            con = SqlFactory::createConnection(CSqlGateway);
            break;
        default:
            return NULL;
    }
    return con;
}

AbsSqlStatement * SqlNetworkHandler::createStatement(SqlApiImplType type)
{
    AbsSqlStatement *stmt = NULL;
    switch(type) {
        case CSqlNetwork:
            stmt = SqlFactory::createStatement(CSql);
            break;
        case CSqlNetworkAdapter:
            stmt = SqlFactory::createStatement(CSqlAdapter);
            break;
        case CSqlNetworkGateway:
            stmt = SqlFactory::createStatement(CSqlGateway);
            break;
        default:
            return NULL;
    }
    return stmt;
}

void * SqlNetworkHandler::processSqlShowTables(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    rpkt->isSelect = false;
    char *retval = (char *) &rpkt->retVal;
    AbsSqlStatement *sqlstmt = createStatement(type);
    sqlstmt->setConnection(conn);
    DbRetVal rv = OK;
    tableNameList = sqlstmt->getAllTableNames(rv);
    rpkt->errRetVal = rv;
    rpkt->rows = tableNameList.size();
    strcpy(rpkt->errorString, "Success");
    delete sqlstmt;
    return rpkt;
}

//only csql connection asks for this with or without durability.
void *SqlNetworkHandler::processSqlIsTablePresent(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    rpkt->isSelect = false;
    SqlPacketIsTablePresent *pkt = new SqlPacketIsTablePresent();
    pkt->setBuffer(buffer);
    pkt->unmarshall();
    SqlStatement *sqlstmt = new SqlStatement();
    SqlConnection *sqlcon = NULL;
    if (isSqlLogNeeded) sqlcon = (SqlConnection *) conn->getInnerConnection();
    else sqlcon = (SqlConnection *) conn;
    sqlstmt->setSqlConnection(sqlcon);
    DbRetVal rv = OK; bool found = false;
    tableNameList = sqlstmt->getAllTableNames(rv);
    ListIterator it = tableNameList.getIterator();
    while (it.hasElement()) {
        Identifier *elem = (Identifier *) it.nextElement();
        if (strcmp(elem->name, pkt->tblName) == 0) {
            found = true;
            break;
        }
    }
    rpkt->errRetVal = rv;
    if (!found) {
        rpkt->errRetVal = ErrNotFound; 
        strcpy(rpkt->errorString, "Table Not found.");
    }
    ListIterator tblIter = SqlNetworkHandler::tableNameList.getIterator();
    while (tblIter.hasElement()) delete tblIter.nextElement();
    SqlNetworkHandler::tableNameList.reset();
    delete pkt;
    delete sqlstmt;
    return rpkt;
}

//only csql connection asks for this with or without durability.
void *SqlNetworkHandler::processSqlLoadRecords(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    rpkt->isSelect = false;
    char *retval = (char *) &rpkt->retVal;
    SqlPacketGetRecords *pkt = new SqlPacketGetRecords();
    pkt->setBuffer(buffer);
    pkt->unmarshall();
    SqlStatement *sqlstmt = new SqlStatement();
    SqlConnection *sqlcon = NULL;
    if (isSqlLogNeeded) sqlcon = (SqlConnection *) conn->getInnerConnection();
    else sqlcon = (SqlConnection *) conn;
    sqlstmt->setSqlConnection(sqlcon);
    DbRetVal rv = OK;
    int pages = sqlstmt->getNoOfPagesForTable(pkt->tblName);
    printDebug(DM_Network, "No of pages to be shipped: %d", pages);
    rpkt->rows = pages;
    strcpy(rpkt->errorString, pkt->tblName);
    delete pkt;
    delete sqlstmt;
    return rpkt;
}

void *SqlNetworkHandler::processSqlLastAutoIncrementVal(PacketHeader &header)
{
    ListIterator stmtIter = stmtList.getIterator();
    NetworkStmt *stmt;
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       if (stmt->stmtID == header.stmtID ) break;
    }
    AbsSqlStatement *sqlstmt = stmt->stmt;
    ResponsePacket *rpkt = new ResponsePacket();
    DbRetVal rv = OK;
    rpkt->lastAutoIncVal = sqlstmt->getLastInsertedVal(rv);
    return rpkt;
}

void SqlNetworkHandler::fillErrorString(ResponsePacket *rpkt)
{
    switch(rpkt->errRetVal) {
        case ErrNoConnection:
            strcpy(rpkt->errorString, "Connection not open.");
            break;
        case ErrUnique:
            strcpy(rpkt->errorString, "Unique constraint violation");
            break;
        case ErrNullViolation:
            strcpy(rpkt->errorString, "Not null constraint violation");
            break;
    }
}

DbRetVal SqlNetworkHandler::servePacket(PacketHeader &header, void *respkt)
{
    ResponsePacket *rpkt = (ResponsePacket *) respkt;
    DbRetVal rv = OK;
    int params=0;
    int proj=0;
    NetworkStmt *stmt=NULL;

    if (header.packetType == SQL_NW_PKT_ISTABLEPRESENT ||
                      header.packetType == SQL_NW_PKT_EXECDIRECT ) {
        delete rpkt;
        return OK;
    }
    char *ptr = (char *)&rpkt->retVal;
    /*if (*ptr==0) {
        delete rpkt;
        return OK;
    }*/
    if (rpkt->errRetVal) {
        delete rpkt;
        return OK;
    }
    params =  *(ptr + 2);
    proj = *(ptr + 3);
    if ((header.packetType == SQL_NW_PKT_PREPARE && params != 0) ||
                      (header.packetType == SQL_NW_PKT_PREPARE && proj != 0)) {
        if (params) {
            SqlPacketParamMetadata *prmpkt = new SqlPacketParamMetadata();
            prmpkt->stmtID = rpkt->stmtID;
            ListIterator stmtIter = SqlNetworkHandler::stmtList.getIterator();
            while (stmtIter.hasElement()) {
                stmt = (NetworkStmt*) stmtIter.nextElement();
                if (stmt->stmtID == prmpkt->stmtID) break;
            }
            prmpkt->noParams = stmt->paramList.size();
            rv = prmpkt->marshall();
            rv = send(SQL_NW_PKT_PARAM_METADATA, prmpkt->getMarshalledBuffer(), prmpkt->getBufferSize());
            delete prmpkt;
            if (rv != OK) {
                printf("Error in sending the metadata to the client\n");
                closeConnection();
                exit(1);
            }
        }
        if (proj) {
            //fill projection list and send it to client   
            SqlPacketProjMetadata *prjpkt = new SqlPacketProjMetadata();
            prjpkt->stmtID = rpkt->stmtID;
            ListIterator stmtIter = SqlNetworkHandler::stmtList.getIterator();
            while (stmtIter.hasElement()) {
                stmt = (NetworkStmt*) stmtIter.nextElement();
                if (stmt->stmtID == prjpkt->stmtID) break;
            }
            prjpkt->noProjs = stmt->projList.size();
            rv = prjpkt->marshall();
            rv = send(SQL_NW_PKT_PROJ_METADATA, prjpkt->getMarshalledBuffer(), prjpkt->getBufferSize());
            delete prjpkt;
            if (rv != OK) {
                printf("Error in sending the metadata to the client\n");
                closeConnection();
                exit(1);
            }
        }
    }
    else if (header.packetType == SQL_NW_PKT_SHOWTABLES) {
        SqlPacketShowTables *shTblPkt = new SqlPacketShowTables();
        shTblPkt->numOfTables = rpkt->rows;
        rv = shTblPkt->marshall();
        if (rv != OK) { printf("marshall failed\n"); }
        ListIterator tblIter = SqlNetworkHandler::tableNameList.getIterator();
        while (tblIter.hasElement()) delete tblIter.nextElement();
        SqlNetworkHandler::tableNameList.reset();
        rv = send(SQL_NW_PKT_SHOWTABLES, shTblPkt->getMarshalledBuffer(), shTblPkt->getBufferSize());
        delete shTblPkt;
        if (rv != OK) {
            printError(ErrOS, "Error in sending the metadata to the client\n");
            closeConnection();
            exit(1);
        }
    }
    else if (header.packetType == SQL_NW_PKT_GETRECORDS) {
        if (!rpkt->rows) return OK; 
        SqlPacketLoadRecords *pkt = new SqlPacketLoadRecords();
        pkt->setPages(rpkt->rows);
        pkt->marshall();
        SqlStatement *sqlstmt = new SqlStatement();
        SqlConnection *sqlcon = NULL;
        if (isSqlLogNeeded)
            sqlcon = (SqlConnection *) conn->getInnerConnection();
        else sqlcon = (SqlConnection *) conn;
        sqlstmt->setSqlConnection(sqlcon);
        sqlstmt->loadRecords(&rpkt->errorString[0], pkt->getMarshalledBuffer());
        char *buf = pkt->getMarshalledBuffer();
        rv = send(SQL_NW_PKT_LOADRECORDS, pkt->getMarshalledBuffer(), pkt->getBufferSize());
        delete pkt;
        delete sqlstmt;
        if (rv != OK) {
            printf("Error in sending the metadata to the client\n");
            closeConnection();
            exit(1);
        }
    }
    else if (header.packetType == SQL_NW_PKT_DISCONNECT) exit(0);
    if (rpkt) { delete rpkt; rpkt = NULL; }
    return OK;
}

DbRetVal SqlNetworkHandler::send(NetworkPacketType type, char *buf, int len)
{
    DbRetVal rv = OK;
    PacketHeader *hdr=  new PacketHeader();
    hdr->packetType = type;
    hdr->packetLength = len;
    hdr->srcNetworkID = 0;//networkid;
    hdr->version = 1;
    int numbytes=0;
    if ((numbytes=os::send(sockfd, hdr, sizeof(PacketHeader), 0)) == -1) {
        printError(ErrOS, "Unable to send the packet\n");
        return ErrOS;
    }
    if ((numbytes=os::send(sockfd, buf, len, 0)) == -1) {
        printError(ErrOS, "Unable to send the packet\n");
        return ErrOS;
    }
    delete hdr;
    return rv;
}
