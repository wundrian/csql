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

DbRetVal TreeIndex::insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool undoFlag)
{
    printDebug(DM_TreeIndex, "\nInside TreeNode::Insert - 1");
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    TreeNode *start = (TreeNode*) iptr->hashNodeChunk_;
    DbRetVal rc = OK;
    int offset = info->fldOffset;
    DataType type = info->type;
    printDebug(DM_TreeIndex, "Inserting tree index node for  %s", iptr->indName_);
    void *keyPtr =(void*)((char*)tuple + offset);
    if (start == NULL)
    {
        //TODO::there is chance that two threads can insert first node at
        //same time causing the first tree node to leak.
        printDebug(DM_TreeIndex, "\nInside if - start=NULL");
        Chunk *chunk = (Chunk*) iptr->chunkPtr_;
        TreeNode *tnode = (TreeNode*) chunk->allocate(tbl->db_, &rc);
        if (tnode == NULL)
        {
            printDebug(DM_TreeIndex, "\nExit TreeNode::Insert - 1 tnode=NULL");
            return rc;
        }
        tnode->mutex_.init();
        tnode->min_ = tuple;
        tnode->max_ = tuple;
        tnode->noElements_ =1;
        tnode->next_ = NULL;
        tnode->prev_ = NULL;
            tnode->balance_ = 0;
        char **rec = (char**)((char*) tnode + sizeof(TreeNode));
        printDebug(DM_TreeIndex, "\nStoring first record at %x\n", rec);
        *rec = (char*) tuple;
        iptr->hashNodeChunk_ = tnode;
    }else {
        rc = start->insert(tbl->db_, indInfo, indexPtr, tuple);
        if (rc != OK)
            printError(rc, "Error in tree node insertion\n");
    }

    printDebug(DM_TreeIndex, "\nExit TreeNode::Insert - 1");
    return rc;
}
void TreeNode::displayAll(int fldOffset)
{
    TreeNode *iter = this;
    int loc=0;
    while(iter->prev_)
    {
        printf("PRABA::ITERATING\n");
        iter = iter->prev_;
    }
    printf("\nDISPLAY NODES:START\n");
    while(iter != NULL)
    {
        char **rec = (char**)((char*) iter + sizeof(TreeNode));
        printf("\n>>>");
        for(loc=0;loc<iter->noElements_;loc++)
        {
            printf("%d,",*((int*)((char*) *(rec + loc )+fldOffset)));
        }
        iter = iter->next_;
    }
    printf("-----\n");
    printf("DISPLAY NODES:END\n");
}
void TreeNode::displayAll(IndexInfo *indInfo, void *indexPtr)
{
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    TreeNode *start = (TreeNode*) iptr->hashNodeChunk_;
    int offset = info->fldOffset;
    DataType type = info->type;
    int noOfBuckets = info->noOfBuckets;
    TreeNode *iter =start;
    int loc=0;
    while(iter->prev_)
    {
        iter = iter->prev_;
    }
    printf("\nDISPLAY NODES:START\n");
    while(iter != NULL)
    {
        char **rec = (char**)((char*) iter + sizeof(TreeNode));
        printf("\n>>>");
        for(loc=0;loc<iter->noElements_;loc++)
        {
            printf("%d,",*((int*)((char*) *(rec + loc )+info->fldOffset)));
        }
        iter = iter->next_;
    }
    printf("-----\n");
    printf("DISPLAY NODES:END\n");
}
DbRetVal TreeNode::insert(Database *db, IndexInfo *indInfo, void *indexPtr, void *tuple)
{
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    TreeNode *start = (TreeNode*) iptr->hashNodeChunk_;
    int offset = info->fldOffset;
    DataType type = info->type;
    int noOfBuckets = info->noOfBuckets;
    TreeNode *iter =start; void *record = NULL;
    TreeNode *prev = start;
    char *keyVal = (char*) tuple + info->fldOffset;
    DbRetVal rc = OK;
    bool recordInserted = false;
    printDebug(DM_TreeIndex, "\nInside TreeNode::Insert - 2");
    int count =0;
    int direction = 0;  //0:current,1:right,2:rightLeft,-1:left,-2:leftRight
    DbRetVal rv = OK;
    while(iter != NULL)
    {
        record = ((char*)iter->max_)+ info->fldOffset;
        printDebug(DM_TreeIndex, "\n%d---%d", *((int*)keyVal), *((int*)record));
        bool result = AllDataType::compareVal(keyVal, record, OpGreaterThan,
                                              info->type, info->compLength);
        if (result)
        {
            if(direction == -1)
            {
                direction = -2;
                break;
            }
            direction = 1;
            prev = iter;
            iter = iter->next_;
            printDebug(DM_TreeIndex, "\n2Insert- > ");
        }else
        {
            record = ((char*)iter->min_)+ info->fldOffset;
            result = AllDataType::compareVal(keyVal, record, OpLessThan,
                                             info->type, info->compLength);
            if (result) {
                if(direction == 1)
                {
                    direction = 2;
                    break;
                }
                direction = -1;
                prev = iter;
                iter = iter->prev_;
                printDebug(DM_TreeIndex, "\n2Insert- < ");
            }
            else
            {
                printDebug(DM_TreeIndex, "\n2Insert- = ");
                direction=0;
                break;
            }
        }
    }

    if(direction == 2)
    {
        //Check the size of the prev node....
        //if not full then move the iter to prev and call insertLast()
        //else call insertFirst();
        
        if((iter->prev_ != NULL) && (iter->prev_->noElements_ < noOfBuckets) )
        {
            printDebug(DM_TreeIndex, "\n2Insert- d=2 if ");
            iter = iter->prev_;
            rv  = insert(1, db, indInfo, iptr, tuple, iter);
        }
        else
        {
            printDebug(DM_TreeIndex, "\n2Insert- d=2 else ");
            rv  = insert(-1, db, indInfo, iptr, tuple, iter);
        }
    }
    else if(direction == 1)
    {
        iter = prev;
        if((iter->noElements_ >= noOfBuckets) && (iter->next_ != NULL)
             && (iter->next_->noElements_ < noOfBuckets) )
        {
            printDebug(DM_TreeIndex, "\n2Insert- d=1 if ");
            iter = iter->next_;
            rv  = insert(-1, db, indInfo, iptr, tuple, iter);
        }
        else
        {
            printDebug(DM_TreeIndex, "\n2Insert- d=1 else ");
            rv = insert(1, db, indInfo, iptr, tuple, iter);
        }
    }
    else if(direction == -2)
    {
       if(iter->next_ != NULL && iter->next_->noElements_ < noOfBuckets )
       {
            printDebug(DM_TreeIndex, "\n2Insert- d=-2 if ");
            iter = iter->next_;
            rv = insert(-1, db, indInfo, iptr, tuple, iter);
       }
       else
       {
           printDebug(DM_TreeIndex, "\n2Insert- d=-2 else ");
           rv = insert(1, db, indInfo, iptr, tuple, iter);
       }
    }
    else if(direction == -1)
    {
        iter = prev;
        if((iter->noElements_ >= noOfBuckets) && (iter->prev_ != NULL)
            && (iter->prev_->noElements_ < noOfBuckets) )
        {
            printDebug(DM_TreeIndex, "\n2Insert- d=-1 if ");
            iter = iter->prev_;
            rv = insert(1, db, indInfo, iptr, tuple, iter);
        }
       else
       {
           printDebug(DM_TreeIndex, "\n2Insert- d=-1 else ");
           rv = insert(-1, db, indInfo, iptr, tuple, iter);
       }
    }
    else
    {
        printDebug(DM_TreeIndex, "\n2Insert- d=0 ");
        rv = insert(0, db, indInfo, iptr, tuple, iter);
    }
    printDebug(DM_TreeIndex, "\n %d While  ..Exit TreeNode::Insert - 2",count);
    return rv;
}
DbRetVal TreeNode::insert(int position, Database * db, IndexInfo * indInfo,
                          CINDEX * iptr, void * tuple, TreeNode * iter)
{
    //position---  -1:First,0:Middle,1:Last

    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    TreeNode *start = (TreeNode*) iptr->hashNodeChunk_;
    int offset = info->fldOffset;
    DataType type = info->type;
    int noOfBuckets = info->noOfBuckets;
    void *record = NULL;
    TreeNode *prev = start;
    TreeNode *next = start;
    char *keyVal = (char*) tuple + info->fldOffset;
    DbRetVal rc = OK;
    bool recordInserted = false;
    iter->mutex_.getLock(db->procSlot);
    if(position == -1)
    {
        if(iter->noElements_ >= noOfBuckets)
        {
            Chunk *chunk = (Chunk*) iptr->chunkPtr_;
            TreeNode *tnode = (TreeNode*) chunk->allocate(db, &rc);
            if (tnode == NULL)
            {
                printDebug(DM_TreeIndex, "\nExit TreeNode::Insert Position tnode=NULL");
                iter->mutex_.releaseLock(db->procSlot);
                return rc;
            }
            tnode->mutex_.init();
            tnode->min_ = tuple;
            tnode->max_ = tuple;
            tnode->noElements_ =1;
            tnode->next_ = iter;
            tnode->prev_ = iter->prev_;
            iter->prev_ = tnode;
            tnode->balance_ = 0;
            char **rec = (char**)((char*)tnode + sizeof(TreeNode));
            *rec = (char*) tuple;
        }
        else
        {
            printDebug(DM_TreeIndex, "\n3Insert- p=-1 else ");
            char **rec = (char**)((char*)iter + sizeof(TreeNode));
            char *tmp = (char *)malloc(sizeof(void **) * iter->noElements_);
            memcpy(tmp, (char*)rec, sizeof(void **)* iter->noElements_);
            memcpy((char*)rec + sizeof(void **), tmp, sizeof(void **) * (iter->noElements_));
            free(tmp);
            iter->min_ = tuple;
            iter->noElements_++;
            *rec = (char*) tuple;
        }
    }
    else if(position == 1)
    {
        if(iter->noElements_ >= noOfBuckets)
        {
            printDebug(DM_TreeIndex, "\n3Insert- p=1 if ");
            Chunk *chunk = (Chunk*) iptr->chunkPtr_;
            TreeNode *tnode = (TreeNode*) chunk->allocate(db, &rc);
            if (tnode == NULL)
            {
                printDebug(DM_TreeIndex, "\nExit TreeNode::Insert Position tnode=NULL");
                iter->mutex_.releaseLock(db->procSlot);
                return rc;
            }
            tnode->mutex_.init();
            tnode->min_ = tuple;
            tnode->max_ = tuple;
            tnode->noElements_ =1;
            tnode->next_ = iter->next_;
            tnode->prev_ = iter;
            iter->next_ = tnode;
            if(tnode->next_)
            {
                tnode->next_->prev_ = tnode;
            }
            tnode->balance_ = 0;
            char **rec = (char**)((char*)tnode + sizeof(TreeNode));
            *rec = (char*) tuple;
        }
        else
        {
            printDebug(DM_TreeIndex, "\n3Insert- p=1 else ");
            char **rec = (char**)((char*)iter + sizeof(TreeNode));
            rec = (char **)((char *)rec + (iter->noElements_ * sizeof(void **)));
            iter->max_ = tuple;
            iter->noElements_++;
            *rec = (char*) tuple;
            rec = (char**)((char*)iter + sizeof(TreeNode));
            rec = (char**)((char *)rec + ((iter->noElements_-1) * sizeof(void **)));
        }
    }
    else
    {
        printDebug(DM_TreeIndex, "\n3Insert- p=0 ");

        int start = 0;
        int end = iter->noElements_ - 1;
        int middle;
        int loc = 0;
        char **rec = (char**)((char*)iter + sizeof(TreeNode));
        char *tmp = NULL;
        loc=0;
        for(middle = (start + end) / 2; start <= end ; middle = (start +end )/2)
        {
            loc = middle;
            record = ((char*)*(rec+middle)) + info->fldOffset;
            printDebug(DM_TreeIndex, "\n3Insert- p=0 get record \n");
            printDebug(DM_TreeIndex, "%d-%d\n\n", *((int*)keyVal), *((int*)record));
            bool res = AllDataType::compareVal(keyVal, record, OpEquals, info->type, info->compLength);
            if(res)
            {
                loc = middle;
                if (info->isUnique) {
                    iter->mutex_.releaseLock(db->procSlot);
                    printError(ErrUnique, "Unique constraint violation\n");
                    return ErrUnique;
                }
                break;
            }
            res = AllDataType::compareVal(keyVal, record, OpLessThan, info->type, info->compLength);
            if(res )
            {
                end = middle - 1;
            }
            else
            {
                start = middle + 1;
                loc = start;
            }
        }
        if(iter->noElements_ >= noOfBuckets)
        {
            printDebug(DM_TreeIndex, "\n3Insert- p=0 if ");
                        Chunk *chunk = (Chunk*) iptr->chunkPtr_;
            TreeNode *tnode = (TreeNode*) chunk->allocate(db, &rc);
            if (tnode == NULL)
            {
                printDebug(DM_TreeIndex, "\nExit TreeNode::Insert Position tnode=NULL");
                iter->mutex_.releaseLock(db->procSlot);
                return rc;
            }
            tnode->mutex_.init();
            tnode->next_ = iter->next_;
            tnode->prev_ = iter;
            iter->next_ = tnode;
            if(tnode->next_)
            {
                tnode->next_->prev_ = tnode;
            }
            tnode->balance_ = 0;
            char **rec = (char**)((char*)iter + sizeof(TreeNode));
            char *tmp = (char *)malloc(sizeof(void *) * (iter->noElements_ - loc));
            memcpy(tmp, (char*)rec + (loc * sizeof(void *)), sizeof(void *) * (iter->noElements_ - loc));/////////  Check the type cast char *
            rec = (char**)((char *)rec + (loc * sizeof(void *)));
            *rec = (char*)tuple;
            tnode->noElements_ = iter->noElements_ - loc;
            iter->noElements_ = loc + 1;
            rec = (char**)((char*)iter + sizeof(TreeNode));
            iter->min_ = *rec;
            iter->max_ = tuple;
            rec = (char**)((char*)tnode + sizeof(TreeNode));
            memcpy((char*)rec, tmp, (tnode->noElements_) * sizeof(void *));
            tnode->min_ = *rec;
            rec = (char**)((char *)rec + ((tnode->noElements_ - 1) * sizeof(void *)));
            tnode->max_ = *rec ;
            free(tmp);
        }
        else
        {
            printDebug(DM_TreeIndex, "\n3Insert- p=0 else pos-%d",loc);
            char **rec = (char**)((char*)iter + sizeof(TreeNode));
            char *tmp = (char *)malloc(sizeof(void *) * (iter->noElements_ - loc));
            memcpy(tmp, (char*)rec + (loc * sizeof(void *)), sizeof(void *) * (iter->noElements_ - loc));/////////  Check the type cast char *
            memcpy((char*)rec + ((loc+1) * sizeof(void *)), tmp, sizeof(void *) * (iter->noElements_ - loc));
            free(tmp);
            if(loc==0)
            {
                iter->min_ = tuple;
            }
            iter->noElements_++;
            rec = (char **)((char*)rec + (loc * sizeof(void *)));
            *rec = (char*)tuple;
        }
    }
    iter->mutex_.releaseLock(db->procSlot);
    return rc;
}

DbRetVal TreeIndex::remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool undoFlag)
{
    printf("Tree index remove called\n");
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    TreeNode *start = (TreeNode*) iptr->hashNodeChunk_;
    TreeNode *iter = locateNode(start, tuple, indInfo);
    if (NULL == iter) return OK; //element not found
    removeElement(tbl->getDB(), iter, tuple, info);
    return OK;
}
TreeNode* TreeIndex::locateNode(TreeNode *iter, void *tuple, IndexInfo *indInfo)
{
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    void *searchKey =(void*)((char*)tuple + info->fldOffset);
    while(iter != NULL)
    {
        char *record = ((char*)iter->max_)+ info->fldOffset;
        bool result = AllDataType::compareVal(searchKey, record,
                                              OpGreaterThan,
                                              info->type, info->compLength);
        if (result)
        {
            iter = iter->next_;
        }else
        {
            record = ((char*)iter->min_)+ info->fldOffset;
            result = AllDataType::compareVal(searchKey, record,
                                             OpGreaterThanEquals,
                                             info->type, info->compLength);
            if (result) {
               //current node contains the key
               return iter;
            }
            else
            {
               //need to move left
               iter = iter->prev_;
            }
        }
    }
    return NULL;
}
DbRetVal TreeIndex::removeElement(Database *db, TreeNode *iter, void *tuple, HashIndexInfo *info)
{
    void *searchKey =(void*)((char*)tuple + info->fldOffset);
    int loc=0, middle=0, start=0, end=iter->noElements_-1;
    char **rec = (char**)((char*)iter + sizeof(TreeNode));
    iter->mutex_.getLock(db->procSlot);
    for(middle = (start + end) / 2; start <= end ; middle = (start +end )/2)
    {
        loc = middle;
        char *record = ((char*)*(rec+middle)) + info->fldOffset;
        bool res = AllDataType::compareVal(searchKey, record, OpEquals,
                                           info->type, info->compLength);
        if(res)
        {
            loc = middle;
            break;
        }
        res = AllDataType::compareVal(searchKey, record, OpLessThan,
                                          info->type, info->compLength);
        if(res)
        {
            end = middle - 1;
        }
        else
        {
            start = middle + 1;
            loc = start;
        }
    }
    char *tmp = (char *)malloc(sizeof(void *) * (iter->noElements_ - loc));
    memcpy(tmp, (char*)rec + ((loc+1) * sizeof(void *)), sizeof(void *) * (iter->noElements_ - loc));
    memcpy((char*)rec + ((loc) * sizeof(void *)), tmp, sizeof(void *) * (iter->noElements_ - loc));
    free(tmp);
    if(loc==0)
    {
       iter->min_ = tuple;
    }
    iter->mutex_.releaseLock(db->procSlot);
    //TODO::if noElement is zero then deallocate the tree node
    iter->noElements_--;
    return OK;
}


DbRetVal TreeIndex::update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool undoFlag)
{
    return ErrNotYet;
}

