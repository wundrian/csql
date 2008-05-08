#include "odbcCommon.h"

// Global error object definition
CSqlOdbcError globalError( SQL_HANDLE_ENV );

CSqlOdbcError::CSqlOdbcError( void )
{
    fprintf(stderr,"This should not happen!!\n");
    exit(1);
}

CSqlOdbcError::CSqlOdbcError( long handleType ) : 
    csqlErrCode ( OK ), 
    hdlType( handleType ) 
{}

void CSqlOdbcError::set( long err ) 
{ 
    csqlErrCode = err; 
    
    if( err != OK );
        printStr( SQL_OV_ODBC3 ); 
}

SQLRETURN CSqlOdbcError::printStr( SQLUINTEGER odbcVersion )
{
    ErrorInfo_t *errorInfoTbl;
    int code = 0, i = 0;
    
#ifndef DEBUG_INFO
    return( SQL_SUCCESS );
#endif

    // Select error table.
    if( odbcVersion >= SQL_OV_ODBC3 )
        errorInfoTbl = errorInfoTable_3x;
    else
        errorInfoTbl = errorInfoTable_2x;

    // Search in table.
    while( errorInfoTbl[i].csqlErrCode != csqlErrCode && errorInfoTbl[i].csqlErrCode != ERROR_ENDOFTABLE ) i++;

    // Print details, if found
    if( errorInfoTbl[i].csqlErrCode == csqlErrCode )
    {
        fprintf( stderr, "[NativeCode: %ld][SqlState: %s][Message: %s].\n", 
            csqlErrCode, 
            (char*) errorInfoTbl[i].sqlState,
            (char*) errorInfoTbl[i].sqlMessage );

        return( SQL_SUCCESS );
    }

    return( SQL_ERROR );
}

SQLRETURN SQLError(
    SQLHENV EnvironmentHandle,  // IN
    SQLHDBC ConnectionHandle,   // IN
    SQLHSTMT StatementHandle,   // IN
    SQLCHAR *Sqlstate,          // OUT
    SQLINTEGER *NativeError,    // OUT
    SQLCHAR *MessageText,       // OUT
    SQLSMALLINT BufferLength,   // IN
    SQLSMALLINT *TextLength)    // OUT
{
    // Call SQLGetDiagRec() on handle whichever is valid.
    if( isValidHandle( EnvironmentHandle, SQL_HANDLE_ENV ) == SQL_SUCCESS )
        return( ((CSqlOdbcEnv*)EnvironmentHandle)->err_.SQLGetDiagRec(EnvironmentHandle, Sqlstate, NativeError, MessageText, BufferLength, TextLength) );

    if( isValidHandle( ConnectionHandle, SQL_HANDLE_DBC ) == SQL_SUCCESS )
        return( ((CSqlOdbcDbc*)ConnectionHandle)->err_.SQLGetDiagRec(ConnectionHandle, Sqlstate, NativeError, MessageText, BufferLength, TextLength) );

    if( isValidHandle( StatementHandle, SQL_HANDLE_STMT ) == SQL_SUCCESS )
        return( ((CSqlOdbcStmt*)StatementHandle)->err_.SQLGetDiagRec(StatementHandle, Sqlstate, NativeError, MessageText, BufferLength, TextLength) );

    return( SQL_INVALID_HANDLE );
} 

// ODBC API's
SQLRETURN SQLGetDiagRec(
    SQLSMALLINT HandleType, 
    SQLHANDLE Handle,
    SQLSMALLINT RecNumber,
    SQLCHAR *Sqlstate,
    SQLINTEGER *NativeError, 
    SQLCHAR *MessageText,
    SQLSMALLINT BufferLength, 
    SQLSMALLINT *TextLength)
{
    // Validate handle
    if( isValidHandle( Handle, HandleType ) != SQL_SUCCESS )
        return( SQL_ERROR );

    return( ((CSqlOdbcEnv*)Handle)->err_.SQLGetDiagRec(Handle, Sqlstate, NativeError, MessageText, BufferLength, TextLength) );
}

SQLRETURN CSqlOdbcError::SQLGetDiagRec(
            SQLHANDLE   handle,     // IN
            SQLCHAR     *sqlState,  // OUT
            SQLINTEGER  *sqlErrCode,// OUT
            SQLCHAR     *Msg,       // OUT
            SQLSMALLINT  bufLen,    // IN
            SQLSMALLINT *textLen)   // OUT
{
    ErrorInfo_t *errorInfoTbl;
    int code = 0, i = 0;
    SQLUINTEGER odbcVersion;
    
    // Get ODBC Version
    switch( hdlType )
    {
        case SQL_HANDLE_ENV:
            odbcVersion = ((CSqlOdbcEnv*) handle)->odbcVersion_; break;
        case SQL_HANDLE_DBC:
            odbcVersion = ((CSqlOdbcDbc*) handle)->parentEnv_->odbcVersion_; break;
        case SQL_HANDLE_STMT:
            odbcVersion = ((CSqlOdbcStmt*) handle)->parentDbc_->parentEnv_->odbcVersion_; break;
        default:
            return( SQL_ERROR );
    }

    // If No Error
    if( csqlErrCode == OK )
        return( SQL_NO_DATA_FOUND );

    // Select Error Msg Table based on ODBC Version
    if( odbcVersion >= SQL_OV_ODBC3 )
        errorInfoTbl = errorInfoTable_3x;
    else
        errorInfoTbl = errorInfoTable_2x;

    // Search in table
    while( errorInfoTbl[i].csqlErrCode != csqlErrCode ) i++;
    if( errorInfoTbl[i].csqlErrCode == csqlErrCode )
    {
        // Fill error info to user space
        strcpy( (char*) sqlState, (char*) errorInfoTbl[i].sqlState );
        *sqlErrCode = csqlErrCode;
        *textLen = (SQLSMALLINT) strlen( (char*) errorInfoTbl[i].sqlMessage );
        if( bufLen > *textLen )
            bufLen = *textLen + 1;
        strncpy( (char*) Msg, (char*) errorInfoTbl[i].sqlMessage, (int) bufLen );
        return( SQL_SUCCESS );
    }

    return( SQL_ERROR );
}

void CSqlOdbcError::printDbg( char *msg )
{
#ifdef DEBUG_INFO
    fprintf( stderr, "ODBC DBG: %s\n", msg );
#endif
    return;
}
