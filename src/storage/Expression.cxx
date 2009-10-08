/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
 *                                                                         *
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
 * ***************************************************************************/
#include<Expression.h>
#include<Table.h>
#include<TableImpl.h>

void Expression::setTable(Table *tbl )
{
    if(NULL!=lhs)
        lhs->setTable(tbl);
    if(NULL!=rhs)
        rhs->setTable(tbl);

    table=(TableImpl*) tbl;
}

void Expression::setTuple(void *tpl)
{
    if(NULL!=lhs)
        lhs->setTuple(tpl);
    if(NULL!=rhs)
        rhs->setTuple(tpl);

    tuple = tpl;
}
 
void Expression::setExpr(void *cVal,bool flag)
{
    arOp=unKnownOperator;
    constVal=cVal;
    lhs = rhs = NULL;
}

void Expression::setExpr(char const *name,ArithOperator op,void *cVal)
{
    strcpy(fldName, name);
    arOp = op;
    constVal = cVal;
    lhs = rhs = NULL;
}

void Expression::setExpr(char const *name)
{
    strcpy(fldName, name);
    arOp=unKnownOperator;
    constVal=NULL;
    lhs = rhs = NULL;
}

void Expression::setExpr(Expression *exp1, ArithOperator op, Expression *exp2)
{
        lhs = exp1;
        rhs = exp2;
        arOp = op;
}

void *Expression::evaluate(DataType type,bool &result)
{   
    calVal=AllDataType::alloc(type,IDENTIFIER_LENGTH);
    AllDataType::memoryset(calVal,type);
    char *rhsResult = NULL , *lhsResult = NULL;
    if (NULL != lhs)
    {
        lhsResult =(char *) lhs->evaluate(type,result);
        if (NULL == lhsResult) return lhsResult;
    }
    if (NULL != rhs)
    {
        rhsResult  = (char *)rhs->evaluate(type,result);
        if (NULL == rhsResult) return rhsResult;
    }
    if(result){return tuple;}
    if (0==strcmp(fldName,"NULL")){
        result=true;return tuple;
    }
    int offset;
    char *val=NULL;
    if(NULL==lhs && NULL == rhs)
    {
        if(strcmp(fldName,"\0")!=0)
        {
            DataType srcType = table->getFieldType(fldName);
            if(srcType > 12) return NULL;
            else 
            {
                offset=table->getFieldOffset(fldName);
                val= ((char*) tuple) + offset;
                if(table->isFldNull(fldName))
                {
                    result=true;
                    return tuple;
                }

            }
        }
        if(constVal!= NULL && strcmp(fldName,"\0")!=0)
        {
            os::memcpy(calVal,val,table->getFieldLength(fldName));
            solve(calVal, constVal, type, arOp);  
        } 
        else if(constVal!= NULL && 0==strcmp(fldName,"\0"))   
        {
            AllDataType::copyVal(calVal, constVal, type, IDENTIFIER_LENGTH);
        }
        else if( NULL==constVal && strcmp(fldName,"\0")!=0)
        {
            os::memcpy(calVal,val,table->getFieldLength(fldName));
        }
        return calVal;
    }
    if(NULL!=lhsResult && NULL!=rhsResult)
    {
        solve(lhsResult, rhsResult, type, arOp);
        return lhsResult;
    }
    
}

void Expression::solve(void *opand1, void *opand2, DataType type, ArithOperator arOp)
{
    switch(arOp)
    {
        case addition:
            AllDataType::addVal(opand1, opand2, type );
            break;
        case subtraction:
            AllDataType::subVal(opand1, opand2, type);
            break;
        case multiplication:
            AllDataType::mulVal(opand1, opand2, type);
            break;
        case division:
            AllDataType::divVal(opand1, opand2, type);
            break;
        case modulus:
            AllDataType::mudVal(opand1, opand2, type);
            break;
        default:
            break;
    }
    return;
}

bool Expression::isSingleTerm()
{
    if (NULL==lhs && NULL==rhs ) return true; 
    else false;
}
void Expression::memFree()
{
    if(lhs!=NULL)
        lhs->memFree();
    if(rhs!=NULL)
        rhs->memFree();
    free(calVal);
}

void Expression::convertStrToVal(DataType type)
{
    if(lhs!=NULL)
        lhs->convertStrToVal(type);
    if(rhs!=NULL)
        rhs->convertStrToVal(type);
    if(constVal !=NULL)
    {   
        void *parseString=constVal;
        constVal=AllDataType::alloc(type);
        AllDataType::strToValue(constVal,(char*)parseString, type);
        free(parseString);
    }    

}
void Expression::freeVal()
{
    if(lhs!=NULL)
        lhs->freeVal();
    if(rhs!=NULL)
        rhs->freeVal();
    if(constVal !=NULL)
        free(constVal);
}
