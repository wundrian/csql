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
#include<Debug.h>
#include<Table.h>
#include<TableImpl.h>
#include<AggTableImpl.h>
AggTableImpl::AggTableImpl()
{
}
AggTableImpl::~AggTableImpl()
{
    close();
}
void *AggTableImpl::getBindFldAddr(const char *name)
{
    printError(ErrBadCall, "AggTableImpl getBindFldAdddr not implemented\n"); 
    return NULL;
}



DbRetVal AggTableImpl::bindFld(const char *name, void *val)
{
    printError(ErrBadCall, "AggTableImpl bindFld not implemented\n"); 
    return ErrBadCall;
}
DbRetVal AggTableImpl::bindFld(const char *fldname, AggType aggType, void *val)
{
    FieldInfo *info = new FieldInfo();
    tableHdl->getFieldInfo(fldname, info);
    AggFldDef *def = new AggFldDef();
    strcpy(def->fldName, fldname);
    def->type = info->type;
    def->length= info->length;
    def->appBuf = val;
    def->atype=aggType;
    def->bindBuf = NULL;
    def->alreadyBinded = false;
    ListIterator iter = fldList.getIterator();
    AggFldDef  *elem;
    //If it is already binded, then use the same buffer which is binded.
    //this code is to handle statements which have more aggregates on same field
    while (iter.hasElement())
    {
        elem = (AggFldDef*) iter.nextElement();
        if (strcmp(elem->fldName, fldname)==0)
        {
            def->bindBuf = elem->bindBuf;
            def->alreadyBinded = true;
            break;
        }
    }
    if (!def->bindBuf)
    {
        def->bindBuf = AllDataType::alloc(def->type, def->length);
        tableHdl->bindFld(fldname, def->bindBuf);
    }
    fldList.append(def);
    delete info;
    return OK;
}
DbRetVal AggTableImpl::setGroup(const char *fldname, void *val)
{
    FieldInfo *info = new FieldInfo();
    tableHdl->getFieldInfo(fldname, info);
    strcpy(groupFld.fldName, fldname);
    groupFld.type = info->type;
    groupFld.length = info->length;
    groupFld.appBuf = val;
    groupFld.bindBuf = AllDataType::alloc(info->type, info->length);
    tableHdl->bindFld(fldname, groupFld.bindBuf);
    delete info;
    return OK;
}

DbRetVal AggTableImpl::execute()
{
    ListIterator iter = fldList.getIterator();
    AggFldDef  *def;
    if (isGroupSet())
        aggNodeSize = groupFld.length;
    else
        aggNodeSize = 0;
    while (iter.hasElement())
    {
         def = (AggFldDef*) iter.nextElement();
         if (def->atype != AGG_UNKNOWN && 
             0 == strcmp(def->fldName, groupFld.fldName))
         {
             def->atype = AGG_UNKNOWN;
         }
         aggNodeSize = aggNodeSize + def->length;
         if (def->atype == AGG_AVG) aggNodeSize = aggNodeSize + sizeof(int);//for count
    }
    void *tuple = NULL;
    int offset=0;
    tableHdl->execute();
    aggNodes.reset();
    while((tuple = tableHdl->fetch()) != NULL)
    {
        char *buffer = (char*)insertOrGet();
        iter.reset();
        if (isGroupSet())
            offset = groupFld.length;
        else
            offset = 0;
        while (iter.hasElement())
        {
           def = (AggFldDef*) iter.nextElement();
           switch(def->atype)
           {
               case AGG_MIN: {
                   bool result = AllDataType::compareVal(buffer+offset,
                                 def->bindBuf, OpGreaterThanEquals, def->type, def->length);
                   if (result)
                       AllDataType::copyVal(buffer+offset, def->bindBuf,
                                            def->type, def->length);
                   break;
               }
               case AGG_MAX: {
                   bool result = AllDataType::compareVal(buffer+offset,
                                        def->bindBuf, OpLessThanEquals, def->type, def->length);
                   if (result)
                       AllDataType::copyVal(buffer+offset, def->bindBuf,
                                            def->type, def->length);
                   break;
               }
               case AGG_SUM: {
                   AllDataType::addVal(buffer+offset, def->bindBuf, def->type);
                   break;
               }
               case AGG_AVG: {
                   AllDataType::addVal(buffer+offset, def->bindBuf, def->type);
                   (*(int*)(buffer+offset + def->length))++;
                   offset = offset +sizeof(int); //->count
                   break;
               }
               case AGG_COUNT:
                   (*(int*)(buffer+offset))++;
                   if ((*(int*)(buffer+offset)) % 1000000 ==0) 
                              printf("PRABA:%d\n", (*(int*)(buffer+offset)));
                   break;
               case AGG_UNKNOWN: 
               {
                   AllDataType::copyVal(buffer+offset, groupFld.bindBuf,
                                            groupFld.type, groupFld.length);
                   break;
               }
           }
           offset = offset + def->length;
        }
    }
    aggNodeIter  = aggNodes.getIterator();
    iter.reset();
    char *element;
    while (iter.hasElement()) {
        def = (AggFldDef*) iter.nextElement();
        if (isGroupSet())
            offset = groupFld.length;
        else
            offset = 0;
        switch(def->atype)
        {
            case AGG_AVG: {
               while (aggNodeIter.hasElement()) {
                   element = (char*)aggNodeIter.nextElement();
                   AllDataType::divVal(element+offset,
                      *(int*)(element+offset+ def->length), def->type);
               }
               offset = offset +sizeof(int);
            }
        }
        offset = offset + def->length;
    }
    aggNodeIter.reset();
    tableHdl->closeScan();
    return OK;
}
void* AggTableImpl::insertOrGet()
{
    char *element;
    if (!isGroupSet()) {
       ListIterator aiter = aggNodes.getIterator();
       if (aiter.hasElement()) 
          return aiter.nextElement();
    } else {
       //TODO::perf opt for no group
       //TODO::if group not set, use another class variable
       element = (char*) aggNodeMap.find(groupFld.bindBuf);
       if (element) return element;
    }

    /*ListIterator aiter = aggNodes.getIterator();
    while (aiter.hasElement()) {
        element = (char*)aiter.nextElement();

        if (!isGroupSet()) return element;
        if (AllDataType::compareVal(element, groupFld.bindBuf, OpEquals,
                                             groupFld.type, groupFld.length))
        {
            return element;
        }
    }*/
    element = (char*)malloc(aggNodeSize);
    ListIterator iter = fldList.getIterator();
    AggFldDef  *def;
    char *offset;
    if (isGroupSet()) {
        AllDataType::copyVal(element, groupFld.bindBuf, groupFld.type,
                                                 groupFld.length);
        offset = element + groupFld.length;
    }
    else
        offset = element;

    while (iter.hasElement())
    {
         def = (AggFldDef*) iter.nextElement();
         switch(def->atype) {
             case AGG_MIN: { *(int*)(offset)=INT_MAX; break; }
             case AGG_MAX: { *(int*)(offset)=INT_MIN; break; }
             case AGG_SUM: { *(int*)(offset)=0; break; }
             case AGG_AVG: {
                 *(int*)(offset)=0;
                 *(int*)(offset+ def->length)=0; //count
                 offset = offset+ sizeof(int);
                 break;
             }
             case AGG_COUNT: { *(int*)(offset)=0; break; }
         }
         offset = offset + def->length;
    }
    aggNodes.append(element);
    aggNodeMap.insert(element);
    return element;
}

void* AggTableImpl::fetch()
{
    if(aggNodeIter.hasElement())
    {
        void *elem = aggNodeIter.nextElement();
        copyValuesToBindBuffer(elem);
        return elem;
    }
    else
    return NULL;

}
void* AggTableImpl::fetch(DbRetVal &rv)
{
    rv = OK;
    return fetch();
}

void* AggTableImpl::fetchNoBind()
{
    if(aggNodeIter.hasElement())
    {
        void *elem = aggNodeIter.nextElement();
        return elem;
    }
    else
    return NULL;
}

void* AggTableImpl::fetchNoBind(DbRetVal &rv)
{
    rv = OK;
    return fetchNoBind();
}

DbRetVal AggTableImpl::copyValuesToBindBuffer(void *elem)
{
    char *element = (char*)elem;
    //Iterate through the bind list and copy the value here
    ListIterator fIter = fldList.getIterator();
    AggFldDef  *def;
    AllDataType::copyVal(groupFld.appBuf, elem, groupFld.type, groupFld.length);
    char *colPtr = (char*) elem + groupFld.length;
    while (fIter.hasElement())
    {
        def = (AggFldDef*) fIter.nextElement();
        if (NULL != def->appBuf) {
            AllDataType::copyVal(def->appBuf, colPtr, def->type, def->length);
        }
        colPtr = colPtr + def->length;
        if(def->atype == AGG_AVG) colPtr = colPtr + sizeof(int);
    }
    return OK;
}

long AggTableImpl::numTuples()
{
    return aggNodes.size();
}
DbRetVal AggTableImpl::closeScan()
{
    aggNodeIter.reset();
    ListIterator aiter = aggNodes.getIterator();
    char *element;
    while (aiter.hasElement()) {
        element = (char*)aiter.nextElement();
        free(element);
    }
    aggNodes.reset();
    aggNodeMap.removeAll();
    tableHdl->closeScan();
}

DbRetVal AggTableImpl::close()
{
    //free memory allocated. make sure that field buffers are freed only once.
    //for stmts which has more than one agg on same field needs to be handled safely
    closeScan();
    free(groupFld.bindBuf);
    groupFld.bindBuf= NULL;
    ListIterator iter = fldList.getIterator();
    AggFldDef  *elem;
    while (iter.hasElement())
    {
        elem = (AggFldDef*) iter.nextElement();
        if(!elem->alreadyBinded) free(elem->bindBuf);
        delete elem;
    }
    fldList.reset();
    return OK;
}

//------------------------------------------------------
DbRetVal HashMap::insert(void *element)
{
    HashMapNode *newNode = new HashMapNode();
    newNode->elem = element;
    newNode->next = NULL;
    int hashVal = (*(int*) element) % bucketSize;
    //printf("Hash val is %d\n", hashVal);
    HashMapNode *node = (HashMapNode*) bucket[hashVal];
    if (NULL == node)
    {
        bucket[hashVal] = newNode;
        return OK;
    }
    while(node->next != NULL) ;
    node->next = newNode;
    return OK;
}
void* HashMap::find(void *element)
{
    int hashVal = (*(int*) element) % bucketSize;
    //printf("Hash val is %d\n", hashVal);
    if (bucket[hashVal] == NULL)
    {
        return NULL;
    }
    HashMapNode *node = (HashMapNode*) bucket[hashVal];
    while(node != NULL) {
        if ( (*(int*) node->elem) == (*(int*)element)) return node->elem;
        node = node->next;
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
