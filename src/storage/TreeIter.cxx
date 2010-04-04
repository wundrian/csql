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
#include<Debug.h>

void* TreeIter::getFirstElement()
{
   if (NULL == iter) return NULL;
   TreeNode *node = iter;
   while(node != NULL) {
      if(NULL == node->prev_)  break;
      node = node->prev_;
   }
   if (node == NULL) printf("Node returned is NULL\n");
   if (0 == node->noElements_) return NULL;
   char **rec = (char**)((char*)node + sizeof(TreeNode));
   int loc = 0; //first element
   char **tuple = (char**)((char*)rec + (loc * sizeof(void *)));
   return *tuple;
}

void* TreeIter::getLastElement()
{
   if (NULL == iter) return NULL;
   TreeNode *node = iter;
   while(node != NULL ) {
      if(NULL == node->next_)  break;
      node = node->next_;
   }
   if (node == NULL) printf("Node returned is NULL\n");
   if (0 == node->noElements_)  return NULL;
   char **rec = (char**)((char*)node + sizeof(TreeNode));
   int loc = node->noElements_-1; //last element
   char **tuple = (char**)((char*)rec + (loc * sizeof(void *)));
   return *tuple;
}

void* TreeIter::prev()
{
   if (0 != nodeOffset )
   {
       nodeOffset--;
       
   }else 
   {
       iter=iter->prev_;
       if (NULL == iter) return NULL;
       nodeOffset = iter->noElements_;
   }
   char **rec = (char**)((char*)iter + sizeof(TreeNode));
   rec = (char**)((char *)rec + ((nodeOffset) * sizeof(void **)));
   return *rec;
}
void TreeIter::nextNode()
{
    if (recordsOver) return ;
    if (NULL == iter) return ;
    TreeNode *tmpIter = iter;
    iter = iter->next_;
    if(iter){
        DbRetVal ret = TreeIndex::getTreeNodeMutex(iter, procSlot);
        if (OK != ret)
        {
             printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
             tmpIter->mutex_.releaseShareLock(procSlot);
             return ;
        }
    }
    tmpIter->mutex_.releaseShareLock(procSlot);
    nodeOffset=0;
}

void TreeIter::reset() 
{ 
    if(iter && !firstCall) iter->mutex_.releaseShareLock(procSlot);
    firstCall = true; 
    recordsOver=false; 
    iter = head; 
}

void* TreeIter::next()
{
    int direction=0;
    if (recordsOver){ 
       if(iter) iter->mutex_.releaseShareLock(procSlot);
       iter = NULL;
       return NULL; 
    }
    if (NULL== iter) return NULL;
    if (firstCall)
    {
        if (OpLessThan ==op || OpLessThanEquals == op)
        {
            nodeOffset = 1;
            firstCall = false;
            char **rec = (char**)((char*) iter + sizeof(TreeNode));
            DbRetVal ret = TreeIndex::getTreeNodeMutex(iter, procSlot);
            if (OK != ret)
            {
               printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
               return NULL;
            }
            //iter->displayAll(fldOffset);
            return *rec;
        }
        else if (OpGreaterThan == op)
        {
            char *rec = (char*)locateNode();
            firstCall = false;
            if(rec){
                bool result = AllDataType::compareVal(searchKey, rec+fldOffset,
                                         OpEquals, type, length);
            //equals comparision does not apply to float and double
                if (result || type==typeFloat || type == typeDouble) return next();
            }
            return rec;
        }else if (OpGreaterThanEquals == op)
        {
            void *rec = locateNode();
            firstCall = false;
            return rec;
        }else if (OpEquals == op)
        {
            void *rec = locateNode();
            firstCall = false;
            if(isUnique) recordsOver = true;
            return rec;
        }
        //firstCall = false;
    }else
    {
        if (nodeOffset == iter->noElements_) 
        {
            if (NULL == iter->next_) {
                recordsOver = true; 
                iter->mutex_.releaseShareLock(procSlot);
                iter = NULL;
                return NULL; 
            }
            char* record = ((char*)iter->next_->min_)+ fldOffset;
            bool result = AllDataType::compareVal(searchKey, record, 
                                              OpGreaterThanEquals,
                                              type, length);
            if (!result && (OpLessThan ==op || OpLessThanEquals == op)) 
            { 
                //Case: search key 10 , next node first record is 20 
                //condition is < or <=
                recordsOver= true; 
                iter->mutex_.releaseShareLock(procSlot);
                iter = NULL;
                return NULL; 
            }else if (result && (OpGreaterThan == op || 
                      OpGreaterThanEquals == op))
            {
                //Case: search key 20 , next node first record is 10 
                //condition is > or >=
                recordsOver= true; 
                iter->mutex_.releaseShareLock(procSlot);
                iter = NULL;
                return NULL;
            }
            TreeNode *tmpIter = iter;
            iter = iter->next_;
            DbRetVal ret = TreeIndex::getTreeNodeMutex(iter, procSlot);
            if (OK != ret) 
            {
               printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
               tmpIter->mutex_.releaseShareLock(procSlot);
               iter = NULL;
               return NULL;
            }
            tmpIter->mutex_.releaseShareLock(procSlot);
            printDebug(DM_TreeIndex,"\n Moving Node next");
            nodeOffset=0;
        }
        char **rec = (char**)((char*)iter + sizeof(TreeNode));
        rec = (char**)((char *)rec + ((nodeOffset) * sizeof(void **)));
        nodeOffset++;
        //TEMP::UNCOMMENT THIS if any issue 
        /*if(NULL==(*rec))
                iter->mutex_.releaseShareLock(procSlot);
        */
        return *rec;
    }
    return NULL;
}
void* TreeIter::locateNode()
{
    TreeNode *tnode=NULL;
    TreeNode *fiter= (TreeNode *)fstLTnode;
    DbRetVal  ret=OK;
    ret = TreeIndex::getTreeNodeMutex(fiter, procSlot);
    if (OK != ret) 
    {
        printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
        return NULL;
    }
    while( fiter!= NULL)
    {
        printDebug(DM_TreeIndex,"\n Search in first level start");
        tnode = (TreeNode *)*((char**)((char*)((char*)fiter + sizeof(TreeNode))+ ((fiter->noElements_-1)*sizeof(void *))));
        char *record = ((char*)tnode->max_)+ fldOffset;
        bool result = AllDataType::compareVal(searchKey, record,OpLessThanEquals,type, length);
        if (result)
        {
            break;
        }else
        {
            printDebug(DM_TreeIndex,"\n Search in first level next");
            TreeNode* tmpIter = fiter;
            if(fiter->next_!= NULL){
               fiter = fiter->next_;
               ret = TreeIndex::getTreeNodeMutex(fiter, procSlot);
               if (OK != ret) 
               {
                   printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
                   tmpIter->mutex_.releaseShareLock(procSlot);
                   iter = NULL;
                   return NULL;
               }
               tmpIter->mutex_.releaseShareLock(procSlot);
            }else{
               tmpIter->mutex_.releaseShareLock(procSlot);
               fiter = NULL;    
            }
        }
    }
    if(fiter == NULL)
    {
        iter = NULL;
        return NULL;
    }
    //Get leaf Node
    
   int loc=0, middle=0, start=0, end=fiter->noElements_-1;
   char **rec = (char**)((char*)fiter + sizeof(TreeNode));
   TreeNode *tNode;
   if(fiter->noElements_==1)
   {
        tNode = ((TreeNode *)*(char**)((char*)rec + (loc * sizeof(void *))));
        iter = tNode;
        fiter->mutex_.releaseShareLock(procSlot);
        void *rec1 = locateElement();
        return rec1;
   }
   for(middle = (start + end) / 2; start <= end ; middle = (start +end )/2)
    {
        loc = middle;
        tNode = (TreeNode *)*((char**)((char*)((char*)fiter + sizeof(TreeNode))+ (loc*sizeof(void *))));
        char *record = ((char*)tNode->max_)+ fldOffset;

        bool res = AllDataType::compareVal(searchKey, record, OpLessThan,
                                           type, length);
        if(res)
        {
            end = middle - 1;
        }
        else
        {
            res = AllDataType::compareVal(searchKey, record, OpGreaterThan,
                                          type, length);
            if (res) {
                start = middle + 1;
                loc = start;
            }else {
                loc = middle;
                break;
            }
        }
    }
    printDebug(DM_TreeIndex,"\n Search in fisrt level end loc =%d\n",loc);
    tNode = ((TreeNode *)*(char**)((char*)rec + (loc * sizeof(void *))));
    iter = tNode;
    fiter->mutex_.releaseShareLock(procSlot);
    void *rec1 = locateElement();
    return rec1;
}

void* TreeIter::locateElement()
{
    //do binary search and locate the element 
    int loc=0, middle=0, start=0, end=iter->noElements_-1;
    char **rec = (char**)((char*)iter + sizeof(TreeNode));
    DbRetVal ret = TreeIndex::getTreeNodeMutex(iter, procSlot);
    if (OK != ret) 
    {
        printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
        return NULL;
    }
    for(middle = (start + end) / 2; start <= end ; middle = (start +end )/2)
    {
        loc = middle;
        char *record = ((char*)*(rec+middle)) + fldOffset;
        bool res = AllDataType::compareVal(searchKey, record, OpLessThan, 
                                           type, length);
        if(res)
        {
            end = middle - 1;
        }
        else
        {
            res = AllDataType::compareVal(searchKey, record, OpGreaterThan,
                                             type, length);
            if (res) {
                start = middle + 1;
                loc = start;
            }else {
                loc = middle;
                break;
            }
        }
    }
    nodeOffset=loc;
    char **tuple = (char**)((char*)rec + (loc * sizeof(void *)));
    nodeOffset++;
    //iter->mutex_.releaseShareLock(procSlot);
    return *tuple;
}
