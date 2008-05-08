/*  Class CSqlOdbcEnv
    Description: Environment Handle manager. 

    ODBC API's:
                CSqlOdbcEnv::SQLAllocHandle();
                CSqlOdbcEnv::SQLFreeHandle();
                CSqlOdbcEnv::SQLSetEnvAttr();

    Other Functions:
                CSqlOdbcEnv::CSqlOdbcEnv();
*/

#include "odbcCommon.h"

// Constructor
CSqlOdbcEnv::CSqlOdbcEnv( void ) : 
    handleType_( SQL_HANDLE_ENV ), 
    state_( E1 ), 
    err_( SQL_HANDLE_ENV ),
    odbcVersion_( SQL_OV_ODBC3 )
{}

SQLRETURN SQLAllocEnv(
    SQLHENV *EnvironmentHandle)
{
    return( CSqlOdbcEnv::SQLAllocHandle( (SQLHANDLE) SQL_NULL_HANDLE, EnvironmentHandle ) );
}

// Static function
SQLRETURN CSqlOdbcEnv::SQLAllocHandle(
    SQLHANDLE   inputHandle,    // IN
    SQLHANDLE   *outputHandle ) // OUT
{   
    // Error in parameters
    if( inputHandle != SQL_NULL_HANDLE )
    {
        *outputHandle = SQL_NULL_HENV;
        return( SQL_ERROR );
    }

    // Allocate Environment.
    *outputHandle = (SQLHANDLE*) new CSqlOdbcEnv;
    if( *outputHandle == NULL )
    {
        globalError.set((int) ERROR_MEMALLOC );
        globalError.printStr( SQL_OV_ODBC3 );
        return( SQL_ERROR );
    }

    return( SQL_SUCCESS );
}

SQLRETURN SQLFreeEnv(
    SQLHENV EnvironmentHandle)
{
    return( CSqlOdbcEnv::SQLFreeHandle( EnvironmentHandle ) );
}

// Static function
SQLRETURN CSqlOdbcEnv::SQLFreeHandle(
    SQLHANDLE inputHandle)      // IN
{
    CSqlOdbcEnv *inputEnv = (CSqlOdbcEnv*) inputHandle;

    // Validate handle
    if( isValidHandle( inputEnv, SQL_HANDLE_ENV ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    // Check whether we can proceed.
    if( inputEnv->chkStateForSQLFreeHandle() != SQL_SUCCESS )
        return( SQL_ERROR );
        
    inputEnv->handleType_ = -1; // Make object invalid.
    delete inputEnv;            // Delete Environment.

    return( SQL_SUCCESS );
}

SQLRETURN SQLTransact(
    SQLHENV EnvironmentHandle,
    SQLHDBC ConnectionHandle, 
    SQLUSMALLINT CompletionType)
{
    // Call SQLEndTrans() on handle whichever is valid 
    if( isValidHandle( EnvironmentHandle, SQL_HANDLE_ENV ) == SQL_SUCCESS )
        return( ((CSqlOdbcEnv*) EnvironmentHandle)->SQLEndTran( CompletionType ) );

    if( isValidHandle( ConnectionHandle, SQL_HANDLE_DBC ) == SQL_SUCCESS )
        return( ((CSqlOdbcDbc*) ConnectionHandle)->SQLEndTran( CompletionType ) );

    return( SQL_INVALID_HANDLE );
}

SQLRETURN CSqlOdbcEnv::SQLEndTran(
    SQLSMALLINT completionType) // IN
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Stop if odbcVersion not set.
    if( odbcVersion_ == 0 )
    {
        err_.set( ERROR_FUNCSEQ );
        return( SQL_ERROR );
    }

    // If no connection objects ?
    if( dbcList_.size() == 0 )
        return( SQL_SUCCESS );

    // For each connect obj, call SQLEndTran
    std::vector<CSqlOdbcDbc*>::iterator iter;
    iter = dbcList_.begin();
    while( iter != dbcList_.end() )
    {
        if( (*iter)->chkStateForSQLEndTran() == SQL_SUCCESS )
            if( (*iter)->SQLEndTran( completionType ) == SQL_ERROR )
                return( SQL_ERROR );

        iter++;
    }

    return( SQL_SUCCESS );
}

SQLRETURN SQLSetEnvAttr(
            SQLHENV    inputEnv,        // IN
            SQLINTEGER Attribute,       // IN
            SQLPOINTER Value,           // IN
            SQLINTEGER StringLength)    // IN
{
   // Validate handle
   if( isValidHandle( inputEnv, SQL_HANDLE_ENV ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

   return( ((CSqlOdbcEnv*)inputEnv)->SQLSetEnvAttr( Attribute, Value, StringLength ) );
}

SQLRETURN  CSqlOdbcEnv::SQLSetEnvAttr(
            SQLINTEGER attribute,       // IN
            SQLPOINTER value,           // IN
            SQLINTEGER stringLength)    // IN
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Check whether we can proceed.
    if( chkStateForSQLSetEnvAttr() != SQL_SUCCESS )
        return( SQL_ERROR );
        
    switch( attribute )
    {
        case SQL_ATTR_ODBC_VERSION:
            switch( (SQLINTEGER) value )
            {
                case SQL_OV_ODBC2:
                case SQL_OV_ODBC3: break;
                default:
                        err_.set( ERROR_OPTCHANGE );
                        return( SQL_ERROR );
            }
            odbcVersion_ = (SQLUINTEGER) value;
            break;

        case SQL_ATTR_OUTPUT_NTS:
            if( (SQLINTEGER) value == SQL_TRUE )
                return( SQL_SUCCESS );
            else
            {
                err_.set( ERROR_OPTFEATURE_NOTIMP );
                return( SQL_ERROR );
            }
            break;

        default: err_.set( ERROR_OPTRANGE );
                 return( SQL_ERROR );
    }

    return( SQL_SUCCESS );
}

SQLRETURN SQLGetEnvAttr(
    SQLHENV EnvironmentHandle,
    SQLINTEGER Attribute,
    SQLPOINTER Value,
    SQLINTEGER BufferLength, 
    SQLINTEGER *StringLength)
{
   // Validate handle
   if( isValidHandle( EnvironmentHandle, SQL_HANDLE_ENV ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

   return( ((CSqlOdbcEnv*)EnvironmentHandle)->SQLGetEnvAttr( Attribute, Value, BufferLength, StringLength ) );
}

SQLRETURN CSqlOdbcEnv::SQLGetEnvAttr(
    SQLINTEGER attribute,
    SQLPOINTER value,
    SQLINTEGER bufferLength, 
    SQLINTEGER *stringLength)
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed.? Always ( in all states)
        
    switch( attribute )
    {
        case SQL_ATTR_ODBC_VERSION:
            *((SQLUINTEGER*) value) = odbcVersion_;
            break;

        case SQL_ATTR_OUTPUT_NTS:
            *((SQLUINTEGER*) value) = SQL_TRUE;
            break;

        default: err_.set( ERROR_OPTRANGE );
                 return( SQL_ERROR );
    }

    return( SQL_SUCCESS );
}
