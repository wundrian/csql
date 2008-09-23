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
#include "Statement.h"
#include <Info.h>
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
 
        char indName[IDENTIFIER_LENGTH];
        sprintf(indName, "%s_idx1_Primary", tblName);
        rv = dbMgr->createIndex(indName, idxInfo);
        delete idxInfo;
    }
    return rv;
}

DbRetVal CreateTblStatement::resolve()
{
    DbRetVal rv = OK;
    strcpy(tblName, parsedData->getTableName());
    FieldIterator iter = parsedData->getCreFldList().getIterator();
    FieldDef fDef; 

    int i = 0;
    FieldName *name = NULL;
    ListIterator nIter = parsedData->getFieldNameList().getIterator();
    while (iter.hasElement())
    {
        fDef = iter.nextElement();
        nIter.reset();
        while (nIter.hasElement())
        {
            name = (FieldName*)nIter.nextElement();
            if (strcmp(name->fldName, fDef.fldName_) == 0) fDef.isNull_ = true;
        }


       //TODO : need a new addField function which can take FieldDef as parameter.
       if (!fDef.isDefault_)  {
           i = tblDef.addField(fDef.fldName_, fDef.type_, fDef.length_, 
                        NULL,fDef.isNull_);
       } else {
           i = tblDef.addField(fDef.fldName_, fDef.type_, fDef.length_, 
                        fDef.defaultValueBuf_,fDef.isNull_);
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
        rv = dbMgr->createIndex(parsedData->getIndexName(), idxInfo);
        delete idxInfo;
    }
    return rv;
}

// function for not to drop cached table
DbRetVal isTableCached(char *tabName) // function added by :Jitendra
{
       
    DbRetVal rv =OK;
    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if(fp==NULL)
    {
        printError(ErrSysInit, "csqltable.conf file does not exist");
        return ErrSysInit;
    }
    char tablename[IDENTIFIER_LENGTH];
      tablename[0] = '\0';
    char condition[IDENTIFIER_LENGTH];
      condition[0]='\0';
    int mode;
    while(!feof(fp))
    {
        fscanf(fp,"%d:%s %s\n",&mode,tablename,condition);
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
    
    rv = isTableCached(tab);
    if(rv !=OK)
    {
	printf("cached table can't be dropped,Table can be unloaded by \"cachetable -t <tableName> -u\"\n");
        return ErrNoPrivilege;
    } // upto this
    rv = dbMgr->dropTable(parsedData->getTableName());
    return rv;
}

DbRetVal DropIdxStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    rv = dbMgr->dropIndex(parsedData->getIndexName());
    return rv;
}

