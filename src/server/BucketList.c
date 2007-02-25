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
#include<Allocator.h>
#include<Database.h>
#include<Debug.h>

DbRetVal BucketList::insert(Chunk *chunk, Database *db, void *key, void*tuple)
{
    HashIndexNode *newNode= (HashIndexNode*) chunk->allocate(db);
    if (NULL == newNode)
    {
        printError(ErrNoMemory,
                   "No memory to allocate HashIndex node");
        return ErrNoMemory;
    }
    printDebug(DM_HashIndex,"Hash Index node allocated:%x", newNode);
    newNode->ptrToKey_ = key;
    newNode->ptrToTuple_ = tuple;
    newNode->next_ = NULL;

    //If this is the first node, set it as head
    if (NULL == head)
    {
        printDebug(DM_HashIndex, "BucketList:insert head is null key:%x",key);
        head = newNode;
        return OK;
    }

    HashIndexNode *it = head;
    while (NULL != it->next_) it = it->next_;
    it->next_ = newNode;
    printDebug(DM_HashIndex, "BucketList:insert adding it to the end of list key:%x", key);
    return OK;
}
//Returns 2 if the head itself is removed.
DbRetVal BucketList::remove(Chunk *chunk, Database *db, void *keyPtr)
{
    if (NULL == head) return ErrNotFound;
    HashIndexNode *ite = head, *prev = head;
    while (ite->next_ != NULL)
    {
        if (ite->ptrToKey_ ==  keyPtr)
        {
            prev->next_ = ite->next_;
            chunk->free(db, ite);
        }
        prev = ite;
        ite = ite->next_;
    }
    if( ite == head) // there is only one node in the list
    {
        if (ite->ptrToKey_ ==  keyPtr)
        {
            chunk->free(db, head);
            printDebug(DM_HashIndex,"BucketList::remove head:%x removed key:%x",
                                                        head, keyPtr);
            head = NULL;
            return SplCase;
        }

    }
    if( prev == head) // there are only two node in the list
    {
        if (ite->ptrToKey_ ==  keyPtr)
        {
            chunk->free(db, head->next_);
            head->next_ = NULL;
            printDebug(DM_HashIndex,"BucketList::remove element:%x removed key:%x",
                                                     head->next_, keyPtr);
            return OK;
        }
    }
    printError(ErrNotFound, "Node not found in the bucket list");
    return ErrNotFound;
}
