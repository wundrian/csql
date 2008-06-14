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
#ifndef TABLE_H
#define TABLE_H
#include<ErrorType.h>
#include<Util.h>
class Predicate;
class Condition;
/**
* @class Table
*
* @brief Handle to the database table.
* Table is a set of data values organized using a model of horizontal rows and columns.<br>
* Columns are identified by name and rows by values. It shall be visualized as a linked <br/>
* list of related data<br/>
* Functionality: <br/>
*     1.insert <br/>
*     2.update <br/>
*     3.delete <br/>
*     4.select with predicate or condition<br/>
* <br/>
* 
*/

class FieldInfo;
class Table
{
    public:
    /** sets condition for the select, update and delete operations
    *   @param c condition
    */
    virtual void setCondition(Condition *c)=0;

    /** binds application buffer to the specified field of the table.
    * Before doing any DML operations required fields are binded first.
    * Below are the candidates for this: <br/>
    * 1.All the fields in the projection list of select statement. <br/>
    * 2.Field list in the insert statement.<br/>
    * 3.Fields in the assignment list of update statement.<br/>
    * <br/>
    *   @param name field name in the table
    *   @param val  address of the application buffer. Memory should be allocated by
    *               the application before binding the buffer.
    */

    virtual DbRetVal bindFld(const char *name, void *val)=0;
    /** marks the specified field to insert null when insert method is called.
    *   @param name field name in the table
    */

    virtual void markFldNull(const char *name)=0;
    /** marks the specified field to insert null when insert method is called.
    *   @param colpos field position
    */
    virtual void markFldNull(int colpos)=0;

    /** clears the null mark which is set before.
    *   @param name field name
    */
    virtual void clearFldNull(const char *name)=0;

    /** clears the null mark which is set before.
    *   @param colpos field position
    */
    virtual void clearFldNull(int colpos)=0;

    /** checks whether the field value is null.
    *   @param name field name
    */
    virtual bool isFldNull(const char *name)=0;

    /** checks whether the field value is null for the specified field position.
    *   @param colpos field position
    */
    virtual bool isFldNull(int colpos)=0;
/*
    virtual void clearFldNull(const char *name)=0;
    virtual void clearFldNull(int colpos) =0;
*/

    //DML operations
    /** executes the select statement. Based on the predicate(condition), respective index is
    * chosen for the select. Application should call execute before they start fetching
    * the values from the table.This starts scan on the table.
    * @returns DbRetVal
    */
    virtual DbRetVal execute()=0;

    /** insert the tuple into the table. Prior to this, the binded buffer should be updated
    *  Values present in the binded buffers of all the fields are taken and stored in
    *  the table.<br/>
    * @returns DbRetVal
    */
    virtual DbRetVal insertTuple()=0;

    /**update values in the current tuple of the table. It works only on top of select
    *  using fetch go to the tuple to be updated, then update the binded buffer value and
    *  then call this method to updates the field values in the tuple.
    * @returns DbRetVal
    */
    virtual DbRetVal updateTuple()=0;

    /**deletes the current tuple of the table. It works only on top of select.
    *  using fetch first go to the tuple to be deleted, then call this method to delete.<br/>
    *  To delete all the tuples, do not set any condition and call fetch followed by delete
    *  in a loop till fetch exhausts.
    * @returns DbRetVal
    */

    virtual DbRetVal deleteTuple()=0;


    /**deletes all the records which satisfies the condition set.
    * @returns int totalTuples deleted
    */

    virtual int deleteWhere()=0;



    /**deletes the all the records in the table. No transaction required to call this. 
    *  It takes table level lock.
    * @returns DbRetVal
    */

    virtual int truncate()=0;



    //scan

    /**fetches the next tuple in the table which satisfies the condition specified.
    * execute should be called before calling this method. Application buffer should be 
    * binded to get the tuple values.
    * @returns void* NULL if there is no tuple.
    */
    virtual void* fetch()=0;
    virtual void* fetch(DbRetVal &rv)=0;

    /**fetches the next tuple in the table which satisfies the condition specified.
    * execute should be called before calling this method. Application buffer need not be 
    * binded to call this method.
    * @returns void* NULL if there is no tuple.
    */
    virtual void* fetchNoBind()=0;
    virtual void* fetchNoBind(DbRetVal &rv)=0;

    
    /**closes the scan. Needs to be called before calling execute again on the same table handle. It releases the resources
 acquired during the scan.
    * @returns DbRetVal
    */

    virtual DbRetVal close()=0;

    /**Retrieves the total space used for this table in bytes
    * @returns DbRetVal
    */
    virtual long spaceUsed()=0;

    /**Retrieves the total number of tuples present in this table
    * @returns DbRetVal
    */
    virtual long numTuples()=0;

    /**takes lock on the table
    * if bool shared flag is set, it will take shared lock, or else exclusive lock
    * @returns DbRetVal
    */
    virtual DbRetVal lock(bool shared)=0;

    /**releases the lock acquired on the table
    * @returns DbRetVal
    */
    virtual DbRetVal unlock()=0;

    /**sets the undo log flag. If this flag is unset then undo logs will not be generated
    * @returns DbRetVal
    */
    virtual DbRetVal setUndoLogging(bool flag)=0;

    virtual DbRetVal getFieldInfo(const char *fieldName, FieldInfo *&info)=0;
    virtual List getFieldNameList()=0;
    virtual char* getName()=0;
    virtual void printSQLIndexString()=0;

    virtual ~Table() { }
};
#endif
