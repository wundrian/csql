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
DbRetVal TreeIndex::deleteLogicalUndoLog(Database *sysdb, void *data)
{
    DbRetVal rv = OK;
    TreeUndoLogInfo *tUndoInfo = (TreeUndoLogInfo *) data;
    Database *db = new Database();
    db->setMetaDataPtr((DatabaseMetaData*) tUndoInfo->metaData_);
    db->setProcSlot(sysdb->procSlot);
    CINDEX *iptr = (CINDEX*) tUndoInfo->cIndex_;
    TreeNode *start = (TreeNode*) iptr->hashNodeChunk_;
    //HashIndexInfo populated here
    HashIndexInfo *info = new HashIndexInfo();
    info->indexPtr = (char *)iptr;
    info->noOfBuckets = iptr->noOfBuckets_;
    info->isUnique = iptr->isUnique_;
    info->type = ((CFIELD*)(((CINDEXFIELD*)(iptr->fstIndFld_))->fieldPtr))->type_;
    info->fldOffset = ((CFIELD*)(((CINDEXFIELD*)(iptr->fstIndFld_))->fieldPtr))->offset_;
    info->indType = iptr->indexType_;
    TreeIndex *treeInd = (TreeIndex*)Index::getIndex(iptr->indexType_);
    int pos=0;
    TreeNode *fltnode = start->locateNode(db, start, tUndoInfo->tuple_, info,rv);
    if (NULL == fltnode){ 
        delete db;
        delete info;
        return rv; 
    } //First Level Node Not found
    TreeNode *iter = start->locateNodeFromFirstLevel(fltnode, info, tUndoInfo->tuple_, &pos);
    if (NULL == iter){ 
        fltnode->mutex_.releaseShareLock(db->procSlot); 
        printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
        delete db;
        delete info;
        return OK;
    } //element not found
    rv = treeInd->removeElement(db, iter, tUndoInfo->tuple_, info);
    if( rv != OK ){
        fltnode->mutex_.releaseShareLock(db->procSlot);
        printError(rv, "Romove from TreeNode Failed ");
        printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
        delete db;
        delete info;
        return rv;
    }
    if(0 == iter->noElements_)
    {
        treeInd->removeNode(db, tUndoInfo->cIndex_, fltnode,iter, pos);
    }else { fltnode->mutex_.releaseShareLock(db->procSlot); 
        printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
    }
    delete db;
    delete info;
    return rv;
}

DbRetVal TreeIndex::insertLogicalUndoLog(Database *sysdb, void *data)
{
    DbRetVal rc = OK;
    TreeUndoLogInfo *tUndoInfo = (TreeUndoLogInfo *) data;
    Database *db = new Database();
    db->setMetaDataPtr((DatabaseMetaData*) tUndoInfo->metaData_);
    db->setProcSlot(sysdb->procSlot);
    CINDEX *iptr = (CINDEX*) tUndoInfo->cIndex_;//CINDEX
    //HashIndexInfo populated here
    HashIndexInfo *info = new HashIndexInfo();
    info->indexPtr = (char *)iptr;
    info->noOfBuckets = iptr->noOfBuckets_;
    info->isUnique = iptr->isUnique_;
    info->type = ((CFIELD*)(((CINDEXFIELD*)(iptr->fstIndFld_))->fieldPtr))->type_;
    info->fldOffset = ((CFIELD*)(((CINDEXFIELD*)(iptr->fstIndFld_))->fieldPtr))->offset_;
    info->indType = iptr->indexType_;
    TreeNode *start = (TreeNode*) iptr->hashNodeChunk_;
    int offset = info->fldOffset;
    DataType type = info->type;
    void *keyPtr =(void*)((char*)tUndoInfo->tuple_ + offset); 
    if (start == NULL)
    {
        //Currently Nodes are not deleted
        printDebug(DM_TreeIndex, "Inside if - start=NULL create First level ");
        Chunk *chunk = (Chunk*) iptr->chunkPtr_;
        TreeNode *tnode = (TreeNode*) chunk->allocate(db, &rc);
        if (tnode == NULL)
        {
            printError(rc, "Exit TreeNode::Insert - 1 tnode=NULL");
            delete info;
            return rc;
        }
        tnode->mutex_.init("TNODE-R");
        tnode->min_ = tUndoInfo->tuple_;
        tnode->max_ = tUndoInfo->tuple_;
        tnode->noElements_ =1;
        tnode->next_ = NULL;
        tnode->prev_ = NULL;
        tnode->balance_ = 0;
        char **rec = (char**)((char*) tnode + sizeof(TreeNode));
        //printDebug(DM_TreeIndex, "\nStoring first record at %x\n", rec);
        *rec = (char*) tUndoInfo->tuple_;
        
        printDebug(DM_TreeIndex, "Inside if - start=NULL create second level ");
        Chunk *ftchunk = (Chunk*) iptr->chunkPtr_;
        TreeNode *ftnode = (TreeNode*) ftchunk->allocate(db, &rc);
        if (NULL == ftnode)
        {
            printError(rc, "Unable to allocate tree node");
            chunk->free(db, tnode);
            delete info;
            return rc;
        }
        ftnode->mutex_.init("TNODE-I");
        ftnode->min_= NULL;
        ftnode->max_ = NULL;
        ftnode->noElements_ =1;
        ftnode->next_ = NULL;
        ftnode->prev_ = NULL;
        ftnode->balance_ = 0;
        char **tn=(char**)((char*) ftnode+sizeof(TreeNode));
        *tn = (char*)tnode;
        //iptr->hashNodeChunk_ = ftnode;
        if( 0 !=Mutex::CASL((long*)&iptr->hashNodeChunk_, 0, (long)ftnode))
        {
            printError(ErrLockTimeOut, "Lock timeout..retry");
            chunk->free(db, tnode);
            chunk->free(db, ftnode);
            delete info;
            return ErrLockTimeOut;
        }
    }else {
        rc = start->insert(db, info, iptr, tUndoInfo->tuple_);
        if (rc != OK){
            delete db; delete info;
            printError(rc, "Error in tree node insertion\n");
            return rc;
        }
    }
    delete db;
    delete info;
    return rc;

}

DbRetVal TreeIndex::insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool undoFlag)
{
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    TreeNode *start = (TreeNode*) iptr->hashNodeChunk_;
    DbRetVal rc = OK;
    int offset = info->fldOffset;
    DataType type = info->type;
    void *keyPtr =(void*)((char*)tuple + offset);
    //TreeUndoLogInfo Populated here
    TreeUndoLogInfo hInfo;
    hInfo.metaData_ = tbl->db_->getMetaDataPtr();
    hInfo.tuple_ = tuple;
    hInfo.cIndex_= indexPtr;
    if (start == NULL)
    {
        printDebug(DM_TreeIndex, "Inside if - start=NULL create First level ");
        Chunk *chunk = (Chunk*) iptr->chunkPtr_;
        TreeNode *tnode = (TreeNode*) chunk->allocate(tbl->db_, &rc);
        if (tnode == NULL)
        {
            printError(rc, "Unable to allocate tree node");
            return rc;
        }
        tnode->mutex_.init("TNODE-R");
        tnode->min_ = tuple;
        tnode->max_ = tuple;
        tnode->noElements_ =1;
        tnode->next_ = NULL;
        tnode->prev_ = NULL;
        tnode->balance_ = 0;
        char **rec = (char**)((char*) tnode + sizeof(TreeNode));
        //printDebug(DM_TreeIndex, "\nStoring first record at %x\n", rec);
        *rec = (char*) tuple;

        printDebug(DM_TreeIndex, "Inside if - start=NULL create second level ");
        TreeNode *ftnode = (TreeNode*) chunk->allocate(tbl->db_, &rc);
        if (NULL == ftnode)
        {
            printError(rc, "Unable to allocate tree node");
            chunk->free(tbl->db_, tnode);
            return rc;
        }
        ftnode->mutex_.init("TNODE-I");
        ftnode->min_= NULL;
        ftnode->max_ = NULL;
        ftnode->noElements_ =1;
        ftnode->next_ = NULL;
        ftnode->prev_ = NULL;
        ftnode->balance_ = 0;
        //TODO: Handle when two process try to allocate first node
        char **tn=(char**)((char*) ftnode + sizeof(TreeNode));
        *tn = (char*)tnode;
        if( 0 !=Mutex::CASL((long*)&iptr->hashNodeChunk_, 0, (long)ftnode))
        {
            printError(ErrLockTimeOut, "Lock timeout..retry");
            chunk->free(tbl->db_, tnode);
            chunk->free(tbl->db_, ftnode);
            return ErrLockTimeOut;
        }

    }else {
        rc = start->insert(tbl->db_, indInfo, indexPtr, tuple);
        if (rc != OK){
            printError(rc, "Error in tree node insertion for tuple %x", tuple);
            return rc;
        }
    }
    //start->displayAll(offset);
    if(!undoFlag){
        rc = tr->appendLogicalTreeUndoLog(tbl->sysDB_, InsertTreeIndexOperation, &hInfo, sizeof(TreeUndoLogInfo));
        if (rc !=OK)
        {
             //Reverse back
             int pos=0;
             start = (TreeNode*) iptr->hashNodeChunk_;
             TreeNode *fltnode = start->locateNode(tbl->sysDB_,start, tuple, indInfo,rc);
             if (NULL == fltnode)
             {
                  return rc;
             } //First Level Node Not found
             TreeNode *iter = start->locateNodeFromFirstLevel(fltnode, indInfo, tuple, &pos);
             if (NULL == iter){
                fltnode->mutex_.releaseShareLock(tbl->sysDB_->procSlot);
                printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
                return OK;
             } //element not found
             rc = removeElement(tbl->getDB(), iter, tuple, info);
             if( rc != OK )
             {
                 fltnode->mutex_.releaseShareLock(tbl->sysDB_->procSlot);
                 printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
                 printError(rc, "Romove from TreeNode Failed ");
                 return rc;
             } 
             if(0 == iter->noElements_)
             {
                 removeNode(tbl->getDB(), indexPtr, fltnode,iter, pos);
             }else
             {
                 fltnode->mutex_.releaseShareLock(tbl->sysDB_->procSlot);
                 printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
             }
             
             printError(ErrSysFatal, "Unable to append undo lock for TreeInsert\n");        
             return rc;

        }
    }
    return rc;
}


DbRetVal TreeIndex::remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool undoFlag)
{
    DbRetVal rc = OK;
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    TreeNode *start = (TreeNode*) iptr->hashNodeChunk_;
    int pos=0;
    TreeNode *fltnode = start->locateNode(tbl->getDB(),start, tuple, indInfo,rc);
    if (NULL == fltnode) return rc; //First Level Node Not found
    TreeNode *iter = start->locateNodeFromFirstLevel(fltnode, indInfo, tuple, &pos);
    if (NULL == iter) { 
        //element not found
        fltnode->mutex_.releaseShareLock((tbl->getDB())->procSlot); 
        printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
        return OK; 
     }  
    rc = removeElement(tbl->getDB(), iter, tuple, info);
    if( rc != OK ){
        fltnode->mutex_.releaseShareLock((tbl->getDB())->procSlot);
        printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
        printError(rc, "Remove from TreeNode Failed");
        return rc;
    }
    if(0 == iter->noElements_)
    { 
        removeNode(tbl->getDB(), indexPtr, fltnode, iter, pos);
    }else
    {
        fltnode->mutex_.releaseShareLock((tbl->getDB())->procSlot);
        printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
    }
    TreeUndoLogInfo hInfo;
    hInfo.metaData_ = tbl->db_->getMetaDataPtr();
    hInfo.tuple_ = tuple;
    hInfo.cIndex_= indexPtr;
    if (!undoFlag) {
        rc =tr->appendLogicalTreeUndoLog(tbl->sysDB_, DeleteTreeIndexOperation, &hInfo, sizeof(TreeUndoLogInfo));
        if( rc != OK){
            //Reverse back
            //Currently nodes are not freed 
            rc = start->insert(tbl->db_, info, iptr, tuple);
            if (rc != OK){ printError(ErrSysFatal, "double failure on undo log remove followed by tree insert\n");}
            printError(ErrSysFatal, "Unable to append undo lock for TreeRemove\n");
            return rc;
        }
   }
   return rc;
}

void TreeIndex::removeNode(Database *db,void *indexPtr,TreeNode *fltnode, TreeNode *node,int pos)
{
    CINDEX *iptr = (CINDEX*)indexPtr;
    char **nod = (char**)((char*)fltnode + sizeof(TreeNode));
    char *tmp = (char *)malloc(sizeof(void *) * (fltnode->noElements_ - pos));
    memcpy(tmp, (char*)nod + ((pos+1) * sizeof(void *)), sizeof(void *) * (fltnode->noElements_ - pos));
    memcpy((char*)nod + ((pos) * sizeof(void *)), tmp, sizeof(void *) * (fltnode->noElements_ - pos));
    free(tmp);
    fltnode->noElements_--;
    if(node->prev_!=NULL) node->prev_->next_= node->next_;
    if(node->next_!=NULL) node->next_->prev_= node->prev_;
    Chunk *chunk = (Chunk*) iptr->chunkPtr_;
    chunk->free(db, node);
    printDebug(DM_TreeIndex,"TreeNode at postion %d Freed",pos);
    if(fltnode->noElements_== 0)
    {
        if(fltnode->prev_!=NULL) { 
            fltnode->prev_->next_= fltnode->next_; 
        }
        else { 
            iptr->hashNodeChunk_ = fltnode->next_ ; 
        }
        if(fltnode->next_!=NULL) { 
            fltnode->next_->prev_= fltnode->prev_; 
        }
        //need discussion in the above situation to solve concureny
        printDebug(DM_TreeIndex,"TreeNode from first level Freed");
        fltnode->mutex_.releaseShareLock(db->procSlot);
        printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
        chunk->free(db, fltnode);
    }else{
        fltnode->mutex_.releaseShareLock(db->procSlot);
        printDebug(DM_TreeIndex," Mutex Release on %x\n",fltnode);
    }
}

DbRetVal TreeIndex::removeElement(Database *db, TreeNode *iter, void *tuple, HashIndexInfo *info)
{
    void *searchKey =(void*)((char*)tuple + info->fldOffset);
    int loc=0, middle=0, start=0, end=iter->noElements_-1;
    char **rec = (char**)((char*)iter + sizeof(TreeNode));
    DbRetVal ret = TreeIndex::upgradeTreeNodeMutex(iter, db->procSlot);
    if (OK != ret) {
         printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
         return ErrLockTimeOut;
    }
    for(middle = (start + end) / 2; start <= end ; middle = (start +end )/2)
    {
        loc = middle;
        char *record = ((char*)*(rec+middle)) + info->fldOffset;
        bool res = AllDataType::compareVal(searchKey, record, OpLessThan,
                                           info->type, info->compLength);
        if(res)
        {
            end = middle - 1;
        }
        else
        {
            res = AllDataType::compareVal(searchKey, record, OpGreaterThan,
                                          info->type, info->compLength);
            if (res) {
                start = middle + 1;
                loc = start;
            } else {
                loc = middle;
                break;
            }
        }
    }
    if (loc == iter->noElements_-1)
    {
        iter->max_ = *(char**)((char*)rec + ((loc-1) * sizeof(void *)));
    }else {
       char *tmp = (char *)malloc(sizeof(void *) * (iter->noElements_ - loc));
       memcpy(tmp, (char*)rec + ((loc+1) * sizeof(void *)), 
                                    sizeof(void *) * (iter->noElements_ - loc));
       memcpy((char*)rec + ((loc) * sizeof(void *)), tmp, 
                                    sizeof(void *) * (iter->noElements_ - loc));
       free(tmp);
    }
    if(loc==0)
    {
       iter->min_ = *(char**)rec ;
    }
    iter->noElements_--;
    iter->mutex_.releaseShareLock(db->procSlot);
    return OK;
}


DbRetVal TreeIndex::update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool undoFlag)
{
    CINDEX *iptr = (CINDEX*)indexPtr;

    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    //check whether the index key is updated or not
    //if it is not updated return from here
    bool keyNotUpdated = false;
    FieldIterator idxFldIter = info->idxFldList.getIterator();
    while (idxFldIter.hasElement()) 
    {
        FieldDef *idef = idxFldIter.nextElement();
        FieldIterator fldIter = tbl->fldList_.getIterator();
        while (fldIter.hasElement()) 
        {
            FieldDef *def = fldIter.nextElement();
            if (0 == strcmp(def->fldName_, idef->fldName_)) 
            {
                if (NULL != def->bindVal_) 
                {
                    //Not Implemented
                    return ErrNotYet;
                }  
               keyNotUpdated = true;
               break;
            }
        }
    }
    if (keyNotUpdated) 
    {
        return OK;
    }
    return ErrNotYet;
}

DbRetVal TreeIndex::getTreeNodeMutex(TreeNode *node, int procSlot, bool isX)
{
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = 0;
        if (isX)
           ret = node->mutex_.getExclusiveLock(procSlot,true);
        else
           ret = node->mutex_.getShareLock(procSlot,true);
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;

}

DbRetVal TreeIndex::upgradeTreeNodeMutex(TreeNode *node, int procSlot)
{
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = 0;
        ret = node->mutex_.getExclusiveLock(procSlot,true, true);
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;
}

