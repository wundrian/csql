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
#include<OrderTableImpl.h>
#include<PredicateImpl.h>
#include<Parser.h>
OrderTableImpl::OrderTableImpl()
{
    tableHdl = NULL;
    curTuple = NULL;
    sortTree.setDistinct(false);
    nullValues = 0;
    orderBySize =0;
    projSize =0;
    orderBindBuf= NULL;
    orderBuffer = NULL;
    isPlanCreated=false;
}

OrderTableImpl::~OrderTableImpl()
{
    //free memory allocated. make sure that field buffers are freed only once.
    //for stmts which has more than one agg on same field needs to be handled safely
    closeScan();

    ListIterator oiter = fldOrderByList.getIterator();
    OrderByFldDef *elem = NULL;
    while (oiter.hasElement())
    {
        elem = (OrderByFldDef*) oiter.nextElement();
        if(!elem->alreadyBinded) free(elem->bindBuf);
        delete elem;
    }
    fldOrderByList.reset();

    if (tableHdl != NULL) tableHdl->close();
    tableHdl = NULL;
    if (orderBuffer) ::free(orderBuffer);
}

void *OrderTableImpl::getBindFldAddr(const char *name)
{
    printError(ErrBadCall, "OrderTableImpl getBindFldAdddr not implemented\n"); 
    return NULL;
}

DbRetVal OrderTableImpl::bindFld(const char *name, void *val, bool dummy)
{
    printError(ErrBadCall, "OrderTableImpl bindFld not implemented\n"); 
    return ErrBadCall;
}

DbRetVal OrderTableImpl::setOrderBy(const char *fldname, bool isDesc)
{
    FieldInfo *info = new FieldInfo();
    DbRetVal rv = tableHdl->getFieldInfo(fldname, info);
    if (OK !=rv) { delete info; return rv; }
    OrderByFldDef *orderFld=new OrderByFldDef();
    strcpy(orderFld->fldName, fldname);
    orderFld->type = info->type;
    //orderFld->length = info->length;
    orderFld->length = AllDataType::size(info->type, info->length);
    orderFld->bindBuf = NULL;
    orderFld->isDesc = isDesc;

    ListIterator iter = fldProjList.getIterator();
    FieldValue  *elem;

    while (iter.hasElement())
    {
        elem = (FieldValue*) iter.nextElement();
        if ((NULL != tableHdl->getName() && 
             NULL != strstr(elem->fldName, fldname) || 
             NULL != strstr(fldname, elem->fldName)) || 
             strcmp(elem->fldName, fldname)==0)
        {
            orderFld->bindBuf = elem->value;
            orderFld->alreadyBinded = true;
            break;
        }
    }
    if (!orderFld->bindBuf)
    {
        orderFld->bindBuf = AllDataType::alloc(orderFld->type, orderFld->length);
        rv = tableHdl->bindFld(fldname, orderFld->bindBuf);
        if (rv != OK) {
            delete info;
            ::free(orderFld->bindBuf);
            delete orderFld;
            return rv;
        }
    }

    //if underlying tablehandle is TableImpl, then set isNull
    orderFld->isNull = true;
    if (info->isNull) orderFld->isNull = false;
    if (info->isPrimary || info->isDefault || info->isAutoIncrement) {
        orderFld->isNull = true;
    }
    if (NULL == tableHdl->getName()) orderFld->isNull=false;
    

    fldOrderByList.append(orderFld);
    delete info;
    return OK;
}

OrderByType OrderTableImpl::getOrderType()
{
    ListIterator oiter = fldOrderByList.getIterator();
    OrderByFldDef *oFldDef = NULL;
    bool isDescending = false;
    bool firstIter = true;
    while (oiter.hasElement())
    {
        oFldDef = (OrderByFldDef*) oiter.nextElement();
        if(firstIter) { 
            firstIter= false; 
            isDescending = oFldDef->isDesc; 
            continue; 
        }
        if (oFldDef->isDesc != isDescending) { isDescending = false; break; }
    }
    if(isDescending) return Desc; else return Asc; 
}

void OrderTableImpl::checkAndSetSortAlgorithm()
{
    if (sortTree.getDistinct()) sortTree.setFullOrderBy();
    sortTree.setOrderByList(fldOrderByList);

    //set orderby size
    orderBySize = computeOrderBySize();
    sortTree.setKeySize(orderBySize + sizeof(int));
    
    //set proj size
    projSize = 0;
    ListIterator iter = fldProjList.getIterator();
    FieldValue  *fValue;
    while (iter.hasElement())
    {
        fValue = (FieldValue*) iter.nextElement();
        projSize = projSize + fValue->length;
    }
    OrderByFldDef *ordFld=NULL;
    bool optGrpIntNoNull= false;
    if (orderBySize == sizeof(int))
    {
       ListIterator iter = fldOrderByList.getIterator();
       ordFld = (OrderByFldDef*)iter.nextElement();
       if (!ordFld->isNull && ordFld->type == typeInt)
       {
           optGrpIntNoNull=true;
           orderBindBuf = ordFld->bindBuf;
           sortTree.setOrdIntNoNull();
       }
    }
    return;
}

DbRetVal OrderTableImpl::execute()
{
    nullValues = 0;
    tableHdl->execute();
    if (!isPlanCreated) {
        checkAndSetSortAlgorithm();
        setNullableForProj();
        if (sortTree.getDistinct())
        {
            orderBuffer = (char*)malloc(orderBySize + sizeof(int));
        }
        isPlanCreated=true;
    }
    void *tuple = NULL;
    while ((tuple = tableHdl->fetch()) != NULL)
    {
       if (sortTree.getDistinct()) insertDistinct(); else insert();
    }
    sortIter = sortTree.getListIterator();
    return OK;
}

int OrderTableImpl::computeOrderBySize()
{
    ListIterator oiter = fldOrderByList.getIterator();
    OrderByFldDef *oFldDef = NULL;
    int nodeOffset =0;
    while (oiter.hasElement())
    {
        oFldDef = (OrderByFldDef*) oiter.nextElement();
        nodeOffset = nodeOffset + oFldDef->length;
    }
    return nodeOffset;
}

DbRetVal OrderTableImpl::insertDistinct()
{
    char *elem = orderBuffer;
    memset(orderBuffer, 0, orderBySize + sizeof(int));
    ListIterator oiter = fldOrderByList.getIterator();
    OrderByFldDef *oFldDef = NULL;
    int orderNullValues =0;
    int nodeOffset =0;
    int i=0;
    while ((oFldDef = (OrderByFldDef*) oiter.nextElement()) != NULL)
    {
        if (oFldDef->isNull && tableHdl->isFldNull(oFldDef->fldName))
            SETBIT(orderNullValues, i);
        else
            AllDataType::copyVal(elem+nodeOffset, oFldDef->bindBuf,
                                 oFldDef->type, oFldDef->length);
        nodeOffset = nodeOffset + oFldDef->length;
        i++;
    }
    AllDataType::copyVal(elem+nodeOffset, &orderNullValues, typeInt,
                                             sizeof(orderNullValues));
    if (sortTree.find(elem)) return OK;
    nodeOffset = nodeOffset+ sizeof(orderNullValues);

    int nodeSize = orderBySize + projSize;
    nodeSize = nodeSize + sizeof(int);//to store order by field null values
    nodeSize = nodeSize + sizeof(nullValues);//to store proj field null values
    char *element = (char*)malloc(nodeSize);
    memcpy(element, elem, orderBySize + sizeof(int));
    nullValues = 0;
    i=0;
    ListIterator iter = fldProjList.getIterator();
    FieldValue  *fValue = NULL;
    void* ptrToCopyNullValues = element+nodeOffset;
    nodeOffset = nodeOffset + sizeof(nullValues);
    while ((fValue = (FieldValue*) iter.nextElement()) != NULL)
    {
        if (fValue->isNullable && tableHdl->isFldNull(fValue->fldName))
            SETBIT(nullValues, i);
        else
            AllDataType::copyVal(element+nodeOffset, fValue->value,
                                        fValue->type, fValue->length);
        nodeOffset = nodeOffset + fValue->length;
        i++;
    }
    AllDataType::copyVal(ptrToCopyNullValues, &nullValues, typeLongLong,
                                    sizeof(nullValues));
    DbRetVal rv = sortTree.insertDataNode(element);
    return rv;
}

DbRetVal OrderTableImpl::insert()
{
    //compute size of projection
    int nodeSize = orderBySize + projSize;
    nodeSize = nodeSize + sizeof(int);//to store order by field null values
    nodeSize = nodeSize + sizeof(nullValues);//to store proj field null values
    char *element = (char*)malloc(nodeSize);
    //copy values
    int nodeOffset =0;
    ListIterator oiter = fldOrderByList.getIterator();
    OrderByFldDef *oFldDef = NULL;
    int orderNullValues =0;
    int i=0;
    while ((oFldDef = (OrderByFldDef*) oiter.nextElement()) != NULL)
    {
        //oFldDef = (OrderByFldDef*) oiter.nextElement();
        if (oFldDef->isNull && tableHdl->isFldNull(oFldDef->fldName)) 
            SETBIT(orderNullValues, i);
        else 
            AllDataType::copyVal(element+nodeOffset, oFldDef->bindBuf, 
                                 oFldDef->type, oFldDef->length);
        nodeOffset = nodeOffset + oFldDef->length;
        i++;
    }
    AllDataType::copyVal(element+nodeOffset, &orderNullValues, typeInt, 
                                             sizeof(orderNullValues));
    nodeOffset = nodeOffset+ sizeof(orderNullValues);
    nullValues = 0;
    i=0;
    ListIterator iter = fldProjList.getIterator();
    FieldValue  *fValue = NULL;
    void* ptrToCopyNullValues = element+nodeOffset;
    nodeOffset = nodeOffset + sizeof(nullValues);
    while ((fValue = (FieldValue*) iter.nextElement()) != NULL)
    {
        //fValue = (FieldValue*) iter.nextElement();
        if (fValue->isNullable && tableHdl->isFldNull(fValue->fldName)) 
            SETBIT(nullValues, i);
        else
            AllDataType::copyVal(element+nodeOffset, fValue->value, 
                                        fValue->type, fValue->length);
        nodeOffset = nodeOffset + fValue->length;
        i++;
    }
    AllDataType::copyVal(ptrToCopyNullValues, &nullValues, typeLongLong,
                                    sizeof(nullValues));
    DbRetVal rv = sortTree.insertDataNode(element);
    if (rv == ErrUnique) ::free (element);
    return OK;
}

void* OrderTableImpl::fetch()
{
    void *elem = sortIter.nextElement();
    if (NULL == elem) return NULL;
    copyValuesToBindBuffer(elem);
    return elem;

}

void* OrderTableImpl::fetch(DbRetVal &rv)
{
    rv = OK;
    return fetch();
}

void* OrderTableImpl::fetchNoBind()
{
    void *elem = sortIter.nextElement();
    if (NULL == elem) return NULL;
    copyValuesToBindBuffer(elem);
    return elem;
}

void* OrderTableImpl::fetchNoBind(DbRetVal &rv)
{
    rv = OK;
    return fetchNoBind();
}

DbRetVal OrderTableImpl::setOrderByList(List oList)
{
    ListIterator fIter = oList.getIterator();
    FieldValue  *def;
    while (fIter.hasElement())
    {
        def = (FieldValue*) fIter.nextElement();
        setOrderBy(def->fldName);
    }
    return OK;
}

DbRetVal OrderTableImpl::copyValuesToBindBuffer(void *elem)
{
    //Iterate through the bind list and copy the value here
    ListIterator fIter = fldProjList.getIterator();
    FieldValue  *def;
    char *colPtr= (char*) elem + orderBySize;
    colPtr = colPtr + sizeof(int);
    nullValues = *(long long*) colPtr;
    colPtr = colPtr + sizeof (nullValues);
    while (fIter.hasElement())
    {
        def = (FieldValue*) fIter.nextElement();
        if (NULL != def->value) {
             AllDataType::copyVal(def->value, colPtr, def->type, def->length);
             colPtr = colPtr + def->length;
        }
    }
    return OK;
}

void OrderTableImpl::setNullableForProj()
{
    ListIterator fIter = fldProjList.getIterator();
    FieldValue  *def;
    FieldInfo *info = new FieldInfo();
    while (fIter.hasElement())
    {
        def = (FieldValue*) fIter.nextElement();
        tableHdl->getFieldInfo(def->fldName, info);
        def->isNullable = true;
        if (info->isNull || info->isPrimary || 
            info->isDefault || info->isAutoIncrement) {
            def->isNullable = false;
        }
        if (NULL == tableHdl->getName()) def->isNullable=true;
    }
    delete info;
    return;
}

bool OrderTableImpl::isFldNull(const char *fldName)
{
    int pos = 0;
    ListIterator fIter = fldProjList.getIterator();
    FieldValue  *def;
    while (fIter.hasElement())
    {
        def = (FieldValue*) fIter.nextElement();
        if (strcmp(fldName, def->fldName) == 0) {
            break;
        }
        pos++;
    }
    return isFldNull(pos);
}

bool OrderTableImpl::isFldNull(int projPos)
{
    if (BITSET(nullValues, projPos)) return true;
    return false;
}

long OrderTableImpl::numTuples()
{
    return tableHdl->numTuples();
}

DbRetVal OrderTableImpl::closeScan()
{
    sortIter.reset();
    ListIterator iter = sortTree.getListIterator();
    void *elem= NULL;
    while(iter.hasElement()) {
        elem = iter.nextElement();
        free(elem);
    }
    sortTree.removeAll();   
    if (tableHdl) tableHdl->closeScan();
    return OK;
}

DbRetVal OrderTableImpl::close()
{
    nullValues = 0;
    closeScan();
    delete this;
    return OK;
}

void OrderTableImpl::printPlan(int space)
{
    char spaceBuf[IDENTIFIER_LENGTH];
    memset(spaceBuf, 32, IDENTIFIER_LENGTH);
    spaceBuf[space] = '\0';
    printf("%s <SORT-NODE>\n", spaceBuf);
    printf("%s <ORDER-BY>\n", spaceBuf);
    ListIterator giter = fldOrderByList.getIterator();
    OrderByFldDef *fldDef=NULL;
    while ((fldDef = (OrderByFldDef*)giter.nextElement()) != NULL)
    {
       if (fldDef->isDesc) \
           printf("%s   <FieldName> %s DESC </FieldName>\n", spaceBuf, 
                                                     fldDef->fldName);
       else 
           printf("%s   <FieldName> %s ASC </FieldName>\n", spaceBuf,
                                                     fldDef->fldName);
    }
    printf("%s </ORDER-BY>\n", spaceBuf);
    if (sortTree.getDistinct())
       printf("%s <DISTINCT> true </DISTINCT>\n", spaceBuf);
    printf("%s </SORT-NODE>\n", spaceBuf);
    if (tableHdl) tableHdl->printPlan(space+2);
    return;
}

