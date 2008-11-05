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
void PredicateImpl::print()
{
    printf("FieldName1 %s, FieldName2 %s", fldName1, fldName2);
    printf("CompOp %d, operand %x operandPtr%x", compOp, operand);
    printf("lhs %x, rhs %x", lhs, rhs);
    
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
    logicalOp = OpInvalidLogicalOp;
}

//Operand should be of the same type of the field.This is must
void PredicateImpl::setTerm(const char* fName1, ComparisionOp op, void *opnd)
{
    strcpy(fldName1, fName1);
    if (op == OpLike) {
	    char *c = (char *) opnd;
		while (*c != '\0') {
		    if (*c == '_') *c = '?';
			else if(*c == '%') *c = '*';
			c++;
		}
	}
    compOp = op;
    operand = opnd;
    operandPtr = NULL;
    lhs = rhs = NULL;
    logicalOp = OpInvalidLogicalOp;
}

void PredicateImpl::setTerm(const char* fName1, ComparisionOp op, void **opnd)
{
    strcpy(fldName1, fName1);
    compOp = op;
    operand = NULL;
    operandPtr = opnd;
    lhs = rhs = NULL;
    logicalOp = OpInvalidLogicalOp;
}


void PredicateImpl::setTerm(Predicate *p1, LogicalOp op, Predicate *p2 )
{
    if (p2 == NULL && op != OpNot || op == OpNot && p2 != NULL) 
    { 
        //TODO::printError
        return; 
    }
    lhs = (PredicateImpl*)p1;
    rhs = (PredicateImpl*)p2;
    logicalOp = op;
    compOp = OpInvalidComparisionOp;
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
    printDebug(DM_Predicate, "Evaluate start logical:%d compOp:%d", logicalOp, compOp);
    DbRetVal retCode =OK;
    result = false;
    if (NULL != lhs)
    {
        retCode = lhs->evaluate(lhsResult);
        printDebug(DM_Predicate, "LHS result %d retcode: %d", lhsResult, retCode);
        if (retCode != OK) return ErrInvalidExpr;
    }
    if (NULL != rhs)
    {
        retCode = rhs->evaluate(rhsResult);
        printDebug(DM_Predicate, "RHS result %d retcode:%d", rhsResult, retCode);
        if (retCode != OK) return ErrInvalidExpr;
    }
    if (NULL != lhs)
    {
        //Means it involves only Logical operator
        printDebug(DM_Predicate,"Evalute operator %d lhsResult %d : rhsResult %d", logicalOp, lhsResult, rhsResult );
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
    printDebug(DM_Predicate, "Evaluating comparision predicate op:%d", compOp);
    //Means it is relational expression
    //first operand is always field identifier
    //get the value in the tuple
    int offset1, offset2;
    offset1 = table->getFieldOffset(fldName1);
    //TODO::do not call getFieldXXX many times, instead get it using getFieldInfo
    char *val1, *val2 ;
    //Assumes that fldName2 data type is also same for expr f1 <f2
    DataType srcType = table->getFieldType(fldName1);
    val1 = ((char*) tuple) + offset1;
    if (operand == NULL && operandPtr == NULL)
    {
        if (fldName2) {
            offset2 = table->getFieldOffset(fldName2);
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
    printDebug(DM_Predicate, " fldname :%s ", fldName1);
	if (compOp == OpLike) result = ! fnmatch(val2, val1, 0);
    else result = AllDataType::compareVal(val1, val2, compOp, srcType,
                              table->getFieldLength(fldName1));
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
    if (OpEquals == compOp)
    {
        //for expressions f1 == f2 use full scan, so return false
        if(NULL == operand && NULL == operandPtr) return false;
        if(0 == strcmp(fldName1, fname)) 
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
    if (OpLessThan == compOp || OpLessThanEquals == compOp ||
        OpGreaterThan == compOp || OpGreaterThanEquals == compOp)
    {
         //for expressions f1 == f2 use full scan, so return false
        if(NULL == operand && NULL == operandPtr) return false;
        if(0 == strcmp(fldName1, fname))
        {
            return true;
        }
    }
    return false;
}


void* PredicateImpl::valPtrForIndexField(const char *fname)
{
    void *lhsRet, *rhsRet;
    if (NULL != lhs)
    {
        lhsRet = lhs->valPtrForIndexField(fname);
    }
    if (NULL != rhs)
    {
        rhsRet = rhs->valPtrForIndexField(fname);
    }
    if (NULL != lhs)
    {
        //Means it involves only Logical operator
        if ( lhsRet !=  NULL) return lhsRet;
        if ( rhsRet !=  NULL) return rhsRet;
    }
    //Means it is relational expression
    //first operand is always field identifier
    //if (OpEquals == compOp)
    {
        if(0 == strcmp(fldName1, fname)) 
        {
            if (operand) return operand; else return *(void**)operandPtr;
        }
    }
    return NULL;
}
ComparisionOp PredicateImpl::opForIndexField(const char *fname)
{
    ComparisionOp lhsRet, rhsRet;
    if (NULL != lhs)
    {
        lhsRet = lhs->opForIndexField(fname);
    }
    if (NULL != rhs)
    {
        rhsRet = rhs->opForIndexField(fname);
    }
    if (NULL != lhs)
    {
        if ( lhsRet !=  NULL) return lhsRet;
        if ( rhsRet !=  NULL) return rhsRet;
    }
    if(0 == strcmp(fldName1, fname))
    {
        return compOp;
    }
    return OpInvalidComparisionOp;
}

