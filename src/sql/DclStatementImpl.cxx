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
}

DbRetVal DclStatementImpl::resolve()
{
    return OK;
}

DbRetVal DclStatementImpl::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    
    if (NULL == usrMgr)
    {
        printError(ErrBadCall, "UserManager should be set before executing DclStatements.");
        return ErrBadCall;
    }
    
    const DclInfoNode *infoNode = parsedData->getDclInfoNode();
    if (NULL == infoNode)
    {
        printError(ErrBadCall, "DclInfoNode was NULL when it shouldn't be.");
        return ErrBadCall;
    }
    
    FieldConditionValMap conditionValues;
    mapConditionValueList(parsedData->getConditionValueList(), conditionValues);
    
    if (GRANTACCESS == infoNode->type)
    {
        Condition *c = parsedData->getCondition();
        usrMgr->grantPrivilege(parsedData->getPrivileges(), 0, (NULL != c ? c->getPredicate() : NULL), conditionValues);
    }
    else if (REVOKEACCESS == infoNode->type)
    {
        return ErrBadCall; // not yet implemented.
    }
    
    return rv;
}
