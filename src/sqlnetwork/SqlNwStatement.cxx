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
#include <SqlNwStatement.h>

DbRetVal SqlNwStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    SqlNwConnection *conn = (SqlNwConnection*)con;
    SqlPacketPrepare *pkt = new SqlPacketPrepare();
    pkt->stmtString = stmtstr;
    pkt->syncMode = OSYNC;
    pkt->stmtLength = strlen(stmtstr) + 1;
    pkt->marshall(); 
    rv = conn->send(SQL_NW_PKT_PREPARE, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return rv;
    }
    rv = conn->receive();
    if(rv != OK) return rv;
    printf("received ack\n");
    return rv;
}

bool SqlNwStatement::isSelect()
{
    //TODO
    return false;
}

DbRetVal SqlNwStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    if (!isPrepared) return ErrNotPrepared;
    //TODO
    return rv;
}

DbRetVal SqlNwStatement::bindParam(int pos, void* value)
{
    DbRetVal rv = OK;
    printError(ErrWarning, "Deprecated. Use setParamXXX instead\n");
    return rv;
}

DbRetVal SqlNwStatement::bindField(int pos, void* value)
{
    if (!isPrepared) return OK;
    //TODO
    return OK;
}
void* SqlNwStatement::fetch()
{
    if (!isPrepared) return NULL;
    void *ptrToFirstField = NULL;
    //TODO
    return ptrToFirstField;
}

void* SqlNwStatement::fetchAndPrint(bool SQL)
{
    if (!isPrepared) return NULL;
    void *ptrToFirstField = NULL;
    //TODO
    return ptrToFirstField;
}

void* SqlNwStatement::next()
{
    return fetch();
}

DbRetVal SqlNwStatement::close()
{
    if (!isPrepared) return OK;
    //TODO
    return OK;
}

void* SqlNwStatement::getFieldValuePtr( int pos )
{
    return NULL;
}

int SqlNwStatement::noOfProjFields()
{
    if (!isPrepared) return 0;
    //TODO
    return 0;
}

int SqlNwStatement::noOfParamFields()
{
    if (!isPrepared) return 0;
    //TODO
    return 0;
}

DbRetVal SqlNwStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    //TODO
    return ErrNotFound;
}

DbRetVal SqlNwStatement::getParamFldInfo (int parampos, FieldInfo *&fInfo)
{
    //TODO
    return ErrNotFound;
}

DbRetVal SqlNwStatement::free()
{
    //TODO
    return OK;
}
void SqlNwStatement::setShortParam(int paramPos, short value)
{
    if (!isPrepared) return ;
    //TODO
    return;
}
void SqlNwStatement::setIntParam(int paramPos, int value)
{
    if (!isPrepared) return ;
    //TODO
    return;

}
void SqlNwStatement::setLongParam(int paramPos, long value)
{
    if (!isPrepared) return ;
    //TODO
    return;

}
void SqlNwStatement::setLongLongParam(int paramPos, long long value)
{
    if (!isPrepared) return ;
    //TODO
    return;
}
void SqlNwStatement::setByteIntParam(int paramPos, ByteInt value)
{
    if (!isPrepared) return ;
    //TODO
}
void SqlNwStatement::setFloatParam(int paramPos, float value)
{
    if (!isPrepared) return ;
    //TODO
}
void SqlNwStatement::setDoubleParam(int paramPos, double value)
{
    if (!isPrepared) return ;
    //TODO

}
void SqlNwStatement::setStringParam(int paramPos, char *value)
{
    if (!isPrepared) return ;
    //TODO
    return;
}
void SqlNwStatement::setDateParam(int paramPos, Date value)
{
    if (!isPrepared) return ;
    //TODO

}
void SqlNwStatement::setTimeParam(int paramPos, Time value)
{
    if (!isPrepared) return ;
    //TODO

}
void SqlNwStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    if (!isPrepared) return ;
    //TODO
}
void SqlNwStatement::setBinaryParam(int paramPos, void *value)
{
    if (!isPrepared) return;
    //TODO
}

void SqlNwStatement::getPrimaryKeyFieldName(char *tablename, char *pkfieldname)
{
    if (pkfieldname == NULL) return;
    //TODO
    return;
}
