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
    creFldList.removeAll();
}
void ParsedData::clearFieldNameList()
{
    fieldNameList.reset();
}

void ParsedData::setFldName(char *name)
{
printf("In setFldName \n");
    strcpy(fldDef.fldName_, name);
    fldDef.fldName_[IDENTIFIER_LENGTH] = '\0';
printf("Value FldType %d \n", fldDef.type_);
}

void ParsedData::setFldType(DataType type)
{
printf("In setFldType %d \n", type);
    fldDef.type_ = type;
printf("Value n setFldType %d \n", fldDef.type_);
}

void ParsedData::setFldLength(size_t length)
{
printf("In setFldLength \n");
    fldDef.length_ = length;
}

void ParsedData::setFldNotNull(bool notNull)
{
printf("In setFldNotNull \n");
    fldDef.isNull_ = notNull;
}

void ParsedData::insertFldDef()
{
printf("In insertFldDef \n");
 printf("Value %s %d %d \n", fldDef.fldName_, fldDef.type_, fldDef.length_);
    DbRetVal rv = creFldList.append(fldDef);
}
