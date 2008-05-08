#ifndef _ODBC_COMMON_H_
#define _ODBC_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

// SQL Standard headers
#include <sqlext.h>

// SQLAPI Interface
#include <SqlStatement.h>

// Forward Declaration
class CSqlOdbcEnv;
class CSqlOdbcDbc;
class CSqlOdbcStmt;
class CSqlOdbcDesc;

// ODBC internal headers
#include "odbcError.h"
#include "odbcEnv.h"
#include "odbcDbc.h"
#include "odbcDesc.h"
#include "odbcStmt.h"

// There is not equivalent mode in CSQL, should confirm. ??
#define ACCESSMODE_READ_ONLY   0
#define ACCESSMODE_READ_WRITE  1

// Is handle valid ?
SQLRETURN isValidHandle( SQLHANDLE hnd, SQLSMALLINT handleType );

// Is C type valid/supported ?
SQLRETURN isValidCType( SQLSMALLINT type );

// Is SQL type valid/supported ?
SQLRETURN isValidSQLType( SQLSMALLINT type );

// Type conversion functions
void copyFromOdbc(void *destData, SQLUINTEGER destLen, 
		  void *odbcData, SQLUINTEGER odbcLen, SQLSMALLINT type);
SQLINTEGER copyToOdbc(void *odbcData, SQLUINTEGER odbcLen, 
		      void *sourceData, SQLUINTEGER sourceLen,SQLSMALLINT type);

void getInputBuffer(void **buffer,SQLSMALLINT  type,SQLUINTEGER length);

DataType getCSqlType( SQLSMALLINT type );

SQLSMALLINT getSQLType( DataType type );

SQLCHAR *getSQLTypeName( SQLSMALLINT type );
 
#endif
