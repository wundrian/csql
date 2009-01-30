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
#include<JoinTableImpl.h>
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
    close();
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

DbRetVal JoinTableImpl::optimize()
{
    PredicateImpl* predImpl = (PredicateImpl*) pred;
    if (NULL != predImpl && !predImpl->isNotOrInvolved())
    {
        //printf("not or or not involved\n");
        PredicateImpl *tblPred = NULL;
        bool isPushed = false;
        while (true)
        {
            tblPred = predImpl->getTablePredicate();
            if (NULL == tblPred) break;
            if (pred == tblPred)
            {
                pred = NULL;
                isPushed = pushPredicate(tblPred);
                if (!isPushed)
                {
                    //printf("optimizer could not push table predicate\n");
                }
                break;
            }
            isPushed = pushPredicate(tblPred);
            if (!isPushed)
            {
                //printf("optimizer could not push table predicate\n");
            }
        }
        while (true)
        {
            tblPred = predImpl->getJoinPredicate();
            if (pred == tblPred)
            {
                break;
            }
            if (NULL == tblPred) break;
            isPushed = pushPredicate(tblPred);
            if (!isPushed)
            {
                //printf("optimizer could not push join predicate\n");
            }
        }
    }
    if (pred != NULL)
    {
        //push predicates leave the predicate nodes empty
        //here we remove all the unnecessary nodes
        predImpl = (PredicateImpl*) pred;
        predImpl->removeIfNotNecessary();
        PredicateImpl *p = predImpl->getIfOneSidedPredicate();
        if (NULL != p)
        {
            //TODO::fix this leak below..it dumps core if uncommented
            //delete pred;
            pred = p;
            predImpl = p;
        }
        if (predImpl->isDummyPredicate()) 
        {
            //TODO::fix this leak below..it dumps core if uncommented
            //delete pred;
            pred = NULL;
        }
    }
    DbRetVal rv = leftTableHdl->optimize();
    if (OK != rv) {
        printError(ErrUnknown, "Left handle optimize failed");
        return rv;
    }
    rv = rightTableHdl->optimize();
    if (OK != rv) {
        printError(ErrUnknown, "Left handle optimize failed");
        return rv;
    }
    optimizeRestrict();
    return OK;
}
void JoinTableImpl::optimizeRestrict()
{
    ScanType lType = leftTableHdl->getScanType();
    ScanType rType = rightTableHdl->getScanType();
    bool interChange = false;
    if (lType == fullTableScan && rType != fullTableScan)  interChange = true;
    else if (lType != hashIndexScan  && rType == treeIndexScan) interChange=true;
    /* 
    if (interChange) {
       Table *tmp = leftTableHdl;
       leftTableHdl=rightTableHdl;
       rightTableHdl = tmp;
    }*/

    //get the predicate with right table handle name
    //rightTableHdl->getIndexType();
    return;
}
ScanType JoinTableImpl::getScanType()
{
    ScanType lType = leftTableHdl->getScanType();
    ScanType rType = rightTableHdl->getScanType();
    if (lType == hashIndexScan || rType == hashIndexScan) return hashIndexScan; 
    if (lType == treeIndexScan || rType == treeIndexScan) return treeIndexScan; 
    return fullTableScan;
}

void JoinTableImpl::printPlan(int space)
{
    char spaceBuf[IDENTIFIER_LENGTH];
    memset(spaceBuf, 32, IDENTIFIER_LENGTH);
    spaceBuf[space] = '\0';
    PredicateImpl* predImpl = (PredicateImpl*) pred;
    printf("%s <JOIN-NODE>\n", spaceBuf);
    if (predImpl) predImpl->print(space);
    printf("%s <LEFT>\n", spaceBuf);
    leftTableHdl->printPlan(space+2);
    printf("%s </LEFT>\n", spaceBuf);
    printf("%s <RIGHT>\n", spaceBuf);
    rightTableHdl->printPlan(space+2);
    printf("%s </RIGHT>\n", spaceBuf);
    printf("%s </JOIN-NODE>\n", spaceBuf);
}
DbRetVal JoinTableImpl::execute()
{
    PredicateImpl* predImpl = (PredicateImpl*) pred;
    isNestedLoop = true;
    if (pred) predImpl->setProjectionList(&projList);
    //push the table scan predicates
    optimize();
    leftTableHdl->execute();
    leftTableHdl->fetch();
    rightTableHdl->execute();
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
            rightTableHdl->closeScan();
            rec = leftTableHdl->fetch();
            if (rec == NULL) return NULL;
            rightTableHdl->execute();
            rec = rightTableHdl->fetch();
            if (rec == NULL) return NULL;
            bool result = true;
            while (true) {
                if (pred) rv = predImpl->evaluate(result);
                if ( OK != rv) return NULL; 
                if (result) break;
                rec = rightTableHdl->fetch(); 
                if (rec == NULL) return fetch();
            }
            copyValuesToBindBuffer(NULL);
            return rec;
        }
        else {
            bool result = true;
            while (true) {
                if (pred) rv = predImpl->evaluate(result);
                if ( rv !=OK) return NULL; 
                if (result) break;
                rec = rightTableHdl->fetch(); 
                if (rec == NULL) return fetch();
            }
            copyValuesToBindBuffer(NULL);
            return rec;
        }
        
    }
    return NULL;
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
DbRetVal JoinTableImpl::closeScan()
{
    leftTableHdl->closeScan();
    rightTableHdl->closeScan();
    return OK;
    
}
DbRetVal JoinTableImpl::close()
{
    closeScan();
    ListIterator iter = projList.getIterator();
    JoinProjFieldInfo  *elem;
    while (iter.hasElement())
    {
        elem = (JoinProjFieldInfo*) iter.nextElement();
        free(elem->bindBuf);
        delete elem;
    }
    projList.reset();
    return OK;
}
void* JoinTableImpl::getBindFldAddr(const char *name)
{
    printf("PRABA::join getBindFldAddr not implemented\n");
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
bool JoinTableImpl::isTableInvolved(char *tableName)
{
    //printf("isTableInvolved called in join for %s\n", tableName);
    bool isInvolved = leftTableHdl->isTableInvolved(tableName);
    if (isInvolved) return true;
    isInvolved = rightTableHdl->isTableInvolved(tableName);
    return isInvolved;
}
void* JoinTableImpl::getBindedBuf(char* tName, char* fName)
{
    ListIterator iter = projList.getIterator();
    JoinProjFieldInfo  *elem;
    while (iter.hasElement())
    {
        elem = (JoinProjFieldInfo*) iter.nextElement();
        if (strcmp(elem->fieldName, fName)==0 &&
            strcmp(elem->tableName, tName) ==0)
        {
            return elem->bindBuf;
        }
    }
    return NULL;
}
bool JoinTableImpl::pushPredicate(Predicate *pr)
{
    //printf("PRABA::pushPredicate called\n");
    PredicateImpl *pImpl = (PredicateImpl*) pr;
    bool pushed = leftTableHdl->pushPredicate(pr);
    if (!pushed)
    { 
        pushed = rightTableHdl->pushPredicate(pr);
    }
    if (!pushed)
    {
        //printf("PRABA::unable to push the predicate\n");
        //TODO::check if needs to be placed here
        char *lTbl = leftTableHdl->getName();
        char *rTbl = rightTableHdl->getName();
        char fullName[IDENTIFIER_LENGTH];
        char lTabName[IDENTIFIER_LENGTH];
        char rTabName[IDENTIFIER_LENGTH];
        char lFldName[IDENTIFIER_LENGTH];
        char rFldName[IDENTIFIER_LENGTH];
        strcpy(fullName, pImpl->getFldName1());
        Table::getTableNameAlone(fullName, lTabName);
        Table::getFieldNameAlone(fullName, lFldName);
        strcpy(fullName, pImpl->getFldName2());
        Table::getTableNameAlone(fullName, rTabName);
        Table::getFieldNameAlone(fullName, rFldName);

        if (NULL != lTbl && NULL != rTbl) 
        {
            //both size TableImpl handles are there
            if (0 == strcmp(lTbl, lTabName) || 0 == strcmp(lTbl, rTabName)) 
            {
                if (0 == strcmp(rTbl, lTabName) || 0 == strcmp(rTbl, rTabName))
                {
                    //printf("PRABA::pushed join predicate here1\n");
                    //PRABA::START
                    ComparisionOp op = pImpl->getCompOp();
                    if (strcmp(rTbl, rTabName) ==0)
                    {
                        bool ind = rightTableHdl->hasIndex(rFldName);
                        if (ind) {
                            void *buf = getBindedBuf(lTabName, lFldName);
                            rightTableHdl->addPredicate(rFldName, op, buf);
                        }
                    }else if (strcmp(rTbl, lTabName) ==0)
                    {
                        bool ind = rightTableHdl->hasIndex(lFldName);
                        if (ind) {
                            void *buf = getBindedBuf(rTabName, rFldName);
                            rightTableHdl->addPredicate(lFldName, op, buf);
                        }
                    }
                    //PRABA::END
                    setPredicate(pr);
                    pushed = true;
                }
            }
        }else{
            if(isTableInvolved(lTabName) && isTableInvolved(rTabName))
            {
                //printf("PRABA::pushed join predicate here2\n");
                    //PRABA::START
                    ComparisionOp op = pImpl->getCompOp();
                    if (strcmp(rTbl, rTabName) ==0)
                    {
                        bool ind = rightTableHdl->hasIndex(rFldName);
                        if (ind) {
                            void *buf = getBindedBuf(lTabName, lFldName);
                            rightTableHdl->addPredicate(rFldName, op, buf);
                        }
                    }else if (strcmp(rTbl, lTabName) ==0)
                    {
                        bool ind = rightTableHdl->hasIndex(lFldName);
                        if (ind) {
                            void *buf = getBindedBuf(rTabName, rFldName);
                            rightTableHdl->addPredicate(lFldName, op, buf);
                        }
                    }
                    //PRABA::END
                setPredicate(pr);
                pushed = true;
            }
        }
    }
    return pushed;
}
void JoinTableImpl::setPredicate(Predicate *pr)
{
    if (NULL == pred) { pred = pr; return; }
    Predicate *curPred = pred;
    PredicateImpl *newPred = new PredicateImpl();
    newPred->setTerm(curPred, OpAnd, pr);
    newPred->setProjectionList(&projList);
    pred = newPred;
    return;
}
