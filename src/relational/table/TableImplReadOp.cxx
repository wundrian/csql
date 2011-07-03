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
    DbRetVal rv = createPlan();
    if (rv != OK) return rv;
    if (iter) { iter->close(); delete iter; iter = NULL; }
    if (useIndex_ >= 0)
        iter = new TupleIterator(pred_, scanType_, idxInfo[useIndex_], chunkPtr_, sysDB_->procSlot,isBetween,isPointLook,shouldNullSearch);
    else if (scanType_ == fullTableScan)
        iter = new TupleIterator(pred_, scanType_, NULL, chunkPtr_, sysDB_->procSlot,isBetween,isPointLook,shouldNullSearch);
    else
    {
        printError(ErrSysFatal,"Unable to create tuple iterator");
        //should never happen
        return ErrSysFatal;
    }
    iter->setPlan();
    return OK;
} 

DbRetVal TableImpl::execute()
{
    if (iter && !iter->isIterClosed())
    {
         //printError(ErrAlready,"Scan already open:Close and re execute");
         return ErrAlready;
    }
    DbRetVal ret = OK;
    if (!isPlanCreated) ret = optimize();
    if (OK != ret)
    {
        printError(ErrSysInternal,"Unable to create the plan");
        return ErrSysInternal;
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
    if (bindListArray_) { ::free(bindListArray_); bindListArray_ = NULL; }
    bindListArray_ = (void **) malloc(numBindFlds_ * sizeof (void *));
    void *elem = NULL;
    int i = 0;
    ListIterator it = bindList_.getIterator();
    while ((elem = it.nextElement()) != NULL) bindListArray_[i++] = elem;
    scanType_ = fullTableScan;
    isPlanCreated = true;

    //if there are no predicates then go for full scan
    //if there are no indexes then go for full scan
    if (NULL == pred_ || NULL == indexPtr_)
    {
        return OK;
    }
    if (NULL != indexPtr_)
    {
       PredicateImpl *pred = (PredicateImpl*)pred_;
       //If searching for IS NULL or IS NOT NULL then fullscan
       if(pred->isIsNullInvolved())
       {
           scanType_ = fullTableScan;
           shouldNullSearch=true;
           return OK;
       }
       printDebug(DM_Predicate, "predicate does not involve NOT , OR operator");
       if (!pred->isNotOrInvolved())
       {
           printDebug(DM_Predicate, "predicate does not involve NOT , OR operator");
          for (int i =0; i < numIndexes_; i++)
          {
              bool isAllFldPointLookup = true;
              HashIndexInfo* info = (HashIndexInfo*) idxInfo[i];
              FieldIterator iter = info->idxFldList.getIterator();
              int noOfIfld =0;
              while(iter.hasElement())
              {
                noOfIfld++;
                FieldDef *def = iter.nextElement();
                if (pred->pointLookupInvolved(def->fldName_))
                {
                  if (!isAllFldPointLookup) break;
                  printDebug(DM_Predicate, "point lookup involved for field %s",def->fldName_);
                  if(hashIndex == info->indType) 
                      scanType_ = hashIndexScan;
                  else if (trieIndex == info->indType)
                      scanType_ = trieIndexScan;
                  else 
                      scanType_ = treeIndexScan;
                  isPointLook = true;
                  useIndex_ = i;
                }
                else if (pred->isBetweenInvolved(def->fldName_))
                {
                    if (treeIndex == info->indType)
                    {
                     scanType_ = treeIndexScan;
                     useIndex_ = i;
                     isBetween=true;
                     break; //no composite index for tree index
                    } else isAllFldPointLookup= false;
                }
                else if (pred->rangeQueryInvolved(def->fldName_))
                {
                  printDebug(DM_Predicate, "range lookup involved for field %s",def->fldName_);
                  if (treeIndex == info->indType)
                  {
                     scanType_ = treeIndexScan;
                     useIndex_ = i;
                     break; //no composite index for tree index
                  } else isAllFldPointLookup=false;
                }else {
                    useIndex_ = -1;
                    isAllFldPointLookup = false;
                    break;
                }
             }//while iter.hasElement()
             if( noOfIfld == 1 && useIndex_ != -1)return OK; 
             if (!isAllFldPointLookup && useIndex_ != -1) return OK;
           }//for
        }
    }
    scanType_ = fullTableScan;
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
    if (!loadFlag) {
    if ((*trans)->isoLevel_ == READ_COMMITTED)
    {
        //if iso level is read committed, operation duration lock is sufficent 
        //so release it here itself.
        int tries = Conf::config.getMutexRetries();
        struct timeval timeout, timeval;
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
            timeval.tv_sec = timeout.tv_sec;
            timeval.tv_usec = timeout.tv_usec;
            os::select(0, 0, 0, 0, &timeval);
        }
        if (tries == 0) 
        { 
            printError(lockRet, "Unable to get the lock for the tuple %x", curTuple_);
            curTuple_ = prevTuple;
            return NULL;
        }
    }
    else if ((*trans)->isoLevel_ == READ_REPEATABLE) {
        if (OK != trySharedLock(curTuple_, trans))
        { 
            printError(lockRet, "Unable to get the lock for the tuple %x", curTuple_);
            curTuple_ = prevTuple;
            return NULL;
        }

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
    if (!loadFlag) {
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
        int tries = Conf::config.getMutexRetries();
        //struct timeval timeout;
        //timeout.tv_sec = Conf::config.getMutexSecs();
        //timeout.tv_usec = Conf::config.getMutexUSecs();

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
            //os::select(0, 0, 0, 0, &timeout);
        }
        if (tries == 0)
        {
            printError(lockRet, "Unable to get the lock for the tuple %x", curTuple_);
            curTuple_ = prevTuple;
            rv = ErrLockTimeOut;
            return NULL;
        }
    }
    }
    return curTuple_;
}

DbRetVal TableImpl::fetchAgg(const char * fldName, AggType aType, void *buf, bool &noRec)
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
              TreeNode *fstNode=(TreeNode *)iptr->hashNodeChunk_;
              TreeIter *iter=NULL;
              if(fstNode!=NULL){
                  TreeNode *start = (TreeNode *)*((char**)((char*)fstNode + sizeof(TreeNode)));
                  iter = new TreeIter(start,(TreeNode*)iptr->hashNodeChunk_,sysDB_->procSlot);
              }else{
                  iter = new TreeIter(NULL,(TreeNode*)iptr->hashNodeChunk_,sysDB_->procSlot);
              }
              char *tuple = (char*) iter->getFirstElement();	
              if (tuple != NULL) {
                  AllDataType::copyVal(buf,(void*)(tuple+info->offset), 
                                   info->type, info->length);
                  delete iter; 
                  return OK;
              }
              delete iter; iter = NULL;
          }
          else if (AGG_MAX == aType) {
              HashIndexInfo* hInfo = (HashIndexInfo*) idxInfo[pos];
              CINDEX *iptr = (CINDEX*) hInfo->indexPtr;
              TreeNode *fstNode=(TreeNode *)iptr->hashNodeChunk_;
              TreeIter *iter=NULL;
              if(fstNode!=NULL){
                  TreeNode *start = (TreeNode *)*((char**)((char*)fstNode + sizeof(TreeNode)));
                  iter = new TreeIter(start,(TreeNode*)iptr->hashNodeChunk_,sysDB_->procSlot);
              }else{
                  iter = new TreeIter(NULL,(TreeNode*)iptr->hashNodeChunk_,sysDB_->procSlot);
              }
              char *tuple = (char*) iter->getLastElement();	
              if (tuple != NULL) { 
                  AllDataType::copyVal(buf,(void*)(tuple+info->offset), 
                                   info->type, info->length);
                  delete iter; iter = NULL;
                  return OK;
              }
              delete iter; iter=NULL;
          }
      }
   }else if (AGG_COUNT == aType) {
       (*(int*)buf) = 0;
   }


   DataType type = info->type;
   int length = info->length;
   int offset = info->offset;
   int colPos = fldList_.getFieldPosition(fldName);
   bool isNullable= true;
   if (info->isNull || info->isPrimary || info->isDefault || info->isAutoIncrement) {
       isNullable = false;
   }
   int nullOffset = length_-4;
   if (aType == AGG_COUNT) {
       length = sizeof(int);
       type = typeInt;
   }
   if (NULL == pred_ && typeInt == type && aType != AGG_AVG)
   { //perf opt
     ChunkIterator cIter = ((Chunk*)chunkPtr_)->getIterator();
     char *tuple =(char*)cIter.nextElement();
     if (NULL == tuple) { 
         *(int *) buf = 0;
         noRec = true; 
         return OK; 
     }
     int count =1;
     if (isNullable) {
         if (isIntUsedForNULL) {
                if (BITSET(*(int*)(tuple+nullOffset), colPos-1)) count =0;
         }
         else {
              curTuple_= tuple;
              if(isFldNull(colPos)) count =0;
         }
     }
     if (aType != AGG_COUNT)
         AllDataType::copyVal(buf, (void*) (tuple+offset), type, length);
     void *prev=NULL;
     prev = curTuple_;
     cIter.pageSize = PAGE_SIZE;
     while(1) 
     {
         tuple = (char*)cIter.nextElementInt();
         if (NULL == tuple) break;
         if (isNullable) {
             if (isIntUsedForNULL) {
                 if (BITSET(*(int*)(tuple+nullOffset), colPos-1)) continue;
             }
             else {
                 curTuple_= tuple;
                 if(isFldNull(colPos)) continue;
             }
         }
         if (aType == AGG_MIN)
         {
             if (*(int*)buf >= *((int*)(tuple+offset)))
                 *(int*)buf = *((int*)(tuple+offset));
         }
         else if (aType == AGG_MAX)
         {
             if (*(int*)buf <= *((int*)(tuple+offset)))
                 *(int*)buf = *((int*)(tuple+offset));
         }
         else if (aType == AGG_SUM)
         {
             *(int*)buf += *((int*)(tuple+offset));
         }
         else if (aType == AGG_AVG)
         {
             *(int*)buf = *(int*)buf + *((int*)(tuple+offset));
             count++;
         }
         else if (aType == AGG_COUNT)
         {
             count++;
         }
      }
      curTuple_= prev;
      if( AGG_AVG == aType) AllDataType::divVal(buf, &count, type);
      else if (AGG_COUNT == aType) (*(int*)buf) = count;
      delete info;
      return OK;
   }

   char *tuple = (char*) fetchNoBind(rv);
   if ( NULL == tuple) { noRec = true; return OK; }
   int count =1;

   while(isFldNull(colPos)) {
       tuple= (char*) fetchNoBind(rv);
       if (aType == AGG_COUNT) count++;
       if (tuple) break;
   }
   if ( NULL == tuple) { noRec = true; return OK; }

   if (aType == AGG_AVG) {
       AllDataType::convertToDouble(buf, (void*) (tuple+offset), type);
   } else if (aType != AGG_COUNT) {
       AllDataType::copyVal(buf, (void*) (tuple+offset), type, length);
   }
   while(1) {
       tuple = (char*) fetchNoBind(rv);
       if (NULL == tuple) break;
       if (isNullable) {
           if (isIntUsedForNULL) {
               if (BITSET(*(int*)(tuple+nullOffset), colPos-1)) continue;
           }
           else {
               curTuple_= tuple;
               if(isFldNull(colPos)) continue;
           }
       }
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
               double tmpBuf=0.0;
               AllDataType::convertToDouble(&tmpBuf, (void*) (tuple+offset), type);
               AllDataType::addVal(buf, &tmpBuf, typeDouble);
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
           AllDataType::divVal((double *)buf, count, type); 
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

long TableImpl::numTuples()
{
    return ((Chunk*)chunkPtr_)->getTotalDataNodes();
}

DbRetVal TableImpl::closeScan()
{
    //do not throw scan not open error
    //this function will be called by table handle
    if (iter) {
        iter->close();
    }
    return OK;
}

bool TableImpl::pushPredicate(Predicate *pred)
{
    bool ret = false;
    PredicateImpl *pImpl = (PredicateImpl*) pred;
    char tableName[IDENTIFIER_LENGTH];
    Table::getTableNameAlone(pImpl->getFldName1(), tableName);
    //printf("predicate tbl name %s\n", tableName);

    //if predicate is of form t1.f1=t2.f1 then do not push here
    bool isAliasSet = (0 !=strcmp(getAliasName(),"")) ;
    if (0 != strcmp(pImpl->getFldName2(),"")) return ret;

    if (0 == strcmp(getName(), tableName) ||(isAliasSet && 0 == strcmp(getAliasName(), tableName)))
    {
        setPredicate(pred);
        //printf("PRABA::pushed predicate in tablehdl  %s\n", getName());
        ret = true;
    }
    return ret;
}
