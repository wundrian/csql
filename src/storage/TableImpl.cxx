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

void Table::getFieldNameAlone(char *fname, char *name) {
    bool dotFound= false;
    char *fullname = fname;
    while(*fullname != '\0')
    {
        if (*fullname == '.') { dotFound = true;  break; }
        fullname++;
    }
    if (dotFound) strcpy(name, ++fullname); else strcpy(name, fname);

}
void Table::getTableNameAlone(char *fname, char *name) {
    strcpy(name, fname);
    char *start = name;
    bool dotFound = false;
    while(*name != '\0')
    {
        if (*name == '.') { *name='\0';  dotFound = true; break; }
        name++;
    }
    if (!dotFound) strcpy(start, "");
    return;
}

DbRetVal TableImpl::bindFld(const char *name, void *val)
{
    if (name[0] == '*' ) return OK;
    //set it in the field list
    char fieldName[IDENTIFIER_LENGTH];
    getFieldNameAlone((char*)name, fieldName);
    DbRetVal rv = fldList_.updateBindVal(fieldName, val);
    if (OK != rv) {
        printError(ErrNotExists, "Field %s does not exist", fieldName);
        return  rv;
    }
    return OK;
}

bool TableImpl::isFldNull(const char *name){
    if (name[0] == '*') return false;
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

int TableImpl::getFldPos(char *name)
{
    return fldList_.getFieldPosition(name);
}
bool TableImpl::isFldNull(int colpos)
{
    if (!curTuple_) return false;
    if (colpos <1 || colpos > numFlds_) return false;
    if (isIntUsedForNULL) {
        int nullVal = *(int*)((char*)curTuple_ + (length_ - 4));
        if (BITSET(nullVal, colpos)) return true;
    }
    else {
        char *nullOffset = (char*)curTuple_ - os::align(numFlds_);
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
        while(i < numFlds_) { cNullInfo[0] = 0;}
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
    bool isBitSet = false;
    if (isIntUsedForNULL) {
        if (!BITSET(iNotNullInfo, fldpos)) {
            SETBIT(iNullInfo, fldpos);
            isBitSet = true;
        }
        else { 
            printError(ErrNullViolation, "NOT NULL constraint violation");
            return ErrNullViolation;
        }
    }
    else {
        if (!BITSET(iNotNullInfo, fldpos)) cNullInfo[fldpos-1] = 1;
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
    if (isIntUsedForNULL) { 
        CLEARBIT(iNullInfo, colpos);
    }
    else
        cNullInfo[colpos-1] = 0;
    return;
}

bool TableImpl::hasIndex(char* fName)
{
   if (NULL == indexPtr_) return false;
   for (int i =0; i < numIndexes_; i++)
   {
      HashIndexInfo* info = (HashIndexInfo*) idxInfo[i];
      FieldIterator iter = info->idxFldList.getIterator();
      if(iter.hasElement())
      {
        FieldDef *def = iter.nextElement();
        if(strcmp(def->fldName_, fName) == 0)
            if(!iter.hasElement())//neglet if it is composite index
                return true;
      }
   } 
   return false;
}

IndexType TableImpl::getIndexType(char *fName, int *pos)
{
   if (NULL == indexPtr_) return unknownIndex;
   for (int i =0; i < numIndexes_; i++)
   {
      HashIndexInfo* info = (HashIndexInfo*) idxInfo[i];
      FieldIterator iter = info->idxFldList.getIterator();
      if(iter.hasElement())
      {
        FieldDef *def = iter.nextElement();
        if(strcmp(def->fldName_, fName) == 0)
            if(!iter.hasElement()) {//neglet if it is composite index
                *(int*)pos = i;
                return info->indType;
            }
      }
   } 
   *(int*)pos = -1;
   return unknownIndex;
}
void TableImpl::addPredicate(char *fName, ComparisionOp op, void *buf)
{
    char fieldName[IDENTIFIER_LENGTH];
    Table::getFieldNameAlone(fName, fieldName);
    PredicateImpl *pred = (PredicateImpl*) pred_;
    PredicateImpl *newPred = new PredicateImpl();
    newPred->setTerm(fName, op, buf);
    if (NULL == pred) { pred_ = newPred; return; }
    if (pred->isSingleTerm())
    {
       bool res = pred->appendIfSameFld(fName, op, buf);
       if(res) { 
           delete newPred;
           return; 
       }
    }
    PredicateImpl *bothPred = new PredicateImpl();
    bothPred->setTerm(pred, OpAnd, newPred);
    pred_ = bothPred;
}

DbRetVal TableImpl::optimize()
{
    //table ptr is set in predicate because it needs to access the
    //type and length to evaluate
    if( NULL != pred_)
    {
        PredicateImpl *pred = (PredicateImpl*) pred_;
        pred->setTable(this);
        pred->setProjectionList(NULL);
        pred->setOffsetAndType();
    }
    return createPlan();
} 

DbRetVal TableImpl::execute()
{
    if (NULL != iter)
    {
         //printError(ErrAlready,"Scan already open:Close and re execute");
         return ErrAlready;
    }
    DbRetVal ret = OK;
    ret = optimize();
    if (OK != ret)
    {
        printError(ErrSysInternal,"Unable to create the plan");
        return ErrSysInternal;
    }
    if (useIndex_ >= 0) 
        iter = new TupleIterator(pred_, scanType_, idxInfo[useIndex_], chunkPtr_, sysDB_->procSlot,isBetween,isPointLook);
    else if (scanType_ == fullTableScan)
        iter = new TupleIterator(pred_, scanType_, NULL, chunkPtr_, sysDB_->procSlot,isBetween,isPointLook);
    else
    {
        printError(ErrSysFatal,"Unable to create tuple iterator");//should never happen
        return ErrSysFatal;
    }
    ret = iter->open();
    if (OK != ret)
    {
        printError(ret,"Unable to open the iterator");
        return ret;
    }
    return OK;
}


DbRetVal TableImpl::createPlan()
{
    if (isPlanCreated) {
        //will do early return here. plan is generated only when setPredicate is called.
        if (scanType_ == unknownScan) return ErrSysFatal; //this should never happen
        else return OK;
    }
    isBetween=false;
    isPointLook = false;
    useIndex_ = -1;

    FieldIterator fIter = fldList_.getIterator();
    FieldDef *def = NULL;
    while ((def = fIter.nextElement())!= NULL) {
        if (NULL != def->bindVal_) bindList_.append(def);
    }
    numBindFlds_ = bindList_.size();
    bindListArray_ = (void **) malloc(numBindFlds_ * sizeof (void *));
    void *elem = NULL;
    int i = 0;
    ListIterator it = bindList_.getIterator();
    while ((elem = it.nextElement()) != NULL) bindListArray_[i++] = elem;

    //if there are no predicates then go for full scan
    //if there are no indexes then go for full scan
    if (NULL == pred_ || NULL == indexPtr_)
    {
        scanType_ = fullTableScan;
        isPlanCreated = true;
        return OK;
    }
    if (NULL != indexPtr_)
    {
       PredicateImpl *pred = (PredicateImpl*)pred_;
       printDebug(DM_Predicate, "predicate does not involve NOT , OR operator");
       if (!pred->isNotOrInvolved())
       {
           printDebug(DM_Predicate, "predicate does not involve NOT , OR operator");
          for (int i =0; i < numIndexes_; i++)
          {
              HashIndexInfo* info = (HashIndexInfo*) idxInfo[i];
              FieldIterator iter = info->idxFldList.getIterator();
              while(iter.hasElement())
              {
                FieldDef *def = iter.nextElement();
                if (pred->pointLookupInvolved(def->fldName_))
                {
                  printDebug(DM_Predicate, "point lookup involved for field %s",def->fldName_);
                  if(hashIndex == info->indType) scanType_ = hashIndexScan;
                  else scanType_ = treeIndexScan;
                  isPlanCreated = true;
                  isPointLook = true;
                  useIndex_ = i;
                }
                else if (pred->isBetweenInvolved(def->fldName_))
                {
                    if (treeIndex == info->indType)
                    {
                     scanType_ = treeIndexScan;
                     isPlanCreated = true;
                     useIndex_ = i;
                     isBetween=true;
                     break; //no composite index for tree index
                    }
                }
                else if (pred->rangeQueryInvolved(def->fldName_))
                {
                  printDebug(DM_Predicate, "range lookup involved for field %s",def->fldName_);
                  if (treeIndex == info->indType)
                  {
                     scanType_ = treeIndexScan;
                     isPlanCreated = true;
                     useIndex_ = i;
                     break; //no composite index for tree index
                  }
                }else {
                    useIndex_ = -1;
                    break;
                }
             }//while iter.hasElement()
             if (useIndex_ != -1) return OK;
           }//for
        }
    }
    scanType_ = fullTableScan;
    isPlanCreated = true;
    return OK;
}

void* TableImpl::fetch()
{
    fetchNoBind();
    if (NULL == curTuple_) return curTuple_;
    copyValuesToBindBuffer(curTuple_);
    return curTuple_;
}
void* TableImpl::fetch(DbRetVal &rv)
{
    fetchNoBind(rv);
    if (NULL == curTuple_) return curTuple_;
    copyValuesToBindBuffer(curTuple_);
    return curTuple_;
}

void* TableImpl::fetchNoBind()
{
    if (NULL == iter)
    {
        printError(ErrNotOpen,"Scan not open or Scan is closed\n");
        return NULL;
    }
    void *prevTuple = curTuple_;
    curTuple_ = iter->next();
    if (NULL == curTuple_)
    {
        return NULL;
    }
    DbRetVal lockRet = OK;
    if ((*trans)->isoLevel_ == READ_COMMITTED)
    {
        //if iso level is read committed, operation duration lock is sufficent 
        //so release it here itself.
        int tries = 5;
        struct timeval timeout;
        timeout.tv_sec = Conf::config.getMutexSecs();
        timeout.tv_usec = Conf::config.getMutexUSecs();

        bool status = false;
        while(true) { 
            lockRet = lMgr_->isExclusiveLocked( curTuple_, trans, status);
            if (OK != lockRet)
            { 
                printError(lockRet, "Unable to get the lock for the tuple %x", curTuple_);
                curTuple_ = prevTuple;
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
            curTuple_ = prevTuple;
            return NULL;
        }
    }
    else if ((*trans)->isoLevel_ == READ_REPEATABLE) {
        lockRet = lMgr_->getSharedLock(curTuple_, trans);
        if (OK != lockRet)
        { 
            printError(lockRet, "Unable to get the lock for the tuple %x", curTuple_);
            curTuple_ = prevTuple;
            return NULL;
        }

    }
    return curTuple_;
}

void* TableImpl::fetchNoBind(DbRetVal &rv)
{
    rv = OK;
    if (NULL == iter)
    {
        printError(ErrNotOpen,"Scan not open or Scan is closed\n");
        rv = ErrNotOpen;
        return NULL;
    }
    void *prevTuple = curTuple_;
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
            rv = ErrLockTimeOut;
            curTuple_ = prevTuple;
            return NULL;
        }

    }
    else if ((*trans)->isoLevel_ == READ_COMMITTED)
    {
        //if iso level is read committed, operation duration lock is sufficent
        //so release it here itself.
        int tries = 5;
        struct timeval timeout;
        timeout.tv_sec = Conf::config.getMutexSecs();
        timeout.tv_usec = Conf::config.getMutexUSecs();

        bool status = false;
        while(true) {
            lockRet = lMgr_->isExclusiveLocked( curTuple_, trans, status);
            if (OK != lockRet)
            {
                printError(lockRet, "Unable to get the lock for the tuple %x", curTuple_);
                curTuple_ = prevTuple;
                rv = ErrLockTimeOut;
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
            curTuple_ = prevTuple;
            rv = ErrLockTimeOut;
            return NULL;
        }
    }
    return curTuple_;
}
DbRetVal TableImpl::fetchAgg(const char * fldName, AggType aType, void *buf)
{
   FieldInfo *info = new FieldInfo();
   DbRetVal rv = getFieldInfo(fldName, info);
   if (OK != rv) return rv;
   bool res= false;
   if (AGG_MIN == aType || AGG_MAX == aType) {
      int pos =0;
      IndexType iType = getIndexType((char*)fldName, &pos);
      if(treeIndex == iType && pos >=0) {
          if (AGG_MIN == aType) {
              HashIndexInfo* hInfo = (HashIndexInfo*) idxInfo[pos];
              CINDEX *iptr = (CINDEX*) hInfo->indexPtr;
              TreeIter *iter = new TreeIter((TreeNode*)iptr->hashNodeChunk_);
              char *tuple = (char*) iter->getFirstElement();	
              if (tuple != NULL) {
                  AllDataType::copyVal(buf,(void*)(tuple+info->offset), 
                                   info->type, info->length);
                  delete iter; 
                  return OK;
              }
              delete iter;
          }
          else if (AGG_MAX == aType) {
              HashIndexInfo* hInfo = (HashIndexInfo*) idxInfo[pos];
              CINDEX *iptr = (CINDEX*) hInfo->indexPtr;
              TreeIter *iter = new TreeIter((TreeNode*)iptr->hashNodeChunk_);
              char *tuple = (char*) iter->getLastElement();	
              if (tuple != NULL) { 
                  AllDataType::copyVal(buf,(void*)(tuple+info->offset), 
                                   info->type, info->length);
                  delete iter;
                  return OK;
              }
              delete iter;
          }
      }
   }

   DataType type = info->type;
   int length = info->length;
   int offset = info->offset;

   if (NULL == pred_ && typeInt == type)
   { //perf opt
     ChunkIterator cIter = ((Chunk*)chunkPtr_)->getIterator();
     char *tuple =(char*)cIter.nextElement();
     if (NULL == tuple) return OK;
     int count =1;
     AllDataType::copyVal(buf, (void*) (tuple+offset), type, length);
     while(1) {
       tuple = (char*)cIter.nextElement();
       if (NULL == tuple) break;
       switch(aType) {
           case AGG_MIN:
           {
               if (*(int*)buf >= *((int*)(tuple+offset)))
                   *(int*)buf = *((int*)(tuple+offset));
               break;
           }
           case AGG_MAX:
           {
               if (*(int*)buf <= *((int*)(tuple+offset)))
                   *(int*)buf = *((int*)(tuple+offset));
               break;
           }
           case AGG_SUM:
           {
               *(int*)buf = *(int*)buf + *((int*)(tuple+offset));
               break;
           }
           case AGG_AVG:
           {
               *(int*)buf = *(int*)buf + *((int*)(tuple+offset));
               count++;
               break;
           }
           case AGG_COUNT:
           {
               count++;
               break;
           }
         }
       }
       if( AGG_AVG == aType) AllDataType::divVal(buf, &count, type);
       else if (AGG_COUNT == aType) (*(int*)buf) = count;
       delete info;
       return OK;
   }

   char *tuple = (char*) fetchNoBind(rv);
   if ( NULL == tuple)  return OK; 
   int count =1;
   AllDataType::copyVal(buf, (void*) (tuple+offset), type, length);
   while(1) {
       tuple = (char*) fetchNoBind(rv);
       if (NULL == tuple) break;
       switch(aType) {
           case AGG_MIN:
           {
               res = AllDataType::compareVal(buf, (void*) (tuple+offset), 
                               OpGreaterThanEquals,
                               type, length);
               if (res) AllDataType::copyVal(buf, (void*) (tuple+offset), 
                                     type, length);
               break;
           }
           case AGG_MAX:
           {
               res = AllDataType::compareVal(buf, (void*) (tuple+offset), 
                               OpLessThanEquals,
                               type, length);
               if (res) AllDataType::copyVal(buf, (void*) (tuple+offset), 
                                     type, length);
               break;
           }
           case AGG_SUM:
           {
               AllDataType::addVal(buf, (void*) (tuple+offset), 
                               type);
               break;
           }
           case AGG_AVG:
           {
               AllDataType::addVal(buf, (void*) (tuple+offset), 
                               type);
               count++;
               break;
           }
           case AGG_COUNT:
           {
               count++;
               break;
           }
       }
   }
   switch(aType) {
       case AGG_AVG:
       {
           AllDataType::divVal(buf, &count,type); 
           break;
       }
       case AGG_COUNT:
       {
           (*(int*)buf) = count;
           break;
       }
   }
   delete info;
   return OK;
}
DbRetVal TableImpl::insertTuple()
{
    DbRetVal ret =OK;
    void *tptr = ((Chunk*)chunkPtr_)->allocate(db_, &ret);
    if (NULL == tptr)
    {
        printError(ret, "Unable to allocate record from chunk");
        return ret;
    }
    ret = lMgr_->getExclusiveLock(tptr, trans);
    if (OK != ret)
    {
        ((Chunk*)chunkPtr_)->free(db_, tptr);
        printError(ret, "Could not get lock for the insert tuple %x", tptr);
        return ErrLockTimeOut;
    }

    curTuple_ = tptr;   
 
    ret = copyValuesFromBindBuffer(tptr);
    if (ret != OK)
    {
        printError(ret, "Unable to copy values from bind buffer");
        (*trans)->removeFromHasList(db_, tptr);
        lMgr_->releaseLock(tptr);
        ((Chunk*)chunkPtr_)->free(db_, tptr);
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
            if (ret != OK) { printError(ret, "Error in inserting to index"); break;}
        }
        if (i != numIndexes_ )
        {
            for (int j = 0; j < i ; j++) {
                printError(ErrWarning, "Deleting index node");
                deleteIndexNode(*trans, indexPtr_[j], idxInfo[j], tptr);
            }
            lMgr_->releaseLock(tptr);
            (*trans)->removeFromHasList(db_, tptr);
            ((Chunk*)chunkPtr_)->free(db_, tptr);
            //PRABA::TEMP
            //printError(ret, "Unable to insert index node for tuple %x ", tptr);
            printError(ret, "Unable to insert index node for tuple %x %d", tptr, *(int*)tptr);
            return ret;
        }
    }
    if (undoFlag)
        ret = (*trans)->appendUndoLog(sysDB_, InsertOperation, tptr, length_);
    if (ret != OK) {
        printError(ret, "Unable to create undo log for %x %d", tptr, *(int*)tptr);
        for (int j = 0; j < numIndexes_ ; j++) {
            printError(ErrWarning, "Deleting index node");
            deleteIndexNode(*trans, indexPtr_[j], idxInfo[j], tptr);
        }
        lMgr_->releaseLock(tptr);
        (*trans)->removeFromHasList(db_, tptr);
        ((Chunk*)chunkPtr_)->free(db_, tptr);
    }
    return ret;
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
        return ErrLockTimeOut;
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
            for (int j = 0; j < i ; j++)
                insertIndexNode(*trans, indexPtr_[j], idxInfo[j], curTuple_);
            lMgr_->releaseLock(curTuple_);
            (*trans)->removeFromHasList(db_, curTuple_);
            printError(ret, "Unable to insert index node for tuple %x", curTuple_);
            return ret;
        }
    }
    ((Chunk*)chunkPtr_)->free(db_, curTuple_);
    if (undoFlag)
        ret = (*trans)->appendUndoLog(sysDB_, DeleteOperation, curTuple_, length_);
    iter->prev();
    return ret;
}

int TableImpl::deleteWhere()
{
    int tuplesDeleted = 0;
    DbRetVal rv  = OK;
    rv =  execute();
    if (rv !=OK) return (int) rv;
    while(true){
        fetchNoBind( rv);
        if (rv != OK) { tuplesDeleted = (int)rv; break; }
        if (NULL == curTuple_) break;
        rv = deleteTuple();
        if (rv != OK) {
            printError(rv, "Error: Could only delete %d tuples", tuplesDeleted);
            closeScan();
            return (int) rv;
        }
        tuplesDeleted++;
    }
    closeScan();
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
    DbRetVal ret = lMgr_->getExclusiveLock(curTuple_, trans);
    if (OK != ret)
    {
        printError(ret, "Could not get lock for the update tuple %x", curTuple_);
        return ErrLockTimeOut;
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
                lMgr_->releaseLock(curTuple_);
                (*trans)->removeFromHasList(db_, curTuple_);
                printError(ret, "Unable to update index node for tuple %x", curTuple_);
                return ret;
            }
        }
    }
    if (undoFlag)
        ret = (*trans)->appendUndoLog(sysDB_, UpdateOperation, curTuple_, length_);
    if (ret != OK) return ret;
    int addSize = 0;
    int iNullVal=iNullInfo;
    if (numFlds_ < 31){ 
	addSize=4;
	if(!iNullVal){ 
            iNullInfo = *(int*)((char*)(curTuple_) + (length_- addSize));
        } 
	else
	{
            *(int*)((char*)(curTuple_) + (length_-addSize)) |= iNullInfo;    
	}
    }
    DbRetVal rv = copyValuesFromBindBuffer(curTuple_, false);
    if (rv != OK) { 
        lMgr_->releaseLock(curTuple_); 
        (*trans)->removeFromHasList(db_, curTuple_); 
        return rv; 
    }
    
    if (numFlds_ < 31) 
    {
        if (!iNullVal) { 
		*(int*)((char*)(curTuple_) + (length_-addSize)) = iNullInfo;
		iNullInfo=0;
        }
	else iNullInfo=iNullVal;
    }
    else 
    {
        addSize = os::align(numFlds_);
        //TODO::Do not do blind memcpy. It should OR each and every char
        //os::memcpy(((char*)(curTuple_) + (length_-addSize)), cNullInfo, addSize);

    }
    return OK;
}

void TableImpl::printInfo()
{
    printf("  <TableName> %s </TableName>\n", tblName_);
    printf("  <TupleCount> %d </TupleCount>\n", numTuples());
    printf("  <PagesUsed> %d </PagesUsed>\n", pagesUsed());
    printf("  <SpaceUsed> %d </SpaceUsed>\n", spaceUsed());
    printf("  <Indexes> %d <Indexes>\n", numIndexes_);
    printf("  <TupleLength> %d </TupleLength>\n", length_);
    printf("  <Fields> %d </Fields>\n", numFlds_);
    printf("  <Indexes>\n");
    for (int i =0; i<numIndexes_; i++)
        printf("<IndexName> %s </IndexName>\n", CatalogTableINDEX::getName(indexPtr_[i]));
    printf("  </Indexes>\n");

}

DbRetVal TableImpl::copyValuesFromBindBuffer(void *tuplePtr, bool isInsert)
{
    //Iterate through the bind list and copy the value here
    FieldIterator fIter = fldList_.getIterator();
    char *colPtr = (char*) tuplePtr;
    int fldpos=1;
    while (fIter.hasElement())
    {
        FieldDef *def = fIter.nextElement();
        if(def->isAutoIncrement_ && isInsert)
        {
            void *dest = AllDataType::alloc(def->type_, def->length_);
            AllDataType::copyVal(dest,ptrToAuto, def->type_, def->length_);
            if(def->bindVal_==NULL)
            {
                AllDataType::increment(colPtr, dest , def->type_);
                AllDataType::copyVal(ptrToAuto,colPtr, def->type_, def->length_);
                colPtr = colPtr + def->length_;
                fldpos++;
                free(dest);
                continue;
            }else {
                if(AllDataType::compareVal(def->bindVal_, dest, OpGreaterThan, def->type_)){
                    AllDataType::copyVal(ptrToAuto,def->bindVal_, def->type_, def->length_);
                }
                free(dest);
            }
        }
        if (def->isNull_ && !def->isDefault_ && NULL == def->bindVal_ && isInsert) 
        {
            printError(ErrNullViolation, "NOT NULL constraint violation for field %s\n", def->fldName_);
            return ErrNullViolation;
        }
        if (def->isDefault_ && NULL == def->bindVal_ && isInsert)
        {
            void *dest = AllDataType::alloc(def->type_, def->length_);
            AllDataType::convert(typeString, def->defaultValueBuf_, def->type_, dest, def->length_);
            AllDataType::copyVal(colPtr, dest, def->type_, def->length_);
            colPtr = colPtr + def->length_;
            fldpos++;
            free (dest); 
            continue;
        }
        switch(def->type_)
        {
            case typeString:
                if (NULL != def->bindVal_)
                {
		    if(!isInsert && isFldNull(fldpos)){clearNullBit(fldpos);}
                    strcpy((char*)colPtr, (char*)def->bindVal_);
                    *(((char*)colPtr) + (def->length_-1)) = '\0';
                }
                else if (!def->isNull_ && !def->bindVal_ && isInsert)  setNullBit(fldpos);
                colPtr = colPtr + def->length_;
                break;
            case typeBinary:
                if (NULL != def->bindVal_ ) 
                {
		    if(!isInsert && isFldNull(fldpos)){clearNullBit(fldpos);}
		    DbRetVal rv = AllDataType::strToValue(colPtr, (char *) def->bindVal_, def->type_, def->length_);
                    if (rv != OK) return ErrBadArg;
		}
                else if (!def->isNull_ && isInsert && !def->bindVal_)  setNullBit(fldpos);
                colPtr = colPtr + def->length_;
                break;
            default:
                if (NULL != def->bindVal_){
		    if(!isInsert && isFldNull(fldpos)){clearNullBit(fldpos);}
                    AllDataType::copyVal(colPtr, def->bindVal_, def->type_);}
                else { if (!def->isNull_ && isInsert)  setNullBit(fldpos); }
                colPtr = colPtr + def->length_;
                break;
        }
        fldpos++;
    }
    return OK;
}
void TableImpl::clearNullBit(int fldpos)
{
    if (isIntUsedForNULL){
        CLEARBIT(iNullInfo, fldpos);}
    else
        cNullInfo[fldpos-1] = 0;
}
void TableImpl::setNullBit(int fldpos)
{
    if (isIntUsedForNULL) 
        SETBIT(iNullInfo, fldpos);
    else
        cNullInfo[fldpos-1] = 1;
}
DbRetVal TableImpl::copyValuesToBindBuffer(void *tuplePtr)
{
    //Iterate through the bind list and copy the value here
    char *colPtr = (char*) tuplePtr;
    FieldDef *def = NULL;
    for (int i = 0; i < numBindFlds_; i++) {
       def = (FieldDef *) bindListArray_[i];
       colPtr =  (char *) tuplePtr + def->offset_;
       AllDataType::copyVal(def->bindVal_, colPtr, def->type_, def->length_);
    }
    return OK;
}

//-1 index not supported
DbRetVal TableImpl::insertIndexNode(Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple)
{
    CINDEX *iptr = (CINDEX*)indexPtr;
    DbRetVal ret = OK;
    printDebug(DM_Table, "Inside insertIndexNode type %d", iptr->indexType_);
    Index* idx = Index::getIndex(iptr->indexType_);
    ret = idx->insert(this, tr, indexPtr, info, tuple,undoFlag);
    return ret;
}

DbRetVal TableImpl::deleteIndexNode(Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple)
{
    CINDEX *iptr = (CINDEX*)indexPtr;
    DbRetVal ret = OK;
    Index* idx = Index::getIndex(iptr->indexType_);
    ret = idx->remove(this, tr, indexPtr, info, tuple, undoFlag);
    return ret;
}
void TableImpl::printSQLIndexString()
{
    CatalogTableINDEXFIELD cIndexField(sysDB_);
    char fName[IDENTIFIER_LENGTH];
    char *fldName = fName; 
    char idxName[IDENTIFIER_LENGTH];
    DataType type;
    for (int i = 0; i < numIndexes_ ; i++)
    {
        CINDEX *iptr = (CINDEX*) indexPtr_[i];
        sprintf(idxName,"%s_idx_Auto_increment",getName());
        if(strcmp(iptr->indName_,idxName)==0){ continue; }
        printf("CREATE INDEX %s on %s ( ", iptr->indName_, getName());
        FieldList fldList;
        cIndexField.getFieldInfo(iptr, fldList);
        FieldIterator fIter = fldList.getIterator();
        bool firstFld = true;
        while(fIter.hasElement())
        {
            FieldDef *def = fIter.nextElement();
            if (firstFld) { printf(" %s ", def->fldName_); firstFld = false; }
            else printf(" ,%s ", def->fldName_);
        }
        printf(" ) ");
        if (iptr->indexType_ == hashIndex) printf(" HASH ");
        else printf(" TREE ");
        if (((HashIndexInfo*) idxInfo[i])->isUnique) printf(" UNIQUE");
        if(((HashIndexInfo*) idxInfo[i])->noOfBuckets != 1009 ) printf(" SIZE %d ",((HashIndexInfo*) idxInfo[i])->noOfBuckets );
        printf(";\n");
    }
}


DbRetVal TableImpl::updateIndexNode(Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple)
{
    CINDEX *iptr = (CINDEX*)indexPtr;
    DbRetVal ret = OK;
    Index* idx = Index::getIndex(iptr->indexType_);
    //TODO::currently it updates irrespective of whether the key changed or not 
    //because of this commenting the whole index update code. relook at it and uncomment

    ret = idx->update(this, tr, indexPtr, info, tuple, undoFlag);

    return ret;
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

int TableImpl::pagesUsed()
{
    Chunk *chk = (Chunk*)chunkPtr_;
    return chk->totalPages();
}

long TableImpl::numTuples()
{
    return ((Chunk*)chunkPtr_)->getTotalDataNodes();
}

List TableImpl::getFieldNameList()
{
    List fldNameList;
    FieldIterator fIter = fldList_.getIterator();
    char fieldName[IDENTIFIER_LENGTH];
    while (fIter.hasElement())
    {
        FieldDef *def = fIter.nextElement();
        Identifier *elem = new Identifier();
        Table::getFieldNameAlone(def->fldName_, fieldName);
        sprintf(elem->name, "%s.%s", getName(), fieldName); 
        fldNameList.append(elem);
    } 
    return fldNameList;
}
DbRetVal TableImpl::close()
{
    if (iter) { iter->close(); delete iter; iter = NULL; }
    printDebug(DM_Database,"Closing table handle: %x", this);
    //table->unlock();
    delete pred_;
    delete this;
    logFinest(logger, "Closing Table");
    return OK;
}

DbRetVal TableImpl::closeScan()
{
    //do not throw scan not open error
    //this function will be called by table handle
    if (iter) {
        // iter->reset();
        //PRABA::TEMP::otherwise fails.check with kishor
        delete iter;
        iter = NULL;
    }
    return OK;
}
DbRetVal TableImpl::lock(bool shared)
{

    DbRetVal ret = OK;
/*
    if (shared) 
        ret = lMgr_->getSharedLock(chunkPtr_, NULL);
    else 
        ret = lMgr_->getExclusiveLock(chunkPtr_, NULL);
    if (OK != ret)
    {
        printError(ret, "Could not exclusive lock on the table %x", chunkPtr_);
    }else {
        //do not append for S to X upgrade
        if (!ProcessManager::hasLockList.exists(chunkPtr_)) 
            ProcessManager::hasLockList.append(chunkPtr_);
    }
*/
    return ret;
}
DbRetVal TableImpl::unlock()
{
/*
    if (!ProcessManager::hasLockList.exists(chunkPtr_)) return OK;
    DbRetVal ret = lMgr_->releaseLock(chunkPtr_);
    if (OK != ret)
    {
        printError(ret, "Could not release exclusive lock on the table %x", chunkPtr_);
    }else
    {
        ProcessManager::hasLockList.remove(chunkPtr_);
    }
*/
    return OK;
}

TableImpl::~TableImpl()
{
    if (NULL != iter ) { delete iter; iter = NULL; }
    if (NULL != indexPtr_) { delete[] indexPtr_; indexPtr_ = NULL;  }
    if (NULL != idxInfo) 
    {
        for (int i = 0; i < numIndexes_; i++) delete idxInfo[i];
        delete[] idxInfo; 
        idxInfo = NULL; 
    }
    if (numFlds_ > 31 && cNullInfo != NULL) { free(cNullInfo); cNullInfo = NULL; }
    if (bindList_.size()) bindList_.reset();
    if (bindListArray_) { free (bindListArray_); bindListArray_ = NULL; }
    fldList_.removeAll();

}

void *TableImpl::getBindFldAddr(const char *name)
{
	return fldList_.getBindField(name);
}
bool TableImpl::isTableInvolved(char  *tblName)
{
    //printf("Table isTableInvolved called for %s with %s\n", tblName, getName());
    if (0 == strcmp(getName(), tblName)) return true; else return false;
}
bool TableImpl::pushPredicate(Predicate *pred)
{
    bool ret = false;
    PredicateImpl *pImpl = (PredicateImpl*) pred;
    char tableName[IDENTIFIER_LENGTH];
    Table::getTableNameAlone(pImpl->getFldName1(), tableName);
    //printf("predicate tbl name %s\n", tableName);

    //if predicate is of form t1.f1=t2.f1 then do not push here
    if (0 != strcmp(pImpl->getFldName2(),"")) return ret;

    if (0 == strcmp(getName(), tableName))
    {
        setPredicate(pred);
        //printf("PRABA::pushed predicate in tablehdl  %s\n", getName());
        ret = true;
    }
    return ret;
}
void TableImpl::setPredicate(Predicate *pred)
{
    if (NULL == pred_) { pred_ = pred; return; }
    Predicate *curPred = pred_;
    PredicateImpl *newPred = new PredicateImpl();
    newPred->setTerm(curPred, OpAnd, pred);
    newPred->setTable(this);
    pred_ = newPred;
    return;
}
void TableImpl::printPlan(int space)
{
    char spaceBuf[IDENTIFIER_LENGTH];
    memset(spaceBuf, 32, IDENTIFIER_LENGTH);
    spaceBuf[space] = '\0';
    printf("%s <TABLE-NODE>\n", spaceBuf);
    printf("%s <NAME> %s </NAME>\n", spaceBuf, getName());
    printf("%s <ScanType> %s </ScanType>\n", spaceBuf, ScanTypeNames[scanType_]);
    PredicateImpl *pred = (PredicateImpl*)pred_;
    if (pred) pred->print(space+2);
    printf("%s </TABLE-NODE>\n", spaceBuf);
}

