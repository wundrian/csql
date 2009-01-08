/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
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
#include<Table.h>
#include<Index.h>
#include<CatalogTables.h>
#include<Lock.h>
#include<Debug.h>
#include<PredicateImpl.h>
#include<Table.h>
#include<TableImpl.h>
#include<fnmatch.h>
#include<JoinTableImpl.h>
#include<Util.h>
void PredicateImpl::print(int space)
{
    char spaceBuf[IDENTIFIER_LENGTH];
    memset(spaceBuf, 32, IDENTIFIER_LENGTH);
    spaceBuf[space] = '\0';

    printf("%s <PREDICATE>\n", spaceBuf);
    printf("%s <FieldName1> %s </FieldName1>\n", spaceBuf, fldName1);
    printf("%s <FieldName2> %s </FieldName2>\n", spaceBuf, fldName2);
    printf("%s <CompOp> %s </CompOp>\n", spaceBuf, CompOpNames[compOp]);
    printf("%s <LogOp> %s </LogOp>\n", spaceBuf, LogOpNames[logicalOp]);
    printf("%s <Operand> %x </Operand>\n", spaceBuf, operand);
    printf("%s <OperandPtr> %x </OperandPtr>\n", spaceBuf, operandPtr);
    if (lhs) {
       printf("%s <PRED-LEFT>\n", spaceBuf);
       lhs->print(space+2);
       printf("%s </PRED-LEFT>\n", spaceBuf);
    }
    if (rhs) 
    {
       printf("%s <PRED-RIGHT>\n", spaceBuf);
       rhs->print(space+2);
       printf("%s </PRED-RIGHT>\n", spaceBuf);
    }
    printf("%s </PREDICATE>\n", spaceBuf);
    
}

void PredicateImpl::setTerm(const char* fName1, ComparisionOp op,
                        const char *fName2)
{
    strcpy(fldName1, fName1);
    strcpy(fldName2, fName2);
    compOp = op;
    operand = NULL;
    operandPtr = NULL;
    lhs = rhs = NULL;
    parent = NULL;
    logicalOp = OpInvalidLogicalOp;
}

//Operand should be of the same type of the field.This is must
void PredicateImpl::setTerm(const char* fName1, ComparisionOp op, void *opnd)
{
    strcpy(fldName1, fName1);
    if (op == OpLike) 
    {
        char *c = (char *) opnd;
	while (*c != '\0') 
        {
	    if (*c == '_') *c = '?';
	    else if(*c == '%') *c = '*';
	    c++;
	}
    }
    compOp = op;
    operand = opnd;
    operandPtr = NULL;
    lhs = rhs = NULL;
    parent = NULL;
    logicalOp = OpInvalidLogicalOp;
}

void PredicateImpl::setTerm(const char* fName1, ComparisionOp op, void **opnd)
{
    strcpy(fldName1, fName1);
    compOp = op;
    operand = NULL;
    operandPtr = opnd;
    lhs = rhs = NULL;
    parent = NULL;
    logicalOp = OpInvalidLogicalOp;
}

void PredicateImpl::setParent(PredicateImpl *pImpl)
{
   //if (parent != NULL) printf("Parent already set\n");
   parent = pImpl;
   return;
}
void PredicateImpl::setTerm(Predicate *p1, LogicalOp op, Predicate *p2 )
{
    if (p2 == NULL && op != OpNot || op == OpNot && p2 != NULL) 
    { 
        //TODO::printError
        printError(ErrBadArg, "Wrong argument passed\n");
        return; 
    }
    lhs = (PredicateImpl*)p1;
    rhs = (PredicateImpl*)p2;
    logicalOp = op;
    compOp = OpInvalidComparisionOp;
    if (lhs != NULL) lhs->setParent(this);
    if (rhs != NULL) rhs->setParent(this);
    return;
}

void PredicateImpl::setTable(Table *tbl)
{
    if (NULL != lhs)
        lhs->setTable((TableImpl*)tbl);
    if (NULL != rhs)
        rhs->setTable((TableImpl*)tbl);
   table = (TableImpl*)tbl;
}

void PredicateImpl::setTuple(void *tpl)
{
    if (NULL != lhs)
        lhs->setTuple(tpl);
    if (NULL != rhs)
         rhs->setTuple(tpl);
    tuple = tpl;
}
void PredicateImpl::setProjectionList(List *lst)
{
    if (NULL != lhs)
        lhs->setProjectionList(lst);
    if (NULL != rhs)
         rhs->setProjectionList(lst);
    if (operand == NULL && operandPtr == NULL)
        projList = lst;
}
bool PredicateImpl::isSingleTerm()
{
    if (NULL == lhs  && NULL == rhs) return true; else false;
}


bool PredicateImpl::isNotOrInvolved()
{
    bool lhsResult = true, rhsResult = true;
    if (NULL != lhs)
    {
        lhsResult = lhs->isNotOrInvolved();
    }
    if (NULL != rhs)
    {
        rhsResult = rhs->isNotOrInvolved();
    }
    if (NULL != lhs)
    {
        //Means it involves only Logical operator
            switch(logicalOp)
            {
                case OpAnd:
                     if (lhsResult || rhsResult) return true;  else return false;
                     break;
                case OpOr:
                     return true;
                     break;
                case OpNot:
                default:
                     return true;
                     break;
        }
    }
    return false;
}

DbRetVal PredicateImpl::evaluate(bool &result)
{
    bool rhsResult = false, lhsResult=false;
    DbRetVal retCode =OK;
    result = false;
    if (NULL != lhs)
    {
        retCode = lhs->evaluate(lhsResult);
        if (retCode != OK) return ErrInvalidExpr;
    }else lhsResult = true;
    if (NULL != rhs)
    {
        retCode = rhs->evaluate(rhsResult);
        if (retCode != OK) return ErrInvalidExpr;
    } else rhsResult = true;
    if (NULL != lhs)
    {
        //Means it involves only Logical operator
            switch(logicalOp)
            {
                case OpAnd:
                    if (lhsResult && rhsResult) result = true;
                    break;
                case OpOr:
                    if (lhsResult || rhsResult) result = true;
                    break;
                case OpNot:
                    if (lhsResult)  result = false; else result = true;
                    break;
                default:
                    return ErrInvalidExpr;

            }
            printDebug(DM_Predicate, "result is %d", result);
            return OK;
    }
    //Means it is relational expression
    //first operand is always field identifier
    //get the value in the tuple
    char fieldName1[IDENTIFIER_LENGTH];
    char fieldName2[IDENTIFIER_LENGTH];
    memset(fieldName1, 0, IDENTIFIER_LENGTH);
    memset(fieldName2, 0, IDENTIFIER_LENGTH);
    Table::getFieldNameAlone(fldName1, fieldName1);
    Table::getFieldNameAlone(fldName2, fieldName2);
    if (projList)
    {
        DataType type=typeUnknown;
        int length=0;
        //for join node evaluation
        ListIterator fIter = projList->getIterator();        
        JoinProjFieldInfo  *def;
        char *val1, *val2;
        while (fIter.hasElement())
        {
            def = (JoinProjFieldInfo*) fIter.nextElement();
            if (NULL != def->appBuf) {
                if (0 == strcmp(fldName1, def->tabFieldName))
                {
                    val1 = (char*)def->bindBuf;
                    type = def->type;
                    length = def->length;
                    break;
                }
            }else{
                printError(ErrNotExists, "Field not binded %s.%s\n", 
                                      def->tableName, def->fieldName);
                return ErrNotExists;
            }
        }
        if (operand == NULL && operandPtr == NULL)
        {
            if (fieldName2) {
                fIter.reset();
                while (fIter.hasElement())
                {
                    def = (JoinProjFieldInfo*) fIter.nextElement();
                    if (NULL != def->appBuf) {
                        if (0 == strcmp(fldName2, def->tabFieldName))
                        {
                            val2 = (char*)def->bindBuf;
                            break;
                        }
                    }else{
                        printError(ErrNotExists, "Field not binded %s.%s\n",
                                            def->tableName, def->fieldName);
                        return ErrNotExists;
                    }
                }
            }
        } 
        else if(operand != NULL && operandPtr == NULL)
        { 
            val2 = (char*) operand;
        }
        else if(operand == NULL && operandPtr != NULL)
        { 
            val2 = *(char**)operandPtr;
        }
        if (compOp == OpLike) result = ! fnmatch(val2, val1, 0);
        else result = AllDataType::compareVal(val1, val2, compOp, type,
                              length);
        return OK;
    }
    //the below code works only for single table 
    int offset1, offset2;

    offset1 = table->getFieldOffset(fieldName1);
    //TODO::do not call getFieldXXX many times, instead get it using getFieldInfo
    char *val1, *val2;
    //Assumes that fldName2 data type is also same for expr f1 <f2
    DataType srcType = table->getFieldType(fieldName1);
    val1 = ((char*) tuple) + offset1;
    if (operand == NULL && operandPtr == NULL)
    {
        if (fieldName2) {
            offset2 = table->getFieldOffset(fieldName2);
            val2 = ((char*)tuple) + offset2; 
        }
    } 
    else if(operand != NULL && operandPtr == NULL)
    { 
        val2 = (char*) operand;
    }
    else if(operand == NULL && operandPtr != NULL)
    { 
        val2 = *(char**)operandPtr;
    }
    int ret = 0;
    if (compOp == OpLike) result = ! fnmatch(val2, val1, 0);
    else result = AllDataType::compareVal(val1, val2, compOp, srcType,
                              table->getFieldLength(fieldName1));
    return OK;
}

bool PredicateImpl::pointLookupInvolved(const char *fname)
{
    bool rhsResult, lhsResult;
    if (NULL != lhs)
    {
        lhsResult = lhs->pointLookupInvolved(fname);
    }
    if (NULL != rhs)
    {
        rhsResult = rhs->pointLookupInvolved(fname);
    }
    if (NULL != lhs)
    {
        //Means it involves only Logical operator
            switch(logicalOp)
            {
                case OpAnd:
                     //return lhsResult;
                     if (lhsResult || rhsResult) return true;  else return false;
                     break;
                case OpOr:
                     return false;
                     break;
                case OpNot:
                default:
                     return false;
                     break;
        }
    }
    //Means it is relational expression
    //first operand is always field identifier
    char fieldName1[IDENTIFIER_LENGTH];
    Table::getFieldNameAlone(fldName1, fieldName1);
    if (OpEquals == compOp)
    {
        //for expressions f1 == f2 use full scan, so return false
        if(NULL == operand && NULL == operandPtr) return false;
        if(0 == strcmp(fieldName1, fname)) 
        {
            return true;
        }
    }
    return false;
}
bool PredicateImpl::rangeQueryInvolved(const char *fname)
{
    bool rhsResult, lhsResult;
    if (NULL != lhs)
    {
        lhsResult = lhs->rangeQueryInvolved(fname);
    }
    if (NULL != rhs)
    {
        rhsResult = rhs->rangeQueryInvolved(fname);
    }
    if (NULL != lhs)
    {
            switch(logicalOp)
            {
                case OpAnd:
                     if (lhsResult || rhsResult) return true;  else return false;
                     break;
                case OpOr:
                     return false;
                     break;
                case OpNot:
                default:
                     return false;
                     break;
        }
    }
    //Means it is relational expression
    //first operand is always field identifier
    char fieldName1[IDENTIFIER_LENGTH];
    Table::getFieldNameAlone(fldName1, fieldName1);
    if (OpLessThan == compOp || OpLessThanEquals == compOp ||
        OpGreaterThan == compOp || OpGreaterThanEquals == compOp)
    {
         //for expressions f1 == f2 use full scan, so return false
        if(NULL == operand && NULL == operandPtr) return false;
        if(0 == strcmp(fieldName1, fname))
        {
            return true;
        }
    }
    return false;
}


void* PredicateImpl::valPtrForIndexField(const char *fname)
{
    void *lhsRet=NULL, *rhsRet=NULL;
    if (NULL != lhs)
    {
        lhsRet = lhs->valPtrForIndexField(fname);
        if ( lhsRet !=  NULL) return lhsRet;
    }
    if (NULL != rhs)
    {
        rhsRet = rhs->valPtrForIndexField(fname);
        if ( rhsRet !=  NULL) return rhsRet;
    }
    char fieldName1[IDENTIFIER_LENGTH];
    Table::getFieldNameAlone(fldName1, fieldName1);
    //Means it is relational expression
    //first operand is always field identifier
    //if (OpEquals == compOp)
    {
        if(0 == strcmp(fieldName1, fname)) 
        {
            if (operand) return operand; else return *(void**)operandPtr;
        }
    }
    return NULL;
}
ComparisionOp PredicateImpl::opForIndexField(const char *fname)
{
    ComparisionOp lhsRet= OpInvalidComparisionOp, rhsRet= OpInvalidComparisionOp;
    if (NULL != lhs)
    {
        lhsRet = lhs->opForIndexField(fname);
        if ( lhsRet !=  OpInvalidComparisionOp) return lhsRet;
        
    }
    if (NULL != rhs)
    {
        rhsRet = rhs->opForIndexField(fname);
        if ( rhsRet !=  OpInvalidComparisionOp) return rhsRet;
    }
    char fieldName1[IDENTIFIER_LENGTH];
    Table::getFieldNameAlone(fldName1, fieldName1);
    if(0 == strcmp(fieldName1, fname))
    {
        return compOp;
    }
    return OpInvalidComparisionOp;
}
PredicateImpl* PredicateImpl::getTablePredicate()
{
    PredicateImpl *lhsRet = NULL, *rhsRet = NULL;
    if (NULL != lhs)
    {
        lhsRet = lhs->getTablePredicate();
        if ( lhsRet !=  NULL) return lhsRet;
    }
    if (NULL != rhs)
    {
        rhsRet = rhs->getTablePredicate();
        if ( rhsRet !=  NULL) return rhsRet;
    }
    if (operand || operandPtr )
    {
        //printf("PRABA::getTablePredicate returning %s %d\n", fldName1, compOp);
        if (parent)
        {
           if (this == parent->lhs) {
               parent->lhs = NULL;
           }
           else { 
              parent->rhs = NULL;
           }
           parent = NULL;
        }
        return this;    
    } 
    return NULL;
}
PredicateImpl* PredicateImpl::getJoinPredicate()
{
    PredicateImpl *lhsRet = NULL, *rhsRet = NULL;
    if (NULL != lhs)
    {
        lhsRet = lhs->getJoinPredicate();
        if ( lhsRet !=  NULL) return lhsRet;
    }
    if (NULL != rhs)
    {
        rhsRet = rhs->getJoinPredicate();
        if ( rhsRet !=  NULL) return rhsRet;
    }
    if (0 != strcmp(fldName2, ""))
    {
        //printf("PRABA::getJoinPredicate returning %s %s\n", fldName1, fldName2);
        if (parent)
        {
           if (this == parent->lhs) 
               parent->lhs = NULL;
           else 
               parent->rhs = NULL;
           parent = NULL;
        }
        return this;    
    } 
    return NULL;
}
void PredicateImpl::removeIfNotNecessary()
{
    if (NULL != lhs)
    {
        lhs->removeIfNotNecessary();
    }
    if (NULL != rhs)
    {
        rhs->removeIfNotNecessary();
    }
    if (logicalOp != OpAnd) return;   
    if (NULL ==  lhs && NULL == rhs)
    {
        if (NULL == parent)
        {
            return;
        }
        if (this == parent->rhs) parent->rhs = NULL;
        else if (this == parent->lhs) parent->lhs = NULL;
        delete this;
        //WARNINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
        //current object is deleted. do not any code here
        return;
    }
    else if (NULL ==  lhs )
    {
        //left side of the node is empty means we can remove this AND node 
        //and place it as left or right of my parent where i am currently placed
        if (NULL == parent)
        {
            return;
        }
        if (this == parent->rhs) parent->rhs=this->rhs;
        else if (this == parent->lhs) parent->lhs = this->rhs;
        delete this;
        //WARNINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
        //current object is deleted. do not any code here
        return;
    }
    else if (NULL ==  rhs )
    {
        //right side of the node is empty means we can remove this AND node 
        //and place it as left or right of my parent where i am currently placed
        if (NULL == parent)
        {
            return;
        }
        if (this == parent->rhs) parent->rhs=this->lhs;
        else if (this == parent->lhs) parent->lhs = this->lhs;
        delete this;
        //WARNINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
        //current object is deleted. do not any code here
        return;
    }
    return;
}
bool PredicateImpl::isDummyPredicate()
{
    if (NULL == lhs && NULL == rhs && NULL == parent
                    && NULL == operand && NULL == operandPtr &&
                    (0 == strcmp(fldName1, "")) && (0==strcmp(fldName2, "")))
        return true; 
    else
        return false;
}
PredicateImpl* PredicateImpl::getIfOneSidedPredicate()
{
    if (logicalOp != OpAnd) return NULL;
    if (NULL ==  lhs && NULL !=rhs)
    {
        return rhs;
    }
    if (NULL !=  lhs && NULL ==rhs)
    {
        return lhs;
    }
    return NULL;
}
