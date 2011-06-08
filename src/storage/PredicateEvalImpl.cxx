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
#include<JoinTableImpl.h>
#include<Util.h>
DbRetVal PredicateImpl::evaluateLogical(bool &result)
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
        if (OpAnd == logicalOp) {
            if (lhsResult && rhsResult) result = true;
        }else if (OpOr == logicalOp) {
            if (lhsResult || rhsResult) result = true;
        }else if (OpNot == logicalOp){
            if (lhsResult)  result = false; else result = true;
        }
        printDebug(DM_Predicate, "result is %d", result);
    }
    return OK;
}

DbRetVal PredicateImpl::evaluateForHaving(bool &result, AggTableImpl *aImpl, void *aggElement)
{
    bool rhsResult = false, lhsResult=false;
    DbRetVal retCode =OK;
    result = false;
    if (NULL != lhs)
    {
       retCode = lhs->evaluateForHaving(lhsResult, aImpl, aggElement);
        if (retCode != OK) return ErrInvalidExpr;
    }else lhsResult = true;
    if (NULL != rhs)
    {
        retCode = rhs->evaluateForHaving(rhsResult, aImpl, aggElement);
        if (retCode != OK) return ErrInvalidExpr;
    } else rhsResult = true;
    if (NULL != lhs)
    {
        if (OpAnd == logicalOp) {
            if (lhsResult && rhsResult) result = true;
        }else if (OpOr == logicalOp) {
            if (lhsResult || rhsResult) result = true;
        }else if (OpNot == logicalOp){
            if (lhsResult)  result = false; else result = true;
        }
        printDebug(DM_Predicate, "result is %d", result);
        return OK;
    }

    void *val1 = NULL, *val2 =NULL;
    int  offset = aImpl->getAggOffset(fldName1, aggType);
    val1 = (void*)((char*)aggElement + offset);
    if (!isBindBufSet) {
        //sets the type and length when it is called first time
        FieldInfo *info = new FieldInfo();
        DbRetVal rv  = aImpl->getFieldInfo(fldName1, info);
        if (aggType == AGG_AVG) {
            type = typeDouble;
            length = sizeof(double);
        } else if (aggType == AGG_COUNT) { 
            type = typeInt;
            length = sizeof(int);
        } else {
            type = info->type;
            length = info->length;
        }
        delete info;
        isBindBufSet = true;
    }
    if(operand != NULL && operandPtr == NULL)
    {
        val2 = (char*) operand;
    }
    else if(operand == NULL && operandPtr != NULL)
    {
            val2 = *(char**)operandPtr;
    }
    if (aggType == AGG_AVG) { 
        double dVal2 = 0;
        AllDataType::convertToDouble(&dVal2, val2, type);
        result = AllDataType::compareVal(val1, &dVal2, compOp, typeDouble, length);
    }
    else  if (aggType == AGG_COUNT) {
        int dVal2 = 0;
        AllDataType::convertToInt(&dVal2, val2, type);
        result = AllDataType::compareVal(val1, &dVal2, compOp, typeInt, length);
    } 
    else
        result = AllDataType::compareVal(val1, val2, compOp, type, length);
    return OK;
}

DbRetVal PredicateImpl::evaluateLogicalForTable(bool &result, char *tuple)
{
    bool rhsResult = false, lhsResult=false;
    DbRetVal retCode =OK;
    result = false;
    if (NULL != lhs)
    {
        lhs->evaluateForTable(lhsResult, tuple);
    }else lhsResult = true;
    if (NULL != rhs)
    {
        rhs->evaluateForTable(rhsResult, tuple);
    } else rhsResult = true;
    if (NULL != lhs)
    {
        //Means it involves only Logical operator
        if (OpAnd == logicalOp) {
            if (lhsResult && rhsResult) result = true;
        }else if (OpOr == logicalOp) {
            if (lhsResult || rhsResult) result = true;
        }else if (OpNot == logicalOp){
            if (lhsResult)  result = false; else result = true;
        }
        printDebug(DM_Predicate, "result is %d", result);
    }
    return OK;
}
void PredicateImpl::evaluateForTable(bool &result, char *tuple)
{
    if (!isNoLeftRight) {
        bool rhsResult = false;
        if (NULL != rhs)
        {
            rhs->evaluateForTable(rhsResult, tuple);
            if(rhsResult == false && OpAnd == logicalOp) {//do early return
                result = false;
                return;
            }
        } else rhsResult = true;
        bool lhsResult = false;
        if (NULL != lhs)
        {
            lhs->evaluateForTable(lhsResult, tuple);
        }else lhsResult = true;
        if (NULL != lhs)
        {
            //Means it involves only Logical operator
            if (OpAnd == logicalOp) {
                if (lhsResult && rhsResult) result = true;
            }else if (OpOr == logicalOp) {
                if (lhsResult || rhsResult) result = true;
            }else if (OpNot == logicalOp){
                if (lhsResult)  result = false; else result = true;
            }
            printDebug(DM_Predicate, "result is %d", result);
            return ;
        }
    }
    //Table null check of condition
    if(lExp || rExp){
       void* val=NULL;    
       void* rval = NULL;
       TableImpl *tImpl =  (TableImpl*) table;
       if(lExp){  
          lExp->setTable(tImpl);
          lExp->setTuple(tuple);
          val = lExp->evaluateForFunction(AllDataType::getCsqlTypeFromFunctionType(lExp->getFunctionType())); 
       }
       if(rExp) {  
          rExp->setTable(tImpl);
          rExp->setTuple(tuple);
          rval = rExp->evaluateForFunction(AllDataType::getCsqlTypeFromFunctionType(rExp->getFunctionType()));
       }
       if( val && rval){
          result = AllDataType::compareVal(val, rval, compOp, AllDataType::getCsqlTypeFromFunctionTypeForComparision(lExp->getFunctionType()),length);
       }else if( val && operandPtr!=NULL){
           val2 = *(char**)operandPtr;
           result = AllDataType::compareVal(val, val2, compOp, AllDataType::getCsqlTypeFromFunctionTypeForComparision(lExp->getFunctionType()),length);
       }else if(val && (offset2 != -1 && operand == NULL && operandPtr == NULL)){
             val2 = tuple + offset2;
             result = AllDataType::compareVal(val, val2, compOp, AllDataType::getCsqlTypeFromFunctionTypeForComparision(lExp->getFunctionType()),length); 
       }else{
           result =false;
       }
       
       return;
    }
    if (isNullable) {
        TableImpl *tImpl =  (TableImpl*) table;
        tImpl->setCurTuple(tuple);
        bool isValueNull = table->isFldNull(fldPos);
        if(compOp == OpIsNull)
        {
           if( (isValueNull && isNull) || (!isValueNull && !isNull) )
           result = true;
           else
            result = false;
           return;
        }
        if(isValueNull)
        {
            result=false;
            return;
        }
    }
    //the below code works only for single table 
    val1= tuple + offset1;
    if(offset2 != -1 && operand == NULL && operandPtr == NULL)
        val2 = tuple + offset2; 
    if (!isBindBufSet) {
       //Assumes that fldName2 data type is also same for expr f1 <f2
       //Note:Perf: Do not change the order below
       if(operand == NULL && operandPtr != NULL)
       { 
          val2 = *(char**)operandPtr;
          if (compOp == OpLike) {
             char *c = (char *)val2;
             //OPT:If LIKE has only %, then no need to evaluate
             if (*c == '%' && *(c+1) == '\0') {result=true; return;}
             Util::changeWildcardChar(val2);
          }

       } else if (operand == NULL && operandPtr == NULL)
       {
         if(offset2 != -1)
             val2 = tuple + offset2; 
       } else if(operand != NULL && operandPtr == NULL)
       { 
          val2 = (char*) operand;
          if (compOp == OpLike) {
             char *c = (char *)val2;
             if (*c == '%' && *(c+1) == '\0') {result=true; return;}
             Util::changeWildcardChar(val2);
          }
       } 
       if(operand2 == NULL && operand2Ptr != NULL)
       { 
          val3 = *(char**)operand2Ptr;
       } else if(operand2 != NULL && operand2Ptr == NULL)
       { 
          val3 = (char*) operand2;
       }
       isBindBufSet = true;
    }
    result = true;
    if(val3) {
        //printf(" val1 %d val3 %d\n", *(int*)val1, *(int*)val3);
        result = AllDataType::compareVal(val1, val3, comp2Op, type,length);
        if(result==false) return;
    }
    if (isPushedDown) {
        return;
    }
    //printf(" val1 %d val2 %d\n", *(int*)val1, *(int*)val2);
    if (type != typeVarchar) 
        result = AllDataType::compareVal(val1, val2, compOp, type,length);
    else 
        result = AllDataType::compareVal((void *) *(long *) val1, val2, 
                                                         compOp, type,length);
    return;
}

DbRetVal PredicateImpl::evaluate(bool &result)
{
    if (!isNoLeftRight) {
        bool rhsResult = false, lhsResult=false;
        DbRetVal retCode =OK;
        result = false;
        if (NULL != lhs)
        {
            retCode = lhs->evaluate(lhsResult);
            if (retCode < OK) return ErrInvalidExpr;
        }else lhsResult = true;
        if (NULL != rhs)
        {
            retCode = rhs->evaluate(rhsResult);
            if (retCode < OK) return ErrInvalidExpr;
        } else rhsResult = true;
        if (NULL != lhs)
        {
            //Means it involves only Logical operator
            if (OpAnd == logicalOp) {
                if (lhsResult && rhsResult) result = true;
            }else if (OpOr == logicalOp) {
                if (lhsResult || rhsResult) result = true;
            }else if (OpNot == logicalOp){
                if (lhsResult)  result = false; else result = true;
                if ( ErrNullValues == retCode) result = false;
            }
            printDebug(DM_Predicate, "result is %d", result);
            return OK;
        }
    }
    //Means it is relational expression
    //first operand is always field identifier
    //get the value in the tuple
    if (projList) {
      if (dontEvaluate) {result= true; return OK; }
      if (!isBindBufSet)
      {
        //for join node evaluation
        ListIterator fIter = projList->getIterator();        
        JoinProjFieldInfo  *def;
        //char *val1, *val2;
        while (fIter.hasElement())
        {
            def = (JoinProjFieldInfo*) fIter.nextElement();
            if (NULL != def->bindBuf) {
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
            char fieldName2[IDENTIFIER_LENGTH];
            memset(fieldName2, 0, IDENTIFIER_LENGTH);
            Table::getFieldNameAlone(fldName2, fieldName2);
            if (fieldName2) {
                fIter.reset();
                while (fIter.hasElement())
                {
                    def = (JoinProjFieldInfo*) fIter.nextElement();
                    if (NULL != def->bindBuf) {
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
        isBindBufSet = true;
      }
      JoinTableImpl *jTable = (JoinTableImpl*) table;
      if (jTable->isFldNullInt(fldName1) || jTable->isFldNullInt(fldName2))
      {
          result=false;
          return ErrNullValues;
      }
      result = AllDataType::compareVal(val1, val2, compOp, type,
                              length);
      return OK;

    }
    printf("PRABA::wrong method call\n");
    //the below code works only for single table 
    val1= (char*)tuple + offset1;
    if(offset2 != -1 && operand == NULL && operandPtr == NULL)
        val2 = ((char*)tuple) + offset2; 
    if (!isBindBufSet) {
       //Assumes that fldName2 data type is also same for expr f1 <f2
       //Note:Perf: Do not change the order below
       if(operand == NULL && operandPtr != NULL)
       { 
        val2 = *(char**)operandPtr;
       }
       else if (operand == NULL && operandPtr == NULL)
       {
         if(offset2 != -1)
             val2 = ((char*)tuple) + offset2; 
       } 
       else if(operand != NULL && operandPtr == NULL)
       { 
          val2 = (char*) operand;
       }
       isBindBufSet = true;
    }
    result = AllDataType::compareVal(val1, val2, compOp, type,length);
    return OK;
}
