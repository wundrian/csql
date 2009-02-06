// Class CSqlOdbcDbc
// Description: Database Connection Handle manager. 

#ifndef _ODBC_DBC_H_
#define _ODBC_DBC_H_
#include<SqlFactory.h>
// State's of Connection Handle.
typedef enum 
{
    C0,  // henv not allocated,hdbc not allocated
    C1,  // henv allocated,hdbc not allocated
    C2,  // henv allocated,hdbc allocated
    C3,  // Connection function needs data
    C4,  // Connected hdbc
    C5,  // Connected hdbc, allocated statement
    C6   // Connected hdbc, Transaction in progress
} DbcState_t ;

class CSqlOdbcDbc
{
        CSqlOdbcDbc(void); // Should not create obj without using SQLAllocHandle

    public:
        // Top 2 variable declaration should not be moved down.
        int         handleType_;    // Handle type.
        CSqlOdbcError      err_;           // Last error info.

        DbcState_t  state_;         // Environment State.
        CSqlOdbcEnv        *parentEnv_;    // Parent Environment Handle.
        std::vector<CSqlOdbcStmt*>   stmtList_;      // Statement handle list.
        std::vector<CSqlOdbcDesc*>   descList_;      // Descriptor handle list.
        AbsSqlConnection  *fsqlConn_;      // CSQL connection object 
        int mode_; //1->csql , 2->gateway
        SQLUINTEGER curAccessMode_;
        IsolationLevel curIsolationLevel_;
        List stmtHdlList_;
        // Connection Attributes
        SQLUINTEGER accessMode_;    // Transaction access mode
                                    // SQL_MODE_READ_ONLY OR
                                    // SQL_MODE_READ_WRITE

        IsolationLevel  isolationLevel_;// Transaction Isolation Level.
                                    // SQL_TXN_READ_UNCOMMITTED
                                    // SQL_TXN_READ_COMMITTED
                                    // SQL_TXN_REPEATABLE_READ
                                    // SQL_TXN_SERIALIZABLE

        SQLUINTEGER autoCommit_;    // Automatically Commit after execution.
                                    // SQL_AUTOCOMMIT_ON
                                    // SQL_AUTOCOMMIT_OFF

    // METHODS
        // State Transition
        SQLRETURN chkStateForSQLFreeHandle( void );
        SQLRETURN chkStateForSQLConnect( void );
        SQLRETURN chkStateForSQLDisconnect( void );
        SQLRETURN chkStateForSQLEndTran( void );
        SQLRETURN chkStateForSQLSetConnectAttr( void );

        // ODBC API's
        static SQLRETURN SQLAllocHandle(
            SQLHANDLE   inputHandle,    // IN
            SQLHANDLE   *outputHandle );// OUT

        static SQLRETURN SQLFreeHandle(
            SQLHANDLE inputHandle);     // IN
 
        SQLRETURN SQLConnect(           // All param's are IN
            SQLCHAR *serverName,
            SQLSMALLINT len1,
            SQLCHAR *user,
            SQLSMALLINT len2,
            SQLCHAR *pass, 
            SQLSMALLINT len3);

        SQLRETURN SQLDisconnect(); 

        SQLRETURN SQLEndTran(
            SQLSMALLINT completionType);// IN

        SQLRETURN SQLSetConnectAttr(
            SQLINTEGER attribute,       // IN
            SQLPOINTER value,           // IN
            SQLINTEGER stringLength);   // IN

        SQLRETURN SQLGetConnectAttr(
            SQLINTEGER attribute,       // IN
            SQLPOINTER value,           // OUT
            SQLINTEGER bufferLength,    // IN
            SQLINTEGER *stringLength);  // OUT
            
        // Others
};

#endif // _ODBC_DBC_H_
