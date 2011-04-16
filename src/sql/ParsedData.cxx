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
#include<os.h>
#include <Parser.h>
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
void** ParsedData::insertCondValueAndGetPtr(char *fldName, char *val, bool opLike, AggType aType, bool isInHaving,bool function)
{
    ConditionValue *newVal = new ConditionValue();
    if (val == NULL) 
        newVal->parsedString = NULL;
    else
        newVal->parsedString = strdup(val);
    newVal->value = NULL;
    newVal->paramNo = 0;
    newVal->type = typeUnknown;
    newVal->aType = aType;
    newVal->length = 0;
    strcpy(newVal->fName, fldName);
    newVal->opLike = opLike;
    newVal->isFunctionInvolve = function;
    conditionValueList.append(newVal);
    if (isInHaving) {
        FieldName *fName = new FieldName();
        strcpy(fName->fldName, fldName);
        fName->aType = aType;
        havingFieldNameList.append(fName);
    }
    return &(newVal->value);

}

void ParsedData::insertCondValue(char *fldName)
{
    ConditionValue *newVal = new ConditionValue();
    newVal->parsedString = NULL;
    newVal->value = NULL;
    newVal->paramNo = 1;//To solve parsedString Null problem
    newVal->type = typeUnknown;
    newVal->aType = AGG_UNKNOWN;
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
void ParsedData::insertFieldAlias(char *name)
{
    FieldName *newVal=NULL;
    newVal = (FieldName *)fieldNameList.get(fieldNameList.size());
    strcpy(newVal->aliasFldName, name);
}

void ParsedData::insertFKField(char *fkName)
{
    FieldName *newVal = new FieldName();
    strcpy(newVal->fldName , fkName);
    fkFieldNameList.append(newVal);
}
void ParsedData::insertPKField(char *pkName)
{
    FieldName *newVal = new FieldName();
    strcpy(newVal->fldName , pkName);
    pkFieldNameList.append(newVal);
}
void ParsedData::insertForeignKeyList()
{
    FieldName *name=NULL;
    ForeignKeyInfo *fkInfo = new ForeignKeyInfo();
   // strcpy(fkInfo->fkTableName,tblName);
    strcpy(fkInfo->pkTableName,pkTblName);
    ListIterator fNameIter = getFkFieldNameList().getIterator();
    fNameIter.reset();
    while (fNameIter.hasElement())
    {
        name = (FieldName *)fNameIter.nextElement();
        fkInfo->fkFldList.append(name->fldName);
        delete name;
    }
    fkFieldNameList.reset();
    fNameIter = getPkFieldNameList().getIterator();
    fNameIter.reset();
    while (fNameIter.hasElement())
    {
        name = (FieldName *)fNameIter.nextElement();
        fkInfo->pkFldList.append(name->fldName);
        delete name;
    }
    pkFieldNameList.reset();
    foreignKeyList.append(fkInfo);
}
void ParsedData::insertTableName(char *tName)
{
    TableName *newVal = new TableName();
    strcpy(newVal->tblName , tName);
    tableNameList.append(newVal);
}
void ParsedData::insertJoinType(JoinType joinType)
{
    JoinTypeNode *newVal = new JoinTypeNode();
    newVal->jType = joinType;
    joinTypeList.append(newVal);
}


void ParsedData::insertTableName(char *tName, char *aName)
{
    TableName *newVal = new TableName();
    strcpy(newVal->tblName , tName);
    strcpy(newVal->aliasName , aName);
    tableNameList.append(newVal);
}
void ParsedData::insertGroupField(char *fName)
{
    FieldName *newVal = new FieldName();
    strcpy(newVal->fldName , fName);
    groupFieldNameList.append(newVal);
}
void ParsedData::insertOrderByField(char *fName, bool isDesc)
{
    FieldName *newVal = new FieldName();
    strcpy(newVal->fldName , fName);
    if (isDesc) newVal->aType = AGG_MIN; //using MIN to denote descending order
    orderFieldNameList.append(newVal);
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

Predicate* ParsedData::insertPredicate(Expression *exp, ComparisionOp op,void **val)
{
    PredicateImpl *pImpl = new PredicateImpl();
    exp->convertStrToVal(AllDataType::getCsqlTypeFromFunctionType(exp->getFunctionType()));
    pImpl->setTerm(exp, op, val);
    predList.append(pImpl);
    return (Predicate*) pImpl;
}
Predicate* ParsedData::insertPredicate(Expression *exp, ComparisionOp op,char *fName2)
{
   PredicateImpl *pImpl = new PredicateImpl();
   exp->convertStrToVal(AllDataType::getCsqlTypeFromFunctionType(exp->getFunctionType()));
    pImpl->setTerm(exp, op, fName2);
    predList.append(pImpl);
    return (Predicate*) pImpl;

}
Predicate* ParsedData::insertPredicate(Expression *exp1, ComparisionOp op,Expression *exp2)
{
   PredicateImpl *pImpl = new PredicateImpl();
   exp1->convertStrToVal(AllDataType::getCsqlTypeFromFunctionType(exp1->getFunctionType()));
   exp2->convertStrToVal(AllDataType::getCsqlTypeFromFunctionType(exp2->getFunctionType()));
    pImpl->setTerm(exp1, op, exp2);
    predList.append(pImpl);
    return (Predicate*) pImpl;
}

Predicate* ParsedData::insertPredicate(char *fName, ComparisionOp op, void **val, AggType aggType)
{
    PredicateImpl *pImpl = new PredicateImpl();
    pImpl->setTerm(fName, op, val, aggType);
    predList.append(pImpl);
    return (Predicate*) pImpl;
}
Predicate* ParsedData::insertBetPredicate(char *fName, ComparisionOp op1, 
                            void **val1, ComparisionOp op2, void **val2)
{
    PredicateImpl *pImpl = new PredicateImpl();
    pImpl->setTerm(fName, op1, val1, op2, val2);
    predList.append(pImpl);
    return (Predicate*) pImpl;
}
Predicate* ParsedData::insertNullPredicate(char *fName, ComparisionOp op,bool nullFlag)
{
    PredicateImpl *pImpl = new PredicateImpl();
    pImpl->setTerm(fName, op, nullFlag);
    predList.append(pImpl);
    return (Predicate*) pImpl;
}

Predicate* ParsedData::insertPredicate(char *fName1, ComparisionOp op, char *fName2)
{
    PredicateImpl *pImpl = new PredicateImpl();
    pImpl->setTerm(fName1, op, fName2);
    predList.append(pImpl);
    return (Predicate*) pImpl;
}

Predicate* ParsedData::insertPredicate(Predicate *p1, LogicalOp op, Predicate *p2)
{
    PredicateImpl *pImpl = new PredicateImpl();
    pImpl->setTerm(p1, op, p2);
    predList.append(pImpl);
    return (Predicate*) pImpl;
}
void ParsedData::init()
{
    tableNameList.init();
    fieldNameList.init();
    fieldValueList.init();
    inValueList.init();
    setCondition(NULL);
    setHavingCondition(NULL);
    predList.init();
    conditionValueList.init();
    updFldValList.init();
    groupFieldNameList.init();
    havingFieldNameList.init();
    orderFieldNameList.init();
    isDistinct = false;
    joinTypeList.init();
    isUnique = false;
    isPrimary = false;
    isAutoIncrement =false;
    isForeign=false;
    indexType = hashIndex;
    hCondFld=false; vCondFld=false;
    shouldCreateTbl=false;
    limit =0;
    offset =0;
    paramCounter = 0; stmtType = UnknownStatement;
    isExplain=false;
    plan = Normal;
}
void ParsedData::resetInValueList()
{
    FieldValue *value;
    ListIterator inIter = inValueList.getIterator();
    while (inIter.hasElement()) {
        value = (FieldValue *) inIter.nextElement();
        if (value->parsedString) free(value->parsedString);
        delete value;
    }
    inValueList.reset();
    return;
}

//NOTE::when you add members to reset() check whether it needs to be added in init() as it is used for statement caching when it contains parameters
void ParsedData::reset()
{
    ListIterator fNameIter = fieldNameList.getIterator();
    fNameIter.reset();
    while (fNameIter.hasElement())
        delete ((FieldName *) fNameIter.nextElement());
    fieldNameList.reset();
    fNameIter = secondaryIndexFieldList.getIterator();
    fNameIter.reset();
    while (fNameIter.hasElement())
        delete ((FieldName *) fNameIter.nextElement());
    secondaryIndexFieldList.reset();
    
    fNameIter =pkFieldNameList.getIterator();
    fNameIter.reset();
    while (fNameIter.hasElement())
        delete ((FieldName *) fNameIter.nextElement());
    pkFieldNameList.reset();
    fNameIter = fkFieldNameList.getIterator();
    fNameIter.reset();
    while (fNameIter.hasElement())
        delete ((FieldName *) fNameIter.nextElement());
    fkFieldNameList.reset();
    ForeignKeyInfo *info=NULL; 
    fNameIter = foreignKeyList.getIterator();
    while (fNameIter.hasElement())
    {
        info=(ForeignKeyInfo *) fNameIter.nextElement();
        info->fkFldList.removeAll();
        info->pkFldList.removeAll();
        delete info;
    }  
    foreignKeyList.reset();
    ListIterator iter = fieldValueList.getIterator();
    FieldValue *value;
    while (iter.hasElement())
    {
        value = (FieldValue*)iter.nextElement();
        if (value->parsedString) free(value->parsedString);
        if (value->isAllocVal) free(value->value);
        delete value;
    }
    fieldValueList.reset();

    resetInValueList();

    predicate.reset();
    havingPredicate.reset();
    ListIterator pIter = predList.getIterator();
    while (pIter.hasElement()) {
        PredicateImpl *pImpl= (PredicateImpl *) pIter.nextElement();    
        delete pImpl;
    }
    predList.reset();

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
    iter = orderFieldNameList.getIterator();
    while(iter.hasElement())
    {
        delete iter.nextElement();
    }

    iter = havingFieldNameList.getIterator();
     while(iter.hasElement())
    {
        delete iter.nextElement();
    }
    havingFieldNameList.reset();

    orderFieldNameList.reset();
    isDistinct = false;
    isExplain = false;

    iter = tableNameList.getIterator();
    TableName *tname;  
    while (iter.hasElement())
    {
        tname = (TableName*)iter.nextElement();
        delete tname;
    }
    tableNameList.reset(); 

    iter = joinTypeList.getIterator();
    JoinTypeNode *jNode;
    while (iter.hasElement())
    {
        jNode = (JoinTypeNode*)iter.nextElement();
        delete jNode;
    }
    joinTypeList.reset();

    if(userNode) { delete userNode; userNode =NULL;}
    
    creFldList.removeAll();
    isUnique = false; 
    isPrimary = false; 
    isAutoIncrement =false;
    isForeign=false;
    indexType = hashIndex;
    hCondFld=false; vCondFld=false;pkFld=false;forceOption=false; direct=false; uncache=false; noschema=false; dsn=false;
    bucketSize = 0;
    shouldCreateTbl=false;
    limit =0;
    offset =0;
    ftype = UNKNOWN_FUNCTION;
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
char *ParsedData::getFldName()
{
    return fldDef.fldName_;
}
void ParsedData::setAutoFldName(char *fldName)
{
    FieldInfo *newVal = new FieldInfo();
    strcpy(newVal->fldName , fldName);
    newVal->isAutoIncrement = true;
    secondaryIndexFieldList.append(newVal);
}
void ParsedData::setFldType(DataType type)
{
    fldDef.type_ = type;
}
DataType ParsedData::getFldType()
{
   return fldDef.type_;
}
DbRetVal ParsedData::setAutoIncreament(bool flag)
{
    if(isAutoIncrement){return ErrAlready;}
    fldDef.isAutoIncrement_=flag;
    isAutoIncrement=true;
    return OK;
}
bool ParsedData::getAutoIncreament()
{
    return fldDef.isAutoIncrement_;
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
DbRetVal ParsedData::setDefaultValue(char *value)
{
    DbRetVal rv=OK;
    fldDef.isDefault_ = true;
    if (value == NULL) {
        fldDef.defaultValueBuf_[0]='\0';
        return OK;;
    }
    /* Function to check Default Value */
    rv=validateDefaultValue(value);
    if(rv !=OK) return ErrDefaultValue;

    if (strlen(value) > DEFAULT_VALUE_BUF_LENGTH -1) 
    {
        strncpy(fldDef.defaultValueBuf_, value, DEFAULT_VALUE_BUF_LENGTH -1);
        fldDef.defaultValueBuf_[DEFAULT_VALUE_BUF_LENGTH] ='\0';
    } else strcpy(fldDef.defaultValueBuf_, value);
    return rv;
}
/* Validate Default value  */
DbRetVal ParsedData::validateDefaultValue(char *value)
{
    DbRetVal rv=OK;
    Date date;
    Time time;
    TimeStamp timeStamp;
    int ret=0;
    /* Default value checking for INT, SHORT, LONG, LONGLONG data type */
    if(fldDef.type_ == typeInt || fldDef.type_ == typeShort || fldDef.type_ == typeByteInt || fldDef.type_ == typeLongLong || fldDef.type_ == typeLong){
        for(int i=0; i<strlen(value); i++){
            if(!(value[i] >= '0' && value[i] <= '9'  || value[0]=='-')){
                return ErrDefaultValue;
            }
        }
    }
    /* Default value check for FLOAT and DOUBLE data type*/
    else if (fldDef.type_ == typeFloat || fldDef.type_ == typeDouble){
        for(int i=0;i<strlen(value);i++){
            if(!(value[i] >= '0' && value[i] <='9' || value[0]=='-'  || value[i] == '.')){
                return ErrDefaultValue;
            }
        }
    }
    /* Default value checking for DATE */
    else if(fldDef.type_ == typeDate ){
        ret=date.parseFrom(value);
        if(ret==-1){ return ErrDefaultValue;}
    }
     /*Default value checking for TIME  */
    else if(fldDef.type_ == typeTime ){
        ret=time.parseFrom(value);
        if(ret==-1){ return ErrDefaultValue;}
    }
    /* Default value checking for TIMESTAMP */
    else if(fldDef.type_ == typeTimeStamp ){
        ret=timeStamp.parseFrom(value);
        if(ret==-1){ return ErrDefaultValue;}
    }
    return rv;
}




void ParsedData::insertFldDef()
{
    DbRetVal rv = creFldList.append(fldDef);
    fldDef.init();
}
Expression* ParsedData::insertExpression(Expression* exp1, FunctionType type,Expression* exp2)
{
    Expression *exp =new Expression();
    exp->setExpr(exp1, type, exp2);
    return exp;
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
void ParsedData::createUserNode(char *name, char *password)
{
    userNode = new UserNode();
    strcpy(userNode->userName, name);
    strcpy(userNode->passName, password);
    userNode->type = CREATEUSER;
}
void ParsedData::dropUserNode(char *name)
{
    userNode = new UserNode();
    strcpy(userNode->userName, name);
    userNode->type = DROPUSER;
}
void ParsedData::alterUserNode(char *name, char *password)
{
    userNode = new UserNode();
    strcpy(userNode->userName, name);
    strcpy(userNode->passName, password);
    userNode->type = ALTERUSER;
}
