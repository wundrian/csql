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
#include <SqlOdbcStatement.h>
//Important Note: MySQL Bug
//Bug #1382     SQLDescribeParam returns the same type information for any type
//as varchar of length 255. To avoid this, this class converts every data type
//to varchar by using appropriate conversion functions.

DbRetVal SqlOdbcStatement::executeDirect(char *stmtstr)
{
    DbRetVal rv = OK;
    int retValue = 0;
    SqlOdbcConnection *conn = (SqlOdbcConnection*)con;
    retValue=SQLAllocHandle (SQL_HANDLE_STMT, conn->dbHdl, &hstmt);
    if (retValue) return ErrBadCall;
    SQLCHAR* sstr= (SQLCHAR*)stmtstr;
    retValue=(*SqlOdbcConnection::ODBCFuncPtrs.SQLExecDirectPtr) (hstmt, sstr, SQL_NTS);
    if (retValue) return ErrBadCall;
    logFinest(Conf::logger, "executeDirect %s", stmtstr);
    return rv;
}     

DbRetVal SqlOdbcStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    if (innerStmt) rv = ErrBadCall;
    if (rv != OK) return rv;
    int retValue =0;
    isPrepared = false;
    isProcedureCallStmt = false;
    SqlOdbcConnection *conn = (SqlOdbcConnection*)con;
    //retValue=SQLAllocHandle (SQL_HANDLE_STMT, conn->dbHdl, &hstmt);
    retValue=(*SqlOdbcConnection::ODBCFuncPtrs.SQLAllocHandlePtr) (SQL_HANDLE_STMT, conn->dbHdl, &hstmt);
    if (retValue) return ErrBadCall;
    SQLCHAR* sstr= (SQLCHAR*)stmtstr;
    //retValue = SQLPrepare (hstmt, sstr, SQL_NTS);
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLPreparePtr) (hstmt, sstr, SQL_NTS);
    if (retValue) { 
    //    setErrorState(hstmt); 
        printError(ErrSysInternal, "Unable to prepare statement");
        return ErrSysInternal; 
    }
    isSelStmt=chechStmtType(stmtstr);
    isPrepared = true;
    if(strstr(stmtstr,"call ")!=NULL || strstr(stmtstr,"CALL ")!=NULL)
    {
        logFinest(Conf::logger, "Procedure call statement =true");
        isProcedureCallStmt=true;
    }
    short totalFields=0;
    tdbname = conn->getTrDbName();
    rv = resolveForBindField(hstmt);
    if(rv!=OK) return rv; 
    UWORD                   icol;
    SWORD                   colNameMax;
    SWORD                   scale;
    SWORD                   nullable;
    BindSqlField *bindField;
    //retValue = SQLNumParams (hstmt, &totalFields);
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLNumParamsPtr) (hstmt, &totalFields);
    if (retValue) return ErrBadCall;
    icol = 1; colNameMax = IDENTIFIER_LENGTH;
    SWORD                   cType=0;
    SQLULEN                 cLength=0;
    scale=0;
    logFinest(Conf::logger, "NumParams %d", totalFields);
    if(totalFields != 0)
    {
        paramlen =(SQLINTEGER *) malloc((totalFields+1)*sizeof(SQLINTEGER));
        for(int i=0;i<=totalFields;i++) { paramlen[i] = SQL_NTS; }
    }

    while (icol <= totalFields)
    {
        //retValue = SQLDescribeParam(hstmt, icol, &cType, &cLength,
        //Note: MySQL Bug
        //Bug #1382  	SQLDescribeParam returns the same type information

        bindField = new BindSqlField();
        bindField->type = typeString; 
        bindField->length = 512;
        bindField->value =  AllDataType::alloc(bindField->type, bindField->length);
        bindField->targetvalue = NULL;
        int fieldsize =0;
        switch(bindField->type)
        {
            case typeString:
                fieldsize = bindField->length;
                bindField->targetvalue = malloc(fieldsize);
                break;
            case typeDate:
                fieldsize = sizeof(DATE_STRUCT);
                bindField->targetvalue = malloc(sizeof(DATE_STRUCT));
                break;
            case typeTime:
                fieldsize = sizeof(TIME_STRUCT);
                bindField->targetvalue = malloc(sizeof(TIME_STRUCT));
                break;
            case typeTimeStamp:
                fieldsize = sizeof(TIMESTAMP_STRUCT);
                bindField->targetvalue = malloc(sizeof(TIMESTAMP_STRUCT));
                break;
            default:
                bindField->targetvalue = AllDataType::alloc(bindField->type, cLength);
                break;

        }
        //retValue = SQLBindParameter(hstmt, icol, SQL_PARAM_INPUT, 
        retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLBindParameterPtr)(hstmt, icol, SQL_PARAM_INPUT, 
                      AllDataType::convertToSQL_C_Type(bindField->type,tdbname), 
                       AllDataType::convertToSQLType(bindField->type), fieldsize, scale, bindField->targetvalue, 
                      fieldsize, &paramlen[icol]);
        if (retValue) return ErrBadCall;
        paramList.append(bindField);
        icol++;
    }
    //TODO::deallocate memory and remove elements from list in case of any
    //failure in any of the above ODBC functions
    logFinest(Conf::logger, "Statement prepared %s", stmtstr);
    return OK;
}

bool SqlOdbcStatement::isSelect()
{
    //TODO
    return isSelStmt;
}

DbRetVal SqlOdbcStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    if (!isPrepared) return ErrNotPrepared;
    int retValue=0;
    ListIterator iter = paramList.getIterator();
    BindSqlField *bindField = NULL;
    int col = 0;
    while (iter.hasElement())
    {
        bindField = (BindSqlField*)iter.nextElement();
        if(paramlen[++col] == SQL_NULL_DATA){
           ::free(bindField->targetvalue);
           bindField->targetvalue = NULL;
           continue;
        }
        switch(bindField->type)
        {
            case typeDate: {
                Date *dtCSQL = (Date*) bindField->value;
                DATE_STRUCT *dtTarget = (DATE_STRUCT*) bindField->targetvalue;
                dtTarget->year= dtCSQL->year();
                dtTarget->month= dtCSQL->month();
                dtTarget->day = dtCSQL->dayOfMonth();
                break;
            }
            case typeTime: {
                Time *dtCSQL = (Time*) bindField->value;
                TIME_STRUCT *dtTarget = (TIME_STRUCT*) bindField->targetvalue;
                dtTarget->hour = dtCSQL->hours();
                dtTarget->minute = dtCSQL->minutes();
                dtTarget->second = dtCSQL->seconds();
                break;
            }
            case typeTimeStamp: {
                TimeStamp *dtCSQL = (TimeStamp*) bindField->value;
                TIMESTAMP_STRUCT *dtTarget = (TIMESTAMP_STRUCT*) bindField->targetvalue;
                dtTarget->year= dtCSQL->year();
                dtTarget->month= dtCSQL->month();
                dtTarget->day = dtCSQL->dayOfMonth();
                dtTarget->hour = dtCSQL->hours();
                dtTarget->minute = dtCSQL->minutes();
                dtTarget->second = dtCSQL->seconds();
                break;
            }
            default: {
                AllDataType::cachecopyVal(bindField->targetvalue, bindField->value,
                                     bindField->type, bindField->length);
                break;
            }
        }
    }
    //int retValue = SQLExecute (hstmt);
    if(isProcedureCallStmt)
    {
        retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLExecutePtr) (hstmt);
        if ((retValue != SQL_SUCCESS) && (retValue != SQL_SUCCESS_WITH_INFO )) {
            return ErrBadCall;
        }
        rv = resolveForBindField(hstmt);
        if(rv!=OK) return rv;
        logFinest(Conf::logger, "Procedure executed");
    }else{
        retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLExecutePtr) (hstmt);
        if ((retValue != SQL_SUCCESS) && (retValue != SQL_SUCCESS_WITH_INFO )) { 
        //    setErrorState(hstmt); 
           return ErrBadCall;
         }
         logFinest(Conf::logger, "Statement executed");
    }
    //retValue=SQLRowCount(hstmt,(SQLINTEGER*)&rowsAffected);
    retValue= (*SqlOdbcConnection::ODBCFuncPtrs.SQLRowCountPtr)(hstmt,(SQLINTEGER*)&rowsAffected);
    if(isSelStmt) rowsAffected = 0;
    return rv;
}

DbRetVal SqlOdbcStatement::bindParam(int pos, void* value)
{
    DbRetVal rv = OK;
    printError(ErrWarning, "Deprecated. Use setParamXXX instead\n");
    return rv;
}

DbRetVal SqlOdbcStatement::bindField(int pos, void* value)
{
    if (!isPrepared) return OK;
    BindSqlProjectField *bindField = (BindSqlProjectField*)bindList.get(pos);
    if (NULL == bindField) 
    {
        printError(ErrBadArg, "Could not get the projection list. Should be called only for SELECT statement");
        return ErrBadArg;
    }
    bindField->value = value;
    return OK;
}

//void SqlOdbcStatement::setNullInfo(Table *table)
void SqlOdbcStatement::setNullInfo(AbsSqlStatement *stmt)
{
    int fldpos=0;
    while(fldpos < totalFld)
    {
        if(len[++fldpos] == SQL_NULL_DATA)
        {
            stmt->setNull(fldpos);
        }
    }
}

void* SqlOdbcStatement::fetch()
{
    if (!isPrepared) return NULL;
    //int retValue = SQLFetch (hstmt);
    int retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLFetchPtr) (hstmt);
    if (retValue) return NULL;
    ListIterator iter = bindList.getIterator();
    BindSqlProjectField *bindField = NULL;
    void *ptrToFirstField = NULL;
    int icol=0;
    while (iter.hasElement())
    {
        bindField = (BindSqlProjectField*)iter.nextElement();
        if (ptrToFirstField == NULL) ptrToFirstField=bindField->value;
        if(len[++icol] == SQL_NULL_DATA) 
        { 
            if(bindField->value) AllDataType::memoryset(bindField->value,bindField->type);
            continue; 
        }
        if( isSelStmt && NULL == bindField->value )
        {
            if (ptrToFirstField == NULL) ptrToFirstField=bindField->targetvalue;
            continue;
        }
        switch(bindField->type)
        {
            case typeDate: {
                Date *dtCSQL = (Date*) bindField->value;
                DATE_STRUCT *dtTarget = (DATE_STRUCT*) bindField->targetvalue;
                dtCSQL->set(dtTarget->year,dtTarget->month,dtTarget->day);
                break;
            }
            case typeTime: {
                Time *dtCSQL = (Time*) bindField->value;
                TIME_STRUCT *dtTarget = (TIME_STRUCT*) bindField->targetvalue;
                dtCSQL->set(dtTarget->hour,dtTarget->minute,dtTarget->second);
                break;
            }
            case typeTimeStamp: {
                TimeStamp *dtCSQL = (TimeStamp*) bindField->value;
                TIMESTAMP_STRUCT *dtTarget = (TIMESTAMP_STRUCT*) bindField->targetvalue;
                dtCSQL->setDate(dtTarget->year,dtTarget->month,dtTarget->day);
                dtCSQL->setTime(dtTarget->hour,dtTarget->minute,
                                dtTarget->second, 0);//dtTarget->fraction);
                break;
            }
            default: {
                AllDataType::cachecopyVal(bindField->value, bindField->targetvalue,
                                     bindField->type, bindField->length,tdbname);
                break;
            }
        } 
    }
    return ptrToFirstField;
}

void* SqlOdbcStatement::fetch(DbRetVal &rv)
{
    if (!isPrepared) return NULL;
    //int retValue = SQLFetch (hstmt);
    int retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLFetchPtr) (hstmt);
    if (retValue) { rv = OK; return NULL; }
    ListIterator iter = bindList.getIterator();
    BindSqlProjectField *bindField = NULL;
    void *ptrToFirstField = NULL;
    int icol=0;
    while (iter.hasElement())
    {
        bindField = (BindSqlProjectField*)iter.nextElement();
        if (ptrToFirstField == NULL) ptrToFirstField=bindField->value;
        if(len[++icol] == SQL_NULL_DATA) 
        { 
            if(bindField->value) AllDataType::memoryset(bindField->value,bindField->type);
            continue; 
        }
        if( isSelStmt && NULL == bindField->value )
        {
            if (ptrToFirstField == NULL) ptrToFirstField=bindField->targetvalue;
            continue;
        }
        switch(bindField->type)
        {
            case typeDate: {
                Date *dtCSQL = (Date*) bindField->value;
                DATE_STRUCT *dtTarget = (DATE_STRUCT*) bindField->targetvalue;
                dtCSQL->set(dtTarget->year,dtTarget->month,dtTarget->day);
                break;
            }
            case typeTime: {
                Time *dtCSQL = (Time*) bindField->value;
                TIME_STRUCT *dtTarget = (TIME_STRUCT*) bindField->targetvalue;
                dtCSQL->set(dtTarget->hour,dtTarget->minute,dtTarget->second);
                break;
            }
            case typeTimeStamp: {
                TimeStamp *dtCSQL = (TimeStamp*) bindField->value;
                TIMESTAMP_STRUCT *dtTarget = (TIMESTAMP_STRUCT*) bindField->targetvalue;
                dtCSQL->setDate(dtTarget->year,dtTarget->month,dtTarget->day);
                dtCSQL->setTime(dtTarget->hour,dtTarget->minute,
                                dtTarget->second, 0);// dtTarget->fraction);
                break;
            }
            default: {
                AllDataType::cachecopyVal(bindField->value, bindField->targetvalue, bindField->type, bindField->length, tdbname);
                break;
            }
        } 
    }
    return ptrToFirstField;
}

void* SqlOdbcStatement::fetchAndPrint(bool SQL)
{
    if (!isPrepared) return NULL;
    //int retValue = SQLFetch (hstmt);
    int retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLFetchPtr) (hstmt);
    if (retValue) return NULL;
    ListIterator iter = bindList.getIterator();
    BindSqlProjectField *bindField = NULL;
    void *ptrToFirstField = NULL;
    int icol=1;
    while (iter.hasElement())
    {

        bindField = (BindSqlProjectField*)iter.nextElement();
        if (ptrToFirstField == NULL) ptrToFirstField=bindField->targetvalue;
        if(len[icol++] == SQL_NULL_DATA) 
        { 
            printf("NULL"); 
            continue;
        }
        switch(bindField->type)
        {
            case typeDate: {
                Date dtCSQL;
                DATE_STRUCT *dtTarget = (DATE_STRUCT*) bindField->targetvalue;
                dtCSQL.set(dtTarget->year,dtTarget->month,dtTarget->day);
                AllDataType::printVal(&dtCSQL, bindField->type, bindField->length);
                break;
            }
            case typeTime: {
                Time dtCSQL;
                TIME_STRUCT *dtTarget = (TIME_STRUCT*) bindField->targetvalue;
                dtCSQL.set(dtTarget->hour,dtTarget->minute,dtTarget->second);
                AllDataType::printVal(&dtCSQL, bindField->type, bindField->length);
                break;
            }
            case typeTimeStamp: {
                TimeStamp dtCSQL;
                TIMESTAMP_STRUCT *dtTarget = (TIMESTAMP_STRUCT*) bindField->targetvalue;
                dtCSQL.setDate(dtTarget->year,dtTarget->month,dtTarget->day);
                dtCSQL.setTime(dtTarget->hour,dtTarget->minute,
                                dtTarget->second, 0);//dtTarget->fraction);
                AllDataType::printVal(&dtCSQL, bindField->type, bindField->length);
                break;
            }
            default: {
                AllDataType::printVal(bindField->targetvalue,
                                     bindField->type, bindField->length,tdbname);
                break;
            }
        }
        printf("\t");
    }
    return ptrToFirstField;
}

void* SqlOdbcStatement::next()
{
    return fetch();
}

DbRetVal SqlOdbcStatement::close()
{
    if (!isPrepared) return OK;
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLCloseCursorPtr)(hstmt);
    logFinest(Conf::logger, "CloseCursor");
    return OK;
}
bool SqlOdbcStatement::chechStmtType(char *buf)
{
    char c;
    while(1)
    {
        c=*buf;
        if(c !=' ') break;
        buf++;
    }
    if (strncasecmp (buf, "SELECT", 6) == 0)  { return true;}
    return false;
}
void* SqlOdbcStatement::getFieldValuePtr( int pos )
{

   ListIterator biter = bindList.getIterator();
   BindSqlProjectField *elem = NULL;
    int count =0;
    while (biter.hasElement())
    {
        elem = (BindSqlProjectField*) biter.nextElement();
        if (count == pos)
        {
            if(elem->value == NULL)
             {
                 switch(elem->type)
                 {
                      case typeDate: {
                          Date *dtCSQL=(Date *) elem->jdbcBindValue;
                          DATE_STRUCT *dtTarget = (DATE_STRUCT*) elem->targetvalue;
                          dtCSQL->set(dtTarget->year,dtTarget->month,dtTarget->day);
                          return dtCSQL;
                      }
                      case typeTime: {
                         Time *dtCSQL = (Time *) elem->jdbcBindValue;
                          TIME_STRUCT *dtTarget = (TIME_STRUCT*) elem->targetvalue;
                          dtCSQL->set(dtTarget->hour,dtTarget->minute,dtTarget->second);
                          return dtCSQL;
                      }
                      case typeTimeStamp: {
                          TimeStamp *dtCSQL= (TimeStamp *) elem->jdbcBindValue;
                          TIMESTAMP_STRUCT *dtTarget = (TIMESTAMP_STRUCT*) elem->targetvalue;
                          dtCSQL->setDate(dtTarget->year,dtTarget->month,dtTarget->day);
                          dtCSQL->setTime(dtTarget->hour,dtTarget->minute,dtTarget->second, 0);//dtTarget->fraction);
                          return dtCSQL;
                      }
                }
             }
             return elem->targetvalue;
        }
        count++;
    }
    return NULL;

}
void SqlOdbcStatement::getProjFieldType(int *data)
{
    ListIterator biter = bindList.getIterator();
    BindSqlProjectField *elem = NULL;
    int i = 1;
    while (biter.hasElement())
    {
        elem = (BindSqlProjectField*) biter.nextElement();
        if((tdbname == postgres) && typeLongLong == elem->type)
            data[i++] = typeString;
        else 
            data[i++] = elem->type;
    }
}

void* SqlOdbcStatement::getFieldValuePtr( char *name )
{
    ListIterator biter = bindList.getIterator();
    BindSqlProjectField *elem = NULL;
    int count =0;
    while (biter.hasElement())
    {
        elem = (BindSqlProjectField*) biter.nextElement();
        if ( strcpy(elem->fName,name) == 0 )
        {
            return elem->targetvalue;
        }
    }
    return NULL;

}
int SqlOdbcStatement::noOfProjFields()
{
    if (!isPrepared) return 0;
    return bindList.size();
}

int SqlOdbcStatement::noOfParamFields()
{
    if (!isPrepared) return 0;
    return paramList.size();
}

DbRetVal SqlOdbcStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    ListIterator biter = bindList.getIterator();
    BindSqlProjectField *elem = NULL;
    int count =0;
    while (biter.hasElement())
    {
        elem = (BindSqlProjectField*) biter.nextElement();
        if (count == projpos-1) 
        {
            strcpy(fInfo->fldName, elem->fName);
            fInfo->length = elem->length;
            fInfo->type =elem->type;
            return OK;
        }
        count++;
    }
    return ErrNotFound;
}

DbRetVal SqlOdbcStatement::getParamFldInfo (int parampos, FieldInfo *&fInfo)
{
    ListIterator biter = paramList.getIterator();
    BindSqlField *elem = NULL;
    int count =0;
    while (biter.hasElement())
    {
        elem = (BindSqlField*) biter.nextElement();
        if (count == parampos-1) 
        {
            fInfo->length = elem->length;
            fInfo->type =elem->type;
            return OK;
        }
        count++;
    }
    return ErrNotFound;
}

DbRetVal SqlOdbcStatement::free()
{
    if(!isPrepared) return OK;
    ListIterator biter = bindList.getIterator();
    BindSqlProjectField *elem = NULL;
    while (biter.hasElement())
    {
        elem = (BindSqlProjectField*) biter.nextElement();
        if(elem->targetvalue)
            ::free(elem->targetvalue); 
        if(elem->jdbcBindValue)
            ::free(elem->jdbcBindValue);
        delete elem;
    }
    bindList.reset();
    ListIterator piter = paramList.getIterator();
    BindSqlField *bindField = NULL;
    while (piter.hasElement())
    {
        bindField = (BindSqlField*) piter.nextElement();
        ::free(bindField->value);
        ::free(bindField->targetvalue);
        delete bindField; 
    }
    paramList.reset();
    if(len){ ::free(len); len = NULL;}
    if(paramlen) {::free(paramlen); paramlen = NULL;}
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLFreeHandlePtr)(SQL_HANDLE_STMT, hstmt);
    isPrepared = false;
    isProcedureCallStmt = false;
    logFinest(Conf::logger, "Statement Freed");
    return OK;
}
void SqlOdbcStatement::setShortParam(int paramPos, short value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    AllDataType::convertToString(bindField->value, &value, typeShort, 0,tdbname);
    return;
}
void SqlOdbcStatement::setIntParam(int paramPos, int value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
     //Note: MySQL Bug
     //Bug #1382     SQLDescribeParam returns the same type information, varchar
    AllDataType::convertToString(bindField->value, &value, typeInt,0,tdbname);
    return;

}
void SqlOdbcStatement::setLongParam(int paramPos, long value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
     //Note: MySQL Bug
     //Bug #1382     SQLDescribeParam returns the same type information, varchar
    AllDataType::convertToString(bindField->value, &value, typeLong,0,tdbname);
    return;

}
void SqlOdbcStatement::setLongLongParam(int paramPos, long long value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    AllDataType::convertToString(bindField->value, &value, typeLongLong,0,tdbname);
    return;
}
void SqlOdbcStatement::setByteIntParam(int paramPos, ByteInt value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    AllDataType::convertToString(bindField->value, &value, typeByteInt,0,tdbname);
    return;
}
void SqlOdbcStatement::setFloatParam(int paramPos, float value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    AllDataType::convertToString(bindField->value, &value, typeFloat,0, tdbname);
    return;
}
void SqlOdbcStatement::setDoubleParam(int paramPos, double value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    AllDataType::convertToString(bindField->value, &value, typeDouble,0,tdbname);
    return;
}
void SqlOdbcStatement::setStringParam(int paramPos, char *value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeString) return;
    char *dest = (char*)bindField->value;
    strncpy(dest, value, bindField->length);
    dest[ bindField->length - 1] ='\0';
    return;
}
void SqlOdbcStatement::setDateParam(int paramPos, Date value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    AllDataType::convertToString(bindField->value, &value, typeDate,0,tdbname);
    return;
}
void SqlOdbcStatement::setTimeParam(int paramPos, Time value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    AllDataType::convertToString(bindField->value, &value, typeTime,0,tdbname);
    return;
}
void SqlOdbcStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*) paramList.get(paramPos);
    AllDataType::convertToString(bindField->value, &value, typeTimeStamp,0, tdbname);
    return;
}
void SqlOdbcStatement::setBinaryParam(int paramPos, void *value, int length)
{
    if (!isPrepared) return;
    BindSqlField *bindField = (BindSqlField*) paramList.get(paramPos);
    AllDataType::convertToString(bindField->value, value, typeBinary, bindField->length,tdbname);
    return;
}

void SqlOdbcStatement::getPrimaryKeyFieldName(char *tablename, char *pkfieldname)
{
    if (pkfieldname == NULL) return;
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;
    int retValue =0;
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    SqlOdbcConnection *conn = (SqlOdbcConnection*)con;
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLAllocHandlePtr) (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
    }
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLSetEnvAttrPtr)(henv, SQL_ATTR_ODBC_VERSION,(void *) SQL_OV_ODBC3, 0);
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLAllocHandlePtr) (SQL_HANDLE_DBC, henv, &hdbc);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
    }
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLDriverConnectPtr)(hdbc, NULL, (SQLCHAR*)conn->dsn, SQL_NTS, outstr, sizeof(outstr), &outstrlen,SQL_DRIVER_NOPROMPT);
    if (SQL_SUCCEEDED(retValue)) {
        printDebug(DM_Gateway, "Connected to target database using dsn = %s\n", conn->dsn);
    } else {
        printError(ErrSysInit, "Failed to connect to target database\n");
    }
    retValue=(*SqlOdbcConnection::ODBCFuncPtrs.SQLAllocHandlePtr) (SQL_HANDLE_STMT, hdbc, &hstmt);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
    }
    char columnname[IDENTIFIER_LENGTH];
    retValue=(*SqlOdbcConnection::ODBCFuncPtrs.SQLPrimaryKeysPtr)(hstmt, NULL, SQL_NTS, NULL, SQL_NTS, (SQLCHAR*) tablename, SQL_NTS);
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLBindColPtr)(hstmt, 4, SQL_C_CHAR,columnname, 129,NULL);
    bool isPkExists=false;
    if((*SqlOdbcConnection::ODBCFuncPtrs.SQLFetchPtr)( hstmt ) == SQL_SUCCESS)
    {
        Util::str_tolower(columnname);
        strcpy(pkfieldname, columnname);
        isPkExists = true;
    }
    tdbname = conn->getTrDbName();
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLFreeHandlePtr)(SQL_HANDLE_STMT, hstmt);
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLDisconnectPtr)(hdbc);
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLFreeHandlePtr)(SQL_HANDLE_DBC, hdbc);
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLFreeHandlePtr)(SQL_HANDLE_ENV, henv);
    return;
}

bool SqlOdbcStatement::isFldNull(int pos)
{
    if( len[pos] == SQL_NULL_DATA )
        return true;
    else
        return false;
}
bool SqlOdbcStatement::isFldNull(char *name)
{
    ListIterator iter = bindList.getIterator();
    BindSqlProjectField *bindField = NULL;
    int pos=1;
    while (iter.hasElement())
    {
        bindField = (BindSqlProjectField*)iter.nextElement();
        if(strcmp(name,bindField->fName)==0)
        {
            break;
        }
        pos++;
    }
    if( len[pos] == SQL_NULL_DATA )
        return true;
    else
        return false;
}

void SqlOdbcStatement::setNull(int pos)
{
    paramlen[pos] = SQL_NULL_DATA ;
}

bool SqlOdbcStatement::isTableExists( char *name)
{

    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;
    int retValue =0;
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    SqlOdbcConnection *conn = (SqlOdbcConnection*)con;
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLAllocHandlePtr) (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
    }

    (*SqlOdbcConnection::ODBCFuncPtrs.SQLSetEnvAttrPtr)(henv, SQL_ATTR_ODBC_VERSION,(void *) SQL_OV_ODBC3, 0);
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLAllocHandlePtr) (SQL_HANDLE_DBC, henv, &hdbc);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
    }
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLDriverConnectPtr)(hdbc, NULL, (SQLCHAR*)conn->dsn, SQL_NTS, outstr, sizeof(outstr), &outstrlen,SQL_DRIVER_NOPROMPT);
    if (SQL_SUCCEEDED(retValue)) {
        printDebug(DM_Gateway, "Connected to target database using dsn = %s\n", conn->dsn);
    } else {
        printError(ErrSysInit, "Failed to connect to target database\n");
    }

    retValue=(*SqlOdbcConnection::ODBCFuncPtrs.SQLAllocHandlePtr) (SQL_HANDLE_STMT, hdbc, &hstmt);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
    }
    char tablename[IDENTIFIER_LENGTH];
    //retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLTablesPtr)(hstmt, (SQLCHAR*)"test", SQL_NTS, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"TABLE", SQL_NTS );
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLTablesPtr)(hstmt, NULL, SQL_NTS, NULL, SQL_NTS, NULL, SQL_NTS, NULL, SQL_NTS );
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLBindColPtr)(hstmt,3,SQL_C_CHAR,tablename,sizeof(tablename),NULL);
    while(SQL_SUCCEEDED(retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLFetchPtr)(hstmt)))
    {
        if(strcmp(tablename,name)==0){  
            (*SqlOdbcConnection::ODBCFuncPtrs.SQLFreeHandlePtr)(SQL_HANDLE_STMT, hstmt);
            (*SqlOdbcConnection::ODBCFuncPtrs.SQLDisconnectPtr)(hdbc);
            (*SqlOdbcConnection::ODBCFuncPtrs.SQLFreeHandlePtr)(SQL_HANDLE_DBC, hdbc);
            (*SqlOdbcConnection::ODBCFuncPtrs.SQLFreeHandlePtr)(SQL_HANDLE_ENV, henv);
            return true; 
        }
    }
    
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLFreeHandlePtr)(SQL_HANDLE_STMT, hstmt);
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLDisconnectPtr)(hdbc);
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLFreeHandlePtr)(SQL_HANDLE_DBC, hdbc);
    (*SqlOdbcConnection::ODBCFuncPtrs.SQLFreeHandlePtr)(SQL_HANDLE_ENV, henv);
    return false;
}
void SqlOdbcStatement::setErrorState(SQLHSTMT hStmt)
{
    SQLINTEGER   i = 0;
    SQLINTEGER   native;
    SQLCHAR      state[ 7 ];
    SQLCHAR      text[256];
    SQLSMALLINT  len;
    SQLRETURN    ret;
    ret = (*SqlOdbcConnection::ODBCFuncPtrs.SQLGetDiagRecPtr)(SQL_HANDLE_STMT, hStmt, ++i,
                                   state, &native, text, sizeof(text), &len );

    if (SQL_SUCCEEDED(ret)){
        printf("%s:%ld:%ld:%s\n", state, i, native, text);
        strcpy(errState,(char*)state);
    }
}

DbRetVal SqlOdbcStatement::resolveForBindField(SQLHSTMT hstmt)
{
    short totalFields=0;
    int retValue = 0;
    retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLNumResultColsPtr) (hstmt, &totalFields);
    if (retValue){   return ErrBadCall;  }
    BindSqlProjectField *bindProjField = NULL;
    UWORD                   icol;
    UCHAR                   colName[IDENTIFIER_LENGTH];
    SWORD                   colNameMax;
    SWORD                   nameLength;
    SWORD                   colType;
    SQLULEN                 colLength;
    SWORD                   scale;
    SWORD                   nullable;
    icol = 1; colNameMax = IDENTIFIER_LENGTH;
    if(totalFields != 0)
    {
        if(isProcedureCallStmt) isSelStmt = true;
        len = (SQLINTEGER *)malloc((totalFields+1)*sizeof(SQLINTEGER));
        for(int i=0;i<=totalFields;i++) { len[i] = SQL_NTS ;}
    }
    while (icol <= totalFields)
    {
        retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLDescribeColPtr)(hstmt, icol, colName, colNameMax,
                   &nameLength, &colType, &colLength,
                   &scale, &nullable);
        if (retValue) return ErrBadCall;
        bindProjField = new BindSqlProjectField();
        strcpy(bindProjField->fName, (char*)colName);
        bindProjField->type = AllDataType::convertFromSQLType(colType,colLength,scale,tdbname);
        bindProjField->length = AllDataType::size(bindProjField->type, colLength+1);
        bindProjField->value = NULL;
        bindProjField->targetvalue = NULL;
        int fieldsize =0;
        if(tdbname==postgres && -5 == colType) {
            bindProjField->targetvalue = AllDataType::alloc(typeString, 128);
            retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLBindColPtr)(hstmt, icol,
                              AllDataType::convertToSQLType(typeString),
                              bindProjField->targetvalue, 128, &len[icol]);
        }else{
             switch(bindProjField->type)
             {
                case typeString:
                    fieldsize = colLength+1;
                    bindProjField->targetvalue = malloc(fieldsize);
                    break;
                case typeDate:
                    fieldsize = sizeof(DATE_STRUCT);
                    bindProjField->targetvalue = malloc(sizeof(DATE_STRUCT));
                    bindProjField->jdbcBindValue = AllDataType::alloc(typeDate);
                    break;
                case typeTime:
                    fieldsize = sizeof(TIME_STRUCT);
                    bindProjField->targetvalue = malloc(sizeof(TIME_STRUCT));
                    bindProjField->jdbcBindValue = AllDataType::alloc(typeTime);
                    break;
                case typeTimeStamp:
                    fieldsize = sizeof(TIMESTAMP_STRUCT);
                    bindProjField->targetvalue = malloc(sizeof(TIMESTAMP_STRUCT));
                    bindProjField->jdbcBindValue = AllDataType::alloc(typeTimeStamp);
                    break;
                default:
                    bindProjField->targetvalue = AllDataType::alloc(bindProjField->type, bindProjField->length);
            }
        retValue = (*SqlOdbcConnection::ODBCFuncPtrs.SQLBindColPtr)(hstmt, icol,
                              AllDataType::convertToSQL_C_Type(bindProjField->type,tdbname),
                              bindProjField->targetvalue, fieldsize, &len[icol]);
        }
        if (retValue) return ErrBadCall;
        bindList.append(bindProjField);
        icol++;
    }
    totalFld = totalFields;
    return OK;
}

