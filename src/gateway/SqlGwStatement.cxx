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
#include <SqlGwStatement.h>

DbRetVal SqlGwStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    SqlGwConnection *conn = (SqlGwConnection*) con;
    conn->connectCSqlIfNotConnected();
    conn->connectAdapterIfNotConnected();

    if (innerStmt) rv = innerStmt->prepare(stmtstr);
    if (rv == OK) { isAdapterHanding= false; return rv; }
    //prepare failed. means table not there in sql->uncached table
    //or sql statement is complex and csql parser failed
    if (adapter) rv = adapter->prepare(stmtstr);
    if (rv == OK) { 
        printError(ErrWarning, "Handled by adapter\n");
        isAdapterHanding = true;
    }
    else
        printError(ErrSysInit, "Both csql and adapter could not prepare\n");
    return rv;
}

bool SqlGwStatement::isSelect()
{
    if (isAdapterHanding && adapter) return adapter->isSelect();
    if (innerStmt) return innerStmt->isSelect();
    return false;
}

DbRetVal SqlGwStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    if (isAdapterHanding && adapter) return adapter->execute(rowsAffected);
    if (innerStmt) rv = innerStmt->execute(rowsAffected);
    return rv;
}

DbRetVal SqlGwStatement::bindParam(int pos, void* value)
{
    DbRetVal rv = OK;
    printError(ErrWarning, "Deprecated and does not replicate or cache");
    return rv;
}

DbRetVal SqlGwStatement::bindField(int pos, void* value)
{
    DbRetVal rv = OK;
    if (isAdapterHanding && adapter) return adapter->bindField(pos, value);
    if (innerStmt) rv = innerStmt->bindField(pos,value);
    if (rv != OK) return rv;
    return rv;
}
void* SqlGwStatement::fetch()
{
    if (isAdapterHanding && adapter) return adapter->fetch();
    if (innerStmt) return innerStmt->fetch();
    return NULL;
}

void* SqlGwStatement::fetchAndPrint()
{
    if (isAdapterHanding && adapter) return adapter->fetchAndPrint();
    if (innerStmt) return innerStmt->fetchAndPrint();
    return NULL;
}

void* SqlGwStatement::next()
{
    if (isAdapterHanding && adapter) return adapter->next();
    if (innerStmt) return innerStmt->next();
    return NULL;
}

DbRetVal SqlGwStatement::close()
{
    if (isAdapterHanding && adapter) return adapter->close();
    if (innerStmt) return innerStmt->close();
    return OK;
}

void* SqlGwStatement::getFieldValuePtr( int pos )
{
    if (isAdapterHanding && adapter) return adapter->getFieldValuePtr(pos);
    if (innerStmt) return innerStmt->getFieldValuePtr(pos);
    return NULL;
}

int SqlGwStatement::noOfProjFields()
{
    if (isAdapterHanding && adapter) return adapter->noOfProjFields();
    if (innerStmt) return innerStmt->noOfProjFields();
    return 0;
}

int SqlGwStatement::noOfParamFields()
{
    if (isAdapterHanding && adapter) return adapter->noOfParamFields();
    if (innerStmt) return innerStmt->noOfParamFields();
    return 0;
}

DbRetVal SqlGwStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    if (isAdapterHanding && adapter) return adapter->getProjFldInfo(projpos, fInfo);
    if (innerStmt) return innerStmt->getProjFldInfo(projpos, fInfo);
    return OK;
}

DbRetVal SqlGwStatement::getParamFldInfo (int parampos, FieldInfo *&fInfo)
{
    if (isAdapterHanding && adapter) return adapter->getParamFldInfo(parampos, fInfo);
    if (innerStmt) return innerStmt->getParamFldInfo(parampos, fInfo);
    return OK;
}

DbRetVal SqlGwStatement::free()
{
    DbRetVal rv = OK;
    if (isAdapterHanding && adapter) 
    { 
        isAdapterHanding = false;
        return adapter->free(); 
    }
    if (innerStmt) rv = innerStmt->free();
    return rv;
}
void SqlGwStatement::setShortParam(int paramPos, short value)
{
    if (isAdapterHanding && adapter) return adapter->setShortParam(paramPos, value);
    if (innerStmt) innerStmt->setShortParam(paramPos,value);
    return;
}
void SqlGwStatement::setIntParam(int paramPos, int value)
{
    if (isAdapterHanding && adapter) return adapter->setIntParam(paramPos, value);
    if (innerStmt) innerStmt->setIntParam(paramPos,value);
    return;

}
void SqlGwStatement::setLongParam(int paramPos, long value)
{
    if (isAdapterHanding && adapter) return adapter->setLongParam(paramPos, value);
    if (innerStmt) innerStmt->setLongParam(paramPos,value);
    return;

}
void SqlGwStatement::setLongLongParam(int paramPos, long long value)
{
    if (isAdapterHanding && adapter) return adapter->setLongLongParam(paramPos, value);
    if (innerStmt) innerStmt->setLongLongParam(paramPos,value);
    return;
}
void SqlGwStatement::setByteIntParam(int paramPos, ByteInt value)
{
    if (isAdapterHanding && adapter) return adapter->setByteIntParam(paramPos, value);
    if (innerStmt) innerStmt->setByteIntParam(paramPos,value);
    return;
}
void SqlGwStatement::setFloatParam(int paramPos, float value)
{
    if (isAdapterHanding && adapter) return adapter->setFloatParam(paramPos, value);
    if (innerStmt) innerStmt->setFloatParam(paramPos,value);
    return;
}
void SqlGwStatement::setDoubleParam(int paramPos, double value)
{
    if (isAdapterHanding && adapter) return adapter->setDoubleParam(paramPos, value);
    if (innerStmt) innerStmt->setDoubleParam(paramPos,value);
    return;

}
void SqlGwStatement::setStringParam(int paramPos, char *value)
{
    if (isAdapterHanding && adapter) return adapter->setStringParam(paramPos, value);
    if (innerStmt) innerStmt->setStringParam(paramPos,value);
    return;
}
void SqlGwStatement::setDateParam(int paramPos, Date value)
{
    if (isAdapterHanding && adapter) return adapter->setDateParam(paramPos, value);
    if (innerStmt) innerStmt->setDateParam(paramPos,value);
    return;
}
void SqlGwStatement::setTimeParam(int paramPos, Time value)
{
    if (isAdapterHanding && adapter) return adapter->setTimeParam(paramPos, value);
    if (innerStmt) innerStmt->setTimeParam(paramPos,value);
    return;
}
void SqlGwStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    if (isAdapterHanding && adapter) return adapter->setTimeStampParam(paramPos, value);
    if (innerStmt) innerStmt->setTimeStampParam(paramPos,value);
    return;
}
