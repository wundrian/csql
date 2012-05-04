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
#include<Database.h>
#include<DatabaseManager.h>
#include<DatabaseManagerImpl.h>
#include<os.h>
#include<Table.h>
#include<TableImpl.h>
#include<Transaction.h>
#include<CatalogTables.h>
#include<Index.h>
#include<Lock.h>
#include<Debug.h>
#include<Config.h>
#include<Process.h>

DbRetVal DatabaseManagerImpl::renameIndex(const char *oldName,const char *newName)
{
    void *chunk = NULL;
    DbRetVal rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to get database mutex for rename table");
        return ErrSysInternal;
    }
    CatalogTableTABLE cTable(systemDatabase_);
    rv = cTable.renameIndex(oldName,newName);
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to rename table");
        systemDatabase_->releaseCheckpointMutex();
        return ErrSysInternal;
    }
    systemDatabase_->releaseCheckpointMutex();
    return OK;
}

DbRetVal DatabaseManagerImpl::createIndex(const char *indName, IndexInitInfo *info)
{
    DbRetVal rv = OK;
    if (!info->isUnique && info->isPrimary) 
    {
        printError(ErrBadCall, "Primary key cannot be non unique\n");
        return ErrBadCall;
    }
    if (!Util::isIdentifier((char*)indName)) {
        printError(ErrBadArg, "Invalid character for index name");
        return ErrBadArg;
    }

    if (info->indType == hashIndex)
    {
        //Assumes info is of type HashIndexInitInfo
        HashIndexInitInfo *hInfo = (HashIndexInitInfo*) info;
        rv = createHashIndex(indName, info->tableName, info->list, hInfo->bucketSize,
                             info->isUnique, info->isPrimary);
    }
    else if (info->indType == treeIndex)
    {
        HashIndexInitInfo *hInfo = (HashIndexInitInfo*) info;
        rv = createTreeIndex(indName, info->tableName, info->list, 
                          hInfo->bucketSize, info->isUnique, info->isPrimary);
    }
    else if (info->indType == trieIndex)
    {
        HashIndexInitInfo *hInfo = (HashIndexInitInfo*) info;
        rv = createTrieIndex(indName, info->tableName, info->list, 
                          info->isUnique, info->isPrimary);

    }else {
        printError(ErrBadCall, "Index type not supported\n");
        return ErrBadCall;
    }
    return rv;
}


//-1 -> Table does not exists
//-2 -> Field does not exists
//-3 -> bucketSize is not valid
DbRetVal DatabaseManagerImpl::createHashIndex(const char *indName, const char *tblName,
                      FieldNameList &fldList, int bucketSize, bool isUnique, bool isPrimary)
{
    //validate the bucket size
    if (bucketSize < 100 || bucketSize > 200000)
    {
        printError(ErrBadRange, "Index Bucket size %d not in range 100-200000",
                                 bucketSize);
        return ErrBadRange;
    }
    int totFlds = fldList.size();
    if (totFlds == 0) 
    {
        printError(ErrBadCall, "No Field name specified");
        return ErrBadCall;
    }
    void *tptr =NULL;
    void *chunk = NULL;
    void *vcchunk = NULL;
    DbRetVal rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }

    //check whether table exists
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(tblName, chunk, tptr, vcchunk);
    if (NULL == tptr)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrNotExists, "Table does not exist %s", tblName);
        return ErrNotExists;
    }

    //check whether field exists
    char **fptr = new char* [totFlds];
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.getFieldPtrs(fldList, tptr, fptr);
    if (OK != rv)
    {
        delete[] fptr;
        systemDatabase_->releaseCheckpointMutex();
        //TODO::check test cases of dbapi/Index, they give wrong results
        //if (rv == ErrBadCall) {
        ////    if (isPrimary) printError(ErrBadCall, "Field can have NULL values");
        //} else {
        //printError(ErrNotExists, "Field does not exist");
        //} 
        //return ErrBadCall;
        if (rv != ErrBadCall) {
            printError(ErrNotExists, "Field does not exist");
            return ErrNotExists;
        }
    }
    for (int i=0; i <totFlds; i++)
    {
        CFIELD* fInfo = (CFIELD*)fptr[i];
        if (fInfo->type_ == typeFloat || fInfo->type_ == typeDouble || fInfo->type_ == typeTimeStamp) 
        {
            printError(ErrBadArg, "HashIndex cannot be created for float or double or timestamp type");
            delete[] fptr;
            systemDatabase_->releaseCheckpointMutex();
            return ErrBadArg;
        }
        if (!fInfo->isNull_ && isPrimary ) 
        {
            printError(ErrBadArg, "Primary Index cannot be created on field without NOTNULL constraint");
            delete[] fptr;
            systemDatabase_->releaseCheckpointMutex();
            return ErrBadArg;
        }
	 if(isPrimary){fInfo->isPrimary_=true;fInfo->isUnique_=true;}
	 if(isUnique){fInfo->isUnique_=true;}
    }
    //create chunk to store the meta data of the index created
    //for latches and bucket pointers
    printDebug(DM_HashIndex, "Creating chunk for storing hash buckets of size %d\n", 
                             bucketSize * sizeof(Bucket));
    Chunk* chunkInfo = createUserChunk(bucketSize * sizeof(Bucket));
    if (NULL == chunkInfo)
    {
        delete[] fptr;
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to create chunk");
        return ErrSysInternal;
    }
    chunkInfo->setChunkName(indName);
    //create memory for holding the bucket pointers
    void *buckets = chunkInfo->allocate(db_, &rv);
    if (NULL == buckets)
    {
        delete[] fptr;
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(rv, "Unable to allocate memory for bucket");
        return rv;
    }
    Bucket *buck = (Bucket*) buckets;
    initHashBuckets(buck, bucketSize);

    //create chunk to store the hash index nodes
    Chunk* hChunk = createUserChunk(sizeof(IndexNode));
    if (NULL == hChunk)
    {
        delete[] fptr;
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to create chunk for storing hash index nodes");
        return ErrSysInternal;
    }

     hChunk->setChunkName(indName);
    //add row to INDEX
    void *tupleptr = NULL;
    CatalogTableINDEX cIndex(systemDatabase_);
    rv = cIndex.insert(indName, tptr, fldList.size(), isUnique,
                        chunkInfo, bucketSize, hChunk, tupleptr);
    if (OK != rv)
    {
        delete[] fptr;
        deleteUserChunk(hChunk);
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in INDEX table");
        return ErrSysInternal;
    }
    //add rows to INDEXFIELD
    CatalogTableINDEXFIELD cIndexField(systemDatabase_);
    rv = cIndexField.insert(fldList, tupleptr, tptr, fptr);

    if (OK != rv)
    {
        delete[] fptr;
        cIndex.remove(indName, (void *&)chunkInfo, (void *&)hChunk, (void *&)tupleptr);
        deleteUserChunk(hChunk);
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in INDEXFIELD table");
        return ErrSysInternal;
    }
    delete[] fptr;
    systemDatabase_->releaseCheckpointMutex();
    
    //TODO:: Take table lock

    // Following code is written by Kishor Amballi
    TableImpl *tbl = (TableImpl *) openTable(tblName);
    if (NULL == tbl) {
        printError(ErrSysInternal, "Unable to open table %s", tblName);
        return ErrSysInternal;
    }
    if (! tbl->numTuples()) { 
        printDebug(DM_Database, "Creating Hash Index Name:%s tblname:%s buckets:%x", indName, tblName, buckets);
        logFinest(Conf::logger, "Creating HashIndex %s on %s with bucket size %d", indName, tblName, buckets);
        closeTable(tbl);
        return OK;
    }
    HashIndexInfo *indxInfo = NULL;
    int i = 0;
    for (i = 0; i < tbl->numIndexes_; i++) {
        if(((HashIndexInfo *)tbl->idxInfo[i])->indexPtr == tupleptr) {
            indxInfo = (HashIndexInfo *) tbl->idxInfo[i];  
            break;
        }
    }
    void *recPtr = NULL;
    ChunkIterator chIter = ((Chunk *)chunk)->getIterator();
    tbl->setLoading(true);
    while ((recPtr = chIter.nextElement()) != NULL) {
        rv = tbl->insertIndexNode(*tbl->trans, tupleptr, indxInfo, recPtr);
        if (rv == ErrUnique) {
            closeTable(tbl);
            dropIndex(indName);
            return rv;
        }
    }
    closeTable(tbl);
    printDebug(DM_Database, "Creating Hash Index Name:%s tblname:%s buckets:%x", indName, tblName, buckets);
    logFinest(Conf::logger, "Creating HashIndex %s on %s with bucket size %d", indName, tblName, buckets);
    return OK;
}


DbRetVal DatabaseManagerImpl::createTreeIndex(const char *indName, const char *tblName,
                      FieldNameList &fldList, int nodeSize, bool isUnique, bool isPrimary)
{
    if (nodeSize < 20 || nodeSize > 20000)
    {
        printError(ErrBadRange,"Tree Index Node size %d not in range 20-20000",
                                 nodeSize);
        return ErrBadRange;
    }
    int totFlds = fldList.size();
    if (totFlds == 0) {
        printError(ErrBadCall, "No Field name specified");
        return ErrBadCall;
    }else if (totFlds != 1) {
        printError(ErrBadCall, "Composite index not supported for Tree");
        return ErrBadCall;
    }
    void *tptr =NULL;
    void *chunk = NULL;
    void *vcchunk = NULL;
    DbRetVal rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }
    //check whether table exists
    
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(tblName, chunk, tptr, vcchunk);
    if (NULL == tptr)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrNotExists, "Table does not exist %s", tblName);
        return ErrNotExists;
    }
    char **fptr = new char* [totFlds];
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.getFieldPtrs(fldList, tptr, fptr);
    if (OK != rv)
    {
        delete[] fptr;
        systemDatabase_->releaseCheckpointMutex();
        if (rv != ErrBadCall) {
            printError(ErrNotExists, "Field does not exist");
            return ErrNotExists;
        }
    }
    for (int i=0; i <totFlds; i++)
    {
        CFIELD* fInfo = (CFIELD*)fptr[i];
        if (!fInfo->isNull_ && isPrimary )
        {
            printError(ErrBadArg, "Primary Index cannot be created on field without NOTNULL constraint");
            delete[] fptr;
            systemDatabase_->releaseCheckpointMutex();
            return ErrBadArg;
        }
        if (fInfo->type_ == typeVarchar)
        {
            printError(ErrBadArg, "Tree Index not supported for varchar type. Use char data type instead.");
            delete[] fptr;
           systemDatabase_->releaseCheckpointMutex();
            return ErrBadArg;
        }

    }
    int chunkSize = sizeof(TreeNode)+(nodeSize * sizeof(void*));
    printDebug(DM_HashIndex, "Creating chunk for storing tree nodes of size %d\n", chunkSize);

    Chunk* chunkInfo = createUserChunk(chunkSize);
    if (NULL == chunkInfo)
    {
        delete[] fptr;
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to create chunk");
        return ErrSysInternal;
    }


    void *tupleptr = NULL;

    CatalogTableINDEX cIndex(systemDatabase_);
    rv = cIndex.insert(indName, tptr, fldList.size(), isUnique,
                        chunkInfo, nodeSize, NULL, tupleptr);
    if (OK != rv)
    {
        delete[] fptr;
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in INDEX table");
        return ErrSysInternal;
    }
    CatalogTableINDEXFIELD cIndexField(systemDatabase_);
    rv = cIndexField.insert(fldList, tupleptr, tptr, fptr);

    if (OK != rv)
    {
        delete[] fptr;
        void *hChunk = NULL;
        cIndex.remove(indName, (void *&)chunkInfo, (void *&)hChunk, (void *&)tupleptr);
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in INDEXFIELD table");
        return ErrSysInternal;
    }
    delete[] fptr;
    rv = createIndexNodeForRecords(tblName, tupleptr, chunk);
    if (rv != OK)
    {
        //dropIndex again takes checkpoint mutex so releasing it here
        systemDatabase_->releaseCheckpointMutex();
        dropIndex(indName);
        return rv;
    }
    systemDatabase_->releaseCheckpointMutex();
    logFinest(Conf::logger, "Creating TreeIndex %s on %s rv:%d",
                                   indName, tblName, rv);
    return OK;
}
DbRetVal DatabaseManagerImpl::createIndexNodeForRecords(const char* tblName,
                              void *tupleptr, void *chunk)
{
    //TODO::if tuples already present in this table, then create tree index '
    //nodes
    TableImpl *tbl = (TableImpl *) openTable(tblName);
    if (NULL == tbl) {
        printError(ErrSysInternal, "Unable to open table %s", tblName);
        return ErrSysInternal;
    }
    if (! tbl->numTuples()) {
        closeTable(tbl);
        return OK;
    }
    HashIndexInfo *indxInfo = NULL;
    int i = 0;
    for (i = 0; i < tbl->numIndexes_; i++) {
        if(((HashIndexInfo *)tbl->idxInfo[i])->indexPtr == tupleptr) {
            indxInfo = (HashIndexInfo *) tbl->idxInfo[i];
            break;
        }
    }
    void *recPtr = NULL;
    ChunkIterator chIter = ((Chunk *)chunk)->getIterator();
    tbl->setLoading(true);
    DbRetVal rv = OK;
    while ((recPtr = chIter.nextElement()) != NULL) {
        rv = tbl->insertIndexNode(*tbl->trans, tupleptr, indxInfo, recPtr);
        if (rv == ErrUnique) {
            closeTable(tbl);
            return rv;
        }
    }
    closeTable(tbl);
    return OK;
}

DbRetVal DatabaseManagerImpl::createTrieIndex(const char *indName, const char *tblName,
                      FieldNameList &fldList, bool isUnique, bool isPrimary)
{
    int totFlds = fldList.size();
    void *tptr =NULL;
    char **fptr = new char* [totFlds];
    DbRetVal rv = validateIndex(tblName, fldList, &tptr, &fptr, isPrimary);
    if (OK != rv)
    {
        delete[] fptr;
        return rv;
    }
    rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }

    //below statements are actually setting values in the catalog table
    //thats why mutex is taken before this stmt. Do not change the order
    CFIELD* fInfo = (CFIELD*)fptr[0];
    if(isPrimary){fInfo->isPrimary_=true;fInfo->isUnique_=true;}
    if(isUnique){fInfo->isUnique_=true;}

    printDebug(DM_TrieIndex, "Creating chunk for storing trie nodes\n" );
    Chunk* chunkInfo = createUserChunk(sizeof(TrieNode));

    //chunk to store the linked list of trie values 
    Chunk* hChunk = createUserChunk(sizeof(IndexNode));
    if (NULL == chunkInfo || NULL == hChunk)
    {
        delete[] fptr;
        if (chunkInfo) deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to create trie node chunk");
        return ErrSysInternal;
    }
    chunkInfo->setChunkName(indName);
    hChunk->setChunkName(indName);
    void *tupleptr = NULL;
    rv = updateIndexCatalogTables(indName,tptr, fptr, fldList, isUnique,
                                  chunkInfo, hChunk , tupleptr);
    delete[] fptr;
    if (OK != rv) {
        printError(ErrSysInternal, "Catalog table updation failed");
        deleteUserChunk(chunkInfo);
        deleteUserChunk(hChunk);
        systemDatabase_->releaseCheckpointMutex();
        return rv;
    }

    void *chunk = NULL;
    void *vcchunk = NULL;
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(tblName, chunk, tptr, vcchunk);
    //create index nodes if records already exist in the table
    rv = createIndexNodeForRecords(tblName, tupleptr, chunk);
    if (rv != OK)
    {
        dropIndex(indName);
        systemDatabase_->releaseCheckpointMutex();
        return rv;
    }
    systemDatabase_->releaseCheckpointMutex();
    logFinest(Conf::logger, "Creating TrieIndex %s on %s rv:%d",
                                   indName, tblName, rv);
    return OK;
}
DbRetVal DatabaseManagerImpl::validateIndex(const char *tblName, 
                             FieldNameList &fldList, void **tptr, char ***fptr,
                             bool isPrimary)
{
    int totFlds = fldList.size();
    if (totFlds != 1)
    {
        printError(ErrBadCall, "No Field name specified or composite fields specified");
        return ErrBadCall;
    }
    void *chunk = NULL;
    void *vcchunk = NULL;
    //check whether table exists
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(tblName, chunk, *tptr, vcchunk);
    if (NULL == tptr)
    {
        printError(ErrNotExists, "Table does not exist %s", tblName);
        return ErrNotExists;
    }

    //check whether field exists
    CatalogTableFIELD cField(systemDatabase_);
    DbRetVal rv = cField.getFieldPtrs(fldList, *tptr, *fptr);
    if (OK != rv)
    {
        if (rv != ErrBadCall) {
            printError(ErrNotExists, "Field does not exist");
            return ErrNotExists;
        }
    }
    CFIELD* fInfo = (CFIELD*)*fptr[0];
    if (!(fInfo->type_ == typeInt || fInfo->type_ == typeLongLong || fInfo->type_ == typeString || fInfo->type_ == typeVarchar))
    {
        printError(ErrBadArg, "Trie Index cannot be created for float or double or timestamp type");
        return ErrBadArg;
    }
    if (!fInfo->isNull_ && isPrimary )
    {
        printError(ErrBadArg, "Primary Index cannot be created on field without NOTNULL constraint");
        return ErrBadArg;
    }

    return OK;
}

DbRetVal DatabaseManagerImpl::updateIndexCatalogTables(const char *indName,
                        void *tptr, char **fptr, FieldNameList &fldList, 
                        bool isUnique, Chunk* chunkInfo, Chunk* hChunk,
                        void *&tupleptr ) 
{
    //void *tupleptr = NULL;
    CatalogTableINDEX cIndex(systemDatabase_);
    DbRetVal rv = cIndex.insert(indName, tptr, fldList.size(), isUnique,
                        chunkInfo, 0, hChunk, tupleptr);
    if (OK != rv)
    {
        printError(ErrSysInternal, "Catalog table updation failed in INDEX table");
        return ErrSysInternal;
    }
    CatalogTableINDEXFIELD cIndexField(systemDatabase_);
    rv = cIndexField.insert(fldList, tupleptr, tptr, fptr);
    if (OK != rv)
    {
        //rollback the previous operation
        cIndex.remove(indName, (void *&)chunkInfo, (void *&)hChunk, (void *&)tupleptr);
        printError(ErrSysInternal, "Catalog table updation failed in INDEXFIELD table");
        return ErrSysInternal;
    }
    return rv;
}

DbRetVal DatabaseManagerImpl::removeIndexCatalogTables(const char *name, void *&chunk, void *&hchunk, void *&tptr)
{
    //remove the entry in INDEX
    CatalogTableINDEX cIndex(systemDatabase_);
    DbRetVal rv = cIndex.remove(name, chunk, hchunk, tptr);
    if (OK != rv)
    {
        printError(ErrSysInternal, "Catalog table updation failed for INDEX table");
        return ErrSysInternal;
    }
    printDebug(DM_Database, "Removing from INDEX %s",name);
    //remove the entries in the INDEXFIELD table
    CatalogTableINDEXFIELD cIndexField(systemDatabase_);
    rv = cIndexField.remove(tptr);
    if (OK != rv)
    {
        printError(ErrSysInternal, "Catalog table updation failed for INDEX table");
        return ErrSysInternal;
    }
    printDebug(DM_Database, "Removing from INDEXFIELD %s",name);
    return OK;
}

DbRetVal DatabaseManagerImpl::removeIndexChunks(void* chunk, void* hchunk, IndexType iType)
{
    DbRetVal rv = deleteUserChunk((Chunk*)chunk);
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to delete the index chunk");
        return ErrSysInternal;
    }
    //delete the index hash node chunk
    if (iType == hashIndex || iType == trieIndex) {
        rv = deleteUserChunk((Chunk*)hchunk);
        if (OK != rv)
        {
            printError(ErrSysInternal, "Unable to delete the index hash node chunk");
            return ErrSysInternal;
        }
    }
    return OK;
}

void DatabaseManagerImpl::initHashBuckets(Bucket *buck, int bucketSize)
{
    os::memset((void*)buck, 0, bucketSize * sizeof(Bucket));
    char mutName[IDENTIFIER_LENGTH];
    for (int i=0; i < bucketSize ; i++)
    {
        sprintf(mutName, "BKT:%d",i);
        buck[i].mutex_.init(mutName);
    }
    return;
}

DbRetVal DatabaseManagerImpl::dropIndex(const char *name)
{
    return dropIndexInt(name, true);
}

DbRetVal DatabaseManagerImpl::dropIndexInt(const char *name, bool takeLock)
{
    DbRetVal rv = OK;
    void *chunk = NULL, *hchunk = NULL;
    void *tptr =NULL;
    int ret = 0;
    if (takeLock) {
        rv = systemDatabase_->getXCheckpointMutex();
        if (OK != rv)
        {
            printError(ErrSysInternal, "Unable to get database mutex");
            return ErrSysInternal;
        }
    }
    rv = removeIndexCatalogTables(name, chunk, hchunk, tptr);
    if (OK != rv)
    {
        if (takeLock) systemDatabase_->releaseCheckpointMutex();
        return rv;
    }

    CINDEX *iptr = (CINDEX*)tptr;
    rv = removeIndexChunks(chunk, hchunk, iptr->indexType_);
    if (OK != rv)
    {
        if (takeLock) systemDatabase_->releaseCheckpointMutex();
        return rv;
    }
    if (takeLock) systemDatabase_->releaseCheckpointMutex();

    printDebug(DM_Database, "Dropped index %s",name);
    logFinest(Conf::logger, "Deleted Index %s", name);
    return OK;
}

void DatabaseManagerImpl::printTreeIndexNodeInfo(char *name, bool flag)
{
    CatalogTableINDEX cIndex(systemDatabase_);
    DbRetVal rv = OK;
    void *chunk = NULL, *hchunk = NULL;
    void *tptr =NULL;
    rv = cIndex.get(name, chunk, hchunk, tptr);
    if (OK != rv) return;
    IndexType iType = CatalogTableINDEX::getType(tptr);
    if (treeIndex != iType)
    {
       printf("%s is not a tree index\n ", name);
       return;
    }
    Chunk *ch = (Chunk*) chunk;
    if(flag){  if(hchunk)((TreeNode*) hchunk)->displayAll(); }
    else { 
        int offset = CatalogTableINDEX::getOffsetOfFirstField(tptr);
        //if(typeInt != offset) { printf("%s is not on Integer Type Field. To see info Index should be on integer type field. \n "); return;}       
        if(hchunk) ((TreeNode*) hchunk)->displayAll(offset);
    }
}
DbRetVal DatabaseManagerImpl::printIndexDebugInfo(char *name)
{
    CatalogTableINDEX cIndex(systemDatabase_);
    DbRetVal rv = OK;
    void *chunk = NULL, *hchunk = NULL;
    void *tptr =NULL;
    rv = cIndex.get(name, chunk, hchunk, tptr);
    if (OK != rv) return rv;
    IndexType iType = CatalogTableINDEX::getType(tptr);
    if(hashIndex == iType) {
    }
    else if (treeIndex == iType) {
        CINDEX *iptr = (CINDEX*)tptr;
        TreeNode *start = (TreeNode*) iptr->hashNodeChunk_;
        start->displayAll(0);
    }
    else if (trieIndex == iType) {
        ChunkIterator citer = CatalogTableINDEX::getIterator(tptr);
        TrieNode* start = (TrieNode*)citer.nextElement();
        if(start) TrieIndex::displayAll(start);
    }
    else
        printf("Unknown Index\n");


}

DbRetVal DatabaseManagerImpl::printIndexInfo(char *name)
{
    CatalogTableINDEX cIndex(systemDatabase_);
    DbRetVal rv = OK;
    void *chunk = NULL, *hchunk = NULL;
    void *tptr =NULL;
    rv = cIndex.get(name, chunk, hchunk, tptr);
    if (OK != rv) return rv;
    printf("<IndexName> %s </IndexName>\n", name);
    printf("<Unique> %d </Unique>\n", CatalogTableINDEX::getUnique(tptr));
    IndexType iType = CatalogTableINDEX::getType(tptr);
    if(hashIndex == iType)
        printf("<Type> Hash Index </Type>\n");
    else if (treeIndex == iType)
        printf("<Type> Tree Index </Type>\n");
    else if (trieIndex == iType)
        printf("<Type> Trie Index </Type>\n");
    else
        printf("<Type> Unknown Index </Type>\n");

    Chunk *ch = (Chunk*) chunk;
    printf("<HashBucket>\n");
    printf("  <TotalPages> %d </TotalPages>\n", ch->totalPages());
    printf("  <TotalBuckets> %d </TotalBuckets> \n", CatalogTableINDEX::getNoOfBuckets(tptr));
    printf("</HashBucket>\n");
    printf("<IndexNodes>\n");
    if(hashIndex == iType){
        ch = (Chunk*) hchunk;
        printf("  <TotalPages> %d </TotalPages>\n", ch->totalPages());
        printf("  <TotalNodes> %ld </TotalNodes>\n", ch->getTotalDataNodes());
    } else if (treeIndex == iType) {
        printf("  <TotalNodes> %ld </TotalNodes>\n", ch->getTotalDataNodes());
        if(hchunk)
            printf("  <TotalElements> %lld </TotalElements>\n",((TreeNode*) hchunk)->getTotalElements());
        else
            printf("  <TotalElements> 0 </TotalElements>\n");
    } else if (trieIndex == iType)
    {
        printf(" <TrieNodes> \n");
        printf("  <TotalPages> %d </TotalPages>\n", ch->totalPages());
        printf("  <TotalNodes> %ld </TotalNodes>\n", ch->getTotalDataNodes());
        printf(" </TrieNodes> \n <TrieValues>\n");
        ch = (Chunk*) hchunk;
        printf("  <TotalPages> %d </TotalPages>\n", ch->totalPages());
        printf("  <TotalNodes> %ld </TotalNodes>\n", ch->getTotalDataNodes());
        printf(" </TrieValues>\n");
    } else 
    {
        printf("Unknown Index type\n");
    }
    printf("<IndexNodes>\n");
    return OK;
}
