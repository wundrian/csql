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
void Expression::setFunctionType(FunctionType type)
{
    if(NULL!=lhs)
        lhs->setFunctionType(type);      
    if(NULL!=rhs)
        rhs->setFunctionType(type);
    fType = type;
}
void Expression::setExpr(Expression* exp1, FunctionType type,Expression* exp2) 
{
    lhs = exp1;
    rhs = exp2;
    setFunctionType(type);
    arOp=unKnownOperator;
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

void *Expression::evaluateForFunction(DataType type)
{
    void *rhsResult = NULL , *lhsResult = NULL;
    if (NULL != lhs)
    {
        lhsResult =(char *) lhs->evaluateForFunction(type);
        if (NULL == lhsResult) return lhsResult;
    }
    if (NULL != rhs)
    {
        rhsResult  = (char *)rhs->evaluateForFunction(type);
        if (NULL == rhsResult) return rhsResult;
    }
    int offset;
    char *val=NULL;
    if(NULL==lhs && NULL == rhs)
    {
        if(strcmp(fldName,"\0")!=0)
        {
            DataType srcType = table->getFieldType(fldName);
            offset=table->getFieldOffset(fldName);
            setDataType(srcType);
            val= ((char*) tuple) + offset;
            if(table->isFldNull(fldName))
            {
                return NULL;
            }else {
               calVal=AllDataType::alloc(srcType,IDENTIFIER_LENGTH);
               AllDataType::copyVal(calVal,val, srcType,IDENTIFIER_LENGTH);
               return calVal;
            }

        }
        calVal=AllDataType::alloc(type,IDENTIFIER_LENGTH);
        AllDataType::memoryset(calVal,type);
        if(constVal!= NULL && strcmp(fldName,"\0")==0)
        {
            copyFunctionVal(calVal, constVal, fType, IDENTIFIER_LENGTH);
            return calVal;
        }
    }
    if(NULL!=lhsResult && NULL!=rhsResult)
    {
        if(calVal==NULL){
            calVal=AllDataType::alloc(type,IDENTIFIER_LENGTH);
            AllDataType::memoryset(calVal,type);
        }
        return evaluateAndGetValPtr(lhsResult,rhsResult);
    }
    if(NULL!=lhsResult && NULL==rhsResult)
    {
        if(calVal==NULL){
            calVal=AllDataType::alloc(type,IDENTIFIER_LENGTH);
            AllDataType::memoryset(calVal,type);
        }
        dType = lhs->getDataType();
        if(fType == EXTRACTYEARFROMDAY || fType == EXTRACTHOURFROMTIME){
            if(dType == typeTimeStamp)
                fType = (FunctionType)((int)(fType)+3);
        }
        return evaluateAndGetValPtr(lhsResult,rhsResult);
    }
    return NULL;
}

void *Expression::evaluateAndGetValPtr( void *lhsResult, void *rhsResult)
{
    switch(fType)
    {
        case DATEDIFF:
        {
            *(int *)calVal = (*(Date*)lhsResult - *(Date*)rhsResult);
            return calVal;
        }
        case DATEADDWITHYEAR:
        {
           ((Date*)lhsResult)->addYear(*(int*)rhsResult);
           return lhsResult;
        }
        case DATEADDWITHMON: 
        {
           ((Date*)lhsResult)->addMonth(*(int*)rhsResult);
           return lhsResult;
        }
        case DATEADDWITHDAY:
        {
           ((Date*)lhsResult)->addDay(*(int*)rhsResult);
           return lhsResult;
        }
        case DATESUBWITHYEAR:
        {
           ((Date*)lhsResult)->subYear(*(int*)rhsResult);
           return lhsResult;
        }
        case DATESUBWITHMON:
        {
           ((Date*)lhsResult)->subMonth(*(int*)rhsResult);
           return lhsResult;
        }
        case DATESUBWITHDAY:
        {
           ((Date*)lhsResult)->subDay(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMEDIFF:
        {
           *(int *)calVal = (*(Time*)lhsResult - *(Time*)rhsResult);
            return calVal;
        } 
        case TIMEADDWITHHOUR:
        {
           ((Time*)lhsResult)->addHour(*(int*)rhsResult);
           return lhsResult; 
        }
        case TIMEADDWITHMIN: 
        {
           ((Time*)lhsResult)->addMin(*(int*)rhsResult);
           return lhsResult; 
        }
        case TIMEADDWITHSEC:
        {
           ((Time*)lhsResult)->addSec(*(int*)rhsResult);
           return lhsResult; 
        }
        case TIMESUBWITHHOUR: 
        {
           ((Time*)lhsResult)->subHour(*(int*)rhsResult);
           return lhsResult; 
        }
        case TIMESUBWITHMIN:
        {
           ((Time*)lhsResult)->subMin(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESUBWITHSEC:
        {
           ((Time*)lhsResult)->subSec(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPADDWITHYEAR:
        {
           ((TimeStamp*)lhsResult)->addYear(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPADDWITHMON:
        {
           ((TimeStamp*)lhsResult)->addMonth(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPADDWITHDAY:
        {
           ((TimeStamp*)lhsResult)->addDay(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPSUBWITHYEAR:
        {
           ((TimeStamp*)lhsResult)->subYear(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPSUBWITHMON:
        {
           ((TimeStamp*)lhsResult)->subMonth(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPSUBWITHDAY:
        {
           ((TimeStamp*)lhsResult)->subDay(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPADDWITHHOUR:
        {
           ((TimeStamp*)lhsResult)->addHour(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPADDWITHMIN:
        {
           ((TimeStamp*)lhsResult)->addMin(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPADDWITHSEC:
        {
           ((TimeStamp*)lhsResult)->addSec(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPSUBWITHHOUR:
        {
           ((TimeStamp*)lhsResult)->subHour(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPSUBWITHMIN:
        {
           ((TimeStamp*)lhsResult)->subMin(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPSUBWITHSEC:
        {
           ((TimeStamp*)lhsResult)->subSec(*(int*)rhsResult);
           return lhsResult;
        }
        case TIMESTAMPDIFFYEAR:
        {
           *(int *)calVal = ((TimeStamp*)lhsResult)->yearDiff((*(TimeStamp*)rhsResult));
            return calVal;
        }
        case TIMESTAMPDIFFMON:
        {
           *(int *)calVal = ((TimeStamp*)lhsResult)->monthDiff((*(TimeStamp*)rhsResult));
            return calVal;
        }
        case TIMESTAMPDIFFDAY:
        {
           *(int *)calVal = ((TimeStamp*)lhsResult)->dayDiff((*(TimeStamp*)rhsResult));
            return calVal;
        }
        case TIMESTAMPDIFFHOUR:
        {
           *(int *)calVal = ((TimeStamp*)lhsResult)->hourDiff((*(TimeStamp*)rhsResult));
            return calVal;
        }
        case TIMESTAMPDIFFMIN:
        {
           *(int *)calVal = ((TimeStamp*)lhsResult)->minDiff((*(TimeStamp*)rhsResult));
            return calVal;
        }
        case TIMESTAMPDIFFSEC:
        {
           *(int *)calVal = ((TimeStamp*)lhsResult)->secDiff((*(TimeStamp*)rhsResult));
            return calVal;
        }
        case EXTRACTYEARFROMDAY:
        {
           *(int *)calVal = ((Date*)lhsResult)->year(); 
            return calVal;
        }
        case EXTRACTMONFROMDAY:
        {
           *(int *)calVal = ((Date*)lhsResult)->month(); 
            return calVal;
        }
        case EXTRACTDAYFROMDAY:
        {
            *(int *)calVal = ((Date*)lhsResult)->dayOfMonth();
            return calVal;
        }
        case EXTRACTHOURFROMTIME:
        {
            *(int *)calVal = ((Time*)lhsResult)->hours();
            return calVal;
        }
        case EXTRACTMINFROMTIME:
        {
            *(int *)calVal = ((Time*)lhsResult)->minutes();
            return calVal;
        }
        case EXTRACTSECFROMTIME:
        {
            *(int *)calVal = ((Time*)lhsResult)->seconds();
            return calVal;
        }
        case EXTRACTYEARFROMTIMESTAMP:
        {
            *(int *)calVal = ((TimeStamp*)lhsResult)->year();
            return calVal;
        }
        case EXTRACTMONFROMTIMESTAMP:
        {
            *(int *)calVal = ((TimeStamp*)lhsResult)->month();
            return calVal;
        }
        case EXTRACTDAYFROMTIMESTAMP:
        {
            *(int *)calVal = ((TimeStamp*)lhsResult)->dayOfMonth();
            return calVal;
        }
        case EXTRACTHOURFROMTIMESTAMP:
        {
            *(int *)calVal = ((TimeStamp*)lhsResult)->hours();
            return calVal;
        }
        case EXTRACTMINFROMTIMESTAMP:
        {
            *(int *)calVal = ((TimeStamp*)lhsResult)->minutes();
            return calVal;
        }
        case EXTRACTSECFROMTIMESTAMP:
        {
            *(int *)calVal = ((TimeStamp*)lhsResult)->seconds();
            return calVal;
        }
        default: return NULL; 
    }
 
}

void Expression::copyFunctionVal(void *dest,void *src, FunctionType type, int length)
{
     switch(type)
    {
        case DATEDIFF: 
        {
            //Date date;
            //date.parseFrom((char*)src);
            AllDataType::copyVal(dest, src, typeDate,length);
            return;
        }
        case DATEADDWITHYEAR:
        {
            AllDataType::copyVal(dest, src,typeInt,length);
            return;
        }
        case DATEADDWITHMON: 
        {
            AllDataType::copyVal(dest, src,typeInt,length);
            return;
        }
        case DATEADDWITHDAY:
        {
            AllDataType::copyVal(dest, src,typeInt,length);
            return;
        }
        case DATESUBWITHYEAR: 
        {
            AllDataType::copyVal(dest, src,typeInt,length);
            return;
        }
        case DATESUBWITHMON: 
        {
            AllDataType::copyVal(dest, src,typeInt,length);
            return;
        }
        case DATESUBWITHDAY:
        {
            AllDataType::copyVal(dest, src,typeInt,length);
            return;
        }
        case TIMEDIFF: 
        {
            AllDataType::copyVal(dest, src, typeTime,length);
            return;
        }
        case TIMEADDWITHHOUR: 
        case TIMEADDWITHMIN:
        case TIMEADDWITHSEC:
        case TIMESUBWITHHOUR:
        case TIMESUBWITHMIN:
        case TIMESUBWITHSEC:
        {
            AllDataType::copyVal(dest, src,typeInt,length);
            return;
        }
        case TIMESTAMPADDWITHYEAR:
        case TIMESTAMPADDWITHMON:
        case TIMESTAMPADDWITHDAY:
        case TIMESTAMPSUBWITHYEAR:
        case TIMESTAMPSUBWITHMON:
        case TIMESTAMPSUBWITHDAY:
        case TIMESTAMPADDWITHHOUR:
        case TIMESTAMPADDWITHMIN:
        case TIMESTAMPADDWITHSEC:
        case TIMESTAMPSUBWITHHOUR:
        case TIMESTAMPSUBWITHMIN:
        case TIMESTAMPSUBWITHSEC:
        {
            AllDataType::copyVal(dest, src,typeInt,length);
            return;
        }
        case TIMESTAMPDIFFYEAR:
        case TIMESTAMPDIFFMON:
        case TIMESTAMPDIFFDAY:
        case TIMESTAMPDIFFHOUR:
        case TIMESTAMPDIFFMIN:
        case TIMESTAMPDIFFSEC:
        {
            AllDataType::copyVal(dest, src,typeTimeStamp,length);
            return;
        }
        case EXTRACTYEARFROMDAY:
        case EXTRACTMONFROMDAY:
        case EXTRACTDAYFROMDAY:
        case EXTRACTHOURFROMTIME:
        case EXTRACTMINFROMTIME:
        case EXTRACTSECFROMTIME:
        case EXTRACTYEARFROMTIMESTAMP:
        case EXTRACTMONFROMTIMESTAMP:
        case EXTRACTDAYFROMTIMESTAMP:
        case EXTRACTHOURFROMTIMESTAMP:
        case EXTRACTMINFROMTIMESTAMP:
        case EXTRACTSECFROMTIMESTAMP:
        default: return;
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
