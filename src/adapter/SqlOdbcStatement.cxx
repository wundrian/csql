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

DbRetVal SqlOdbcStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    if (innerStmt) rv = ErrBadCall;
    if (rv != OK) return rv;
    int retValue;
    isPrepared = false;
    SqlOdbcConnection *conn = (SqlOdbcConnection*)con;
    retValue=SQLAllocHandle (SQL_HANDLE_STMT, conn->dbHdl, &hstmt);
    if (retValue) return ErrBadCall;
    retValue = SQLPrepare (hstmt, (unsigned char *) stmtstr, SQL_NTS);
    //printf("retvalue from prepare is %d %s\n", retValue, stmtstr);
    if (retValue) return ErrBadCall;
    isPrepared = true;
    short totalFields=0;
    retValue = SQLNumResultCols (hstmt, &totalFields);
    //printf("Total project fields %d\n", totalFields);
    if (retValue) return ErrBadCall;
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
    while (icol <= totalFields)
    {
        retValue = SQLDescribeCol(hstmt, icol, colName, colNameMax,
                   &nameLength, &colType, &colLength,
                   &scale, &nullable);
        if (retValue) return ErrBadCall;
        
        bindProjField = new BindSqlProjectField();
        strncpy(bindProjField->fName, (char*)colName, IDENTIFIER_LENGTH);
        bindProjField->fName[IDENTIFIER_LENGTH] = '\0';
        bindProjField->type = AllDataType::convertFromSQLType(colType);
        bindProjField->length = colLength;
        bindProjField->value = NULL;
        bindProjField->targetvalue = NULL;
        int fieldsize =0;
        switch(bindProjField->type)
        {
            case typeString:
                fieldsize = colLength;
                bindProjField->targetvalue = malloc(fieldsize); 
                break;
            case typeDate:
                fieldsize = sizeof(DATE_STRUCT);
                bindProjField->targetvalue = malloc(sizeof(DATE_STRUCT));
                break;
            case typeTime:
                fieldsize = sizeof(TIME_STRUCT);
                bindProjField->targetvalue = malloc(sizeof(TIME_STRUCT));
                break;
            case typeTimeStamp:
                fieldsize = sizeof(TIMESTAMP_STRUCT);
                bindProjField->targetvalue = malloc(sizeof(TIMESTAMP_STRUCT));
                break;
            default:
                bindProjField->targetvalue = AllDataType::alloc(bindProjField->type, bindProjField->length);
        }
        retValue = SQLBindCol(hstmt, icol, 
                              AllDataType::convertToSQLType(bindProjField->type),
                              bindProjField->targetvalue, fieldsize, NULL);
        if (retValue) return ErrBadCall; 
        bindList.append(bindProjField);
        //printf("appending to bindlist %d\n", icol);
        icol++;
       
    }
    totalFields =0;
    BindSqlField *bindField;
    retValue = SQLNumParams (hstmt, &totalFields);
    if (retValue) return ErrBadCall;
    //printf("SQLNUMParams returned %d\n", totalFields);
    icol = 1; colNameMax = IDENTIFIER_LENGTH;
    SWORD                   cType=0;
    SQLULEN                 cLength=0;
    while (icol <= totalFields)
    {
        retValue = SQLDescribeParam(hstmt, icol, &cType, &cLength,
                   &scale, &nullable);
        //Note: MySQL Bug
        //Bug #1382  	SQLDescribeParam returns the same type information

        if (retValue) return ErrBadCall;
        
        bindField = new BindSqlField();
        bindField->type = AllDataType::convertFromSQLType(cType);
        bindField->length = cLength;
        bindField->value =  AllDataType::alloc(bindField->type, cLength);
        bindField->targetvalue = NULL;
        int fieldsize =0;
        switch(bindField->type)
        {
            case typeString:
                fieldsize = cLength;
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
        retValue = SQLBindParameter(hstmt, icol, SQL_PARAM_INPUT, 
                      AllDataType::convertToSQL_C_Type(bindField->type), 
                      cType, fieldsize, scale, bindField->targetvalue, 
                      fieldsize, NULL);
        if (retValue) return ErrBadCall;
        //printf("adding to param list\n");
        paramList.append(bindField);
        icol++;
    }
    //TODO::deallocate memory and remove elements from list in case of any
    //failure in any of the above ODBC functions
    return OK;
}

bool SqlOdbcStatement::isSelect()
{
    //TODO
    return false;
}

DbRetVal SqlOdbcStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    if (!isPrepared) return OK;
    //printf("Adapter calling execute\n");
    ListIterator iter = paramList.getIterator();
    BindSqlField *bindField = NULL;
    while (iter.hasElement())
    {
        bindField = (BindSqlField*)iter.nextElement();
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
                AllDataType::copyVal(bindField->targetvalue, bindField->value,
                                     bindField->type, bindField->length);
                break;
            }
        }
    }
    int retValue = SQLExecute (hstmt);
    printf("EXECUTE returned %d\n", retValue);
    if (retValue) return ErrBadCall;
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
    bindField->value = value;
    return OK;
}
void* SqlOdbcStatement::fetch()
{
    if (!isPrepared) return NULL;
    int retValue = SQLFetch (hstmt);
    //printf("SQLFETCH return value %d\n", retValue);
    if (retValue) return NULL;
    ListIterator iter = bindList.getIterator();
    BindSqlProjectField *bindField = NULL;
    void *ptrToFirstField = NULL;
    while (iter.hasElement())
    {
        bindField = (BindSqlProjectField*)iter.nextElement();
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
                                dtTarget->second, dtTarget->fraction);
                break;
            }
            default: {
                AllDataType::copyVal(bindField->value, bindField->targetvalue,
                                     bindField->type, bindField->length);
                break;
            }
        } 
        if (ptrToFirstField == NULL) ptrToFirstField=bindField->value;
    }
    //printf("ptrToFirstField is %x\n", ptrToFirstField);
    return ptrToFirstField;
}

void* SqlOdbcStatement::fetchAndPrint(bool SQL)
{
    if (!isPrepared) return NULL;
    int retValue = SQLFetch (hstmt);
    if (retValue) return NULL;
    ListIterator iter = bindList.getIterator();
    BindSqlProjectField *bindField = NULL;
    void *ptrToFirstField = NULL;
    while (iter.hasElement())
    {
        bindField = (BindSqlProjectField*)iter.nextElement();
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
                                dtTarget->second, dtTarget->fraction);
                AllDataType::printVal(&dtCSQL, bindField->type, bindField->length);
                break;
            }
            default: {
                AllDataType::printVal(bindField->targetvalue,
                                     bindField->type, bindField->length);
                break;
            }
        }
        if (ptrToFirstField == NULL) ptrToFirstField=bindField->targetvalue;
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
    SQLCloseCursor(hstmt);
    return OK;
}

void* SqlOdbcStatement::getFieldValuePtr( int pos )
{
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
        if (count == projpos) 
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
        if (count == parampos) 
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
    isPrepared = false;
    ListIterator biter = bindList.getIterator();
    BindSqlProjectField *elem = NULL;
    while (biter.hasElement())
    {
        elem = (BindSqlProjectField*) biter.nextElement();
        ::free(elem->targetvalue); 
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

    SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
    return OK;
}
void SqlOdbcStatement::setShortParam(int paramPos, short value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeShort) return;
    *(short*)(bindField->value) = value;
    return;
}
void SqlOdbcStatement::setIntParam(int paramPos, int value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    /*if (bindField->type != typeInt) return;
    *(int*)(bindField->value) = value;
    */

     //Note: MySQL Bug
     //Bug #1382     SQLDescribeParam returns the same type information, varchar
    AllDataType::convertToString(bindField->value, &value, typeInt);

    return;

}
void SqlOdbcStatement::setLongParam(int paramPos, long value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    //if (bindField->type != typeLong) return;
    //*(long*)(bindField->value) = value;
     //Note: MySQL Bug
     //Bug #1382     SQLDescribeParam returns the same type information, varchar
    AllDataType::convertToString(bindField->value, &value, typeLong);
    return;

}
void SqlOdbcStatement::setLongLongParam(int paramPos, long long value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    //if (bindField->type != typeLongLong) return;
    //*(long long*)(bindField->value) = value;
    AllDataType::convertToString(bindField->value, &value, typeLongLong);
    return;
}
void SqlOdbcStatement::setByteIntParam(int paramPos, ByteInt value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    //if (bindField->type != typeByteInt) return;
    //*(char*)(bindField->value) = value;
    AllDataType::convertToString(bindField->value, &value, typeByteInt);

}
void SqlOdbcStatement::setFloatParam(int paramPos, float value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    //if (bindField->type != typeFloat) return;
    //*(float*)(bindField->value) = value;
    AllDataType::convertToString(bindField->value, &value, typeFloat);
}
void SqlOdbcStatement::setDoubleParam(int paramPos, double value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    //if (bindField->type != typeDouble) return;
    //*(double*)(bindField->value) = value;
    AllDataType::convertToString(bindField->value, &value, typeDouble);

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
    //if (bindField->type != typeDate) return;
    //*(Date*)(bindField->value) = value;
    AllDataType::convertToString(bindField->value, &value, typeDate);
    //printf("Param value contains %s\n", bindField->value);

}
void SqlOdbcStatement::setTimeParam(int paramPos, Time value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    //if (bindField->type != typeTime) return;
    //*(Time*)(bindField->value) = value;
    AllDataType::convertToString(bindField->value, &value, typeTime);

}
void SqlOdbcStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    if (!isPrepared) return ;
    BindSqlField *bindField = (BindSqlField*) paramList.get(paramPos);
    //if (bindField->type != typeTimeStamp) return;
    //*(TimeStamp*)(bindField->value) = value;
    AllDataType::convertToString(bindField->value, &value, typeTimeStamp);
    //printf("Param value contains %s\n", bindField->value);
}
