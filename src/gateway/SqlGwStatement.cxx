/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <SqlGwConnection.h>
#include <SqlOdbcStatement.h>
#include <SqlGwStatement.h>
#include <SqlLogStatement.h>
#include <CacheTableLoader.h>
#include <TableConfig.h>

DbRetVal SqlGwStatement::executeDirect(char *stmtstr)
{
    DbRetVal rv = OK;
    int rows = 0;
    rv = prepare(stmtstr);
    if (rv != OK)  return rv;
    rv = execute(rows);
    if (rv != OK) return rv;
    return rv;
}
 
DbRetVal SqlGwStatement::prepare(char *stmtstr)
{
    char dsnname[IDENTIFIER_LENGTH];
    char *dsn = dsnname;
    char tab[IDENTIFIER_LENGTH]; 

    bool connClose=false; 
    bool SyntaxError=false;
    DbRetVal rv = OK,ret=OK;
    char *stmtTblName = NULL;
    
    SqlGwConnection *conn = (SqlGwConnection*) con;
    if (!conn->isAdptConnected() && !conn->isCsqlConnected()) return ErrNoConnection; 
    SqlOdbcStatement *ada=(SqlOdbcStatement*) adapter;
    struct MultiDSN *node = conn->multi_adapter_head; //
    
    stmtHdlr = NoHandler;
    if (innerStmt) rv = innerStmt->prepare(stmtstr);
    if (rv == OK) isPrepared = true;
    if (rv == ErrNotOpen) connClose=true;//new line addded for MultiDsn
    if (rv == ErrSyntaxError) SyntaxError=true;//new line addded for MultiDsn
    stmtTblName = innerStmt->getTableName();

    bool isAllcachedTableForJoin = true;
    int noOfTable = 0;
    
    StatementType stype = innerStmt->getStmtType();
    printDebug(DM_Gateway,"Table Name %s\t Stmt Type %d\n",stmtTblName, stype);
    if (stype == CacheTableStatement || stype == CompactTableStatement)
    {
        stmtHdlr = CSqlHandler;
        return OK;
    }
  
    ListIterator titer =innerStmt->getTableNameList().getIterator();
    while (titer.hasElement())
    {
        TableName *t  = (TableName*)titer.nextElement();
        ret = TableConf::config.isTableCached(t->tblName);
        if(ret!=OK) isAllcachedTableForJoin=false;
        noOfTable++;
    }
    if(noOfTable == 1) { isAllcachedTableForJoin = true; }
    mode = TableConf::config.getTableMode(stmtTblName);
    bool isCached = TableConf::config.isTableCached(mode);
    bool isSelStmt = innerStmt->isSelect();
    bool localTable = false;
    if (rv == OK && mode == 0) localTable = true;
    bool isDirect = mode & DIRECT_CACHE;
/*    if((mode==2||mode==6) && !innerStmt->isSelect())
    {
       printError(ErrReadOnlyCache, "Partial Cache Condition Violation for Non select Dml statement\n");
       return ErrReadOnlyCache;
    } */
    
    if ((rv == OK) && (!isDirect || isSelStmt) && isAllcachedTableForJoin)
    {
        stmtHdlr = CSqlHandler;
        if (localTable || isSelStmt || (( isCached) && Conf::config.getCacheMode()==ASYNC_MODE))
            return rv;  
    }
    //TODO::add procedures also in the below checking
    if (!strncasecmp(stmtstr,"INSERT", 6) == 0 &&
        !strncasecmp(stmtstr, "UPDATE", 6) ==0 &&
        !strncasecmp(stmtstr, "SELECT", 6) ==0 &&
        !strncasecmp(stmtstr, "DELETE", 6) ==0 && 
        (NULL==strstr(stmtstr,"call ") && NULL == strstr(stmtstr,"CALL ")) )return rv;

    printDebug(DM_Gateway, "Handled by csql %d\n", shouldCSqlHandle());

    if (!shouldCSqlHandle()) stmtHdlr = AdapterHandler;
    if ( shouldCSqlHandle() && Conf::config.getCacheMode() == SYNC_MODE && 
         !isSelStmt && isCached) stmtHdlr = CSqlAndAdapterHandler;

    printDebug(DM_Gateway, "Handled  %d\n", stmtHdlr);
    strcpy(tab, stmtTblName);

    /*********The below code is for MultiDsn.***********/
              
    //If Prepared by CSQL and if the table is cached.
    if(isPrepared && (ret = TableConf::config.getDsnForTable(tab,dsn)) == OK) {   
        if (adapter && shouldAdapterHandle()) {
            adapter->setConnection(conn->getAdapterConnection(dsnname));
            rv = adapter->prepare(stmtstr);
            if (rv == OK) setToCommit(dsnname);
        }
    }
    //Default adapter should prepare when table name is not found by csql's prepare(),
    //This happens only when csql connection is down or there is a complex query.
     if((stmtHdlr == AdapterHandler && connClose) || SyntaxError){   
       adapter->setConnection(conn->getAdapterConnection(Conf::config.getDSN()));
           if(adapter && shouldAdapterHandle()){
               rv = adapter->prepare(stmtstr);
               setToCommit(Conf::config.getDSN());
           }
    }
    //For non-cached TDB tables, where the table name is found in csql prepare.
    if(!isPrepared && !SyntaxError && !connClose) {
        if(conn->noOfCon == 1){
            adapter->setConnection(conn->getAdapterConnection(node->dsn));
            if(adapter && shouldAdapterHandle()) {
                rv = adapter->prepare(stmtstr);
                if(rv == OK) node->toCommit=true;
            }
         }else{
            while(node != NULL) {
                if(adapter)
                adapter->setConnection(conn->getAdapterConnection(node->dsn));
                if(ada->isTableExists(tab)){
                    if(adapter && shouldAdapterHandle()){
                        rv = adapter->prepare(stmtstr);
                        if(rv == OK) node->toCommit=true;
                        break; 
                    }
                }
                node=node->next;
            }//while Ends here....
        }                  
    } 
    if(rv != OK) {
        printError(ErrBadCall, "Both adapter and csql could not prepare");
        isPrepared = false;
    }else isPrepared = true;
    return rv;
}

bool SqlGwStatement::shouldAdapterHandle()
{
    if (stmtHdlr == AdapterHandler  || (stmtHdlr == CSqlAndAdapterHandler)) return true;
    return false;
}
bool SqlGwStatement::shouldCSqlHandle()
{
    SqlGwConnection *conn = (SqlGwConnection*) con;
    if (stmtHdlr == CSqlHandler || 
        stmtHdlr == CSqlAndAdapterHandler) return true;
    return false;
}
bool SqlGwStatement::isSelect()
{
    bool retValue;
    if (adapter && shouldAdapterHandle()) retValue =  adapter->isSelect();
    if (innerStmt && shouldCSqlHandle()) retValue =  innerStmt->isSelect();
    return retValue;
}

DbRetVal SqlGwStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    SqlGwConnection *conn = (SqlGwConnection*) con;
    if (!conn->isAdptConnected() && !conn->isCsqlConnected()) return ErrNoConnection; 
    if (!isPrepared) { return ErrNotPrepared; }
    if (adapter && shouldAdapterHandle()) {
        rv = adapter->execute(rowsAffected);
    }
    if (rv != OK) return rv;
    if (shouldAdapterHandle()) 
    {
        GwHandler hdlr = conn->getTxnHandler();
        if (hdlr == NoHandler) conn->setTxnHandler(AdapterHandler);
        if (hdlr == CSqlHandler) conn->setTxnHandler(CSqlAndAdapterHandler);
    }
    if (innerStmt && shouldCSqlHandle()) rv = innerStmt->execute(rowsAffected);
    if (shouldCSqlHandle()) 
    {
        GwHandler hdlr = conn->getTxnHandler();
        if (hdlr == NoHandler) conn->setTxnHandler(CSqlHandler);
        if (hdlr == AdapterHandler) conn->setTxnHandler(CSqlAndAdapterHandler);
    }
    return rv;
}

DbRetVal SqlGwStatement::bindParam(int pos, void* value)
{
    DbRetVal rv = OK;
    printError(ErrWarning, "Deprecated and does not replicate or cache");
    return rv;
}

DbRetVal SqlGwStatement::bindField(int pos, void* value)
{
    DbRetVal rv = OK;
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) rv = adapter->bindField(pos, value);
    if (rv != OK) return rv;
    if (innerStmt && shouldCSqlHandle()) rv = innerStmt->bindField(pos,value);
    return rv;
}

void* SqlGwStatement::fetch()
{
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) return adapter->fetch();
    if (innerStmt && shouldCSqlHandle()) return innerStmt->fetch();
    return NULL;
}

void* SqlGwStatement::fetch(DbRetVal &rv)
{
    //TODO::this will never be handled by both. check the flag for this
    if (!isPrepared) { rv = ErrNotPrepared; return NULL; }
    if (adapter && shouldAdapterHandle()) return adapter->fetch(rv);
    if (innerStmt && shouldCSqlHandle()) return innerStmt->fetch(rv);
    return NULL;
}

void* SqlGwStatement::fetchAndPrint(bool SQL)
{
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) return adapter->fetchAndPrint(SQL);
    if (innerStmt && shouldCSqlHandle()) return innerStmt->fetchAndPrint(SQL);
    return NULL;
}

void* SqlGwStatement::next()
{
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) return adapter->next();
    if (innerStmt && shouldCSqlHandle()) return innerStmt->next();
    return NULL;
}

DbRetVal SqlGwStatement::close()
{
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) return adapter->close();
    if (innerStmt && shouldCSqlHandle()) return innerStmt->close();
    return OK;
}

void* SqlGwStatement::getFieldValuePtr( int pos )
{
    //TODO::this will never be handled by both. check the flag for this
    if (adapter && shouldAdapterHandle()) return adapter->getFieldValuePtr(pos);
    if (innerStmt && shouldCSqlHandle()) return innerStmt->getFieldValuePtr(pos);
    return NULL;
}
void SqlGwStatement::getProjFieldType(int *data)
{
   if (innerStmt && shouldCSqlHandle()) return innerStmt->getProjFieldType(data);
   if (adapter && shouldAdapterHandle()) return adapter->getProjFieldType(data);
}

void* SqlGwStatement::getFieldValuePtr( char *name )
{
   if (adapter && shouldAdapterHandle()) return adapter->getFieldValuePtr(name);
   if (innerStmt && shouldCSqlHandle()) return innerStmt->getFieldValuePtr(name);
   return NULL;
}
int SqlGwStatement::noOfProjFields()
{
    //TODO::this will never be handled by both. check the flag for this
    if (innerStmt && shouldCSqlHandle()) return innerStmt->noOfProjFields();
    if (adapter && shouldAdapterHandle()) return adapter->noOfProjFields();
    return 0;
}

int SqlGwStatement::noOfParamFields()
{
    if (innerStmt && shouldCSqlHandle()) return innerStmt->noOfParamFields();
    if (adapter && shouldAdapterHandle()) return adapter->noOfParamFields();
    return 0;
}

DbRetVal SqlGwStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    if (innerStmt && shouldCSqlHandle()) return innerStmt->getProjFldInfo(projpos, fInfo);
    if (adapter && shouldAdapterHandle()) return adapter->getProjFldInfo(projpos, fInfo);
    return OK;
}

DbRetVal SqlGwStatement::getParamFldInfo (int parampos, FieldInfo *&fInfo)
{
    if (innerStmt && shouldCSqlHandle()) return innerStmt->getParamFldInfo(parampos, fInfo);
    if (adapter && shouldAdapterHandle()) return adapter->getParamFldInfo(parampos, fInfo);
    return OK;
}

DbRetVal SqlGwStatement::free()
{
    DbRetVal rv = OK;
    if (!isPrepared) return OK;
    if (adapter && shouldAdapterHandle()) rv = adapter->free(); 
    if (innerStmt && shouldCSqlHandle()) rv = innerStmt->free();
    stmtHdlr = NoHandler;
    isPrepared = false;
    return rv;
}
void SqlGwStatement::setShortParam(int paramPos, short value)
{
    if (adapter && shouldAdapterHandle()) adapter->setShortParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setShortParam(paramPos,value);
    return;
}
void SqlGwStatement::setIntParam(int paramPos, int value)
{
    if (adapter && shouldAdapterHandle()) adapter->setIntParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setIntParam(paramPos,value);
    return;

}
void SqlGwStatement::setLongParam(int paramPos, long value)
{
    if (adapter && shouldAdapterHandle()) adapter->setLongParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setLongParam(paramPos,value);
    return;

}
void SqlGwStatement::setLongLongParam(int paramPos, long long value)
{
    if (adapter && shouldAdapterHandle()) adapter->setLongLongParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setLongLongParam(paramPos,value);
    return;
}
void SqlGwStatement::setByteIntParam(int paramPos, ByteInt value)
{
    if (adapter && shouldAdapterHandle()) adapter->setByteIntParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setByteIntParam(paramPos,value);
    return;
}
void SqlGwStatement::setFloatParam(int paramPos, float value)
{
    if (adapter && shouldAdapterHandle()) adapter->setFloatParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setFloatParam(paramPos,value);
    return;
}
void SqlGwStatement::setDoubleParam(int paramPos, double value)
{
    if (adapter && shouldAdapterHandle()) adapter->setDoubleParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setDoubleParam(paramPos,value);
    return;

}
void SqlGwStatement::setStringParam(int paramPos, char *value)
{
    if (adapter && shouldAdapterHandle()) adapter->setStringParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setStringParam(paramPos,value);
    return;
}
void SqlGwStatement::setDateParam(int paramPos, Date value)
{
    if (adapter && shouldAdapterHandle()) adapter->setDateParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setDateParam(paramPos,value);
    return;
}
void SqlGwStatement::setTimeParam(int paramPos, Time value)
{
    if (adapter && shouldAdapterHandle()) adapter->setTimeParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setTimeParam(paramPos,value);
    return;
}
void SqlGwStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    if (adapter && shouldAdapterHandle()) adapter->setTimeStampParam(paramPos, value);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setTimeStampParam(paramPos,value);
    return;
}
void SqlGwStatement::setBinaryParam(int paramPos, void *value, int length)
{
    if (adapter && shouldAdapterHandle()) adapter->setBinaryParam(paramPos, value, length);
    if (innerStmt && shouldCSqlHandle()) innerStmt->setBinaryParam(paramPos,value, length);
}
bool SqlGwStatement::isFldNull(int pos)
{
    if (adapter && shouldAdapterHandle()) return adapter->isFldNull(pos);
    if (innerStmt && shouldCSqlHandle()) return innerStmt->isFldNull(pos);

}
bool SqlGwStatement::isFldNull(char *name)
{
    if (adapter && shouldAdapterHandle()) return adapter->isFldNull(name);
    if (innerStmt && shouldCSqlHandle()) return innerStmt->isFldNull(name);

}
void SqlGwStatement::setNull(int pos)
{
    if (adapter && shouldAdapterHandle()) adapter->setNull(pos);
    if (innerStmt && shouldCSqlHandle()) innerStmt-> setNull(pos);
}
List SqlGwStatement::getAllTableNames(DbRetVal &ret)
{
    printf("in csql\n"); if (innerStmt) return innerStmt->getAllTableNames(ret);
    printf("in Target Db\n"); if (adapter) adapter->getAllTableNames(ret);
}
List SqlGwStatement::getAllUserNames(DbRetVal &ret)
{
    if (innerStmt) return innerStmt->getAllTableNames(ret);
    if (adapter) adapter->getAllTableNames(ret);
}

ResultSetPlan SqlGwStatement::getResultSetPlan()
{
   if (adapter && shouldAdapterHandle()) return adapter->getResultSetPlan();
   if (innerStmt && shouldCSqlHandle())  return innerStmt->getResultSetPlan();
   return Normal;
}
long long SqlGwStatement::getLastInsertedVal(DbRetVal &rv)
{
    if (innerStmt) return innerStmt->getLastInsertedVal(rv);
    if (adapter) return adapter->getLastInsertedVal(rv);
}

//Function for COMMIT according to its name DSN 
void SqlGwStatement::setToCommit(char *dsName)
{
   SqlGwConnection *conn = (SqlGwConnection*) con;
   struct MultiDSN *node = conn->multi_adapter_head; 
   while(node != NULL){
       if(strcmp(dsName,node->dsn)==0){
           node->toCommit=true;
           break;
       }
       node=node->next;
   }
}

 

