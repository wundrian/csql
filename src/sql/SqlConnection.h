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
#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H
#include<CSql.h>
class SqlConnection
{
    Connection conn;
    public:

    // Connection handling.
    DbRetVal connect (char *user, char * pass) 
        { return conn.open(user, pass); }
    DbRetVal disconnect () { return conn.close(); }

    // Transaction handling.
    DbRetVal commit() { return conn.commit(); }
    DbRetVal rollback() { return conn.rollback(); }
    DbRetVal beginTrans (IsolationLevel isoLevel = READ_COMMITTED) 
        { return conn.startTransaction(isoLevel); }


    Connection& getConnObject(){  return conn; }
};

#endif
