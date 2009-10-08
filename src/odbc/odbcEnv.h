// Class CSqlOdbcEnv
// Description: Environment Handle manager. 

#ifndef _ODBC_ENV_H_
#define _ODBC_ENV_H_

// State's of Environment Handle.
typedef enum 
{
    E0,     // Environment in unallocated state. (DriverManager)
    E1,     // Allocated Environment , hdbc in unallocated state.
    E2      // Allocated Environment , allocated hdbc.
} EnvState_t ;

class CSqlOdbcEnv
{
        CSqlOdbcEnv(void); // Should not create obj without SQLAllocHandle
        
    public:
        // Top 2 variable declaration should not be moved down.
        int         handleType_;      // Handle type.
        CSqlOdbcError      err_;       // Last error info.

        EnvState_t  state_;           // Environment State.
        List dbcList_; // Connection handle list.

        // Environment Attributes
        SQLUINTEGER odbcVersion_;
        
        // State Transition
        // Check whether we can continue executing SQLxxxx API.
        SQLRETURN   chkStateForSQLFreeHandle( void );
        SQLRETURN   chkStateForSQLSetEnvAttr( void );
        
        // ODBC API's
        static SQLRETURN SQLAllocHandle(
            SQLHANDLE inputHandle,      // IN
            SQLHANDLE *outputHandle );  // OUT

        static SQLRETURN SQLFreeHandle(
            SQLHANDLE inputHandle);     // IN

        SQLRETURN SQLEndTran(
            SQLSMALLINT completionType);// IN

        SQLRETURN SQLSetEnvAttr(
            SQLINTEGER attribute,       // IN
            SQLPOINTER value,           // IN
            SQLINTEGER stringLength);   // IN

        SQLRETURN SQLGetEnvAttr(
            SQLINTEGER attribute,       // IN
            SQLPOINTER value,           // OUT
            SQLINTEGER bufferLength,    // IN
            SQLINTEGER *stringLength);  // OUT

        // Other's
};

#endif // _ODBC_ENV_H_
