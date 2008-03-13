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
#include <SqlGwConnection.h>
#include <CSql.h>
#include <Network.h>

DbRetVal SqlGwConnection::connect (char *user, char * pass)
{
    isCSqlConnected = false;
    isAdapterConnected = false;
    strcpy(username, user);
    strcpy(password, pass);
    DbRetVal rv = OK;
    if (innerConn) rv = innerConn->connect(user,pass);
    if (rv == OK) isCSqlConnected = true;
    if (adapter) rv = adapter->connect(user,pass);
    if (rv == OK) isAdapterConnected = true;
    if (!isAdapterConnected && !isCSqlConnected) return ErrNoConnection;
    return OK;
    
}
DbRetVal SqlGwConnection::disconnect()
{
    DbRetVal rv = OK;
    if (innerConn && isCSqlConnected) rv =innerConn->disconnect();
    if (rv != OK) return rv;
    if (adapter && isAdapterConnected) rv = adapter->disconnect();
    isCSqlConnected = false;
    isAdapterConnected = false;
    return rv;
}
DbRetVal SqlGwConnection::beginTrans(IsolationLevel isoLevel, TransSyncMode smode)
{
    DbRetVal rv = OK;
    if (innerConn && isCSqlConnected) rv =  innerConn->beginTrans(isoLevel);
    if (rv != OK) return rv;
    if (adapter && isAdapterConnected) rv = adapter->beginTrans(isoLevel);
    if (!isAdapterConnected && !isCSqlConnected) return ErrNoConnection;
    //printf("passed mode is %d\n", smode);
    mode = smode;
    txnHdlr = CSqlHandler;
    return rv;
}
DbRetVal SqlGwConnection::commit()
{
    DbRetVal rv = OK;
    if (innerConn && isCSqlConnected)
        //(txnHdlr == CSqlHandler || txnHdlr == CSqlAndAdapterHandler))
        rv = innerConn->commit();
    if (rv != OK) return rv;
    if (adapter && 
        (txnHdlr == AdapterHandler || txnHdlr == CSqlAndAdapterHandler))
        rv = adapter->commit();
    if (!isAdapterConnected && !isCSqlConnected) return ErrNoConnection;
    return rv;
}
DbRetVal SqlGwConnection::rollback()
{
    DbRetVal rv = OK;
    if (innerConn && isCSqlConnected)
        //(txnHdlr == CSqlHandler || txnHdlr == CSqlAndAdapterHandler))
        rv =  innerConn->rollback();
    if (rv != OK) return rv;
    if (adapter && isAdapterConnected &&
        (txnHdlr == AdapterHandler || txnHdlr == CSqlAndAdapterHandler))
        rv = adapter->rollback();
    if (!isAdapterConnected && !isCSqlConnected) return ErrNoConnection;
    return rv;
}
DbRetVal SqlGwConnection::connectCSqlIfNotConnected()
{
    if (!isCSqlConnected) { 
        DbRetVal rv = innerConn->connect(username, password);
        if (rv != OK) return rv;
        isCSqlConnected = true;
    }
    return OK;
}
DbRetVal SqlGwConnection::connectAdapterIfNotConnected()
{
    if (!isAdapterConnected) { 
        DbRetVal rv = adapter->connect(username, password);
        if (rv != OK) return rv;
        isAdapterConnected = true;
    }
    return OK;
}
