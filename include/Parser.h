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
#include <Function.h>
#ifndef STMT_TYPE
#define STMT_TYPE
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
    DropIndexStatement,
    CacheTableStatement,
    CompactTableStatement,
    CopyTableStatement,
    MetaStatement,
    UserStatement,
    MgmtStatement,
    AlterStatement,
    TruncateStatement
};
#endif

struct FieldValue
{
    char fldName[IDENTIFIER_LENGTH];
    char defValBuf[DEFAULT_VALUE_BUF_LENGTH];
    char *parsedString;
    void *value;
    int paramNo; // 0 ->not a param. It stores the param position
    DataType type;
    AggType aType;
    int length;
    size_t offset;
    bool isNullable;
    bool isAllocVal;
    bool isInResSet;
    bool isPrimary;
    bool isUnique;
    bool isAutoIncrement;
    bool isDefault;
};


struct ConditionValue
{
    char *parsedString;
    void *value;
    int paramNo; // 0 ->not a param. It stores the param position
    DataType type;
    AggType aType;
    int length;
    bool opLike;
    bool isNullable;
    char fName[IDENTIFIER_LENGTH];
    bool isFunctionInvolve;
};

struct FieldName
{
    char fldName[IDENTIFIER_LENGTH];
    AggType aType; //used only in case of select projection
    char aliasFldName[IDENTIFIER_LENGTH];
    FieldName()
    {
        strcpy(fldName,"");
        strcpy(aliasFldName,"");
        aType = AGG_UNKNOWN;
    }
};
struct TableName
{
    char tblName[IDENTIFIER_LENGTH];
    char aliasName[IDENTIFIER_LENGTH];
    TableName()
    {
        strcpy(tblName,"");
        strcpy(aliasName,"");
    }
};
#ifndef JOINTYPE
#define JOINTYPE
enum JoinType
{
    INNER_JOIN = 1,
    RIGHT_JOIN,
    LEFT_JOIN,
    FULL_JOIN,
    UNKNOWN_JOIN
};
#endif

struct JoinTypeNode
{
    JoinType jType;
    JoinTypeNode(){ jType = INNER_JOIN; }
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

enum UserNodeType
{
    CREATEUSER=0,
    DROPUSER,
    ALTERUSER
};
enum AlterTableType
{
    ALTERADD=0,
    ALTERDROP,
    ALTERMODIFY,
    ALTERFIELDRENAME,
    ALTERTABLERENAME
};


class UserNode
{
    public:
    char userName[IDENTIFIER_LENGTH];
    char passName[IDENTIFIER_LENGTH];
    UserNodeType type;
};

class ParsedData
{
    private:
    char tblName[IDENTIFIER_LENGTH];
    char idxName[IDENTIFIER_LENGTH]; //Also used for rename table
    char pkTblName[IDENTIFIER_LENGTH];//This is also used as DSN name when cachestatement executed and copy table statemnet
    StatementType stmtType;
    bool isDistinct; 
    bool isExplain;
  
    int paramCounter;

    List tableNameList;
    List joinTypeList;
    //holds pointer to field names. used in insert to store field name list
    //and for projection list of select
    //also used to store primary or unique key fields in create statement
    List fieldNameList;

    List groupFieldNameList;
 
    List havingFieldNameList;

    List orderFieldNameList;

    //holds pointer to condition values.
    List conditionValueList;
    
    List secondaryIndexFieldList;
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
    Condition havingPredicate;
    List predList;
    
    //stores field information in CREATE TABLE
    FieldDef fldDef;
    //User Management
    UserNode *userNode;
    //stores list of fields for CREATE TABLE
    FieldList creFldList;
    //Foreign Key storage
    
    List fkFieldNameList;
    List pkFieldNameList;
    List foreignKeyList;
    bool isForeign;
    bool shouldCreateTbl;
    //ALTER Statement
    AlterTableType aTblType;
    //stores index information
    bool isUnique;
    bool isPrimary;
    bool isAutoIncrement;
    IndexType indexType;
    ResultSetPlan plan;
    int bucketSize;
    //Cache table 
    char hcondition[IDENTIFIER_LENGTH];
    char vcondition[IDENTIFIER_LENGTH];
    bool hCondFld;
    bool vCondFld;
    bool pkFld;
    bool forceOption;
    bool direct;
    bool uncache; 
    bool noschema;
    bool dsn;
    int limit;
    int offset;
    bool isWorthyToCache;
    FunctionType ftype;
    public:
    ParsedData() { limit = 0;  offset= 0; paramCounter = 0; stmtType = UnknownStatement;  isDistinct = false; isExplain=false;
                 isUnique = false; isPrimary = false; isAutoIncrement=false ;indexType = hashIndex; plan = Normal; bucketSize=0; isForeign=false; hCondFld=false; vCondFld=false;pkFld=false;forceOption=false; direct=false; uncache=false; noschema=false; dsn=false; 
    shouldCreateTbl=false; userNode = NULL; isWorthyToCache=false; ftype = UNKNOWN_FUNCTION;
    } 
    void setFunctionType(FunctionType type) { ftype = type; }
    FunctionType getFunctionType(){ return ftype;}
    void setAlterType(AlterTableType type){ aTblType = type;}
    AlterTableType getAlterType(){ return aTblType; }
    
    void createUserNode(char *name, char *password);
    char *getUserName() { return userNode->userName; }
    char *getPassWord() { return userNode->passName; }
    UserNodeType getUserType() { return userNode->type; }
    void dropUserNode(char *name);
    void alterUserNode(char *name, char *password);

    void setCreateTbl(){ shouldCreateTbl=true; }
    bool getCreateTbl(){ return shouldCreateTbl; }

    void setDSN(bool flag){ dsn = flag;}
    bool getDSN(){ return dsn; }
    void setNoSchema(bool flag){ noschema = flag; }
    bool getNoSchema(){return noschema;}
    char *getHCondition(){return hcondition;}
    char *getVCondition(){return vcondition;}
    void setHCondition(char *fld){ strcpy(hcondition,fld);}
    void setVCondition(char *fld){ strcpy(vcondition,fld);}
    void setHCondFld(bool flag){hCondFld = flag;}
    bool getHCondFld(){return hCondFld;}
    void setVCondFld(bool flag){vCondFld = flag;}
    bool getVCondFld(){return vCondFld;}
    void setPkFld(bool flag){pkFld = flag;}
    bool getPkFld(){return pkFld;}
    void setDirect(bool flag){direct=flag;}
    bool getDirect(){return direct;}
    void setUnCache(bool flag){uncache=flag;}
    bool getUnCache(){return uncache;}
    void setLimit(int l, int o) { limit =l; offset=o; }
    int getLimit(){ return limit; }
    int getOffset(){ return offset; }
 

    int getBucketSize(){return bucketSize; };
    void setBucketSize(int bucket){ bucketSize = bucket; };
    void setStmtType(StatementType type) { stmtType = type; }
    void setTableName(char *name) { strcpy(tblName, name); }
    void setIndexName(char *name) { strcpy(idxName, name); }
    void setPKTableName(char *name){strcpy(pkTblName, name); }
    void setResultSetPlan(ResultSetPlan pl){plan = pl;}
    ResultSetPlan getResultSetPlan(){return plan;}
    char* getTableName() { return tblName; }
    char* getIndexName() { return idxName; }
    char* getPKTableName(){ return pkTblName;}
    DbRetVal setAutoIncreament(bool flag);
    bool getAutoIncreament();
    void insertValue(char *value);
    void insertInValue(char *value);
	// third parameter is to avoid conflict between '?' between like operand and parameterized value in sql statement.
	// eg: select * from t1 where f1 = ? and f2 like '_ti%';
	// _ is converted to ? before it is processed
    void** insertCondValueAndGetPtr(char *fName, char *value, bool opLike=false, AggType atp=AGG_UNKNOWN, bool isInHaving=false,bool function=false);
    void insertCondValue(char *fldName); //For Predecate t1.f1=t2.f1
    void insertUpdateValue(char *fldName, char *value);

    void insertField(char *fName, AggType aggType= AGG_UNKNOWN);
    void insertFieldAlias(char *name);
    void insertGroupField(char *fName);
    void insertOrderByField(char *fName, bool isDesc= false);
    void clearFieldNameList();
    void insertTableName(char *value);
    void insertJoinType(JoinType jType);
    void insertTableName(char *value, char *alias);
    void insertFKField(char *fkName);
    void insertPKField(char *pkName);
    void insertForeignKeyList();
    Predicate* insertPredicate(char *fldName, ComparisionOp op, void** value, AggType aggType = AGG_UNKNOWN);
    Predicate* insertPredicate(char *fldName, ComparisionOp op, char *fldName1);
    Predicate* insertBetPredicate(char *fldName, ComparisionOp op1, void **value1, ComparisionOp op2, void **value2);
    Predicate* insertPredicate(Predicate *p1, LogicalOp op, Predicate *p2 = NULL);
    Predicate* insertPredicate(Expression *exp, ComparisionOp op,void **val);
    Predicate* insertPredicate(Expression *exp, ComparisionOp op,char *fName2);
    Predicate* insertPredicate(Expression *exp1, ComparisionOp op,Expression *exp2);
    Predicate* insertNullPredicate(char *fName, ComparisionOp op,bool nullFlag);
    void setCondition(Predicate *pred) 
    { 
        predicate.setPredicate(pred); 
    }
    void setHavingCondition(Predicate *pred) 
    { 
        havingPredicate.setPredicate(pred); 
    }
    Condition* getCondition() { return &predicate; }
    Condition* getHavingCondition() { return &havingPredicate; }

    void insertFieldValue(FieldValue *newVal) { fieldValueList.append(newVal); }

    List getFieldNameList() { return fieldNameList; }
    List getGroupFieldNameList() { return groupFieldNameList; }
    List getHavingFieldNameList() { return havingFieldNameList; }
    List getOrderFieldNameList() { return orderFieldNameList; }
    List getConditionValueList() { return conditionValueList; }
    List getFieldValueList() { return fieldValueList; }
    List getInValueList() { return inValueList; }
    List getUpdateFieldValueList() { return updFldValList; }
    List getTableNameList() { return tableNameList; }
    List getJoinTypeList() { return joinTypeList; }
    List getSecondaryIndexFieldList() { return secondaryIndexFieldList; }
    List getForeignKeyList(){ return foreignKeyList;}
    List getPkFieldNameList(){return pkFieldNameList;}
    List getFkFieldNameList(){return fkFieldNameList;}

    void setDistinct() { isDistinct = true;}
    bool getDistinct() { return isDistinct; }
    void setExplain() { isExplain=true; }
    bool getExplain() { return isExplain; }
    bool getCacheWorthy() { return isWorthyToCache; }
    void setCacheWorthy(bool flag) { isWorthyToCache = flag;}


    void setFldName(char *name);
    void setFldType(DataType type);
    DataType getFldType();
    DbRetVal setFldLength(size_t length);
    DbRetVal setDefaultValue(char * value);
    DbRetVal validateDefaultValue(char* value);
    //void setFldDefaultValue -- will need two parametersers, check how u want to pass default value.
    void setFldNotNull(bool notNull);
    void setForeign(bool foreign){ isForeign = foreign; }
    void setUnique(bool unique){ isUnique = unique; }
    void setPrimary(bool primary) { isPrimary = primary; }
    void setIndexType (IndexType type) { indexType = type; }
    IndexType getIndexType(){ return indexType; }
    bool getUnique() { return isUnique; }
    bool getPrimary() { return isPrimary; }
    Expression* insertExpression(char *fldName);
    Expression* insertExpression(char *value, bool flag);
    Expression* insertExpression(Expression* exp1, ArithOperator op ,Expression* exp2);
    Expression* insertExpression(Expression* exp1, FunctionType type,Expression* exp2);
    void insertUpdateExpression(char *fName, Expression *exp);

    void insertFldDef(); //check if fldDef needs to be a part of ParsedData 
    
    FieldList getCreFldList() { return creFldList; }

    StatementType getStmtType() { return stmtType; }
    char *getFldName();
    void setAutoFldName(char *fldName);
    void reset();
    void init();

};

#endif

//TODO: Aruna
//variable and function names suck, change if u want to
//setFldDefaultValue
//finding out if fldDef needs to be part of parsedData, or can allocate memory and pass around
//primary key
//foreign key
