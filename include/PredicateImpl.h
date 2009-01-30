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
#ifndef PREDICATE_IMPL_H
#define PREDICATE_IMPL_H
#include<DataType.h>
#include<Predicate.h>
#include<ErrorType.h>
class TableImpl;
class Table;
class List;
class PredicateImpl:public Predicate
{
    //Members set during initialization of the term
    char fldName1[IDENTIFIER_LENGTH];
    char fldName2[IDENTIFIER_LENGTH];
    ComparisionOp compOp;
    void *operand;
    void **operandPtr;
    LogicalOp logicalOp;
    PredicateImpl *lhs;
    PredicateImpl *rhs;
    PredicateImpl *parent;
    int offset1,offset2;
    DataType type;
    int length;
    //Members set during execution
    void *tuple; //pointer to the tuple
    List *projList;

    //This will be set before calling evaluate
    TableImpl *table;

    public:
    PredicateImpl()
    {
        strcpy(fldName1, ""); strcpy(fldName2, ""); 
        operand = NULL; operandPtr = NULL; lhs = rhs = NULL; 
        tuple = NULL; table = NULL; 
        projList = NULL;
        parent = NULL;
        offset1 = -1;  offset2 =-1;
        type = typeUnknown;
        length = 0;
    }
    ~PredicateImpl(){}

    void setTerm(const char* fName1, ComparisionOp op, const char *fName2);

    //Operand should be of the same type of the field.This is must
    void setTerm(const char* fName1, ComparisionOp op, void *opnd);

    void setTerm(const char* fName1, ComparisionOp op, void **opnd);


    void setTerm(Predicate *p1, LogicalOp op, Predicate *p2 = NULL);

    void* valPtrForIndexField(const char *name);
    ComparisionOp opForIndexField(const char *name);

    DbRetVal evaluate(bool &result);

    void setTable(Table *tbl);
    void setTuple(void *tpl);
    void setProjectionList(List *list); //used by JoinTableImpl
    void setOffsetAndType();
    bool isSingleTerm();
    bool isNotOrInvolved();
    //check predicate, whether it has field name and == operator
    //and does not have OR, NOT operator
    // TODO:: expression like !(f1 !=100) wont be optimized for now
    bool pointLookupInvolved(const char *fName);
    bool rangeQueryInvolved(const char *fName);
    bool isBetweenInvolved(const char *fname);
    PredicateImpl *getTablePredicate();
    PredicateImpl *getJoinPredicate();
    void removeIfNotNecessary();
    bool isDummyPredicate();
    PredicateImpl* getIfOneSidedPredicate();
    void setParent(PredicateImpl *pImpl);
    char* getFldName1(){ return fldName1; }
    char* getFldName2(){ return fldName2; }
    ComparisionOp getCompOp() {return compOp; }
    void print(int space);
};

#endif
