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
    iter.iterPage_ = (PageInfo*)firstPage_;
    iter.nodeOffset_ = 0;
    iter.noOfNodes_ = os::floor((PAGE_SIZE - sizeof(PageInfo)) / allocSize_);
    iter.data = NULL;
    iter.iterPageEnd = ((char*)firstPage_) +PAGE_SIZE;
    printDebug(DM_Iterator,"ChunkID:%d FirstPage is %x",
                                  chunkID_, iter.iterPage_);
    return iter;
}

void* ChunkIterator::nextElement()
{
    /*if(NULL == iterPage_)
    {
        printError(ErrNotExists,"No iter page exists.");
        return NULL;
    }*/
    //PageInfo* pageInfo = (PageInfo*)iterPage_;
    if (0 == noOfNodes_)
    {
        //means tuple larger than PAGE_SIZE
        if(NULL == iterPage_) return NULL;
        char *record =NULL;
        record = ((char*)iterPage_)  +sizeof(PageInfo);
        while(*(int*)record != 1)
        {
            iterPage_ = (PageInfo*) iterPage_->nextPage_;
            if(NULL == iterPage_) return NULL;
            record = ((char*)iterPage_)  +sizeof(PageInfo);
        }
        iterPage_ = (PageInfo*) iterPage_->nextPage_;
        return (record + sizeof(int));
    }

    //check whether there are any nodes in the current page
    //int i = nodeOffset_;
    if (!data) {
        data = ((char*)iterPage_) + sizeof(PageInfo);
        if ((*(int*)data) == 1) 
            return data + sizeof(int);
    } 
    data = data + allocSize_;
    while(data < iterPageEnd)
    {
        if (*((int*)data) == 0)
        {
          //not used, so skip it
           data = data + allocSize_;
           printDebug(DM_Iterator,"ChunkID:%d Moving to next data node %x",
                                  chunkID_, data);
        }
        else
        {
           //used, return element pointer
           //nodeOffset_++;
           printDebug(DM_Iterator,"ChunkID:%d Returning %x nodeOffset:%d",
                                  chunkID_, data + sizeof(int), nodeOffset_);
           return data + sizeof(int);
        }
    }
    //go to next page and check till it exhausts
    while(iterPage_->nextPage_ != NULL)
    {
        iterPage_ = (PageInfo*)iterPage_->nextPage_;
        data = ((char*)iterPage_) + sizeof(PageInfo);
        iterPageEnd = ((char*)iterPage_) + PAGE_SIZE;
        while(data < iterPageEnd)
        {
            if (*((int*)data) == 0)
            {
               //not used, so skip it
               data = data + allocSize_;
               nodeOffset_++;
            }
            else
            {
                //nodeOffset_++;
                printDebug(DM_Iterator,"ChunkID:%d Returning %x",
                                 chunkID_, data + sizeof(int));
                return data +sizeof(int);
            }
        }
    }
    return NULL;
}
