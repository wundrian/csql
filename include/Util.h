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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef UTIL_H
#define UTIL_H
#include<ErrorType.h>
#include<Debug.h>
enum UniqueIDType {
    STMT_ID=0,
    TXN_ID
};

class ListNode
{
    public:
    void *element;
    ListNode *next;
    
};

class ListIterator
{
    ListNode *iter;
    ListNode *start;
    public:
    ListIterator(){}

    ListIterator(ListNode *head) { iter = head; start = head; }

    bool hasElement()
    {
        if (iter == NULL) return false; else return true;
    }

    void reset()
    {
        iter = start;
    }
    //isRemove ->the node needs to deleted after returning
    void* nextElement(bool isRemove = false) 
    {
        if (iter == NULL) return NULL;
        ListNode *node = iter;
        iter = iter ->next;
        return node->element;
    }
    //index start with one, such that 1->first element in list
    void* getElement(int index)
    {
        ListNode *localIter = start;
        if (localIter == NULL) return NULL;
        for (int i=0; i <index; i++) {
           localIter = localIter->next;
           if (localIter == NULL) break;
        }
        return localIter->element;
    }
};

class Identifier
{
    public:
    char name[IDENTIFIER_LENGTH];
};

class List
{
    ListNode *head;
    int totalElements;
    public:
    List() { head = NULL; totalElements = 0;}

    DbRetVal append(void *elem)
    {
        ListNode *newNode = new ListNode();
        newNode->element = elem;
        newNode->next = NULL;
        totalElements++;
        //If this is the first node, set it as head
        if (NULL == head) { head = newNode; return OK; }

        ListNode *iter = head;
        while (NULL != iter->next) iter = iter->next;
        iter->next = newNode;
        return OK;
    }
    //Warning:Try to avoid using this method while using the iterator.The behavior 
    //is undefined. Instead set flag isRemove to yes and call nextElement of iterator.
    DbRetVal remove(void *elem, bool err=true) 
    {
        if (NULL == head)
        {
            if (err) 
               printError(ErrNotExists, "There are no elements in the list. Empty list");
            return ErrNotExists;
        }
        ListNode *iter = head, *prev = head;
        while (iter != NULL)
        {
            if (elem == iter->element)
            {
                if (iter == head) { head = iter->next; delete iter; return OK;}
                prev->next = iter->next;
                delete iter;
                totalElements--;
                return OK;
            }
            prev = iter;
            iter = iter->next;
        }
        if (err) 
            printError(ErrNotFound, "There are no elements in the list");
        return ErrNotFound;
    }

    //index start with one, such that 1->first element in list
    void* get(int index)
    {
        ListNode *localIter = head;
        if (localIter == NULL) return NULL;
        for (int i=0; i <index -1; i++) {
           localIter = localIter->next;
           if (localIter == NULL) break;
        }
        return localIter->element;
    }


    bool exists(void *elem) 
    {
        ListNode *iter = head;
        while (iter != NULL)
        {
            if (elem == iter->element)
            {
                return true;
            }
            iter = iter->next;
        }
        return false;
    }

    ListIterator getIterator()
    {
        ListIterator iter(head);
        return iter;
    }
    void reset()
    {
        if (NULL == head) return;
        ListNode *iter = head, *prevIter = head;
        while (iter->next != NULL)
        {
            prevIter = iter;
            iter = iter->next;
            delete prevIter;

        }
        delete iter;
        head = NULL;
        totalElements = 0;
        return;
    }
    int size()
    {
        return totalElements;
    }

};
#define MAX_UNIQUE_ID 10
class GlobalUniqueID
{
   void *ptr;
   public:
   GlobalUniqueID() { ptr = NULL; }
   DbRetVal create();
   DbRetVal open();
   DbRetVal close() { os::shm_detach(ptr); return OK; }
   DbRetVal destroy();
   int getID(UniqueIDType type);
};

class UniqueID
{
   int startID;
   Mutex mutex;
   public:
   UniqueID() { startID = 1; mutex.init(); }


   void setID(int id)
   {
        startID = id;mutex.init();
   }


   int getID()
   {
      //TODO::change mutex to atomic increment instruction
      if (mutex.getLock(-1, false) != 0) return 0;
      startID++;
      mutex.releaseLock(-1, false); 
      return startID;
   }
};

#endif
