/* 
 * File:   DclStatementImpl.cxx (so named b/c of a symbol conflict with StatementTypes.DclStatement)
 * Author: mabi
 * 
 * Created on April 15, 2012, 10:22 PM
 */

#include <Statement.h>
#include "PredicateImpl.h"

DbRetVal DclStatementImpl::mapConditionValueList(List values, FieldConditionValMap& result)
{
    ListIterator it = values.getIterator();
    while (it.hasElement()) {
        ConditionValue *el = (ConditionValue *)it.nextElement();

        if (0 == strcmp("?", el->parsedString))
        {
            printError(ErrSyntaxError, "Positional parameters are not allowed in a GRANT statement");
            return ErrSyntaxError;
        }
        
        result.insert(std::make_pair(std::string(el->fName), *el));
    }
    
    return OK;
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
    
    const std::vector<DclInfoNode> infoNodes = parsedData->getDclInfoNodes();
    for (std::vector<DclInfoNode>::const_iterator it = infoNodes.begin(); it != infoNodes.end(); ++it)
    {
        if (GRANTACCESS == it->type)
        {
            Condition *c = parsedData->getCondition();
            PredicateImpl *rootPred = (NULL != c ? (PredicateImpl*)c->getPredicate() : NULL);

            FieldConditionValMap conditionValues;
            if (OK != (rv = mapConditionValueList(parsedData->getConditionValueList(), conditionValues)))
            {
                dbMgr->closeTable(table);
                return rv;
            }

            rv = (DbRetVal)usrMgr->grantPrivilege(it->privs, table->getId(), it->userName, rootPred, conditionValues);
        }
        else if (REVOKEACCESS == it->type)
        {
            rv = (DbRetVal)usrMgr->revokePrivilege(it->privs, table->getId(), it->userName);
        }

        if (OK != rv) break;
    }
    
    dbMgr->closeTable(table);
    return rv;
}
