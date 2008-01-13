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
#include<Table.h>
#include<Index.h>
#include<CatalogTables.h>
#include<Lock.h>
#include<Debug.h>

//does not check for duplicates
DbRetVal FieldList::append(FieldDef fDef)
{
    FieldNode *newNode = new FieldNode();
    newNode->fldDef = fDef;
    newNode->next = NULL;
    //If this is the first node, set it as head
    if (NULL == head) { head = newNode; return OK; }

    FieldNode *iter = head;
    while (NULL != iter->next) iter = iter->next;
    iter->next = newNode;
    return OK;
}


DbRetVal FieldList::remove(const char* fldName)
{
    if (NULL == head)
    {
        printError(ErrNotExists, "There are no elements in the list. Empty list");
        return ErrNotExists;
    }
    FieldNode *iter = head, *prev = head;
    while (iter->next != NULL)
    {
        if (0 == strcmp(iter->fldDef.fldName_, fldName))
        {
            prev->next = iter->next;
            delete iter;
        }
        prev = iter;
        iter = iter->next;
    }
    if( iter == head) // there is only one node in the list
    {
        if (0 == strcmp(iter->fldDef.fldName_, fldName))
        {
            delete head;
            head = NULL;
            return OK;
        }

    }
    if( prev == head) // there are only two node in the list
    {
        if (0 == strcmp(iter->fldDef.fldName_, fldName))
        {
            head->next = NULL;
            delete iter;
            return OK;
        }
    }
    printError(ErrNotFound, "There are no elements in the list");
    return ErrNotFound;
}

DbRetVal FieldList::removeAll()
{
    if (NULL == head) return OK;
    FieldNode *iter = head, *next = head;
    while (iter->next != NULL)
    {
        next = iter->next;
        delete iter;
        iter = next;
    }
    delete iter;  //deleting the last element
    head = NULL;
    return OK;
}

//-1->if val is passed NULL
//-2->if fld is not present
DbRetVal FieldList::updateBindVal(const char *fldName, void *val )
{
    if (NULL == val)
    {
        printError(ErrBadArg, "Value passed is NULL");
        return ErrBadArg;
    }
    FieldNode *iter = head;
    while(NULL != iter)
    {
        if (strcmp(iter->fldDef.fldName_, fldName) == 0)
        {
            iter->fldDef.bindVal_ = val;
            return OK;
        }
        iter = iter ->next;
    }
    printError(ErrNotFound, "Field not present in the list");
    return ErrNotFound;
}

DbRetVal FieldList::getFieldInfo(const char *fldName, FieldInfo *&info)
{
    FieldNode *iter = head;
    while(iter != NULL)
    {
        if (0 == strcmp(iter->fldDef.fldName_, fldName))
        {
            strcpy(info->fldName , iter->fldDef.fldName_);
            info->length = iter->fldDef.length_;
            info->type   = iter->fldDef.type_;
            info->offset = getFieldOffset(fldName);
            info->isDefault = iter->fldDef.isDefault_;
            strcpy(info->defaultValueBuf, iter->fldDef.defaultValueBuf_);
            info->isNull = iter->fldDef.isNull_;
            info->isPrimary = iter->fldDef.isPrimary_;
            return OK;

        }
        iter = iter ->next;
    }
    return ErrNotFound;
}

int FieldList::getFieldOffset(const char *fldName)
{
    FieldNode *iter = head;
    int offset = 0;
    while(iter != NULL)
    {
        if (0 == strcmp(iter->fldDef.fldName_, fldName))
        {
            return offset;
        }
        offset = offset + os::align(iter->fldDef.length_);
        iter = iter ->next;
        }
        return -1;
}
int FieldList::getFieldOffset(int fldpos)
{
    if (fldpos < 1) return -1;
    FieldNode *iter = head;
    int offset = 0;
    int counter =0;
    while(iter != NULL)
    {
        if (counter == fldpos -1)
        {
            return offset;
        }
        offset = offset + os::align(iter->fldDef.length_);
        iter = iter ->next;
        counter++;
    }
    return -1;
}

//Returns position of field in the list
//Count starting from 1
//-1 if field not found in the list
int FieldList::getFieldPosition(const char *fldName)
{
    int position = 1;
    FieldNode *iter = head;
    while(iter != NULL)
    {
        if (0 == strcmp(iter->fldDef.fldName_, fldName))
            return position;
        position++;
    }

    return -1;
}

int FieldList::getTupleSize()
{
    FieldNode *iter = head;
    int offset = 0;
    while(iter != NULL)
    {
        offset = offset + os::align(iter->fldDef.length_);
        iter = iter ->next;
        }
        return offset;
}



DataType FieldList::getFieldType(const char *fldName)
{
    FieldNode *iter = head;
    int offset = 0;
    while(iter != NULL)
    {
        if (0 == strcmp(iter->fldDef.fldName_, fldName))
        {
            return iter->fldDef.type_;
        }
        iter = iter ->next;
        }
    return typeUnknown;
}

//-1->if field not present in list
size_t FieldList::getFieldLength(const char *fldName)
{
    FieldNode *iter = head;
    int offset = 0;
    while(iter != NULL)
    {
        if (0 == strcmp(iter->fldDef.fldName_, fldName))
        {
            return iter->fldDef.length_;
        }
        iter = iter ->next;
    }
    return -1;
}


//No check for duplicates
//TODO::User exposed so check for duplicates
DbRetVal FieldNameList::append(const char *name)
{
    FieldNameNode *newNode = new FieldNameNode();
    strcpy(newNode->fldName, name);
    newNode->next = NULL;
    //If this is the first node, set it as head
    if (NULL == head) { head = newNode; return OK; }

    FieldNameNode *it = head;
    while (NULL != it->next) it = it->next;
    it->next = newNode;
    return OK;
}
//-1 -> if there is nothing in list
//-2 -> if it is not present in list
DbRetVal FieldNameList::remove(const char* name)
{
    if (NULL == head)
    {
            printError(ErrNotExists, "List is empty");
            return ErrNotExists;
        }
    FieldNameNode *ite = head, *prev = head;
    while (ite->next != NULL)
    {
        if (0 == strcmp(ite->fldName, name))
        {
            prev->next = ite->next;
            delete ite;
        }
        prev = ite;
        ite = ite->next;
    }
    if( ite == head) // there is only one node in the list
    {
        if (0 == strcmp(ite->fldName, name))
        {
            delete head;
            head = NULL;
            return OK;
        }

    }
    if( prev == head) // there are only two node in the list
    {
        if (0 == strcmp(ite->fldName, name))
        {
            head->next = NULL;
            delete ite;
            return OK;
        }
    }
        printError(ErrNotFound, "Field name %s not present in the list", name);
        return ErrNotFound;
}

DbRetVal FieldNameList::removeAll()
{
    if (NULL == head) return OK;
    FieldNameNode *iter = head, *next = head;
    while (iter->next != NULL)
    {
        next = iter->next;
        delete iter;
        iter = next;
    }
    delete iter;  //deleting the last element
    head = NULL;
    return OK;
}

char* FieldNameList::nextFieldName()
{
    if (iter == NULL) return NULL;
    FieldNameNode *node = iter;
    iter = iter ->next;
    return node->fldName;
}

int FieldNameList::size()
{
    FieldNameNode *it = head;
    if (NULL == it) return 0;
    int count = 1;
    while (NULL != it->next) {it = it->next; count++;}
    return count;
}
