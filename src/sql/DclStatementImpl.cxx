/* 
 * File:   DclStatementImpl.cxx (so named b/c of a symbol conflict with StatementTypes.DclStatement)
 * Author: mabi
 * 
 * Created on April 15, 2012, 10:22 PM
 */

#include <Statement.h>
#include "PredicateImpl.h"

int DclStatementImpl::mapConditionValueList(List values, FieldConditionValMap& result)
{
    ListIterator it = values.getIterator();
    while (it.hasElement()) {
        ConditionValue *el = (ConditionValue *)it.nextElement();
        
        result.insert(std::make_pair(std::string(el->fName), *el));
    }
    
    return result.size();
}

// TODO take and release database mutex!!!
DbRetVal DclStatementImpl::createAndPopulatePredicateChunk(void *&dataPtr)
{
    DbRetVal rv = OK;
    Condition *c = parsedData->getCondition();
    PredicateImpl *rootPred = (NULL != c ? (PredicateImpl*)c->getPredicate() : NULL);

    // No condition, no problem
    if (NULL == rootPred)
    {
        dataPtr = NULL;
        return rv;
    }

    /* first step: calculate total space needed to store ConditionValue list and serialized PredicateImpl tree */
    size_t allocSize = 1 /*PredicateImpl::SERIALIZED_VERSION */
      + sizeof(unsigned int) /* ConditionValue list size */
      + PredicateImpl::SERIALIZED_SIZE * rootPred->treeSize(); /* nodes */
    
    List condValues = parsedData->getConditionValueList();
    ListIterator it = condValues.getIterator();
    unsigned int conditionValueCount = 0;
    while (it.hasElement())
    {
        allocSize += ((ConditionValue*)it.nextElement())->sizeTotal();
        conditionValueCount++;
    }

    /* second: allocate enough memory, take care not to loose the data pointer! */
    Chunk *predChunk = ((DatabaseManagerImpl*)dbMgr)->createUserChunk(allocSize);
    if (NULL == predChunk)
    {
        printError(ErrSysInternal, "Unable to create user predChunk for condition values");
        return ErrSysInternal;
    }

    dataPtr = predChunk->allocate(((DatabaseManagerImpl*)dbMgr)->sysDb(), &rv);
    if (OK != rv)
    {
        ((DatabaseManagerImpl*)dbMgr)->deleteUserChunk(predChunk);
        printError(rv, "Unable to allocate predChunk memory for condition values.");
        return rv;
    }
    
    it.reset();
    /* this loop copies all ConditionValue instances into predChunk.
     * Note how they are seperated by the first '\0' after offset + sizeof(ConditionValue)
     *
     * To make it easier to reconstruct the list, save the list length at the start
     *
     * We need to reconstruct the whole list every time we use the predChunk, so
     * there's no benefit to store all ConditionValue instances first in the
     * predChunk (so they make an indexable array)
     */
    *((unsigned int*)dataPtr) = conditionValueCount;
    int offset = sizeof(unsigned int);
    for (int strLen = 0; it.hasElement(); )
    {
        ConditionValue *elem = (ConditionValue*)it.nextElement();
        (void) memcpy((char*)dataPtr + offset, elem, sizeof(ConditionValue));

        offset += sizeof(ConditionValue);

        strLen = strlen(elem->parsedString) + 1;
        (void) memcpy((char*)dataPtr + offset, elem->parsedString, strLen);
        offset += strLen;
    }

    /* finally, PredicateImpl can take care of serializing itself to dataPtr */
    *((char *)dataPtr + offset) = PredicateImpl::SERIALIZED_VERSION;
    rootPred->serialize((char*)dataPtr + offset + 1);

    return rv;
}

DbRetVal DclStatementImpl::resolve()
{
    table = (TableImpl*)dbMgr->openTable(parsedData->getTableName());
    if (NULL == table)
    {
        printError(ErrBadArg, "Table %s does not exist. Can't grant privileges on it.", parsedData->getTableName());
        return ErrBadArg;
    }
    
    return OK;
}

DbRetVal DclStatementImpl::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    
    if (NULL == table)
    {
        rv = ErrBadCall;
        printError(rv, "Table %s not open when it should be.", parsedData->getTableName());
        return rv; // no table to cleanup
    }
    
    if (NULL == usrMgr)
    {
        rv = ErrBadCall;
        printError(rv, "UserManager should be set before executing DclStatements.");
        dbMgr->closeTable(table);
        return rv;
    }
    
    void *predPtr;
    rv = createAndPopulatePredicateChunk(predPtr);
    if (OK != rv)
    {
        dbMgr->closeTable(table);
        printError(rv, "Unable to collect Predicate(s)");
        return rv;
    }
    
    const std::vector<DclInfoNode> infoNodes = parsedData->getDclInfoNodes();
    for (std::vector<DclInfoNode>::const_iterator it = infoNodes.begin(); it != infoNodes.end(); ++it)
    {
        if (GRANTACCESS == it->type)
        {
            rv = (DbRetVal)usrMgr->grantPrivilege(it->privs, table->getId(), it->userName, predPtr);
        }
        else if (REVOKEACCESS == it->type)
        {
            rv = (DbRetVal)usrMgr->revokePrivilege(it->privs, table->getId(), it->userName);
        }
    }
    
    dbMgr->closeTable(table);
    return rv;
}
