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
    isPointReturned = false;
    handleAggWithTbl=false;
    numRecords = 0;
    isOffsetReached = false;
    isRecLimitReached = false;
    isExplain=false;
    isJoin=false;
}

SelStatement::~SelStatement()
{
    close();
    if (table) { table->close(); table = NULL; }
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
DbRetVal SelStatement::getParamFldInfo(int paramNo, FieldInfo *&info)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    table->getFieldNameAlone(cValue->fName,info->fldName);
    info->type = cValue->type;
    info->length = cValue->length;
    info->isNull = cValue->isNullable;
    return OK;
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
            continue;
            //printError(ErrBadCall, "param values not set");
            //return ErrBadCall;
        }
        AllDataType::copyVal(value->value, paramValues[i], value->type, value->length);
    }
    //table->printPlan(0);
    //printf("Execute Called\n");
    rv = table->execute();
    numRecords = 0;
    isOffsetReached = false;
    isRecLimitReached = false;

    if (isExplain) table->printPlan(0);
    return rv;
}

DbRetVal SelStatement::setParam(int paramNo, void *value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == value) return ErrBadArg;
    paramValues[paramNo -1] = (char*) value; 
    return OK;
}

DbRetVal SelStatement::setShortParam(int paramNo, short value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "field value is null. Should never happen");
        return ErrSysFatal;
    }
    *(short*)cValue->value = value; 
    return OK;
}

DbRetVal SelStatement::setIntParam(int paramNo, int value)
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
DbRetVal SelStatement::setLongParam(int paramNo, long value)
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

DbRetVal SelStatement::setLongLongParam(int paramNo, long long value)
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
DbRetVal SelStatement::setByteIntParam(int paramNo, ByteInt value)
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
DbRetVal SelStatement::setFloatParam(int paramNo, float value)
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
DbRetVal SelStatement::setDoubleParam(int paramNo, double value)
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
DbRetVal SelStatement::setStringParam(int paramNo, char *value)
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
DbRetVal SelStatement::setDateParam(int paramNo, Date value)
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
DbRetVal SelStatement::setTimeParam(int paramNo, Time value)
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
DbRetVal SelStatement::setTimeStampParam(int paramNo, TimeStamp value)
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

DbRetVal SelStatement::setBinaryParam(int paramNo, void *value, int length)
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

DbRetVal SelStatement::setBindField(int colNo, void *value)
{
    if (colNo <=0) return ErrBadArg;
    //TODO: check the upper limit
    //if (colNo > table->getFieldNameList().size()) return ErrBadArg;
    if (NULL == value) return ErrBadArg;
    bindFieldValues[colNo -1] = (char*) value; 
    return OK;
}
bool SelStatement::isTableAlreadyPresent(char *tblName, char *aliasName)
{
    ListIterator titer = parsedData->getTableNameList().getIterator();
    int count =0;
    while (titer.hasElement())
    {
        TableName *t  = (TableName*)titer.nextElement();
        if (strcmp(t->tblName, tblName) ==0 && 
            strcmp(t->aliasName, aliasName) ==0) count++;
    }
    if (count == 1) return false; 
    return true;
}
DbRetVal SelStatement::openTables()
{
    if (dbMgr == NULL) return ErrNoConnection;
    JoinTableImpl *jHdl = NULL;
    Table *tHdl = NULL, *prevHdl = NULL;
    isJoin = false;
    //check whether all the table exists
    ListIterator titer = parsedData->getTableNameList().getIterator();
    ListIterator jiter = parsedData->getJoinTypeList().getIterator();
    while (titer.hasElement())
    {
        TableName *t  = (TableName*)titer.nextElement();
        parsedData->setTableName(t->tblName);        
        if (isTableAlreadyPresent(t->tblName, t->aliasName)) {
            printError(ErrSyntaxError, 
                       "Referencing same table again %s", t->tblName);
            if (prevHdl) delete prevHdl;
            return ErrSyntaxError;
        }
        tHdl = dbMgr->openTable(t->tblName);
        if ( NULL == tHdl ) 
        {
            printError(ErrNotExists, 
                       "Unable to open the table:Table not exists");
            if (prevHdl) delete prevHdl;
            return ErrNotExists;
        }
        TableImpl *tImpl=  (TableImpl*) tHdl;
        tImpl->setAliasName(t->aliasName);
        if (NULL != prevHdl) 
        { 
            isJoin = true;
            jHdl = new JoinTableImpl();
            jHdl->setTable(prevHdl, tHdl);
            JoinTypeNode *node = (JoinTypeNode*) jiter.nextElement();
            if (node == NULL) {
                printError(ErrSyntaxError, 
                           "Join Type and number of tables do not match");
                delete jHdl;
                return ErrSyntaxError;
            }
            jHdl->setJoinType(node->jType);
            prevHdl = jHdl;
            continue;
        }
        prevHdl = tHdl;
    }

    if (isJoin) table = jHdl; else table = tHdl;
    return OK;
}
DbRetVal SelStatement::resolve()
{
    DbRetVal rv = openTables();
    if (rv != OK) return rv;
    //get the fieldname list and validate field names
    ListIterator iter = parsedData->getFieldNameList().getIterator();
    FieldName *name = NULL;
    FieldInfo *fInfo = new FieldInfo();
    List bindFldList;
    bool isMixPrjList = false;
    bool isAggFld = false;
    bool isNotAggFld = false;
    bool isSingleTableNoGrp = false;
    bool isGroupFld = false;
    if(parsedData->getTableNameList().size() == 1 &&
       parsedData->getGroupFieldNameList().size() == 0)
    {
        isSingleTableNoGrp = true;
    }
    AggTableImpl *aggTable = NULL;
    while (iter.hasElement())
    {
        name = (FieldName*)iter.nextElement();
        if (NULL == name) 
        {
            dbMgr->closeTable(table);
            table = NULL;
            delete fInfo;
            printError(ErrSysFatal, "Should never happen. Field Name list has NULL");
            return ErrSysFatal;
        }
        bool isBindFld=false;
        if ('*' == name->fldName[0] && name->aType == AGG_UNKNOWN) 
        {
            rv = resolveStar();
            if (rv != OK)
            { 
                dbMgr->closeTable(table);
                table = NULL;
                delete fInfo; 
                return rv; 
            }
            if (parsedData->getGroupFieldNameList().size()!= 0 
                            && !isSingleTableNoGrp)
            {
                if (!aggTable)
                    aggTable = new AggTableImpl();
                aggTable->setTable(table);
            }
            //as soon as it encounters *, it breaks the loop negleting other field names
            //as they all are deleted during resolveStar method.
            break;
        } else {
            if ('*' == name->fldName[0] && name->aType != AGG_COUNT) {
                return ErrSyntaxError;
            }
            rv = table->getFieldInfo(name->fldName, fInfo);
            if (ErrNotFound == rv || ErrNotExists == rv)
            {
                if (aggTable) { delete aggTable; aggTable = NULL; }
                else dbMgr->closeTable(table);
                table = NULL;
                delete fInfo;
                printError(ErrSyntaxError, "Field %s does not exist in table",
                                        name->fldName);
                return ErrSyntaxError;
            }
            FieldValue *newVal = new FieldValue();
            strcpy(newVal->fldName,name->fldName);
            newVal->parsedString = NULL;
            newVal->paramNo = 0;
            newVal->aType = name->aType;
            if (!isMixPrjList) {
                if (newVal->aType != AGG_UNKNOWN) isAggFld = true;
                else isNotAggFld = true;
                if (isAggFld && isNotAggFld) isMixPrjList = true;
            }
            newVal->isInResSet = true;
            newVal->offset = fInfo->offset;
            newVal->isPrimary = fInfo->isPrimary;
            newVal->isUnique = fInfo->isUnique;
            newVal->isAutoIncrement = fInfo->isAutoIncrement;
            newVal->isDefault = fInfo->isDefault;
            if (newVal->isDefault) 
                strcpy(newVal->defValBuf, fInfo->defaultValueBuf);
            else newVal->defValBuf[0]='\0';

            if (name->aType == AGG_COUNT) {
                newVal->type = typeInt;
                newVal->length = sizeof(int);
            }
            else if (name->aType == AGG_AVG) {
                newVal->type = typeDouble;
                newVal->length = sizeof(double);
                if (!AllDataType::isValidFieldForAvg(fInfo->type)) {
                    printError(ErrBadArg, "Illegal operation for field %s", 
                                                               fInfo->fldName);
                    dbMgr->closeTable(table);
                    if (aggTable) { delete aggTable; aggTable = NULL; }
                    table = NULL;
                    delete fInfo;
                    return ErrBadArg;
                }
            }
            else {
                newVal->type = fInfo->type;
                newVal->length = fInfo->length;
            }
            newVal->isNullable = fInfo->isNull;
            FieldName *bFldName=NULL;
            ListIterator it = bindFldList.getIterator();
            while (it.hasElement())
            {
                bFldName = (FieldName*)it.nextElement();
                if(0==strcmp(bFldName->fldName,name->fldName) &&
                             name->aType == AGG_UNKNOWN)
                {
                    newVal->value=table->getBindFldAddr(name->fldName);
                    newVal->isAllocVal=false;
                    isBindFld=true;
                    break;
                }
            }
            if (!isBindFld) {
                if ( name->aType == AGG_UNKNOWN || 
                                    (name->aType != AGG_COUNT &&
                                                   name->aType != AGG_AVG) ) { 
                    if(newVal->type == typeBinary) 
                        newVal->value = AllDataType::alloc(fInfo->type, 
                                                           2 * fInfo->length);
                    else newVal->value = AllDataType::alloc(fInfo->type, 
                                                            fInfo->length);
                } else { 
                    if (name->aType == AGG_AVG) {
                        newVal->value = AllDataType::alloc(typeDouble,
                                                            sizeof(double));
                        memset(newVal->value, 0, sizeof(double));
                    }
                    else if (name->aType == AGG_COUNT) {
                        newVal->value = AllDataType::alloc(typeInt,
                                                               sizeof(int));
                        memset(newVal->value, 0, sizeof(int));
                    }
                        
                }
                newVal->isAllocVal=true;
            }
            if (name->aType ==AGG_UNKNOWN && 
                            parsedData->getGroupFieldNameList().size()== 0) {
                rv = table->bindFld(name->fldName, newVal->value);
                if (OK !=rv) {
                   if (newVal->isAllocVal) free(newVal->value);
                   delete newVal; 
                   delete fInfo; 
                   return rv; 
               }
            }
            else if (!isSingleTableNoGrp) 
            {
                if (!aggTable) {
                    aggTable = new AggTableImpl();
                    aggTable->setTable(table);
                }
                rv = aggTable->bindFld(name->fldName, name->aType, newVal->value);
                if (OK !=rv) {
                    if (newVal->isAllocVal) free(newVal->value);
                    delete newVal; delete fInfo; delete aggTable;
                    aggTable = NULL; table = NULL;
                    return rv;
                }
            }
            if (name->aType !=AGG_UNKNOWN && isSingleTableNoGrp) 
                handleAggWithTbl= true;
            parsedData->insertFieldValue(newVal);
        } 
        if (!isBindFld) bindFldList.append(name);
    }
    bindFldList.reset();
 
    //Check if the having list is present in projection list or not.
    //If not present bind here not to be printed in fetchAndPrint later.
    ListIterator hiter = parsedData->getHavingFieldNameList().getIterator();
    while (hiter.hasElement()) {
        FieldName *fnm = (FieldName *) hiter.nextElement();
        rv = table->getFieldInfo(fnm->fldName, fInfo);
        if (!isInProjectionList(fnm->fldName, fnm->aType)) {
            FieldValue *newVal = new FieldValue();
            strcpy(newVal->fldName,fnm->fldName);
            newVal->parsedString = NULL;
            newVal->paramNo = 0;
            newVal->aType = fnm->aType;
            newVal->isInResSet = false;
            newVal->isNullable = fInfo->isNull;
            newVal->offset = fInfo->offset;
            newVal->isPrimary = fInfo->isPrimary;
            newVal->isUnique = fInfo->isUnique;
            newVal->isAutoIncrement = fInfo->isAutoIncrement;
            if (fnm->aType == AGG_AVG) {
                newVal->value = AllDataType::alloc(typeDouble, sizeof(double));
                memset(newVal->value, 0, sizeof(double));
            } else if (fnm->aType == AGG_COUNT) {
                newVal->value = AllDataType::alloc(typeInt, sizeof(int));
                memset(newVal->value, 0, sizeof(int));
            } else {
                newVal->value = AllDataType::alloc(fInfo->type, fInfo->length);
                memset(newVal->value, 0, fInfo->length);
            }
            newVal->isAllocVal = true;
            parsedData->insertFieldValue(newVal);
            aggTable->bindFld(fnm->fldName, fnm->aType, newVal->value);
        }
    }

    rv = setBindFieldAndValues();
    if (rv != OK) 
    {
        delete fInfo;
        if (aggTable) { delete aggTable; aggTable = NULL; }
        else dbMgr->closeTable(table);
        table = NULL;
        return rv;
    }

    table->setCondition(parsedData->getCondition());

    rv = resolveForCondition();
    if (rv != OK) 
    {
        delete fInfo;
        //TODO::free memory allocated for params
        if (aggTable) { delete aggTable; aggTable = NULL; }
        else { 
            table->setCondition(NULL);
            dbMgr->closeTable(table);
        }
        table = NULL;
        return rv;
    }
    if (NULL == parsedData->getCondition()) parsedData->setCacheWorthy(false);
    rv = resolveGroupFld(aggTable, isGroupFld);
    if (rv != OK) 
    {
        delete fInfo;
        //TODO::free memory allocated for params
        if (aggTable) { delete aggTable; aggTable = NULL; }
        else if (table)
        {
            table->setCondition(NULL);
            dbMgr->closeTable(table);
        }
        table = NULL;
        return rv;
    }
    if (isMixPrjList && ! isGroupFld) {
        printError(ErrSyntax, "Group By Field required.");
        delete fInfo;
        if (aggTable) { delete aggTable; aggTable = NULL; }
        else if (table)
        {
            table->setCondition(NULL);
            dbMgr->closeTable(table);
        }
        table = NULL;
        return ErrSyntax;
    }   
 
    rv = resolveOrderByFld();
    if (rv != OK) 
    {
        delete fInfo;
        delete table;
        table = NULL;
        return rv;
    }
    rv = resolveDistinct();
    delete fInfo;
    if(parsedData->getExplain())  isExplain = true;
    return rv;
}
DbRetVal SelStatement::resolveDistinct()
{   
    if (!parsedData->getDistinct()) {
         return OK;
    }
    OrderTableImpl *orderTable = new OrderTableImpl();
    orderTable->setTable(table);
    orderTable->setProjList(parsedData->getFieldValueList());
    orderTable->setOrderByList(parsedData->getFieldValueList());
    orderTable->setDistinct();
    table = orderTable;
    handleAggWithTbl= false;
    return OK;
}


DbRetVal SelStatement::resolveOrderByFld()
{
    if (0 == parsedData->getOrderFieldNameList().size()) {
         return OK;
    }
    OrderTableImpl *orderTable = new OrderTableImpl();
    orderTable->setTable(table);
    orderTable->setProjList(parsedData->getFieldValueList());
    ListIterator giter = parsedData->getOrderFieldNameList().getIterator();
    FieldName *name = NULL;
    DbRetVal rv = OK;
    FieldInfo *fInfo = new FieldInfo();
    while (giter.hasElement())
    {
        name = (FieldName*)giter.nextElement();
        rv = table->getFieldInfo(name->fldName, fInfo);
        if (ErrNotFound == rv || ErrNotExists == rv)
        {
            delete fInfo;
            printError(ErrSyntaxError, "Field %s does not exist in table",
                                        name->fldName);
            return ErrSyntaxError;
        }
        /*FieldValue *newVal = new FieldValue();
        strcpy(newVal->fldName,name->fldName);
        newVal->parsedString = NULL;
        newVal->paramNo = 0;
        newVal->type = fInfo->type;
        newVal->isNullable = fInfo->isNull;
        newVal->length = fInfo->length;
        if (newVal->type == typeBinary)
            newVal->value = AllDataType::alloc(fInfo->type, 2 * fInfo->length);
        else newVal->value = AllDataType::alloc(fInfo->type, fInfo->length);
        newVal->isAllocVal=true;
        parsedData->insertFieldValue(newVal);
        */
        if (name->aType == AGG_UNKNOWN) orderTable->setOrderBy(name->fldName);
        else orderTable->setOrderBy(name->fldName, true); //descending
    }
    delete fInfo;
    table = orderTable;
    handleAggWithTbl= false;
    return OK;
}

DbRetVal SelStatement::resolveGroupFld(AggTableImpl *aggTable, bool &isGrpFld)
{
    if (!aggTable) return OK;
    
    //check whether all non aggregate projections are from group list
    ListIterator iter = parsedData->getFieldNameList().getIterator();
    ListIterator giter = parsedData->getGroupFieldNameList().getIterator();
    FieldName *name = NULL;
    while (iter.hasElement())
    {
        name = (FieldName*) iter.nextElement();
        if (name->aType == AGG_UNKNOWN && !isGroupFld(name->fldName) ) {
            printError(ErrSyntaxError, 
                 "Non aggregate projection contains non group field: %s", 
                                                                name->fldName);
            return ErrSyntaxError;
        } 
    }
    
    DbRetVal rv = OK;
    FieldInfo *fInfo = new FieldInfo();
    while (giter.hasElement())
    {
        name = (FieldName*)giter.nextElement();
        rv = table->getFieldInfo(name->fldName, fInfo);
        if (ErrNotFound == rv || ErrNotExists == rv)
        {
            delete fInfo;
            printError(ErrSyntaxError, "Field %s does not exist in table",
                                                                name->fldName);
            return ErrSyntaxError;
        }
        FieldValue *newVal = new FieldValue();
        strcpy(newVal->fldName,name->fldName);
        newVal->parsedString = NULL;
        newVal->paramNo = 0;
        newVal->type = fInfo->type;
        newVal->isNullable = fInfo->isNull;
        newVal->length = fInfo->length;
        newVal->offset = fInfo->offset;
        newVal->isPrimary = fInfo->isPrimary;
        newVal->isUnique = fInfo->isUnique;
        newVal->isAutoIncrement = fInfo->isAutoIncrement;
        if (newVal->type == typeBinary)
            newVal->value = AllDataType::alloc(fInfo->type, 2 * fInfo->length);
        else newVal->value = AllDataType::alloc(fInfo->type, fInfo->length);
        newVal->isAllocVal=true;
        parsedData->insertFieldValue(newVal);
        aggTable->setGroup(name->fldName, newVal->value);
    }
    delete fInfo;
    aggTable->setCondition(parsedData->getHavingCondition());
    /*if (giter.hasElement()) 
    { 
       printError(ErrSyntaxError, "Only one field allowed in group\n");
       return ErrSyntaxError; 
    }*/
    table = aggTable;
    isGrpFld = true;
    return OK; 
}

DbRetVal SelStatement::resolveStar()
{
    DbRetVal rv = OK;
    parsedData->clearFieldNameList();
    FieldValue *newVal = NULL;
    List fNameList = table->getFieldNameList();
    ListIterator fNameIter = fNameList.getIterator();
    //fNameList.resetIter(); //do not remove this.
    FieldInfo *fInfo = new FieldInfo();
    for (int i = 0; i < fNameList.size() ; i++)
    {
        char *fName = ((Identifier*)(fNameIter.nextElement()))->name;
        rv = table->getFieldInfo(fName, fInfo);
        if (ErrNotFound == rv || ErrNotExists == rv)
        {
            delete fInfo;
            fNameList.reset();
            printError(ErrSysFatal, "Should never happen.");
            return ErrSysFatal;
        }
        newVal = new FieldValue();
        strcpy(newVal->fldName,fName);
        newVal->parsedString = NULL;
        newVal->paramNo = 0;
        newVal->type = fInfo->type;
        newVal->length = fInfo->length;
        newVal->offset = fInfo->offset;
        newVal->isPrimary = fInfo->isPrimary;
        newVal->isUnique = fInfo->isUnique;
        newVal->isAutoIncrement = fInfo->isAutoIncrement;

        // for binary datatype input buffer size should be 2 times the length 
        if(newVal->type == typeBinary) 
            newVal->value = AllDataType::alloc(fInfo->type, 2 * fInfo->length);
        else newVal->value = AllDataType::alloc(fInfo->type, fInfo->length);
        newVal->isAllocVal=true;
        newVal->isInResSet = true;
        parsedData->insertFieldValue(newVal);
        parsedData->insertField(fName);
        rv = table->bindFld(fName, newVal->value);
        if (rv != OK) { 
            delete fInfo;
            return rv;
        }
    }
    fNameIter.reset();
    while (fNameIter.hasElement())
        delete (Identifier *) fNameIter.nextElement();
    fNameList.reset();
    delete fInfo;
    return OK;
}

DbRetVal SelStatement::setBindFieldAndValues()
{
    totalFields = parsedData->getFieldNameList().size();
    bindFields = (FieldValue**) malloc ( totalFields * sizeof(FieldValue*));
    bindFieldValues = (char**) malloc( totalFields * sizeof(char*));
    memset(bindFields, 0, totalFields * sizeof(FieldValue*));
    memset(bindFieldValues, 0, totalFields * sizeof(char*));
    ListIterator valIter = parsedData->getFieldValueList().getIterator();
    int colNo =0;
    FieldValue *value = NULL;
    //The second condition colNo < totalFields is important for projection list
    //might not contain the binded having field. 
    while(valIter.hasElement() && colNo < totalFields)
    {
        value = (FieldValue*) valIter.nextElement();
        if (value == NULL)
        {
            free(bindFields); bindFields = NULL;
            free(bindFieldValues); bindFieldValues = NULL;
            printError(ErrSysFatal, "Should never happen. value NULL after iteration");
            return ErrSysFatal;
        }
        bindFields[colNo++] = value;
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
            delete fInfo;
            printError(ErrSysFatal, "Should never happen.");
            return ErrSysFatal;
        }
        if(!value->isFunctionInvolve){
            rv = table->getFieldInfo(value->fName, fInfo);
            if (ErrNotFound == rv || ErrNotExists == rv)
            {
                delete fInfo;
                printError(ErrSyntaxError, "Field %s does not exist in table", 
                                        value->fName);
                return ErrSyntaxError;
            }
            if (value->aType == AGG_AVG) {
                value->type = typeDouble;
                value->length = sizeof(double);
            } else if (value->aType == AGG_COUNT) {
                value->type = typeInt;
                value->length = sizeof(int);
            } else {
                value->type = fInfo->type;
                value->length = fInfo->length;
            }
            value->isNullable = fInfo->isNull;
        }else{
             value->type = AllDataType::getCsqlTypeFromFunctionTypeForComparision(parsedData->getFunctionType());
        }
        value->value = AllDataType::alloc(value->type, value->length);
        //table->bindFld(name->fldName, value->value);
        if(value->paramNo ==1) continue;//For Predecate t1.f1=t2.f1
        if (value->parsedString == NULL)
        {
            delete fInfo;
            printError(ErrSyntaxError, "Condition value should not be NULL"); 
            return ErrSyntaxError;
        }
        if (value->parsedString[0] == '?')
        {
		//if(!value->opLike) // checks if 'LIKE' operator is used
                value->paramNo = paramPos++;
        }
        if (!value->paramNo) {
	        // for valid Integer 
            if (value->type  == typeDate || value->type == typeTime ||
                value->type == typeTimeStamp)
                parsedData->setCacheWorthy(false);
	        if((value->type == typeInt) || (value->type==typeShort) || 
                (value->type==typeByteInt) || (value->type==typeLongLong) || 
                                                     (value->type==typeLong)) {
	            int len=strlen(value->parsedString);
	            for(int n=0;n<len;n++){
	                int p=value->parsedString[n];
	                if(!(p>=48 && p<=57 || p==45)) return ErrBadArg;
	            }
	        }
		     		    
	        // Here for binary dataType it is not strcpy'd bcos internally memcmp is done for predicates like f2 = 'abcd' where f2 is binary
            AllDataType::strToValue(value->value, value->parsedString, value->type, value->length);
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
        if (value->paramNo) params[value->paramNo - 1] = value;
    }
    return OK;
}
bool SelStatement::isGroupFld(char *fieldName)
{
    ListIterator giter = parsedData->getGroupFieldNameList().getIterator();
    FieldName *name = NULL;
    while (giter.hasElement())
    {
        name = (FieldName*) giter.nextElement();
        if (0 == strcmp(name->fldName, fieldName)) return true;
    }
    return false;
}

void* SelStatement::handleSingleTableAggWithoutGroup()
{
    if (isPointReturned) return NULL;
    TableImpl *tblImpl = (TableImpl*)table;
    ListIterator iter = parsedData->getFieldNameList().getIterator();
    int i=0;
    DbRetVal rv = OK;
    FieldName *name;
    FieldValue *fVal = NULL;
    bool noRec = false;
    while (iter.hasElement())
    {
        name = (FieldName*) iter.nextElement();
        fVal = bindFields[i];
        
        rv = tblImpl->fetchAgg(name->fldName, name->aType, fVal->value, noRec);
        if (OK != rv) return NULL;
        i++;
        tblImpl->closeScan();
        tblImpl->execute();
    }
    isPointReturned = true;
    if(noRec && name->aType != AGG_COUNT) return NULL;
    return fVal;
}
void* SelStatement::fetch()
{
    void *tuple = NULL;
    if(handleAggWithTbl)
    {
       tuple = handleSingleTableAggWithoutGroup();
       if (NULL == tuple) return NULL;
    }else {
        if (isOffsetReached) {
            if (!isRecLimitReached) {
                tuple = table->fetch();
                if (NULL != tuple) numRecords++;
                if (numRecords == parsedData->getLimit()) isRecLimitReached=true;
            }
        }
        else {
          int recordOffset =0;
          while(recordOffset <= parsedData->getOffset()) {
            tuple = table->fetch();
            if (NULL == tuple) break;
            recordOffset++;
          }
          isOffsetReached = true;
          if (NULL != tuple) numRecords++;
          if (numRecords == parsedData->getLimit()) isRecLimitReached=true;
        }
    }
    if (NULL == tuple) return NULL;

    //copy values to binded buffer
    FieldValue *value;
    for (int i = 0; i < totalFields; i++)
    {
        value = bindFields[i];
        if (bindFieldValues[i] == NULL) 
        {
            printError(ErrBadCall, "Fields are not binded properly. Should never happen");
            return NULL;
        }
	AllDataType::copyVal(bindFieldValues[i], value->value, value->type, value->length);
    }
    return tuple;
}

void* SelStatement::fetch(DbRetVal &rv)
{
    void *tuple = NULL;
    if(handleAggWithTbl)
    {
        tuple = handleSingleTableAggWithoutGroup();
        if (NULL == tuple) return NULL;
    }else {
        if (isOffsetReached) {
            if (!isRecLimitReached) {
                tuple = table->fetch(rv);
                if (NULL != tuple) numRecords++;
                if (numRecords == parsedData->getLimit()) isRecLimitReached=true;
            }
        } else {
            int recordOffset =0;
            while(recordOffset <= parsedData->getOffset()) {
                tuple = table->fetch(rv);
                if (NULL == tuple) break;
                recordOffset++;
            }
            isOffsetReached = true;
            if (NULL != tuple) numRecords++;
            if (numRecords == parsedData->getLimit()) isRecLimitReached=true;
        }
    }
    if (NULL == tuple) return NULL;
    //copy values to binded buffer
    FieldValue *value;
    for (int i = 0; i < totalFields; i++)
    {
        value = bindFields[i];
        if (bindFieldValues[i] == NULL) 
        {
            printError(ErrBadCall, "Fields are not binded properly. Should never happen %d", i);
            return NULL;
        }
		AllDataType::copyVal(bindFieldValues[i], value->value, value->type, value->length);
    }
    return tuple;
}

DbRetVal SelStatement::close()
{
    isPointReturned = false;
    if (table) return table->closeScan();
    else return OK;
}

void* SelStatement::getParamValuePtr( int pos )
{
    ConditionValue *p = (ConditionValue*) params [pos-1];
    return ( (void*) p->value );
}

char* SelStatement::getFieldName ( int pos )
{
    //TODO::if not yet prepared return error
    //TODO::check the upper limit for projpos
    ListIterator iter = parsedData->getFieldNameList().getIterator();
    int position = 1;
    while (iter.hasElement())
    {
        FieldName *name = (FieldName*) iter.nextElement();
        if (position == pos) {
              if (NULL == name)
              {
                  printError(ErrSysFatal, "Should never happen. Field Name list has NULL");
                  return (char*) 0;
              }
              return name->fldName;
        }
        position++;
    }
    return (char*) 0;
}

DataType SelStatement::getFieldType( int pos )
{
    FieldValue *v = bindFields[pos];
    return ( (DataType) v->type );
}

int SelStatement::getFieldLength( int pos )
{
    FieldValue *v = bindFields[pos];
    return ( (int) v->type );
}

void* SelStatement::fetchAndPrint(bool SQL)
{
    void *tuple = NULL;
    if(handleAggWithTbl)
    {
       tuple = handleSingleTableAggWithoutGroup();
    }else {
        if (isOffsetReached) {
            if (!isRecLimitReached) {
                tuple = table->fetch(); 
                if (NULL != tuple) numRecords++;
                if (numRecords == parsedData->getLimit()) isRecLimitReached=true;
            }
        }
        else {
          int recordOffset =0;
          while(recordOffset <= parsedData->getOffset()) {
            tuple = table->fetch(); 
            if (NULL == tuple) break;
            recordOffset++;
          }
          isOffsetReached = true;
          if (NULL != tuple) numRecords++;
          if (numRecords == parsedData->getLimit()) isRecLimitReached=true;
        }
    }
    if (NULL == tuple) return NULL;
    FieldValue *value;
    bool nullValueSet;
    char stmt[128];
    if (SQL) {
        sprintf(stmt, "INSERT INTO %s VALUES(", table->getName());
        printf("%s", stmt);
    }
    for (int i = 0; i < totalFields; i++)
    {
        value = bindFields[i];
        if (!value->isInResSet) continue;
        nullValueSet = table->isFldNull(value->fldName);
        if (nullValueSet) {
            if (SQL) { 
                if (i==0) 
                    printf("NULL"); 
                else
                    printf(", NULL"); 
            }
            else if (value->aType != AGG_COUNT) printf("NULL\t");
            else printf("0\t");
        }
        else  {
            if (SQL) {
                switch(value->type)
                {
                    case typeString:
                    case typeVarchar:
                    case typeBinary:
                    case typeDate:
                    case typeTime:
                    case typeTimeStamp:
                    {
                        if (i==0) 
                            printf(" '"); 
                        else
                            printf(", '");
                        break;
                    }
                    default:
                    {
                        if (i!=0) 
                           printf(",");
                    }
                }
            }
            AllDataType::printVal(value->value, value->type, value->length);
            if (SQL) {
                switch(value->type)
                {
                    case typeString:
                    case typeVarchar:
                    case typeBinary:
                    case typeDate:
                    case typeTime:
                    case typeTimeStamp:
                        printf("'");
                }
            } else printf("\t");
        }
    }
    if (SQL) printf(");\n");
    return tuple;
}

void* SelStatement::next()
{
    if(handleAggWithTbl)
    {
       return handleSingleTableAggWithoutGroup();
    }
    return( table->fetch() );
}


void* SelStatement::getFieldValuePtr( int pos )
{
    FieldValue *v = bindFields[pos];
    return ( (void*) v->value );
}

void* SelStatement::getFieldValuePtr( char *name )
{
    FieldValue *value;
    char fName[IDENTIFIER_LENGTH];
    for (int i = 0; i < totalFields; i++)
    {
        value = bindFields[i];
        table->getFieldNameAlone(value->fldName,fName);
        if (strcmp(fName,name)==0)
        {
            return ( (void*) value->value );
        }
        
    }
    return NULL;
}
void SelStatement::getProjFieldType(int *data)
{
    FieldValue *value;
    for (int i = 0; i < totalFields; i++)
    {
        value = bindFields[i];
        data[i+1] = value->type; 
    }
}

int SelStatement::noOfProjFields()
{
    return totalFields;
}

DbRetVal SelStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{

    DbRetVal rv = OK;
    //TODO::if not yet prepared return error
    //TODO::check the upper limit for projpos
    if (projpos < 0 || projpos >totalFields) return ErrBadArg;
    FieldValue *value = bindFields[projpos-1];
    fInfo->type = value->type;
    fInfo->length= value->length;
    fInfo->isNull = value->isNullable;
    fInfo->aType = value->aType;
    fInfo->offset = value->offset;
    fInfo->isPrimary = value->isPrimary;
    fInfo->isUnique = value->isUnique;
    fInfo->isAutoIncrement= value->isAutoIncrement;
    fInfo->isDefault = value->isDefault;
    if (fInfo->aType == AGG_UNKNOWN) {
        strcpy(fInfo->fldName, value->fldName);
        if (fInfo->isDefault) strcpy(fInfo->defaultValueBuf, value->defValBuf); 
        return OK;
    }
    switch(fInfo->aType)
    {
       case AGG_COUNT:
           sprintf(fInfo->fldName, "COUNT(%s)",  value->fldName);
           fInfo->type = typeInt;
           fInfo->length = sizeof(int);
           break;
       case AGG_MIN:
           sprintf(fInfo->fldName, "MIN(%s)",  value->fldName);
           break;
       case AGG_MAX:
           sprintf(fInfo->fldName, "MAX(%s)",  value->fldName);
           break;
       case AGG_SUM:
           sprintf(fInfo->fldName, "SUM(%s)",  value->fldName);
           break;
       case AGG_AVG:
           sprintf(fInfo->fldName, "AVG(%s)",  value->fldName);
           fInfo->type = typeDouble;
           fInfo->length = sizeof(double);
           break;
       default:
           strcpy(fInfo->fldName, value->fldName);
           break;
    }
    return rv;
}
int SelStatement::getFldPos(char *name)
{
    return table->getFldPos(name);
}

bool SelStatement::isInProjectionList(char *name, AggType aType) 
{
    ListIterator iter = parsedData->getFieldNameList().getIterator();
    FieldName *fldName = NULL;
    while (iter.hasElement()) {
        fldName = (FieldName*) iter.nextElement();
        if ((strcmp(fldName->fldName, name)==0) && fldName->aType == aType) {
            return true;
        }
    }
    return false;
}

