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
#ifndef SQLLOGSTATEMENT_H
#define SQLLOGSTATEMENT_H
#include <AbsSqlStatement.h>
#include <SqlLogConnection.h>
#include <SqlFactory.h>
#include <CSql.h>
class TableSyncMode{
    public:
    char tableName[IDENTIFIER_LENGTH];
    DataSyncMode mode;
};
class SqlLogStatement: public AbsSqlStatement
{
    public:
    SqlLogStatement(){innerStmt = NULL; con = NULL; needLog= false; sid=0; }

    void setConnection(AbsSqlConnection *conn)
    {
        if (innerStmt) innerStmt->setConnection(conn->getInnerConnection());
        con = conn;
    }

    bool isNonSelectDML(char *stmtstr);
    DbRetVal  getTableSyncMode();
    DbRetVal prepare(char *stmt);

    DbRetVal execute(int &rowsAffect);
    DbRetVal bindParam(int pos, void*);

    DbRetVal bindField(int pos, void* val);

    void* fetch();
    void* fetchAndPrint();
    void* next();
    DbRetVal close();
    int noOfProjFields();

    void* getFieldValuePtr( int pos );

    DbRetVal free();

    int noOfParamFields();

    DbRetVal getProjFldInfo(int projPos, FieldInfo *&info);

    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);

    void setShortParam(int paramPos, short value);
    void setIntParam(int paramPos, int value);
    void setLongParam(int paramPos, long value);
    void setLongLongParam(int paramPos, long long value);
    void setByteIntParam(int paramPos, ByteInt value);
    void setFloatParam(int paramPos, float value);
    void setDoubleParam(int paramPos, double value);
    void setStringParam(int paramPos, char *value);
    void setDateParam(int paramPos, Date value);
    void setTimeParam(int paramPos, Time value);
    void setTimeStampParam(int paramPos, TimeStamp value);
    bool isSelect();

    private:
    DbRetVal populateSyncModeList();

    bool needLog;
    DataSyncMode syncMode;
    int sid; //statement id
    List paramList;

    static List syncModeList;
    static UniqueID stmtUID;
    friend class SqlFactory;
};

#endif
