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
#include <dmllex.h>

char *lexInput;
extern ParsedData *parsedData;

int yyparse ();

SqlStatement::SqlStatement()
{
    sqlCon = NULL;
    stmt = NULL;
    isPrepd = false;
}
void SqlStatement::setConnection(AbsSqlConnection *conn)
{
    sqlCon = (SqlConnection*)conn;
    con = conn;

}
void SqlStatement::setSqlConnection(SqlConnection *conn)
{
    sqlCon = conn;
}

DbRetVal SqlStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    if (! sqlCon->isConnectionOpen()) {
        printError(ErrNotOpen, "Connection not open");
        return ErrNotOpen;
    }
    if(isPrepared()) free();
    lexInput = stmtstr;
    parsedData = &pData;
    yy_scan_string( stmtstr );
    int rc = yyparse();
    if (rc != 0) 
    {
        free();
        parsedData = NULL;
        yyrestart(yyin);
        return ErrSyntaxError;
    }
    stmt = StatementFactory::getStatement(parsedData);
    stmt->setDbMgr(sqlCon->getConnObject().getDatabaseManager());
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
    isPrepd = true;
    return OK;
}

char*  SqlStatement::getTableName()
{
    return pData.getTableName();
}

bool SqlStatement::isSelect()
{
    if (pData.getStmtType() == SelectStatement) return true;
    return false;
}

bool SqlStatement::isPrepared() { return isPrepd; }

DbRetVal SqlStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    if (! sqlCon->isConnectionOpen()) {
        printError(ErrNotOpen, "Connection not open");
        return ErrNotOpen;
    }
    if (! isPrepared()) {
        printError(ErrNotPrepared, "Statement Not Prepared");
        return ErrNotPrepared;
    }
    rv = stmt->execute(rowsAffected);
    return rv;
}

void* SqlStatement::fetch()
{
    if (! sqlCon->isConnectionOpen()) {
        printError(ErrNotOpen, "Connection not open");
        return NULL;
    }
    if (! isPrepared()) {
        printError(ErrNotPrepared, "Statement Not Prepared");
        return NULL;
    }
    if (pData.getStmtType() != SelectStatement) return NULL;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return selStmt->fetch();
}

void* SqlStatement::fetch(DbRetVal &rv)
{
    if (! sqlCon->isConnectionOpen()) {
        printError(ErrNotOpen, "Connection not open");
        return NULL;
    }
    if (! isPrepared()) {
        printError(ErrNotPrepared, "Statement Not Prepared");
        return NULL;
    }
    if (pData.getStmtType() != SelectStatement) return NULL;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return selStmt->fetch(rv);
}

void* SqlStatement::fetchAndPrint(bool SQL)
{
    if (! sqlCon->isConnectionOpen()) {
        printError(ErrNotOpen, "Connection not open");
        return NULL;
    }
    if (! isPrepared()) {
        printError(ErrNotPrepared, "Statement Not Prepared");
        return NULL;
    }
    if (pData.getStmtType() != SelectStatement) return NULL;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return selStmt->fetchAndPrint(SQL);
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
void* SqlStatement::next()
{
    if (pData.getStmtType() != SelectStatement) return 0;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return( (void*) selStmt->next() );
}

bool SqlStatement::isFldNull(int pos)
{
    if (pData.getStmtType() != SelectStatement) return 0;
    SelStatement *selStmt = (SelStatement*) stmt;
    return (selStmt->isFldNull(pos));
}
DbRetVal SqlStatement::close()
{
    if (pData.getStmtType() != SelectStatement) return OK;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return selStmt->close();
}

void* SqlStatement::getParamValuePtr( int pos )
{
    //if (pData.getStmtType() != SelectStatement) return 0;
    DmlStatement *dmlStmt = (DmlStatement*) stmt;
    return( (void*) dmlStmt->getParamValuePtr( pos ) );
}

char* SqlStatement::getFieldName( int pos )
{
    if (pData.getStmtType() != SelectStatement) return 0;
    SelStatement *selStmt = (SelStatement*) stmt;
    return( (char*) selStmt->getFieldName( pos ) );
}

DataType SqlStatement::getFieldType( int pos )
{
    if (pData.getStmtType() != SelectStatement) return typeUnknown;
    SelStatement *selStmt = (SelStatement*) stmt;
    return( (DataType) selStmt->getFieldType( pos ) );
}
int SqlStatement::getFieldLength( int pos )
{
    if (pData.getStmtType() != SelectStatement) return 0;
    SelStatement *selStmt = (SelStatement*) stmt;
    return( (int) selStmt->getFieldLength( pos ) );
}

void* SqlStatement::getFieldValuePtr( int pos )
{
    if (pData.getStmtType() != SelectStatement) return 0;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return( (void*) selStmt->getFieldValuePtr( pos ) );
}

int SqlStatement::noOfProjFields()
{
    if (pData.getStmtType() != SelectStatement) return 0;
    SelStatement *selStmt = (SelStatement*) stmt; 
    return selStmt->noOfProjFields();
}

int SqlStatement::noOfParamFields()
{
    return stmt->noOfParamFields();
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
    if (pData.getStmtType() ==SelectStatement ||
        pData.getStmtType() ==InsertStatement ||
        pData.getStmtType() ==UpdateStatement ||
        pData.getStmtType() ==DeleteStatement)
    {
 
        DmlStatement *dmlStmt = (DmlStatement*) stmt; 
        rv = dmlStmt->getParamFldInfo(parampos, fInfo);
    }
    return rv;
}

DbRetVal SqlStatement::free()
{
    delete stmt;
    stmt = NULL;
    pData.reset();
    isPrepd = false;
    return OK;
}

void SqlStatement::setNull(int pos)
{
    stmt->setNull(pos);
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
void SqlStatement::setBinaryParam(int paramPos, void *value)
{
    stmt->setBinaryParam(paramPos, value);
}
int SqlStatement::getFldPos(char *name)
{
    return stmt->getFldPos(name);
}
List SqlStatement::getAllTableNames(DbRetVal &ret)
{
    DatabaseManager *dbMgr = sqlCon->getConnObject().getDatabaseManager();
    return dbMgr->getAllTableNames();
}

