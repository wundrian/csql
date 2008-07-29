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
#include <SqlLogStatement.h>

DbRetVal SqlGwStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    SqlGwConnection *conn = (SqlGwConnection*) con;
    //conn->connectCSqlIfNotConnected();
    //conn->connectAdapterIfNotConnected();
    stmtHdlr = NoHandler;
    if (innerStmt) rv = innerStmt->prepare(stmtstr);
    SqlLogStatement *stmt = (SqlLogStatement*) innerStmt;
    if (rv == OK) {
        if (!stmt->isCached) { 
            stmtHdlr = CSqlHandler;
            return rv;  
        }else {
            if (stmt->mode != TABLE_OSYNC) {
                stmtHdlr = CSqlHandler;
                return rv;
            }else {
                stmtHdlr = CSqlAndAdapterHandler;
            }
        }
    }

    //TODO::add procedures also in the below checking
    if (!strncasecmp(stmtstr,"INSERT", 6) == 0 &&
        !strncasecmp(stmtstr, "UPDATE", 6) ==0 &&
        !strncasecmp(stmtstr, "SELECT", 6) ==0 &&
        !strncasecmp(stmtstr, "DELETE", 6) ==0) return rv;

    //prepare failed. means table not there in csql->uncached table
    //or sql statement is complex and csql parser failed
    if (adapter) rv = adapter->prepare(stmtstr);
    if (rv == OK) { 
        printDebug(DM_Gateway, "Handled by csql %d\n", shouldCSqlHandle());
        if (!shouldCSqlHandle()) stmtHdlr = AdapterHandler;
        else stmtHdlr = CSqlAndAdapterHandler;
        printDebug(DM_Gateway, "Handled  %d\n", stmtHdlr);
    }
    else
        printError(ErrSysInit, "Both csql and adapter could not prepare\n");
    return rv;
}
bool SqlGwStatement::shouldAdapterHandle()
{
    if (stmtHdlr == AdapterHandler || 
        stmtHdlr == CSqlAndAdapterHandler) return true;
    return false;
}
bool SqlGwStatement::shouldCSqlHandle()
{
    SqlGwConnection *conn = (SqlGwConnection*) con;
    if (stmtHdlr == CSqlHandler || 
        stmtHdlr == CSqlAndAdapterHandler) return true;
    return false;
}
bool SqlGwStatement::isSelect()
{
    bool retValue;
    if (adapter && shouldAdapterHandle()) retValue =  adapter->isSelect();
    if (innerStmt && shouldCSqlHandle()) retValue =  innerStmt->isSelect();
    return retValue;
}

DbRetVal SqlGwStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    SqlGwConnection *conn = (SqlGwConnection*) con;
    if (adapter && shouldAdapterHandle()) rv = adapter->execute(rowsAffected);
    if (rv != OK) return rv;
    if (shouldAdapterHandle()) 
    {
        GwHandler hdlr = conn->getTxnHandler();
        if (hdlr == NoHandler) conn->setTxnHandler(AdapterHandler);
        if (hdlr == CSqlHandler) conn->setTxnHandler(CSqlAndAdapterHandler);
    }
    if (innerStmt && shouldCSqlHandle()) rv = innerStmt->execute(rowsAffected);
    if (shouldCSqlHandle()) 
    {
        GwHandler hdlr = conn->getTxnHandler();
        if (hdlr == NoHandler) conn->setTxnHandler(CSqlHandler);
        if (hdlr == AdapterHandler) conn->setTxnHandler(CSqlAndAdapterHandler);
    }
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
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) rv = adapter->bindField(pos, value);
    if (rv != OK) return rv;
    if (innerStmt && shouldCSqlHandle()) rv = innerStmt->bindField(pos,value);
    return rv;
}
void* SqlGwStatement::fetch()
{
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) return adapter->fetch();
    if (innerStmt && shouldCSqlHandle()) return innerStmt->fetch();
    return NULL;
}

void* SqlGwStatement::fetchAndPrint(bool SQL)
{
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) return adapter->fetchAndPrint(SQL);
    if (innerStmt && shouldCSqlHandle()) return innerStmt->fetchAndPrint(SQL);
    return NULL;
}

void* SqlGwStatement::next()
{
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) return adapter->next();
    if (innerStmt && shouldCSqlHandle()) return innerStmt->next();
    return NULL;
}

DbRetVal SqlGwStatement::close()
{
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) return adapter->close();
    if (innerStmt && shouldCSqlHandle()) return innerStmt->close();
    return OK;
}

void* SqlGwStatement::getFieldValuePtr( int pos )
{
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) return adapter->getFieldValuePtr(pos);
    if (innerStmt && shouldCSqlHandle()) return innerStmt->getFieldValuePtr(pos);
    return NULL;
}

int SqlGwStatement::noOfProjFields()
{
    //TODO::this will never be handled by both. check the flag for this
    if (innerStmt && shouldCSqlHandle()) return innerStmt->noOfProjFields();
    if (adapter && shouldAdapterHandle()) return adapter->noOfProjFields();
    return 0;
}

int SqlGwStatement::noOfParamFields()
{
    if (innerStmt && shouldCSqlHandle()) return innerStmt->noOfParamFields();
    if (adapter && shouldAdapterHandle()) return adapter->noOfParamFields();
    return 0;
}

DbRetVal SqlGwStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    if (innerStmt && shouldCSqlHandle()) return innerStmt->getProjFldInfo(projpos, fInfo);
    if (adapter && shouldAdapterHandle()) return adapter->getProjFldInfo(projpos, fInfo);
    return OK;
}

DbRetVal SqlGwStatement::getParamFldInfo (int parampos, FieldInfo *&fInfo)
{
    if (innerStmt && shouldCSqlHandle()) return innerStmt->getParamFldInfo(parampos, fInfo);
    if (adapter && shouldAdapterHandle()) return adapter->getParamFldInfo(parampos, fInfo);
    return OK;
}

DbRetVal SqlGwStatement::free()
{
    DbRetVal rv = OK;
    if (adapter && shouldAdapterHandle()) rv = adapter->free(); 
    if (innerStmt && shouldCSqlHandle()) rv = innerStmt->free();
    return rv;
}
void SqlGwStatement::setShortParam(int paramPos, short value)
{
    if (adapter && shouldAdapterHandle()) adapter->setShortParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setShortParam(paramPos,value);
    return;
}
void SqlGwStatement::setIntParam(int paramPos, int value)
{
    if (adapter && shouldAdapterHandle()) adapter->setIntParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setIntParam(paramPos,value);
    return;

}
void SqlGwStatement::setLongParam(int paramPos, long value)
{
    if (adapter && shouldAdapterHandle()) adapter->setLongParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setLongParam(paramPos,value);
    return;

}
void SqlGwStatement::setLongLongParam(int paramPos, long long value)
{
    if (adapter && shouldAdapterHandle()) adapter->setLongLongParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setLongLongParam(paramPos,value);
    return;
}
void SqlGwStatement::setByteIntParam(int paramPos, ByteInt value)
{
    if (adapter && shouldAdapterHandle()) adapter->setByteIntParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setByteIntParam(paramPos,value);
    return;
}
void SqlGwStatement::setFloatParam(int paramPos, float value)
{
    if (adapter && shouldAdapterHandle()) adapter->setFloatParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setFloatParam(paramPos,value);
    return;
}
void SqlGwStatement::setDoubleParam(int paramPos, double value)
{
    if (adapter && shouldAdapterHandle()) adapter->setDoubleParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setDoubleParam(paramPos,value);
    return;

}
void SqlGwStatement::setStringParam(int paramPos, char *value)
{
    if (adapter && shouldAdapterHandle()) adapter->setStringParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setStringParam(paramPos,value);
    return;
}
void SqlGwStatement::setDateParam(int paramPos, Date value)
{
    if (adapter && shouldAdapterHandle()) adapter->setDateParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setDateParam(paramPos,value);
    return;
}
void SqlGwStatement::setTimeParam(int paramPos, Time value)
{
    if (adapter && shouldAdapterHandle()) adapter->setTimeParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setTimeParam(paramPos,value);
    return;
}
void SqlGwStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    if (adapter && shouldAdapterHandle()) adapter->setTimeStampParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setTimeStampParam(paramPos,value);
    return;
}
void SqlGwStatement::setBinaryParam(int paramPos, void *value)
{
    if (adapter && shouldAdapterHandle()) adapter->setBinaryParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setBinaryParam(paramPos,value);
}

