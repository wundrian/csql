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
#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H
#include<Info.h>
#include<Util.h>
class Table;
/**
* @class DatabaseManager
*
* @brief Interface for database management operations.
* This manages all the database objects. Currently it supports two database <br>
* objects namely table and index.<br/>
* <br/>
* Functionality: <br/>
*     1.Table Management (create, drop, open and close) <br/>
*     2.Index Management (create and drop) <br/>
* <br/>
* 
*/
class DatabaseManager
{
    public:
    /** creates a table in the database
    *   @param name name of the table
    *   @param def table definition
    *   @return DbRetVal
    */
    virtual DbRetVal createTable(const char *name, TableDef &def)=0;

    /** deletes a table from the database
    *   @param name name of the table
    *   @return DbRetVal
    */
    virtual DbRetVal dropTable(const char *name)=0;
    virtual DbRetVal renameTable(const char *oldName,const char *newName)=0;
    virtual DbRetVal renameField(const char *tableName, const char *oldName, const char *newName)=0;
    /** opens a table for processing
    *   @param name name of the table
    *   @return DbRetVal
    */
    virtual Table* openTable(const char *name, bool checkpkfk=true)=0;
 
    /** closes the table handle passed
    *   @param table handle to the table
    */
    virtual void closeTable(Table *table)=0;

    /** Returns all the tables as list
    *   @return List of table names
    */
    virtual List getAllTableNames(int *rv=0)=0;

    /** creates an index on the specified table. <br/>
    *   Create appropriate derived class object of IndexInitInfo based on the type of <br/>
    *   the index created and pass it to this method.
    *   @param indName index name
    *   @param info IndexInitInfo 
    */
    virtual DbRetVal createIndex(const char *indName, IndexInitInfo *info)=0;

    /** deletes the index object
    *   @param name index name
    */
    virtual DbRetVal dropIndex(const char *name)=0;
    virtual DbRetVal checkPoint()=0;
    virtual DbRetVal recover()=0;
    virtual DbRetVal createForeignKey(char *fkName,ForeignKeyInfo *info)=0;
    virtual DbRetVal dropForeignKey(void *ctpr,bool trylock)=0;
    virtual void sendSignal(int sig)=0;
    virtual ~DatabaseManager(){ }
};

#endif
