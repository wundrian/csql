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
        bindVal_ = NULL;
        isDefault_ = false;
        isNull_ = false;
    }
    char fldName_[IDENTIFIER_LENGTH];
    DataType type_;
    size_t length_;
    //currently default value is supported for string and binary
    //less than length 32 bytes
    char defaultValueBuf_[DEFAULT_VALUE_BUF_LENGTH];

    //used only in case of binding fields
    void *bindVal_;

    bool isNull_;
    bool isPrimary_;
    bool isDefault_;
    bool isUnique_;
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
    FieldDef nextElement()
    {
        if (iter == NULL) { FieldDef dummyDef; return dummyDef;}
        FieldNode *node = iter;
        iter = iter ->next;
        return node->fldDef;
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

    int getFieldOffset(const char *fldName);
    int getFieldOffset(int fldpos);

    DataType getFieldType(const char *fldName);

    size_t getFieldLength(const char *fldName);

    DbRetVal getFieldInfo(const char *fldName, FieldInfo *&info);

    int getTupleSize();

    FieldIterator getIterator()
    {
        FieldIterator iter(head);
        return iter;
    }
};
#endif
