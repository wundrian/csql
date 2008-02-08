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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef ABSSQLSTATEMENT_H
#define ABSSQLSTATEMENT_H
//#include <SqlConnection.h>
//#include "Statement.h"
//#include<CSql.h>
#include<AbsSqlConnection.h>
//#include <SqlStatement.h>
class Statement;
class ParsedData;

/**
* @class AbsSqlStatement
*
* @brief Handle to the sql statement.
* It is used to execute queries and return the values from the database<br>
* Sql Statement is fed to the prepare method first and then it should be executed. <br/>
* Functionality: <br/>
*     1.Input values for insert statement <br/>
*     2.Iterator for retrieving rows from the table <br/>
*     3.Parameter support for performance.<br/>
* <br/>
* @author Prabakaran Thirumalai
*/
class AbsSqlStatement
{
    protected:
    AbsSqlStatement *innerStmt;
    AbsSqlConnection *con;
    public:
    void setInnerStatement(AbsSqlStatement *stmt) { innerStmt = stmt; }
    /** sets connection handle to be used for subsequent operations
    *   @param con SqlConnection*
    */
    virtual void setConnection(AbsSqlConnection *conn) { con = conn; }

    /** compiles the sql statement. It calls the parser and tokenizes the statement 
    * into logical plan. This method sets the statement string which needs to be executed.
    * free method needs to be called, if application wants to use the same handle to compile
    * another sql statement.
    * @param stmt sql statement string
    * @returns DbRetVal
    */
    virtual DbRetVal prepare(char *stmt) = 0;

    /** executes the sql statement. For insert, update, delete queries execute performs the
    * required operation on the table. 
    * For Select queries, application should call execute before they start fetching
    * the values from the table.This starts scan on the table.
    * @param rowsAffect number of rows affected by the sql statement
    * @returns DbRetVal
    */
    virtual DbRetVal execute(int &rowsAffect) =0;

    /**fetches the next tuple from the result of the execution of sql select query.
    * execute should be called before calling this method. Application buffer should be 
    * binded to get the tuple values.
    * @returns void* NULL if there is no tuple.
    */
    virtual void* fetch() = 0;
    

    /**fetches the next tuple from the result of the execution of sql select query 
    * and prints it to stdout.
    * execute should be called before calling this method.
    * @returns void* NULL if there is no tuple.
    */
    virtual void* fetchAndPrint() = 0;


    /** binds application buffer to the specified parameter position in the sql statement. 
    * This method should be called for all the parameters in the sql statement.
    * Parameters shall be specified for predicate for select, update, delete statements.
    * Parameters shall be specified for field list value in SET of update statements. 
    * If value is not set for all parameters, execute will return error.
    * <br/>
    *   @param pos  position of the parameter in the statement
    *   @param val  address of the application buffer. Memory should be allocated by
    *               the application before binding the buffer.
    */
    virtual DbRetVal bindParam(int pos, void*) = 0;

    /** binds application buffer to the specified field position of the projection list 
    *  in the select query or for fields in the insert statement. 
    *  This method should be called for select queries, insert, update statements.
    *  Before executing select queries, required fields must be binded first.
    *  Before executing insert statement, required fields must be binded first.
    *  Before executing update statement, required fields to be updated must be 
    *  binded first.
    * <br/>
    *   @param pos  position in the projection list
    *   @param val  address of the application buffer. Memory should be allocated by
    *               the application before binding the buffer.
    */
    virtual DbRetVal bindField(int pos, void* val) = 0;

    /** same as fetch, but does not populate bindFieldValues
    * @returns address void*
    */
    virtual void* next() = 0;

    /**Closes the iterator and makes the statement ready for another execution
    * @returns DbRetVal
    */
    virtual DbRetVal close() = 0;

    /** get FieldValue->value ptr after fetch is done.
    * @returns address void*
    */
    virtual void* getFieldValuePtr( int pos )  = 0;

    /**Frees all the resources held for the sql statement. Needs to be called before calling prepare again on the same statement handle.
    * @returns DbRetVal
    */
    virtual DbRetVal free() = 0;

    /**Retrieves the total number of projection fields in the statement
    * @returns int no of projection fields
    */
    virtual int noOfProjFields() = 0;

    /**Retrieves the total number of parameters in the statement
    * @returns int no of parameters
    */
    virtual int noOfParamFields() = 0;

    /**Retrieves the field info for the required projection field position in statement
    * @param projPos int - projection field position
    * @param info FieldInfo*& - OUT parameter
    * @returns DbRetVal
    */
    virtual DbRetVal getProjFldInfo(int projPos, FieldInfo *&info) = 0;

    /**Retrieves the field info for the required parameter position in statement
    * @param projPos int - parameter position
    * @param info FieldInfo*& - OUT parameter
    * @returns DbRetVal
    */
    virtual DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info) = 0;

    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value short - value to be set 
    */
    virtual void setShortParam(int paramPos, short value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value int - value to be set 
    */
    virtual void setIntParam(int paramPos, int value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value long - value to be set 
    */
    virtual void setLongParam(int paramPos, long value)  =0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value long long - value to be set 
    */
    virtual void setLongLongParam(int paramPos, long long value)  =0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value ByteInt - value to be set 
    */
    virtual void setByteIntParam(int paramPos, ByteInt value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value float - value to be set 
    */
    virtual void setFloatParam(int paramPos, float value)  = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value double - value to be set 
    */
    virtual void setDoubleParam(int paramPos, double value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value char* - value to be set 
    */
    virtual void setStringParam(int paramPos, char *value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value Date - value to be set 
    */
    virtual void setDateParam(int paramPos, Date value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value Time - value to be set 
    */
    virtual void setTimeParam(int paramPos, Time value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value TimeStamp - value to be set 
    */
    virtual void setTimeStampParam(int paramPos, TimeStamp value)  = 0;

    /**Returns whether the statement prepared is select statement
    * @return bool true if it is select stmt, false otherwise
    */
    virtual bool isSelect() = 0;
    
    virtual ~AbsSqlStatement(){}
};

#endif
