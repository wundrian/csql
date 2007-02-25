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
#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H
//USER EXPOSED
#include<Info.h>
class Table;
//User exposed class who provides interface to manage all database objects
//which include create/drop table/index
class DatabaseManager
{
    public:
    virtual DbRetVal createTable(const char *name, TableDef &def)=0;
    virtual DbRetVal dropTable(const char *name)=0;
    virtual Table* openTable(const char *name)=0;
    virtual void closeTable(Table *table)=0;

    //Pass appropriate IndexInitInfo derived class object.
    virtual DbRetVal createIndex(const char *indName, IndexInitInfo *info)=0;
    virtual DbRetVal dropIndex(const char *name)=0;
    virtual ~DatabaseManager(){ }
};

#endif
