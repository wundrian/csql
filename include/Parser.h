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
#include <AggTableImpl.h>
#include <JoinTableImpl.h>
#include <os.h>
#include <Util.h>
enum StatementType
{
    UnknownStatement,
    SelectStatement,
    InsertStatement,
    UpdateStatement,
    DeleteStatement,
    CreateTableStatement,
    DropTableStatement,
    CreateIndexStatement,
    DropIndexStatement
};

struct FieldValue
{
    char fldName[IDENTIFIER_LENGTH];
    char *parsedString;
    void *value;
    int paramNo; // 0 ->not a param. It stores the param position
    DataType type;
    int length;
    bool isNullable;
    bool isAllocVal;
};


struct ConditionValue
{
    char *parsedString;
    void *value;
    int paramNo; // 0 ->not a param. It stores the param position
    DataType type;
    int length;
    bool opLike;
    bool isNullable;
    char fName[IDENTIFIER_LENGTH];
};

struct FieldName
{
    char fldName[IDENTIFIER_LENGTH];
    AggType aType; //used only in case of select projection
    FieldName()
    {
        strcpy(fldName,"");
        aType = AGG_UNKNOWN;
    }
};
struct TableName
{
    char tblName[IDENTIFIER_LENGTH];
    TableName()
    {
        strcpy(tblName,"");
    }
};

struct UpdateFieldValue
{
    char fldName[IDENTIFIER_LENGTH];
    char *parsedString;
    void *value;
    Expression *expre;
    DataType type;
    int length;
    bool isNullable;
    int paramNo;
};


class ParsedData
{
    private:
    char tblName[IDENTIFIER_LENGTH];
    char idxName[IDENTIFIER_LENGTH];

    StatementType stmtType;
  
    int paramCounter;

    List tableNameList;
    //holds pointer to field names. used in insert to store field name list
    //and for projection list of select
    //also used to store primary or unique key fields in create statement
    List fieldNameList;

    List groupFieldNameList;

    //holds pointer to condition values.
    List conditionValueList;

    //holds pointer to field values. used in insert to store field values
    //used in update to store the current value returned by fetch().This gets replaced 
    //by value in updFldValList and then update() is called.
    List fieldValueList;

    //used to store IN values of SELECT statement
    //This should be a list of list. so that multiple IN shall be present
    //in the select statement
    List inValueList;

    //update field value list. used to store the values to be updated
    //value in the SET clause of UPDATE statement is stored here.
    List updFldValList;

    //stores the where clause condition for SELECT, UPDATE and DELETE
    Condition predicate;
    
    //stores field information in CREATE TABLE
    FieldDef fldDef;

    //stores list of fields for CREATE TABLE
    FieldList creFldList;

    //stores index information
    bool isUnique;
    bool isPrimary;
    IndexType indexType;

    public:
    ParsedData() { paramCounter = 0; stmtType = UnknownStatement; 
                 isUnique = false; isPrimary = false; indexType = hashIndex;} 
    void setStmtType(StatementType type) { stmtType = type; }
    void setTableName(char *name) { strcpy(tblName, name); }
    void setIndexName(char *name) { strcpy(idxName, name); }

    char* getTableName() { return tblName; }
    char* getIndexName() { return idxName; }

    void insertValue(char *value);
    void insertInValue(char *value);
	// third parameter is to avoid conflict between '?' between like operand and parameterized value in sql statement.
	// eg: select * from t1 where f1 = ? and f2 like '_ti%';
	// _ is converted to ? before it is processed
    void** insertCondValueAndGetPtr(char *fName, char *value, bool opLike=false);
    void insertUpdateValue(char *fldName, char *value);

    void insertField(char *fName, AggType aggType= AGG_UNKNOWN);
    void insertGroupField(char *fName);
    void clearFieldNameList();
    void insertTableName(char *value);


    Predicate* insertPredicate(char *fldName, ComparisionOp op, void** value);
    Predicate* insertPredicate(char *fldName, ComparisionOp op, char *fldName);
    Predicate* insertBetPredicate(char *fldName, ComparisionOp op1, void **value1, ComparisionOp op2, void **value2);
    Predicate* insertPredicate(Predicate *p1, LogicalOp op, Predicate *p2 = NULL);
    void setCondition(Predicate *pred) 
    { 
        //No body is deleting memory allocated during condition::setTerm for PredicateImpl 
        //have list in this pared data and delete it during reset
        predicate.setPredicate(pred); 
    }
    Condition* getCondition() { return &predicate; }

    void insertFieldValue(FieldValue *newVal) { fieldValueList.append(newVal); }

    List getFieldNameList() { return fieldNameList; }
    List getGroupFieldNameList() { return groupFieldNameList; }
    List getConditionValueList() { return conditionValueList; }
    List getFieldValueList() { return fieldValueList; }
    List getInValueList() { return inValueList; }
    List getUpdateFieldValueList() { return updFldValList; }
    List getTableNameList() { return tableNameList; }

    void setFldName(char *name);
    void setFldType(DataType type);
    DbRetVal setFldLength(size_t length);
    void setDefaultValue(char * value);
    //void setFldDefaultValue -- will need two parametersers, check how u want to pass default value.
    void setFldNotNull(bool notNull);

    void setUnique(bool unique){ isUnique = unique; }
    void setPrimary(bool primary) { isPrimary = primary; }
    void setIndexType (IndexType type) { indexType = type; }
    IndexType getIndexType(){ return indexType; }
    bool getUnique() { return isUnique; }
    bool getPrimary() { return isPrimary; }
    Expression* insertExpression(char *fldName);
    Expression* insertExpression(char *value, bool flag);
    Expression* insertExpression(Expression* exp1, ArithOperator op ,Expression* exp1);
    void insertUpdateExpression(char *fName, Expression *exp);

    void insertFldDef(); //check if fldDef needs to be a part of ParsedData 
    
    FieldList getCreFldList() { return creFldList; }

    StatementType getStmtType() { return stmtType; }

    void reset();

};

#endif

//TODO: Aruna
//variable and function names suck, change if u want to
//setFldDefaultValue
//finding out if fldDef needs to be part of parsedData, or can allocate memory and pass around
//primary key
//foreign key
