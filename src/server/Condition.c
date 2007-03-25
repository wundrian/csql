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
#include<os.h>
#include<Predicate.h>
#include<PredicateImpl.h>
Condition::Condition()
{
    pred = new PredicateImpl();
}
Condition::~Condition()
{
    delete pred;
    pred = NULL;
}
void Condition::setTerm(const char* fName1, ComparisionOp op,
                        const char *fName2)
{
    pred->setTerm(fName1, op, fName2);
}

//Operand should be of the same type of the field.This is must
void Condition::setTerm(const char* fName1, ComparisionOp op, void *opnd)
{
    pred->setTerm(fName1, op, opnd);
}

void Condition::setTerm(Predicate *p1, LogicalOp op, Predicate *p2 )
{
    pred->setTerm(p1, op, p2);
}
