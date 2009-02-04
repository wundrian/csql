/*  Class CSqlOdbcDbc
    Description: Connection Handle manager. 

    ODBC API's:
                CSqlOdbcDbc::SQLAllocDbc();
                CSqlOdbcDbc::SQLFreeDbc();
                CSqlOdbcDbc::SQLConnect();
*/

#include "odbcCommon.h"

// Constructor
CSqlOdbcDbc::CSqlOdbcDbc( void ) :
        handleType_( SQL_HANDLE_DBC ),
        parentEnv_( 0 ),
        state_( C1 ),
        err_( SQL_HANDLE_DBC ),
        mode_ (1), 
        curAccessMode_( ACCESSMODE_READ_WRITE ),
        curIsolationLevel_( READ_REPEATABLE ),
        accessMode_( ACCESSMODE_READ_WRITE ),
        isolationLevel_( READ_COMMITTED ),
        autoCommit_( SQL_AUTOCOMMIT_ON ),
        fsqlConn_( NULL ) 
{}

SQLRETURN SQLAllocConnect(
    SQLHENV EnvironmentHandle,
    SQLHDBC *ConnectionHandle)
{
    return( CSqlOdbcDbc::SQLAllocHandle( EnvironmentHandle, ConnectionHandle ) );
}

// All ODBC API's below.
SQLRETURN CSqlOdbcDbc::SQLAllocHandle(
    SQLHANDLE   inputHandle,    // IN
    SQLHANDLE   *outputHandle ) // OUT
{

    CSqlOdbcEnv *inputEnv = (CSqlOdbcEnv*) inputHandle;

    if( isValidHandle( inputEnv, SQL_HANDLE_ENV ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    // Stop if odbcVersion not set.
    if( inputEnv->odbcVersion_ == 0 )
    {
        inputEnv->err_.set( ERROR_FUNCSEQ );
        return( SQL_ERROR );
    }

    // Allocate Connection object.
    *outputHandle = (SQLHANDLE*) new CSqlOdbcDbc;
    if( *outputHandle == NULL )
    {
        globalError.set( ERROR_MEMALLOC );
        globalError.printStr( SQL_OV_ODBC3 );
        return( SQL_ERROR );
    }

    // Initialize relation b/w Env and Dbc
    inputEnv->dbcList_.insert( inputEnv->dbcList_.begin(), (CSqlOdbcDbc*) *outputHandle );
    inputEnv->state_ = E2;
    ((CSqlOdbcDbc*) *outputHandle)->parentEnv_ = inputEnv;
    ((CSqlOdbcDbc*) *outputHandle)->state_ = C2;

    return( SQL_SUCCESS );
}

SQLRETURN SQLFreeConnect(
    SQLHDBC ConnectionHandle)
{
    return( CSqlOdbcDbc::SQLFreeHandle( ConnectionHandle ) );
}

SQLRETURN CSqlOdbcDbc::SQLFreeHandle(
    SQLHANDLE inputHandle)      // IN
{
    CSqlOdbcDbc *inputDbc = (CSqlOdbcDbc*) inputHandle;

    // Validate handle
    if( isValidHandle( inputDbc, SQL_HANDLE_DBC ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    // Check whether we can proceed.
    if( inputDbc->chkStateForSQLFreeHandle() != SQL_SUCCESS )
        return( SQL_ERROR );

    // Remove Dbc from Parent Env.
    std::vector<CSqlOdbcDbc*>::iterator iter;
    iter = inputDbc->parentEnv_->dbcList_.begin();
    while( iter != inputDbc->parentEnv_->dbcList_.end() )
    {
        if( *iter == inputDbc )
        {
            inputDbc->parentEnv_->dbcList_.erase( iter );
            break;
        }
        iter++;
    }
    if( inputDbc->parentEnv_->dbcList_.size() == 0 )
        inputDbc->parentEnv_->state_ = E1;

    inputDbc->handleType_ = -1; // Make object invalid.
    delete inputDbc;            // Delete Dbc.

    return( SQL_SUCCESS );
}

SQLRETURN SQLDriverConnect(
     SQLHDBC     ConnectionHandle,
     SQLHWND     WindowHandle,
     SQLCHAR *     InConnectionString,
     SQLSMALLINT     StringLength1,
     SQLCHAR *     OutConnectionString,
     SQLSMALLINT     BufferLength,
     SQLSMALLINT *     StringLength2Ptr,
     SQLUSMALLINT     DriverCompletion)
{
    printf("Connection string is %s\n", InConnectionString);
    // Validate handle
    if( isValidHandle( ConnectionHandle, SQL_HANDLE_DBC ) != SQL_SUCCESS )
                 return( SQL_INVALID_HANDLE );
    
    return( ((CSqlOdbcDbc*) ConnectionHandle)->SQLConnect((SQLCHAR*)"a", 
                      (SQLSMALLINT)strlen("a"), (SQLCHAR*)"root", (SQLSMALLINT)strlen("root"), 
                      (SQLCHAR*)"manager", (SQLSMALLINT)strlen("manager")) );
   
}

SQLRETURN SQLConnect(           // All param's are IN
    SQLHDBC ConnectionHandle,
    SQLCHAR *ServerName,
    SQLSMALLINT NameLength1,
    SQLCHAR *UserName,
    SQLSMALLINT NameLength2,
    SQLCHAR *Authentication, 
    SQLSMALLINT NameLength3)
{
    // Validate handle
    if( isValidHandle( ConnectionHandle, SQL_HANDLE_DBC ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcDbc*) ConnectionHandle)->SQLConnect( ServerName, NameLength1, 
        UserName, NameLength2, Authentication, NameLength3) );
}

SQLRETURN CSqlOdbcDbc::SQLConnect(           // All param's are IN
    SQLCHAR *serverName,
    SQLSMALLINT len1,
    SQLCHAR *user,
    SQLSMALLINT len2,
    SQLCHAR *pass, 
    SQLSMALLINT len3)
{
    int rc;
    char *hostName,*portNo;
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLConnect() != SQL_SUCCESS )
        return( SQL_ERROR );
    
    // Invalid Buffer Length.
    if( (len1 < 0 && len1 != SQL_NTS) || (len2 < 0 && len2 != SQL_NTS) || (len2 < 0 && len2 != SQL_NTS) )
    {
        err_.set( ERROR_BUFLEN );
        return( SQL_ERROR );
    }
    if (fsqlConn_ != NULL)
    {
        err_.set( ERROR_CONNINUSE);
        return ( SQL_ERROR );
    }
    if (strcasecmp((char*)serverName, "gateway") == 0)
    {
        fsqlConn_ = SqlFactory::createConnection(CSqlGateway);
        mode_ = 2;
    }else if (strcasecmp((char*)serverName, "adapter") == 0){
        fsqlConn_ = SqlFactory::createConnection(CSqlAdapter);
        mode_ = 3;
    }else{
        fsqlConn_ = SqlFactory::createConnection(CSql);
        mode_ = 1;
    }

    rc = fsqlConn_->connect( (char*) user, (char*) pass );
    if( rc != OK )
    {
        err_.set( ERROR_CONNREJCTD);
        return( SQL_ERROR );
    }
    rc = fsqlConn_->beginTrans( isolationLevel_ );
    if( rc != OK )
    {
        err_.set( ERROR_INVTRANSTATE );
        return( SQL_ERROR );
    }
    curAccessMode_ = accessMode_;
    curIsolationLevel_ = isolationLevel_;

    // Update Dbc state
    state_ = C4;

    return( SQL_SUCCESS );
}

SQLRETURN SQLDisconnect(
    SQLHDBC ConnectionHandle)   // IN
{
    // Validate Handle
    if( isValidHandle( ConnectionHandle, SQL_HANDLE_DBC ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );
    SQLRETURN ret = ( ((CSqlOdbcDbc*) ConnectionHandle)->SQLDisconnect() );
    return ret;
}

SQLRETURN CSqlOdbcDbc::SQLDisconnect( void )
{
    SQLRETURN rc;

    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLDisconnect() != SQL_SUCCESS )
        return( SQL_ERROR );

    // Free all stmts
    while( stmtList_.size() != 0 )
    {
        rc = CSqlOdbcStmt::SQLFreeHandle( stmtList_[0] );
        // This free's the stmt and removes element from stmtList_.
        if( rc != OK )
            return( SQL_ERROR );
    }

    // Commit the transaction
    if( fsqlConn_->commit() != OK )
        return( SQL_ERROR );
        
    // Disconnect
    if( fsqlConn_->disconnect() != OK )
        return( SQL_ERROR );

    delete fsqlConn_;
    fsqlConn_ = NULL;
    // Change the state of Dbc
    state_ = C2;

    return( SQL_SUCCESS );
}

SQLRETURN CSqlOdbcDbc::SQLEndTran(
    SQLSMALLINT completionType) // IN
{
    SQLRETURN rc;

    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLEndTran() != SQL_SUCCESS )
        return( SQL_ERROR );

    // Stop if no transaction is started.
    if( state_ != C6 )
        return( SQL_SUCCESS );

    // Close cursors of all the statements
    std::vector<CSqlOdbcStmt*>::iterator iter;
    iter = stmtList_.begin();
    while( iter != stmtList_.end() )
    {
        (*iter)->SQLFreeHandle( SQL_CLOSE );
        iter++;
    }

    // Finish transaction
    switch( completionType )
    {
        case SQL_COMMIT:

		    if( fsqlConn_->commit() != OK )
			return( SQL_ERROR );

                    if( fsqlConn_->beginTrans( curIsolationLevel_ ) != OK )
			return( SQL_ERROR );

                    break;

        case SQL_ROLLBACK:
                    if( fsqlConn_->rollback() != OK )
                        return( SQL_ERROR );

                    rc = fsqlConn_->beginTrans( curIsolationLevel_ );
                    break;

        default:    err_.set( ERROR_OPTRANGE );
                    return( SQL_ERROR );
    }

    // Had statements ?
    if( stmtList_.size() == 0 )
        state_ = C4;
    else
        state_ = C5;

    return( SQL_SUCCESS );
}

SQLRETURN SQLSetConnectOption(
    SQLHDBC ConnectionHandle,
    SQLUSMALLINT Option,
    SQLUINTEGER Value)
{
    return( SQLSetConnectAttr( ConnectionHandle, Option, (SQLPOINTER) Value, 0) );
}

SQLRETURN SQLSetConnectAttr(
    SQLHDBC ConnectionHandle,
    SQLINTEGER Attribute,
    SQLPOINTER Value,
    SQLINTEGER StringLength)
{
   // Validate handle
   if( isValidHandle( ConnectionHandle, SQL_HANDLE_DBC ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

   return( ((CSqlOdbcDbc*)ConnectionHandle)->SQLSetConnectAttr( Attribute, Value, StringLength ) );
}

SQLRETURN CSqlOdbcDbc::SQLSetConnectAttr(
    SQLINTEGER attribute,
    SQLPOINTER value,
    SQLINTEGER stringLength)
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    switch( attribute )
    {
        case SQL_ATTR_ACCESS_MODE:
            // validate 'value'
            if( (SQLUINTEGER) value == SQL_MODE_READ_ONLY )
                accessMode_ = ACCESSMODE_READ_ONLY;
            else if( (SQLUINTEGER) value == SQL_MODE_READ_WRITE )
                accessMode_ = ACCESSMODE_READ_WRITE;
            else
                return( SQL_ERROR );

            break;
        case SQL_DEFAULT_TXN_ISOLATION:
        case SQL_ATTR_TXN_ISOLATION:
            // validate 'value'
            if( (SQLUINTEGER) value == SQL_TXN_READ_UNCOMMITTED )
                isolationLevel_ = READ_UNCOMMITTED;
            else if( (SQLUINTEGER) value == SQL_TXN_READ_COMMITTED )
                isolationLevel_ = READ_COMMITTED;
            else if( (SQLUINTEGER) value == SQL_TXN_REPEATABLE_READ )
                isolationLevel_ = READ_REPEATABLE;
//            else if( (SQLUINTEGER) value == SQL_TXN_SERIALIZABLE )
//                isolationLevel_ = SERIALIZABLE;
            else
                return( SQL_ERROR );

            break;
        case SQL_ATTR_AUTOCOMMIT:
            autoCommit_ = (SQLUINTEGER) value;
            if( state_ == C6 )
                SQLEndTran( SQL_COMMIT );
            break;

        default: err_.set( ERROR_OPTRANGE );
                 return( SQL_ERROR );
    }

    return( SQL_SUCCESS );
}

SQLRETURN SQLGetConnectOption(
    SQLHDBC ConnectionHandle,
    SQLUSMALLINT Option,
    SQLPOINTER Value)
{
    return( SQLGetConnectAttr( ConnectionHandle, Option, Value, 0, 0) );
}

SQLRETURN SQLGetConnectAttr(
    SQLHDBC ConnectionHandle,
    SQLINTEGER Attribute,
    SQLPOINTER Value,
    SQLINTEGER BufferLength,
    SQLINTEGER *StringLength)
{
   // Validate handle
   if( isValidHandle( ConnectionHandle, SQL_HANDLE_DBC ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

   return( ((CSqlOdbcDbc*)ConnectionHandle)->SQLGetConnectAttr( Attribute, Value, BufferLength, StringLength ) );
}

SQLRETURN CSqlOdbcDbc::SQLGetConnectAttr(
    SQLINTEGER attribute,
    SQLPOINTER value,
    SQLINTEGER bufferLength,
    SQLINTEGER *stringLength)
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    switch( attribute )
    {
        case SQL_ATTR_ACCESS_MODE:
            // Get ODBC Access Mode
            if( accessMode_ == ACCESSMODE_READ_ONLY )
                *((SQLUINTEGER*) value) = SQL_MODE_READ_ONLY;
            else if( accessMode_ == ACCESSMODE_READ_WRITE )
                *((SQLUINTEGER*) value) = SQL_MODE_READ_WRITE;
            else
                return( SQL_ERROR );

            break;
        case SQL_DEFAULT_TXN_ISOLATION:
        case SQL_ATTR_TXN_ISOLATION:
            // validate 'value'
            if( (SQLUINTEGER) isolationLevel_ == READ_UNCOMMITTED )
                *((SQLUINTEGER*) value) = SQL_TXN_READ_UNCOMMITTED;
            else if( (SQLUINTEGER) isolationLevel_ == READ_COMMITTED )
                *((SQLUINTEGER*) value) = SQL_TXN_READ_COMMITTED;
            else if( (SQLUINTEGER) isolationLevel_ == READ_REPEATABLE )
                *((SQLUINTEGER*) value) = SQL_TXN_REPEATABLE_READ;
//            else if( (SQLUINTEGER) isolationLevel_ == SERIALIZABLE )
//                *((SQLUINTEGER*) value) = SQL_TXN_SERIALIZABLE;
            else
                return( SQL_ERROR );

            break;
        case SQL_ATTR_AUTOCOMMIT:
            *((SQLUINTEGER*) value) = autoCommit_;
            break;

        default: err_.set( ERROR_OPTRANGE );
                 return( SQL_ERROR );
    }

    return( SQL_SUCCESS );
}
