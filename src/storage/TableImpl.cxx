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

DbRetVal TableImpl::bindFld(const char *name, void *val, bool isNullExpl)
{
    if (name[0] == '*' ) return OK;
    //set it in the field list
    char fieldName[IDENTIFIER_LENGTH];
    getFieldNameAlone((char*)name, fieldName);
    DbRetVal rv = fldList_.updateBindVal(fieldName, val, isNullExpl);
    if (OK != rv) {
        printError(ErrNotExists, "Field %s does not exist", fieldName);
        return  rv;
    }
    return OK;
}

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

int TableImpl::getFldPos(char *name)
{
    return fldList_.getFieldPosition(name);
}
void TableImpl::setAliasName(char *name)
{
    strcpy(aliasName, name);
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
    if (NULL == pred) { pred_ = newPred; predList.append(newPred); return; }
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
    predList.append(bothPred);
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
                  if(hashIndex == info->indType) scanType_ = hashIndexScan;
                  else scanType_ = treeIndexScan;
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
DbRetVal TableImpl::trySharedLock(void *curTuple, Transaction **trans)
{
    DbRetVal lockRet = OK;
    int tries = Conf::config.getMutexRetries();
    while((lockRet = lMgr_->getSharedLock(curTuple_, trans)) == ErrLockTimeOut)
    {
        tries--;
        if (tries <=0) break;
    }
    return lockRet;
}
DbRetVal TableImpl::tryExclusiveLock(void *curTuple, Transaction **trans)
{
    DbRetVal lockRet = OK;
    int tries = Conf::config.getMutexRetries();
    while((lockRet = lMgr_->getExclusiveLock(curTuple_, trans)) == ErrLockTimeOut)
    {
        tries--;
        if (tries <=0) break;
    }
    return lockRet;
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
DbRetVal TableImpl::getCheckpointMutex()
{
   int tries=0;
   DbRetVal rv = OK;
   int totalTries = Conf::config.getMutexRetries();
   struct timeval timeout, timeval;
   timeout.tv_sec = Conf::config.getMutexSecs();
   timeout.tv_usec = Conf::config.getMutexUSecs();

   while (tries < totalTries)
   {
        rv =  sysDB_->getSCheckpointMutex();
        if (OK == rv) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0,0,0,0,&timeval);
        tries++;
   }
   if (tries == totalTries) {
      printError(ErrLockTimeOut, "Checkpoint server is running. Retry after sometime.");
      return ErrLockTimeOut;
   }
   return OK;
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
long long TableImpl::getLastInsertedVal(DbRetVal &rv)
{
    rv=OK;
    return *(long long*)ptrToAuto;
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
            if (OK != takeTableMutex())
            {
                printError(ErrLockTimeOut,
                  " Unable to take table mutex for increment key");
                return ErrLockTimeOut;
            }
            AllDataType::copyVal(&tempAutoVal,ptrToAuto, def->type_, def->length_);
            if(def->bindVal_==NULL)
            {
                AllDataType::increment(colPtr, &tempAutoVal , def->type_);
                AllDataType::copyVal(ptrToAuto,colPtr, def->type_,
                                                                 def->length_);
                colPtr = colPtr + def->length_;
                fldpos++;
            }else {
                if(AllDataType::compareVal(def->bindVal_, &tempAutoVal, OpGreaterThan,
                                                                 def->type_)) {
                    AllDataType::copyVal(ptrToAuto,def->bindVal_, def->type_,
                                                                 def->length_);
                }
            }
            releaseTableMutex();
            continue;
        }

        if (def->isNull_ && !def->isDefault_ && NULL == def->bindVal_ && 
                                                                      isInsert) 
        {
            printError(ErrNullViolation, 
                  "NOT NULL constraint violation for field %s", def->fldName_);
            return ErrNullViolation;
        }
        if (def->isDefault_ && NULL == def->bindVal_ && isInsert)
        {
            if (! def->isNullExplicit_) {
                if (def->type_ == typeVarchar) {
                    DbRetVal rv = OK;
                    void *ptr =
                     ((Chunk *) vcChunkPtr_)->allocate(db_, def->length_, &rv);
                    *(long *)colPtr = (long)ptr;
                    AllDataType::convert(typeString, def->defaultValueBuf_, 
                                                def->type_, ptr, def->length_);
                } else {
                    void *dest = AllDataType::alloc(def->type_, def->length_);
                    AllDataType::convert(typeString, def->defaultValueBuf_, 
                                               def->type_, dest, def->length_);
                    AllDataType::copyVal(colPtr, dest, def->type_, 
                                                                 def->length_);
                    free (dest);
                }
            } else {
                setNullBit(fldpos);
                *(long *) colPtr = 0L;
            }
            if (def->type_ != typeVarchar) colPtr = colPtr + def->length_;
            else colPtr = colPtr + sizeof(void *);
            fldpos++;
            continue;
        }
        switch(def->type_)
        {
            case typeString:
                if (NULL != def->bindVal_)
                {
		            if(!isInsert && isFldNull(fldpos)){clearNullBit(fldpos);}
                //    strncpy((char*)colPtr, (char*)def->bindVal_, def->length_);
                //    *(((char*)colPtr) + (def->length_-1)) = '\0';
                    strcpy((char*)colPtr, (char*)def->bindVal_);
                } 
                else if (!def->isNull_ && isInsert) setNullBit(fldpos);
                colPtr = colPtr + def->length_;
                break;
            case typeBinary:
                if (NULL != def->bindVal_ ) 
                {
		            if(!isInsert && isFldNull(fldpos)){clearNullBit(fldpos);}
		            DbRetVal rv = AllDataType::strToValue(colPtr, 
                             (char *) def->bindVal_, def->type_, def->length_);
                    if (rv != OK) return ErrBadArg;
		        } else if (!def->isNull_ && isInsert && !def->bindVal_) {
                    setNullBit(fldpos);
                }
                colPtr = colPtr + def->length_;
                break;
            case typeVarchar: 
                if (NULL != def->bindVal_) {
                    if (!isInsert && isFldNull(fldpos)) {clearNullBit(fldpos);}
                    DbRetVal rv = OK;
                    if (!isInsert) {
                        if (*(long *) colPtr != 0L)
                           ((Chunk *) vcChunkPtr_)->free(db_,
                                                      (void *)*(long *)colPtr);
                        *(long *) colPtr = 0L;
                    }
                    if (strcmp((char *)def->bindVal_,"") != 0) {
                        void *ptr = 
                             ((Chunk *) vcChunkPtr_)->allocate(db_, 
                                                            def->length_, &rv);
                        if (rv != OK) return ErrBadArg;
                        *(long *)colPtr = (long)ptr;
                        strcpy((char *)ptr, (char *)def->bindVal_); 
                    } else {  setNullBit(fldpos); } 
                } else if (!def->isNull_ && isInsert) setNullBit(fldpos);
                colPtr = colPtr + sizeof(void *); 
                break;
            default:
                if (NULL != def->bindVal_) {
		            if(!isInsert && isFldNull(fldpos)){clearNullBit(fldpos);}
                    AllDataType::copyVal(colPtr, def->bindVal_, def->type_);
                } else { if (!def->isNull_ && isInsert) setNullBit(fldpos); }
                colPtr = colPtr + def->length_;
                break;
        }
        fldpos++;
    }
        return OK;
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

DbRetVal TableImpl::copyValuesToBindBuffer(void *tuplePtr)
{
    //Iterate through the bind list and copy the value here
    char *colPtr = (char*) tuplePtr;
    FieldDef *def = NULL;
    for (int i = 0; i < numBindFlds_; i++) {
       def = (FieldDef *) bindListArray_[i];
       colPtr =  (char *) tuplePtr + def->offset_;
       if (def->type_ != typeVarchar)
           AllDataType::copyVal(def->bindVal_, colPtr, def->type_, 
                                                                 def->length_);
       else {
           char *ptr = (char *) *(long *) colPtr;
           if (ptr != NULL) strcpy((char *)def->bindVal_, ptr);
       }
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
void TableImpl::printSQLIndexString(FILE *fp, int fd)
{
    if (fp == NULL) fp = stdout;
    CatalogTableINDEXFIELD cIndexField(sysDB_);
    char fName[IDENTIFIER_LENGTH];
    char idxName[IDENTIFIER_LENGTH];
    char *fldName = fName; 
    DataType type;
    for (int i = 0; i < numIndexes_ ; i++)
    {
        CINDEX *iptr = (CINDEX*) indexPtr_[i];
        sprintf(idxName,"%s_idx_Auto_increment",getName());
        if(strcmp(iptr->indName_,idxName)==0){ continue; }
        if (Conf::config.useDurability()) {
            struct Object obj;
            strcpy(obj.name, iptr->indName_);
            if (iptr->indexType_ == hashIndex) {
                obj.type = hIdx;
                obj.bucketChunk = ((Chunk *)iptr->chunkPtr_)->getFirstPage();
                obj.firstPage = ((Chunk *)iptr->hashNodeChunk_)->getFirstPage();
                obj.curPage = ((Chunk *)iptr->hashNodeChunk_)->getCurrentPage();
            } else if (iptr->indexType_ == treeIndex) {
                obj.type = tIdx;
                obj.firstPage = ((Chunk *)iptr->chunkPtr_)->getFirstPage();
                obj.curPage = ((Chunk *)iptr->chunkPtr_)->getCurrentPage();
                long nodes = ((Chunk *)iptr->chunkPtr_)->getTotalDataNodes();
                if(nodes) {
                    ChunkIterator cIter = ((Chunk *)iptr->chunkPtr_)->getIterator();
                    obj.bucketChunk = cIter.nextElement();
                } else obj.bucketChunk = NULL;
            } 
            void *buf = &obj;
            write(fd, buf, sizeof(obj));
        }
        fprintf(fp, "CREATE INDEX %s on %s ( ", iptr->indName_, getName());
        FieldList fldList;
        cIndexField.getFieldInfo(iptr, fldList);
        FieldIterator fIter = fldList.getIterator();
        bool firstFld = true;
        while(fIter.hasElement())
        {
            FieldDef *def = fIter.nextElement();
            if (firstFld) { fprintf(fp, " %s ", def->fldName_); firstFld = false; }
            else fprintf(fp, " ,%s ", def->fldName_);
        }
        fldList.removeAll(); 
        fprintf(fp, " ) ");
        if (iptr->indexType_ == hashIndex) fprintf(fp, " HASH ");
        else fprintf(fp, " TREE ");
        if (((HashIndexInfo*) idxInfo[i])->isUnique) fprintf(fp, " UNIQUE"); 
        if(((HashIndexInfo*) idxInfo[i])->noOfBuckets != 1009 ) fprintf(fp, " SIZE %d ",((HashIndexInfo*) idxInfo[i])->noOfBuckets ); 
        fprintf(fp, ";\n");
    }
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


void TableImpl::setTableInfo(char *name, int tblid, size_t  length,
                       int numFld, int numIdx, void *chunk, void *vcchunk)
{
    strcpy(tblName_, name);
    tblID_ = tblid;
    length_ = length;
    numFlds_ = numFld;
    numIndexes_ = numIdx;
    chunkPtr_ = chunk;
    vcChunkPtr_ = vcchunk;
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
    TableImpl *fkTbl =NULL;
    ListIterator tblIter = tblList.getIterator();
    tblIter.reset();
    while (tblIter.hasElement()){
        fkTbl = (TableImpl *) tblIter.nextElement();
        fkTbl->close();
    }
    tblList.reset();
    tblIter = tblFkList.getIterator();
    tblIter.reset();
    while (tblIter.hasElement()){
        fkTbl = (TableImpl *) tblIter.nextElement();
        fkTbl->close();
    }
    tblFkList.reset();
    printDebug(DM_Database,"Closing table handle: %x", this);
    //table->unlock();
    //delete pred_;
    ListIterator pIter = predList.getIterator();
    while (pIter.hasElement())
    {
        PredicateImpl *pImpl = (PredicateImpl*) pIter.nextElement();
        delete pImpl;
    }
    predList.reset();
    delete this;
    logFinest(Conf::logger, "Closing Table");
    return OK;
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
DbRetVal TableImpl::takeTableMutex()
{
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = sysDB_->getAllocDatabaseMutex();
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;
}
DbRetVal TableImpl::releaseTableMutex()
{
    sysDB_->releaseAllocDatabaseMutex();
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
    if (numFlds_ > 32 && cNullInfo != NULL) { 
        free(cNullInfo); cNullInfo = NULL; 
    }
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

void TableImpl::setCondition(Condition *p)
{ 
    isPlanCreated = false; 
    ListIterator pIter = predList.getIterator();
    while (pIter.hasElement())
    {
        PredicateImpl *pImpl = (PredicateImpl*) pIter.nextElement();
        delete pImpl;
    }
    predList.reset();

    if (p) pred_ = p->getPredicate(); else pred_ = NULL;
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
void TableImpl::printSQLForeignString()
{
    DbRetVal rv=OK;
    FieldNameList pkFieldList,fkFieldList;
    void *tPkptr =NULL;
    void *tFkptr = NULL;
    void *chunkPk = NULL;
    void *vcchunkPk = NULL;
    CatalogTableTABLE cTable(sysDB_);
    TableImpl *fkTbl =NULL;
    ListIterator tblIter = tblList.getIterator();
    tblIter.reset();
    int firstFK=true;
    while (tblIter.hasElement()){
        fkTbl = (TableImpl *) tblIter.nextElement();
        rv = cTable.getChunkAndTblPtr(fkTbl->getName(), chunkPk, tPkptr,vcchunkPk);
        if ( OK != rv){return ;}
        rv = cTable.getChunkAndTblPtr(getName(), chunkPk, tFkptr, vcchunkPk);
        if ( OK != rv){return ;}
        CatalogTableFK cFk(sysDB_);
        rv = cFk.getPkFkFieldInfo(tPkptr,tFkptr,pkFieldList,fkFieldList);
        if ( OK != rv){return;}
        pkFieldList.resetIter();
        fkFieldList.resetIter();
        char *fldName = NULL;
        bool firstField=true;
        if(!firstFK) printf(", ");
        printf(", FOREIGN KEY ( ");
        while((fldName = fkFieldList.nextFieldName())!= NULL)
        {
            if (firstField) {
                printf("%s",fldName);
                firstField=false;
            }
            else
                printf(",%s",fldName);
        }
        printf(" ) REFERENCES %s ( ",fkTbl->getName());
        firstField=true;
        while((fldName = pkFieldList.nextFieldName())!= NULL)
        {
            if (firstField) {
                printf("%s",fldName);
                firstField=false;
            }
            else
                printf(",%s",fldName);
        }
        printf(" )");
        firstFK=true;        
        pkFieldList.removeAll(); 
        fkFieldList.removeAll(); 
    }
    return;
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
DbRetVal TableImpl::compact()
{
    DbRetVal rv=OK;
    int ret =((Chunk*)chunkPtr_)->compact(db_->procSlot);
    if(ret!=0) return ErrLockTimeOut;

    if (NULL != vcChunkPtr_) {
        ret = ((Chunk*)vcChunkPtr_)->compact(db_->procSlot);
        if(ret!=0) return ErrLockTimeOut;
    }
 
    if (NULL != indexPtr_)
    {
        int i;
        //it has index
        for (i = 0; i < numIndexes_ ; i++)
        {
            rv = compactIndexNode(indexPtr_[i]);
            if (rv != OK) { 
                printError(rv, "Error in compacting index Node"); 
                break;
            }
        }
    }  
    return rv;
}

DbRetVal TableImpl::compactIndexNode( void *indexPtr)
{
    CINDEX *iptr = (CINDEX*)indexPtr;
    int ret1=0;
    printDebug(DM_Table, "Inside insertIndexNode type %d", iptr->indexType_);
    if( hashIndex == (iptr->indexType_) )
    {
        ret1 =((Chunk*)iptr->hashNodeChunk_)->compact(db_->procSlot);
        if(ret1!=0){
            return ErrLockTimeOut;
        }
    }else
    {
        ret1 =((Chunk*)iptr->chunkPtr_)->compact(db_->procSlot);
        if(ret1!=0){
            return ErrLockTimeOut;
        }
    }
    return OK;
}
