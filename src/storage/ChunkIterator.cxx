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
#include<Allocator.h>
#include<Database.h>
#include<os.h>
#include<Debug.h>
#include<Config.h>

//No iterators for variable size allocators
ChunkIterator Chunk::getIterator()
{
    ChunkIterator iter;
    iter.chunkID_ = chunkID_;
    iter.allocSize_ = allocSize_;
    iter.allocType_ = allocType_;
    iter.iterPage_ = firstPage_;
    iter.nodeOffset_ = 0;
    iter.noOfNodes_ = os::floor((PAGE_SIZE - sizeof(PageInfo)) / allocSize_);
    return iter;
}

void* ChunkIterator::nextElement()
{
    if(NULL == iterPage_)
    {
        printError(ErrNotExists,"No iter page exists.");
        return NULL;
    }
    //No iterators for variable size allocators
    if(0 == allocSize_)
    {
        printError(ErrNotExists,"Iterators are not for variable size allocators");
        return NULL;
    }
    PageInfo* pageInfo = (PageInfo*)iterPage_;
    if (0 == noOfNodes_)
    {
        //means tuple larger than PAGE_SIZE
        iterPage_ = pageInfo->nextPage_;
        return (char*)pageInfo + sizeof(PageInfo)+ sizeof(int);
    }

    char *data = ((char*)iterPage_) + sizeof(PageInfo) + (nodeOffset_ * allocSize_) ;

    //check whether there are any nodes in the current page
    int i = nodeOffset_;
    while(nodeOffset_ < noOfNodes_)
    {
        if (*((int*)data) == 0)
        {
          //not used, so skip it
           data = data + allocSize_;
           nodeOffset_++;
           if (data >= (char*)iterPage_ + PAGE_SIZE) break; 
        }
        else
        {
           //used, return element pointer
           nodeOffset_++;
           printDebug(DM_Iterator,"ChunkID:%d Returning %x nodeOffset:%d",
                                  chunkID_, data + sizeof(int), nodeOffset_);
           return data + sizeof(int);
        }
    }
    //go to next page and check till it exhausts
    while(pageInfo->nextPage_ != NULL)
    {
        iterPage_ = pageInfo->nextPage_;
        pageInfo = ((PageInfo*)iterPage_);
        data = (char*)iterPage_ + sizeof(PageInfo);
        nodeOffset_ = 0;
        while(nodeOffset_ < noOfNodes_)
        {
            if (*((int*)data) == 0)
            {
               //not used, so skip it
               data = data + allocSize_;
               nodeOffset_++;
            }
            else
            {
                nodeOffset_++;
                printDebug(DM_Iterator,"ChunkID:%d Returning %x Page:%x nodeOffset:%d",
                                 chunkID_, data + sizeof(int), pageInfo, nodeOffset_);
                return data +sizeof(int);
            }
        }
    }
    return NULL;
}
