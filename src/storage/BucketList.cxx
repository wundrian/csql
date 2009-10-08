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
#include<Allocator.h>
#include<Database.h>
#include<Debug.h>
DbRetVal BucketList::insert(Chunk *chunk, Database *db, void *key, void*tuple)
{
    DbRetVal rv = OK;
    HashIndexNode *newNode;// (HashIndexNode*) chunk->allocate(db, &rv);
    int tries=0;
    int totalTries = Conf::config.getMutexRetries();
    while (tries < totalTries)
    {
        rv = OK;
        newNode= (HashIndexNode*) chunk->allocate(db, &rv);
        if (newNode !=NULL) break;
        if (rv != ErrLockTimeOut) 
        {
            printError(rv, "Unable to allocate hash index node");
            return rv;
        }
        //printError (ErrWarning, "Hash Node Alloc: LockTimeOut Retry:%d", tries);
        tries++;
    }
    if (newNode == NULL){
        printError(rv, "Unable to allocate hash index node after %d retry", Conf::config.getMutexRetries());
        return rv;
    }
    printDebug(DM_HashIndex,"Hash Index node allocated:%x", newNode);
    newNode->ptrToKey_ = key;
    newNode->ptrToTuple_ = tuple;
    newNode->next_ = NULL;

    //If this is the first node, set it as head
    if (NULL == head)
    {
        printDebug(DM_HashIndex, "BucketList:insert head is null key:%x",key);
        //head = newNode;
        if ( 0 != Mutex::CASL((long*)&head, 0, (long)newNode)) {
            printError(ErrLockTimeOut, "Unable to set bucket head..retry\n");
            chunk->free(db, newNode);  
            return ErrLockTimeOut;
        }
        return OK;
    }

    HashIndexNode *it = head;
    while (NULL != it->next_) it = it->next_;
    //it->next_ = newNode;
    if ( 0 != Mutex::CASL((long*)&it->next_, 0, (long)newNode)) {
        printError(ErrLockTimeOut, "Unable to add to bucket..retry\n");
        chunk->free(db, newNode);  
        return ErrLockTimeOut;
    }
    printDebug(DM_HashIndex, "BucketList:insert adding it to the end of list key:%x", key);
    if (rv != OK) printError(ErrSysFatal, "rv is not OK %d\n", rv);
    return rv;
}
//Returns 2 if the head itself is removed.
DbRetVal BucketList::remove(Chunk *chunk, Database *db, void *keyPtr)
{
    if (NULL == head) return ErrNotFound;
    HashIndexNode *ite = head, *prev = head;
    while (ite != NULL)
    {
        if (ite->ptrToKey_ ==  keyPtr)
        {
            if ( ite == head) { 
                //head = ite->next_; 
                if ( 0 != Mutex::CASL((long*)&head, (long)ite, 
                                                    (long)ite->next_)) {
                    printError(ErrLockTimeOut, "Unable to set bucket head..retry");
                    return ErrLockTimeOut;
                }
                chunk->free(db, ite); 
                return SplCase; 
            }
            //prev->next_ = ite->next_;
            if ( 0 != Mutex::CASL((long*)&prev->next_, (long)prev->next_, (long)ite->next_)) {
                printError(ErrLockTimeOut, "Unable to remove hash bucket node..retry");
                return ErrLockTimeOut;
            }
            chunk->free(db, ite);
            return OK;
        }
        prev = ite;
        ite = ite->next_;
    }
    printError(ErrNotFound, "Node not found in the bucket list");
    printStackTrace();
    return ErrNotFound;
}
