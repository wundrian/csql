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


void ParsedData::insertValue(char *val)
{
    FieldValue *newVal = new FieldValue();
    newVal->parsedString = strdup(val);
    newVal->value = NULL;
    newVal->paramNo = 0;
    newVal->type = typeUnknown;
    newVal->length = 0;
    fieldValueList.append(newVal);
}

void** ParsedData::insertCondValueAndGetPtr(char *fldName, char *val)
{
    ConditionValue *newVal = new ConditionValue();
    newVal->parsedString = strdup(val);
    newVal->value = NULL;
    newVal->paramNo = 0;
    newVal->type = typeUnknown;
    newVal->length = 0;
    strcpy(newVal->fName, fldName);
    conditionValueList.append(newVal);
    return &(newVal->value);

}

void ParsedData::insertField(char *fName)
{
    FieldName *newVal = new FieldName();
    strcpy(newVal->fldName , fName);
    fieldNameList.append(newVal);
}

void ParsedData::insertUpdateValue(char *fName, char *val)
{
    UpdateFieldValue *newVal = new UpdateFieldValue();
    strcpy(newVal->fldName, fName);
    newVal->parsedString = strdup(val);
    newVal->value = NULL;
    newVal->paramNo = 0;
    updFldValList.append(newVal);
}

Predicate* ParsedData::insertPredicate(char *fName, ComparisionOp op, void **val)
{
    Condition cond;
    cond.setTerm(fName, op, val);
    return cond.getPredicate();
}

Predicate* ParsedData::insertPredicate(Predicate *p1, LogicalOp op, Predicate *p2)
{
    Condition cond;
    cond.setTerm(p1, op, p2);
    return cond.getPredicate();
}

void ParsedData::reset()
{
    fieldNameList.reset();
    ListIterator iter = fieldValueList.getIterator();
    FieldValue *value;
    while (iter.hasElement())
    {
        value = (FieldValue*)iter.nextElement();
        free(value->parsedString);
        free(value->value);
    }
   
    fieldValueList.reset();
    predicate.reset();
    conditionValueList.reset();
    
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

void ParsedData::insertFldDef()
{
    DbRetVal rv = creFldList.append(fldDef);
    fldDef.init();
}
