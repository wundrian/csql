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
#include <SqlNwConnection.h>
#include <CSql.h>

DbRetVal SqlNwConnection::connect (char *user, char * pass)
{
    DbRetVal rv = OK;
    //TODO
    return rv;
    
}
DbRetVal SqlNwConnection::disconnect()
{
    DbRetVal rv = OK;
    //TODO
    return rv;
}
DbRetVal SqlNwConnection::beginTrans(IsolationLevel isoLevel, TransSyncMode mode)
{
    if (prevIsoLevel == isoLevel) return OK;
    DbRetVal rv = OK;
    //TODO
    return rv;
}
DbRetVal SqlNwConnection::commit()
{
    DbRetVal rv = OK;
    //TODO
    return rv;
}
DbRetVal SqlNwConnection::rollback()
{
    DbRetVal rv = OK;
    //TODO
    return rv;
}
