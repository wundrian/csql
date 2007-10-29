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

#ifndef CATALOGTABLE_H
#define CATALOGTABLE_H

#include<DataType.h>
#include<os.h>
#include<Index.h>
#include<Debug.h>
#include<Util.h>

class FieldList;
class FieldNameList;
class FieldIterator;
class ChunkIterator;

enum CatalogTableID
{
    // chunk id 0 ->userChunkTable
    //
    // chunk id 10->DATABASE
    // chunk id 11->USER
    // chunk id 12->TABLE
    // chunk id 13->FIELD
    // chunk id 14->ACCESS
    // chunk id 15->INDEX
    // chunk id 16->INDEXFIELD

    UserChunkTableId      =  0,
    LockTableHashBucketId =  1,
    LockTableMutexId      =  2,
    LockTableId           =  3,
    TransHasTableId       =  4,
    UndoLogTableID        =  5,


    DatabaseTableId  = 10,
    UserTableId      = 11,
    TableTableId     = 12,
    FieldTableId     = 13,
    AccessTableId    = 14,
    IndexTableId     = 15,
    IndexFieldTableId= 16

};


class TABLE
{
    public:
    char tblName_[IDENTIFIER_LENGTH];
    int tblID_;
    size_t length_; //length of the tuple
    int numFlds_;
    int numIndexes_;
    void* chunkPtr_;

};

class CatalogTableTABLE
{
    Database *systemDatabase_;
    public:
    CatalogTableTABLE(Database *db) { systemDatabase_  = db; }

    //Last argument is OUT parameter which will contain the
    //pointer to the inserted tuple
    DbRetVal insert(const char *name, int id, size_t size,
                     int numFlds, void* chunk, void *&tptr);

    //Second argument is OUT parameter which will contain the
    //chunk pointer of this table
    //Third argument is OUT parameter which will contain the
    //pointer to the removed tuple
    DbRetVal remove(const char *name, void *&chunk, void *&tptr);

    DbRetVal getChunkAndTblPtr(const char *name, void *&chunk, void *&tptr);

    List getTableList();
};


class FIELD
{
    public:
    char fldName_[IDENTIFIER_LENGTH];
    int tblID_;      //table id where this field resides
    void* tblPtr_;    //pointer to tuple in catalog table TABLE
    DataType type_;
    size_t length_;  //length of the field
    size_t offset_;  //offset (in bytes) into tuple
    //currently default value is supported for string and binary
    //less than length 32 bytes
    char defaultValueBuf_[DEFAULT_VALUE_BUF_LENGTH];
    bool isNull_;
    bool isPrimary_;
    bool isDefault_;
    int width_;
    int scale_;
};

class CatalogTableFIELD
{
    Database *systemDatabase_;
    public:
    CatalogTableFIELD(Database *db) { systemDatabase_  = db; }

    //returns -1 on error
    DbRetVal insert(FieldIterator &iter, int tblID, void *tblPtr);

    DbRetVal remove(void *tblPtr);

    //II argument is OUT parameter
    //field list is populated from the catalog table for
    // the table pointed by tblPtr
    void getFieldInfo( void* tblPtr, FieldList &list);

    //array is OUT param
    //returns the pointer to fields for the corresponding name
    //in field name list as an array
    DbRetVal getFieldPtrs(FieldNameList &fldList,void *tptr, char **&array);
};

class USER
{
    public:
    char userName_[IDENTIFIER_LENGTH];
    char password_[IDENTIFIER_LENGTH];
};

class CatalogTableUSER
{
    Database *systemDatabase_;
    public:
    CatalogTableUSER(Database *db) { systemDatabase_  = db; }

    //returns -1 on error
    DbRetVal insert(const char *name, const char *pass);
    DbRetVal authenticate(const char *name, const char *pass,
                     bool &isAuthenticated, bool &isDba);
    DbRetVal remove(const char *name);
    DbRetVal changePass(const char *name, const char *pass);

};

class ACCESS
{
    public:
    char userName_[IDENTIFIER_LENGTH];
    char dbName_[IDENTIFIER_LENGTH];
};

class DATABASEFILE
{
    public:
    int dbID_;
    char dbName_[IDENTIFIER_LENGTH];
    int maxChunks_;
    size_t maxSize_;  //maximum size of database
    caddr_t dbStart_; //address where the database is mapped
};


class INDEX
{
    public:
    char indName_[IDENTIFIER_LENGTH];
    int tblID_;      //table id of the table
    void* tblPtr_;    //pointer to tuple in catalog table TABLE
    IndexType indexType_;
    void* chunkPtr_; //pointer to the index chunk
    int numFlds_;
    int noOfBuckets_;
    bool isPrimary_;
    void *hashNodeChunk_;

};

class CatalogTableINDEX
{
    Database *systemDatabase_;
    public:
    CatalogTableINDEX(Database *db) { systemDatabase_  = db; }


    //last arg is OUT parameter which will give the pointer to
    //the index tuple
    DbRetVal insert(const char *name, void *tblPtr, int numFlds,
                     void* chunk, int bucketSize, void *hChunk, void *&tupleptr);

    //Second argument is OUT parameter which will contain the
    //chunk pointer of this table
    //Third argument is OUT parameter which will contain the
    //pointer to the removed tuple
    DbRetVal remove(const char *name, void *&chunk, void *&hchunk, void *&iptr);

    //get the number of indexes on table pointed by tblPtr
    int getNumIndexes(void *tblPtr);

    char* getIndexName(void *tblPtr, int pos);

    //gets all the index ptrs as array for the table pointed by tblPtr
    void getIndexPtrs(void *tblPtr, char **&array);

    static ChunkIterator getIterator(void *iptr);
    static int getNoOfBuckets(void *iptr);
};


class INDEXFIELD
{
    public:
    void* indexPtr; //pointer to tuple in catalog table INDEX
    void* tablePtr; //pointer to tuple in catalog table TABLE
    void* fieldPtr; //pointer to tuple in catalog table FIELD

};

class CatalogTableINDEXFIELD
{
    Database *systemDatabase_;
    public:
    CatalogTableINDEXFIELD(Database *db) { systemDatabase_  = db; }

    DbRetVal insert(FieldNameList &fldList, void *indexPtr,
                               void *tblPtr, char **&fptr);

    DbRetVal remove(void *iptr);

    DbRetVal getFieldNameAndType(void *iptr, char *&name, DataType &type);

};
#endif
