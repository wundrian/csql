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

DbRetVal AllDataType::strToValue(void* dest, char *src, DataType type, int length)
{
    Date date;
    Time time;
    switch(type)
    {
        case typeInt: {
            int val;
            sscanf( src, "%d",  &val);
            *(int*)dest = val;
            break; }
        case typeLong: {
            long val;
            sscanf( src, "%ld",  &val);
            *(long*)dest = val;
            break; }
        case typeLongLong: {
            long long val;
            sscanf( src, "%lld",  &val);
            *(long long*)dest = val;
            break; }
        case typeShort: {
            short val;
            sscanf( src, "%hd",  &val);
            *(short*)dest = val;
            break; }
        case typeByteInt: {
            char val;
            sscanf( src, "%hhd",  &val);
            *(char*)dest = *(char *)&val;
            break; }
        case typeDouble: {
            double val;
            sscanf( src, "%lg",  &val);
            *(double*)dest = val;
            break; }
        case typeFloat: {
            float val;
            sscanf( src, "%f",  &val);
            *(float*)dest = val;
            break; }
        case typeDecimal:
            //TODO::for porting
        case typeString: 
        case typeVarchar: {
                strncpy((char*)dest, (char*)src, length);
                char *d =(char*)dest;
                d[length-1] = '\0'; 
                break;}
        case typeDate: {
            int d,m,y,res=0;
            if (strlen(src) == 11) {
                if ( src[6] == '-' || src[6] == '/' ) {
                    Date::changeToCsqlFormat(src);
                }
            }
	        res = sscanf( src, "%d-%d-%d", &y, &m, &d );
            if( res != 3 )
                res = sscanf( src, "%d/%d/%d", &y, &m, &d );
            if (strcmp(src,"now")==0 || strcmp(src,"NOW")==0){
	            Date *dt = (Date*) dest;
	            dt->parseFrom((char*)src);
	            break;
	        }
	        if( res != 3 )
            {
                fprintf(stderr,"Error reading date. yyyy{-/}mm{-/}dd is the valid format.");
                d=m=y=0;
            }
            /* Looking up at ranges of year-month-day */
            if(!date.isValidDate(y, m, d)){
                fprintf(stderr,"Error reading date. The value \"%d-%d-%d\" is inappropriate.",y,m,d);
                d=m=y=0;
                return ErrBadArg;
            }
            Date dateObj(y,m,d);
            *(Date*)dest = dateObj;
            break; }
        case typeTime: {
            int h,m,s,res=0;
	    res = sscanf( src, "%d:%d:%d", &h, &m, &s );
            if(strcmp(src,"now")==0 || strcmp(src,"NOW")==0){
	         Time *dt = (Time*) dest;
	         dt->parseFrom((char*)src);
	         break;
	    }
	    if( res != 3 )
            {
                int d,mn,y;
                res = sscanf( src, "%d-%d-%d %d:%d:%d", &y, &mn, &d, &h, &m, &s );
                if(res!=6){
                    fprintf(stderr, "Error reading time, hh:mm:ss is the valid format.");
                    h=m=s=0;
                    return ErrBadArg;
                }
            }
            /* validate time */
            if(!time.isValidTime(h, m, s)){
                fprintf(stderr,"Error reading Time. The value \"%d-%d-%d\" is inappropriate.",h,m,s);
                h=m=s=0;
                return ErrBadArg;
            }
	    Time timeObj(h,m,s);
            *(Time*)dest = timeObj;
            break; }
        case typeTimeStamp: {
            int d,m,y, h,mn,s, res=0;
            bool isNow = ( strcasecmp(src,"now")==0 );
            if(!isNow && isalpha(int(src[5]))) {
                TimeStamp::changeToCsqlFormat(src);
            }
	        res = sscanf( src, "%d-%d-%d %d:%d:%d", &y, &m, &d, &h, &mn, &s );
            if( res != 6 )
                res = sscanf( src, "%d-%d-%d, %d:%d:%d", &y, &m, &d, &h, &mn, &s );
            if( res != 6 )
                res = sscanf( src, "%d/%d/%d %d:%d:%d", &y, &m, &d, &h, &mn, &s );
            if( res != 6 )
                res = sscanf( src, "%d/%d/%d, %d:%d:%d", &y, &m, &d, &h, &mn, &s );
            
	    if(isNow){
	    	    TimeStamp *dt = (TimeStamp*) dest;
		        dt->parseFrom((char*)src);
		        break;
            }	    
	        if ( res != 6 )
            {
                fprintf(stderr, "Error reading timestamp, yyyy{-/}mm{-/}dd[,] hh:mm:ss is the valid format.");
                d=m=y=h=mn=s=0;
                return ErrBadArg;
            }
             /* Looking up at 'YY-MM-DD' */
            if(!date.isValidDate(y, m, d)){
                fprintf(stderr,"Error reading date. The value \"%d-%d-%d\" is inappropriate.",y,m,d);
                d=m=y=h=mn=s=0;
                return ErrBadArg;
            }
            /* Looking up at 'Hour-Min-Sec' */
            if(!time.isValidTime(h, m, s)){
                fprintf(stderr,"Error reading Time. The value \"%d-%d-%d\" is inappropriate.",h,m,s);
                d=m=y=h=mn=s=0;
                return ErrBadArg;
            }
            TimeStamp timeStampObj(y,m,d,h,mn,s);
            *(TimeStamp*)dest = timeStampObj;
            break; }
        case typeBinary: {
            memset ((void *) dest, 0, length);
            unsigned char c = 0;
            const char *str = (const char *)src;
            int i=0;
            i = strlen(src)-1;
            if( i > (length*2)-1 ){ i = (length*2)-1 ; }         
            bool evenlegth=false;
            if(i%2){ evenlegth=true;}   
            unsigned char *val = (unsigned char *)dest+(length-1);
            while (i >= 0) {
                c = str[i]; 
               if (!isxdigit((int)c)) {
                   printError(ErrBadArg, "Invalid hexadecimal value");
                   return ErrBadArg;
               }
               if (c <= '9') c -= '0';
               else if (c >= 'a') c = c - 'a' + 10;
               else c = c - 'A' + 10;
               if(evenlegth)
               {
                   if ((i+1) % 2) { *val = *val | (c<<4); val--;}
                   else { *val = c; }
               }else{
                   if (i % 2) { *val = *val | (c<<4);   val--;}
                   else { *val = c; }
               }
               i--;
            }
            break;
        }
        default:
            break;
        }
	return OK;
}


void AllDataType::convert(DataType srcType, void *src, 
                          DataType destType, void *dest, int length)
{
    switch ((DataType) destType )
    {
        case typeInt:        convertToInt(dest, src, srcType); break;
        case typeLong:       convertToLong(dest, src, srcType); break;
        case typeLongLong:   convertToLongLong(dest, src, srcType); break;
        case typeShort:      convertToShort(dest, src, srcType); break;
        case typeByteInt:    convertToByteInt(dest, src, srcType); break;

        case typeFloat:      convertToFloat(dest, src, srcType); break;
        case typeDouble:     convertToDouble(dest, src, srcType); break;

        //TODO 
        case typeDecimal:    convertToDouble(dest, src, srcType); break;
        case typeVarchar:
        case typeString:     convertToString(dest, src, srcType); break;
        case typeBinary:     convertToBinary(dest, src, srcType,length); break;
        case typeDate:       convertToDate(dest, src, srcType); break;
        case typeTime:       convertToTime(dest, src, srcType); break;
        case typeTimeStamp:  convertToTimeStamp(dest, src, srcType); break;
        default: return;
    }
}

void AllDataType::convertToInt( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(int *)dest = *(int *)src; break;
        case typeLong:       *(int *)dest =(int) *(long *)src; break;
        case typeLongLong:   *(int *)dest =(int) *(long long *)src; break;
        case typeShort:      *(int *)dest =(int) *(short *)src; break;
        case typeByteInt:    *(int *)dest =(int) *(char *)src; break;

        case typeFloat:      *(int *)dest = (int) *(float *)src; break;
        case typeDouble:     *(int *)dest =(int) *(double *)src; break;
        case typeVarchar:
        case typeString:     sscanf((const char*)src, "%d", (int*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(int *)dest = (int) 0;
    }
}

void AllDataType::convertToLong( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(long *)dest =(long) *(int *)src; break;
        case typeLong:       *(long *)dest = *(long *)src; break;
        case typeLongLong:   *(long *)dest =(long) *(long long *)src; break;
        case typeShort:      *(long *)dest =(long) *(short *)src; break;
        case typeByteInt:    *(long *)dest =(long) *(char *)src; break;

        case typeFloat:      *(long *)dest = (long) *(float *)src; break;
        case typeDouble:     *(long *)dest =(long) *(double *)src; break;
        case typeVarchar:
        case typeString:     sscanf((const char*)src, "%ld", (long*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(long *)dest = (long) 0;
    }
}


void AllDataType::convertToLongLong( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(long long *)dest =(long long) *(int *)src; break;
        case typeLong:       *(long long *)dest = (long long) *(long *)src; break;
        case typeLongLong:   *(long long *)dest = *(long long *)src; break;
        case typeShort:      *(long long *)dest =(long long) *(short *)src; break;
        case typeByteInt:    *(long long *)dest =(long long) *(char *)src; break;

        case typeFloat:      *(long long *)dest = (long long) *(float *)src; break;
        case typeDouble:     *(long long *)dest =(long long) *(double *)src; break;
        case typeVarchar:
        case typeString:     sscanf((const char*)src, "%lld", (long long*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(long long *)dest = (long long) 0;
    }
}

void AllDataType::convertToShort( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(short*)dest =(short) *(int*)src; break;
        case typeLong:       *(short*)dest = (short) *(long*)src; break;
        case typeLongLong:   *(short*)dest = (short) *(long long*)src; break;
        case typeShort:      *(short*)dest = *(short*)src; break;
        case typeByteInt:    *(short*)dest =(short) *(char *)src; break;

        case typeFloat:      *(short*)dest = (short) *(float *)src; break;
        case typeDouble:     *(short*)dest =(short) *(double *)src; break;
        case typeVarchar: 
        case typeString:     sscanf((const char*)src, "%hd", (short*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(short*)dest = (short) 0;
    }
}

void AllDataType::convertToByteInt( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(char*)dest = (char) *(int*)src; break;
        case typeLong:       *(char*)dest = (char) *(long*)src; break;
        case typeLongLong:   *(char*)dest = (char) *(long long*)src; break;
        case typeShort:      *(char*)dest = (char) *(short*)src; break;
        case typeByteInt:    *(char*)dest = *(char *)src; break;

        case typeFloat:      *(char*)dest = (char) *(float *)src; break;
        case typeDouble:     *(char*)dest =(char) *(double *)src; break;
        case typeVarchar:
        case typeString:     sscanf((const char*)src, "%hhd", (char*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(char*)dest = (char) 0;
    }
}

void AllDataType::convertToFloat( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(float *)dest =(float) *(int *)src; break;
        case typeLong:       *(float *)dest =(float) *(long *)src; break;
        case typeLongLong:   *(float *)dest =(float) *(long long *)src; break;
        case typeShort:      *(float *)dest =(float) *(short *)src; break;
        case typeByteInt:    *(float *)dest =(float) *(char *)src; break;

        case typeFloat:      *(float *)dest = *(float *)src; break;
        case typeDouble:     *(float *)dest =(float) *(double *)src; break;
        case typeVarchar:
        case typeString:     sscanf((const char*)src, "%f", (float*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(float *)dest = (float) 0;
    }
}

void AllDataType::convertToDouble( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:        *(double *)dest =(double) *(int *)src; break;
        case typeLong:       *(double *)dest =(double) *(long *)src; break;
        case typeLongLong:   *(double *)dest =(double) *(long long *)src; break;
        case typeShort:      *(double *)dest =(double) *(short *)src; break;
        case typeByteInt:    *(double *)dest =(double) *(char *)src; break;

        case typeFloat:      *(double *)dest =(double) *(float *)src; break;
        case typeDouble:     *(double *)dest = *(double *)src; break;
        case typeVarchar:
        case typeString:     sscanf((const char*)src, "%lf", (double*) dest); break;

        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeBinary:
        default:             *(double *)dest = (double) 0;
    }
}

void AllDataType::convertToString( void* dest, void* src, DataType srcType, int length,TDBInfo tdbname )
{
    switch(srcType)
    {
        case typeInt:
        {
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
        case typeVarchar:
        case typeString:
        {
            strcpy((char*)dest, (char*)src);
            break;
        }
        case typeDate:
        {
            Date* dt = (Date*)src;
            sprintf((char*) dest, "%d/%d/%d", dt->year(),dt->month(), dt->dayOfMonth());
            break;
        }
        case typeTime:
        {
            Time* tm = (Time*)src;
            sprintf((char*)dest,"%d:%d:%d.%d", tm->hours(), tm->minutes(), tm->seconds(), 0);
            break;
        }
        case typeTimeStamp:
        {
            TimeStamp* tm = (TimeStamp*)src;
            sprintf((char*)dest, "%d/%d/%d %d:%d:%d.%d", tm->year(),tm->month(), tm->dayOfMonth(), tm->hours(),tm->minutes(), tm->seconds(), 0 );
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
void AllDataType::convertToDate( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:
        case typeLong:
        case typeLongLong:
        case typeShort:
        case typeByteInt:
        case typeFloat:
        case typeDouble:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeVarchar:
        case typeString:
        {
            Date *dt = (Date*) dest;
            dt->parseFrom((char*)src);
            break;
        }
        default: ((char*)dest)[0] = '\0';
    }
}

void AllDataType::convertToTime( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:
        case typeLong:
        case typeLongLong:
        case typeShort:
        case typeByteInt:
        case typeFloat:
        case typeDouble:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeVarchar:
        case typeString:
        {
            Time *dt = (Time*) dest;
            dt->parseFrom((char*)src);
            break;
        }
        default: ((char*)dest)[0] = '\0';
    }
}

void AllDataType::convertToTimeStamp( void* dest, void* src, DataType srcType )
{
    switch(srcType)
    {
        case typeInt:
        case typeLong:
        case typeLongLong:
        case typeShort:
        case typeByteInt:
        case typeFloat:
        case typeDouble:
        case typeDate:
        case typeTime:
        case typeTimeStamp:
        case typeVarchar:
        case typeString:
        {
            TimeStamp *dt = (TimeStamp*) dest;
            dt->parseFrom((char*)src);
            break;
        }
        default: ((char*)dest)[0] = '\0';
    }
}

void AllDataType::convertToBinary(void *dest, void *src, DataType srcType, int length)
{
    switch(srcType)
    {
        case typeString:
        {
            memset ((void *) dest, 0, length);
            unsigned char c = 0;
            const char *str = (const char *)src;
            int i=0;
            i = strlen((char*)src)-1;
            if( i > (length*2)-1 ){ i = (length*2)-1 ; }
            bool evenlegth=false;
            if(i%2){ evenlegth=true;}
            unsigned char *val = (unsigned char *)dest+(length-1);
            while (i >= 0) {
                c = str[i];
               if (c <= '9') c -= '0';
               else if (c >= 'a') c = c - 'a' + 10;
               else c = c - 'A' + 10;
               if(evenlegth)
               {
                   if ((i+1) % 2) { *val = *val | (c<<4); val--;}
                   else { *val = c; }
               }else{
                   if (i % 2) { *val = *val | (c<<4);   val--;}
                   else { *val = c; }
               }
               i--;
            }
           break;
        }
    }
}
