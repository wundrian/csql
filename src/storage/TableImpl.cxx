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
DbRetVal TableImpl::getQualifiedName(const char *fldname, char *qualName)
{
    FieldInfo *info = new FieldInfo();
    DbRetVal rv = getFieldInfo(fldname,info);
    if (rv == OK)
        sprintf(qualName, "%s.%s", getName(), fldname);
    return rv;
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

int TableImpl::getFldPos(char *name)
{
    return fldList_.getFieldPosition(name);
}

void TableImpl::setAliasName(char *name)
{
    strcpy(aliasName, name);
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
                if(AllDataType::compareVal(def->bindVal_, &tempAutoVal, 
                                           OpGreaterThan, def->type_)) 
                {
                    AllDataType::copyVal(ptrToAuto,def->bindVal_, def->type_,
                                                                 def->length_);
                }
                AllDataType::copyVal(colPtr, def->bindVal_, def->type_,
                                                       def->length_);
                colPtr = colPtr + def->length_;
                fldpos++;
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
            //TODO::Trie
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
        else if (iptr->indexType_ == treeIndex) fprintf(fp, " TREE ");
        else fprintf(fp, " TRIE ");

        HashIndexInfo* hInfo = (HashIndexInfo*)idxInfo[i];
        if (hInfo->isUnique) fprintf(fp, " UNIQUE"); 
        if(hInfo->noOfBuckets != 1009  &&
           hInfo->noOfBuckets !=0) fprintf(fp, " SIZE %d ",((HashIndexInfo*) idxInfo[i])->noOfBuckets ); 
        fprintf(fp, ";\n");
    }
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
    }else if (treeIndex == (iptr->indexType_))
    {
        ret1 =((Chunk*)iptr->chunkPtr_)->compact(db_->procSlot);
        if(ret1!=0){
            return ErrLockTimeOut;
        }
    } else if ( trieIndex == (iptr->indexType_))
    {
        ret1 =((Chunk*)iptr->chunkPtr_)->compact(db_->procSlot);
        if(ret1!=0){
            return ErrLockTimeOut;
        }
        ret1 =((Chunk*)iptr->hashNodeChunk_)->compact(db_->procSlot);
        if(ret1!=0){
            return ErrLockTimeOut;
        }
    }
    return OK;
}
