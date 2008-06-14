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
#ifndef SQLFACTORY_H
#define SQLFACTORY_H
#include<CSql.h>

#include<AbsSqlConnection.h>
#include<AbsSqlStatement.h>

enum SqlApiImplType
{
    CSql =1,
    CSqlAdapter =2,
    CSqlGateway =3,
    CSqlLog= 4
};
/**
* @class SqlFactory
*
* @brief Factory class to create appropriate implementation of SQL API
* 
*/
class SqlFactory
{
    public:

    /** creates appropriate implementation of AbsSqlConnection based on implFlag passed
    *   @param implFlag 1->SqlConnection, 2->?
    *   @return AbsSqlConnection
    */
    static AbsSqlConnection* createConnection (SqlApiImplType implFlag);

    /** creates appropriate implementation of AbsSqlStatement based on implFlag passed
    *   @param implFlag 1->SqlConnection, 2->?
    *   @return AbsSqlStatement
    */
    static AbsSqlStatement* createStatement (SqlApiImplType implFlag);
};

#endif
