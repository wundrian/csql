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
#ifndef PREDICATE_H
#define PREDICATE_H
#include<DataType.h>
class PredicateImpl;
class Predicate;
class Condition
{
    Predicate *pred;
    public:
    Condition();
    ~Condition();
    void setTerm(const char* fName1, ComparisionOp op, const char *fName2);
    void setTerm(const char* fName1, ComparisionOp op, void *opnd);
    void setTerm(Predicate *p1, LogicalOp op, Predicate *p2 = NULL);
    Predicate* getPredicate() { return pred; }
};
//User Exposed
class Predicate
{
    public:
    virtual void setTerm(const char* fName1, ComparisionOp op, const char *fName2)=0;

    //Operand should be of the same type of the field. This is must
    virtual void setTerm(const char* fName1, ComparisionOp op, void *opnd)=0;

    virtual void setTerm(Predicate *p1, LogicalOp op, Predicate *p2 = NULL)=0;
};


#endif
