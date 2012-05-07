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
  ***************************************************************************/
#include <os.h>
#include <Statement.h>
#include <Info.h>
#ifndef MMDB
#include <TableConfig.h>
#endif
CreateTblStatement::CreateTblStatement()
{
    parsedData = NULL; 
    dbMgr = NULL; 
}

CreateTblStatement::~CreateTblStatement()
{
    tblDef.reset();
}
DbRetVal CreateTblStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    rv = dbMgr->createTable(tblName, tblDef);
    if (rv != OK) return rv;
    if (parsedData->getFieldNameList().size() > 0)
    {
        HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
        strcpy(idxInfo->tableName, tblName);
        ListIterator iter = parsedData->getFieldNameList().getIterator();
        FieldName *name = NULL;
        while (iter.hasElement())
        {
            name = (FieldName*)iter.nextElement();
            idxInfo->list.append(name->fldName);
        }
        idxInfo->indType = hashIndex;
        idxInfo->isPrimary = true;
        idxInfo->isUnique = true;
        int bucket = parsedData->getBucketSize();
        if(bucket!=0)
            idxInfo->bucketSize = bucket;
        char indName[IDENTIFIER_LENGTH];
        sprintf(indName, "%s_idx1_Primary", tblName);
        rv = dbMgr->createIndex(indName, idxInfo);
        if (rv != OK)
        {
            dbMgr->dropTable(tblName);
            delete idxInfo;
            return rv;
        }
        delete idxInfo;
    }
    if(parsedData->getSecondaryIndexFieldList().size() > 0)
    {
        HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
        strcpy(idxInfo->tableName, tblName);
        ListIterator iter = parsedData->getSecondaryIndexFieldList().getIterator();
        FieldInfo *name = NULL;
        while (iter.hasElement())
        {
            name = (FieldInfo*)iter.nextElement();
            idxInfo->list.append(name->fldName);
        }
        idxInfo->indType = treeIndex;
        idxInfo->isPrimary = true;
        idxInfo->isUnique = true;
        char indName[IDENTIFIER_LENGTH];
        sprintf(indName, "%s_idx_Auto_increment", tblName);
        rv = dbMgr->createIndex(indName, idxInfo);
        if (rv != OK)
        {
            dbMgr->dropTable(tblName);
            delete idxInfo;
            return rv;
        }
        delete idxInfo;
    }
    if(parsedData->getForeignKeyList().size() > 0)
    {
        ForeignKeyInfo *fkInfo=NULL;
        int i=0;
        ListIterator iter = parsedData->getForeignKeyList().getIterator();
        while (iter.hasElement())
        {
            fkInfo = (ForeignKeyInfo *)iter.nextElement();
            strcpy(fkInfo->fkTableName,tblName);
            char fkName[IDENTIFIER_LENGTH];
            sprintf(fkName, "%s_FKEY_%d", tblName,++i);
            rv = dbMgr->createForeignKey(fkName,fkInfo);
            if (rv != OK)
            {
                dbMgr->dropTable(tblName);
                return rv;
            }
        } 

    }
    return rv;
}
DbRetVal CreateTblStatement::checkForDot(char *name)
{
    int i=0;
    while ( name[i] != '\0')
    {
        if (name[i++] == '.') { return ErrSyntaxError; }
    }
    return OK;

}
DbRetVal CreateTblStatement::resolve()
{
    DbRetVal rv = OK;
    strcpy(tblName, parsedData->getTableName());
    rv = checkForDot(tblName);
    if ( rv!=OK ) 
    { 
          printf("Check SQL Syntax: .\n");
          return  rv;
    }
    FieldIterator iter = parsedData->getCreFldList().getIterator();

    int i = 0;
    FieldName *name = NULL;
    ListIterator nIter = parsedData->getFieldNameList().getIterator();
    while (iter.hasElement())
    {
        FieldDef *fDef = iter.nextElement();
        nIter.reset();
        while (nIter.hasElement())
        {
            name = (FieldName*)nIter.nextElement();
            if (strcmp(name->fldName, fDef->fldName_) == 0) fDef->isNull_ = true;
        }
        rv = checkForDot(fDef->fldName_);
        if ( rv!=OK )
        {
            printf("Check SQL Syntax: .\n");
            return  rv;
        }
        if (fDef->type_ == typeVarchar || fDef->type_ == typeString) {
            fDef->length_++;
            //varchar and char require \0 to be stored at the end
        }
        /* To check char field and restrict it for the max length 8kb(8000)  */
        if( (fDef->type_ == typeString) && (fDef->length_ > 8000) ){
            printError(ErrBadRange,"Char data type length should be less than 8kb(8000).");
            return ErrBadRange;
        }
        //TODO : need a new addField function which can take FieldDef as parameter.
       if (!fDef->isDefault_ || fDef->isDefault_ && fDef->defaultValueBuf_[0] == '\0')  {
           i = tblDef.addField(fDef->fldName_, fDef->type_, fDef->length_, 
                        NULL,fDef->isNull_,fDef->isAutoIncrement_);
       } else {
           i = tblDef.addField(fDef->fldName_, fDef->type_, fDef->length_, 
                        fDef->defaultValueBuf_,fDef->isNull_,fDef->isAutoIncrement_);
       }
       if( 0 != i )
       {
          printError(ErrUnknown, "Error while adding field");
          rv = ErrUnknown;
          break;
       }
    }
    return rv;
}
/////////////////////////////////////
DbRetVal CacheTblStatement::resolve()
{
    DbRetVal rv = OK;
#ifndef MMDB
    TableConf::config.init();
    cacheLoader.setConnParam(I_USER, I_PASS);
    cacheLoader.setTable(parsedData->getTableName());
    TableConf::config.setTable(parsedData->getTableName());
    if(parsedData->getHCondFld()){
        cacheLoader.setCondition(parsedData->getHCondition());// new one
        TableConf::config.setCondition(parsedData->getHCondition());
    }
    if(parsedData->getVCondFld()) {
        cacheLoader.setFieldListVal(parsedData->getVCondition());
        TableConf::config.setFieldListVal(parsedData->getVCondition());
    }
    if(parsedData->getPkFld()){
        cacheLoader.setFieldName(parsedData->getIndexName());
        TableConf::config.setFieldName(parsedData->getIndexName());
    }
    if(parsedData->getDSN()){
        cacheLoader.setDsnName(parsedData->getPKTableName());
        TableConf::config.setDsnName(parsedData->getPKTableName());
    }
    if( !(parsedData->getUnCache()))
    {
        rv = TableConf::config.isTableCached(parsedData->getTableName());
        if(rv == OK){
           printError(ErrAlready, "Table is already cached,unload table then try");
           return ErrAlready;
        }
    }
#endif
    return OK;
}
DbRetVal CacheTblStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
#ifndef MMDB
    if( parsedData->getUnCache())
    {
        unsigned int mode = 
                    TableConf::config.getTableMode(parsedData->getTableName());
        bool isCached = TableConf::config.isTableCached(mode);
        if (!isCached) {
            printError(ErrNotCached, "Table is not Cached");
            return ErrNotCached;
        }
        TableConf::config.removeFromCacheTableFile();
    } else {
        rv = cacheLoader.load(!(parsedData->getNoSchema()));
        if(rv == OK){
            TableConf::config.addToCacheTableFile(parsedData->getDirect());
        } else return rv;
    }
#endif
    return OK;
}
///////////////////////////////////////
CreateIdxStatement::CreateIdxStatement()
{
    parsedData = NULL; 
    dbMgr = NULL; 
}

CreateIdxStatement::~CreateIdxStatement()
{

}

DbRetVal CreateIdxStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    if (parsedData->getFieldNameList().size() > 0)
    {
        HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
        strcpy(idxInfo->tableName, parsedData->getTableName());
        ListIterator iter = parsedData->getFieldNameList().getIterator();
        FieldName *name = NULL;
        while (iter.hasElement())
        {
            name = (FieldName*)iter.nextElement();
            idxInfo->list.append(name->fldName);
        }
        idxInfo->indType = parsedData->getIndexType();
        idxInfo->isPrimary = parsedData->getPrimary();
        idxInfo->isUnique = parsedData->getUnique();
        int bucket = parsedData->getBucketSize();
        if(bucket!=0)
            idxInfo->bucketSize = bucket;
        rv = dbMgr->createIndex(parsedData->getIndexName(), idxInfo);
        delete idxInfo;
    }
    if (rv == OK) dbMgr->sendSignal(SIGCSQL1);
    return rv;
}

// function for not to drop cached table
DbRetVal isTableCached(char *tabName) // function added by :Jitendra
{
       
    DbRetVal rv =OK;
    FILE *fp;
    if (!Conf::config.useCache()) return OK;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if(fp==NULL) return OK;
    char tablename[IDENTIFIER_LENGTH]; tablename[0] = '\0';
    char condition[IDENTIFIER_LENGTH]; condition[0]='\0';
    char fieldname[IDENTIFIER_LENGTH]; fieldname[0]='\0';
    char field[IDENTIFIER_LENGTH];  field[0]='\0';
    char dsnName[IDENTIFIER_LENGTH]; dsnName[0]='\0';
    int mode;
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %s %s %s\n",&mode,tablename,fieldname,condition,field,dsnName);
        if(strcmp(tablename,tabName) ==0){
        fclose(fp);
        return ErrNoPrivilege;}
    }
    fclose(fp);
    return rv;
}      

DbRetVal DropTblStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK; // newly added
    char *tab;
    tab = parsedData->getTableName();

    DatabaseManagerImpl *dmgr = (DatabaseManagerImpl *)dbMgr;
    IsolationLevel iso = dmgr->txnMgr()->getIsoLevel();
    rv = dmgr->txnMgr()->rollback(dmgr->lockMgr());
    rv = dmgr->txnMgr()->startTransaction(dmgr->lockMgr(),iso);    
#ifndef MMDB    
    int mode = TableConf::config.getTableMode(tab);
//    rv = isTableCached(tab);
    if (mode != 0 && mode < 8) {
	    printf("Cached table '%s' cannot be dropped.\n", tab);
        printf("uncache the table by 'cachetable -t %s -u' and drop.\n", tab);
	    printError(ErrNoPrivilege, "Cached table '%s' cannot be dropped.", tab);
        return ErrNoPrivilege;
    } 
    else if (mode == 8) {
        printf("Replicated table '%s' cannot be dropped.\n", tab);
        printf("Unreplicate the table by 'repltable -t %s -u' and drop.\n", tab);
        printError(ErrNoPrivilege, "Replicated table '%s' cannot be dropped.", tab);
        return ErrNoPrivilege;
    }
    else if (mode > 8) {
        printf("Table %s is cached and replicated. Cannot be dropped.\n", tab);
        printf("Uncache the table by 'cachetable -t %s -u'.\n", tab);
        printf("Unreplicated the table by 'repltable -t %s -u' and drop.\n", tab);   
        printError(ErrNoPrivilege, "Table %s is cached and replicated. Cannot be dropped.", tab);
        return ErrNoPrivilege;
    }
#endif

	if (!usrMgr->isAuthorized(PRIV_DROP, tab))
	{
		printError(ErrNoPrivilege, "You are not allowed to DROP table %s", tab);
		return ErrNoPrivilege;
	}

    rv = dbMgr->dropTable(parsedData->getTableName());
    if (rv == OK) dbMgr->sendSignal(SIGCSQL1);
    return rv;
}

DbRetVal DropIdxStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    DatabaseManagerImpl *dmgr = (DatabaseManagerImpl *)dbMgr;
    IsolationLevel iso = dmgr->txnMgr()->getIsoLevel();
    rv = dmgr->txnMgr()->rollback(dmgr->lockMgr());
    rv = dmgr->txnMgr()->startTransaction(dmgr->lockMgr(),iso);
    rv = dmgr->dropIndex(parsedData->getIndexName());
    if (rv == OK) dbMgr->sendSignal(SIGCSQL1);
    return rv;
}

//================== Truncate Table Statement ===============


DbRetVal TruncateTblStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    table->setCondition(NULL);
    IsolationLevel level = ((DatabaseManagerImpl*)dbMgr)->txnMgr()->getIsoLevel();
    rv=((DatabaseManagerImpl*)dbMgr)->txnMgr()->commit(((DatabaseManagerImpl*)dbMgr)->lockMgr());
    if (rv != OK) return rv;
    rv=((DatabaseManagerImpl*)dbMgr)->txnMgr()->startTransaction(((DatabaseManagerImpl*)dbMgr)->lockMgr(),level);
    if (rv != OK) return rv;

    rv = table->execute();
    if (rv != OK) return rv;
    rowsAffected = 0;
    table->setLoading(true);
    void *tuple;
    while(true)
    {
        tuple = (char*)table->fetchNoBind(rv);
        if (rv != OK) break;
        if (tuple == NULL) {break;}
        rv = table->deleteTuple();
        if (rv != OK) break;
        rowsAffected++;
    }
    table->closeScan();
    return rv;
}
DbRetVal TruncateTblStatement::resolve()
{
   DbRetVal rv = OK;
   table = dbMgr->openTable(parsedData->getTableName());
    if (table == NULL)
    {
        printError(ErrNotExists, "Unable to open the table:Table not exists");
        return ErrNotExists;
    }

	if (!usrMgr->isAuthorized(PRIV_DELETE, table->getId()))
	{
		printError(ErrNoPrivilege, "Permission denied");
		return ErrNoPrivilege;
	}

    return rv;
}





//================== Compact Table Statement===================
DbRetVal CompactTblStatement::resolve()
{
    DbRetVal rv = OK;
    table = dbMgr->openTable(parsedData->getTableName());
    if (table == NULL)
    {
        printError(ErrNotExists, "Unable to open the table:Table not exists");
        return ErrNotExists;
    }
    return OK;
}
DbRetVal CompactTblStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    rv = table->compact();
    dbMgr->closeTable(table);
    return rv;
}
DbRetVal UserTblStatement::resolve()
{
    uType = parsedData->getUserType();
    if( uType == CREATEUSER || uType == DROPUSER || (uType == ALTERUSER && strcmp(userName,parsedData->getUserName())!=0))
    {
       if(strcmp(userName,"root")!=0)
       {
           printError(ErrNoPrivilege,"Permission Denied. Login as root");
           return ErrNoPrivilege;
       }else if(uType == DROPUSER && strcmp(parsedData->getUserName(),"root")==0)
       {
            printError(ErrNoPrivilege,"Permission Denied. root user cannot be deleted");
            return ErrNoPrivilege;
       }
    }
    return OK;
}
DbRetVal UserTblStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    if( uType == CREATEUSER){
       rv =(DbRetVal) usrMgr->createUser(parsedData->getUserName(), parsedData->getPassWord());
    }else if(uType == DROPUSER){
       rv =(DbRetVal) usrMgr->deleteUser(parsedData->getUserName());
    }else{
       rv =(DbRetVal) usrMgr->changePassword(parsedData->getUserName(), parsedData->getPassWord());
    }
    return rv;
}

