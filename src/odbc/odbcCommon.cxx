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
            return typeInt;
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
void copyFromOdbc(AbsSqlStatement *stmt, int paramNo, SQLUINTEGER destLen,void *odbcData,SQLUINTEGER odbcLen,SQLSMALLINT type)
{
    //No point in continuing further
    if(odbcData == NULL)
        return;
    switch( type )
    {
        case typeShort:
            //*(short*)destData = *(short*)odbcData;
            stmt->setShortParam(paramNo, *(short*)odbcData);
            break;
        case typeInt:
            //*(int*)destData = *(int*)odbcData;
            stmt->setIntParam(paramNo, *(int*)odbcData);
            break;
        case typeLong:
            //*(long*)destData = *(long*)odbcData;
            stmt->setLongParam(paramNo, *(long*)odbcData);
            break;
        case typeLongLong:
            //*(long long*)destData = *(long long*)odbcData;
            stmt->setLongLongParam(paramNo, *(long long *)odbcData);
            break;
        case typeByteInt: {
            //*(char*)destData = *(char*)odbcData;
            ByteInt bt(*(char*)odbcData);
             stmt->setByteIntParam(paramNo, bt);
            break;
        }
/*        case csqlSqlTbit:
            *(unsigned char*)destData = *(unsigned char*)odbcData;
            break;*/

        case typeFloat:
            //*(float*)destData = *(float*)odbcData;
            stmt->setFloatParam(paramNo, *(float*)odbcData);
            break;

        case typeDouble:
            //*(double*)destData = *(double*)odbcData;
            stmt->setDoubleParam(paramNo, *(double*)odbcData);
            break;

//        case csqlSqlTlongDouble:
//        case csqlSqlTnumeric:
        case typeDecimal:
            //*(long double*)destData = *(long double*)odbcData;
            // TODO
            break;

        case typeString:
            stmt->setStringParam(paramNo, (char*) odbcData);
            /*if(odbcLen < destLen)
            {
                strcpy( (char*)destData, (char*)odbcData);
                *((char*)destData+odbcLen)='\0';
            }
            else
            {
                strncpy((char*)destData,(char*)odbcData,(destLen-1));
                *((char*)destData+destLen)='\0';
            }*/
            
            break;
        case typeDate: {
            Date dt;
            dt.set((*(SQL_DATE_STRUCT *)odbcData).year,
                   (*(SQL_DATE_STRUCT *)odbcData).month,
                   (*(SQL_DATE_STRUCT *)odbcData).day);
            stmt->setDateParam(paramNo, dt);
            break;
        }
        case typeTime: {
            Time tm;
            tm.set((*(SQL_TIME_STRUCT *)odbcData).hour,
                   (*(SQL_TIME_STRUCT *)odbcData).minute,
                   (*(SQL_TIME_STRUCT *)odbcData).second);
            stmt->setTimeParam(paramNo, tm);
            break;
        }
        case typeTimeStamp: {
            TimeStamp ts;
            ts.setDate((*(SQL_TIMESTAMP_STRUCT *)odbcData).year,
                       (*(SQL_TIMESTAMP_STRUCT *)odbcData).month,
                       (*(SQL_TIMESTAMP_STRUCT *)odbcData).day);
            ts.setTime((*(SQL_TIMESTAMP_STRUCT*)odbcData).hour,
                       (*(SQL_TIMESTAMP_STRUCT *)odbcData).minute,
                       (*(SQL_TIMESTAMP_STRUCT *)odbcData).second);
            stmt->setTimeStampParam(paramNo, ts);
            break;
        }
   }
    
}

void convertFromOdbc(DataType srcType, void *src, DataType destType, void *dest,int length, TDBInfo tdbname)
{
    switch ((DataType) destType )
    {
        case typeInt:       AllDataType::convertToInt(dest, src, srcType); break;
        case typeLong:      AllDataType::convertToLong(dest, src, srcType); break;
        case typeLongLong:  AllDataType::convertToLongLong(dest, src, srcType); break;
        case typeShort:     AllDataType::convertToShort(dest, src, srcType); break;
        case typeByteInt:   AllDataType::convertToByteInt(dest, src, srcType); break;

        case typeFloat:     AllDataType::convertToFloat(dest, src, srcType); break;
        case typeDouble:    AllDataType::convertToDouble(dest, src, srcType); break;

        //TODO 
        case typeDecimal:   AllDataType::convertToDouble(dest, src, srcType); break;

        case typeString:    convertToStringFromOdbc(dest, src, srcType); break;
        case typeBinary:    AllDataType::convertToBinary(dest, src, srcType,length); break;
        case typeDate:      AllDataType::convertToDate(dest, src, srcType); break;
        case typeTime:      AllDataType::convertToTime(dest, src, srcType); break;
        case typeTimeStamp: AllDataType::convertToTimeStamp(dest, src, srcType); break;
        default: return;
    }
}
void convertToStringFromOdbc(void *dest,void*src,DataType srcType,int length,TDBInfo tdbname )
{
    switch(srcType)
    {
        case typeInt:
        {
            //sprintf ((char *)dest, "%d", *(int *)src); 
            Util::itoa(*(int*)src, (char*)dest);
            break;
        }
        case typeLong:
        {
            sprintf ((char *)dest, "%ld", *(long *)src);
            break;
        }
        case typeLongLong:
        {
            sprintf ((char *)dest, "%lld", *(long long *)src);
            break;
        }
        case typeShort:
        {
            sprintf ((char *)dest, "%hd", *(short *)src);
            break;
        }
        case typeByteInt:
        {
            sprintf ((char *)dest, "%hhd", *(char *)src);
            break;
        }

        case typeFloat:
        {
            sprintf ((char *)dest, "%f", *(float *)src);
            break;
        }
        case typeDouble:
        {
            sprintf ((char *) dest, "%lf", *(double *)src);
            break;
        }
        case typeString:
        {
            strcpy((char*)dest, (char*)src);
            break;
        }
        case typeDate:
        {
            Date dt;
            dt.set((*(SQL_DATE_STRUCT *)src).year,
                   (*(SQL_DATE_STRUCT *)src).month,
                   (*(SQL_DATE_STRUCT *)src).day);
            sprintf((char*) dest, "%d/%d/%d", dt.year(),dt.month(), dt.dayOfMonth());
            break;
        }
        case typeTime:
        {
            Time tm;
            tm.set((*(SQL_TIME_STRUCT *)src).hour,
                   (*(SQL_TIME_STRUCT *)src).minute,
                   (*(SQL_TIME_STRUCT *)src).second);
            sprintf((char*)dest,"%d:%d:%d.%d", tm.hours(), tm.minutes(), tm.seconds(), 0);
            break;
        }
        case typeTimeStamp:
        {
            TimeStamp ts;
            ts.setDate((*(SQL_TIMESTAMP_STRUCT *)src).year,
                       (*(SQL_TIMESTAMP_STRUCT *)src).month,
                       (*(SQL_TIMESTAMP_STRUCT *)src).day);
            ts.setTime((*(SQL_TIMESTAMP_STRUCT*)src).hour,
                       (*(SQL_TIMESTAMP_STRUCT *)src).minute,
                       (*(SQL_TIMESTAMP_STRUCT *)src).second);
            sprintf((char*)dest, "%d/%d/%d %d:%d:%d.%d", ts.year(),ts.month(), ts.dayOfMonth(), ts.hours(),ts.minutes(), ts.seconds(), 0 );
            break;
        }
        case typeBinary:
        {
            unsigned char *c = (unsigned char *) src;
            unsigned char *str = (unsigned char *) dest;
            unsigned char p = 0;
            int i = 0;
            while (i < length) {
                p = *c >> 4;
                if (p < 10) sprintf ((char *)str++, "%c", '0' + p);
                else sprintf((char *)str++, "%c", 'A' + p - 10);
                p = *c & 0xF;
                if (p < 10) sprintf ((char *)str++, "%c", '0' + p);
                else sprintf((char *)str++, "%c", 'A' + p - 10);
                i++; c++;
            }
            break;
        }

        default: ((char*)dest)[0] = '\0';
    }
 
}

//Copies data from the database onto the application buffer 
//Called from SQLFetch
//Destination here can be the actual application buffer or
//it may be ipd_
SQLINTEGER copyToOdbc(void *odbcData,SQLUINTEGER odbcLen,void *sourceData,SQLUINTEGER sourceLen,SQLSMALLINT type, SQLSMALLINT apptype)
{
    SQLINTEGER ind;
    if(odbcData == NULL || sourceData == NULL)
        return -1;
    if( apptype == typeString && type != apptype){
        AllDataType::convertToString(odbcData , sourceData,(DataType) type);
        if(sourceLen < odbcLen) return sourceLen;
        else return odbcLen;
    }
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
bool isFunctionSupports(SQLUSMALLINT type)
{
    switch(type)
    {
        case SQL_API_SQLALLOCHANDLE:
        {
            return true;
        }
        case SQL_API_SQLGETDESCFIELD:
        {
            return false;
        }
        case SQL_API_SQLBINDCOL:
        {
            return true;
        }
        case SQL_API_SQLGETDESCREC:
        {
            return false;
        }
        case SQL_API_SQLCANCEL:
        {
            return false;
        }
        case SQL_API_SQLGETDIAGFIELD:
        {
            return false;
        }
        case SQL_API_SQLCLOSECURSOR:
        {
            return true;
        }
        case SQL_API_SQLGETDIAGREC:
        {
            return true;
        }
        case SQL_API_SQLCOLATTRIBUTE:
        {
            return true;
        }
        case SQL_API_SQLGETENVATTR:
        {
            return false;
        }
        case SQL_API_SQLCONNECT:
        {
            return true;
        }
        case SQL_API_SQLGETFUNCTIONS:
        {
            return true;
        }
        case SQL_API_SQLCOPYDESC:
        {
            return false;
        }
        case SQL_API_SQLGETINFO:
        {
            return true;
        }
        case SQL_API_SQLDATASOURCES:
        {
            return false;
        }
        case SQL_API_SQLGETSTMTATTR:
        {
            return true;
        }
        case SQL_API_SQLDESCRIBECOL:
        {
            return true;
        }
        case SQL_API_SQLGETTYPEINFO:
        {
            return true;
        }
        case SQL_API_SQLDISCONNECT:
        {
            return true;
        }
        case SQL_API_SQLNUMRESULTCOLS:
        {
            return true;
        }
        case SQL_API_SQLDRIVERS:
        {
            return false;
        }
        case SQL_API_SQLPARAMDATA:
        {
            return false;
        }
        case SQL_API_SQLENDTRAN:
        {
            return true;
        }
        case SQL_API_SQLPREPARE:
        {
            return true;
        }
        case SQL_API_SQLEXECDIRECT:
        {
            return true;
        }
        case SQL_API_SQLPUTDATA:
        {
            return false;
        }
        case SQL_API_SQLEXECUTE:
        {
            return true;
        }
        case SQL_API_SQLROWCOUNT:
        {
            return true;
        }
        case SQL_API_SQLFETCH:
        {
            return true;
        }
        case SQL_API_SQLSETCONNECTATTR:
        {
            return true;
        }
        case SQL_API_SQLFETCHSCROLL:
        {
            return false;
        }
        case SQL_API_SQLSETCURSORNAME:
        {
            return false;
        }
        case SQL_API_SQLFREEHANDLE:
        {
            return true;
        }
        case SQL_API_SQLSETDESCFIELD:
        {
            return false;
        }
        case SQL_API_SQLFREESTMT:
        {
            return true;
        }
        case SQL_API_SQLSETDESCREC:
        {
            return false;
        }
        case SQL_API_SQLGETCONNECTATTR:
        {
            return true;
        }
        case SQL_API_SQLSETENVATTR:
        {
            return true;
        }
        case SQL_API_SQLGETCURSORNAME:
        {
            return false;
        }
        case SQL_API_SQLSETSTMTATTR:
        {
            return true;
        }
        case SQL_API_SQLGETDATA:
        {
            return true;
        }
        case SQL_API_SQLCOLUMNS:
        {
            return true;
        }
        case SQL_API_SQLSTATISTICS:
        {
            return true;
        }
        case SQL_API_SQLSPECIALCOLUMNS:
        {
            return false;
        }
        case SQL_API_SQLTABLES:
        {
            return true;
        }
        case SQL_API_SQLBINDPARAMETER:
        {
            return true;
        }
        case SQL_API_SQLNATIVESQL:
        {
            return false;
        }
        case SQL_API_SQLBROWSECONNECT:
        {
            return false;
        }
        case SQL_API_SQLNUMPARAMS:
        {
            return true;
        }
        case SQL_API_SQLPRIMARYKEYS:
        {
            return true;
        }
        case SQL_API_SQLCOLUMNPRIVILEGES:
        {
            return false;
        }
        case SQL_API_SQLPROCEDURECOLUMNS:
        {
            return false; 
        }
        case SQL_API_SQLDESCRIBEPARAM:
        {
            return true;
        }
        case SQL_API_SQLPROCEDURES:
        {
            return false;
        }
        case SQL_API_SQLDRIVERCONNECT:
        {
            return true;
        }
        case SQL_API_SQLSETPOS:
        {
            return false;
        }
        case SQL_API_SQLFOREIGNKEYS:
        {
            return true;
        }
        case SQL_API_SQLTABLEPRIVILEGES:
        {
            return false;
        }
        case SQL_API_SQLMORERESULTS:
        {
            return false;
        }
        default :
            return false;
    }

}
