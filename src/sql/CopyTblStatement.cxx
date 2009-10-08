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
  ***************************************************************************/
#include <os.h>
#include <Statement.h>
#include <TableImpl.h>
#include <OrderTableImpl.h>

CopyTblStatement::CopyTblStatement()
{
    innerSelStmt = NULL;
    totalFields = 0;
    bindFieldValues= NULL;
}

CopyTblStatement::~CopyTblStatement()
{
    if (table) { table->close(); table = NULL; }
    SelStatement *stmt= (SelStatement *)innerSelStmt;
    stmt->close();
    if(totalFields){
       for(int i=0;i<totalFields;i++)
       {
           free(bindFieldValues[i]);    
       }
       free(bindFieldValues); bindFieldValues = NULL;
    }
    totalFields =0;
    delete innerSelStmt;
}

DbRetVal CopyTblStatement::resolve()
{
    DbRetVal rv = OK;
    strcpy(tblName,parsedData->getPKTableName());
    SelStatement *sStmt = new SelStatement();
    innerSelStmt = ( Statement *) sStmt;
    innerSelStmt->setDbMgr(dbMgr);
    innerSelStmt->setParsedData(parsedData);
    innerSelStmt->resolve();
    if(parsedData->getCreateTbl())
        rv = resolveForCreate();
    else 
        rv = resolveForInsert();
    return rv;
}

DbRetVal CopyTblStatement::resolveForInsert()
{
    table = dbMgr->openTable(tblName);
    if (table == NULL)
    {
        printError(ErrNotExists, "Unable to open the table:Table not exists");
        return ErrNotExists;
    }
    table->setLoading(true);
    //bind field
    List fNameList = table->getFieldNameList();
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    int fcount = 1; void *valBuf; int fieldsize=0;
    Identifier *elem = NULL;
    totalFields = fNameList.size();
    bindFieldValues = (void**) malloc( totalFields * sizeof(char*));
    memset(bindFieldValues, 0, totalFields * sizeof(char*));
    SelStatement *selStmt = (SelStatement*) innerSelStmt;
    while (fNameIter.hasElement()) 
    {
        elem = (Identifier*) fNameIter.nextElement();
        table->getFieldInfo((const char*)elem->name, info);
        //TODO :: Should free
        valBuf = AllDataType::alloc(info->type, info->length);
        table->bindFld(elem->name, valBuf);
        fieldsize=0;
        selStmt->setBindField(fcount, valBuf);
        bindFieldValues[fcount-1] = valBuf;
        fcount++;
    }
    delete info;
    fNameIter.reset();
    while (fNameIter.hasElement())
    {
         delete (Identifier*) fNameIter.nextElement();
    }
    fNameList.reset();
    return OK;
}

DbRetVal CopyTblStatement::resolveForCreate()
{
    DbRetVal rv = OK;
    int  nop = 0;
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    nop = stmt->noOfProjFields();
    FieldInfo *field = new FieldInfo();
    TableDef tabDef;
    char name[IDENTIFIER_LENGTH];
    for(int i=0; i<nop; i++)
    {
        rv = stmt->getProjFldInfo(i+1,field);
        Table::getFieldNameAlone(field->fldName, name);
        tabDef.addField(name,field->type, field->length, field->defaultValueBuf, field->isNull);
    }
    delete field;
    rv = dbMgr->createTable(tblName, tabDef);
    if(rv!=OK){
       return rv;
    }
    rv = resolveForInsert();
    return rv;
}

DbRetVal CopyTblStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    SelStatement *selStmt = (SelStatement*) innerSelStmt;
    selStmt->execute(rowsAffected);
    while(selStmt->fetch())
    {
        rv = table->insertTuple();
        if(rv!=OK) break;
    }
    if( (rv!=OK) && ( !parsedData->getCreateTbl()))
    {
        dbMgr->dropTable(tblName);
    }
    return rv;
}

DbRetVal CopyTblStatement::setShortParam(int paramNo, short value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setShortParam(paramNo,value);
}

DbRetVal CopyTblStatement::setIntParam(int paramNo, int value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setIntParam(paramNo,value);
}

DbRetVal CopyTblStatement::setLongParam(int paramNo, long value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setLongParam(paramNo,value);
}

DbRetVal CopyTblStatement::setLongLongParam(int paramNo, long long value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setLongLongParam(paramNo,value);
}

DbRetVal CopyTblStatement::setByteIntParam(int paramNo, ByteInt value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setByteIntParam(paramNo,value);
}

DbRetVal CopyTblStatement::setFloatParam(int paramNo, float value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setFloatParam(paramNo,value);
}

DbRetVal CopyTblStatement::setDoubleParam(int paramNo, double value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setDoubleParam(paramNo,value); 
}

DbRetVal CopyTblStatement::setStringParam(int paramNo, char *value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setStringParam(paramNo,value); 
}

DbRetVal CopyTblStatement::setDateParam(int paramNo, Date value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setDateParam(paramNo,value); 
}

DbRetVal CopyTblStatement::setTimeParam(int paramNo, Time value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setTimeParam(paramNo,value); 
}

DbRetVal CopyTblStatement::setTimeStampParam(int paramNo, TimeStamp value)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setTimeStampParam(paramNo,value); 
}

DbRetVal CopyTblStatement::setBinaryParam(int paramNo, void *value, int length)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->setBinaryParam(paramNo,value,length); 
}

void* CopyTblStatement::getParamValuePtr(int pos)
{
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    return stmt->getParamValuePtr(pos); 
}

int CopyTblStatement::getFldPos(char *name)
{
   return 0;
}

DbRetVal CopyTblStatement::getParamFldInfo(int paramPos, FieldInfo *&info)
{
    DbRetVal rv = OK;
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    rv = stmt->getParamFldInfo(paramPos, info);
    return rv;
}
DbRetVal CopyTblStatement::setParam(int paramNo, void *value)
{
    DbRetVal rv = OK;
    SelStatement *stmt = (SelStatement*) innerSelStmt;
    rv = stmt->setParam(paramNo,value);
    return rv;
}
