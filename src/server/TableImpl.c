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
#include<Index.h>
#include<CatalogTables.h>
#include<Lock.h>
#include<Debug.h>
#include<Table.h>
#include<TableImpl.h>
#include<Predicate.h>
#include<PredicateImpl.h>
#include<Index.h>

void TableImpl::bindFld(const char *name, void *val)
{
    //set it in the field list
    fldList_.updateBindVal(name, val);
    return ;
}
bool TableImpl::isFldNull(const char *name){
    return true;
}
bool TableImpl::isFldNull(int colpos)
{
    return true;
}
void TableImpl::markFldNull(char const* name)
{
    return;
}
void TableImpl::markFldNull(int fldpos)
{
    return;
}

/*
void TableImpl::clearFldNull(const char *name)
{
    return;
}
void TableImpl::clearFldNull(int colpos)
{
    return;
}
*/

DbRetVal TableImpl::execute()
{
    if (NULL != iter)
    {
         printError(ErrAlready,"Scan already open:Close and re execute");
         return ErrAlready;
    }
    //table ptr is set in predicate because it needs to access the
    //type and length to evaluate
    if( NULL != pred_)
    {
        PredicateImpl *pred = (PredicateImpl*) pred_;
        pred->setTable(this);
    }
    DbRetVal ret = OK;

    ret = createPlan();
    if (OK != ret)
    {
        printError(ErrSysInternal,"Unable to create the plan");
        return ErrSysInternal;
    }
    iter = new TupleIterator(pred_, scanType_, idxInfo, chunkPtr_);
    ret = iter->open();
    if (OK != ret)
    {
            printError(ErrSysInternal,"Unable to open the iterator");
            return ErrSysInternal;
        }
    return OK;
}


DbRetVal TableImpl::createPlan()
{
    useIndex_ = -1;
    //if there are no predicates then go for full scan
    //if there are no indexes then go for full scan
    if (NULL == pred_ || NULL == indexPtr_)
    {
        scanType_ = fullTableScan;
        return OK;
    }
    if (NULL != indexPtr_)
    {
        useIndex_ = 0;
        if (numIndexes_ == 1) {
           //check predicate, whether it has field name and == operator
           //and does not have OR, NOT operator
           char *fName = ((SingleFieldHashIndexInfo*)idxInfo)->fldName;
           PredicateImpl *pred = (PredicateImpl*)pred_;
           if (pred->pointLookupInvolved(fName))
           {
               scanType_ = hashIndexScan;
               useIndex_ = 0;
               return OK;
           }
            }
            return ErrNotYet;
    }
    scanType_ = fullTableScan;
    return OK;
}



void* TableImpl::fetch()
{
    if (NULL == iter)
    {
        printError(ErrNotOpen,"Scan not open or Scan is closed\n");
        return NULL;
    }
    curTuple_ = iter->next();
    if (NULL == curTuple_)
    {
        return NULL;
    }
    DbRetVal lockRet = OK;
    if ((*trans)->isoLevel_ == READ_REPEATABLE) {
        lockRet = lMgr_->getSharedLock(curTuple_, trans);
        if (OK != lockRet)
        { 
            printError(lockRet, "Unable to get the lock for the tuple %x", curTuple_);
            return NULL;
        }

    }
    else if ((*trans)->isoLevel_ == READ_COMMITTED)
    {
        //if iso level is read committed, operation duration lock is sufficent 
        //so release it here itself.
        int tries = 5;
        struct timeval timeout;
        timeout.tv_sec = MUTEX_TIMEOUT_SECS;
        timeout.tv_usec = MUTEX_TIMEOUT_USECS;
        bool status = false;
        while(true) { 
            lockRet = lMgr_->isExclusiveLocked( curTuple_, status);
            if (OK != lockRet)
            { 
                printError(lockRet, "Unable to get the lock for the tuple %x", curTuple_);
                return NULL;
            }
            if (!status) break; 
            tries--;
            if (tries == 0) break;
            os::select(0, 0, 0, 0, &timeout);

        }
        if (tries == 0) 
        { 
            printError(lockRet, "Unable to get the lock for the tuple %x", curTuple_);
            return NULL;
        }
    }
    copyValuesToBindBuffer(curTuple_);
    return curTuple_;
}

DbRetVal TableImpl::insertTuple()
{
    void *tptr = ((Chunk*)chunkPtr_)->allocate(db_);
    if (NULL == tptr)
    {
        printError(ErrNoMemory, "Unable to allocate memory to store tuple");
        return ErrNoMemory;
    }
    DbRetVal ret = lMgr_->getExclusiveLock(tptr, trans);
    if (OK != ret)
    {
        ((Chunk*)chunkPtr_)->free(db_, tptr);
        printError(ret, "Could not get lock for the insert tuple %x", tptr);
        return ret;
    }
    int tupleSize = fldList_.getTupleSize ();


    ret = copyValuesFromBindBuffer(tptr);
    if (ret != OK)
    {
        printError(ret, "Unable to copy values from bind buffer");
        lMgr_->releaseLock(tptr);
        ((Chunk*)chunkPtr_)->free(db_, tptr);
        return ret;
    }
    if (NULL != indexPtr_)
    {
        int i;
        //it has index
        for (i = 0; i < numIndexes_ ; i++)
        {
            ret = insertIndexNode(*trans, indexPtr_[i], tptr);
            if (ret != OK) break;
        }
        if (i != numIndexes_ )
        {
            for (int j = 0; j < i ; j++)
                deleteIndexNode(*trans, indexPtr_[j], tptr);
            lMgr_->releaseLock(tptr);
            ((Chunk*)chunkPtr_)->free(db_, tptr);
            printError(ret, "Unable to insert index node for tuple %x", tptr);
            return ret;
        }
        
    }
    (*trans)->appendUndoLog(sysDB_, InsertOperation, tptr, tupleSize);
    return OK;
}

DbRetVal TableImpl::deleteTuple()
{
    if (NULL == curTuple_)
    {
        printError(ErrNotOpen, "Scan not open: No Current tuple");
        return ErrNotOpen;
    }
    DbRetVal ret = lMgr_->getExclusiveLock(curTuple_, trans);
    if (OK != ret)
    {
        printError(ret, "Could not get lock for the delete tuple %x", curTuple_);
        return ret;
    }

    if (NULL != indexPtr_)
    {
        int i;
        //it has index
        for (i = 0; i < numIndexes_ ; i++)
        {
            ret = deleteIndexNode(*trans, indexPtr_[i], curTuple_);
            if (ret != OK) break;
        }
        if (i != numIndexes_ )
        {
            for (int j = 0; j < i ; j++)
                insertIndexNode(*trans, indexPtr_[j], curTuple_);
            lMgr_->releaseLock(curTuple_);
            printError(ret, "Unable to insert index node for tuple %x", curTuple_);
            return ret;
        }
    }
    ((Chunk*)chunkPtr_)->free(db_, curTuple_);
    (*trans)->appendUndoLog(sysDB_, DeleteOperation, curTuple_, fldList_.getTupleSize());
    return OK;
}

DbRetVal TableImpl::updateTuple()
{
    if (NULL == curTuple_)
    {
        printError(ErrNotOpen, "Scan not open: No Current tuple");
        return ErrNotOpen;
    }
    DbRetVal ret = lMgr_->getExclusiveLock(curTuple_, trans);
    if (OK != ret)
    {
        printError(ret, "Could not get lock for the update tuple %x", curTuple_);
        return ret;
    }
    if (NULL != indexPtr_)
    {
        //it has index
        //TODO::If it fails while updating index node, we have to undo all the updates 
        //on other indexes on the table.Currently it will leave the database in an 
        //inconsistent state.
        for (int i = 0; i < numIndexes_ ; i++)
        {
            ret = updateIndexNode(*trans, indexPtr_[i], curTuple_);
            if (ret != OK)
            {
                lMgr_->releaseLock(curTuple_);
                printError(ret, "Unable to update index node for tuple %x", curTuple_);
                return ret;
            }
        }
    }
    (*trans)->appendUndoLog(sysDB_, UpdateOperation, curTuple_, fldList_.getTupleSize());
    return copyValuesFromBindBuffer(curTuple_);
}

DbRetVal TableImpl::copyValuesFromBindBuffer(void *tuplePtr)
{
    //Iterate through the bind list and copy the value here
    FieldIterator fIter = fldList_.getIterator();
    char *colPtr = (char*) tuplePtr;
    while (0 == fIter.hasElement())
    {
        FieldDef def = fIter.nextElement();
        switch(def.type_)
        {
            case typeString:
                strcpy((char*)colPtr, (char*)def.bindVal_);
                *(((char*)colPtr) + def.length_) = '\0';
                colPtr = colPtr + os::align(def.length_);
                break;
            case typeBinary:
                os::memcpy((char*)colPtr, (char*)def.bindVal_, def.length_);
                colPtr = colPtr + os::align(def.length_);
                break;
            default:
                AllDataType::copyVal(colPtr, def.bindVal_, def.type_);
                colPtr = colPtr + os::align(AllDataType::size(def.type_));
                break;
        }
    }
    return OK;
}

DbRetVal TableImpl::copyValuesToBindBuffer(void *tuplePtr)
{
    //Iterate through the bind list and copy the value here
    FieldIterator fIter = fldList_.getIterator();
    char *colPtr = (char*) tuplePtr;
    while (0 == fIter.hasElement())
    {
        FieldDef def = fIter.nextElement();
        switch(def.type_)
        {
            case typeString:
                strcpy((char*)def.bindVal_, (char*)colPtr);
                colPtr = colPtr + os::align(def.length_);
                break;
            case typeBinary:
                os::memcpy((char*)def.bindVal_, (char*)colPtr, def.length_);
                colPtr = colPtr + os::align(def.length_);
                break;
            default:
                AllDataType::copyVal(def.bindVal_, colPtr, def.type_);
                colPtr = colPtr + os::align(AllDataType::size(def.type_));
                break;
        }
    }
    return OK;
}

//-1 index not supported
DbRetVal TableImpl::insertIndexNode(Transaction *tr, void *indexPtr, void *tuple)
{
    INDEX *iptr = (INDEX*)indexPtr;
    DbRetVal ret = OK;
    Index* idx = Index::getIndex(iptr->indexType_);
    ret = idx->insert(this, tr, indexPtr, tuple);
    return ret;
}

DbRetVal TableImpl::deleteIndexNode(Transaction *tr, void *indexPtr, void *tuple)
{
    INDEX *iptr = (INDEX*)indexPtr;
    DbRetVal ret = OK;
    //CatalogTableINDEX::getMutex(indexPtr);
    Index* idx = Index::getIndex(iptr->indexType_);
    ret = idx->remove(this, tr, indexPtr, tuple);
    //CatalogTableINDEX::releaseMutex(indexPtr);
    return ret;
}


DbRetVal TableImpl::updateIndexNode(Transaction *tr, void *indexPtr, void *tuple)
{
    INDEX *iptr = (INDEX*)indexPtr;
    DbRetVal ret = OK;
    //CatalogTableINDEX::getMutex(indexPtr);
    Index* idx = Index::getIndex(iptr->indexType_);
    ret = idx->update(this, tr, indexPtr, tuple);
    //CatalogTableINDEX::releaseMutex(indexPtr);
    return ret;
}



DbRetVal TableImpl::close()
{
    if (NULL == iter)
    {
         printError(ErrNotOpen,"Scan not open");
         return ErrNotOpen;
    }
    iter->close();
    delete iter;
    iter = NULL;
    return OK;
}

TableImpl::~TableImpl()
{
    if (NULL != iter ) { delete iter; iter = NULL; }
    if (NULL != idxInfo) { delete idxInfo; idxInfo = NULL; }
    if (NULL != indexPtr_) { delete[] indexPtr_; indexPtr_ = NULL; }
    fldList_.removeAll();

}
void TableImpl::setTableInfo(char *name, int tblid, size_t  length,
                       int numFld, int numIdx, void *chunk)
{
    strcpy(tblName_, name);
    tblID_ = tblid;
    length_ = length;
    numFlds_ = numFld;
    numIndexes_ = numIdx;
    chunkPtr_ = chunk;
}

long TableImpl::spaceUsed()
{
    Chunk *chk = (Chunk*)chunkPtr_;
    long totSize = chk->getTotalDataNodes() * chk->getSize();
    totSize = totSize + (chk->totalPages() * sizeof (PageInfo));
    return totSize;
}

long TableImpl::numTuples()
{
    return ((Chunk*)chunkPtr_)->getTotalDataNodes();
}
