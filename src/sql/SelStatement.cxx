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

SelStatement::SelStatement()
{
    parsedData = NULL; 
    dbMgr = NULL; 
    table = NULL;
    params = NULL;
    paramValues = NULL;
    totalParams = 0;
    bindFields = NULL;
    bindFieldValues = NULL;
    totalFields = 0;
}

SelStatement::~SelStatement()
{
    if (totalParams) {
        free(params);
        params =  NULL;
        free(paramValues);
        paramValues = NULL;
    }
    if (totalFields)
    {
        free(bindFields);
        bindFields =  NULL;
        free(bindFieldValues);
        bindFieldValues = NULL;

    }
}

DbRetVal SelStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    //copy param values to binded buffer
    ConditionValue *value;
    for (int i = 0; i < totalParams; i ++)
    {
        value = (ConditionValue*) params[i];
        if (paramValues[i] == NULL) 
        {
            printError(ErrBadCall, "param values not set");
            return ErrBadCall;
        }
        AllDataType::copyVal(value->value, paramValues[i], value->type, value->length);
    }
    rv = table->execute();
    return rv;
}

DbRetVal SelStatement::setParam(int paramNo, void *value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == value) return ErrBadArg;
    paramValues[paramNo -1] = (char*) value; 
    return OK;
}

DbRetVal SelStatement::setBindField(int colNo, void *value)
{
    if (colNo <=0) return ErrBadArg;
    //TODO: check the upper limit
    //if (colNo > table->getFieldNameList().size()) return ErrBadArg;
    if (NULL == value) return ErrBadArg;
    bindFieldValues[colNo -1] = (char*) value; 
    return OK;
}

DbRetVal SelStatement::resolve()
{
    if (dbMgr == NULL) return ErrNoConnection;
    //check whether the table exists
    table = dbMgr->openTable(parsedData->getTableName());
    if (table == NULL) 
    {
        printError(ErrNotExists, "Unable to open the table:Table not exists");
        return ErrNotExists;
    }
    //get the fieldname list and validate field names
    ListIterator iter = parsedData->getFieldNameList().getIterator();
    FieldName *name = NULL;
    FieldInfo *fInfo = new FieldInfo();
    DbRetVal rv = OK;
    while (iter.hasElement())
    {
        name = (FieldName*)iter.nextElement();
        if (NULL == name) 
        {
            dbMgr->closeTable(table);
            delete fInfo;
            printError(ErrSysFatal, "Should never happen. Field Name list has NULL");
            return ErrSysFatal;
        }
        if ('*' == name->fldName[0]) 
        {
            rv = resolveStar();
            if (rv != OK) { delete fInfo; return rv; }
            //as soon as it encounters *, it breaks the loop negleting other field names
            //as they all are deleted during resolveStar method.
            break;
        } else {
            rv = table->getFieldInfo(name->fldName, fInfo);
            if (ErrNotFound == rv)
            {
                dbMgr->closeTable(table);
                delete fInfo;
                printError(ErrSyntaxError, "Field %s does not exist in table", 
                                        name->fldName);
                return ErrSyntaxError;
            }
            FieldValue *newVal = new FieldValue();
            newVal->parsedString = NULL;
            newVal->paramNo = 0;
            newVal->type = fInfo->type;
            newVal->length = fInfo->length;
            newVal->value = AllDataType::alloc(fInfo->type);
            parsedData->insertFieldValue(newVal);
            table->bindFld(name->fldName, newVal->value);
        }
    }
    delete fInfo;

    rv = setBindFieldAndValues();
    if (rv != OK) return rv;

    table->setCondition(parsedData->getCondition());



    rv = resolveForCondition();
    if (rv != OK) 
    {
        //TODO::free memory allocated for params
        table->setCondition(NULL);
    }
    return rv;
}
DbRetVal SelStatement::resolveStar()
{
    DbRetVal rv = OK;
    parsedData->clearFieldNameList();
    FieldNameList fNameList = table->getFieldNameList();
    FieldValue *newVal = NULL;
    fNameList.resetIter(); //do not remove this.
    FieldInfo *fInfo = new FieldInfo();
    for (int i = 0; i < fNameList.size() ; i++)
    {
        char *fName = fNameList.nextFieldName();
        rv = table->getFieldInfo(fName, fInfo);
        if (ErrNotFound == rv)
        {
            dbMgr->closeTable(table);
            delete fInfo;
            fNameList.removeAll();
            printError(ErrSysFatal, "Should never happen.");
            return ErrSysFatal;
        }
        newVal = new FieldValue();
        newVal->parsedString = NULL;
        newVal->paramNo = 0;
        newVal->type = fInfo->type;
        newVal->length = fInfo->length;
        newVal->value = AllDataType::alloc(fInfo->type);
        parsedData->insertFieldValue(newVal);
        parsedData->insertField(fName);
        table->bindFld(fName, newVal->value);
    }
    delete fInfo;
    return OK;
}

DbRetVal SelStatement::setBindFieldAndValues()
{
    totalFields = table->getFieldNameList().size();
    bindFields = (FieldValue**) malloc ( totalFields * sizeof(FieldValue*));
    bindFieldValues = (char**) malloc( totalFields * sizeof(char*));
    ListIterator valIter = parsedData->getFieldValueList().getIterator();
    int colNo =0;
    FieldValue *value = NULL;
    valIter.reset();
    while(valIter.hasElement())
    {
        value = (FieldValue*) valIter.nextElement();
        if (value == NULL)
        {
            dbMgr->closeTable(table);
            free(bindFields); bindFields = NULL;
            free(bindFieldValues); bindFieldValues = NULL;
            printError(ErrSysFatal, "Should never happen. value NULL after iteration");
            return ErrSysFatal;
        }
        bindFields[colNo++ ] = value;
    }
    return OK;
}


DbRetVal SelStatement::resolveForCondition()
{
    //get the fieldname list and validate field names
    ListIterator iter = parsedData->getConditionValueList().getIterator();

    ConditionValue *value;
    FieldInfo *fInfo = new FieldInfo();
    int paramPos =1;
    DbRetVal rv = OK;
    while (iter.hasElement())
    {
        value = (ConditionValue*) iter.nextElement();
        if (NULL == value) 
        {
            dbMgr->closeTable(table);
            delete fInfo;
            printError(ErrSysFatal, "Should never happen.");
            return ErrSysFatal;
        }
        rv = table->getFieldInfo(value->fName, fInfo);
        if (ErrNotFound == rv)
        {
            dbMgr->closeTable(table);
            delete fInfo;
            printError(ErrSyntaxError, "Field %s does not exist in table", 
                                        value->fName);
            return ErrSyntaxError;
        }
        value->type = fInfo->type;
        value->length = fInfo->length;
        value->value = AllDataType::alloc(fInfo->type);
        //table->bindFld(name->fldName, value->value);
        if (value->parsedString[0] == '?')
        {
            value->paramNo = paramPos++;
        }
        if (!value->paramNo) 
            AllDataType::strToValue(value->value, value->parsedString, fInfo->type);
    }
    delete fInfo;
    totalParams = paramPos -1;
    if (0 == totalParams) return OK;
    params = (void**) malloc ( totalParams * sizeof(FieldValue*));
    paramValues = (char**) malloc( totalParams * sizeof(char*));
    iter.reset();
    while(iter.hasElement())
    {
        value = (ConditionValue*) iter.nextElement();
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

void* SelStatement::fetch()
{
    void *tuple = table->fetch();
    if (NULL == tuple) return NULL;
    //copy values to binded buffer
    FieldValue *value;
    for (int i = 0; i < totalFields; i++)
    {
        value = bindFields[i];
        if (bindFieldValues[i] == NULL) 
        {
            printError(ErrBadCall, "Fields are not binded");
            return NULL;
        }
        AllDataType::copyVal(bindFieldValues[i], value->value, value->type, value->length);
    }
    return tuple;
}


int SelStatement::noOfProjFields()
{
    return totalFields;
}

DbRetVal SelStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    //TODO::if not yet prepared return error
    //TODO::check the upper limit for projpos
    ListIterator iter = parsedData->getFieldNameList().getIterator();
    FieldName *name = NULL;
    DbRetVal rv = OK;
    int position =0;
    while (iter.hasElement())
    {
        name = (FieldName*)iter.nextElement();
        if (NULL == name) 
        {
            printError(ErrSysFatal, "Should never happen. Field Name list has NULL");
            return ErrSysFatal;
        }
        position++;
        if (position == projpos) break;
    }

    rv = table->getFieldInfo(name->fldName, fInfo);
}