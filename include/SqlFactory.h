/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef SQLFACTORY_H
#define SQLFACTORY_H

#include<AbsSqlConnection.h>
#include<AbsSqlStatement.h>

enum SqlApiImplType
{
    CSql =1,
    CSqlAdapter,
    CSqlGateway,
    CSqlNetwork,
    CSqlNetworkAdapter,
    CSqlNetworkGateway,
    CSqlLog,
    CSqlDirect,
    CSqlUnknown
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
