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
#include "Parser.h"
#include <CSql.h>
#include<PredicateImpl.h>


void ParsedData::insertValue(char *val)
{
    FieldValue *newVal = new FieldValue();
    if (val == NULL) 
        newVal->parsedString = NULL;
    else 
        newVal->parsedString = strdup(val);
    strcpy(newVal->fldName," ");
    newVal->value = NULL;
    newVal->paramNo = 0;
    newVal->type = typeUnknown;
    newVal->length = 0;
    newVal->isAllocVal=false;
    fieldValueList.append(newVal);
}

void ParsedData::insertInValue(char *val)
{
    FieldValue *newVal = new FieldValue();
    if (val == NULL) 
        newVal->parsedString = NULL;
    else 
        newVal->parsedString = strdup(val);
    strcpy(newVal->fldName," ");
    newVal->value = NULL;
    newVal->paramNo = 0;
    newVal->type = typeUnknown;
    newVal->length = 0;
    newVal->isAllocVal=false;
    inValueList.append(newVal);
}

void** ParsedData::insertCondValueAndGetPtr(char *fldName, char *val, bool opLike)
{
    ConditionValue *newVal = new ConditionValue();
    if (val == NULL) 
        newVal->parsedString = NULL;
    else
        newVal->parsedString = strdup(val);
    newVal->value = NULL;
    newVal->paramNo = 0;
    newVal->type = typeUnknown;
    newVal->length = 0;
    strcpy(newVal->fName, fldName);
	newVal->opLike = opLike;
    conditionValueList.append(newVal);
    return &(newVal->value);

}
void ParsedData::insertCondValue(char *fldName)
{
    ConditionValue *newVal = new ConditionValue();
    newVal->parsedString = NULL;
    newVal->value = NULL;
    newVal->paramNo = 1;//To solve parsedString Null problem
    newVal->type = typeUnknown;
    newVal->length = 0;
    strcpy(newVal->fName, fldName);
    newVal->opLike = false;
    conditionValueList.append(newVal);
}
void ParsedData::insertField(char *fName, AggType type)
{
    FieldName *newVal = new FieldName();
    strcpy(newVal->fldName , fName);
    newVal->aType = type;
    fieldNameList.append(newVal);
}
void ParsedData::insertTableName(char *tName)
{
    TableName *newVal = new TableName();
    strcpy(newVal->tblName , tName);
    tableNameList.append(newVal);
}
void ParsedData::insertGroupField(char *fName)
{
    FieldName *newVal = new FieldName();
    strcpy(newVal->fldName , fName);
    groupFieldNameList.append(newVal);
}

void ParsedData::insertUpdateValue(char *fName, char *val)
{
    UpdateFieldValue *newVal = new UpdateFieldValue();
    strcpy(newVal->fldName, fName);
    if (val == NULL) 
        newVal->parsedString = NULL;
    else 
        newVal->parsedString = strdup(val);
    newVal->value = NULL;
    newVal->expre = NULL;
    newVal->paramNo = 0;
    updFldValList.append(newVal);
}

Predicate* ParsedData::insertPredicate(char *fName, ComparisionOp op, void **val)
{
    PredicateImpl *pImpl = new PredicateImpl();
    pImpl->setTerm(fName, op, val);
    return (Predicate*) pImpl;
}
Predicate* ParsedData::insertBetPredicate(char *fName, ComparisionOp op1, 
                            void **val1, ComparisionOp op2, void **val2)
{
    PredicateImpl *pImpl = new PredicateImpl();
    pImpl->setTerm(fName, op1, val1, op2, val2);
    return (Predicate*) pImpl;
}
Predicate* ParsedData::insertPredicate(char *fName1, ComparisionOp op, char *fName2)
{
    PredicateImpl *pImpl = new PredicateImpl();
    pImpl->setTerm(fName1, op, fName2);
    return (Predicate*) pImpl;
}

Predicate* ParsedData::insertPredicate(Predicate *p1, LogicalOp op, Predicate *p2)
{
    PredicateImpl *pImpl = new PredicateImpl();
    pImpl->setTerm(p1, op, p2);
    return (Predicate*) pImpl;
}

void ParsedData::reset()
{
    ListIterator fNameIter = fieldNameList.getIterator();
    fNameIter.reset();
    while (fNameIter.hasElement())
        delete ((FieldName *) fNameIter.nextElement());
    fieldNameList.reset();
    ListIterator iter = fieldValueList.getIterator();
    FieldValue *value;
    while (iter.hasElement())
    {
        value = (FieldValue*)iter.nextElement();
        free(value->parsedString);
        if (value->isAllocVal) free(value->value);
        delete value;
    }
    fieldValueList.reset();
    ListIterator inIter = inValueList.getIterator();
    while (inIter.hasElement()) {
        value = (FieldValue *) inIter.nextElement();    
        if (value->parsedString) free(value->parsedString);
        delete value;
    }
    inValueList.reset();

    predicate.reset();

    iter = conditionValueList.getIterator();
    ConditionValue *condVal;
    while (iter.hasElement())
    {
        condVal = (ConditionValue*)iter.nextElement();
        free(condVal->parsedString);
        free(condVal->value);
        delete condVal;
    }
    conditionValueList.reset();

    iter = updFldValList.getIterator();
    UpdateFieldValue *updFldVal;
    while (iter.hasElement())
    {
        updFldVal = (UpdateFieldValue*)iter.nextElement();
        if(updFldVal->parsedString!=NULL)
           free(updFldVal->parsedString);
        if(updFldVal->expre!=NULL){
           updFldVal->expre->freeVal();
           delete updFldVal->expre;
        }
        free(updFldVal->value);
        delete updFldVal;
    }
    updFldValList.reset();
    iter = groupFieldNameList.getIterator();
    while(iter.hasElement())
    {
        delete iter.nextElement();
    }
    groupFieldNameList.reset();

    iter = tableNameList.getIterator();
    TableName *tname;  
    while (iter.hasElement())
    {
        tname = (TableName*)iter.nextElement();
        delete tname;
    }
    tableNameList.reset(); 
    
    creFldList.removeAll();
    isUnique = false; 
    isPrimary = false; 
    bucketSize = 0;
    indexType = hashIndex;
}
void ParsedData::clearFieldNameList()
{
    ListIterator it = fieldNameList.getIterator();
    while (it.hasElement()) delete ((FieldName *) it.nextElement());
    fieldNameList.reset();
}

void ParsedData::setFldName(char *name)
{
    strcpy(fldDef.fldName_, name);
    fldDef.fldName_[IDENTIFIER_LENGTH] = '\0';
}

void ParsedData::setFldType(DataType type)
{
    fldDef.type_ = type;
}

DbRetVal ParsedData::setFldLength(size_t length)
{
    if(fldDef.type_ == typeBinary && (length-1) && (length-1) <= 256) {
        fldDef.length_ = length - 1; return OK;
    }
    else if (fldDef.type_ == typeBinary && (length-1) > 256) {
        return ErrBadRange;
    }
    else { fldDef.length_ = length; return OK; }
}

void ParsedData::setFldNotNull(bool notNull)
{
    fldDef.isNull_ = notNull;
}
void ParsedData::setDefaultValue(char *value)
{
    fldDef.isDefault_ = true;
    if (strlen(value) > DEFAULT_VALUE_BUF_LENGTH -1) 
    {
        strncpy(fldDef.defaultValueBuf_, value, DEFAULT_VALUE_BUF_LENGTH -1);
        fldDef.defaultValueBuf_[DEFAULT_VALUE_BUF_LENGTH] ='\0';
    } else
        strcpy(fldDef.defaultValueBuf_, value);
    return;
}


void ParsedData::insertFldDef()
{
    DbRetVal rv = creFldList.append(fldDef);
    fldDef.init();
}

Expression* ParsedData::insertExpression(char *fldName)
{
    Expression *exp =new Expression();
    exp->setExpr(fldName);
    return exp;
}
Expression* ParsedData::insertExpression(char *value,bool flag)
{
    Expression *exp =new Expression();
    exp->setExpr(strdup(value),flag);
    return exp;
}
Expression* ParsedData::insertExpression(Expression* exp1, ArithOperator op ,Expression* exp2)
{
    Expression *exp =new Expression();
    exp->setExpr(exp1, op, exp2);
    return exp;
}
void ParsedData::insertUpdateExpression(char *fName, Expression *exp)
{
    UpdateFieldValue *newVal = new UpdateFieldValue();
    strcpy(newVal->fldName, fName);
    newVal->parsedString = NULL;
    newVal->value = NULL;
    newVal->expre=exp;
    newVal->paramNo = 0;
    updFldValList.append(newVal);
}
