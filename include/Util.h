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
#ifndef UTIL_H
#define UTIL_H
#include<ErrorType.h>
#include<Debug.h>
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
    ListIterator();
    public:

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
};


class List
{
    ListNode *head;
    public:
    List() { head = NULL;}

    DbRetVal append(void *elem)
    {
        ListNode *newNode = new ListNode();
        newNode->element = elem;
        newNode->next = NULL;
        //If this is the first node, set it as head
        if (NULL == head) { head = newNode; return OK; }

        ListNode *iter = head;
        while (NULL != iter->next) iter = iter->next;
        iter->next = newNode;
        return OK;
    }
    //Warning:Try to avoid using this method while using the iterator.The behavior 
    //is undefined. Instead set flag isRemove to yes and call nextElement of iterator.
    DbRetVal remove(void *elem) 
    {
        if (NULL == head)
        {
            printError(ErrNotExists, "There are no elements in the list. Empty list");
            return ErrNotExists;
        }
        ListNode *iter = head, *prev = head;
        while (iter->next != NULL)
        {
            if (elem == iter->element)
            {
                prev->next = iter->next;
                delete iter;
            }
            prev = iter;
            iter = iter->next;
        }
        if( iter == head) // there is only one node in the list
        {
            if (elem == iter->element)
            {
                delete head;
                head = NULL;
                return OK;
            }

        }
        if( prev == head) // there are only two node in the list
        {
            if (elem == iter->element)
            {
                head->next = NULL;
                delete iter;
                return OK;
            }
        }
        printError(ErrNotFound, "There are no elements in the list");
        return ErrNotFound;
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
        return;
    }
    int size()
    {
        int count =1;
        if (NULL == head) return 0;
        ListNode *iter = head;
        while (iter->next != NULL)
        {
            count++;
            iter = iter->next;
        }
        return count;
    }

};
#endif
