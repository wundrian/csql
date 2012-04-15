/* 
 * File:   DclStatementImpl.cxx (so named b/c of a symbol conflict with StatementTypes.DclStatement)
 * Author: mabi
 * 
 * Created on April 15, 2012, 10:22 PM
 */

#include <Statement.h>

DclStatementImpl::DclStatementImpl() {}
DclStatementImpl::~DclStatementImpl() {}

DbRetVal DclStatementImpl::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    
    return rv;
}
