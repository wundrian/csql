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
#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include<os.h>
#include<Mutex.h>
#include<ErrorType.h>
#include<Config.h>

typedef void Page;

enum AllocType
{
    FixedSizeAllocator = 0,
    VariableSizeAllocator = 1,
    UnknownAllocator
};

//Used to store the meta data information about the variable size data
class VarSizeInfo
{
    public:
    InUse size_;
    InUse isUsed_;
};

//Each Page has this info.
//pages are of size PAGE_SIZE normally.
//If data size is more than PAGE_SIZE then
//contigous pages are merged and those pages wont
//have this info in them.Only the start page where that
//data is stored will have this info
//This object is stored at the start of each page
#define HAS_SPACE 1
#define IS_DIRTY  2

class PageInfo
{
     public:
     InUse isUsed_;
     InUse flags; //stores hasFreeSpace and isDirty

     Page *nextPageAfterMerge_; //used only in case of
     //where pages are merged to store data which are more than
     //PAGE_SIZE.
     //More detail about how it is used is found in Database::getFreePage

     Page *nextPage_; //next page in the same chunk
     void setPageAsUsed(size_t offset);
     void setFirstPageAsUsed();
     void setPageAsFree();

};
class Chunk;


//Iterator for the data
//Data is stored in chunks and this class gives
//iterator for it.
class ChunkIterator
{
    int chunkID_;
    size_t allocSize_; // used if it is a fixed size allocator
    AllocType allocType_;

    //current iterating page
    PageInfo *iterPage_;

    //Each page is divided into nodes of size allocSize_
    //This gives the offset of the node in the page
    int nodeOffset_;
    char *data;
    char *iterPageEnd;

    //Total number of nodes in the page
    //It is a constant value for this chunk
    //and it is cached for performance
    int noOfNodes_;


    public:
    int pageSize;
    ChunkIterator() { pageSize = PAGE_SIZE; allocSize_ =0; iterPage_ = NULL; nodeOffset_ =0; 
                      chunkID_ = -1; noOfNodes_  =0; }
    int isLargeSize() { if (noOfNodes_ == 0) return true; else return false; }
    void* nextElement();
    void* nextElementIntMatch(int value, int offset);
    inline void* nextElementInt() {
        if (!data) {
            pageSize = PAGE_SIZE;
            data = ((char*)iterPage_) + sizeof(PageInfo);
            if ((*(InUse*)data) == 1) return data + sizeof(InUse);
        }

        if(0 == noOfNodes_) return nextElement();
        data += allocSize_;
        while(data < iterPageEnd)
        {
            if (*((InUse*)data)) {
                return data + sizeof(InUse);
            } else {
               data += allocSize_;
            }
        }
        while(iterPage_->nextPage_ != NULL)
        {
            iterPage_ = (PageInfo*)iterPage_->nextPage_;
            data = ((char*)iterPage_) + sizeof(PageInfo);
            iterPageEnd = ((char*)iterPage_) + pageSize;
            while(data < iterPageEnd)
            {
                if (*((InUse*)data) == 0) {
                   data = data + allocSize_;
                   nodeOffset_++;
                } else 
                    return data +sizeof(InUse);
            }
        }
        return NULL;
    }
    friend class Chunk;
};

class Database;
class DatabaseManagerImpl;

class Chunk
{
    int chunkID_;

    // used if it is a fixed size allocator
    size_t allocSize_;
    AllocType allocType_;

    //Current page where the last data allocation was made
    Page *curPage_;

    //Page where data allocation was made for the first time
    //This is the start of the data
    //Iterator should start from this page
    Page *firstPage_;
    char chunkName[CHUNK_NAME_LEN];
    Mutex chunkMutex_;

    public:

    //sets the size of the allocator
    //for fixed size allocator
    void setSize(size_t size);

    void setChunkNameForSystemDB(int id);
    void setChunkName(char const *name){strcpy(chunkName,name);}
    char *getChunkName(){return chunkName;}

    size_t getSize()                  { return allocSize_; }
    void setChunkID(unsigned int id)           { chunkID_ = id; }
    int getChunkID()                  { return chunkID_; }
    void setAllocType(AllocType type) { allocType_ = type; }
    AllocType getAllocType()          { return allocType_; }
    Page* getFirstPage(){ return firstPage_; }
    Page* getCurrentPage(){ return curPage_; }
    void setFirstPage(void *fp) { firstPage_ = fp;}
    void setCurPage(void *cp) { curPage_ = cp;}
    PageInfo* getPageInfo(Database *db, void *ptr);
    void* allocate(Database *db, DbRetVal *status);

    void* allocate(Database *db, size_t size, DbRetVal *status);

    void  free(Database *db, void* ptr);
    ChunkIterator getIterator();
    void print();

    long getTotalDataNodes();
    int totalPages();
    int totalDirtyPages();
    int compact(int procSlot);

    private:

    int initMutex();
    int getChunkMutex(int procSlot);
    int releaseChunkMutex(int procSlot);
    int destroyMutex();
    int createDataBucket(Page *page, size_t totalSize, size_t needSize, int pslot);
    int splitDataBucket(VarSizeInfo *varInfo, size_t needSize, int pslot, DbRetVal *status);
    void* varSizeFirstFitAllocate(size_t size, int pslot, DbRetVal *status);
    void freeForLargeAllocator(void *ptr, int pslot);
    void freeForVarSizeAllocator(Database *db, void *ptr, int pslot);

    void* allocateForLargeDataSize(Database *db);
    void* allocateFromFirstPage(Database *db, int noOfDataNodes, DbRetVal *status);
    void* allocateFromNewPage(Database *db, DbRetVal *status);

    void* allocateForLargeDataSize(Database *db, size_t size);
    void* allocFromNewPageForVarSize(Database *db, size_t size, int pslot,
                                     DbRetVal *status);
    void* allocateFromCurPageForVarSize(size_t size, int pslot, DbRetVal *status);
    void setPageDirty(Database *db, void *ptr);
    void setPageDirty(PageInfo *pInfo);


    friend class Database;
    friend class DatabaseManagerImpl;
};
#endif
