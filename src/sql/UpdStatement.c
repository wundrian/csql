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
  ***************************************************************************/
#include "Statement.h"
#include <Info.h>

DbRetVal UpdStatement::execute(int &rowsAffected)
{
}
DbRetVal UpdStatement::setParam(int paramNo, void *value)
{
}
DbRetVal UpdStatement::resolve()
{
    if (dbMgr == NULL) return ErrNoConnection;
    //check whether the table exists
    table = dbMgr->openTable(parsedData->getTableName());
    if (table == NULL) 
    {
        printError(ErrNotExists, "Unable to open the table:Table not exists");
        return ErrNotExists;
    }
    return OK;
}
    

UpdStatement::~UpdStatement()
{
}
