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
#include<Info.h>
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
* @author Prabakaran Thirumalai
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

    /** opens a table for processing
    *   @param name name of the table
    *   @return DbRetVal
    */
    virtual Table* openTable(const char *name)=0;
 
    /** closes the table handle passed
    *   @param table handle to the table
    */
    virtual void closeTable(Table *table)=0;

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
    virtual ~DatabaseManager(){ }
};

#endif
