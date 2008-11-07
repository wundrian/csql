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

JoinTableImpl::JoinTableImpl()
{
    isNestedLoop= true;
    pred = NULL;
    curTuple = NULL;
    leftTableHdl = NULL;
    rightTableHdl = NULL;
}
JoinTableImpl::~JoinTableImpl()
{
}
/* moved to Table class
 * shall be removed
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
*/
DbRetVal JoinTableImpl::bindFld(const char *fldname, void *val)
{
    FieldInfo *info = new FieldInfo();
    char tableName[IDENTIFIER_LENGTH];
    char fieldName[IDENTIFIER_LENGTH];
    getTableNameAlone((char*)fldname, tableName);
    getFieldNameAlone((char*)fldname, fieldName);
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
    strcpy(def->tabFieldName, fldname);
    def->appBuf = val;
    getFieldInfo(fldname, info);
    def->bindBuf = AllDataType::alloc(info->type, info->length);
    if (availableLeft)
        leftTableHdl->bindFld(fldname, def->bindBuf);
    else 
        rightTableHdl->bindFld(fldname, def->bindBuf);
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
    PredicateImpl* predImpl = (PredicateImpl*) pred;
    isNestedLoop = true;
    leftTableHdl->execute();
    rightTableHdl->execute();
    if (pred) predImpl->setProjectionList(&projList);
    leftTableHdl->fetch();
    //TODO
    //if join condition is not set then do nl
    //if it is inner join, hen do nl
    //nl cannot be done for outer join
    return OK;
}

void* JoinTableImpl::fetch()
{
    PredicateImpl* predImpl = (PredicateImpl*) pred;
    DbRetVal rv = OK;
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
            if (pred) rv = predImpl->evaluate(result);
            if ( rv !=OK) return NULL; 
            if (!result) return fetch();
            copyValuesToBindBuffer(NULL);
            return rec;
        }
        else {
            bool result = evaluate();
            if (! result) return fetch();
            if (pred) rv = predImpl->evaluate(result);
            if ( rv !=OK) return NULL; 
            if (!result) return fetch();
            copyValuesToBindBuffer(NULL);
            return rec;
        }
        
    }
    return NULL;
}
bool JoinTableImpl::evaluate()
{
    if (!jCondition.bindBuf1 || !jCondition.bindBuf2) return true;
    bool res = AllDataType::compareVal(jCondition.bindBuf1, 
                                   jCondition.bindBuf2, 
                                   jCondition.op,  
                                   jCondition.type1, jCondition.length1);
    return res;
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
DbRetVal JoinTableImpl::getFieldInfo(const char* fldname, FieldInfo *&info)
{
    DbRetVal retCode = OK;
    retCode = leftTableHdl->getFieldInfo(fldname, info);
    if (retCode ==OK)
    {
        availableLeft= true;
        return OK;
    }
    retCode = rightTableHdl->getFieldInfo(fldname, info);
    if (retCode ==OK)
    {
        availableLeft= false;
        return OK;
    }
    return ErrNotExists;
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
    leftTableHdl->close();
    rightTableHdl->close();
    return OK;
}
void* JoinTableImpl::getBindFldAddr(const char *name)
{
    return NULL;
}
List JoinTableImpl::getFieldNameList()
{
    List fldNameList;

    List leftList = leftTableHdl->getFieldNameList();
    ListIterator lIter = leftList.getIterator();
    while (lIter.hasElement())
    {
        Identifier *elem = (Identifier*) lIter.nextElement();
        fldNameList.append(elem);
    }

    List rightList = rightTableHdl->getFieldNameList();
    ListIterator rIter = rightList.getIterator();
    while (rIter.hasElement())
    {
        Identifier *elem = (Identifier*) rIter.nextElement();
        fldNameList.append(elem);
    }
    return fldNameList;
}
