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
Statement* StatementFactory::getStatement(ParsedData *data)
{
    Statement *stmt;
    switch(data->getStmtType())
    {
        case InsertStatement:
            stmt = new InsStatement();
            break;
        case SelectStatement:
            stmt = new SelStatement();
            break;
        case UpdateStatement:
            stmt = new UpdStatement();
            break;
        case DeleteStatement:
            stmt = new DelStatement();
            break;
        case CreateTableStatement:
            stmt = new CreateTblStatement();
            break;
        case DropTableStatement:
            stmt = new DropTblStatement();
            break;
        case CreateIndexStatement:
            stmt = new CreateIdxStatement();
            break;
        case DropIndexStatement:
            stmt = new DropIdxStatement();
            break;
    }
    stmt->setParsedData(data);
    return stmt;
}
