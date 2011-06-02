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

bool AllDataType::compareIntVal(void* src1, void *src2, ComparisionOp op)
{
    printf("This function should never be called by anyone\n");
    if (OpEquals == op) {
        if (*(int*)src1 == *(int*)src2) return true;
        else return false;
    }else if (OpGreaterThan == op) {
        if (*(int*)src1 > *(int*)src2) return true;
        else return false;
    }else if (OpLessThan == op) {
        if (*(int*)src1 < *(int*)src2) return true;
        else return false;
    }else if (OpLessThanEquals == op) {
        if (*(int*)src1 <= *(int*)src2) return true;
        else return false;
    }else if (OpGreaterThanEquals == op) {
        if (*(int*)src1 >= *(int*)src2) return true;
        else return false;
    }else if (OpNotEquals == op) {
        if (*(int*)src1 != *(int*)src2) return true;
        else return false;
    }
    return false;
}

bool AllDataType::compareLongVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(long*)src1 == *(long*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(long*)src1 != *(long*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(long*)src1 < *(long*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(long*)src1 <= *(long*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(long*)src1 > *(long*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(long*)src1 >= *(long*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareLongLongVal(void* src1, void *src2,
                                      ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(long long*)src1 == *(long long*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(long long*)src1 != *(long long*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(long long*)src1 < *(long long*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(long long*)src1 <= *(long long*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(long long*)src1 > *(long long*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(long long*)src1 >= *(long long*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareShortVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(short*)src1 == *(short*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(short*)src1 != *(short*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(short*)src1 < *(short*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(short*)src1 <= *(short*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(short*)src1 > *(short*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(short*)src1 >= *(short*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareByteIntVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(ByteInt*)src1 == *(ByteInt*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(ByteInt*)src1 != *(ByteInt*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(ByteInt*)src1 < *(ByteInt*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(ByteInt*)src1 <= *(ByteInt*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(ByteInt*)src1 > *(ByteInt*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(ByteInt*)src1 >= *(ByteInt*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareDoubleVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(double*)src1 == *(double*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(double*)src1 != *(double*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(double*)src1 < *(double*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(double*)src1 <= *(double*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(double*)src1 > *(double*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(double*)src1 >= *(double*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareFloatVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(float*)src1 == *(float*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(float*)src1 != *(float*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(float*)src1 < *(float*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(float*)src1 <= *(float*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(float*)src1 > *(float*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(float*)src1 >= *(float*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareDateVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(Date*)src1 == *(Date*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(Date*)src1 != *(Date*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(Date*)src1 < *(Date*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(Date*)src1 <= *(Date*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(Date*)src1 > *(Date*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(Date*)src1 >= *(Date*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareTimeVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(Time*)src1 == *(Time*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(Time*)src1 != *(Time*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(Time*)src1 < *(Time*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(Time*)src1 <= *(Time*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(Time*)src1 > *(Time*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(Time*)src1 >= *(Time*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareTimeStampVal(void* src1, void *src2, ComparisionOp op)
{
    bool result = false;
    switch(op)
    {
        case OpEquals:
            if (*(TimeStamp*)src1 == *(TimeStamp*)src2) result = true;
            else result = false;
            break;
        case OpNotEquals:
            if (*(TimeStamp*)src1 != *(TimeStamp*)src2) result = true;
            else result = false;
            break;
        case OpLessThan:
            if (*(TimeStamp*)src1 < *(TimeStamp*)src2) result = true;
            else result = false;
            break;
        case OpLessThanEquals:
            if (*(TimeStamp*)src1 <= *(TimeStamp*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThan:
            if (*(TimeStamp*)src1 > *(TimeStamp*)src2) result = true;
            else result = false;
            break;
        case OpGreaterThanEquals:
            if (*(TimeStamp*)src1 >= *(TimeStamp*)src2) result = true;
            else result = false;
            break;
   }
   return result;
}

bool AllDataType::compareStringVal(void* src1, void *src2, ComparisionOp op)
{
    if (OpEquals == op) {
        if (strcmp((char*)src1, (char*)src2) ==0) return true;
            else return false;
    }else if (OpGreaterThan == op) {
        if (strcmp((char*)src1, (char*)src2) >0) return true;
        else return false;
    }else if (OpLessThan == op) {
        if (strcmp((char*)src1, (char*)src2) <0 ) return true;
        else return false;
    }else if (OpLessThanEquals == op) {
       // printf("Illegal Operator:Not Supported for String\n");
       // return false;
       if (strcmp((char*)src1, (char*)src2)<= 0) return true;
       else return false;
    }else if (OpGreaterThanEquals == op) {
    //    printf("Illegal Operator:Not Supported for String\n");
    //    return false;
        if (strcmp((char*)src1, (char*)src2) >=0) return true;
        else return false;
    }else if (OpNotEquals == op) {
        if (strcmp((char*)src1, (char*)src2) != 0) return true;
        else return false;
    }else if (OpLike == op) {
        return !os::strmatch((char*)src2, (char*)src1);
    }
    printf("Illegeal Operator:Not supported for String\n");
    return false;
}

bool AllDataType::compareBinaryVal(void* src1, void *src2,
                                 ComparisionOp op, int length)
{
    bool result = false;
    int ret = os::memcmp(src1, src2, length);
    switch(op)
    {
        case OpEquals:
            if (ret == 0 ) result= true; else result = false;
            break;
        case OpNotEquals:
            if (ret != 0 ) result= true; else result = false;
            break;
        case OpLessThan:
            if (ret < 0 ) result= true; else result = false;
            break;
        case OpLessThanEquals:
            printf("Illegal Operator:Not Supported for Binary\n");
            break;
        case OpGreaterThan:
            if (ret > 0 ) result= true; else result = false;
            break;
        case OpGreaterThanEquals:
            printf("Illegal Operator:Not Supported for Binary\n");
            break;
   }
   return result;
}
