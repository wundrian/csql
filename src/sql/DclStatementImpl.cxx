/* 
 * File:   DclStatementImpl.cxx (so named b/c of a symbol conflict with StatementTypes.DclStatement)
 * Author: mabi
 * 
 * Created on April 15, 2012, 10:22 PM
 */

#include <Statement.h>
#include "PredicateImpl.h"

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
    
    if (OK != (rv = ((DatabaseManagerImpl*)dbMgr)->sysDb()->getXCheckpointMutex()))
    {
        printError(rv, "Unable to get exclusive access to system database.");
        dbMgr->closeTable(table);
        return rv;
    }

    const std::vector<DclInfoNode> infoNodes = parsedData->getDclInfoNodes();
    for (std::vector<DclInfoNode>::const_iterator it = infoNodes.begin(); it != infoNodes.end(); ++it)
    {
        if (GRANTACCESS == it->type)
        {
            Condition *c = parsedData->getCondition();
            PredicateImpl *rootPred = (NULL != c ? (PredicateImpl*)c->getPredicate() : NULL);

            rv = (DbRetVal)usrMgr->grantPrivilege(it->privs, table->getId(), it->userName, rootPred, parsedData->getConditionValueList());
        }
        else if (REVOKEACCESS == it->type)
        {
            rv = (DbRetVal)usrMgr->revokePrivilege(it->privs, table->getId(), it->userName);
        }

        if (OK != rv) break;
    }
    
    ((DatabaseManagerImpl*)dbMgr)->sysDb()->releaseCheckpointMutex();
    dbMgr->closeTable(table);
    return rv;
}
