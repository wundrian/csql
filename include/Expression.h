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
#ifndef EXPRESSION_H 
#define EXPRESSION_H
#include<os.h>
#include<DataType.h>

class Table;
class TableImpl;

enum ArithOperator {
    unKnownOperator = 0,
    addition,
    subtraction,
    multiplication,
    division,
    modulus
};
class Expression
{
    char fldName[IDENTIFIER_LENGTH];
    void *tuple;
    void *constVal;
    void *calVal;
    TableImpl *table;
    ArithOperator arOp;
    Expression *lhs;
    Expression *rhs;
    public:
    Expression()
    {
        table=NULL; arOp = unKnownOperator; lhs=NULL; rhs=NULL;
        tuple=NULL; constVal=NULL;
        strcpy(fldName,"\0");
    }
    ~Expression()
    {
        if(lhs){ delete lhs; lhs=NULL;}
        if(rhs){ delete rhs; rhs=NULL;}
    }
    void setTable(Table *tbl);
    void setTuple(void *tpl);
    bool isSingleTerm();
    void setExpr(char const *name,ArithOperator op,void *cVal );
    void setExpr(char const *name);
    void setExpr(Expression *exp1, ArithOperator op, Expression *exp2 );
    void setExpr(void *cVal,bool flag );
    void *evaluate(DataType type,bool &result);
    void solve(void *opand1, void *opand2, DataType type, ArithOperator arOp);
    void convertStrToVal(DataType type);
    void freeVal();
    void memFree();
};

#endif
