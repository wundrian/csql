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
DelStatement::DelStatement()
{
    parsedData = NULL; 
    dbMgr = NULL; 
    table = NULL;
    params = NULL;
    paramValues = NULL;
    totalParams = 0;
}

DelStatement::~DelStatement() {
    if (table) {
        table->setCondition(NULL);
        if (dbMgr) dbMgr->closeTable(table);
    }
    if (totalParams) {
        free(params);
        params =  NULL;
        free(paramValues);
        paramValues = NULL;
    }

}

DbRetVal DelStatement::getParamFldInfo(int paramPos, FieldInfo *&info)
{
    if (paramPos <=0 || paramPos > totalParams) return ErrBadArg;
    ConditionValue *value = (ConditionValue*) params[paramPos-1];
    if (value == NULL) { printError(ErrBadArg, "Should never happen\n");
                         return ErrBadArg; }
    table->getFieldNameAlone(value->fName,info->fldName);
    info->type = value->type;
    info->length = value->length;
    info->isNull = value->isNullable;
    return OK;
}
DbRetVal DelStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    //copy param values to binded buffer
    ConditionValue *value;
    for (int i = 0; i < totalParams; i ++)
    {
        value = (ConditionValue*) params[i];
        if (paramValues[i] == NULL) 
        {
            continue;
            //printError(ErrBadCall, "param values not set");
            //return ErrBadCall;
        }
        AllDataType::copyVal(value->value, paramValues[i], value->type, value->length);
    }
    rv = table->execute();
    if (rv != OK) return rv;
    rowsAffected = 0;
    void *tuple;
    while(true)
    {
        tuple = (char*)table->fetchNoBind(rv);
        if (rv != OK) break;
        if (tuple == NULL) {break;}
        rv = table->deleteTuple();
        if (rv != OK) break;
        rowsAffected++;
    }
    table->close();
    return rv;
}


DbRetVal DelStatement::setParam(int paramNo, void *value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == value) return ErrBadArg;
    paramValues[paramNo -1] = (char*) value; 
    return OK;
}

DbRetVal DelStatement::setShortParam(int paramNo, short value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(short*)cValue->value = value; 
    return OK;
}

DbRetVal DelStatement::setIntParam(int paramNo, int value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(int*)cValue->value = value; 
    return OK;
}
DbRetVal DelStatement::setLongParam(int paramNo, long value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(long*)cValue->value = value; 
    return OK;
}

DbRetVal DelStatement::setLongLongParam(int paramNo, long long value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(long long*)cValue->value = value; 
    return OK;
}
DbRetVal DelStatement::setByteIntParam(int paramNo, ByteInt value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(ByteInt*)cValue->value = value; 
    return OK;
}
DbRetVal DelStatement::setFloatParam(int paramNo, float value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(float*)cValue->value = value; 
    return OK;
}
DbRetVal DelStatement::setDoubleParam(int paramNo, double value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(double*)cValue->value = value; 
    return OK;
}
DbRetVal DelStatement::setStringParam(int paramNo, char *value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    strcpy((char*)cValue->value, value);
    return OK;
}
DbRetVal DelStatement::setDateParam(int paramNo, Date value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(Date*)cValue->value = value; 
    return OK;
}
DbRetVal DelStatement::setTimeParam(int paramNo, Time value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(Time*)cValue->value = value; 
    return OK;
}
 void* DelStatement::getParamValuePtr( int pos )
 {
     ConditionValue *cValue = (ConditionValue*) params [pos-1];
     return ( (void*) cValue->value );
 }

DbRetVal DelStatement::setTimeStampParam(int paramNo, TimeStamp value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(TimeStamp*)cValue->value = value;
    return OK;
}

DbRetVal DelStatement::setBinaryParam(int paramNo, void *value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    AllDataType::convertToBinary(cValue->value,value,typeString,cValue->length);
    return OK;
}

DbRetVal DelStatement::resolve()
{
    if (dbMgr == NULL) return ErrNoConnection;
    //check whether the table exists
    table = dbMgr->openTable(parsedData->getTableName());
    if (table == NULL) 
    {
        printError(ErrNotExists, "Unable to open the table:Table not exists");
        return ErrNotExists;
    }

    table->setCondition(parsedData->getCondition());

    DbRetVal rv = resolveForCondition();
    if (rv != OK) 
    {
        //TODO::free memory allocated for params
        table->setCondition(NULL);
        dbMgr->closeTable(table);
        table = NULL;
    }
    return rv;
}


DbRetVal DelStatement::resolveForCondition()
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
            delete fInfo;
            printError(ErrSysFatal, "Should never happen.");
            return ErrSysFatal;
        }
        rv = table->getFieldInfo(value->fName, fInfo);
        if (ErrNotFound == rv)
        {
            delete fInfo;
            printError(ErrSyntaxError, "Field %s does not exist in table", 
                                        value->fName);
            return ErrSyntaxError;
        }
        value->type = fInfo->type;
        value->length = fInfo->length;
        value->isNullable = fInfo->isNull;
        // for binary datatype input buffer size should be 2 times the length 
        value->value = AllDataType::alloc(fInfo->type, fInfo->length);
        if (value->parsedString == NULL)
        {
            delete fInfo;
            printError(ErrSyntaxError, "Condition value should not be NULL");
            return ErrSyntaxError;
        }

        if (value->parsedString[0] == '?')
        {
		    if (! value->opLike) // checks if 'LIKE' operator is used
                value->paramNo = paramPos++;
        }
        if (!value->paramNo) { 
		    // Here for binary dataType it is not strcpy'd bcos internally memcmp is done for predicates like f2 = 'abcd' where f2 is binary
            AllDataType::strToValue(value->value, value->parsedString, fInfo->type, fInfo->length);
		}	
    }
    delete fInfo;
    totalParams = paramPos -1;
    if (0 == totalParams) return OK;
    params = (void**) malloc ( totalParams * sizeof(FieldValue*));
    paramValues = (char**) malloc( totalParams * sizeof(char*));
    memset(params, 0, totalParams * sizeof(FieldValue*));
    memset(paramValues, 0, totalParams * sizeof(char*));
    iter.reset();
    while(iter.hasElement())
    {
        value = (ConditionValue*) iter.nextElement();
        if (value == NULL) 
        {
            free(params); params = NULL;
            free(paramValues); paramValues = NULL;
            printError(ErrSysFatal, "Should never happen. value NULL after iteration");
            return ErrSysFatal;
        }
        params[value->paramNo -1 ] = value;
    }
    return OK;
}

int  DelStatement::getFldPos(char *name)
{
    return table->getFldPos(name);
}

