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
#include<Index.h>
#include<CatalogTables.h>
#include<Lock.h>
#include<Debug.h>
#include<Table.h>
#include<TableImpl.h>
#include<Predicate.h>
#include<PredicateImpl.h>
#include<Index.h>
#include<Config.h>
#include<AggTableImpl.h> //for AggType

bool TableImpl::isFldNull(const char *name){
    if (name[0] == '*') return false;
    if ( strncasecmp(name,"COUNT",5) == 0 || strncasecmp(name,"AVG",3) == 0 ||
         strncasecmp(name,"MIN",3) == 0 || strncasecmp(name,"MAX",3) == 0 ||
         strncasecmp(name,"SUM",3) == 0 ) return false;
    char fieldName[IDENTIFIER_LENGTH];
    getFieldNameAlone((char*)name, fieldName);
    int colpos = fldList_.getFieldPosition(fieldName);
    if (-1 == colpos)
    {
        printError(ErrNotExists, "Field %s does not exist", name);
        return false;
    }

    return isFldNull(colpos);
}

bool TableImpl::isFldNull(int colpos)
{
    if (!curTuple_) return false;
    if (colpos <1 || colpos > numFlds_) return false;
    if (isIntUsedForNULL) {
        int nullVal = *(int*)((char*)curTuple_ + (length_ - 4));
        if (BITSET(nullVal, colpos-1)) return true;
    }
    else {
        char *nullOffset = (char*)curTuple_ + (length_ - os::align(numFlds_));
        if (nullOffset[colpos-1]) return true;
    }
    return false;
}

void TableImpl::resetNullinfo()
{   
    if (isIntUsedForNULL) {
        iNullInfo =0;
    }
    else {
        int i=0;
        while(i < numFlds_) { cNullInfo[i++] = 0;}
    }
}

DbRetVal TableImpl::markFldNull(char const* name)
{
    DbRetVal rv = OK;
    int colpos = fldList_.getFieldPosition(name);
    if (-1 == colpos)
    {
        printError(ErrNotExists, "Field %s does not exist", name);
        return ErrNotExists;
    }
    rv =  markFldNull(colpos);
    return rv;
}

DbRetVal TableImpl::markFldNull(int fldpos)
{
    if (fldpos <1 || fldpos > numFlds_) return ErrBadArg;
    if (isIntUsedForNULL) {
        if (!BITSET(iNotNullInfo, fldpos-1)) SETBIT(iNullInfo, fldpos-1);
        else { 
            printError(ErrNullViolation, "NOT NULL constraint violation");
            return ErrNullViolation;
        }
    }
    else {
        if (!cNotNullInfo[fldpos-1]) cNullInfo[fldpos-1] = 1;
        else {
            printError(ErrNullViolation, "NOT NULL constraint violation");
            return ErrNullViolation;
        }
    }
    return OK;
}

void TableImpl::clearFldNull(const char *name)
{
    int colpos = fldList_.getFieldPosition(name);
    if (-1 == colpos)
    {
        printError(ErrNotExists, "Field %s does not exist", name);
        return;
    }
    clearFldNull(colpos);
}

void TableImpl::clearFldNull(int colpos)
{
    if (colpos <1 || colpos > numFlds_) return;
    if (isIntUsedForNULL) CLEARBIT(iNullInfo, colpos-1);
    else cNullInfo[colpos-1] = 0;
    return;
}

DbRetVal TableImpl::insertTuple()
{
    DbRetVal ret = getCheckpointMutex();
    if (ret !=OK) return ret;
    void *tptr = NULL;
    int tries=0;
    int totalTries = Conf::config.getMutexRetries();
    while (tries < totalTries)
    {
        ret = OK;
        tptr = ((Chunk*)chunkPtr_)->allocate(db_, &ret);
        if (tptr !=NULL) break;
        if (ret != ErrLockTimeOut)
        {
            sysDB_->releaseCheckpointMutex();
            printError(ret, "Unable to allocate record from chunk");
            return ret;
        }
        tries++;
    }
    if (NULL == tptr)
    {
        sysDB_->releaseCheckpointMutex();
        printError(ret, "Unable to allocate record from chunk after %d retries", tries);
        return ret;
    }
    curTuple_ = tptr;   
    if(isFkTbl){
        TableImpl *fkTbl =NULL; 
        ListIterator tblIter = tblList.getIterator();
        tblIter.reset();
        while (tblIter.hasElement()){
           fkTbl = (TableImpl *) tblIter.nextElement();
           bool pkRec = isPkTableHasRecord(fkTbl->getName(),fkTbl,true);
           if(!pkRec){
               printError(ErrForeignKeyInsert, "Unable to insert into foreign Key table.Check PK table");
               ((Chunk*)chunkPtr_)->free(db_, tptr);
               sysDB_->releaseCheckpointMutex();
               return ErrForeignKeyInsert;
           }
        }
        tblIter.reset();
    }
    if (!loadFlag) {
      //ret = lMgr_->getExclusiveLock(tptr, trans);
      if (OK != tryExclusiveLock(tptr, trans))
      {
        ((Chunk*)chunkPtr_)->free(db_, tptr);
        printError(ret, "Could not get lock for the insert tuple %x", tptr);
        sysDB_->releaseCheckpointMutex();
        return ErrLockTimeOut;
      }
    }

    ret = copyValuesFromBindBuffer(tptr);
    if (ret != OK)
    {
        printError(ret, "Unable to copy values from bind buffer");
        if (!loadFlag) {
            (*trans)->removeFromHasList(db_, tptr);
             lMgr_->releaseLock(tptr);
        }

        FieldIterator fIter = fldList_.getIterator();
        char *colPtr = (char*) curTuple_;
        while (fIter.hasElement()) {
            FieldDef *def = fIter.nextElement();
            colPtr =  (char *) curTuple_ + def->offset_;
            if (def->type_ == typeVarchar) {
                char *ptr = (char *) *(long *) colPtr;
                if (ptr != 0L) ((Chunk *) vcChunkPtr_)->free(db_, ptr);
            }
        }
        ((Chunk*)chunkPtr_)->free(db_, tptr);
        sysDB_->releaseCheckpointMutex();
        return ret;
    }
    int addSize = 0;
    if (numFlds_ < 31) 
    {
        addSize = 4; 
        *(int*)((char*)(tptr) + (length_-addSize)) = iNullInfo;
    }
    else 
    {
        addSize = os::align(numFlds_);
        os::memcpy(((char*)(tptr) + (length_-addSize)), cNullInfo, addSize);

    }
    //int tupleSize = length_ + addSize;
    if (NULL != indexPtr_)
    {
        int i;
        //it has index
        for (i = 0; i < numIndexes_ ; i++)
        {
            ret = insertIndexNode(*trans, indexPtr_[i], idxInfo[i], tptr);
            if (ret != OK) { printError(ret, "Error in inserting to index %x", tptr); break;}
        }
        if ( ret != OK)
        {
            for (int j = 0; j < i ; j++) {
                printError(ErrWarning, "Undo:Deleting index node");
                deleteIndexNode(*trans, indexPtr_[j], idxInfo[j], tptr);
            }
            if (!loadFlag) {
              (*trans)->removeFromHasList(db_, tptr);
               lMgr_->releaseLock(tptr);
            }

            FieldIterator fIter = fldList_.getIterator();
            char *colPtr = (char*) curTuple_;
            while (fIter.hasElement()) {
                FieldDef *def = fIter.nextElement();
                colPtr =  (char *) curTuple_ + def->offset_;
                if (def->type_ == typeVarchar) {
                    char *ptr = (char *) *(long *) colPtr;
                    if (ptr != 0L) ((Chunk *) vcChunkPtr_)->free(db_, ptr);
                }
            }
            ((Chunk*)chunkPtr_)->free(db_, tptr);
            sysDB_->releaseCheckpointMutex();
            return ret;
        }
    }
    if (!loadFlag) {
        //TODO: number of varchar fields to be stored as a member in TableImpl 
        int nVarchars = 0;
        FieldIterator fIter = fldList_.getIterator();
        while (fIter.hasElement()) {
            FieldDef *def = fIter.nextElement();
            if (def->type_ == typeVarchar) nVarchars++;
        }

        // the undo log for insert should contain 
        // tuple ptr + metadata Ptr + no of varchars + ptrs to varchars for insert opearation
        int size = (3 + nVarchars) * sizeof(void *) + sizeof(int);
        void *data = malloc(size);
        char *ptr = (char *)data;
        *(long *) ptr = (long) tptr; ptr += sizeof(void *);
        void *metaData = db_->getMetaDataPtr();
        *(long *) ptr = (long) metaData; ptr += sizeof(void *);
        *(int *) ptr = nVarchars; ptr += sizeof(int);
        *(long *) ptr = (long) vcChunkPtr_; ptr += sizeof(void *);
        fIter = fldList_.getIterator();
        char *colPtr = (char*) curTuple_;
        while (fIter.hasElement()) {
            FieldDef *def = fIter.nextElement();
            colPtr =  (char *) curTuple_ + def->offset_;
            if (def->type_ == typeVarchar) {
                *(long *) ptr = (long)colPtr;
                ptr += sizeof(void *);
            }
        }
        ret = (*trans)->appendUndoLog(sysDB_, InsertOperation, data, size);
        ::free(data);
    }
    if (ret != OK) {
        printError(ret, "Unable to create undo log for %x %d", tptr, *(int*)tptr);
        for (int j = 0; j < numIndexes_ ; j++) {
            printError(ErrWarning, "Deleting index node");
            deleteIndexNode(*trans, indexPtr_[j], idxInfo[j], tptr);
        }
        if (!loadFlag) {
          (*trans)->removeFromHasList(db_, tptr);
           lMgr_->releaseLock(tptr);
        }
        ((Chunk*)chunkPtr_)->free(db_, tptr);
    }
    sysDB_->releaseCheckpointMutex();
    return ret;
}

DbRetVal TableImpl::deleteTuple()
{
    if (NULL == curTuple_)
    {
        printError(ErrNotOpen, "Scan not open: No Current tuple");
        return ErrNotOpen;
    }
    DbRetVal ret = getCheckpointMutex();
    if (ret != OK) return ret;
    if(isPkTbl){
        TableImpl *fkTbl =NULL;
        ListIterator tblIter = tblFkList.getIterator();
        tblIter.reset();
        while (tblIter.hasElement()){
           fkTbl = (TableImpl *) tblIter.nextElement();
           bool pkRec = isFkTableHasRecord(fkTbl->getName(),fkTbl);
           if(pkRec){
                printError(ErrForeignKeyDelete, "A Relation Exists. Delete from child table first");
                sysDB_->releaseCheckpointMutex();
                return ErrForeignKeyDelete;
           }
        }
        tblIter.reset();
    }
    if (!loadFlag) {   
        //ret = lMgr_->getExclusiveLock(curTuple_, trans);
        if (OK != tryExclusiveLock(curTuple_, trans))
        {
            printError(ret, "Could not get lock for the delete tuple %x", 
                                                              curTuple_);
            sysDB_->releaseCheckpointMutex();
            return ErrLockTimeOut;
        }
    }

    if (NULL != indexPtr_)
    {
        int i;
        //it has index
        for (i = 0; i < numIndexes_ ; i++)
        {
            ret = deleteIndexNode(*trans, indexPtr_[i], idxInfo[i], curTuple_);
            if (ret != OK) break;
        }
        if (i != numIndexes_ )
        {
            printError(ErrWarning, "Inserting back index node");
            for (int j = 0; j < i ; j++)
                insertIndexNode(*trans, indexPtr_[j], idxInfo[j], curTuple_);
            if (!loadFlag) {   
                lMgr_->releaseLock(curTuple_);
                (*trans)->removeFromHasList(db_, curTuple_);
            }
            printError(ret, "Unable to insert index node for tuple %x", curTuple_);
            sysDB_->releaseCheckpointMutex();
            return ret;
        }
    }
    if (!loadFlag) {
        // the undo log for delete should contain 
        // tupleptr + metadataPtr + nVarchars + varchar chunk ptr + 
        // ptrs to varchars + size and value pairs for varchars

        //TODO: number of varchar fields to be stored as a member in TableImpl 
        void *tptr = curTuple_;
        char *colPtr = (char *)curTuple_;
        int nVarchars = 0;
        int vcLenValPairSize = 0;
        FieldIterator fIter = fldList_.getIterator();
        while (fIter.hasElement()) {
            FieldDef *def = fIter.nextElement();
            colPtr =  (char *) curTuple_ + def->offset_;
            if (def->type_ == typeVarchar) {
                nVarchars++;
                if (* (long *) colPtr == 0L)
                    vcLenValPairSize = vcLenValPairSize + sizeof(int);
                else vcLenValPairSize = vcLenValPairSize + sizeof(int) +
                             + os::align(strlen((char *) *(long *)colPtr) + 1);
            }
        }
        int size = (3 + nVarchars) * sizeof(void *) + sizeof(int)
                                                    + vcLenValPairSize;
        void *data = malloc(size);
        char *ptr = (char *)data;
        *(long *) ptr = (long) tptr; ptr += sizeof(void *);
        void *metaData = db_->getMetaDataPtr();
        *(long *) ptr = (long) metaData; ptr += sizeof(void *);
        *(int *) ptr = nVarchars; ptr += sizeof(int);
        *(long *) ptr = (long) vcChunkPtr_; ptr += sizeof(void *);
        fIter = fldList_.getIterator();
        colPtr = (char*) curTuple_;
        char *valLenPairPtr = ptr + nVarchars * sizeof(void *);
        while (fIter.hasElement()) {
            FieldDef *def = fIter.nextElement();
            colPtr =  (char *) curTuple_ + def->offset_;
            int vcStrLen = 0;
            if (def->type_ == typeVarchar) {
                *(long *) ptr = (long )colPtr; ptr += sizeof(void *);
                if (*(long *) colPtr == 0L) {
                    *(int *) valLenPairPtr = vcStrLen = 0;
                    valLenPairPtr += sizeof(int);
                } else {
                    *(int *) valLenPairPtr = vcStrLen =
                                os::align(strlen((char *)*(long *)colPtr) + 1);
                    valLenPairPtr += sizeof(int);
                    strcpy(valLenPairPtr, (char *)*(long *)colPtr);
                    valLenPairPtr += vcStrLen;
                }
            }
        }
        ret = (*trans)->appendUndoLog(sysDB_, DeleteOperation, data, size);
        ::free(data);
    }
    if (ret != OK) {
        printError(ret, "Unable to create undo log for %x ", curTuple_);
        for (int j = 0; j < numIndexes_ ; j++) {
            printError(ErrWarning, "Inserting back index node");
            insertIndexNode(*trans, indexPtr_[j], idxInfo[j], curTuple_);
        }
        if (!loadFlag) {
          (*trans)->removeFromHasList(db_, curTuple_);
           lMgr_->releaseLock(curTuple_);
        }
    }
   
    FieldIterator fIter = fldList_.getIterator();
    char *colPtr = (char*) curTuple_;
    while (fIter.hasElement()) {
        FieldDef *def = fIter.nextElement();
        colPtr =  (char *) curTuple_ + def->offset_;
        if (def->type_ == typeVarchar) {
            if (*(long *) colPtr != 0L) {
                char *ptr = (char *) *(long *) colPtr;
                ((Chunk *) vcChunkPtr_)->free(db_, ptr);
            }
        }
    }
    ((Chunk*)chunkPtr_)->free(db_, curTuple_);
    iter->prev();
    sysDB_->releaseCheckpointMutex();
    return ret;
}

int TableImpl::deleteWhere()
{
    DbRetVal ret = getCheckpointMutex();
    if (ret !=OK) return ret;

    int tuplesDeleted = 0;
    DbRetVal rv  = OK;
    rv =  execute();
    if (rv !=OK) {
        sysDB_->releaseCheckpointMutex();
        return (int) rv;
    }
    while(true){
        fetchNoBind( rv);
        if (rv != OK) { tuplesDeleted = (int)rv; break; }
        if (NULL == curTuple_) break;
        rv = deleteTuple();
        if (rv != OK) {
            printError(rv, "Error: Could only delete %d tuples", tuplesDeleted);
            closeScan();
            sysDB_->releaseCheckpointMutex();
            return (int) rv;
        }
        tuplesDeleted++;
    }
    closeScan();
    sysDB_->releaseCheckpointMutex();
    return tuplesDeleted;
}

int TableImpl::truncate()
{
    //take exclusive lock on the table
    //get the chunk ptr of the table
    //traverse the tablechunks and free all the pages except the first one
    //get the chunk ptr of all its indexes
    //traverse the indexchunks and free all the pages except the first one
    //release table lock

    //TEMPORARY FIX
    DbRetVal rv = OK;
    Predicate* tmpPred = pred_;
    pred_ = NULL;
    isPlanCreated = false;
    int tuplesDeleted = deleteWhere();
    isPlanCreated = false;
    pred_ = tmpPred;
    return tuplesDeleted;
}

DbRetVal TableImpl::updateTuple()
{
    if (NULL == curTuple_)
    {
        printError(ErrNotOpen, "Scan not open: No Current tuple");
        return ErrNotOpen;
    }
    DbRetVal ret = getCheckpointMutex();
    if (ret !=OK) return ret;
    if(isFkTbl){
        TableImpl *fkTbl =NULL;
        ListIterator tblIter = tblList.getIterator();
        tblIter.reset();
        while (tblIter.hasElement()){
           fkTbl = (TableImpl *) tblIter.nextElement();
           bool pkRec = isPkTableHasRecord(fkTbl->getName(),fkTbl,false);
           if(!pkRec){
               printError(ErrForeignKeyInsert, "Unable to insert into foreign Key table.Check PK table");
               sysDB_->releaseCheckpointMutex();
               return ErrForeignKeyInsert;
           }
        }
        tblIter.reset();
    }

    if (!loadFlag) {
      //ret = lMgr_->getExclusiveLock(curTuple_, trans);
      if (OK != tryExclusiveLock(curTuple_, trans))
      {
        printError(ret, "Could not get lock for the update tuple %x", curTuple_);
        sysDB_->releaseCheckpointMutex();
        return ErrLockTimeOut;
      }
    }
    if (NULL != indexPtr_)
    {
        //it has index
        //TODO::If it fails while updating index node, we have to undo all the updates 
        //on other indexes on the table.Currently it will leave the database in an 
        //inconsistent state.
        for (int i = 0; i < numIndexes_ ; i++)
        {
            ret = updateIndexNode(*trans, indexPtr_[i], idxInfo[i], curTuple_);
            if (ret != OK)
            {
                if (!loadFlag) {
                  lMgr_->releaseLock(curTuple_);
                  (*trans)->removeFromHasList(db_, curTuple_);
                }
                printError(ret, "Unable to update index node for tuple %x", curTuple_);
                sysDB_->releaseCheckpointMutex();
                return ret;
            }
        }
    }
    
    if (!loadFlag) {
        // the undo log for update should contain 
        // tupleptr + tuple length + actual tuple + metadataPtr + 
        // nVarchars + varchar chunk ptr + ptrs to varchars +
        // size and value pairs for varchars

        //TODO: number of varchar fields to be stored as a member in TableImpl 
        void *tptr = curTuple_;
        char *colPtr = (char *)curTuple_;
        int nVarchars = 0;
        int vcLenValPairSize = 0;
        FieldIterator fIter = fldList_.getIterator();
        while (fIter.hasElement()) {
            FieldDef *def = fIter.nextElement();
            colPtr =  (char *) curTuple_ + def->offset_;
            if (def->type_ == typeVarchar) {
                nVarchars++;
                if (* (long *) colPtr == 0L) 
                    vcLenValPairSize = vcLenValPairSize + sizeof(int);
                else vcLenValPairSize = vcLenValPairSize + sizeof(int) +
                             + os::align(strlen((char *) *(long *)colPtr) + 1);
            }
        }
        int size = (3 + nVarchars) * sizeof(void *) + 2 * sizeof(int) +
                                                   vcLenValPairSize + length_;
        void *data = malloc(size);
        char *ptr = (char *) data;
        *(long *) ptr = (long) tptr; ptr += sizeof(void *);
        *(int *) ptr = length_; ptr += sizeof(int);
        os::memcpy(ptr, tptr, length_); ptr += length_;
        void *metaData = db_->getMetaDataPtr();
        *(long *) ptr = (long) metaData; ptr += sizeof(void *);
        *(int *) ptr = nVarchars; ptr += sizeof(int);
        *(long *) ptr = (long) vcChunkPtr_; ptr += sizeof(void *);
        fIter = fldList_.getIterator();
        colPtr = (char*) curTuple_;
        char *valLenPairPtr = ptr + nVarchars * sizeof(void *);
        while (fIter.hasElement()) {
            FieldDef *def = fIter.nextElement();
            colPtr =  (char *) curTuple_ + def->offset_;
            int vcStrLen = 0;
            if (def->type_ == typeVarchar) {
                *(long *) ptr = (long)colPtr; ptr += sizeof(void *);
                if (*(long *) colPtr == 0L) {
                    *(int *) valLenPairPtr = vcStrLen = 0;
                    valLenPairPtr += sizeof(int);
                } else {
                    *(int *) valLenPairPtr = vcStrLen =
                                os::align(strlen((char *)*(long *)colPtr) + 1);
                    valLenPairPtr += sizeof(int);
                    strcpy(valLenPairPtr, (char *)*(long *)colPtr);
                    valLenPairPtr += vcStrLen;
                }
            }
        }
        ret = (*trans)->appendUndoLog(sysDB_, UpdateOperation, data, size);
        ::free(data);
    }
    if (ret != OK) {
        if (!loadFlag) {
           lMgr_->releaseLock(curTuple_);
           (*trans)->removeFromHasList(db_, curTuple_);
         }
         sysDB_->releaseCheckpointMutex();
         return ret;
    }

    int addSize = 0;
    int iNullVal=iNullInfo;
    char *cNullVal = NULL;
    if (numFlds_ > 32) { 
       addSize = os::align(numFlds_);
       cNullVal = (char *) malloc(addSize);
       os::memcpy(cNullVal, cNullInfo, addSize);
    }
    bool nullCharSet = false;
    if (numFlds_ <= 32){
        addSize=4;
        if (!iNullVal)
            iNullInfo = *(int*)((char*)(curTuple_) + (length_- addSize));
        else
            *(int*)((char*)(curTuple_) + (length_-addSize)) |= iNullInfo;
    } else {
        int i=0;
        while(i < numFlds_) {
            if(cNullInfo[i++]) { nullCharSet = true; break; }
        }
        char *null=(char*)(curTuple_) + (length_-addSize);
        if (!nullCharSet) {
            i=0;
            while(i < numFlds_) {
                if(null[i]) cNullInfo[i] = null[i];
                i++;
            }
        } else {
            i = 0;
            while(i < numFlds_) {
                if(cNullInfo[i]) { null[i] |= cNullInfo[i]; }
                i++;
            }
        }
    }    
    DbRetVal rv = copyValuesFromBindBuffer(curTuple_, false);
    if (rv != OK && !loadFlag) { 
        lMgr_->releaseLock(curTuple_); 
        (*trans)->removeFromHasList(db_, curTuple_); 
        sysDB_->releaseCheckpointMutex();
        return rv; 
    }
    if (numFlds_ <= 32) {
        if (!iNullVal) {
            *(int*)((char*)(curTuple_) + (length_-addSize)) = iNullInfo;
            iNullInfo=0;
        } else iNullInfo=iNullVal;
    } else {
        int i = 0;
        char *null=(char*)(curTuple_) + (length_-addSize);
        if (!nullCharSet) {
            os::memcpy(null, cNullInfo, addSize);
            while (i < numFlds_) cNullInfo[i++] = 0;
        } else os::memcpy(cNullInfo, cNullVal, addSize);
        free(cNullVal); cNullVal = NULL;
    }
    sysDB_->releaseCheckpointMutex();
    return OK;
}    

long long TableImpl::getLastInsertedVal(DbRetVal &rv)
{
    rv=OK;
    return *(long long*)ptrToAuto;
}

void TableImpl::clearNullBit(int fldpos)
{
    if (fldpos <1 || fldpos > numFlds_) return;
    if (isIntUsedForNULL) CLEARBIT(iNullInfo, fldpos-1);
    else cNullInfo[fldpos-1] = 0;
}

void TableImpl::setNullBit(int fldpos)
{
    if (fldpos <1 || fldpos > numFlds_) return;
    if (isIntUsedForNULL) SETBIT(iNullInfo, fldpos-1);
    else cNullInfo[fldpos-1] = 1;
}


//-1 index not supported
DbRetVal TableImpl::insertIndexNode(Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple)
{
    CINDEX *iptr = (CINDEX*)indexPtr;
    DbRetVal ret = OK;
    printDebug(DM_Table, "Inside insertIndexNode type %d", iptr->indexType_);
    Index* idx = Index::getIndex(iptr->indexType_);
    ret = idx->insert(this, tr, indexPtr, info, tuple,loadFlag);
    return ret;
}

DbRetVal TableImpl::deleteIndexNode(Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple)
{
    CINDEX *iptr = (CINDEX*)indexPtr;
    DbRetVal ret = OK;
    Index* idx = Index::getIndex(iptr->indexType_);
    ret = idx->remove(this, tr, indexPtr, info, tuple, loadFlag);
    return ret;
}

DbRetVal TableImpl::updateIndexNode(Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple)
{
    CINDEX *iptr = (CINDEX*)indexPtr;
    DbRetVal ret = OK;
    Index* idx = Index::getIndex(iptr->indexType_);
    //TODO::currently it updates irrespective of whether the key changed or not 
    //because of this commenting the whole index update code. relook at it and uncomment

    ret = idx->update(this, tr, indexPtr, info, tuple, loadFlag);

    return ret;
}

bool TableImpl::isPkTableHasRecord(char *pkTableName, TableImpl *fkTbl,bool isInsert)
{
    DbRetVal rv=OK;
    bool isRecExist=false;
    FieldNameList pkFieldList,fkFieldList;
    void *tPkptr =NULL;
    void *tFkptr = NULL;
    void *chunkPk = NULL;
    void *vcchunkPk = NULL;
    CatalogTableTABLE cTable(sysDB_);
    rv = cTable.getChunkAndTblPtr(pkTableName, chunkPk, tPkptr, vcchunkPk);
    if ( OK != rv){return false;}
    rv = cTable.getChunkAndTblPtr(getName(), chunkPk, tFkptr, vcchunkPk);
    if ( OK != rv){return false;}
    CatalogTableFK cFk(sysDB_);
    rv = cFk.getPkFkFieldInfo(tPkptr,tFkptr,pkFieldList,fkFieldList);
    if ( OK != rv){return false;}
    int totFld = pkFieldList.size();
    Condition *condition = new Condition[totFld];
    char *pkFldName = NULL;
    char *fkFldName = NULL;
    FieldDef *def=NULL;
    int i=0;
    pkFieldList.resetIter();
    fkFieldList.resetIter();
    void *val=NULL;
    while((pkFldName = pkFieldList.nextFieldName())!= NULL)
    {
        fkFldName = fkFieldList.nextFieldName();
        FieldIterator fIter = fldList_.getIterator();
        while (fIter.hasElement())
        {
            def = fIter.nextElement();
            if (strcmp(def->fldName_, fkFldName) == 0)
            {
                if(NULL == def->bindVal_ && isInsert) { return true; }
                if(NULL == def->bindVal_) {
                    if (def->type_ != typeVarchar)
                        val = (char*)curTuple_+ def->offset_;
                    else val = (void *) *(long *) ((char*)curTuple_+
                                                                 def->offset_);
                } else {
                    val = def->bindVal_;
                }
                if(def->type_==typeString)
                    condition[i].setTerm(pkFldName,OpEquals,&val);
                else
                    condition[i].setTerm(pkFldName,OpEquals,val);
                i++;
                break;
            }
        }
    }
    pkFieldList.removeAll();
    fkFieldList.removeAll();
    Condition *cond = NULL;
    if(i == 0 && !isInsert)return true;
    if( i > 1){
        cond = new Condition[i-1];
        int totcon = i;
        i=0;
        int j=0;
        for(j=0;j<totcon-1;j++)
        {
            if(j==0)
                cond[j].setTerm(condition[i++].getPredicate(),OpAnd,condition[i++].getPredicate());
            else
                cond[j].setTerm(cond[j-1].getPredicate(), OpAnd, condition[i++].getPredicate());
        }
        fkTbl->setCondition(&cond[j-1]);
    }
    else{
        fkTbl->setCondition(&condition[i-1]);
    }
    fkTbl->execute();
    if(fkTbl->fetch()){
        fkTbl->closeScan();
        delete[] cond;
        delete[] condition;
        return true;
    }
    delete[] cond;
    delete[] condition;
    return false;
}

bool TableImpl::isFkTableHasRecord(char *pkTableName, TableImpl *fkTbl)
{
    DbRetVal rv=OK;
    FieldNameList pkFieldList,fkFieldList;
    void *tPkptr =NULL;
    void *tFkptr = NULL;
    void *chunkPk = NULL;
    void *vcchunkPk = NULL;
    CatalogTableTABLE cTable(sysDB_);
    rv = cTable.getChunkAndTblPtr(getName(), chunkPk, tPkptr, vcchunkPk);
    if ( OK != rv){return false;}
    rv = cTable.getChunkAndTblPtr(pkTableName, chunkPk, tFkptr, vcchunkPk);
    if ( OK != rv){return false;}
    CatalogTableFK cFk(sysDB_);
    rv = cFk.getPkFkFieldInfo(tPkptr,tFkptr,pkFieldList,fkFieldList);
    if ( OK != rv){return false;}
    int totFld = pkFieldList.size();
    Condition *condition = new Condition[totFld];
    char *pkFldName = NULL;
    char *fkFldName = NULL;
    FieldDef *def=NULL;
    int i=0;
    pkFieldList.resetIter();
    fkFieldList.resetIter();
    while((pkFldName = pkFieldList.nextFieldName())!= NULL)
    {
        fkFldName = fkFieldList.nextFieldName();
        FieldIterator fIter = fldList_.getIterator();
        while (fIter.hasElement())
        {
            def = fIter.nextElement();
            void *val = NULL;
            if (def->type_ != typeVarchar)
                val = (char*)curTuple_+ def->offset_;
            else val = (void *) *(long *) ((char*)curTuple_+ def->offset_);
            if (strcmp(def->fldName_, pkFldName) == 0)
            {
                if(def->type_==typeString)
                    condition[i].setTerm(fkFldName,OpEquals,&val);//((char*)curTuple_+def->offset_));
                else
                    condition[i].setTerm(fkFldName,OpEquals,val);//((char*)curTuple_+def->offset_));
                i++;
                break;
            }
        }
    }
    pkFieldList.removeAll(); 
    fkFieldList.removeAll(); 
    if(i == 0 )return true;
    Condition *cond = new Condition[i-1];
    i=0;
    int j=0;
    for(j=0;j<totFld-1;j++)
    {
        if(j==0)
            cond[j].setTerm(condition[i++].getPredicate(),OpAnd,condition[i++].getPredicate());
        else
            cond[j].setTerm(cond[j-1].getPredicate(), OpAnd, condition[i++].getPredicate());
    }
    if(totFld==1)
        fkTbl->setCondition(&condition[totFld-1]);
    else
        fkTbl->setCondition(&cond[j-1]);
    fkTbl->execute();
    if(fkTbl->fetch()){
        fkTbl->closeScan();
        delete[] cond;
        delete[] condition;
        return true;
    }
    delete[] cond;
    delete[] condition;
    return false;
}
