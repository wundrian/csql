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
#ifndef INFO_H
#define INFO_H
#include<ErrorType.h>
#include<DataType.h>
#include<Field.h>


class FieldNameNode;

/**
* @class FieldNameList
*
* @brief Field name list used to specify composite key while creating index. <br/>
* @author Prabakaran Thirumalai
*/
class FieldNameList
{
    FieldNameNode *head;
    FieldNameNode *iter;
    public:
    FieldNameList() { head = iter = NULL; }
    ~FieldNameList() { } //TODO::Remove all elements from the list
    char *nextFieldName();
    void resetIter(){ iter = head; }
    int size();

    /** appends field name to the list
    *   @param name field name 
    *   @return int
    */
    DbRetVal append(const char *name);

    /** removes field name from the list
    *   @param name field name 
    *   @return int
    */
    DbRetVal remove(const char *name);
    DbRetVal removeAll();
};

class FieldList;
class FieldIterator;


/**
* @class TableDef
*
* @brief Represents table definition used to create the table.
* Encapsulates the information or schema definition of a table.For Example say if <br/>
* we need to create table with two fields, call addField method with necessary parameters<br/>
* twice. Passed as argument to createTable method of DatabaseManager to create table.<br/>
* @author Prabakaran Thirumalai
*/
class TableDef
{
    private:
    FieldList fldList;
    int fldCount;

    public:
    TableDef() { fldCount = 0; }
    ~TableDef();
    void reset();
    /** adds a field to the schema definition.
    *   @param name field name 
    *   @param type data type of the field
    *   @param length size of the field. used in case of char and binary data types.
    *   @param defaultValue default value for the field. It is currently limited to 32 bytes.
    *   @param isPrimary whether the field is primary key( not null + unique)
    *   @param notNull whether the field can be null
    *   @param unique whether the field values are unique
    *   @return int
    */
    int addField(const char *name,  DataType type = typeUnknown, size_t
                 length = 0, const void *defaultValue = 0,
                 bool notNull = false);

    /** removes a field from the schema definition
    *   @param name field name 
    *   @return int
    */
    int dropField(const char *name);

    /** returns the total number of fields in this table definition
    *   @return int no of fields
    */
    int getFieldCount();

    /** returns the total tuple size in bytes.
    *   @return size_t tuple size
    */
    size_t getTupleSize();

    //Internal method used to iterate and get information stored
    //in this table definition.
    FieldIterator getFieldIterator(){ return fldList.getIterator(); }

};

class FieldInfo
{
    public:
    char fldName[IDENTIFIER_LENGTH];
    DataType type;
    size_t length;
    int offset;
    char defaultValueBuf[DEFAULT_VALUE_BUF_LENGTH];
    bool isNull;
    bool isPrimary;
    bool isDefault;
};



/** A Enum value
*/
enum IndexType
{
    hashIndex = 0, /**<hash index*/
    treeIndex      /**<tree index*/
};

/**
* @class IndexInitInfo
*
* @brief Represents index definition used to create index.
* Encapsulates the information or definition of an index.<br/>
* @author Prabakaran Thirumalai
*/
class IndexInitInfo
{
    public:
    char tableName[IDENTIFIER_LENGTH]; /**<tablename*/
    FieldNameList list;               /**<field name list*/
    IndexType indType;                /**<index type*/
    bool isUnique;                    /**<unique values*/
    bool isPrimary;                   /**<primary key*/
    IndexInitInfo() {  indType = hashIndex;  isUnique = false; isPrimary= false;}
    ~IndexInitInfo() {list.removeAll();}
};

/**
* @class HashIndexInitInfo
*
* @brief Represents hash index definition used to create index.
* Encapsulates the information or definition of hash index.<br/>
* @author Prabakaran Thirumalai
*/
class HashIndexInitInfo : public IndexInitInfo
{
    public:
    int bucketSize; /**<bucket size*/
    HashIndexInitInfo() { bucketSize = 1009; }
};
#endif
