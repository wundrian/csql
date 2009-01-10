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
    if (table) {
        table->setCondition(NULL);
        //if (dbMgr) dbMgr->closeTable(table);
        table->close();
        delete table;
    }
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
    rv = table->execute();
    //table->printPlan(0);
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

DbRetVal SelStatement::setBinaryParam(int paramNo, void *value)
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
DbRetVal SelStatement::openTables()
{
    if (dbMgr == NULL) return ErrNoConnection;
    JoinTableImpl *jHdl = NULL;
    Table *tHdl = NULL, *prevHdl = NULL;
    bool joinInvolved = false;
    //check whether all the table exists
    ListIterator titer = parsedData->getTableNameList().getIterator();
    while (titer.hasElement())
    {
        TableName *t  = (TableName*)titer.nextElement();
        tHdl = dbMgr->openTable(t->tblName);
        if ( NULL == tHdl ) 
        {
            printError(ErrNotExists, 
                       "Unable to open the table:Table not exists");
            return ErrNotExists;
        }
        if (NULL != prevHdl) 
        { 
            joinInvolved = true;
            jHdl = new JoinTableImpl();
            jHdl->setTable(prevHdl, tHdl);
            prevHdl = jHdl;
            continue;
        }
        prevHdl = tHdl;
    }
    if (joinInvolved) table = jHdl; else table = tHdl;
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
            if (parsedData->getGroupFieldNameList().size()!= 0)
            {
                if (!aggTable)
                    aggTable = new AggTableImpl();
                aggTable->setTable(table);
            }
            //as soon as it encounters *, it breaks the loop negleting other field names
            //as they all are deleted during resolveStar method.
            break;
        }else {
            if ('*' == name->fldName[0] && name->aType != AGG_COUNT) {return ErrSyntaxError;}
            rv = table->getFieldInfo(name->fldName, fInfo);
            if (ErrNotFound == rv || ErrNotExists == rv)
            {
                dbMgr->closeTable(table);
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
            newVal->type = fInfo->type;
            newVal->length = fInfo->length;
            newVal->isNullable = fInfo->isNull;
            FieldName *bFldName=NULL;
            ListIterator it = bindFldList.getIterator();
            while (it.hasElement())
            {
                bFldName = (FieldName*)it.nextElement();
                if(0==strcmp(bFldName->fldName,name->fldName))
                {
                    newVal->value=table->getBindFldAddr(name->fldName);
                    newVal->isAllocVal=false;
                    isBindFld=true;
                    break;
                }
            }
            if (!isBindFld) {
                if(newVal->type == typeBinary)
                    newVal->value = AllDataType::alloc(fInfo->type, 
                                                       2 * fInfo->length);
                else newVal->value = AllDataType::alloc(fInfo->type, 
                                                        fInfo->length);
                newVal->isAllocVal=true;
            }
            if (name->aType ==AGG_UNKNOWN && 
                            parsedData->getGroupFieldNameList().size()== 0)
                table->bindFld(name->fldName, newVal->value);
            else {
                if (!aggTable)
                    aggTable = new AggTableImpl();
                aggTable->setTable(table);
                aggTable->bindFld(name->fldName, name->aType, newVal->value);
            }
            parsedData->insertFieldValue(newVal);
        } 
        if (!isBindFld) bindFldList.append(name);
    }
    rv = setBindFieldAndValues();
    if (rv != OK) 
    {
        delete fInfo;
        dbMgr->closeTable(table);
        table = NULL;
        return rv;
    }

    table->setCondition(parsedData->getCondition());

    rv = resolveForCondition();
    if (rv != OK) 
    {
        delete fInfo;
        //TODO::free memory allocated for params
        table->setCondition(NULL);
        dbMgr->closeTable(table);
        table = NULL;
        return rv;
    }
    rv = resolveGroupFld(aggTable);
    if (rv != OK) 
    {
        delete fInfo;
        //TODO::free memory allocated for params
        if (table) 
        {
            table->setCondition(NULL);
            dbMgr->closeTable(table);
        }
        table = NULL;
        return rv;
    }
    delete fInfo;
    return rv;
}
DbRetVal SelStatement::resolveGroupFld(AggTableImpl *aggTable)
{
    if (!aggTable) return OK;
    ListIterator giter = parsedData->getGroupFieldNameList().getIterator();
    FieldName *name = NULL;
    DbRetVal rv = OK;
    FieldInfo *fInfo = new FieldInfo();
    if (giter.hasElement())
    {
        name = (FieldName*)giter.nextElement();
        rv = table->getFieldInfo(name->fldName, fInfo);
        if (ErrNotFound == rv || ErrNotExists == rv)
        {
            dbMgr->closeTable(table);
            table = NULL;
            delete fInfo;
            delete aggTable;
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
        if (newVal->type == typeBinary)
            newVal->value = AllDataType::alloc(fInfo->type, 2 * fInfo->length);
        else newVal->value = AllDataType::alloc(fInfo->type, fInfo->length);
        newVal->isAllocVal=true;
        parsedData->insertFieldValue(newVal);
        aggTable->setGroup(name->fldName, newVal->value);
    }
    if (giter.hasElement()) { table= aggTable; return ErrSyntaxError; }
    table = aggTable;
    return OK; 
}
DbRetVal SelStatement::resolveStar()
{
    DbRetVal rv = OK;
    parsedData->clearFieldNameList();

    List fNameList = table->getFieldNameList();
    ListIterator fNameIter = fNameList.getIterator();
    FieldValue *newVal = NULL;
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
        // for binary datatype input buffer size should be 2 times the length 
        if(newVal->type == typeBinary) 
            newVal->value = AllDataType::alloc(fInfo->type, 2 * fInfo->length);
        else newVal->value = AllDataType::alloc(fInfo->type, fInfo->length);
	newVal->isAllocVal=true;
        parsedData->insertFieldValue(newVal);
        parsedData->insertField(fName);
        table->bindFld(fName, newVal->value);
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
    valIter.reset();
    while(valIter.hasElement())
    {
        value = (FieldValue*) valIter.nextElement();
        if (value == NULL)
        {
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
            delete fInfo;
            printError(ErrSysFatal, "Should never happen.");
            return ErrSysFatal;
        }
        rv = table->getFieldInfo(value->fName, fInfo);
        if (ErrNotFound == rv || ErrNotExists == rv)
        {
            delete fInfo;
            printError(ErrSyntaxError, "Field %s does not exist in table", 
                                        value->fName);
            return ErrSyntaxError;
        }
        value->type = fInfo->type;
        value->length = fInfo->length;
        value->isNullable = fInfo->isNull;
        value->value = AllDataType::alloc(fInfo->type, fInfo->length);
        //table->bindFld(name->fldName, value->value);
        if (value->parsedString == NULL)
        {
            delete fInfo;
            printError(ErrSyntaxError, "Condition value should not be NULL"); 
            return ErrSyntaxError;
        }
        if (value->parsedString[0] == '?')
        {
		if(!value->opLike) // checks if 'LIKE' operator is used
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
            printError(ErrBadCall, "Fields are not binded properly. Should never happen");
            return NULL;
        }
		AllDataType::copyVal(bindFieldValues[i], value->value, value->type, value->length);
    }
    return tuple;
}

void* SelStatement::fetch(DbRetVal &rv)
{
    void *tuple = table->fetch(rv);
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
    return table->close();
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
    int position =0;
    while (iter.hasElement())
    {
        if (position == pos) {
              FieldName *name = (FieldName*) iter.nextElement();
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
    void *tuple = table->fetch();
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
        nullValueSet = table->isFldNull(value->fldName);
        if (nullValueSet) 
            if (SQL) { 
                if (i==0) 
                    printf("NULL"); 
                else
                    printf(", NULL"); 
            }
            else printf("NULL\t");
        else  {
            if (SQL) {
                switch(value->type)
                {
                    case typeString:
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
    return( table->fetch() );
}


void* SelStatement::getFieldValuePtr( int pos )
{
    FieldValue *v = bindFields[pos];
    return ( (void*) v->value );
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
        if (position == (projpos-1)) break;
        position++;
    }

    rv = table->getFieldInfo(name->fldName, fInfo);
}
int SelStatement::getFldPos(char *name)
{
    return table->getFldPos(name);
}


