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
                   offset = offset +sizeof(int);
               }
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







//-----------------------------------------------------------

JoinTableImpl::JoinTableImpl()
{
    isNestedLoop= true;
}
JoinTableImpl::~JoinTableImpl()
{
}
void JoinTableImpl::getFieldNameAlone(char *fname, char *name) {
    bool dotFound= false;
    char *fullname = fname;
    while(*fullname != '\0')
    {
        if (*fullname == '.') { dotFound = true;  break; }
        fullname++;
    }
    if (dotFound) strcpy(name, ++fullname); else strcpy(name, fname);

}
void JoinTableImpl::getTableNameAlone(char *fname, char *name) {
    strcpy(name, fname);
    while(*name != '\0')
    {
        if (*name == '.') { *name='\0';  break; }
        name++;
    }
    return;
}
DbRetVal JoinTableImpl::bindFld(const char *fldname, void *val)
{
    FieldInfo *info = new FieldInfo();
    char tableName[IDENTIFIER_LENGTH];
    char fieldName[IDENTIFIER_LENGTH];
    getTableNameAlone((char*)fldname, tableName);
    getFieldNameAlone((char*)fldname, fieldName);
    printf("%s %s \n", tableName, fieldName);

    ListIterator iter = projList.getIterator();
    JoinProjFieldInfo  *elem;
    while (iter.hasElement())
    {
        elem = (JoinProjFieldInfo*) iter.nextElement();   
        if (strcmp(elem->fieldName, fieldName)==0 &&
            strcmp(elem->tableName, tableName) ==0) 
        {
            printError(ErrBadCall, "Field already binded %s\n", fldname);
            delete info;
            return ErrBadCall;
        }
    }
    JoinProjFieldInfo *def = new JoinProjFieldInfo();
    strcpy(def->tableName, tableName);
    strcpy(def->fieldName, fieldName);
    def->appBuf = val;
    def->bindBuf = AllDataType::alloc(def->type, def->length);

    if (strcmp(tableName, leftTableHdl->getName()) == 0)
    {
        leftTableHdl->getFieldInfo(fieldName, info);
        def->bindBuf = AllDataType::alloc(info->type, info->length);
        leftTableHdl->bindFld(fieldName, def->bindBuf);
        
    }else if (strcmp(tableName, rightTableHdl->getName()) == 0)
    {
        rightTableHdl->getFieldInfo(fieldName, info);
        def->bindBuf = AllDataType::alloc(info->type, info->length);
        rightTableHdl->bindFld(fieldName, def->bindBuf);
    }else
    {
        printError(ErrBadCall, "TableName is invalid\n");
        delete info;
        return ErrBadCall;
    }
    def->type = info->type;
    def->length= info->length;
    projList.append(def);
    delete info;
    return OK;
}
DbRetVal JoinTableImpl::setJoinCondition(const char *fldname1, 
                                         ComparisionOp op,
                                         const char *fldname2)
{
    getTableNameAlone((char*)fldname1, jCondition.tableName1);
    getFieldNameAlone((char*)fldname1, jCondition.fieldName1);
    getTableNameAlone((char*)fldname2, jCondition.tableName2);
    getFieldNameAlone((char*)fldname2, jCondition.fieldName2);

    //check if it is already binded
    ListIterator iter = projList.getIterator();
    JoinProjFieldInfo  *elem;
    jCondition.alreadyBinded1 = false;
    jCondition.alreadyBinded2 = false;
    jCondition.op = op;
    while (iter.hasElement())
    {
        elem = (JoinProjFieldInfo*) iter.nextElement();   
        if (strcmp(elem->fieldName, jCondition.fieldName1)==0 &&
            strcmp(elem->tableName, jCondition.tableName1) ==0) 
        {
            jCondition.alreadyBinded1 = true;
            jCondition.bindBuf1 = elem->bindBuf;
            jCondition.type1 = elem->type;
            jCondition.length1 = elem->length;
        }
        if (strcmp(elem->fieldName, jCondition.fieldName2)==0 &&
            strcmp(elem->tableName, jCondition.tableName2) ==0) 
        {
            jCondition.alreadyBinded2 = true;
            jCondition.bindBuf2 = elem->bindBuf;
            jCondition.type2 = elem->type;
            jCondition.length2 = elem->length;
        }
    }
    
    FieldInfo *info = new FieldInfo();
    if (!jCondition.alreadyBinded1) {
      if (strcmp(jCondition.tableName1, leftTableHdl->getName()) == 0)
      {
        leftTableHdl->getFieldInfo(jCondition.fieldName1, info);
        jCondition.bindBuf1 = AllDataType::alloc(info->type, info->length);
        leftTableHdl->bindFld(jCondition.fieldName1, jCondition.bindBuf1);
        
      }else if (strcmp(jCondition.tableName1, rightTableHdl->getName()) == 0)
      {
        rightTableHdl->getFieldInfo(jCondition.fieldName1, info);
        jCondition.bindBuf1 = AllDataType::alloc(info->type, info->length);
        rightTableHdl->bindFld(jCondition.fieldName1, jCondition.bindBuf1);
      }else
      {
        printError(ErrBadCall, "TableName is invalid\n");
        delete info;
        return ErrBadCall;
      }
    }
    if (!jCondition.alreadyBinded2) {
      if (strcmp(jCondition.tableName2, leftTableHdl->getName()) == 0)
      {
        leftTableHdl->getFieldInfo(jCondition.fieldName2, info);
        jCondition.bindBuf2 = AllDataType::alloc(info->type, info->length);
        leftTableHdl->bindFld(jCondition.fieldName2, jCondition.bindBuf2);
        
      }else if (strcmp(jCondition.tableName2, rightTableHdl->getName()) == 0)
      {
        rightTableHdl->getFieldInfo(jCondition.fieldName2, info);
        jCondition.bindBuf2 = AllDataType::alloc(info->type, info->length);
        rightTableHdl->bindFld(jCondition.fieldName2, jCondition.bindBuf2);
      }else
      {
        printError(ErrBadCall, "TableName is invalid\n");
        delete info;
        return ErrBadCall;
      }
    }
    return OK;
}


DbRetVal JoinTableImpl::execute()
{
    isNestedLoop = true;
    leftTableHdl->execute();
    rightTableHdl->execute();
    leftTableHdl->fetch();
    //TODO
    //if join condition is not set then do nl
    //if it is inner join, hen do nl
    //nl cannot be done for outer join
    return OK;
}

void* JoinTableImpl::fetch()
{
    if (isNestedLoop)
    {
        void *rec = rightTableHdl->fetch();
        if (rec==NULL)
        {
            rightTableHdl->close();
            rightTableHdl->execute();
            rec = rightTableHdl->fetch();
            if (rec == NULL) return NULL;
            rec = leftTableHdl->fetch();
            if (rec == NULL) return NULL;
            bool result = evaluate();
            if (! result) return fetch();
            copyValuesToBindBuffer(NULL);
            return rec;
        }
        else {
            bool result = evaluate();
            if (! result) return fetch();
            copyValuesToBindBuffer(NULL);
            return rec;
        }
        
    }
    return NULL;
}
bool JoinTableImpl::evaluate()
{
    if (!jCondition.bindBuf1 || !jCondition.bindBuf2) return true;
    return AllDataType::compareVal(jCondition.bindBuf1, jCondition.bindBuf2, 
                                   jCondition.op,  
                                   jCondition.type1, jCondition.length1);
}
void* JoinTableImpl::fetch(DbRetVal &rv)
{
    rv = OK; 
    return fetch();
}

void* JoinTableImpl::fetchNoBind()
{
    return NULL;
}

void* JoinTableImpl::fetchNoBind(DbRetVal &rv)
{
    rv = OK;
    return fetchNoBind();
}

DbRetVal JoinTableImpl::copyValuesToBindBuffer(void *elem)
{
    //Iterate through the bind list and copy the value here
    ListIterator fIter = projList.getIterator();
    JoinProjFieldInfo  *def;
    while (fIter.hasElement())
    {
        def = (JoinProjFieldInfo*) fIter.nextElement();
        if (NULL != def->appBuf) {
            AllDataType::copyVal(def->appBuf, def->bindBuf, def->type, def->length);
        }
    }
    return OK;
}

long JoinTableImpl::numTuples()
{
    return 0;
}
void JoinTableImpl::closeScan()
{
}
DbRetVal JoinTableImpl::close()
{
    return OK;
}
