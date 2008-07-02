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
    newVal->value = NULL;
    newVal->paramNo = 0;
    newVal->type = typeUnknown;
    newVal->length = 0;
    fieldValueList.append(newVal);
}

void ParsedData::insertInValue(char *val)
{
    FieldValue *newVal = new FieldValue();
    if (val == NULL) 
        newVal->parsedString = NULL;
    else 
        newVal->parsedString = strdup(val);
    newVal->value = NULL;
    newVal->paramNo = 0;
    newVal->type = typeUnknown;
    newVal->length = 0;
    inValueList.append(newVal);
}

void** ParsedData::insertCondValueAndGetPtr(char *fldName, char *val)
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
    conditionValueList.append(newVal);
    return &(newVal->value);

}

void ParsedData::insertField(char *fName, AggType type)
{
    FieldName *newVal = new FieldName();
    strcpy(newVal->fldName , fName);
    newVal->aType = type;
    fieldNameList.append(newVal);
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
    newVal->paramNo = 0;
    updFldValList.append(newVal);
}

Predicate* ParsedData::insertPredicate(char *fName, ComparisionOp op, void **val)
{
    PredicateImpl *pImpl = new PredicateImpl();
    pImpl->setTerm(fName, op, val);
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
        delete (Identifier *) fNameIter.nextElement();
    fieldNameList.reset();
    ListIterator iter = fieldValueList.getIterator();
    FieldValue *value;
    while (iter.hasElement())
    {
        value = (FieldValue*)iter.nextElement();
        free(value->parsedString);
        free(value->value);
        delete value;
    }
    fieldValueList.reset();
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
        free(updFldVal->parsedString);
        free(updFldVal->value);
        delete updFldVal;
    }
    updFldValList.reset();
    groupFieldNameList.reset();
    
    creFldList.removeAll();
    isUnique = false; 
    isPrimary = false; 
    indexType = hashIndex;
}
void ParsedData::clearFieldNameList()
{
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

void ParsedData::setFldLength(size_t length)
{
    fldDef.length_ = length;
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
