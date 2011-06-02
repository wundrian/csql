/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
  ***************************************************************************/
#include<os.h>
#include<DataType.h>
#include<Debug.h>
#include<sqlext.h>
#include<sqltypes.h>

DataType AllDataType::getCsqlTypeFromFunctionType(FunctionType type)
{
    switch(type)
    {
        case DATEDIFF: return typeDate;
        case TIMEDIFF: return typeTime;
        case DATEADDWITHYEAR:
        case DATEADDWITHMON:
        case DATEADDWITHDAY:
        case DATESUBWITHYEAR:
        case DATESUBWITHMON:
        case DATESUBWITHDAY:
        case TIMEADDWITHHOUR:
        case TIMEADDWITHMIN:
        case TIMEADDWITHSEC:
        case TIMESUBWITHHOUR:
        case TIMESUBWITHMIN:
        case TIMESUBWITHSEC: return typeInt;
        case TIMESTAMPADDWITHYEAR:
        case TIMESTAMPADDWITHMON:
        case TIMESTAMPADDWITHDAY:
        case TIMESTAMPSUBWITHYEAR:
        case TIMESTAMPSUBWITHMON:
        case TIMESTAMPSUBWITHDAY:
        case TIMESTAMPADDWITHHOUR:
        case TIMESTAMPADDWITHMIN:
        case TIMESTAMPADDWITHSEC:
        case TIMESTAMPSUBWITHHOUR:
        case TIMESTAMPSUBWITHMIN:
        case TIMESTAMPSUBWITHSEC: return typeInt;
        case TIMESTAMPDIFFYEAR:
        case TIMESTAMPDIFFMON:
        case TIMESTAMPDIFFDAY:
        case TIMESTAMPDIFFHOUR:
        case TIMESTAMPDIFFMIN:
        case TIMESTAMPDIFFSEC: return typeTimeStamp;
        case EXTRACTYEARFROMDAY:
        case EXTRACTMONFROMDAY:
        case EXTRACTDAYFROMDAY:return typeDate;
        case EXTRACTHOURFROMTIME:
        case EXTRACTMINFROMTIME:
        case EXTRACTSECFROMTIME: return typeTime;
        case EXTRACTYEARFROMTIMESTAMP:
        case EXTRACTMONFROMTIMESTAMP:
        case EXTRACTDAYFROMTIMESTAMP:
        case EXTRACTHOURFROMTIMESTAMP:
        case EXTRACTMINFROMTIMESTAMP:
        case EXTRACTSECFROMTIMESTAMP: return typeTimeStamp;
        case DATEFROMTIMESTAMP: return typeTimeStamp;
        case TIMEFROMTIMESTAMP: return typeTimeStamp;
        default: return typeInt;
    }
}
DataType AllDataType::getCsqlTypeFromFunctionTypeForComparision(FunctionType type)
{
    switch(type)
    {
        case DATEDIFF: return typeInt;
        case DATEADDWITHYEAR: return typeDate;
        case DATEADDWITHMON: return typeDate;
        case DATEADDWITHDAY: return typeDate;
        case DATESUBWITHYEAR: return typeDate;
        case DATESUBWITHMON: return typeDate;
        case DATESUBWITHDAY: return typeDate;
        case TIMEDIFF: return typeInt;
        case TIMEADDWITHHOUR: return typeTime;
        case TIMEADDWITHMIN: return typeTime;
        case TIMEADDWITHSEC: return typeTime;
        case TIMESUBWITHHOUR: return typeTime;
        case TIMESUBWITHMIN: return typeTime;
        case TIMESUBWITHSEC: return typeTime;
        case TIMESTAMPADDWITHYEAR: return typeTimeStamp;
        case TIMESTAMPADDWITHMON: return typeTimeStamp;
        case TIMESTAMPADDWITHDAY: return typeTimeStamp;
        case TIMESTAMPSUBWITHYEAR: return typeTimeStamp;
        case TIMESTAMPSUBWITHMON: return typeTimeStamp;
        case TIMESTAMPSUBWITHDAY: return typeTimeStamp;
        case TIMESTAMPADDWITHHOUR:  return typeTimeStamp;
        case TIMESTAMPADDWITHMIN: return typeTimeStamp;
        case TIMESTAMPADDWITHSEC: return typeTimeStamp;
        case TIMESTAMPSUBWITHHOUR:  return typeTimeStamp;
        case TIMESTAMPSUBWITHMIN: return typeTimeStamp;
        case TIMESTAMPSUBWITHSEC: return typeTimeStamp;
        case TIMESTAMPDIFFYEAR:
        case TIMESTAMPDIFFMON:
        case TIMESTAMPDIFFDAY:
        case TIMESTAMPDIFFHOUR:
        case TIMESTAMPDIFFMIN:
        case TIMESTAMPDIFFSEC:
        case EXTRACTYEARFROMDAY:
        case EXTRACTMONFROMDAY:
        case EXTRACTDAYFROMDAY:
        case EXTRACTHOURFROMTIME:
        case EXTRACTMINFROMTIME:
        case EXTRACTSECFROMTIME:
        case EXTRACTYEARFROMTIMESTAMP:
        case EXTRACTMONFROMTIMESTAMP:
        case EXTRACTDAYFROMTIMESTAMP:
        case EXTRACTHOURFROMTIMESTAMP:
        case EXTRACTMINFROMTIMESTAMP:
        case EXTRACTSECFROMTIMESTAMP:return typeInt;
        case DATEFROMTIMESTAMP: return typeDate;
        case TIMEFROMTIMESTAMP: return typeTime;
        default: return typeInt;
    }

}

char* AllDataType::getSQLString(DataType type)
{
    switch(type)
    {
        case typeInt: return "INT";
        case typeLong: return "INT";
        case typeLongLong: return "BIGINT";
        case typeShort: return "SMALLINT";
        case typeByteInt: return "TINYINT";
        case typeDouble: return "REAL";
        case typeFloat: return "FLOAT";
        case typeDate: return "DATE";
        case typeTime: return "TIME";
        case typeTimeStamp: return "TIMESTAMP";
        case typeString: return "CHAR";
        case typeVarchar: return "VARCHAR";
        case typeBinary: return "BINARY";
        default: return "UNKNOWN";
    }
}


short AllDataType::convertToSQLType(DataType type)
{
    switch(type)
    {
        case typeInt:
            return SQL_INTEGER;
        case typeLong:
            return SQL_INTEGER;
        case typeLongLong:
            //TODO
            return SQL_BIGINT;
        case typeShort:
            return SQL_SMALLINT;
        case typeByteInt:
            //TODO
            return SQL_INTEGER;
        case typeDouble:
            return SQL_DOUBLE;
        case typeFloat:
            return SQL_REAL;
        case typeDecimal:
            //TODO
            return SQL_INTEGER;
        case typeDate:
            return SQL_TYPE_DATE;
        case typeTime:
           return SQL_TYPE_TIME;
        case typeTimeStamp:
           return SQL_TYPE_TIMESTAMP;
        case typeString:
            return SQL_CHAR;
        case typeBinary:
            return SQL_BINARY;
        case typeVarchar:
            return SQL_VARCHAR;
    }
    return SQL_INTEGER;
}
SQLSMALLINT AllDataType::convertToCSQLSQLType(DataType type)
{
    switch(type)
    {
        case typeInt:
            return SQL_INTEGER;
        case typeLong:
            return SQL_INTEGER;
        case typeLongLong:
            //TODO
            return SQL_BIGINT;
        case typeShort:
            return SQL_SMALLINT;
        case typeByteInt:
            //TODO
            return SQL_TINYINT;
        case typeDouble:
            return SQL_DOUBLE;
        case typeFloat:
            return SQL_REAL;
        case typeDecimal:
            //TODO
            return SQL_INTEGER;
        case typeDate:
            return SQL_TYPE_DATE;
        case typeTime:
           return SQL_TYPE_TIME;
        case typeTimeStamp:
           return SQL_TYPE_TIMESTAMP;
        case typeString:
            return SQL_CHAR;
        case typeBinary:
            return SQL_BINARY;
        case typeVarchar:
            return SQL_VARCHAR;
    }
    return SQL_INTEGER;
}

SQLSMALLINT AllDataType::convertToSQL_C_Type(DataType type,TDBInfo tdbname)
{
    switch(type)
    {
        case typeInt:
            return SQL_C_SLONG;
        case typeLong:
            return SQL_C_SLONG;
        case typeLongLong:
        {
            if(tdbname == postgres)
                return SQL_C_CHAR;
            else
                return SQL_C_SBIGINT;
        }
        case typeShort:
            return SQL_C_SSHORT;
        case typeByteInt:
            return SQL_C_STINYINT;
        case typeDouble:
            return SQL_C_DOUBLE;
        case typeFloat:
            return SQL_C_FLOAT;
        case typeDecimal:
            //TODO
            return SQL_INTEGER;
        case typeDate:
            return SQL_C_TYPE_DATE;
        case typeTime:
           return SQL_C_TYPE_TIME;
        case typeTimeStamp:
           return SQL_C_TYPE_TIMESTAMP;
        case typeVarchar:
        case typeString:
            return SQL_C_CHAR;
        case typeBinary:
            return SQL_C_BINARY;
    }
    return SQL_C_SLONG;
}

DataType  AllDataType::convertFromSQLType(SQLSMALLINT type,int length,int scale,TDBInfo tdbname)
{
    if(tdbname==postgres)
    {
       switch(type)
       {
            case SQL_INTEGER :
                return typeInt;
            case  SQL_SMALLINT:
                return typeShort;
            case  SQL_BIGINT:
                return typeLongLong;
            case  SQL_FLOAT:
            case  SQL_DOUBLE:
                return typeDouble;
            case  SQL_REAL:
                return typeFloat;
            case SQL_TYPE_DATE:
                return typeDate;
            case SQL_TYPE_TIME :
               return typeTime;
            case SQL_TYPE_TIMESTAMP :
               return typeTimeStamp;
            case SQL_CHAR:
               return typeString;
            case SQL_LONGVARCHAR:
               return typeString;
            case SQL_VARCHAR:
               return typeVarchar;
            case SQL_BINARY:
               return typeBinary;
       }
       return typeInt;
    } 
    switch(type)
    {
        case  SQL_TINYINT:
            return typeByteInt;
        case SQL_INTEGER :
            return typeInt;
        case  SQL_SMALLINT:
            return typeShort;
        case  SQL_BIGINT:
            return typeLongLong;
        case  SQL_DOUBLE:
            return typeDouble;
        case  SQL_FLOAT:
        case  SQL_REAL:
            return typeFloat;
        case SQL_TYPE_DATE:
            return typeDate;
        case SQL_TYPE_TIME :
           return typeTime;
        case SQL_TYPE_TIMESTAMP :
           return typeTimeStamp;
        case SQL_CHAR:
            return typeString;
        case SQL_LONGVARCHAR:
            return typeString;
        case SQL_VARCHAR:
            return typeVarchar;
        case SQL_BINARY:
            return typeBinary;
    }
    return typeInt;
}
void AllDataType::subVal(void* dest, void *src, DataType type)
{
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)dest - *(int*)src;
            break;
        case typeLong:
            *(long*)dest = *(long*)dest - *(long*)src;
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)dest - *(long long*)src;
            break;
        case typeShort:
            *(short*)dest = *(short*)dest - *(short*)src;
            break;
        case typeByteInt:
            *(char*)dest = *(char*)dest - *(char*)src;
            break;
        case typeDouble:
            *(double*)dest = *(double*)dest - *(double*)src;
            break;
        case typeFloat:
            *(float*)dest = *(float*)dest - *(float*)src;
            break;
        case typeDecimal:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:
             break;
     }
     return;
}
void AllDataType::mulVal(void* dest, void *src, DataType type)
{
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)dest * (*(int*)src);
            break;
        case typeLong:
            *(long*)dest = *(long*)dest * (*(long*)src);
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)dest * (*(long long*)src);
            break;
        case typeShort:
            *(short*)dest = *(short*)dest * (*(short*)src);
            break;
        case typeByteInt:
            *(char*)dest = *(char*)dest * (*(char*)src);
            break;
        case typeDouble:
            *(double*)dest = *(double*)dest * (*(double*)src);
            break;
        case typeFloat:
            *(float*)dest = *(float*)dest * (*(float*)src);
            break;
        case typeDecimal:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:
             break;
    }
    return;
}   
void AllDataType::mudVal(void* dest, void *src, DataType type)
{
    if (type == typeInt)
    {
        *(int*)dest = *(int*)dest % (*(int*)src);
        return;
    }
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)dest % (*(int*)src);
            break;
        case typeLong:
            *(long*)dest = *(long*)dest % (*(long*)src);
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)dest % (*(long long*)src);
            break;
        case typeShort:
            *(short*)dest = *(short*)dest % (*(short*)src);
            break;
        case typeByteInt:
            *(char*)dest = *(char*)dest % (*(char*)src);
            break;
        case typeDouble:
            *(double*)dest = *(long long*)dest % (*(long long*)src);
            break;
        case typeFloat:
            *(float*)dest = *(int*)dest % (*(int*)src);
            break;
        case typeDecimal:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:
             break;
    }
    return;
}
void AllDataType::divVal(void* dest, void *src, DataType type)
{
    if (type == typeInt)
    {
        *(int*)dest = *(int*)dest / (*(int*)src);
        return;
    }
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)dest / (*(int*)src);
            break;
        case typeLong:
            *(long*)dest = *(long*)dest / (*(long*)src);
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)dest / (*(long long*)src);
            break;
        case typeShort:
            *(short*)dest = *(short*)dest / (*(short*)src);
            break;
        case typeByteInt:
            *(char*)dest = *(char*)dest / (*(char*)src);
            break;
        case typeDouble:
            *(double*)dest = *(double *)dest / (*(double*)src);
            break;
        case typeFloat:
            *(float*)dest = *(float*)dest / (*(float*)src);
            break;
        case typeDecimal:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:
             break;
    }
    return;
}
void AllDataType::divVal(double* dest, int src, DataType type)
{
    switch(type)
    {
        case typeInt:     
        case typeLong:     
        case typeLongLong: 
        case typeShort: 
        case typeByteInt: 
        case typeDouble: 
        case typeFloat:
        case typeDecimal:
            *dest = *dest / src;
            break;
            //TODO::for porting
        case typeDate:
        case typeTime:
        case typeTimeStamp:
		case typeBinary:
        default:
             break;
     }
     return;
}

void AllDataType::increment(void* dest, void *src, DataType type)
{
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)src + 1;
            break;
        case typeLong:
            *(long*)dest = *(long*)src + 1;
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)src + 1;
            break;
        case typeByteInt:
            *(char*)dest = *(char*)src + 1;
            break;
        case typeShort:
            *(short*)dest = *(short*)src + 1;
            break;
        case typeDouble:
            *(double*)dest = *(double*)src + 1;
            break;
        case typeFloat:
            *(float*)dest = *(float*)src+ 1;
            break;
        default:
             break;
     }
}

bool AllDataType::isValueZero(void *src, DataType type)
{
    switch(type)
    {
        case typeInt:
            if (*(int*)src == 0) return true;
            else return false;
        case typeLong:
            if (*(int*)src == 0) return true;
            else return false;
        case typeLongLong:
            if (*(int*)src == 0) return true;
            else return false;
        case typeShort:
            if (*(int*)src == 0) return true;
            else return false;
        case typeDouble:
            if (*(int*)src == 0) return true;
            else return false;
        case typeFloat:
            if (*(int*)src == 0) return true;
            else return false;
        default:
             break;
     }
     return false;
}

void* AllDataType::alloc(DataType type, int length)
{
    void *dest;
    switch(type)
    {
        case typeInt:
            dest = malloc(sizeof(int));
            break;
        case typeLong:
            dest = malloc(sizeof(long));
            break;
        case typeLongLong:
            dest = malloc(sizeof(long long));
            break;
        case typeShort:
            dest = malloc(sizeof(short));
            break;
        case typeByteInt:
            dest = malloc(sizeof(char));
            break;
        case typeDouble:
            dest = malloc(sizeof(double));
            break;
        case typeFloat:
            dest = malloc(sizeof(float));
            break;
        case typeDecimal:
            //TODO::for porting
            //fldDef.length_ = sizeof(long double);
            break;
        case typeVarchar:
        case typeString:
            if (length == 0 ) return NULL;
            dest = malloc(length);
            break;
        case typeBinary:
	    if (length == 0 || length > 512) return NULL;
	    dest = malloc(length);
	     memset(dest, 0, length);
   	     break;
        case typeDate:
            dest = malloc(sizeof(Date));
            break;
        case typeTime:
            dest = malloc(sizeof(Time));
            break;
        case typeTimeStamp:
            dest = malloc(sizeof(TimeStamp));
            break;
    }
    return dest;
}

void  AllDataType::memoryset(void *value,DataType type)
{
    switch(type)
    {
        case typeInt:
            value= ::memset(value, 0, sizeof(int));
            break;
        case typeLong:
            value = ::memset(value, 0, sizeof(long));
            break;
        case typeLongLong:
            value =::memset(value, 0, sizeof(long long));
            break;
        case typeShort:
            value = ::memset(value, 0, sizeof(short));
            break;
        case typeByteInt:
            value = ::memset(value, 0, sizeof(char));
            break;
        case typeDouble:
            value = ::memset(value, 0, sizeof(double));
            break;
        case typeFloat:
            value = ::memset(value, 0, sizeof(float));
            break;
        case typeDecimal:
            break;
        case typeString:
        case typeVarchar:
             *(char*)value = '\0';
            //if (length == 0 ) return NULL;
            //dest = malloc(length);
            break;
        case typeBinary:
                 /*   if (length == 0 || length > 256 ) return NULL;
                        
                        memset(dest, 0, length);*/
                        break;
        case typeDate:
            value = ::memset(value, 0, sizeof(Date));
            break;
        case typeTime:
            value = ::memset(value, 0, sizeof(Time));
            break;
        case typeTimeStamp:
            value = ::memset(value, 0, sizeof(TimeStamp));
            break;
        defalut:
            break;
    }
}

int AllDataType::printVal(void* src, DataType srcType, int length,int dbFlag )
{ 
    //dbFlag is the database flag 0:mysql (default), 1:postgres
    int count = 0;
    switch(srcType)
    {
        case typeInt:
        {
            count = printf ("%d", *(int *)src); 
            break;
        }
        case typeLong:
        {
            count = printf ("%ld", *(long *)src);
            break;
        }
        case typeLongLong:
        {
            if(1 == dbFlag){  
                long long temp = 0; 
                convertToLongLong((void*)&temp, src,typeString); 
                count = printf ("%lld", temp );
            }
            else count = printf ("%lld", *(long long *)src); 
            break;
        }
        case typeShort:
        {
            count = printf("%hd", *(short *)src); 
            break;
        }
        case typeByteInt:
        {
            count = printf("%hhd", *(char *)src); 
            break;
        }

        case typeFloat:
        {
            count = printf("%f", *(float *)src);
            break;
        }
        case typeDouble:
        {
            if (*(double*)src > 9999999999999999.0F)
                count = printf("%g", *(double *)src); 
            else
                count = printf("%lf", *(double *)src); 
            break;
        }

        case typeString:
        case typeVarchar:
        {
            count = printf("%s", (char*)src);
            break;
        }
        case typeDate:
        {
            Date* dt = (Date*)src;
            count = printf("%d/%d/%d", dt->year(),
                                  dt->month(), dt->dayOfMonth());
            break;
        }
        case typeTime:
        {
            Time* tm = (Time*)src;
            count = printf("%d:%d:%d.%d", tm->hours(), tm->minutes(), tm->seconds(), 0);
            break;
        }
        case typeTimeStamp:
        {
            TimeStamp* tm = (TimeStamp*)src;
            count = printf("%d/%d/%d %d:%d:%d.%d", tm->year(),
                                tm->month(), tm->dayOfMonth(), tm->hours(),
                                tm->minutes(), tm->seconds(), 0 );
            break;
        }
        case typeBinary:
        {
            unsigned char *c = (unsigned char *) src;
            unsigned char p = 0;
            int i = 0;
            bool isDigitFound=false;
            while (i < length) {
                p = *c >> 4;
                if(('0'+p)!='0'|| isDigitFound){
                    if (p < 10) printf ("%c", '0' + p);
                    else printf("%c", 'A' + p - 10);
                    isDigitFound=true;
                }
                p = *c & 0xF;
                if(('0'+p)!='0' || isDigitFound){
                    if (p < 10) printf ("%c", '0' + p);
                    else printf("%c", 'A' + p - 10);
                    isDigitFound=true;
                }
                i++; c++;
            }
            count = length * 2;
            break;
        }
        default: { printf("DataType not supported\n"); break; }
    }
    return count;
}
