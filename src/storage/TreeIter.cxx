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
void* TreeIter::next()
{
    int direction=0;
    if (recordsOver) return NULL;
    if (NULL== iter) return NULL;
    if (firstCall)
    {
        if (OpLessThan ==op || OpLessThanEquals == op)
        {
            while(iter->prev_)
            {
                iter = iter->prev_;
            }
            firstCall = false;
            nodeOffset = 1;
            char **rec = (char**)((char*) iter + sizeof(TreeNode));
            iter->displayAll(fldOffset);
            return *rec;
        }
        else if (OpGreaterThan == op || OpGreaterThanEquals == op || 
                 OpEquals == op)
        {
            void *rec = locateNode();
            firstCall = false;
            iter->displayAll(fldOffset);
            return rec;
        }
        firstCall = false;
    }else
    {
        if (nodeOffset == iter->noElements_) 
        {
            if (NULL == iter->next_) {recordsOver = true; return NULL;}
            char* record = ((char*)iter->next_->min_)+ fldOffset;
            bool result = AllDataType::compareVal(searchKey, record, 
                                              OpGreaterThanEquals,
                                              type, length);
            if (!result && (OpLessThan ==op || OpLessThanEquals == op)) 
            { 
                recordsOver= true; return NULL; 
            }else if (result && (OpGreaterThan == op || 
                      OpGreaterThanEquals == op))
            {
                recordsOver= true; return NULL; 
            }
            iter=iter->next_;
            if (NULL == iter) return NULL;
            nodeOffset=0;
        }
        char **rec = (char**)((char*)iter + sizeof(TreeNode));
        rec = (char**)((char *)rec + ((nodeOffset) * sizeof(void **)));
        nodeOffset++;
        return *rec;
    }
    return NULL;
}
void* TreeIter::locateNode()
{
    while(iter != NULL)
    {
        char *record = ((char*)iter->max_)+ fldOffset;
        bool result = AllDataType::compareVal(searchKey, record,
                                              OpGreaterThan,
                                              type, length);
        if (result)
        {
            //need to move right
            iter = iter->next_;
        }else
        {
            record = ((char*)iter->min_)+ fldOffset;
            result = AllDataType::compareVal(searchKey, record, 
                                             OpGreaterThanEquals,
                                             type, length);
            if (result) {
                //current node contains the key
                void *rec = locateElement();
                return rec;
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
void* TreeIter::locateElement()
{
    //do binary search and locate the element 
    int loc=0, middle=0, start=0, end=iter->noElements_-1;
    char **rec = (char**)((char*)iter + sizeof(TreeNode));
    for(middle = (start + end) / 2; start <= end ; middle = (start +end )/2)
    {
        loc = middle;
        char *record = ((char*)*(rec+middle)) + fldOffset;
        bool res = AllDataType::compareVal(searchKey, record, OpEquals, 
                                           type, length);
        if(res)
        {
            loc = middle;
            break;
        }
        res = AllDataType::compareVal(searchKey, record, OpLessThan, 
                                          type, length);
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
    nodeOffset=loc;
    char **tuple = (char**)((char*)rec + (loc * sizeof(void *)));
    nodeOffset++;
    return *tuple;
}
