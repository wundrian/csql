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
#ifndef TABLE_H
#define TABLE_H
#include<ErrorType.h>
class Predicate;
class Condition;
class Table
{
    public:
    // search predicate
    virtual void setCondition(Condition c)=0;

    //binding
    virtual void bindFld(const char *name, void *val)=0;
    virtual void markFldNull(const char *name)=0;
    virtual void markFldNull(int colpos)=0;
    virtual bool isFldNull(const char *name)=0;
    virtual bool isFldNull(int colpos)=0;

    //DML operations
    virtual DbRetVal execute()=0;
    virtual DbRetVal insertTuple()=0;
    virtual DbRetVal updateTuple()=0;
    virtual DbRetVal deleteTuple()=0;
    //scan
    virtual void* fetch()=0;
    virtual DbRetVal close()=0;

    virtual ~Table() { }
};
#endif
