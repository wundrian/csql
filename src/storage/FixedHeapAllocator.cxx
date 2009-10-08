#include <HeapAllocator.h>
#include <ErrorType.h>
#include <Debug.h>

void FixedHeapAllocator::initializeInfo(void *ptr)
{
    *(void **)ptr = top;
    top = ptr;
    usedBytes = 0;
    offset = (char*)top+PAGEINFOSIZE;
    *(short*)((char*)offset+1) = pageSize- PAGEINFOSIZE-BLOCKINFOSIZE;
}

void FixedHeapAllocator::init(int pSize,int allocSize)
{
     void *ptr;
    ptr = ::calloc(pSize,1);
    if(ptr == NULL)
    {
        printError(ErrOS, "Unable to allocate %d bytes", pSize);
        return;
    }
    allocateSize = allocSize;
    pageSize = pSize;
    initializeInfo(ptr);
    isInitialized = 1;
    pageCounter++;
 
}

void* FixedHeapAllocator::allocate()
{
    void *allocateptr, *ptr, *freeSpaceDetector, *pageDetector;
    short int pageSizeCounter = 0, add;
    short int isFound = 0;

    if(isInitialized != 1)
    {
        printError(ErrBadCall, "Allocator is not initialized");
        return NULL;
    }
    if(allocateSize > ( pageSize - PAGEINFOSIZE-(2*BLOCKINFOSIZE) ))
    {
        printf("The requested size is greater than the page Size");
        return NULL;
    }
    //TODO::we will implement mode later for this fixed size allocator
    //printf("\ninside allocate offset = %u\tpagesize= %d\tusedmemory=%d\tmemoryrequested = %d",offset,pageSize,usedBytes, allocateSize  );
    if( ( usedBytes + allocateSize ) > ( pageSize - PAGEINFOSIZE ) )
    {
        printDebug(DM_Alloc, "Current page exhausted. allocating new page");
        ptr = calloc(pageSize,1);
        if(ptr == NULL)
        {
            printError(ErrOS, "Unable to allocate %d bytes", pageSize);
            return NULL;
        }
        pageCounter++;
        initializeInfo(ptr);
    }
    allocateptr = offset;
    offset = (char *)offset+allocateSize ;
    usedBytes += allocateSize ;
    //printf("\nafter allocate offset = %u\tusedmemory=%d\tmemoryrequested = %d\treturn ptr = %u",offset,usedBytes, allocateSize,allocateptr);
    return (allocateptr);
}

void FixedHeapAllocator::deAllocate(void *ptr)
{
}

void FixedHeapAllocator::destroy()
{
    void *ptr, *temp;
    ptr = top;
    unsigned int  add;
    while(ptr)
    {
        temp = ptr;
        ptr = *(void **)ptr;
        //printf("deallocating %u",temp);
        free(temp);
    }
}

/*int main()
{
    cout << "This is the main program";
    int bsize;
    FixedHeapAllocator mAllocator;
    mAllocator.init(50,10);
    int i = 0, choice;
    unsigned int ptr;
    while(true)
    {
        cout << "enter the choice that u want";
        cin>> choice;
        if(choice == 1)
        {
    //        cout << "please enter the memory in bytes that u want to allocate";
      //      cin >> bsize;
            mAllocator.allocate();
        }
        else if(choice == 2)
        {
            cout << "please enter the memory address to deallocate";
            cin >> ptr;
        }
        else
        {
        //              exit(1);
            break;
        }
    }

    mAllocator.destroy();
    exit(1);
}*/
