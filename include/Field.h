/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef FIELD_H
#define FIELD_H
#include<os.h>
#include<DataType.h>
#include<ErrorType.h>

//used by FieldNameList
class FieldNameNode
{
    public:
    char  fldName[IDENTIFIER_LENGTH];
    FieldNameNode *next;
};


class FieldDef
{
    public:
    FieldDef()
    {
        init();
    }
    void init() {
        type_ = typeUnknown;
        length_ = 0;
        offset_ = 0;
        bindVal_ = NULL;
        isDefault_ = false;
        isNull_ = false;
        isPrimary_ = false;
        isUnique_ = false;
        isAutoIncrement_=false;
        strcpy(fldName_, "");
    }
    char fldName_[IDENTIFIER_LENGTH];
    DataType type_;
    size_t length_;
    size_t offset_;
    //currently default value is supported for string and binary
    //less than length 32 bytes
    char defaultValueBuf_[DEFAULT_VALUE_BUF_LENGTH];

    //used only in case of binding fields
    void *bindVal_;

    bool isNull_;
    bool isPrimary_;
    bool isDefault_;
    bool isUnique_;
    bool isAutoIncrement_;
    long long autoVal_;//[DEFAULT_VALUE_BUF_LENGTH];
    //TODO::width and scale
};

class FieldNode
{
    public:
    FieldDef fldDef;
    FieldNode *next;
};


class FieldIterator
{
    public:
    FieldNode *iter;
    FieldIterator(FieldNode *ptr) { iter = ptr; }
    bool hasElement()
    {
        if (iter == NULL) return false; else return true;
    }
    FieldDef* nextElement()
    {
        if (iter == NULL) { return NULL;}
        FieldNode *node = iter;
        iter = iter ->next;
        return &(node->fldDef);
    }
};

class FieldInfo;

//Internal class used to implement the field list information
//to create the table
class FieldList
{
    public:
    FieldNode *head;
    FieldList(){ head = NULL;}

    //TODO::pass by reference instead of value
    DbRetVal append(FieldDef fDef);

    DbRetVal remove(const char* fldName);

    DbRetVal removeAll();

    DbRetVal updateBindVal(const char *fldName, void *val);
    void * getBindField(const char *fldName);
    int getFieldOffset(const char *fldName);
    int getFieldOffset(int fldpos);

    //Returns position of field in the list:count starting from 1
    int getFieldPosition(const char *fldName);

    DataType getFieldType(const char *fldName);

    size_t getFieldLength(const char *fldName);

    DbRetVal getFieldInfo(const char *fldName, FieldInfo *&info);
    void fillFieldInfo(int fldpos, void *info);

    int getTupleSize();

    FieldIterator getIterator()
    {
        FieldIterator iter(head);
        return iter;
    }
};

//The below struct should be same as Parser.h:FieldValue
//For performance reason and it is
//done such that storage does not have dependency on SQL 
struct FieldInfoValue
{
    char fldName[IDENTIFIER_LENGTH];
    char *parsedString;
    void *value;
    int paramNo; // 0 ->not a param. It stores the param position
    DataType type;
    int aType; //assumes enum is always int
    int length;
    bool isNullable;
    bool isAllocVal;
    bool isInResSet;

    size_t offset;
    bool isPrimary;
    bool isUnique;
    bool isAutoIncrement;
};

#endif
