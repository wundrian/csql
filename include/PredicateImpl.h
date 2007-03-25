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
class TableImpl;
class Table;
class PredicateImpl:public Predicate
{
    //Members set during initialization of the term
    char fldName1[IDENTIFIER_LENGTH];
    char fldName2[IDENTIFIER_LENGTH];
    ComparisionOp compOp;
    void *operand;
    LogicalOp logicalOp;
    PredicateImpl *lhs;
    PredicateImpl *rhs;

    //Members set during execution
    void *tuple; //pointer to the tuple

    //This will be set before calling evaluate
    TableImpl *table;

    public:
    PredicateImpl(){ operand = NULL; lhs = rhs = NULL; }
    ~PredicateImpl(){}

    void setTerm(const char* fName1, ComparisionOp op, const char *fName2);

    //Operand should be of the same type of the field.This is must
    void setTerm(const char* fName1, ComparisionOp op, void *opnd);

    void setTerm(Predicate *p1, LogicalOp op, Predicate *p2 = NULL);

    void* valPtrForIndexField(const char *name);

    int evaluate(bool &result);

    void setTable(Table *tbl);
    void setTuple(void *tpl);

    //check predicate, whether it has field name and == operator
    //and does not have OR, NOT operator
    // TODO:: expression like !(f1 !=100) wont be optimized for now
    bool pointLookupInvolved(const char *fName);

};

#endif
