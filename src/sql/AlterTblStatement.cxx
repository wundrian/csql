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
#include <TableImpl.h>

AlterTblStatement::AlterTblStatement()
{
    bindFieldValues = NULL;
    table = NULL;
    totalFields = 0 ; 
}

AlterTblStatement::~AlterTblStatement()
{
    if (table) { table->close(); table = NULL; }
    if(totalFields){
       for(int i=0;i<totalFields;i++)
       {
           free(bindFieldValues[i]);    
       }
       free(bindFieldValues); bindFieldValues = NULL;
    }
}

DbRetVal AlterTblStatement::resolve()
{
    DbRetVal rv = OK;
    altType = parsedData->getAlterType();
    if(altType == ALTERMODIFY)
    {
      printError(ErrUnknown, " NOT Done \n");
      return ErrUnknown;
    }
    rv = resolveForAddDropColumn();
    return rv;
}

DbRetVal AlterTblStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    DatabaseManagerImpl *dmgr = (DatabaseManagerImpl *)dbMgr;
    IsolationLevel iso = dmgr->txnMgr()->getIsoLevel();
    rv = dmgr->txnMgr()->rollback(dmgr->lockMgr());
    rv = dmgr->txnMgr()->startTransaction(dmgr->lockMgr(),iso);

    if( altType == ALTERTABLERENAME)
    {
       rv = dbMgr->renameTable(parsedData->getTableName(), parsedData->getIndexName());
       return rv;
    }else if( altType == ALTERFIELDRENAME)
    {
        if (strcmp(parsedData->getIndexName(),parsedData->getPKTableName())==0)
            return OK;
       rv = dbMgr->renameField(parsedData->getTableName(), parsedData->getIndexName(),parsedData->getPKTableName());
       return rv;
    }else if(ALTERINDEXRENAME == altType){
        rv = dbMgr->renameIndex(parsedData->getTableName(), parsedData->getIndexName());
        return rv;
    }
    rv = executeForAddDropColumn(rowsAffected);
    return rv;
}

DbRetVal AlterTblStatement::resolveForAddDropColumn()
{
    DbRetVal rv = OK;
    if( altType == ALTERTABLERENAME || altType == ALTERFIELDRENAME || altType == ALTERINDEXRENAME) return OK;
    table = dbMgr->openTable(parsedData->getTableName());
    if (table == NULL)
    {
        printError(ErrNotExists, "Unable to open the table:Table not exists");
        return ErrNotExists;
    }
    List fNameList = table->getFieldNameList();
    FieldList extraFldList = parsedData->getCreFldList() ; 
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    int fcount = 1; void *valBuf; int ret=0;
    Identifier *elem = NULL;
    noOfOldTabFld = fNameList.size();
    totalFields = noOfOldTabFld + extraFldList.size();
    bindFieldValues = (void**) malloc( totalFields * sizeof(char*));
    memset(bindFieldValues, 0, totalFields * sizeof(char*)); 
    char fldName[IDENTIFIER_LENGTH];
    int i = 1;
    while (fNameIter.hasElement())
    {
        elem = (Identifier*) fNameIter.nextElement();
        table->getFieldInfo((const char*)elem->name, info);
        Table::getFieldNameAlone(elem->name,fldName);
        //TODO :: Should free
        valBuf = AllDataType::alloc(info->type, info->length);
        table->bindFld(elem->name, valBuf);
        if(altType == ALTERDROP && 0 == strcmp(parsedData->getIndexName(),fldName)){
            bindFieldValues[totalFields-i] = valBuf; //Store Last
            i--;
        }
        else { 
            bindFieldValues[fcount-1] = valBuf;
            if (info->type == typeVarchar || info->type == typeString)
                info->length++;

            ret = tblDef.addField(fldName,info->type, info->length, info->defaultValueBuf, info->isNull, info->isAutoIncrement);
            if( 0 != ret )
            {
                printError(ErrUnknown, "Error while adding field");
                rv = ErrUnknown;
                break;
            }
            fcount++;
        }
    }
    fNameIter.reset();
    while (fNameIter.hasElement())
    {
        delete (Identifier*) fNameIter.nextElement();
    }
    fNameList.reset();
    if(altType == ALTERDROP)
    {
        delete info;
        return rv;
    }
    FieldIterator iter = extraFldList.getIterator();
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
        if (fDef->type_ == typeVarchar || fDef->type_ == typeString) {
            fDef->length_++;
            //varchar and char require \0 to be stored at the end
        }
        if (!fDef->isDefault_ || fDef->isDefault_ && fDef->defaultValueBuf_[0] == '\0')  {
           ret = tblDef.addField(fDef->fldName_, fDef->type_, fDef->length_,
                        NULL,fDef->isNull_,fDef->isAutoIncrement_);
         } else {
            ret = tblDef.addField(fDef->fldName_, fDef->type_, fDef->length_,
                        fDef->defaultValueBuf_,fDef->isNull_,fDef->isAutoIncrement_);
         }
         if( 0 != ret )
         {
             printError(ErrUnknown, "Error while adding field");
             rv = ErrUnknown;
             break;
       }
       valBuf = AllDataType::alloc(fDef->type_, fDef->length_);
       bindFieldValues[fcount-1] = valBuf;       
    }
    delete info;
    return rv;
}

DbRetVal AlterTblStatement::executeForAddDropColumn(int &rowsAffected)
{
    DbRetVal rv = OK;
    char tblName[IDENTIFIER_LENGTH];
    sprintf(tblName,"%s_temp",parsedData->getTableName());
    rv = dbMgr->createTable(tblName, tblDef);
    if (rv != OK) return rv;
    rv = createIndex(parsedData->getTableName(),tblName);
    if (rv != OK){ 
        dbMgr->dropTable(tblName);
        return rv;
    }
    //TODO:Create Foreign Key Info
    Table *tempTable = dbMgr->openTable(tblName);
    List fNameList = tempTable->getFieldNameList();
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    int fcount = 1; void *valBuf; 
    Identifier *elem = NULL;
    while (fNameIter.hasElement())
    {
        elem = (Identifier*) fNameIter.nextElement();
        tempTable->getFieldInfo((const char*)elem->name, info);
        valBuf = bindFieldValues[fcount-1];
        tempTable->bindFld(elem->name, valBuf);
        fcount++;
    }
    table->setCondition(NULL);
    rv = table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(tempTable);
       dbMgr->dropTable(tblName);     
       return rv;
    }
    void *tuple = NULL;
    while(true)
    {
        int extraField = totalFields - noOfOldTabFld;
        tuple = (char*)table->fetch();
        if (tuple == NULL) {break;}
        int i=1;
        while(extraField--)
        {
            tempTable->markFldNull(noOfOldTabFld+i);
            i++;
        }
        rv = tempTable->insertTuple();
        if (rv != OK) break;
    }
    if (rv != OK){
       dbMgr->closeTable(tempTable);
       dbMgr->dropTable(tblName);
       return rv;
    }
    char tblName1[IDENTIFIER_LENGTH];
    sprintf(tblName1,"%s_temp2",parsedData->getTableName());
    rv = dbMgr->renameTable(parsedData->getTableName(),tblName1);
    if (rv != OK){
       dbMgr->closeTable(tempTable);
       dbMgr->dropTable(tblName);
       return rv;
    }
    rv = dbMgr->renameTable(tblName,parsedData->getTableName());
    if (rv != OK){
       dbMgr->renameTable(tblName1,parsedData->getTableName());
       dbMgr->closeTable(tempTable);
       dbMgr->dropTable(tblName);
       return rv;
    }
    rv = dbMgr->dropTable(tblName1);
    if (rv != OK){
       dbMgr->renameTable(tblName1,parsedData->getTableName());
       dbMgr->closeTable(tempTable);
       dbMgr->dropTable(tblName);
       return rv;
    }
    return rv;
}
DbRetVal AlterTblStatement::createIndex(const char *oldName,const char *newName)
{
    DbRetVal rv=OK;
    CatalogTableINDEXFIELD cIndexField(((DatabaseManagerImpl *)dbMgr)->sysDb());
    ListIterator iter = cIndexField.getIndexListIterater((char*)oldName);
    IndexInfoForDriver *info=NULL;
    char name[IDENTIFIER_LENGTH]="";
    char indName[IDENTIFIER_LENGTH]="";
    char tempIndexName[IDENTIFIER_LENGTH] ="";
    sprintf(tempIndexName, "%s_idx1_Primary", oldName);
    bool shouldCreateIndex = false;
    bool isFirstEntry=true;
    HashIndexInitInfo *idxInfo = NULL, *indexInfo2 = NULL;
    while(iter.hasElement())
    {
        if(shouldCreateIndex)
        {
            if(idxInfo->isPrimary && 0 == strcmp(info->indexName,tempIndexName))
                sprintf(indName, "%s_idx1_Primary", newName);
            rv = dbMgr->createIndex(indName, idxInfo);
            if (rv != OK)
            {
                delete idxInfo;
                return rv;
            }
            delete idxInfo;
            shouldCreateIndex = false;
            idxInfo = NULL;
        }
        info = (IndexInfoForDriver *) iter.nextElement();
        if((0 == strcmp(info->indexName,indName)))
        {
           if(idxInfo) idxInfo->list.append(info->fieldName);
           else printf("should not happen\n");
        }else{
            idxInfo = new HashIndexInitInfo();
            strcpy(idxInfo->tableName, newName);
            strcpy(indName,info->indexName);
            if(!isFirstEntry)shouldCreateIndex =true;
            isFirstEntry = false;
            idxInfo->indType =(IndexType) info->type;
            idxInfo->isPrimary = info->isPrimary ;
            idxInfo->isUnique = info->isUnique;
            idxInfo->list.append(info->fieldName);            
        }
    }
    if (idxInfo == NULL) return OK;
    if(idxInfo->isPrimary && 0 == strcmp(info->indexName,tempIndexName))
         sprintf(indName, "%s_idx1_Primary", newName);
    rv = dbMgr->createIndex(indName, idxInfo);
    if (rv != OK)
    {
         delete idxInfo;
         return rv;
    }
    delete idxInfo;
    return OK;
}


DbRetVal AlterTblStatement::resolveForModifyColumn()
{
    DbRetVal rv = OK;
    return rv;
}
