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
#include<PredicateImpl.h>
static char AggNames[][20] =
{
    "MIN", "MAX", "SUM", "AVG", "COUNT",  ""
};

AggTableImpl::AggTableImpl()
{
    tableHdl = NULL;
    curTuple = NULL;
    havingPred = NULL;
    groupSize = 0;
    aggNodeSize = 0;
    prjNullInfo = 0;
    grpNullInfo = 0;
    grpFldBuffer = NULL;
    optGrpIntNoNull = false;
    grpBindBuf = NULL;
}
AggTableImpl::~AggTableImpl()
{
    //free memory allocated. make sure that field buffers are freed only once.
    //for stmts which has more than one agg on same field needs to be handled safely
    closeScan();
    ListIterator iter = fldList.getIterator();
    AggFldDef  *elem;
    while (iter.hasElement())
    {
        elem = (AggFldDef*) iter.nextElement();
        if(!elem->alreadyBinded) free(elem->bindBuf); 
        delete elem;
    }
    fldList.reset();

    ListIterator giter = fldGroupList.getIterator();
    while (giter.hasElement())
    {
        elem = (AggFldDef*) giter.nextElement();
        if(!elem->alreadyBinded) free(elem->bindBuf);
        delete elem;
    }
    fldGroupList.reset();
    if (tableHdl != NULL) tableHdl->close();
    tableHdl = NULL;
    ::free(grpFldBuffer);
}
void *AggTableImpl::getBindFldAddr(const char *name)
{
    printError(ErrBadCall, "AggTableImpl getBindFldAdddr not implemented\n"); 
    return NULL;
}

DbRetVal AggTableImpl::bindFld(const char *name, void *val, bool dummy)
{
    printError(ErrBadCall, "AggTableImpl bindFld not implemented\n"); 
    return ErrBadCall;
}
DbRetVal AggTableImpl::bindFld(const char *fldname, AggType aggType, void *val)
{
    FieldInfo *info = new FieldInfo();
    DbRetVal rv = tableHdl->getFieldInfo(fldname, info);
    if (OK != rv) { delete info; return rv; }
    AggFldDef *def = new AggFldDef();
    strcpy(def->fldName, fldname);
    def->type = info->type;
    def->length= info->length;
    def->appBuf = val;
    def->aType=aggType;
    def->bindBuf = NULL;
    def->alreadyBinded = false;

    //if underlying tablehandle is TableImpl, then set isNullable
    def->isNullable = true;
    if (info->isNull || info->isPrimary || 
        info->isDefault || info->isAutoIncrement) {
       def->isNullable = false;
    }
    if (NULL == tableHdl->getName()) def->isNullable=true;

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
        rv = tableHdl->bindFld(fldname, def->bindBuf);
        if (OK !=rv) {
           delete info; 
           ::free(def->bindBuf); 
           delete def;  
           return rv; 
        }
    }
    fldList.append(def);
    delete info;
    return OK;
}
DbRetVal AggTableImpl::setGroup(const char *fldname, void *val)
{
    FieldInfo *info = new FieldInfo();
    DbRetVal rv = tableHdl->getFieldInfo(fldname, info);
    if (rv !=OK) { delete info; return rv; }
    AggFldDef *groupFld=new AggFldDef();
    strcpy(groupFld->fldName, fldname);
    groupFld->type = info->type;
    groupFld->length = info->length;
    groupFld->appBuf = val;
    groupFld->bindBuf = NULL;

    groupFld->isNullable = true;
    if (info->isNull || info->isPrimary || 
        info->isDefault || info->isAutoIncrement) {
       groupFld->isNullable = false;
    }
    if (NULL == tableHdl->getName()) groupFld->isNullable=true;

    ListIterator iter = fldList.getIterator();
    AggFldDef  *elem;

    while (iter.hasElement())
    {
        elem = (AggFldDef*) iter.nextElement();
        if (strcmp(elem->fldName, fldname)==0)
        {
            groupFld->bindBuf = elem->bindBuf;
            groupFld->alreadyBinded = true;
            break;
        }
    }
    if (!groupFld->bindBuf)
    {
        groupFld->bindBuf = AllDataType::alloc(groupFld->type, groupFld->length);
        rv = tableHdl->bindFld(fldname, groupFld->bindBuf);
        if (rv !=OK) { 
            delete info;  
            ::free(groupFld->bindBuf);
            delete groupFld;
            return rv; 
        }
    }

    fldGroupList.append(groupFld);
    delete info;
    return OK;
}

bool AggTableImpl::isFldPresentInGrp(char *fname)
{
   ListIterator iter = fldGroupList.getIterator();
   AggFldDef *grpFld=NULL;	
   while (iter.hasElement())
   {
       grpFld=(AggFldDef *)iter.nextElement();
       if(0==strcmp(fname,grpFld->fldName)) return true;
    }
    return false;
}
int AggTableImpl::getAggOffset(char *fname, AggType aggType)
{
   ListIterator iter = fldList.getIterator();
   AggFldDef *projDef=NULL;	
   int offset = groupSize + sizeof(prjNullInfo);
   while (iter.hasElement())
   {
       projDef=(AggFldDef *)iter.nextElement();
       if(0==strcmp(fname, projDef->fldName) && aggType == projDef->aType) 
       {
           return offset;
       }  
       else {
           if (projDef->aType == AGG_AVG) 
               offset = offset + sizeof (double)+ sizeof(int);
           else if (projDef->aType == AGG_COUNT) offset = offset + sizeof(int);
           else offset = offset + projDef->length;
       }
    }
    printError(ErrSysFatal, "Aggregate condition not found in projection list %s", fname);
    return offset;
}

int AggTableImpl::computeGrpNodeSize()
{
   ListIterator iter = fldGroupList.getIterator();
   AggFldDef *grpFld=NULL;
   int totalGrpNodeSize=sizeof(int);
   while (iter.hasElement())
   {
      grpFld=(AggFldDef *)iter.nextElement();
      totalGrpNodeSize=totalGrpNodeSize + grpFld->length;      
   }   
   return totalGrpNodeSize;
}

DbRetVal AggTableImpl::copyValuesFromGrpBindBuf(char *buffer, char *fname)
{
   ListIterator iter = fldGroupList.getIterator();
   AggFldDef *grpFld=NULL;
   while ((grpFld = (AggFldDef*)iter.nextElement()) != NULL)
   {
       //grpFld=(AggFldDef *)iter.nextElement();
       if(0==strcmp(fname,grpFld->fldName)) 
       { 
	    AllDataType::copyVal(buffer, grpFld->bindBuf, grpFld->type, 
                                                               grpFld->length);
            break;
       }
    }
    return OK;
}
DbRetVal AggTableImpl::optimize()
{
   AggFldDef *grpFld=NULL;
   optGrpIntNoNull= false;
   if (groupSize == sizeof(int)+ sizeof(int))
   {
      ListIterator iter = fldGroupList.getIterator();
      grpFld = (AggFldDef*)iter.nextElement();
      if (!grpFld->isNullable && grpFld->type == typeInt) 
      { 
          optGrpIntNoNull=true;   
          grpBindBuf = grpFld->bindBuf;
          aggNodeMap.setGrpIntNoNull();
      }   
   }
   return OK;
}
DbRetVal AggTableImpl::execute()
{
    ListIterator iter = fldList.getIterator();
    AggFldDef  *def;
    aggNodeSize = groupSize = computeGrpNodeSize();
    aggNodeMap.setKeySize(groupSize);
    optimize();

    grpFldBuffer = (char*) ::malloc(groupSize);
    aggNodeSize += sizeof(long long); // for proj field null Info 
    while (iter.hasElement())
    {
        def = (AggFldDef*) iter.nextElement();
        if (def->aType == AGG_AVG) {
            aggNodeSize += sizeof(double);
            aggNodeSize += sizeof(int);//for count 
        } 
        else if (def->aType == AGG_COUNT) aggNodeSize += sizeof(int);
        else aggNodeSize += def->length;
    }
    void *tuple = NULL;
    int offset=0;
    tableHdl->execute();
    aggNodes.reset();
    int groupOffset = groupSize;
    while((tuple = tableHdl->fetch()) != NULL)
    {
        char *buffer = (char*)insertOrGetAggNode();
        iter.reset();
        offset = groupOffset; 
        char *nullInfo = buffer + offset;
        prjNullInfo = *(long long *) nullInfo;
        offset += sizeof(long long);
        int colpos = 1;
        while ((def = (AggFldDef*)iter.nextElement()) != NULL)
        {
           //def = (AggFldDef*) iter.nextElement();
           if (def->isNullable && tableHdl->isFldNull(def->fldName)) {
               if (def->aType == AGG_AVG) 
                   offset = offset + sizeof(double) + sizeof(int);
               else if (def->aType == AGG_COUNT) offset += sizeof(int);
               else offset = offset + def->length;
               colpos++;
               continue;
           }
           bool result=false; bool isNull=false;
           isNull = isFldNull(colpos);
           switch(def->aType)
           { 
               case AGG_MIN: {
                   if (!isNull) {
                       result = AllDataType::compareVal(buffer+offset,
                            def->bindBuf, OpGreaterThanEquals, def->type, 
                                                                  def->length);
                   }
                   if (result || isNull)
                       AllDataType::copyVal(buffer+offset, def->bindBuf,
                                                       def->type, def->length);
                   break;
               }
               case AGG_MAX: {
                   if (!isNull) {
                       result = AllDataType::compareVal(buffer+offset,
                               def->bindBuf, OpLessThanEquals, def->type, 
                                                                  def->length);
                   }
                   if (result || isNull)
                       AllDataType::copyVal(buffer+offset, def->bindBuf,
                                                       def->type, def->length);
                   break;
               }
               case AGG_SUM: {
                   AllDataType::addVal(buffer+offset, def->bindBuf, def->type);
                   break;
               }
               case AGG_AVG: {
                   double tmpBuf=0.0;
                   AllDataType::convertToDouble(&tmpBuf, def->bindBuf, 
                                                                    def->type);
                   AllDataType::addVal(buffer+offset, &tmpBuf, typeDouble);
                   (*(int*)(buffer+offset + sizeof(double)))++;
                   break;
               }
               case AGG_COUNT:
                   (*(int*)(buffer+offset))++;
                   break;
               case AGG_UNKNOWN: 
               {
                   copyValuesFromGrpBindBuf(buffer+offset, def->fldName);
                   break;
               }
           }
           clearFldNull(colpos);
           if (def->aType == AGG_AVG) 
               offset = offset + sizeof(double) + sizeof(int);
           else if (def->aType == AGG_COUNT) offset += sizeof(int);
           else offset = offset + def->length;
           colpos++;
        }
        memcpy(nullInfo, &prjNullInfo, sizeof(long long));
    }
    aggNodeIter  = aggNodes.getIterator();
    iter.reset();
    char *element;
    offset = groupOffset+sizeof(long long);
    while (iter.hasElement()) {
        def = (AggFldDef*) iter.nextElement();
        if(def->aType == AGG_AVG)  {
            aggNodeIter.reset();
            while (aggNodeIter.hasElement()) {
                element = (char*)aggNodeIter.nextElement();
                AllDataType::divVal((double *) (element+offset),
                         *(int *)(element+offset+ sizeof(double)), typeDouble);
            }
            offset = offset + sizeof(double) + sizeof(int);
            continue;
        }
        else if (def->aType == AGG_COUNT) offset += sizeof(int);
        else offset = offset + def->length;
    }
    aggNodeIter.reset();
    tableHdl->closeScan();
    return OK;
}

void* AggTableImpl::getGroupValueBuffer()
{
   memset(grpFldBuffer, 0, groupSize);
   AggFldDef  *def;
   char *offset= (char*)grpFldBuffer;
   if (optGrpIntNoNull) {
       *(int*)offset = *(int*)grpBindBuf;
       return grpFldBuffer;
   }
   grpNullInfo = 0;
   ListIterator giter = fldGroupList.getIterator();
   int colpos = 1;
   while((def = (AggFldDef*) giter.nextElement()) != NULL)
   {
        if (def->isNullable && tableHdl->isFldNull(def->fldName)) markFldNull(colpos); 
        else AllDataType::copyVal(offset, def->bindBuf, def->type, def->length);
        offset = offset + def->length;
        colpos++;
   }
   memcpy(offset, &grpNullInfo, sizeof(int));
   return grpFldBuffer;
}
void* AggTableImpl::insertOrGetAggNode()
{
    char *element;
    if (0 == fldGroupList.size()) {
       ListIterator aiter = aggNodes.getIterator();
       if (aiter.hasElement()) return aiter.nextElement();
    } else {
       void *grpBuffer = getGroupValueBuffer();
       element = (char*) aggNodeMap.find(grpBuffer);
       if (element) return element;
    }

    element = (char*)malloc(aggNodeSize);
    memset(element, 0, aggNodeSize);
    ListIterator iter = fldList.getIterator();
    AggFldDef *def;
    char *offset = element;
    grpNullInfo = 0;
    //offset += sizeof(int);
    ListIterator giter = fldGroupList.getIterator();
    int colpos = 1;
    while(giter.hasElement())
    {
         def = (AggFldDef*) giter.nextElement();
         if(def->isNullable && tableHdl->isFldNull(def->fldName)) 
                                                           markFldNull(colpos);
         else 
             AllDataType::copyVal(offset, def->bindBuf, def->type,def->length);
         offset = offset + def->length;
         colpos++;
    }
    memcpy(offset, &grpNullInfo, sizeof(int));
    offset += sizeof(int);
    memset(offset, 0xff, sizeof(long long));
    offset += sizeof(long long);
    while (iter.hasElement())
    {
         def = (AggFldDef*) iter.nextElement();
         switch(def->aType) {
             case AGG_MIN: 
             case AGG_MAX: 
             { 
                 AllDataType::copyVal(offset, def->bindBuf, def->type, 
                                                                  def->length);
                 break; 
             }
             case AGG_SUM: 
             { 
                 AllDataType::copyZeroVal(offset, def->type, def->length);
                 break; 
             }
             case AGG_AVG: {
                 *(double*)(offset)=0;
                 *(int*)(offset+ sizeof(double))=0; //count
                 break;
             }
             case AGG_COUNT: { *(int*)(offset)=0; break; }
         }
         if (def->aType == AGG_AVG)
             offset = offset + sizeof(double) + sizeof(int);
         else if (def->aType == AGG_COUNT) offset += sizeof(int);
         else offset = offset + def->length;
    }
    aggNodes.append(element);
    aggNodeMap.insert(element);
    return element;
}

void* AggTableImpl::fetch()
{
    while(aggNodeIter.hasElement())
    {
        void *elem = aggNodeIter.nextElement();
        bool result=false;
        if (havingPred) {
            PredicateImpl *pImpl = (PredicateImpl*)havingPred;
            pImpl->evaluateForHaving(result , this, elem);
            if (!result) continue;
        }
        copyValuesToBindBuffer(elem);
        return elem;
    }
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
    char *colPtr=element+groupSize;
    prjNullInfo = *(long long *) colPtr;
    colPtr += sizeof(long long);
    int colpos = 1;
    while (fIter.hasElement())
    {
        def = (AggFldDef*) fIter.nextElement();
        if (isFldNull(colpos)) {
            if (def->aType == AGG_AVG) 
                colPtr += sizeof(double) + sizeof(int);
            else if (def->aType == AGG_COUNT) colPtr += sizeof(int);
            else colPtr += def->length;
            colpos++;
            continue;
        }    
        if (NULL != def->appBuf) {
            if (def->aType == AGG_AVG) {
                 os::memcpy(def->appBuf, colPtr, sizeof(double));
                 colPtr = colPtr + sizeof(double) + sizeof(int);
            } 
            else if (def->aType == AGG_COUNT) {
                AllDataType::copyVal(def->appBuf, colPtr, typeInt, sizeof(int));
                colPtr += sizeof(int);
            }   
            else {
                 AllDataType::copyVal(def->appBuf, colPtr, def->type, 
                                                                  def->length);
                 colPtr = colPtr + def->length;
            }
        }
        colpos++;
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
    if (tableHdl) tableHdl->closeScan();
    return OK;
}

DbRetVal AggTableImpl::close()
{
    havingPred = NULL;
    delete this;
    return OK;
}

bool AggTableImpl::isFldNull(const char *name)
{
    ListIterator it = fldList.getIterator();
    int colpos = 1;
    char fldName[IDENTIFIER_LENGTH];
    AggType atp = getAggType(name, fldName);
    while (it.hasElement()) {
        AggFldDef *def = (AggFldDef *) it.nextElement();
        if (!def->isNullable) return false;
        if (atp != AGG_UNKNOWN) {
            if (strcmp(def->fldName, fldName)==0 && def->aType == atp) break;
        } 
        else if (strcmp(def->fldName, name)==0) break;
        colpos++;
    }
    return isFldNull(colpos);
}
void AggTableImpl::printPlan(int space)
{
    char spaceBuf[IDENTIFIER_LENGTH];
    memset(spaceBuf, 32, IDENTIFIER_LENGTH);
    spaceBuf[space] = '\0';
    PredicateImpl* predImpl = (PredicateImpl*) havingPred;
    printf("%s <AGG-NODE>\n", spaceBuf);
    printf("%s <PROJECTION>\n", spaceBuf);
    AggFldDef *fldDef=NULL;
    ListIterator iter = fldList.getIterator();
    while ((fldDef = (AggFldDef*)iter.nextElement()) != NULL)
    {
       if (fldDef->aType == AGG_UNKNOWN) 
          printf("%s   <FieldName> %s </FieldName>\n", spaceBuf, 
                                  fldDef->fldName);
       else
          printf("%s   <FieldName> %s(%s) </FieldName>\n", spaceBuf, 
                                  AggNames[fldDef->aType -1], fldDef->fldName);
    }
    printf("%s </PROJECTION>\n", spaceBuf);
    printf("%s <GROUPING>\n", spaceBuf);
    ListIterator giter = fldGroupList.getIterator();
    while ((fldDef = (AggFldDef*)giter.nextElement()) != NULL)
    {
       printf("%s   <FieldName> %s </FieldName>\n", spaceBuf, fldDef->fldName);
    }
    printf("%s </GROUPING>\n", spaceBuf);
    if (havingPred) predImpl->print(space);
    printf("%s </AGG-NODE>\n", spaceBuf);
    if (tableHdl) tableHdl->printPlan(space+2);
    return;
}

AggType AggTableImpl::getAggType(const char *name, char *fldName) 
{
    char *ptr = (char *)name;
    AggType atp = AGG_UNKNOWN;
    if (strncmp(name, "COUNT", 5) == 0) {
        ptr += strlen("COUNT(");
        atp = AGG_COUNT;
    } else if (strncmp(name, "MIN", 3) == 0) {
        ptr += strlen("MIN(");
        atp = AGG_MIN;
    } else if (strncmp(name, "MAX", 3) == 0) { 
        ptr += strlen("MAX(");
        atp = AGG_MAX;
    } else if (strncmp(name, "SUM", 3) == 0) { 
        ptr += strlen("SUM(");
        atp = AGG_SUM;
    } else if (strncmp(name, "AVG", 3) == 0) { 
        ptr += strlen("AVG(");
        atp = AGG_AVG;
    }     
    if (atp == AGG_UNKNOWN) return atp; 
    strcpy(fldName, ptr);
    ptr = fldName;
    while (*ptr != ')') ptr++;
    *ptr = '\0';
    return atp;
}
