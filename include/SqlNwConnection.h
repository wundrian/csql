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
#ifndef SQLNWCONNECTION_H
#define SQLNWCONNECTION_H
#include<CSql.h>
#include<Network.h>
#include<AbsSqlConnection.h>
#include<SqlFactory.h>

/**
* @class SqlNwConnection
*
*/
class SqlNwConnection : public AbsSqlConnection
{
    Connection dummyConn;
    NetworkClient *nwClient;
    public:
    IsolationLevel prevIsoLevel;
    SqlNwConnection(){nwClient = NULL; innerConn = NULL; }

    //Note::forced to implement this as it is pure virtual in base class
    Connection& getConnObject(){  return dummyConn; }
    NetworkClient* getNetworkClient() { return nwClient; }
    DbRetVal connect (char *user, char * pass);

    DbRetVal disconnect();

    DbRetVal commit();

    DbRetVal rollback();

    DbRetVal beginTrans (IsolationLevel isoLevel, TransSyncMode mode = OSYNC);

    DbRetVal send(NetworkPacketType type, char *buffer, size_t len)
    { return  nwClient->send(type, buffer, len); }
    DbRetVal receive() { return nwClient->receive(); }
    friend class SqlFactory;
};

#endif
