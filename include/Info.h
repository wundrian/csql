/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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
#ifndef INFO_H
#define INFO_H
//USER EXPOSED
#include<ErrorType.h>
#include<DataType.h>
#include<Field.h>


class FieldNameNode;
//Used to specify fields for creating the index(composite key index)
class FieldNameList
{
    FieldNameNode *head;
    FieldNameNode *iter;
    public:
    FieldNameList() { head = iter = NULL; }
    ~FieldNameList() { } //TODO::Remove all elements from the list
    DbRetVal append(const char *name);
    DbRetVal remove(const char *name);
    char *nextFieldName();
    void resetIter(){ iter = head; }
    int size();
};

class FieldList;
class FieldIterator;
//user exposed class to specify table definition for the table
class TableDef
{
    private:
    FieldList fldList;
    int fldCount;

    public:

    int addField(const char *name,  DataType type = typeUnknown, size_t
                 length = 0, const void *defaultValue = 0, bool notNull = false,
                 bool isPrimary = false);
    int dropField(const char *name);
    int getFieldCount();
    size_t getTupleSize();

    //Internal method used to iterate and get information stored
    //in this table definition.
    FieldIterator getFieldIterator(){ return fldList.getIterator(); }

};

enum IndexType
{
    hashIndex = 0,
    treeIndex
};

class IndexInitInfo
{
    public:
    char tableName[IDENTIFIER_LENGTH];
    FieldNameList list;
    IndexType indType;
    IndexInitInfo() {  indType = hashIndex; }
};

class HashIndexInitInfo : public IndexInitInfo
{
    public:
    int bucketSize;
    HashIndexInitInfo() { bucketSize = 1009; }
};
#endif
