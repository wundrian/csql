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
#include "Statement.h"
#include <Info.h>

InsStatement::InsStatement()
{
    parsedData = NULL; 
    dbMgr = NULL; 
    table = NULL;
    params = NULL;
    paramValues = NULL;
    totalParams = 0;
}

InsStatement::~InsStatement()
{
    if (totalParams) {
        free(params);
        params =  NULL;
        free(paramValues);
        paramValues = NULL;
    }
}

DbRetVal InsStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    //copy param values to binded buffer
    FieldValue *value;
    for (int i = 0; i < totalParams; i ++)
    {
        value = (FieldValue*) params[i];
        if (paramValues[i] == NULL) 
        {
            printError(ErrBadCall, "param values not set");
            return ErrBadCall;
        }
        AllDataType::copyVal(value->value, paramValues[i], value->type, value->length);
    }
    rv = table->insertTuple();
    return rv;
}

DbRetVal InsStatement::setParam(int paramNo, void *value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == value) return ErrBadArg;
    paramValues[paramNo -1] = (char*) value; 
    return OK;
}

DbRetVal InsStatement::resolve()
{
    if (dbMgr == NULL) return ErrNoConnection;
    //check whether the table exists
    table = dbMgr->openTable(parsedData->getTableName());
    if (table == NULL) 
    {
        printError(ErrNotExists, "Unable to open the table:Table not exists");
        return ErrNotExists;
    }
    //check whether the total number of field name in the list is same as the total 
    //number of values provided in the values list.
    if (parsedData->getFieldNameList().size() != 
                               parsedData->getFieldValueList().size())
    {
        dbMgr->closeTable(table);
        printError(ErrSyntaxError, "Field Name list and field values do not match");
        return ErrSyntaxError;
    }

    //get the fieldname list and validate field names
    ListIterator iter = parsedData->getFieldNameList().getIterator();
    ListIterator valIter = parsedData->getFieldValueList().getIterator();
    FieldName *name; FieldValue *value;
    FieldInfo *fInfo = new FieldInfo();
    int paramPos =1;
    DbRetVal rv = OK;
    while (iter.hasElement())
    {
        name = (FieldName*)iter.nextElement();
        value = (FieldValue*) valIter.nextElement();
        if (NULL == name || NULL == value) 
        {
            dbMgr->closeTable(table);
            delete fInfo;
            printError(ErrSyntaxError, "Field Name list and field values do not match");
            return ErrSyntaxError;
        }
        rv = table->getFieldInfo(name->fldName, fInfo);
        if (ErrNotFound == rv)
        {
            dbMgr->closeTable(table);
            delete fInfo;
            printError(ErrSyntaxError, "Field %s does not exist in table", 
                                        name->fldName);
            return ErrSyntaxError;
        }
        value->type = fInfo->type;
        value->length = fInfo->length;
        value->value = AllDataType::alloc(fInfo->type);
        table->bindFld(name->fldName, value->value);
        if (value->parsedString[0] == '?')
        {
            value->paramNo = paramPos++;
        }
        if (!value->paramNo) 
            AllDataType::strToValue(value->value, value->parsedString, fInfo->type);
    }
    delete fInfo;
    totalParams = paramPos -1;
    params = (void**) malloc ( totalParams * sizeof(FieldValue*));
    paramValues = (char**) malloc( totalParams * sizeof(char*));
    valIter.reset();
    while(valIter.hasElement())
    {
        value = (FieldValue*) valIter.nextElement();
        if (value == NULL) 
        {
            dbMgr->closeTable(table);
            free(params); params = NULL;
            free(paramValues); paramValues = NULL;
            printError(ErrSysFatal, "Should never happen. value NULL after iteration");
            return ErrSysFatal;
        }
        params[value->paramNo -1 ] = value;
    }
    return OK;
}

