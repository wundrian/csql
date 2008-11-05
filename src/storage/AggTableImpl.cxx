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
}
void *AggTableImpl::getBindFldAddr(const char *name)
{
	return NULL;
}



DbRetVal AggTableImpl::bindFld(const char *name, void *val)
{
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
        aggNodeSize = AllDataType::size(groupFld.type, groupFld.length);
    else
        aggNodeSize = 0;
    while (iter.hasElement())
    {
         def = (AggFldDef*) iter.nextElement();
         aggNodeSize = aggNodeSize + AllDataType::size(def->type, def->length);
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
            offset = AllDataType::size(groupFld.type, groupFld.length);
        else
            offset = 0;
        while (iter.hasElement())
        {
           def = (AggFldDef*) iter.nextElement();
           switch(def->atype)
           {
               case AGG_MIN: {
                   bool result = AllDataType::compareVal(buffer+offset,
                                 def->bindBuf, OpGreaterThan, def->type, def->length);
                   if (result)
                       AllDataType::copyVal(buffer+offset, def->bindBuf,
                                            def->type, def->length);
                   break;
               }
               case AGG_MAX: {
                   bool result = AllDataType::compareVal(buffer+offset,
                                        def->bindBuf, OpLessThan, def->type, def->length);
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
                   (*(int*)(buffer+offset + AllDataType::size(def->type, def->length)))++;
                   offset = offset +sizeof(int); //->count
                   break;
               }
               case AGG_COUNT:
                   (*(int*)(buffer+offset))++;
                   break;
           }
           offset = offset + AllDataType::size(def->type, def->length);
        }
    }
    aggNodeIter  = aggNodes.getIterator();
    iter.reset();
    char *element;
    while (iter.hasElement()) {
        def = (AggFldDef*) iter.nextElement();
        if (isGroupSet())
            offset = AllDataType::size(groupFld.type, groupFld.length);
        else
            offset = 0;
        switch(def->atype)
        {
            case AGG_AVG: {
               while (aggNodeIter.hasElement()) {
                   element = (char*)aggNodeIter.nextElement();
                   AllDataType::divVal(element+offset,
                      *(int*)(element+offset+AllDataType::size(def->type, def->length)),
                      def->type);
               }
               offset = offset +sizeof(int);
            }
        }
        offset = offset + AllDataType::size(def->type, def->length);
    }
    aggNodeIter.reset();
    tableHdl->close();
    return OK;
}
void* AggTableImpl::insertOrGet()
{
    ListIterator aiter = aggNodes.getIterator();
    char *element;
    while (aiter.hasElement()) {
        element = (char*)aiter.nextElement();

        if (!isGroupSet()) return element;
        if (AllDataType::compareVal(element, groupFld.bindBuf, OpEquals,
                                             groupFld.type, groupFld.length))
        {
            return element;
        }
    }
    element = (char*)malloc(aggNodeSize);
    ListIterator iter = fldList.getIterator();
    AggFldDef  *def;
    char *offset;
    if (isGroupSet()) {
        AllDataType::copyVal(element, groupFld.bindBuf, groupFld.type,
                                                 groupFld.length);
        offset = element + AllDataType::size(groupFld.type, groupFld.length);
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
                 *(int*)(offset+AllDataType::size(def->type, def->length))=0; //count
                 offset = offset+ sizeof(int);
                 break;
             }
             case AGG_COUNT: { *(int*)(offset)=0; break; }
         }
         offset = offset + AllDataType::size(def->type, def->length);
    }
    aggNodes.append(element);
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
    char *colPtr = (char*) elem + AllDataType::size(groupFld.type, groupFld.length);
    while (fIter.hasElement())
    {
        def = (AggFldDef*) fIter.nextElement();
        if (NULL != def->appBuf) {
            AllDataType::copyVal(def->appBuf, colPtr, def->type, def->length);
        }
        colPtr = colPtr + os::align(AllDataType::size(def->type, def->length));
        if(def->atype == AGG_AVG) colPtr = colPtr + sizeof(int);
    }
    return OK;
}

long AggTableImpl::numTuples()
{
    return aggNodes.size();
}
void AggTableImpl::closeScan()
{
    aggNodeIter.reset();
    ListIterator aiter = aggNodes.getIterator();
    char *element;
    while (aiter.hasElement()) {
        element = (char*)aiter.nextElement();
        free(element);
    }
    aggNodes.reset();
}

DbRetVal AggTableImpl::close()
{
    //free memory allocated. make sure that field buffers are freed only once.
    //for stmts which has more than one agg on same field needs to be handled safely
    free(groupFld.bindBuf);
    ListIterator iter = fldList.getIterator();
    AggFldDef  *elem;
    while (iter.hasElement())
    {
        elem = (AggFldDef*) iter.nextElement();
        if(!elem->alreadyBinded) free(elem->bindBuf);
    }
    fldList.reset();
    return OK;
}
