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
#include "Statement.h"
#include <SqlStatement.h>

char *lexInput;
extern ParsedData *parsedData;
int yyparse ();
void yyrestart (FILE *input_file  );
extern FILE *yyin;
SqlStatement::SqlStatement()
{
    con = NULL;
    stmt = NULL;
}
void SqlStatement::setConnection(SqlConnection *conn)
{
    con = conn;
}

DbRetVal SqlStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    lexInput = stmtstr;
    parsedData = &pData;
    int rc = yyparse();
    if (rc != 0) 
    {
        free();
        parsedData = NULL;
        yyrestart(yyin);
        return ErrSyntaxError;
    }
    stmt = StatementFactory::getStatement(parsedData);
    stmt->setDbMgr(con->getConnObject().getDatabaseManager());
    rv = stmt->resolve();
    if (rv != OK)
    {
        free();
        parsedData = NULL;
        yyrestart(yyin);
        return rv;
    }
    parsedData = NULL;
    yyrestart(yyin);
    return OK;
}

bool SqlStatement::isSelect()
{
    if (pData.getStmtType() == SelectStatement) return true;
    return false;
}

DbRetVal SqlStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    rv = stmt->execute(rowsAffected);
    return rv;
}

void* SqlStatement::fetch()
{
    if (pData.getStmtType() != SelectStatement) return NULL;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return selStmt->fetch();
}

DbRetVal SqlStatement::bindParam(int pos, void* value)
{
    DbRetVal rv = OK;
    rv = stmt->setParam(pos, value);
    return rv;
}

DbRetVal SqlStatement::bindField(int pos, void* value)
{
    DbRetVal rv = OK;
    if (pData.getStmtType() != SelectStatement) return ErrBadCall;
    SelStatement *selStmt = (SelStatement*) stmt; 
    rv = selStmt->setBindField(pos, value);
    return rv;
}

int SqlStatement::noOfProjFields()
{
    if (pData.getStmtType() != SelectStatement) return 0;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return selStmt->noOfProjFields();
}

int SqlStatement::noOfParamFields()
{
    if (pData.getStmtType() != SelectStatement) return 0;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return selStmt->noOfParamFields();
}

DbRetVal SqlStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    DbRetVal rv = OK;
    if (pData.getStmtType() != SelectStatement) return ErrBadCall;
    SelStatement *selStmt = (SelStatement*) stmt; 
    rv = selStmt->getProjFldInfo(projpos, fInfo);
    return rv;
}

DbRetVal SqlStatement::getParamFldInfo (int parampos, FieldInfo *&fInfo)
{
    DbRetVal rv = OK;
    if (pData.getStmtType() != SelectStatement) return ErrBadCall;
    SelStatement *selStmt = (SelStatement*) stmt; 
    rv = selStmt->getParamFldInfo(parampos, fInfo);
    return rv;
}

DbRetVal SqlStatement::free()
{
    delete stmt;
    stmt = NULL;
    pData.reset();
}

void SqlStatement::setShortParam(int paramPos, short value)
{
    stmt->setShortParam(paramPos, value);
}
void SqlStatement::setIntParam(int paramPos, int value)
{
    stmt->setIntParam(paramPos, value);
}
void SqlStatement::setLongParam(int paramPos, long value)
{
    stmt->setLongParam(paramPos, value);
}
void SqlStatement::setLongLongParam(int paramPos, long long value)
{
    stmt->setLongLongParam(paramPos, value);
}
void SqlStatement::setByteIntParam(int paramPos, ByteInt value)
{
    stmt->setByteIntParam(paramPos, value);
}
void SqlStatement::setFloatParam(int paramPos, float value)
{
    stmt->setFloatParam(paramPos, value);
}
void SqlStatement::setDoubleParam(int paramPos, double value)
{
    stmt->setDoubleParam(paramPos, value);
}
void SqlStatement::setStringParam(int paramPos, char *value)
{
    stmt->setStringParam(paramPos, value);
}
void SqlStatement::setDateParam(int paramPos, Date value)
{
    stmt->setDateParam(paramPos, value);
}
void SqlStatement::setTimeParam(int paramPos, Time value)
{
    stmt->setTimeParam(paramPos, value);
}
void SqlStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    stmt->setTimeStampParam(paramPos, value);
}

