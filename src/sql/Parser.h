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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef PARSER_H
#define PARSER_H
#include <CSql.h>
#include <os.h>
#include <Util.h>
enum StatementType
{
    UnknownStatement,
    SelectStatement,
    InsertStatement,
    UpdateStatement,
    DeleteStatement
};

struct FieldValue
{
    char *parsedString;
    void *value;
    int paramNo; // 0 ->not a param. It stores the param position
    DataType type;
    int length;
};


struct ConditionValue
{
    char *parsedString;
    void *value;
    int paramNo; // 0 ->not a param. It stores the param position
    DataType type;
    int length;
    char fName[IDENTIFIER_LENGTH];
};

struct FieldName
{
    char fldName[IDENTIFIER_LENGTH];
};

struct UpdateFieldValue
{
    char *fldName;
    char *parsedString;
    void *value;
    int paramNo;
};


class ParsedData
{
    private:
    char tblName[IDENTIFIER_LENGTH];
    StatementType stmtType;
  
    int paramCounter;
    //holds pointer to field names. used in insert to store field name list
    //and for projection list of select
    List fieldNameList;

    //holds pointer to condition values.
    List conditionValueList;

    //holds pointer to field values. used in insert to store field values
    //used in update to store the current value returned by fetch().This gets replaced 
    //by value in updFldValList and then update() is called.
    List fieldValueList;

    //update field value list. used to store the values to be updated
    //value in the SET clause of UPDATE statement is stored here.
    List updFldValList;

    //stores the where clause condition for SELECT, UPDATE and DELETE
    Condition predicate;
    

    public:
    ParsedData() { paramCounter = 0; stmtType = UnknownStatement; } 
    void setStmtType(StatementType type) { stmtType = type; }
    void setTableName(char *name) { strcpy(tblName, name); }
    char* getTableName() { return tblName; }
    void insertValue(char *value);
    void** insertCondValueAndGetPtr(char *fName, char *value);
    void insertUpdateValue(char *fldName, char *value);

    void insertField(char *fName);
    void clearFieldNameList();


    Predicate* insertPredicate(char *fldName, ComparisionOp op, void** value);
    Predicate* insertPredicate(Predicate *p1, LogicalOp op, Predicate *p2 = NULL);
    void setCondition(Predicate *pred) { predicate.setPredicate(pred); }
    Condition* getCondition() { return &predicate; }

    void insertFieldValue(FieldValue *newVal) { fieldValueList.append(newVal); }

    List getFieldNameList() { return fieldNameList; }
    List getConditionValueList() { return conditionValueList; }
    List getFieldValueList() { return fieldValueList; }
    List getUpdateFieldValueList() { return updFldValList; }

    StatementType getStmtType() { return stmtType; }

    void reset();

};

#endif
