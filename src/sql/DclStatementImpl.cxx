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
    
    FieldConditionValMap conditionValues;
    mapConditionValueList(parsedData->getConditionValueList(), conditionValues);
    
    const std::vector<DclInfoNode> infoNodes = parsedData->getDclInfoNodes();
    for (std::vector<DclInfoNode>::const_iterator it = infoNodes.begin(); it != infoNodes.end(); ++it)
    {
        if (GRANTACCESS == it->type)
        {
            Condition *c = parsedData->getCondition();
            Predicate *p = (NULL != c ? c->getPredicate() : NULL);
            if (NULL != p) ((PredicateImpl*)p)->setTable(table);

            rv = (DbRetVal)usrMgr->grantPrivilege(it->privs, table->getId(), it->userName,
                    p, conditionValues);
        }
        else if (REVOKEACCESS == it->type)
        {
            rv = (DbRetVal)usrMgr->revokePrivilege(it->privs, table->getId(), it->userName);
        }
    }
    
    dbMgr->closeTable(table);
    return rv;
            
}
