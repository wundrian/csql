#include "odbcCommon.h"

SQLRETURN SQLAllocHandle( SQLSMALLINT hdlType, 
			  SQLHANDLE inHdl, 
			  SQLHANDLE *outHdl )
{
    switch( hdlType )
    {
        case SQL_HANDLE_ENV: 
		return CSqlOdbcEnv::SQLAllocHandle( inHdl, outHdl );
        case SQL_HANDLE_DBC: 
		return CSqlOdbcDbc::SQLAllocHandle( inHdl, outHdl );
        case SQL_HANDLE_STMT: 
		return CSqlOdbcStmt::SQLAllocHandle( inHdl, outHdl );
    }

    globalError.set( ERROR_OPTRANGE );
    globalError.printStr( SQL_OV_ODBC3 );
    return( SQL_ERROR );
}

SQLRETURN SQLFreeHandle(
    SQLSMALLINT hdlType,
    SQLHANDLE   inHdl)
{
    switch( hdlType )
    {
        case SQL_HANDLE_ENV: return CSqlOdbcEnv::SQLFreeHandle( inHdl );
        case SQL_HANDLE_DBC: return CSqlOdbcDbc::SQLFreeHandle( inHdl );
        case SQL_HANDLE_STMT: return CSqlOdbcStmt::SQLFreeHandle( inHdl );
    }

    globalError.set( ERROR_OPTRANGE );
    globalError.printStr( SQL_OV_ODBC3 );
    return( SQL_ERROR );
}

SQLRETURN SQLEndTran(
    SQLSMALLINT hdlType, 
    SQLHANDLE hdl,
    SQLSMALLINT compType)
{
    if( isValidHandle( hdl, hdlType ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    switch( hdlType )
    {
        case SQL_HANDLE_ENV:
                return ((CSqlOdbcEnv*) hdl)->SQLEndTran( compType );
        case SQL_HANDLE_DBC:
                return ((CSqlOdbcDbc*) hdl)->SQLEndTran( compType );
    }

    globalError.set( ERROR_OPTRANGE );
    globalError.printStr( SQL_OV_ODBC3 );
    return( SQL_ERROR );
}

SQLRETURN isValidHandle( SQLHANDLE hdl,
    SQLSMALLINT hdlType)
{
    if( hdlType == SQL_HANDLE_ENV || hdlType == SQL_HANDLE_DBC || hdlType == SQL_HANDLE_STMT )

        if( hdl != 0 )
            if( ((CSqlOdbcEnv*) hdl)->handleType_ == hdlType )
                return( SQL_SUCCESS );

    globalError.set( ERROR_MEM_MGMNT );
    globalError.printStr( SQL_OV_ODBC3 );
    return( SQL_INVALID_HANDLE );
}

SQLRETURN isValidCType( SQLSMALLINT type )
{
    switch( type )
    {
        case SQL_C_CHAR:
        case SQL_C_SLONG:
        case SQL_C_ULONG:
        case SQL_C_LONG:
        case SQL_C_FLOAT:
        case SQL_C_DOUBLE:
        case SQL_C_BIT:
        case SQL_C_SSHORT:
        case SQL_C_USHORT:
        case SQL_C_SHORT:
        case SQL_C_STINYINT:
        case SQL_C_UTINYINT:
        case SQL_C_TINYINT:
        case SQL_C_SBIGINT:
        case SQL_C_UBIGINT:
        case SQL_C_NUMERIC:
        case SQL_C_DATE:
        case SQL_C_TIME:
        case SQL_C_TIMESTAMP:
        case SQL_C_TYPE_DATE:
        case SQL_C_TYPE_TIME:
        case SQL_C_TYPE_TIMESTAMP:
        case SQL_C_BINARY: break;
        default: return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}

SQLRETURN isValidSQLType( SQLSMALLINT type )
{
    switch( type )
    {
        case SQL_CHAR:
        case SQL_VARCHAR:
        case SQL_BIT:
        case SQL_SMALLINT:
        case SQL_INTEGER:
        case SQL_REAL:
        case SQL_DOUBLE:
        case SQL_FLOAT:
        case SQL_TINYINT:
        case SQL_BIGINT:
        case SQL_DECIMAL:
        case SQL_NUMERIC:
        case SQL_DATE:
        case SQL_TIME:
        case SQL_TIMESTAMP:
        case SQL_TYPE_DATE:
        case SQL_TYPE_TIME:
        case SQL_TYPE_TIMESTAMP:
        case SQL_BINARY:
        case SQL_VARBINARY: break;
        default: return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}

DataType getCSqlType( SQLSMALLINT type )
{
    switch( type )
    {
        case SQL_C_CHAR:
            return typeString;
        case SQL_C_LONG:
        case SQL_C_SLONG:
        case SQL_C_ULONG:
            return typeLong;
        case SQL_C_FLOAT:
            return typeFloat;
        case SQL_C_DOUBLE:
            return typeDouble;
        case SQL_C_BIT:
            return typeUnknown;
        case SQL_C_SHORT:
        case SQL_C_SSHORT:
        case SQL_C_USHORT:
            return typeShort;
        case SQL_C_TINYINT:
        case SQL_C_STINYINT:
        case SQL_C_UTINYINT:
            return typeByteInt;
        case SQL_C_SBIGINT:
        case SQL_C_UBIGINT:
            return typeLongLong;
        case SQL_C_NUMERIC:
            return typeDecimal;
        case SQL_C_DATE:
        case SQL_C_TYPE_DATE:
            return typeDate;
        case SQL_C_TIME:
        case SQL_C_TYPE_TIME:
            return typeTime;
        case SQL_C_TIMESTAMP:
        case SQL_C_TYPE_TIMESTAMP: 
            return typeTimeStamp;
            break;
	case SQL_C_BINARY:
	    return typeBinary;
        default: return( typeUnknown);
    }
}

SQLSMALLINT  getSQLType( DataType type )
{
    switch(type)
    {
        case typeShort:
            return SQL_SMALLINT;
        case typeInt:
        case typeLong:
            return SQL_INTEGER;
        case typeLongLong:
            return SQL_BIGINT;
        case typeByteInt:
            return SQL_TINYINT;

        case typeFloat:
            return SQL_FLOAT;
        case typeDouble:
            return SQL_DOUBLE;
        case typeDecimal:
            return SQL_NUMERIC;

        case typeDate:
            return SQL_DATE;
        case typeTime:
            return SQL_TIME;
        case typeTimeStamp:
            return SQL_TIMESTAMP;

        case typeString:
            return SQL_CHAR;
        case typeBinary:
            return SQL_BINARY;

	// NOT SUPPORTED
        //case csqlSqlTlongDouble: might be equal typeDecimal
        //    return SQL_REAL;
        //case csqlSqlTvarString:
        //    return SQL_VARCHAR;
        //case csqlSqlTvarBinary:
        //    return SQL_BINARY;
        //case typeBit: 
        //    return SQL_BIT;
        default:
            return SQL_ERROR;
            break;
    }
}

SQLCHAR *getSQLTypeName( SQLSMALLINT type )
{
    switch( type )
    {
        case SQL_CHAR:
            return (SQLCHAR *)"CHAR";
        case SQL_VARCHAR:
            return (SQLCHAR *)"VARCHAR";
        case SQL_BIT:
            return (SQLCHAR *)"BIT";
        case SQL_SMALLINT:
            return (SQLCHAR *)"SMALLINT";
        case SQL_INTEGER:
            return (SQLCHAR *)"INTEGER";
        case SQL_REAL:
            return (SQLCHAR *)"REAL";
        case SQL_DECIMAL:
        case SQL_NUMERIC:
            return (SQLCHAR *)"NUMERIC";
        case SQL_DOUBLE:
            return (SQLCHAR *)"DOUBLE";
        case SQL_FLOAT:
            return (SQLCHAR *)"FLOAT";
        case SQL_TINYINT:
            return (SQLCHAR *)"TINYINT";
        case SQL_BIGINT:
            return (SQLCHAR *)"BIGINT";
        case SQL_DATE:
        case SQL_TYPE_DATE:
            return (SQLCHAR *)"DATE";
        case SQL_TIME:
        case SQL_TYPE_TIME:
            return (SQLCHAR *)"TIME";
        case SQL_TIMESTAMP:
        case SQL_TYPE_TIMESTAMP: 
            return (SQLCHAR *)"TIMESTAMP";
	    case SQL_BINARY:
            return (SQLCHAR *)"BINARY";
        default:
            break;
    }
}

void getInputBuffer(void **buffer,SQLSMALLINT type,SQLUINTEGER length)
{
    switch(type)
    {
        case typeShort:
            *buffer = new short();
            break;
        case typeInt:
            *buffer= new int();
            break;
        case typeLong:
            *buffer= new long();
            break;
        case typeLongLong:
            *buffer = new long long();
            break;
        case typeByteInt:
            *buffer = new signed char();
            break;
/*        case csqlSqlTbit:
            *buffer = new unsigned char ();
            break;*/

        case typeFloat:
            *buffer = new float();
            break;
        case typeDouble:
            *buffer = new double();
            break;
        case typeDecimal:
//        case csqlSqlTlongDouble:
//        case csqlSqlTnumeric:
            *buffer = new long double ();
            break;

        case typeString:
//        case csqlSqlTvarString:
            *buffer = new char [length+1];
            break;
        case typeDate:
            *buffer = new Date();
            break;
        case typeTime:
            *buffer = new Time();
            break;
        case typeTimeStamp:
            *buffer = new TimeStamp();
            break;
        case typeBinary:
//        case csqlSqlTvarBinary:                        
            *buffer = new unsigned char [length+1];
            break;
    }
}

// CSQL TODO - Need to review and finalize.
//Copies data from the application onto the destination 
//Called from SQLExecute
//Destination here can be directly the database bound buffer or 
//it may be ird
void copyFromOdbc(void *destData,SQLUINTEGER destLen,void *odbcData,SQLUINTEGER odbcLen,SQLSMALLINT type)
{
    //No point in continuing further
    if(destData == NULL || odbcData == NULL)
        return;
    switch( type )
    {
        case typeShort:
            *(short*)destData = *(short*)odbcData;
printf("short value is %x %hd\n", destData, *(short*)odbcData);
            break;
        case typeInt:
            *(int*)destData = *(int*)odbcData;
            break;
        case typeLong:
            *(long*)destData = *(long*)odbcData;
            break;
        case typeLongLong:
            *(long long*)destData = *(long long*)odbcData;
            break;
        case typeByteInt:
            *(char*)destData = *(char*)odbcData;
            break;
/*        case csqlSqlTbit:
            *(unsigned char*)destData = *(unsigned char*)odbcData;
            break;*/

        case typeFloat:
            *(float*)destData = *(float*)odbcData;
            break;

        case typeDouble:
            *(double*)destData = *(double*)odbcData;
            break;

//        case csqlSqlTlongDouble:
//        case csqlSqlTnumeric:
        case typeDecimal:
            *(long double*)destData = *(long double*)odbcData;
            break;


        case typeString:
//        case csqlSqlTvarString:
            if(odbcLen < destLen)
            {
                strcpy( (char*)destData, (char*)odbcData);
                *((char*)destData+odbcLen)='\0';
            }
            else
            {
                strncpy((char*)destData,(char*)odbcData,(destLen-1));
                *((char*)destData+destLen)='\0';
            }
            
            break;
        case typeDate:
            (*(Date *)destData).set((*(SQL_DATE_STRUCT *)odbcData).year,
                                                                     (*(SQL_DATE_STRUCT *)odbcData).month,
                                                                     (*(SQL_DATE_STRUCT *)odbcData).day);
            break;
        case typeTime:
            (*(Time *)destData).set((*(SQL_TIME_STRUCT *)odbcData).hour,
                                                                     (*(SQL_TIME_STRUCT *)odbcData).minute,
                                                                     (*(SQL_TIME_STRUCT *)odbcData).second);
            break;
        case typeTimeStamp:
            (*(TimeStamp *)destData).setDate((*(SQL_TIMESTAMP_STRUCT *)odbcData).year,
                                                                              (*(SQL_TIMESTAMP_STRUCT *)odbcData).month,
                                                                              (*(SQL_TIMESTAMP_STRUCT *)odbcData).day);
            (*(TimeStamp *)destData).setTime((*(SQL_TIMESTAMP_STRUCT*)odbcData).hour,
                                                                              (*(SQL_TIMESTAMP_STRUCT *)odbcData).minute,
                                                                              (*(SQL_TIMESTAMP_STRUCT *)odbcData).second);

            break;
        case typeBinary:
//        case csqlSqlTvarBinary:                        
 //            memset((unsigned char*)destData,0,destLen);
            if(odbcLen <= destLen)
            {
                memcpy( (unsigned char*)destData,(unsigned char*)odbcData, 
                    odbcLen);
            }
            else
            {
                memcpy( (unsigned char*)destData,(unsigned char*)odbcData, 
                    (destLen));
            }
            break;
    }
}

//Copies data from the database onto the application buffer 
//Called from SQLFetch
//Destination here can be the actual application buffer or
//it may be ipd_
SQLINTEGER copyToOdbc(void *odbcData,SQLUINTEGER odbcLen,void *sourceData,SQLUINTEGER sourceLen,SQLSMALLINT type)
{
    SQLINTEGER ind;
    //No point in continuing
    if(odbcData == NULL || sourceData == NULL)
        return -1;
    switch( type )
    {
        case typeShort:
            *(short*)odbcData = *(short*)sourceData;
            break;

        case typeInt:
            *(int*)odbcData = *(int*)sourceData;
            break;

        case typeLong:
            *(long*)odbcData = *(long*)sourceData;
            break;

        case typeLongLong:
            *(long long*)odbcData = *(long long*)sourceData;
            break;

        case typeByteInt:
            *(char*)odbcData = *(char*)sourceData;
            break;

//        case csqlSqlTbit:
//            CSqlOdbcError::printDbg("copyToOdbc");
//            *(unsigned char*)odbcData = *(unsigned char*)sourceData;
//            break;

        case typeFloat:
            *(float*)odbcData = *(float*)sourceData;
            break;
        case typeDouble:
            *(double*)odbcData = *(double*)sourceData;
            break;
        case typeDecimal:

//        case csqlSqlTlongDouble:
//        case csqlSqlTnumeric:
            *(long double*)odbcData = *(long double*)sourceData;
            break;
        case typeString:
//      case csqlSqlTvarString:
            if(sourceLen < odbcLen)
            {
                strcpy((char*)odbcData,(char*)sourceData);
                ind=strlen((char*)odbcData)+1;
            }
            else
            {
                strncpy((char*)odbcData,(char*)sourceData ,odbcLen);
                ind=odbcLen;
            }
            *((char *)odbcData+ind-1)='\0';
            break;
        case typeDate:
            (*(SQL_DATE_STRUCT *)odbcData).year = (*(Date *)sourceData).year();
            (*(SQL_DATE_STRUCT *)odbcData).month= (*(Date *)sourceData).month();
            (*(SQL_DATE_STRUCT *)odbcData).day = (*(Date *)sourceData).dayOfMonth();
            break;
        case typeTime:                        
            (*(SQL_TIME_STRUCT *)odbcData).hour = (*(Time *)sourceData).hours();
            (*(SQL_TIME_STRUCT *)odbcData).minute= (*(Time *)sourceData).minutes();
            (*(SQL_TIME_STRUCT *)odbcData).second = (*(Time *)sourceData).seconds();
            break;
        case typeTimeStamp:                        
            (*(SQL_TIMESTAMP_STRUCT *)odbcData).year= (*(TimeStamp *)sourceData).year();
            (*(SQL_TIMESTAMP_STRUCT *)odbcData).month= (*(TimeStamp *)sourceData).month();
            (*(SQL_TIMESTAMP_STRUCT *)odbcData).day= (*(TimeStamp *)sourceData).dayOfMonth();
            (*(SQL_TIMESTAMP_STRUCT *)odbcData).hour = (*(TimeStamp *)sourceData).hours();
            (*(SQL_TIMESTAMP_STRUCT *)odbcData).minute= (*(TimeStamp *)sourceData).minutes();
            (*(SQL_TIMESTAMP_STRUCT *)odbcData).second = (*(TimeStamp *)sourceData).seconds();
            break;
        case typeBinary:
//        case csqlSqlTvarBinary:                        
//            CSqlOdbcError::printDbg("copyToOdbc");
//            memset((unsigned char*)odbcData,0,odbcLen);
            if(sourceLen < odbcLen)
            {
                memcpy( (unsigned char*)odbcData , (unsigned char*)sourceData,sourceLen);
                ind=sourceLen;
            }
            else
            {
                memcpy( (unsigned char*)odbcData , (unsigned char*)sourceData,odbcLen);
                ind=odbcLen;
            }
            break;
    }
    return ind;
}
