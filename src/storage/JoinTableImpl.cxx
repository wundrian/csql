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
    isLeftRecOver = false;
    isFirstCall = true;
    availableLeft = true;
    isFirstFetch = true;
    isReturnNull = false;
    isOuterJoin = false;
    leftSideFail = false;
    jType = INNER_JOIN;
    isNestedLoop = true;
    rightExhausted = false;
}
JoinTableImpl::~JoinTableImpl() {}

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
    DbRetVal rv = getFieldInfo(fldname, info);
    if ( OK != rv) {
        printError(ErrBadCall, "Field not found or unqualified field name %s", fldname);
        delete def;
        delete info;
        return ErrSyntaxError;
    }
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
    if (jType == INNER_JOIN)
        printf("%s <TYPE> INNER_JOIN </TYPE>\n", spaceBuf);
    else if (jType == LEFT_JOIN)
        printf("%s <TYPE> LEFT_JOIN </TYPE>\n", spaceBuf);
    else if (jType == RIGHT_JOIN)
        printf("%s <TYPE> RIGHT_JOIN </TYPE>\n", spaceBuf);
    else if (jType == FULL_JOIN)
        printf("%s <TYPE> FULL_JOIN </TYPE>\n", spaceBuf);

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
    //if (!leftTableHdl->getName())  printf("execute called with isFirstCall %d\n", isFirstCall);
    PredicateImpl* predImpl = (PredicateImpl*) pred;
    isNestedLoop = true;
    if (pred) 
    {
        predImpl->setProjectionList(&projList);
        predImpl->solveForProjList(this);
    }
    //push the table scan predicates
    //PRABA::TEMP:
    //if( jType != LEFT_JOIN) optimize();
    if (leftTableHdl->getName()) {
       //printf("left execute call %s", leftTableHdl->getName());
       optimize();
       leftTableHdl->execute();
       leftTableHdl->fetch();
    }else if (isFirstCall) {
       //printf("First call");
       optimize();
       leftTableHdl->execute();
       void *rec = leftTableHdl->fetch();
       //printf("rec value is %x\n", rec);
       isFirstCall = false;
    }
    rightTableHdl->execute();
    TableImpl *tImpl = (TableImpl*) rightTableHdl;
    isOuterJoin= true;
    isFirstFetch = true;
    return OK;
}
void* JoinTableImpl::fetch()
{
    //if (!leftTableHdl->getName())  printf("fetch called\n");
    if (isLeftRecOver) return NULL;
    void * rec = fetchInt();
    //if (!leftTableHdl->getName())  printf("rec got %x\n", rec);
    
    if (rec == NULL && jType == LEFT_JOIN && isFirstFetch) 
    { 
        isFirstFetch= false; 
        isReturnNull = true; 
        copyValuesToBindBuffer(NULL);
        //if (!leftTableHdl->getName())  printf("rec value is 0x1\n");
        return (void*)0x1;
    }
    isReturnNull = false;
    //if (!leftTableHdl->getName())  printf("rec value is %x\n", rec);
    return rec;
}
void* JoinTableImpl::fetchInt()
{
    PredicateImpl* predImpl = (PredicateImpl*) pred;
    DbRetVal rv = OK;
    if (isNestedLoop)
    {
        void *rec = rightTableHdl->fetch();
        if (rec==NULL)
        {
            return fetchRightFail();
        }
        else {
            if (jType == LEFT_JOIN  && leftSideFail
                && !leftTableHdl->getName()
                && !isFirstFetch) return fetchRightFail();
            
            bool result = true;
            while (true) {
                if (pred) rv = predImpl->evaluate(result);
                if ( rv !=OK) return NULL; 
                if (result) break;
                rec = rightTableHdl->fetch(); 
                if (rec == NULL) {
                    if (jType == LEFT_JOIN && isFirstFetch) return NULL;
                    return fetchInt();
                }
            }
            copyValuesToBindBuffer(NULL);
            isFirstFetch = false;
            return rec;
        }
    }
    return NULL;
}

void* JoinTableImpl::fetchRightFail()
{
    if (jType == LEFT_JOIN && isFirstFetch) { return NULL;}
    //if (!leftTableHdl->getName())  printf("fetch right fail called\n");
    PredicateImpl* predImpl = (PredicateImpl*) pred;
    DbRetVal rv = OK;
    rightTableHdl->closeScan();
    void *rec = leftTableHdl->fetch();
    //if (!leftTableHdl->getName()) printf("rec value is %x\n", rec);
    leftSideFail= false;
    if (rec == NULL) {isLeftRecOver= true; return NULL;}
    else if (rec == (char*)0x1) { leftSideFail = true;}
    rightTableHdl->execute();
    isFirstFetch = true;
    rec = rightTableHdl->fetch();
    if (rec == NULL || leftSideFail) { 
        //if(!leftTableHdl->getName()) printf("RIGHT FETCH returns NULL\n");
        //if join condition(pred) is set and if it is pushed to tablehdl
        //when there is index, it returns no record
        if (jType == LEFT_JOIN && pred) return NULL;
        return fetchRightFail();
    } 
    bool result = true;
    isReturnNull = false;
    while (true) {
        if (pred) rv = predImpl->evaluate(result);
        if ( OK != rv) return NULL;
        if (result) {  break; }
        rec = rightTableHdl->fetch();
        if (rec == NULL) {
            if (jType == LEFT_JOIN) {
                //return from here so that null values for rhs table will be set
                return (void*)  NULL;
            }
            return fetchInt();
        }
    }
    isFirstFetch = false;
    copyValuesToBindBuffer(NULL);
    return rec;
}
void* JoinTableImpl::fetch(DbRetVal &rv)
{
    rv = OK; 
    return fetchInt();
}

void* JoinTableImpl::fetchNoBind()
{
    printError(ErrBadCall, "fetchNoBind not implemented for JoinTableImpl");
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
    DbRetVal retCode = OK, retCode1 =OK;
    availableLeft = false;
    retCode = leftTableHdl->getFieldInfo(fldname, info);
    if (retCode ==OK)
    {
        availableLeft= true;
        //return OK;
    }
    retCode1 = rightTableHdl->getFieldInfo(fldname, info);
    if (retCode1 ==OK)
    {
        if (availableLeft) return ErrSyntaxError;
        return OK;
    }
    return retCode;
}

long JoinTableImpl::numTuples()
{
    return 0;
}
DbRetVal JoinTableImpl::closeScan()
{
    //if (leftTableHdl && leftTableHdl->getName()) leftTableHdl->closeScan();
    if (leftTableHdl) leftTableHdl->closeScan();
    if (rightTableHdl) rightTableHdl->closeScan();
    isLeftRecOver = false;
    isFirstCall = true;
    return OK;
    
}

DbRetVal JoinTableImpl::close()
{
    closeScan();
    if (leftTableHdl) { leftTableHdl->close(); leftTableHdl = NULL; }
    if (rightTableHdl) { rightTableHdl->close(); rightTableHdl = NULL; }
    ListIterator iter = projList.getIterator();
    JoinProjFieldInfo  *elem;
    while (iter.hasElement())
    {
        elem = (JoinProjFieldInfo*) iter.nextElement();
        free(elem->bindBuf);
        delete elem;
    }
    projList.reset();
    //delete pred;
    ListIterator pIter = predList.getIterator();
    while(pIter.hasElement())
    {
        PredicateImpl *pImpl = (PredicateImpl*) pIter.nextElement();
        delete pImpl;
    }
    predList.reset();
    delete this;
    return OK;
}
void* JoinTableImpl::getBindFldAddr(const char *name)
{
    void* bindAddr = leftTableHdl->getBindFldAddr(name);
    if (bindAddr) return bindAddr;
    return rightTableHdl->getBindFldAddr(name);
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
    leftList.reset();
    rightList.reset();
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
        char *lAliasTbl = leftTableHdl->getAliasName();
        char *rAliasTbl = rightTableHdl->getAliasName();
        bool isAliasSet = lAliasTbl &&  rAliasTbl && (!(strcmp(lAliasTbl,"") == 0 && strcmp(rAliasTbl,"") == 0 ));
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
            if (0 == strcmp(lTbl, lTabName) || 0 == strcmp(lTbl, rTabName) || ( isAliasSet && (0 == strcmp(lAliasTbl, lTabName) ||0 == strcmp(lAliasTbl,rTabName))) ) 
            {
                if (0 == strcmp(rTbl, lTabName) || 0 == strcmp(rTbl, rTabName)|| (isAliasSet && (0 == strcmp(rAliasTbl, lTabName) ||0 == strcmp(rAliasTbl,rTabName))))
                {
                    //printf("PRABA::pushed join predicate here1\n");
                    //PRABA::START
                    ComparisionOp op = pImpl->getCompOp();
                    if (0 == strcmp(rTbl, rTabName) ||(isAliasSet && 0 == strcmp(rAliasTbl, rTabName)))
                    {
                        //bool ind = rightTableHdl->hasIndex(rFldName);
                        if (OpEquals ==op) {
                            void *buf = getBindedBuf(lTabName, lFldName);
                            rightTableHdl->addPredicate(rFldName, op, buf);
                            pImpl->setDontEvaluate();
                        }
                    }else if (0==strcmp(rTbl, lTabName) || (isAliasSet && 0== strcmp(rAliasTbl, lTabName)))
                    {
                        //bool ind = rightTableHdl->hasIndex(lFldName);
                        if (OpEquals ==op) {
                            void *buf = getBindedBuf(rTabName, rFldName);
                            rightTableHdl->addPredicate(lFldName, op, buf);
                            pImpl->setDontEvaluate();
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
                        //bool ind = rightTableHdl->hasIndex(rFldName);
                        if (OpEquals ==op) {
                            void *buf = getBindedBuf(lTabName, lFldName);
                            rightTableHdl->addPredicate(rFldName, op, buf);
                            pImpl->setDontEvaluate();
                        }
                    }else if (strcmp(rTbl, lTabName) ==0)
                    {
                        //bool ind = rightTableHdl->hasIndex(lFldName);
                        if (OpEquals ==op) {
                            void *buf = getBindedBuf(rTabName, rFldName);
                            rightTableHdl->addPredicate(lFldName, op, buf);
                            pImpl->setDontEvaluate();
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
    predList.append(newPred);
    pred = newPred;
    return;
}
bool JoinTableImpl::isFldNull(const char *name)
{
    bool ret = false;
    if(NULL==leftTableHdl->getName()) 
    {
        ret = leftTableHdl->isFldNull(name);
        if(ret==true) return true;
    }
    else
    {
        char tableName[IDENTIFIER_LENGTH];
        Table::getTableNameAlone((char*)name, tableName);    
        if(0 == strcmp(tableName,leftTableHdl->getName()))
        {
            return leftTableHdl->isFldNull(name);
        }
    }
    if(NULL==rightTableHdl->getName())
    {
        if (isReturnNull) return true;
        ret = rightTableHdl->isFldNull(name);
        if(ret==true) return true;
    }
    else{
        char tableName[IDENTIFIER_LENGTH];
        Table::getTableNameAlone((char*)name, tableName);
        if(0==strcmp(tableName,rightTableHdl->getName()))
        {
            if (isReturnNull) return true;
            return rightTableHdl->isFldNull(name);
        }
    }
    return ret;
}
//same as above expect it does not check for isRecordFound flag
//as it is set only after predicate evaluate
bool JoinTableImpl::isFldNullInt(const char *name)
{
    bool ret = false;
    if(NULL==leftTableHdl->getName())
    {
        ret = leftTableHdl->isFldNull(name);
        if(ret==true) return true;
    }
    else
    {
        char tableName[IDENTIFIER_LENGTH];
        Table::getTableNameAlone((char*)name, tableName);
        if(0 == strcmp(tableName,leftTableHdl->getName()))
        {
            return leftTableHdl->isFldNull(name);
        }
    }
    if(NULL==rightTableHdl->getName())
    {
        ret = rightTableHdl->isFldNull(name);
        if(ret==true) return true;
    }
    else{
        char tableName[IDENTIFIER_LENGTH];
        Table::getTableNameAlone((char*)name, tableName);
        if(0==strcmp(tableName,rightTableHdl->getName()))
        {
            return rightTableHdl->isFldNull(name);
        }
    }
    return ret;
}

