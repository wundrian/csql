
/* Description: State Transition Functions. 
                States which are maintained by DriverManager is
                not used. Implementation of DriverManager would use them.

*/

#include "odbcCommon.h"

// Related to Environment Handle
//------------------------------
SQLRETURN CSqlOdbcEnv::chkStateForSQLFreeHandle( void )
{
    switch( state_ )
    {
        case E0:
        case E1: break;
        case E2: err_.set( ERROR_FUNCSEQ ); 
                 return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcEnv::chkStateForSQLSetEnvAttr( void )
{
    switch( state_ )
    {
        case E0:
        case E1: break;
        case E2: err_.set( ERROR_ATTR_CANNOT_SET ); 
                 return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}

// Related to Connection Handle
//------------------------------
SQLRETURN CSqlOdbcDbc::chkStateForSQLFreeHandle( void )
{
    switch( state_ )
    {
        case C0:
        case C1:
        case C2: break;
        case C3:
        case C4:
        case C5:
        case C6: err_.set( ERROR_FUNCSEQ );
                 return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcDbc::chkStateForSQLConnect( void )
{
    switch( state_ )
    {
        case C0:
        case C1:
        case C2: break;
        case C3:
        case C4:
        case C5:
        case C6: err_.set( ERROR_CONNINUSE );
                 return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcDbc::chkStateForSQLDisconnect( void )
{
    switch( state_ )
    {
        case C0:
        case C1:
        case C2: err_.set( ERROR_CONNOTOPEN );
                 return( SQL_ERROR );
        case C3:
        case C4:
        case C5: break;
        case C6: err_.set( ERROR_INVTRANSTATE );
                 return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcDbc::chkStateForSQLEndTran( void )
{
    switch( state_ )
    {
        case C0:
        case C1:
        case C2: 
        case C3: err_.set( ERROR_NOTOPENED );
                 return( SQL_ERROR );
        case C4:
        case C5:
        case C6: break;
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcDbc::chkStateForSQLSetConnectAttr( void )
{
    switch( state_ )
    {
        case C0:
        case C1:
        case C2:
        case C3:
        case C4:
        case C5: break;
        case C6: err_.set( ERROR_FUNCSEQ );
                 return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}

// Related to Statement Handle
//------------------------------
SQLRETURN CSqlOdbcStmt::chkStateForSQLFreeHandle( void )
{
    switch( state_ )
    {
        case S0:
        case S1:
        case S2:
        case S3:
        case S4:
        case S5:
        case S6:
        case S7: break;
        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLFreeStmt( void )
{
    switch( state_ )
    {
        case S0:
        case S1:
        case S2:
        case S3:
        case S4:
        case S5:
        case S6:
        case S7: break;
        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLBindCol( void )
{
    switch( state_ )
    {
        case S0:
        case S1:
        case S2:
        case S3:
        case S4:
        case S5:
        case S6:
        case S7: break;
        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLBindParameter( void )
{
    switch( state_ )
    {
        case S0:
        case S1:
        case S2:
        case S3:
        case S4:
        case S5:
        case S6:
        case S7: break;
        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLPrepare( void )
{
    switch( state_ )
    {
        case S0:
        case S1:
        case S2:
        case S3:
        case S4: break;

        case S5:
        case S6:
        case S7: err_.set( ERROR_INVCURSTATE );
                 return( SQL_ERROR );
        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLExecute( void )
{
    switch( state_ )
    {
        case S2:
        case S3:
        case S4: break;

        case S5:
        case S6:
        case S7: err_.set( ERROR_INVCURSTATE );
                 return( SQL_ERROR );

        case S0:
        case S1:
        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLExecDirect( void )
{
    switch( state_ )
    {
        case S0:
        case S1:
        case S2:
        case S3:
        case S4: break;

        case S5:
        case S6:
        case S7: err_.set( ERROR_INVCURSTATE );
                 return( SQL_ERROR );

        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLFetch( void )
{
    switch( state_ )
    {
        case S0:
        case S1:
        case S2:
        case S3: err_.set( ERROR_NOT_PREPAREDSTMT );
                 return( SQL_ERROR );
        case S4: err_.set( ERROR_INVCURSTATE );
                 return( SQL_ERROR );
        case S5:
        case S6:
        case S7: break;

        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLCloseCursor( void )
{
    switch( state_ )
    {
        case S0:
        case S1:
        case S2:
        case S3:
        case S4: err_.set( ERROR_INVCURSTATE );
                 return( SQL_ERROR );
        case S5:
        case S6:
        case S7: break;
        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLGetCursorName( void )
{
    switch( state_ )
    {
        case S0:
        case S1:
        case S2:
        case S3:
        case S4:
        case S5:
        case S6:
        case S7: break; 

        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLSetCursorName( void )
{
    switch( state_ )
    {
        case S0:
        case S1:
        case S2:
        case S3: break;

        case S4:
        case S5:
        case S6:
        case S7: 
        case S8: err_.set( ERROR_INVCURSTATE );
                 return( SQL_ERROR );
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLNumResultCols( void )
{
    switch( state_ )
    {
        case S2:
        case S3:
        case S4:
        case S5:
        case S6:
        case S7: break;

        case S0:
        case S1: 

        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLRowCount( void )
{
    switch( state_ )
    {
        case S4:
        case S5:
        case S6: break;

        case S0:
        case S1: 
        case S2:
        case S3:

        case S7:
        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLDescribeCol( void )
{
    switch( state_ )
    {
        case S4: err_.set( ERROR_INVCURSTATE );
                 return( SQL_ERROR );

        case S3:
        case S5:
        case S6:
        case S7: break;

        case S0:
        case S1: 
        case S2:

        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
SQLRETURN CSqlOdbcStmt::chkStateForSQLNumParams(void )
{
    switch( state_ )
    {

        case S0: err_.set(ERROR_INVCURSTATE );
                 return( SQL_ERROR );
        case S2:
        case S3:
        case S4: 
        case S5:
        case S6:
        case S7: break;
        case S1:
        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}

SQLRETURN CSqlOdbcStmt::chkStateForSQLDescribeParam(void)
{
    switch( state_ )
    {
        case S2:
        case S3:break;
        case S0:
        case S1: 
        case S5:
        case S6:
        case S7: 
        case S8:
        case S9:
        case S10:
        case S11:
        case S12: err_.set( ERROR_FUNCSEQ );
                  return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}
