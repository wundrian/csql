/* 
 * File:   DclStatementImpl.cxx (so named b/c of a symbol conflict with StatementTypes.DclStatement)
 * Author: mabi
 * 
 * Created on April 15, 2012, 10:22 PM
 */

#include <Statement.h>

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
    table = dbMgr->openTable(parsedData->getTableName());
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
        goto cleanup;
    }
    
    const DclInfoNode *infoNode = parsedData->getDclInfoNode();
    if (NULL == infoNode)
    {
        rv = ErrBadCall;
        printError(rv, "DclInfoNode was NULL when it shouldn't be.");
        goto cleanup;
    }
    
    FieldConditionValMap conditionValues;
    mapConditionValueList(parsedData->getConditionValueList(), conditionValues);
    
    if (GRANTACCESS == infoNode->type)
    {
        Condition *c = parsedData->getCondition();
        rv = (DbRetVal)usrMgr->grantPrivilege(parsedData->getPrivileges(), table->getId(), (NULL != c ? c->getPredicate() : NULL), conditionValues);
    }
    else if (REVOKEACCESS == infoNode->type)
    {
        rv = (DbRetVal)usrMgr->revokePrivilege(parsedData->getPrivileges(), table->getId());
    }
    else
    {
        rv = ErrBadCall;
        printError(rv, "Operation not supported.");
        goto cleanup;
    }
    
    cleanup:
            dbMgr->closeTable(table);
            return rv;
            
}
