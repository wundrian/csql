/***************************************************************************
 *                                                                         *
 *       Copyright (C) Lakshya Solutions Ltd. All rights reserved.         *
 *                                                                         *
 ***************************************************************************/

#ifndef HEAP_ALLOCATOR
#define HEAP_ALLOCATOR
#include <os.h>
#include <ErrorType.h>
#define PAGEINFOSIZE 4
#define BLOCKINFOSIZE 4

class DllExport VarHeapAllocator
{
    void *top;
    void *last;
    void *offset;
    int pageSize;
    int usedBytes;
    int mode;
    int newAllocateCounter;
    int reAllocateCounter;
    int pageCounter;
    int deallocateCounter;
    int isInitialized;

    void initializeInfo(void *ptr);
    void initSize(int size);

    public:
    VarHeapAllocator()
    {
        top = offset =  NULL;
        mode = 0;
        isInitialized = 0;
        pageCounter=0;
        newAllocateCounter=0;
        deallocateCounter=0;
        reAllocateCounter=0;
    }
    void init(int size, int pMode =0);
    void * allocate(int size);
    void deallocate(void *);
    void destroy();
    void print();
    void itirate();
};
class DllExport FixedHeapAllocator
{
    int blockSize;
    int usedBytes;
    int pageSize;
    int allocateSize;
    int isInitialized;
    int newAllocateCounter;
    int reAllocateCounter;
    int pageCounter;
    int deallocateCounter;
     
    void *top;
    void *offset;
    void initializeInfo(void *ptr);

    public:
    FixedHeapAllocator()
    {
        top = offset =  NULL;
        isInitialized = 0;
        pageCounter=0;
        newAllocateCounter=0;
        deallocateCounter=0;
        reAllocateCounter=0;  
     }
     void init(int pSize,int allocSize);
     void *allocate();
     void deAllocate(void *ptr);
     void destroy();
};
class DllExport HashMapNode
{
   public:
   void *elem;
   HashMapNode *next;
   HashMapNode() { elem = NULL; next = NULL; }
   void print() { printf("elem:%p next %p\n", elem, next); }
};
class DllExport HashMap
{
    void **bucket;
    int keySize;
    int bucketSize;
    bool optGrpIntNoNull;
    public:
    HashMap(){ keySize = 0; bucketSize = 1009;
               bucket = (void**) ::malloc(bucketSize * sizeof(void*));
               memset(bucket, 0, bucketSize * sizeof(void*));
               optGrpIntNoNull = false;
             }
    ~HashMap() { ::free(bucket); }
    void setKeySize(int size) { keySize = size; }
    void setGrpIntNoNull(){ optGrpIntNoNull = true; }
    DbRetVal insert(void *elem);
    void* find(void *elem);
    bool remove(void *elem);
    void removeAll();
};

#endif
