#include<HeapAllocator.h>
#include<ErrorType.h>
#include<Debug.h>
#include <Util.h>
#include <DataType.h>    

DbRetVal HashMap::insert(void *element)
{
    HashMapNode *newNode = new HashMapNode();
    newNode->elem = element;
    newNode->next = NULL;
    int hashVal =0;
    if (optGrpIntNoNull)
        hashVal = (*(int*)element) % bucketSize;
    else
        hashVal = Util::hashBinary((char*)element, keySize) % bucketSize;
    HashMapNode *node = (HashMapNode*) bucket[hashVal];
    if (NULL == node)
    {
        bucket[hashVal] = newNode;
        return OK;
    }
    while(node->next != NULL) { node=node->next; }
    node->next = newNode;
    return OK;
}
void* HashMap::find(void *element)
{
    int hashVal = 0;
    if (optGrpIntNoNull) {
        int value = *(int*)element;
        hashVal = value % bucketSize;
        HashMapNode *node = (HashMapNode*) bucket[hashVal];
        while(node != NULL) {
          if (*(int*)node->elem == value) return node->elem;
          node = node->next;
        }
    }
    else {
        hashVal = Util::hashBinary((char*)element, keySize) % bucketSize;
        HashMapNode *node = (HashMapNode*) bucket[hashVal];
        while(node != NULL) {
          if (AllDataType::compareVal(node->elem, element, OpEquals,
                                             typeBinary, keySize))
            return node->elem;
          node = node->next;
        }
    }
    return NULL;
}
void HashMap::removeAll()
{
    for (int i=0; i <bucketSize; i++) {
        HashMapNode *node =(HashMapNode*) (bucket[i]);
        HashMapNode *prev = NULL;
        while(node != NULL) {
            prev = node;
            node = node->next;
            delete prev;
        }
        bucket[i]=NULL;
    }
    return;
}

