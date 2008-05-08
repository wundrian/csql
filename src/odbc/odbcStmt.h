
// Class CSqlOdbcStmt
// Description: Statement Handle manager. 

#ifndef _ODBC_STMT_H_
#define _ODBC_STMT_H_

// State's of Statement Handle.
typedef enum
{
     S0,                // hstmt in unallocated state 
     S1,                // hstmt in allocated state    
     S2,                // prepared hstmt - no result set will be genarated
     S3,                // prepared hstmt - result set will be genarated
     S4,                // executed hstmt - no result set generated.   
     S5,                // executed hstmt - result set generated.   
     S6,                // cursor positioned with SQLFetch
     S7,                // cursor positioned with SQLExtendedFetch
     S8,                // Function needs data - SQLParamData not called
     S9,                // Function needs data - SQLPutData not called
     S10,               // Function needs data - SQLPutData called
     S11,               // Still Executing
     S12                // Asyncronous cancel
 } StmtState_t ;

class CSqlOdbcStmt
{
        CSqlOdbcStmt( void ); // Should not create obj without using SQLAllocHandle

    public:
        // Top 2 variable declaration should not be moved down.
        int handleType_;            // Handle type.
        CSqlOdbcError err_;          // Last error info.

        CSqlOdbcDbc *parentDbc_;     // Parent Connection Handle.
        StmtState_t state_; 
        SQLCHAR cursorName_[ SQL_MAX_CURSOR_NAME_LEN ];
        int rowsAffected_;
        bool isPrepared_;

        SQLUINTEGER fetchMode_; // SQL_FETCH_SINGLE_TUPLE or SQL_FETCH_MULTIPLE_TUPLES

        // Descriptor Lists
        bool isParamBound_;
        CSqlOdbcDescList ard_;     // Application Row Descriptor
                                  // Bound columns using SQLBindCol()

        CSqlOdbcDescList ird_;     // Implimentation Row Descriptor
                                  // populated during SQLPrepare()

        CSqlOdbcDescList apd_;     // Application Parameter Descriptor
                                  // Bound paramenters using SQLBindParameter()

        CSqlOdbcDescList ipd_;     // Implimentation Parameter Descriptor
                                  // populated during SQLPrepare()

        // FastSQL Statement Object 
        SqlStatement fsqlStmt_; // CSQL

        // Statement Attributes
        
    // METHODS

        // State Transition
        SQLRETURN chkStateForSQLFreeHandle( void );
        SQLRETURN chkStateForSQLFreeStmt( void );
        SQLRETURN chkStateForSQLBindCol( void );
        SQLRETURN chkStateForSQLBindParameter( void );

        SQLRETURN chkStateForSQLPrepare( void );
        SQLRETURN chkStateForSQLExecute( void );
        SQLRETURN chkStateForSQLExecDirect( void );
        SQLRETURN chkStateForSQLFetch( void );
        SQLRETURN chkStateForSQLCloseCursor( void );

        SQLRETURN chkStateForSQLNumParams( void );
        SQLRETURN chkStateForSQLNumResultCols( void );
        SQLRETURN chkStateForSQLRowCount( void );
        SQLRETURN chkStateForSQLDescribeCol( void );
        SQLRETURN chkStateForSQLDescribeParam(void);

        SQLRETURN chkStateForSQLSetCursorName( void );
        SQLRETURN chkStateForSQLGetCursorName( void );
        

        // ODBC API's
        static SQLRETURN SQLAllocHandle(
            SQLHANDLE   inputHandle,    // IN
            SQLHANDLE   *outputHandle );// OUT

        static SQLRETURN SQLFreeHandle(
            SQLHANDLE inputHandle);     // IN

        SQLRETURN SQLFreeStmt(
            SQLUSMALLINT option);       // IN

        SQLRETURN SQLBindCol(
            SQLUSMALLINT columnNumber,  // IN
            SQLSMALLINT targetType,     // IN
            SQLPOINTER targetValue,     // OUT
            SQLINTEGER bufferLength,    // IN
            SQLINTEGER *ind); // IN_OUT

        SQLRETURN SQLBindParameter(
            SQLUSMALLINT parameterNumber,//IN
            SQLSMALLINT inputOutputType,// IN
            SQLSMALLINT valueType,      // IN
            SQLSMALLINT parameterType,  // IN
            SQLUINTEGER lengthPrecision,// IN
            SQLSMALLINT parameterScale, // IN
            SQLPOINTER parameterValue,  // OUT
            SQLINTEGER bufferLength,    // IN
            SQLINTEGER *ind);           // IN_OUT

        SQLRETURN SQLPrepare(
            SQLCHAR *statementText,     // IN
            SQLINTEGER textLength);     // IN

        SQLRETURN SQLExecute( void );

        SQLRETURN SQLExecDirect(
           SQLCHAR *statementText,      // IN
           SQLINTEGER textLength);      // IN

        SQLRETURN SQLSetStmtAttr(
           SQLINTEGER Option,           //IN
           SQLPOINTER Value,            //IN
           SQLINTEGER stringLength);    //IN

        SQLRETURN SQLFetch();
        
        SQLRETURN SQLCloseCursor();

        SQLRETURN SQLSetCursorName(
            SQLCHAR *cursorName,        // IN
            SQLSMALLINT nameLength);    // OUT

        SQLRETURN SQLGetCursorName(
            SQLCHAR *cursorName,        // OUT
            SQLSMALLINT bufferLength,   // IN
            SQLSMALLINT *nameLength);   // OUT
        
        SQLRETURN SQLNumResultCols(
            SQLSMALLINT *columnCount);  // OUT

        SQLRETURN SQLRowCount(
            SQLINTEGER *rowCount);      // OUT

        SQLRETURN SQLDescribeCol(
            SQLUSMALLINT columnNumber,  // IN 
            SQLCHAR      *columnName,   // OUT
            SQLSMALLINT  bufferLength,  // IN
            SQLSMALLINT  *nameLength,   // OUT
            SQLSMALLINT  *dataType,     // OUT
            SQLUINTEGER  *columnSize,   // OUT
            SQLSMALLINT  *decimalDigits,// OUT
            SQLSMALLINT  *nullable);    // OUT

        SQLRETURN  SQLColAttribute(
            SQLUSMALLINT columnNumber,      //IN
            SQLUSMALLINT fieldIdentifier,//IN
            SQLPOINTER   characterAttributePtr,//OUT
            SQLSMALLINT  bufferLength,       //IN
            SQLSMALLINT *stringLengthPtr, //OUT
            SQLPOINTER numericAttributePtr); //OUT

        SQLRETURN SQLNumParams(
                SQLSMALLINT *     ParameterCountPtr); //OUT

        SQLRETURN SQLDescribeParam(
                SQLUSMALLINT     paramNumber, //IN
                SQLSMALLINT *     dataType,       //OUT
                SQLUINTEGER *     paramSize,  //OUT
                SQLSMALLINT *     decimalDigits,  //OUT
                SQLSMALLINT *     isNullable);    //OUT

    // Other Methods
        void resetStmt( void );
};

#endif // _ODBC_STMT_H_
