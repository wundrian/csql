#ifndef _ODBC_ERROR_H_
#define _ODBC_ERROR_H_

class CSqlOdbcError
{
        CSqlOdbcError( void );     

    public:
        // This object belongs to.
        int    hdlType; 

	// SQLAPI specific err code.
        SQLINTEGER    csqlErrCode;

        // ODBC Methods
        SQLRETURN SQLGetDiagRec(
            SQLHANDLE    hdl,
            SQLCHAR      *sqlState,
            SQLINTEGER   *csqlErrCode,
            SQLCHAR      *Msg,
            SQLSMALLINT  bufLen,
            SQLSMALLINT  *textLen);

        // Other Methods
        CSqlOdbcError( long hdlType );
        void set( long err );
        SQLRETURN printStr( SQLUINTEGER odbcVersion ); 
	// Print diagnostic info to 'stderr'
        static void printDbg( char *msg );
};

extern CSqlOdbcError globalError;

typedef struct ErrorDetails
{
    public:
        int         csqlErrCode;
        SQLCHAR     *sqlState;
        SQLCHAR     *sqlMessage;
} ErrorInfo_t;

// Native Error Codes
#define NO_ERR                      -0L
#define ERROR_GEN_WARN              -1L
#define ERROR_GENERAL               -2L
#define ERROR_OPTFEATURE_NOTIMP     -3L

//Connection Related
#define ERROR_HOSTNAME              -4L
#define ERROR_PORTNO                -5L
#define ERROR_CONNREJCTD            -6L
#define ERROR_INVAUTHSPEC           -7L
#define ERROR_CONN_TIMEOUT_EXP      -8L
#define ERROR_DESTIP_REJ            -9L
#define ERROR_SRCIP_REJ             -10L
#define ERROR_CONNINUSE             -11L
#define ERROR_CONNOTOPEN            -12L
#define ERROR_NOTOPENED             -13L

//Transaction Related
#define ERROR_INVTRANSTATE          -14L
#define ERROR_TRANROLLBACK          -15L

//Statement Related
#define ERROR_SCHNOTFOUND           -16L
#define ERROR_TBLNOTFOUND           -17L
#define ERROR_NO_COLEXISTS          -18L
#define ERROR_NO_IDXEXISTS          -19L

#define ERROR_TBLEXISTS             -20L
#define ERROR_COLEXISTS             -21L
#define ERROR_IDXEXISTS             -22L

#define ERROR_MANY_VALS             -23L
#define ERROR_FEW_VALS              -24L
#define ERROR_SQL_SYNTAX            -25L
#define ERROR_TYPE_INCMP            -26L
#define ERROR_DATA_FORMAT           -27L
#define ERROR_DUP_COL               -28L

#define ERROR_SQL_INT               -29L
#define ERROR_OVERFLOW              -30L
#define ERROR_UNDERFLOW             -31L
#define ERROR_MANY_TUP              -32L
#define ERROR_NUM_PROJ              -33L

#define ERROR_DATATRUNC             -34L
#define ERROR_BUFLEN                -35L
#define ERROR_COLNUM                -36L
#define ERROR_INVBUFTYPE            -37L
#define ERROR_INV_PARAMTYPE         -38L
#define ERROR_INVARGVAL             -39L

#define ERROR_CURNAME               -40L
#define ERROR_DUP_CURNAME           -41L
#define ERROR_NOCURNAME             -42L
#define ERROR_PARAMNUM              -43L
 
//Memory Related
#define ERROR_MEM_MGMNT             -44L
#define ERROR_MEMALLOC              -45L

//DBC Related
#define ERROR_OPTRANGE              -46L
#define ERROR_OPTCHANGE             -47L
#define ERROR_FUNCSEQ               -48L
#define ERROR_ATTR_CANNOT_SET       -49L
#define ERROR_INVCURSTATE           -50L
#define ERROR_NOT_PREPAREDSTMT      -51L

//CREAT TABLE
#define ERROR_STORAGE_ATTR          -53L
#define ERROR_FLDCNT_MISMATCH       -54L
#define ERROR_MATCHKEY_NOTFOUND     -55L

#define ERROR_ENDOFTABLE            -56L

static ErrorInfo_t  errorInfoTable_3x [] = 
{
    { NO_ERR, (SQLCHAR *)("00000"), (SQLCHAR *)("Success") },

    { ERROR_GEN_WARN,(SQLCHAR *)("01000"),(SQLCHAR *)("General Warning")},

    { ERROR_GENERAL,(SQLCHAR *)("HY000"), (SQLCHAR *)("General Error3") },

    { ERROR_OPTFEATURE_NOTIMP,(SQLCHAR *)("HYC00"), (SQLCHAR *)("Optional feature not implemented") },
    
    { ERROR_HOSTNAME,(SQLCHAR *)("SC002"), (SQLCHAR *)("Hostname must be specified") },

    { ERROR_PORTNO,(SQLCHAR *)("SC003"), (SQLCHAR *)("Port number must be specified") },

    { ERROR_CONNREJCTD, (SQLCHAR *)("08006"), (SQLCHAR *)("Server rejected the connection") },

    { ERROR_INVAUTHSPEC,(SQLCHAR *)("28000"), (SQLCHAR *)("Invalid authorization specification") },

    { ERROR_CONN_TIMEOUT_EXP,(SQLCHAR *)("SC001"), (SQLCHAR *)("Connection timeout expired") },

    { ERROR_DESTIP_REJ,(SQLCHAR *)("08004"), (SQLCHAR *)("IPFilter: Destination IP validation failed.") },

    { ERROR_SRCIP_REJ, (SQLCHAR *)("08005"), (SQLCHAR *)("IPFilter: Source IP validation failed.") },

    { ERROR_CONNINUSE,(SQLCHAR *)("08001"), (SQLCHAR *)("Connection name in use") },

    { ERROR_CONNOTOPEN,(SQLCHAR *)("08003"), (SQLCHAR *)("Connection does not exist") },

    { ERROR_NOTOPENED,(SQLCHAR *)("08002"), (SQLCHAR *)("Connection does not exist") },

    { ERROR_INVTRANSTATE,(SQLCHAR *)("TR005"), (SQLCHAR *)("Invalid transaction state") },

    { ERROR_TRANROLLBACK,(SQLCHAR *)("25002"), (SQLCHAR *)("Transaction is rolled back") },

    { ERROR_SCHNOTFOUND,(SQLCHAR *)("3F000"), (SQLCHAR *)("Schema not found.") },

    { ERROR_TBLNOTFOUND, (SQLCHAR *)("42S02"), (SQLCHAR *)("Base Table or view not found") },

    { ERROR_NO_COLEXISTS,(SQLCHAR *)("42S22"), (SQLCHAR *)("Column not found ") },

    { ERROR_NO_IDXEXISTS,(SQLCHAR *)("42S12"), (SQLCHAR *)("Index not found ") },

    { ERROR_TBLEXISTS,(SQLCHAR *)("42S01"), (SQLCHAR *)("Base Table or view already exists") },

    { ERROR_COLEXISTS,(SQLCHAR *)("42S21"), (SQLCHAR *)("Column already exists ") },

    { ERROR_IDXEXISTS,(SQLCHAR *)("42S11"), (SQLCHAR *)("Index already exists") },

    { ERROR_MANY_VALS,(SQLCHAR *)("ST018"), (SQLCHAR *)("Too many values supplied in insert statement") },

    { ERROR_FEW_VALS, (SQLCHAR *)("ST019"), (SQLCHAR *)("Too few values supplied in insert statement") },
    
    { ERROR_SQL_SYNTAX,(SQLCHAR *)("ST026"), (SQLCHAR *)("Syntax error.") },

    { ERROR_TYPE_INCMP,(SQLCHAR *)("ST020"), (SQLCHAR *)("In-Compatible column value") },

    { ERROR_DATA_FORMAT,(SQLCHAR *)("ST021"), (SQLCHAR *)("Invalid value/format") },
    
    { ERROR_DUP_COL,(SQLCHAR *)("ST024"), (SQLCHAR *)("Duplicate field names") },

    { ERROR_SQL_INT,(SQLCHAR *)("ST025"), (SQLCHAR *)("SQL internal error") },

    { ERROR_OVERFLOW,(SQLCHAR *)("ST023"), (SQLCHAR *)("Underflow error") },

    { ERROR_UNDERFLOW,(SQLCHAR *)("ST022"), (SQLCHAR *)("Overflow error") },

    { ERROR_MANY_TUP,(SQLCHAR *)("ST027"), (SQLCHAR *)("Sub query returns multiple rows") },

    { ERROR_NUM_PROJ,(SQLCHAR *)("ST028"), (SQLCHAR *)("Wrong number of projections from sub query") },

    { ERROR_DATATRUNC,(SQLCHAR *)("01004"), (SQLCHAR *)("String data,right truncated") },

    { ERROR_BUFLEN,(SQLCHAR *)("HY090"), (SQLCHAR *)("Invalid string or buffer length") },

    { ERROR_COLNUM,(SQLCHAR *)("07009"), (SQLCHAR *)("Invalid descriptor index") },

    { ERROR_INVBUFTYPE,(SQLCHAR *)("HY003"), (SQLCHAR *)("Invalid application buffer type") },

    { ERROR_INV_PARAMTYPE,(SQLCHAR *)("HY105"), (SQLCHAR *)("Invalid parameter type") },

    { ERROR_INVARGVAL,(SQLCHAR *)("HY024"), (SQLCHAR *)("Invalid attribute value") },

    { ERROR_CURNAME,(SQLCHAR *)("34000"), (SQLCHAR *)("Invalid cursor name") },

    { ERROR_DUP_CURNAME,(SQLCHAR *)("3C000"), (SQLCHAR *)("Duplicate cursor name") },

    { ERROR_NOCURNAME,(SQLCHAR *)("HY015"), (SQLCHAR *)("No cursor name available") },

    { ERROR_PARAMNUM,(SQLCHAR *)("07009"), (SQLCHAR *)("Invalid descriptor index") },

    { ERROR_MEM_MGMNT,(SQLCHAR *)("HY013"), (SQLCHAR *)("Memory management error ") },

    { ERROR_MEMALLOC, (SQLCHAR *)("HY001"), (SQLCHAR *)("Memory Allocation Failure") },

    { ERROR_OPTRANGE,(SQLCHAR *)("HY092"), (SQLCHAR *)("Invalid attribute /option identifier") },

    { ERROR_OPTCHANGE,(SQLCHAR *)("01S02"), (SQLCHAR *)("Option value changed")},

    { ERROR_FUNCSEQ,(SQLCHAR *)("HY010"), (SQLCHAR *)("Function Sequence Error") },

    { ERROR_ATTR_CANNOT_SET,(SQLCHAR *)("HY011"), (SQLCHAR *)("Attribute cannot be set now ") },

    { ERROR_INVCURSTATE,(SQLCHAR *)("24000"), (SQLCHAR *)("Invalid cursor state") },

    { ERROR_NOT_PREPAREDSTMT,(SQLCHAR *)("HY007"), (SQLCHAR *)("Associated statement is not prepared")},

    { ERROR_STORAGE_ATTR,(SQLCHAR *)("ST029"), (SQLCHAR *)("Error while parsing storage attribute")},

    { ERROR_FLDCNT_MISMATCH,(SQLCHAR *)("ST030"), (SQLCHAR *)("Error while creating RIC, specified in to-from table are different")},

    { ERROR_ENDOFTABLE,(SQLCHAR *)("IM015"), (SQLCHAR *)("End of table") }
};

static ErrorInfo_t  errorInfoTable_2x [] = 
{
    { NO_ERR, (SQLCHAR *)("00000"), (SQLCHAR *)("Success") },

    { ERROR_GEN_WARN, (SQLCHAR *)("01000"),(SQLCHAR *)("General Warning")},

    { ERROR_GENERAL, (SQLCHAR *)("S1000"), (SQLCHAR *)("General Error") },

    { ERROR_OPTFEATURE_NOTIMP, (SQLCHAR *)("S1C00"), (SQLCHAR *)("Optional feature not implemented") },
    
    { ERROR_HOSTNAME, (SQLCHAR *)("HY000"), (SQLCHAR *)("Hostname must be specified") },

    { ERROR_PORTNO, (SQLCHAR *)("HY000"), (SQLCHAR *)("Port number must be specified") },

    { ERROR_CONNREJCTD, (SQLCHAR *)("08004"), (SQLCHAR *)("Data source rejected establishment of connection") },

    { ERROR_INVAUTHSPEC,(SQLCHAR *)("28000"), (SQLCHAR *)("Invalid authorization specification") },

    { ERROR_CONN_TIMEOUT_EXP,(SQLCHAR *)("S1T01"), (SQLCHAR *)("Connection timeout expired") },

    { ERROR_DESTIP_REJ,(SQLCHAR *)("08004"), (SQLCHAR *)("IPFilter: Destination IP validation failed.") },

    { ERROR_SRCIP_REJ, (SQLCHAR *)("08005"), (SQLCHAR *)("IPFilter: Source IP validation failed.") },

    { ERROR_CONNINUSE,(SQLCHAR *)("08002"), (SQLCHAR *)("Connection in use") },

    { ERROR_CONNOTOPEN,(SQLCHAR *)("08003"), (SQLCHAR *)("Connection  not open") },

    { ERROR_NOTOPENED, (SQLCHAR *)("08003"), (SQLCHAR *)("Connection not open") },

    { ERROR_INVTRANSTATE,(SQLCHAR *)("25000"), (SQLCHAR *)("Invalid transaction state") },

    { ERROR_TRANROLLBACK,(SQLCHAR *)("25S03"), (SQLCHAR *)("Transaction is rolled back") },

    { ERROR_SCHNOTFOUND,(SQLCHAR *)("3F000"), (SQLCHAR *)("Schema not found.") },

    { ERROR_TBLNOTFOUND,(SQLCHAR *)("S0002"), (SQLCHAR *)("Base Table or view not found") },

    { ERROR_NO_COLEXISTS,(SQLCHAR *)("S0022"), (SQLCHAR *)("Column not found ") },

    { ERROR_NO_IDXEXISTS,(SQLCHAR *)("42S12"), (SQLCHAR *)("Index not found ") },

    { ERROR_TBLEXISTS,(SQLCHAR *)("S0001"), (SQLCHAR *)("Base Table or view already exists") },
    
    { ERROR_COLEXISTS,(SQLCHAR *)("S0021"), (SQLCHAR *)("Column already exists ") },

    { ERROR_IDXEXISTS,(SQLCHAR *)("S0011"), (SQLCHAR *)("Index already exists") },

    { ERROR_MANY_VALS,(SQLCHAR *)("ST018"), (SQLCHAR *)("Too many values supplied in insert statement") },

    { ERROR_FEW_VALS,(SQLCHAR *)("ST019"), (SQLCHAR *)("Too few values supplied in insert statement") },
    
    { ERROR_SQL_SYNTAX,(SQLCHAR *)("ST026"), (SQLCHAR *)("Syntax error.") },

    { ERROR_TYPE_INCMP,(SQLCHAR *)("ST020"), (SQLCHAR *)("In-Compatible column value") },

    { ERROR_DATA_FORMAT,(SQLCHAR *)("ST021"), (SQLCHAR *)("Invalid value/format") },
    
    { ERROR_DUP_COL,(SQLCHAR *)("ST024"), (SQLCHAR *)("Duplicate field names") },

    { ERROR_SQL_INT,(SQLCHAR *)("ST025"), (SQLCHAR *)("SQL internal error") },

    { ERROR_OVERFLOW,(SQLCHAR *)("ST023"), (SQLCHAR *)("Underflow error") },

    { ERROR_UNDERFLOW,(SQLCHAR *)("ST022"), (SQLCHAR *)("Overflow error") },

    { ERROR_MANY_TUP,(SQLCHAR *)("ST027"), (SQLCHAR *)("Sub query returns multiple rows") },

    { ERROR_NUM_PROJ,(SQLCHAR *)("ST028"), (SQLCHAR *)("Wrong number of projections from sub query") },

    { ERROR_DATATRUNC,(SQLCHAR *)("01004"), (SQLCHAR *)("String data,right truncated") },

    { ERROR_BUFLEN,(SQLCHAR *)("S1090"), (SQLCHAR *)("Invalid string or buffer length") },

    { ERROR_COLNUM, (SQLCHAR *)("S1000"), (SQLCHAR *)("Invalid column number") },

    { ERROR_INVBUFTYPE,(SQLCHAR *)("S1003"), (SQLCHAR *)("Invalid application buffer type") },

    { ERROR_INV_PARAMTYPE,(SQLCHAR *)("S1105"), (SQLCHAR *)("Invalid parameter type") },

    { ERROR_INVARGVAL,(SQLCHAR *)("S1009"), (SQLCHAR *)("Invalid argument value") },

    { ERROR_CURNAME,(SQLCHAR *)("34000"), (SQLCHAR *)("Invalid cursor name") },

    { ERROR_DUP_CURNAME,(SQLCHAR *)("3C000"), (SQLCHAR *)("Duplicate cursor name") },

    { ERROR_NOCURNAME,(SQLCHAR *)("S1015"), (SQLCHAR *)("No cursor name available") },

    { ERROR_PARAMNUM,(SQLCHAR *)("S1093"), (SQLCHAR *)("Invalid parameter number") },

    { ERROR_MEM_MGMNT,(SQLCHAR *)("S1013"), (SQLCHAR *)("Memory management error ") },

    { ERROR_MEMALLOC,(SQLCHAR *)("S1001"), (SQLCHAR *)("Memory Allocation Failure") },

    { ERROR_OPTRANGE,(SQLCHAR *)("S1092"), (SQLCHAR *)("Option type out of range") },

    { ERROR_OPTCHANGE,(SQLCHAR *)("01S02"), (SQLCHAR *)("Option value changed")},

    { ERROR_FUNCSEQ,(SQLCHAR *)("S1010"), (SQLCHAR *)("Function Sequence Error") },

    { ERROR_ATTR_CANNOT_SET,(SQLCHAR *)("S1011"), (SQLCHAR *)("Attribute cannot be set now ") },

    { ERROR_INVCURSTATE, (SQLCHAR *)("24000"), (SQLCHAR *)("Invalid cursor state") },

    { ERROR_NOT_PREPAREDSTMT, (SQLCHAR *)("S1010"), (SQLCHAR *)("Associated statement is not prepared")},

    { ERROR_STORAGE_ATTR,(SQLCHAR *)("ST029"), (SQLCHAR *)("Error while parsing storage attribute")},

    { ERROR_FLDCNT_MISMATCH,(SQLCHAR *)("ST030"), (SQLCHAR *)("Error while creating RIC, specified in to-from table are different")},

    { ERROR_MATCHKEY_NOTFOUND,(SQLCHAR *) ("ST031"), (SQLCHAR *) ("Referenced key is not Primary/Unique")},

    { ERROR_ENDOFTABLE,(SQLCHAR *)("IM015"), (SQLCHAR *)("End of table") }
};

#endif
