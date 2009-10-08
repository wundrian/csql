#include <HeapAllocator.h>
#include <ErrorType.h>
#include <Debug.h>

void VarHeapAllocator::print()
{
    printf("\nTotal number of new allocation happened : %d",newAllocateCounter);
    printf("\nTotal number of re allocation happened : %d",reAllocateCounter);
    printf("\nTotal number of deallocation happened : %d",deallocateCounter);
    printf("\nTotal number of page created : %d\n",pageCounter);
}
void VarHeapAllocator::initializeInfo(void *ptr)
{
    *(void **)ptr = top;
    top = ptr;
    usedBytes = 0;
    offset = (char *)top+PAGEINFOSIZE;
    *(short int *)((char *)offset+1) = pageSize- PAGEINFOSIZE-BLOCKINFOSIZE;
}
void VarHeapAllocator::init(int size,int pMode)
{
    mode = pMode;
    initSize(size);
}
void VarHeapAllocator::initSize(int size)
{
    void *ptr;
    ptr = calloc(size,1);
    if(ptr == NULL)
    {
        printError(ErrOS, "unable to allocate memory of %d bytes", size);
        return;
    }
    pageSize = size;
    initializeInfo(ptr);
    isInitialized = 1;
    pageCounter++;
}

void * VarHeapAllocator::allocate(int size)
{
    void *allocateptr, *ptr, *freeSpaceDetector, *pageDetector;
    short int pageSizeCounter = 0, add;
    short int isFound = 0;

    if(isInitialized != 1)
    {
        printError(ErrBadCall, "Error:not initialized");
        return NULL;
    }
    if(size > ( pageSize - PAGEINFOSIZE-(2*BLOCKINFOSIZE) ))
    {
        printError(ErrBadCall, "The requested size is greater than the page Size");
        return NULL;
    }
    if(mode ==0 )
    {
        //printf("\ninside allocate offset = %u\tpagesize= %d\tusedmemory=%d\tmemoryrequested = %d",offset,pageSize,usedBytes, size);
        if( ( usedBytes + size ) > ( pageSize - PAGEINFOSIZE ) )
        {
            ptr = calloc(pageSize,1);
            if(ptr == NULL)
            {
                printError(ErrOS, "unable to allocate memory of %d bytes",pageSize);
                return NULL;
            }
            pageCounter++;
            initializeInfo(ptr);
        }
        allocateptr = offset;
        offset = (char *)offset+size;
        usedBytes += size;
        //printf("\nafter allocate offset = %u\tusedmemory=%d\tmemoryrequested = %d\treturn ptr = %u",offset,usedBytes, size,allocateptr);
        return (allocateptr);
    }
    else if(mode == 1)
    {
        //printf("\nCursor is inside mode = 1");
        pageDetector = top;
        int isAllocated, noOfBytes;
        while(pageDetector)
        {
            isFound = 0;
            pageSizeCounter = 0;
            freeSpaceDetector = (char *)pageDetector+PAGEINFOSIZE;
            pageSizeCounter += PAGEINFOSIZE;
            isAllocated = *(char *)freeSpaceDetector;
            noOfBytes = *(short int *)((char *)freeSpaceDetector+1);
            //printf("\nStarting from the page:");
            //printf(":\nfreespacedetector is looking into the pointer: %d\n",freeSpaceDetector);
            //printf("\nfinding  allocation = %d and bytes = %d\n",isAllocated,noOfBytes);
            while(pageSizeCounter+noOfBytes+BLOCKINFOSIZE < pageSize)
            {
                if(isAllocated == 0 &&  noOfBytes >=  size+BLOCKINFOSIZE)
                {
                    isFound = 1;
                    reAllocateCounter++;
                    break;
                }
                pageSizeCounter = pageSizeCounter+noOfBytes+BLOCKINFOSIZE;
                freeSpaceDetector = (char *)freeSpaceDetector+noOfBytes+BLOCKINFOSIZE;
                //printf("\nfreespacedetector is looking into the pointer = %u ",freeSpaceDetector);
                isAllocated = *(char *)freeSpaceDetector;
                noOfBytes = *(short int *)((char *)freeSpaceDetector+1);
                //printf("\nfinding allocated = %d and bytes = %d\n",isAllocated,noOfBytes);
            }
            //printf("After searching the page (expect last block), pointer is at: %u",freeSpaceDetector);
            if(isFound == 1)
                break;
            //printf(" searching the last block of the page, at: %u",freeSpaceDetector);
            if(isFound == 0 && pageSizeCounter+noOfBytes+BLOCKINFOSIZE == pageSize)
            {
                if(isAllocated == 0 &&  noOfBytes >=  size+BLOCKINFOSIZE)
                {
                    isFound = 1;
                    newAllocateCounter++;
                     break;
                }
            }
            pageDetector = *(void **)pageDetector;
            //printf("next page at : %u",pageDetector);
        }
        if(pageDetector == NULL)
        {
            ptr = calloc(pageSize,1);
            if(ptr == NULL)
            {
                printError(ErrOS, "unable to allocate memory of %d bytes",pageSize);
                return NULL;
            }
            initializeInfo(ptr);
            newAllocateCounter++;
            pageCounter++;
            freeSpaceDetector =  (char *)top+PAGEINFOSIZE;
        }
        *(char *)freeSpaceDetector = 1;
        int availMemory = *(short int *)((char *)freeSpaceDetector+1);
        *(short int *)((char *)freeSpaceDetector+1) = size;
        *(short int *)((char *)freeSpaceDetector+size+BLOCKINFOSIZE+1) = availMemory-size-BLOCKINFOSIZE;
        //printf("\nHere we can get a free spase in side the current page: %d\n",freeSpaceDetector);
        //printf("\nis allocated == %d and bytes = %d\n",*(char *)freeSpaceDetector,*(short int *)((char *)freeSpaceDetector+1));
        //printf("\n next block = %u\t allocated == %d and bytes = %d\n",(char *)freeSpaceDetector+size+BLOCKINFOSIZE,*((char *)freeSpaceDetector+size+BLOCKINFOSIZE),*(short int *)((char *)freeSpaceDetector+size+BLOCKINFOSIZE+1) );
            
    }
}
void VarHeapAllocator::deallocate(void *ptr)
{
    //printf("\nBefore deAllocating the value at pointer is : %d",* (char *)ptr);
    *(char *)ptr = 0;
    //printf("\nAfter deAllocating the value at pointer is : %d",* (char *)ptr);
    deallocateCounter++;
}

void VarHeapAllocator::destroy()
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

/*
int main()
{
        int bsize;
        VarHeapAllocator mAllocator;
        mAllocator.init(50,1);
        int i = 0, choice;
        unsigned int ptr;
        while(true)
        {
                cout << "enter the choice that u want";
                cin>> choice;
                if(choice == 1)
                {
                        cout << "please enter the memory in bytes that u want to allocate";
                        cin >> bsize;
                        mAllocator.allocate(bsize);
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

}
*/

