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
#include <OrderTableImpl.h>


ListIterator MetadataStatement::getExportKeyIterator()
{
    List datalist;
    TableImpl *tbl = (TableImpl*)table;
    if(!tbl->isPkTbl)
    {
       return datalist.getIterator();
    }else
    {
       TableImpl *fkTbl =NULL;
       ListIterator tblIter =tbl->tblFkList.getIterator();
       tblIter.reset();
       void *tPkptr =NULL;
       void *tFkptr = NULL;
       void *chunkPk = NULL;
       char *pkFldName = NULL;
       char *fkFldName = NULL;
       ForeignKeyMetadata *fkMeta= NULL;
       while (tblIter.hasElement()){
           fkTbl = (TableImpl *) tblIter.nextElement();
           FieldNameList pkFieldList,fkFieldList;
           CatalogTableTABLE cTable(tbl->sysDB_);
           cTable.getChunkAndTblPtr(tbl->getName(), chunkPk, tPkptr);
           cTable.getChunkAndTblPtr(fkTbl->getName(), chunkPk, tFkptr);
           CatalogTableFK cFk(tbl->sysDB_);
           cFk.getPkFkFieldInfo(tPkptr,tFkptr,pkFieldList,fkFieldList);
           pkFieldList.resetIter();
           fkFieldList.resetIter();      
           int count = 0;  
           while((fkFldName = fkFieldList.nextFieldName())!= NULL)
           {
               count++;
               fkMeta = new ForeignKeyMetadata();
               pkFldName = pkFieldList.nextFieldName();
               strcpy(fkMeta->pkTableName,tbl->getName());
               strcpy(fkMeta->pkColName,pkFldName);
               strcpy(fkMeta->fkTableName,fkTbl->getName());
               strcpy(fkMeta->fkColName,fkFldName);
               fkMeta->keySeq = count;
               fkMeta->updateRule = 3;
               fkMeta->deleteRule = 3;
               datalist.append(fkMeta);
           }

        }
    }
    return datalist.getIterator();
}

ListIterator MetadataStatement::getImportKeyIterator()
{
    List datalist;
    TableImpl *tbl = (TableImpl*)table;
    if(!tbl->isFkTbl)
    {
       return datalist.getIterator();
    }else
    {
       TableImpl *fkTbl =NULL;
       ListIterator tblIter = tbl->tblList.getIterator();
       tblIter.reset();
       void *tPkptr =NULL;
       void *tFkptr = NULL;
       void *chunkPk = NULL;
       char *pkFldName = NULL;
       char *fkFldName = NULL;
       ForeignKeyMetadata *fkMeta= NULL;
       while (tblIter.hasElement()){
           fkTbl = (TableImpl *) tblIter.nextElement();
           FieldNameList pkFieldList,fkFieldList;
           CatalogTableTABLE cTable(tbl->sysDB_);
           cTable.getChunkAndTblPtr(tbl->getName(), chunkPk, tPkptr);
           cTable.getChunkAndTblPtr(fkTbl->getName(), chunkPk, tFkptr);
           CatalogTableFK cFk(tbl->sysDB_);
           cFk.getPkFkFieldInfo(tFkptr,tPkptr,fkFieldList,pkFieldList);
           pkFieldList.resetIter();
           fkFieldList.resetIter();
           int count = 0;
           while((pkFldName = pkFieldList.nextFieldName())!= NULL)
           {
               count++;
               fkMeta = new ForeignKeyMetadata();
               fkFldName = fkFieldList.nextFieldName();
               strcpy(fkMeta->pkTableName,fkTbl->getName());
               strcpy(fkMeta->pkColName,fkFldName);
               strcpy(fkMeta->fkTableName,tbl->getName());
               strcpy(fkMeta->fkColName,pkFldName);
               fkMeta->keySeq = count;
               fkMeta->updateRule = 3;
               fkMeta->deleteRule = 3;
               datalist.append(fkMeta);
           }

        }
    }
    return datalist.getIterator();
}


MetadataStatement::MetadataStatement()
{
    parsedData = NULL; 
    dbMgr = NULL; 
    table = NULL;
    params = NULL;
    paramValues = NULL;
    totalParams = 0;
    bindFields = NULL;
    bindFieldValues = NULL;
    totalFields = 0;
    plan = Normal;
    numRecords = 0;
    isPlanFreed=false;
    isSecondFetch=false;
}

MetadataStatement::~MetadataStatement()
{
    close();
    if (table) { table->close(); table = NULL; }
    if (totalParams) {
        free(params);
        params =  NULL;
        free(paramValues);
        paramValues = NULL;
    }
    if (totalFields)
    {
        free(bindFields);
        bindFields =  NULL;
        free(bindFieldValues);
        bindFieldValues = NULL;

    }
}
DbRetVal MetadataStatement::getParamFldInfo(int paramNo, FieldInfo *&info)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    ConditionValue *cValue = (ConditionValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    table->getFieldNameAlone(cValue->fName,info->fldName);
    info->type = cValue->type;
    info->length = cValue->length;
    info->isNull = cValue->isNullable;
    return OK;
}
DbRetVal MetadataStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    switch( plan )
    {
      case GetTables: 
      {
           dataListIter = dbMgr->getAllTableNames().getIterator();
           break;
      }
      case GetColumns:
      {
            List colList;
            List fNameList = table->getFieldNameList();
            ListIterator fNameIter = fNameList.getIterator();
            for (int i = 0; i < fNameList.size() ; i++)
            {
                 FieldInfo *fInfo = new FieldInfo();
                 Identifier *elem= (Identifier*)fNameIter.nextElement();
                 char *fName = elem->name;
                 rv = table->getFieldInfo(fName, fInfo);
                 if (ErrNotFound == rv || ErrNotExists == rv)
                 {
                     delete fInfo;
                     fNameList.reset();
                     printError(ErrSysFatal, "Should never happen.");
                     return ErrSysFatal;
                 }
                 delete elem;
                 colList.append(fInfo);
             }
             fNameIter.reset();
             fNameList.reset();
             dataListIter = colList.getIterator();
           break;
      }
      case GetIndexes:
      {
           List colList;
           CatalogTableINDEXFIELD cIndexField(((DatabaseManagerImpl *)dbMgr)->sysDb());
           dataListIter = cIndexField.getIndexListIterater(table->getName());
           break;
      }
      case GetPriIndex:
      {
          List colList;
          CatalogTableINDEXFIELD cIndexField(((DatabaseManagerImpl *)dbMgr)->sysDb());
          dataListIter = cIndexField.getIndexListIterater(table->getName());
          break;
      }
      case GetImportKey:
      {
          dataListIter = getImportKeyIterator();
          break;
      }
      case GetExportKey:
      {
          dataListIter = getExportKeyIterator(); 
          break;
      }
      case GetDataType:
      {
          dataListIter = getDataTypeInfoIterator(); 
          break;
      }
      default:
          break;
    };
    return rv;
}

DbRetVal MetadataStatement::openTables()
{
//TODO : need to remove unnecessery code
    if (dbMgr == NULL) return ErrNoConnection;
    JoinTableImpl *jHdl = NULL;
    Table *tHdl = NULL, *prevHdl = NULL;
    bool joinInvolved = false;
    //check whether all the table exists
    ListIterator titer = parsedData->getTableNameList().getIterator();
    ListIterator jiter = parsedData->getJoinTypeList().getIterator();
    while (titer.hasElement())
    {
        TableName *t  = (TableName*)titer.nextElement();
        parsedData->setTableName(t->tblName);        
        tHdl = dbMgr->openTable(t->tblName);
        if ( NULL == tHdl ) 
        {
            printError(ErrNotExists, 
                       "Unable to open the table:Table not exists");
            if (prevHdl) delete prevHdl;
            return ErrNotExists;
        }
        TableImpl *tImpl=  (TableImpl*) tHdl;
        if (NULL != prevHdl) 
        { 
            joinInvolved = true;
            jHdl = new JoinTableImpl();
            jHdl->setTable(prevHdl, tHdl);
            JoinTypeNode *node = (JoinTypeNode*) jiter.nextElement();
            if (node == NULL) {
                printError(ErrSyntaxError, 
                           "Join Type and number of tables do not match");
                delete jHdl;
                return ErrSyntaxError;
            }
            jHdl->setJoinType(node->jType);
            prevHdl = jHdl;
            continue;
        }
        prevHdl = tHdl;
    }

    if (joinInvolved) table = jHdl; else table = tHdl;
    return OK;
}
DbRetVal MetadataStatement::resolve()
{
    DbRetVal rv =OK;
    plan = parsedData->getResultSetPlan();
    switch(plan)
    {
        case GetTables:
        {
            bindFields = (FieldValue**) malloc (5 * sizeof(FieldValue*));
            bindFieldValues = (char**) malloc  (5 * sizeof(char*));
            for(int i=0;i<5;i++){
                FieldValue *newVal = new FieldValue();
                if(i==0)  strcpy(newVal->fldName,"TABLE_CAT");
                if(i==1)  strcpy(newVal->fldName,"TABLE_SCHEM");
                if(i==2)  strcpy(newVal->fldName,"TABLE_NAME");
                if(i==3)  strcpy(newVal->fldName,"TABLE_TYPE");
                newVal->parsedString = NULL;
                newVal->paramNo = 0;
                newVal->type = typeString;
                newVal->length = 64;
                newVal->value = AllDataType::alloc(newVal->type, 64);
                if(i==0) strcpy((char*)newVal->value,(char*)"CSQL");
                if(i==1) strcpy((char*)newVal->value,(char*)"CSQL");
                if(i==3) strcpy((char*)newVal->value,(char*)"TABLE");
                if(i==4) strcpy((char*)newVal->value,(char*)"TABLE Catalog");
                newVal->isAllocVal=true;
                totalFields =i+1;
                bindFields[i] = newVal;
            }
            break;
        }
        case GetColumns:
        {
            rv = openTables();
            if (rv != OK)  break; //return rv;
            bindFields = (FieldValue**) malloc (23 * sizeof(FieldValue*));
            bindFieldValues = (char**) malloc  (23 * sizeof(char*));
            for(int i=0;i<23;i++){
                FieldValue *newVal = new FieldValue();
                switch(i){
                    case 0:
                        strcpy(newVal->fldName,"TABLE_CAT");
                        newVal->type = typeString;
                        break;
                    case 1:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"TABLE_SCHEM");
                        break;
                    case 2:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"TABLE_NAME");
                        break;
                    case 3:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"COLUMN_NAME");
                        break;
                    case 4:
                        newVal->type = typeInt;
                        strcpy(newVal->fldName,"DATA_TYPE");
                        break;
                    case 5:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"TYPE_NAME");
                        break;
                    case 6:
                        newVal->type = typeInt;
                        strcpy(newVal->fldName,"COLUMN_SIZE");
                        break;
                    case 7:
                        newVal->type = typeInt;
                        strcpy(newVal->fldName,"BUFFER_LENGTH");
                        break;
                    case 8:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"DECIMAL_DIGITS");
                        break;
                    case 9:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"NUM_PREC_RADIX");
                        break;
                    case 10:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"NULLABLE");
                        break;
                    case 11:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"REMARKS");
                        break;
                    case 12:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"COLUMN_DEF");
                        break;
                    case 13:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"SQL_DATA_TYPE");
                        break;
                    case 14:
                        newVal->type = typeInt;
                        strcpy(newVal->fldName,"SQL_DATETIME_SUB");
                        break;
                    case 15:
                        newVal->type = typeInt;
                        strcpy(newVal->fldName,"CHAR_OCTET_LENGTH");
                        break;
                    case 16:
                        newVal->type = typeInt;
                        strcpy(newVal->fldName,"ORDINAL_POSITION");
                        break;
                    case 17:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"IS_NULLABLE");
                        break;
                    case 18:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"SCOPE_CATLOG");
                        break;
                    case 19:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"SCOPE_SCHEMA");
                        break;
                    case 20:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"SCOPE_TABLE");
                        break;
                    case 21:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"SOURCE_DATA_TYPE");
                        break;
                    case 22:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"IS_AUTOINCREMENT");
                        break;
                    default:
                        newVal->type = typeString;
                        break;
                };
                newVal->parsedString = NULL;
                newVal->paramNo = 0;
                newVal->length = AllDataType::size(newVal->type, 64);
                if(i==12)  newVal->length = DEFAULT_VALUE_BUF_LENGTH; 
                newVal->value = AllDataType::alloc(newVal->type,newVal->length);
                if(newVal->type == typeInt) (*(int*)newVal->value) = 0;
                if(newVal->type == typeShort) (*(short*)newVal->value) = 0;
                if(newVal->type == typeString) strcpy((char*)newVal->value,(char*)"");
                if(i==0) strcpy((char*)newVal->value,(char*)"CSQL");
                if(i==1) strcpy((char*)newVal->value,(char*)"CSQL");
                if(i==2) strcpy((char*)newVal->value,(char*)table->getName());
                if(i==11) strcpy((char*)newVal->value,(char*)"Columns Catalog");
              //  if(i==16) (*(int *)newVal->value) = 0;
                newVal->isAllocVal=true;
                totalFields =i+1;
                bindFields[i] = newVal;
            }
            break;
        }
        case GetIndexes:
        {
            rv = openTables();
            if (rv != OK)  break; //return rv;
            bindFields = (FieldValue**) malloc (13 * sizeof(FieldValue*));
            bindFieldValues = (char**) malloc  (13 * sizeof(char*));
            for(int i=0;i<13;i++){
                FieldValue *newVal = new FieldValue();
                switch(i)
                {
                    case 0:
                        strcpy(newVal->fldName,"TABLE_CAT");
                        newVal->type = typeString;
                        break;
                    case 1:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"TABLE_SCHEM");
                        break;
                    case 2:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"TABLE_NAME");
                        break;
                    case 3:
                        newVal->type = typeInt;
                        strcpy(newVal->fldName,"NON_UNIQUE");
                        break;
                    case 4:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"INDEX_QUALIFIER");
                        break;
                    case 5:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"INDEX_NAME");
                        break;
                    case 6:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"TYPE");
                        break;
                    case 7:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"ORDINAL_POSITION");
                        break;
                    case 8:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"COLUMN_NAME");
                        break;
                    case 9:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"ASC_OR_DESC");
                        break;
                    case 10:
                        newVal->type = typeInt;
                        strcpy(newVal->fldName,"CARDINALITY");
                        break;
                    case 11:
                        newVal->type = typeInt;
                        strcpy(newVal->fldName,"PAGES");
                        break;
                    case 12:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"FILTER_CONDITION");
                        break;
                    default:
                        newVal->type = typeString;
                        break;
                };
                newVal->parsedString = NULL;
                newVal->paramNo = 0;
                newVal->length = AllDataType::size(newVal->type, 64);
                newVal->value = AllDataType::alloc(newVal->type,newVal->length);
                if(newVal->type == typeString) strcpy((char*)newVal->value,(char*)"");
                if(i==0) strcpy((char*)newVal->value,(char*)"CSQL");
                if(i==1) strcpy((char*)newVal->value,(char*)"CSQL");
                newVal->isAllocVal=true;
                totalFields =i+1;
                bindFields[i] = newVal;
            }
            break;
        }
        case GetPriIndex:
        {
            rv = openTables();
            if (rv != OK)  break; //return rv;
            bindFields = (FieldValue**) malloc (6 * sizeof(FieldValue*));
            bindFieldValues = (char**) malloc  (6 * sizeof(char*));
            for(int i=0;i<6;i++){
                FieldValue *newVal = new FieldValue();
                switch(i)
                {
                    case 0:
                        strcpy(newVal->fldName,"TABLE_CAT");
                        newVal->type = typeString;
                        break;
                    case 1:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"TABLE_SCHEM");
                        break;
                    case 2:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"TABLE_NAME");
                        break;
                    case 3:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"COLUMN_NAME");
                        break;
                    case 4:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"KEY_SEQ");
                        break;
                    case 5:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"PK_NAME");
                        break;
                    default:
                        break;
                };
                newVal->parsedString = NULL;
                newVal->paramNo = 0;
                newVal->length = AllDataType::size(newVal->type, 64);
                newVal->value = AllDataType::alloc(newVal->type, newVal->length);
                if(i==0) strcpy((char*)newVal->value,(char*)"CSQL");
	        if(i==1) strcpy((char*)newVal->value,(char*)"CSQL");
                newVal->isAllocVal=true;
                totalFields = i+1;
                bindFields[i] = newVal;
            }
            break;
        }
        case GetCatalogs:
        {
             bindFields = (FieldValue**) malloc (1 * sizeof(FieldValue*));
             bindFieldValues = (char**) malloc  (1 * sizeof(char*));
             FieldValue *newVal = new FieldValue();
             strcpy(newVal->fldName,"TABLE_CAT");
             newVal->type = typeString;
             newVal->parsedString = NULL;
             newVal->paramNo = 0;
             newVal->length = AllDataType::size(newVal->type, 64);
             newVal->value = AllDataType::alloc(newVal->type, newVal->length);
             newVal->isAllocVal=true;
             totalFields = 1;
             bindFields[0] = newVal;
             break;
        }
        case GetTableType:
        {
             bindFields = (FieldValue**) malloc (1 * sizeof(FieldValue*));
             bindFieldValues = (char**) malloc  (1 * sizeof(char*));
             FieldValue *newVal = new FieldValue();
             strcpy(newVal->fldName,"TABLE_TYPE");
             newVal->type = typeString;
             newVal->parsedString = NULL;
             newVal->paramNo = 0;
             newVal->length = AllDataType::size(newVal->type, 64);
             newVal->value = AllDataType::alloc(newVal->type, newVal->length);
             newVal->isAllocVal=true;
             totalFields = 1;
             bindFields[0] = newVal;
             break;
        }
        case GetDataType:
        {
             bindFields = (FieldValue**) malloc (19 * sizeof(FieldValue*));
             bindFieldValues = (char**) malloc  (19 * sizeof(char*));
             for(int i=0;i<19;i++)
             {
                 FieldValue *newVal = new FieldValue();
                 switch(i)
                 {
                     case 0:
                         strcpy(newVal->fldName,"TYPE_NAME");
                         newVal->type = typeString;
                         break;
                     case 1:
                         newVal->type = typeInt;
                         strcpy(newVal->fldName,"DATA_TYPE");
                         break;
                     case 2:
                         strcpy(newVal->fldName,"PRECISION");
                         newVal->type = typeInt;
                         break;
                     case 3:
                         strcpy(newVal->fldName,"LITERAL_PREFIX");
                         newVal->type = typeString;
                         break;
                     case 4:
                         strcpy(newVal->fldName,"LITERAL_SUFFIX");
                         newVal->type = typeString;
                         break;
                     case 5:
                         strcpy(newVal->fldName,"CREATE_PARAMS");
                         newVal->type = typeString;
                         break;
                     case 6:
                         strcpy(newVal->fldName,"NULLABLE");
                         newVal->type = typeShort;
                         break;
                     case 7:
                         strcpy(newVal->fldName,"CASE_SENSITIVE");
                         newVal->type = typeInt;
                         break;
                     case 8:
                         strcpy(newVal->fldName,"SEARCHABLE");
                         newVal->type = typeShort;
                         break;
                     case 9:
                         strcpy(newVal->fldName,"UNSIGNED_ATTRIBUTE");
                         newVal->type = typeInt;
                         break;
                     case 10:
                         strcpy(newVal->fldName,"FIXED_PREC_SCALE");
                         newVal->type = typeInt;
                         break;
                     case 11:
                         strcpy(newVal->fldName,"AUTO_INCREMENT");
                         newVal->type = typeInt;
                         break;
                     case 12:
                         strcpy(newVal->fldName,"LOCAL_TYPE_NAME");
                         newVal->type = typeString;
                         break;
                     case 13:
                         strcpy(newVal->fldName,"MINIMUM_SCALE");
                         newVal->type = typeShort;
                         break;
                     case 14:
                         strcpy(newVal->fldName,"MAXIMUM_SCALE");
                         newVal->type = typeShort;
                         break;
                     case 15:
                         strcpy(newVal->fldName,"SQL_DATA_TYPE");
                         newVal->type = typeInt;
                         break;
                     case 16:
                         strcpy(newVal->fldName,"SQL_DATETIME_SUB");
                         newVal->type = typeInt;
                         break;
                     case 17:
                         strcpy(newVal->fldName,"NUM_PREC_RADIX");
                         newVal->type = typeInt;
                         break;
                     case 18:
                         strcpy(newVal->fldName,"INTERVAL_PRECISION");
                         newVal->type = typeShort;
                         break;
                     default:
                         break;
                };
                newVal->parsedString = NULL;
                newVal->paramNo = 0;
                newVal->length = AllDataType::size(newVal->type, 64);
                newVal->value = AllDataType::alloc(newVal->type,newVal->length);
                newVal->isAllocVal = true;
                totalFields = i+1;
                bindFields[i] = newVal;
             }
             break;
        }
        case GetImportKey:
        case GetExportKey:
        {
            rv = openTables();
            if (rv != OK)  break; //return rv;
            bindFields = (FieldValue**) malloc (14 * sizeof(FieldValue*));
            bindFieldValues = (char**) malloc  (14 * sizeof(char*));
            for(int i=0;i<14;i++){
                FieldValue *newVal = new FieldValue();
                switch(i){
                    case 0:
                        strcpy(newVal->fldName,"PKTABLE_CAT");
                        newVal->type = typeString;
                        break;
                    case 1:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"PKTABLE_SCHEM");
                        break;
                    case 2:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"PKTABLE_NAME");
                        break;
                    case 3:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"PKCOLUMN_NAME");
                        break;
                    case 4:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"FKTABLE_CAT");
                        break;
                    case 5:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"FKTABLE_SCHEM");
                        break;
                    case 6:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"FKTABLE_NAME");
                        break;
                    case 7:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"FKCOLUMN_NAME");
                        break;
                    case 8:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"KEY_SEQ");
                        break;
                    case 9:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"UPDATE_RULE");
                        break;
                    case 10:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"DELETE_RULE");
                        break;
                    case 11:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"FK_NAME");
                        break;
                    case 12:
                        newVal->type = typeString;
                        strcpy(newVal->fldName,"PK_NAME");
                        break;
                    case 13:
                        newVal->type = typeShort;
                        strcpy(newVal->fldName,"DEFERRABILITY");
                    default:
                        newVal->type = typeString;
                        break;
                };
                newVal->parsedString = NULL;
                newVal->paramNo = 0;
                newVal->length = AllDataType::size(newVal->type, 64);
                newVal->value = AllDataType::alloc(newVal->type,newVal->length);
                if(typeString == newVal->type) strcpy((char*)newVal->value,(char*)"");
                if(i==0||i==1||i == 4 || i==5) strcpy((char*)newVal->value,(char*)"csql");
                newVal->isAllocVal=true;
                totalFields =i+1;
                bindFields[i] = newVal;
            }
            break;
        }
        default:
            break;
    };
    return rv;
}

void* MetadataStatement::fetch()
{
    
    void *tuple = NULL;
    tuple = fetchMetaData();
    if (NULL == tuple) return NULL;
    FieldValue *value;
    for (int i = 0; i < totalFields; i++)
    {
        value = bindFields[i];
        if (bindFieldValues[i] == NULL)
        {
           continue;
        }
        AllDataType::copyVal(bindFieldValues[i], value->value, value->type, value->length);
    }
    return tuple;
}

void* MetadataStatement::fetch(DbRetVal &rv)
{
    void *tuple = NULL;
    tuple = fetchMetaData();
    if (NULL == tuple) return NULL;
    FieldValue *value;
    for (int i = 0; i < totalFields; i++)
    {
        value = bindFields[i];
        if (bindFieldValues[i] == NULL)
        {
            continue;
        }
        AllDataType::copyVal(bindFieldValues[i], value->value, value->type, value->length);
    }
    return tuple;
}

void MetadataStatement::freeMetadata()
{
   if(isPlanFreed) return;
   dataListIter.reset();
   ListNode *head= (ListNode *)dataListIter.getCurrentListNode();
   if(head && (plan != GetTableType )){
       List *list = new List(head);
       list->reset();
       delete list;
   }
   switch(plan)
   {
       case GetTables:
       {
          FieldValue *newVal = NULL;
          if(bindFields){ 
              for(int i=0;i<5;i++){
                 newVal=bindFields[i];
                 if (newVal->isAllocVal) free(newVal->value);
                 delete newVal;
              }   
          }
          break;
       }
       case GetColumns:
       {
          FieldValue *newVal;
          if(bindFields){ 
              for(int i=0;i<23;i++){
                  newVal=bindFields[i];
                  if ( newVal->isAllocVal) free(newVal->value);
                  delete newVal;
              }
          }
          break;
       }
       case GetIndexes:
       {
          FieldValue *newVal;
          if(bindFields){
              for(int i=0;i<13;i++){
                  newVal=bindFields[i];
                  if ( newVal->isAllocVal) free(newVal->value);
                  delete newVal;
              }
          }
          break;
       }
       case GetPriIndex:
       {
          FieldValue *newVal;
          if(bindFields){
              for(int i=0;i<6;i++){
                  newVal=bindFields[i];
                  if ( newVal->isAllocVal) free(newVal->value);
                  delete newVal;
              }
          }
          break; 
       }
       case GetCatalogs:
       {
          FieldValue *newVal;
          if(bindFields){
              for(int i=0;i<1;i++){
                  newVal=bindFields[i];
                //  if ( newVal->isAllocVal) free(newVal->value);
                  delete newVal;
              }
          }
          break;
       }
       case GetTableType:
       {
          FieldValue *newVal;
          if(bindFields){
              for(int i=0;i<1;i++){
                  newVal=bindFields[i];
                 // if ( newVal->isAllocVal) free(newVal->value);
                  delete newVal;
              }
          }
          break;
       }
       case GetDataType:
       {
          FieldValue *newVal;
          if(bindFields){
              for(int i=0;i<18;i++){
                  newVal=bindFields[i];
                  if ( newVal->isAllocVal) free(newVal->value);
                  delete newVal;
              }
          }
          break;
       }
       case GetImportKey:
       {
          FieldValue *newVal;
          if(bindFields){
              for(int i=0;i<14;i++){
                  newVal=bindFields[i];
                  if ( newVal->isAllocVal) free(newVal->value);
                  delete newVal;
              }
          }
          break;
       }
       case GetExportKey:
       {
          FieldValue *newVal;
          if(bindFields){
              for(int i=0;i<14;i++){
                  newVal=bindFields[i];
                  if ( newVal->isAllocVal) free(newVal->value);
                  delete newVal;
              }
          }
          break;
       }
       default:
         break;
   };
   isPlanFreed=true;
}
DbRetVal MetadataStatement::close()
{
    if(plan!=Normal){ freeMetadata(); }
    if (table) return table->closeScan();
    return OK;
}


char* MetadataStatement::getFieldName ( int pos )
{
    ListIterator iter = parsedData->getFieldNameList().getIterator();
    int position =0;
    while (iter.hasElement())
    {
        if (position == pos) {
              FieldName *name = (FieldName*) iter.nextElement();
              if (NULL == name)
              {
                  printError(ErrSysFatal, "Should never happen. Field Name list has NULL");
                  return (char*) 0;
              }
              return name->fldName;
      }
        position++;
    }
    return (char*) 0;
}

DataType MetadataStatement::getFieldType( int pos )
{
    FieldValue *v = bindFields[pos];
    return ( (DataType) v->type );
}

int MetadataStatement::getFieldLength( int pos )
{
    FieldValue *v = bindFields[pos];
    return ( (int) v->type );
}

void* MetadataStatement::fetchAndPrint(bool SQL)
{
    void *tuple = NULL;
    return tuple;
}

void* MetadataStatement::next()
{
    return fetchMetaData();
}

void* MetadataStatement::getFieldValuePtr( int pos )
{
    FieldValue *v = bindFields[pos];
    return ( (void*) v->value );
}

void* MetadataStatement::getFieldValuePtr( char *name )
{
    FieldValue *value;
    char fName[IDENTIFIER_LENGTH];
    for (int i = 0; i < totalFields; i++)
    {
        value = bindFields[i];
        table->getFieldNameAlone(value->fldName,fName);
        if (strcmp(fName,name)==0)
        {
            return ( (void*) value->value );
        }
        
    }
    return NULL;
}

void MetadataStatement::getProjFieldType(int *data)
{
    FieldValue *value;
    for (int i = 0; i < totalFields; i++)
    {
        value = bindFields[i];
        data[i+1] = value->type;
    }
}

DbRetVal MetadataStatement::setBindField(int colNo, void *value)
{
    if (colNo <=0) return ErrBadArg;
    if (NULL == value) return ErrBadArg;
    bindFieldValues[colNo -1] = (char*) value;
    return OK;
}


int MetadataStatement::noOfProjFields()
{
    return totalFields;
}

DbRetVal MetadataStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{

    DbRetVal rv = OK;
    if(plan != Normal)
    {
        FieldValue *v = bindFields[projpos-1];
        strcpy(fInfo->fldName, v->fldName);
        fInfo->type = v->type;
        fInfo->length = v->length;
        return rv;
    }
    ListIterator iter = parsedData->getFieldNameList().getIterator();
    FieldName *name = NULL;
    int position =0;
    while (iter.hasElement())
    {
        name = (FieldName*)iter.nextElement();
        if (NULL == name) 
        {
            printError(ErrSysFatal, "Should never happen. Field Name list has NULL");
            return ErrSysFatal;
        }
        if (position == (projpos-1)) break;
        position++;
    }

    rv = table->getFieldInfo(name->fldName, fInfo);
    if (OK == rv)
    {
       //get back the qualified name(tablename.fldname)
       char qualName[IDENTIFIER_LENGTH];
       strcpy(qualName, name->fldName);
       switch(name->aType)
       {
           case AGG_COUNT:
               sprintf(fInfo->fldName, "COUNT(%s)", qualName);
               fInfo->type = typeInt;
               fInfo->length = sizeof(int);
               break;
           case AGG_MIN:
               sprintf(fInfo->fldName, "MIN(%s)", qualName);
               break;
           case AGG_MAX:
               sprintf(fInfo->fldName, "MAX(%s)", qualName);
               break;
           case AGG_SUM:
               sprintf(fInfo->fldName, "SUM(%s)", qualName);
               break;
           case AGG_AVG:
               sprintf(fInfo->fldName, "AVG(%s)", qualName);
               fInfo->type = typeDouble;
               fInfo->length = sizeof(double);
               break;
           default:
               strcpy(fInfo->fldName, qualName);
               break;
       }
    }
    return rv;
}
int MetadataStatement::getFldPos(char *name)
{
    return table->getFldPos(name);
}

void *MetadataStatement::fetchMetaData()
{
     switch(plan)
     {
        case GetTables:
        {
           Identifier *elem = NULL;
           if(dataListIter.hasElement())
           {
               FieldValue *v = bindFields[2];
               elem = (Identifier*) dataListIter.nextElement();
               AllDataType::copyVal(v->value, elem->name, v->type, v->length);
               delete elem;
               return v->value;
           } else return NULL;
        }
        case GetColumns:
        {
           FieldInfo *info = NULL;
           if(dataListIter.hasElement())
           {
               info = (FieldInfo *) dataListIter.nextElement();
               FieldValue *v;
               for(int i=0;i<23;i++)
               {
                   switch(i)
                   {
                       case 3:
                         {
                             v = bindFields [i];
                             AllDataType::copyVal(v->value, info->fldName, v->type, v->length);
                             break;
                         }
                      case 4:
                         {
                             v = bindFields [i];
                             int type=0;
                             type = AllDataType::convertToCSQLSQLType(info->type);
                             AllDataType::copyVal(v->value,&type,v->type, v->length);
                             break;
                         }
                      case 5:
                         {
                             v = bindFields [i];
                             AllDataType::copyVal(v->value,AllDataType::getSQLString(info->type),v->type, v->length);
                             break;
                         }

                      case 6:
                         {
                             v = bindFields [i];
                             AllDataType::copyVal(v->value,&info->length,v->type, v->length);
                             break;
                         }
                      case 10:
                         {
                             v = bindFields [i];
                             if(info->isNull)
                                 (*(short*)v->value)=0;
                             else
                                 (*(short*)v->value)=1;
                             break;
                         }
                      case 12:
                         {
                             v = bindFields [i];
                             AllDataType::copyVal(v->value,info->defaultValueBuf,v->type, v->length);
                             break;
                         }
                      case 16:
                         {
                             v = bindFields [i];
                             (*(int*)v->value) = table->getFldPos(info->fldName);
                             break;
                         }                             
                      case 17:
                         {
                             v = bindFields [i];
                             if(info->isNull)
                                 AllDataType::copyVal(v->value,(void *)"NO",v->type, v->length);
                             else 
                                 AllDataType::copyVal(v->value,(void *)"YES",v->type, v->length);
                             break;
                         }
                      case 22:
                             v = bindFields [i];
                             if(info->isAutoIncrement)
                                 AllDataType::copyVal(v->value,(void *)"YES",v->type, v->length);
                             else
                                 AllDataType::copyVal(v->value,(void *)"NO",v->type, v->length);

                      default:
                         break;
                   };
               }
               delete info;
               return v->value ;
           }else return NULL;
        }
        case GetIndexes:
        {
           IndexInfoForDriver *info=NULL;
           if(dataListIter.hasElement())
           {
               info = (IndexInfoForDriver *) dataListIter.nextElement();
               FieldValue *v;
               for(int i=0;i<22;i++)
               {
                   switch(i)
                   {
                       case 2:
                         {
                             v = bindFields [i];
                             AllDataType::copyVal(v->value, info->tableName, v->type, v->length);
                             break;
                         }
                      case 3:
                         {
                             v = bindFields [i];
                             if(info->isUnique) { ( *(int*) v->value) = 1; }
                             else (*(int*) v->value) = 0;
                             break;
                         }
                      case 5:
                         {
                             v = bindFields [i];
                             AllDataType::copyVal(v->value,info->indexName, v->type, v->length);
                             break;
                         }
                      case 6:
                         {
                             v = bindFields [i];
                             if(info->type ==0)  (*(short *) v->value) = SQL_INDEX_HASHED ;
                             else  (*(short *) v->value) = SQL_INDEX_OTHER ;
                             break;
                         }
                      case 7:
                         {
                             v = bindFields [i];
                             (*(short *) v->value) = table->getFldPos(info->fieldName) ;
                             break;
                         }
                      case 8:
                         {
                             v = bindFields [i];
                             AllDataType::copyVal(v->value, info->fieldName, v->type, v->length);
                             break;
                         }
                      default:
                         break;
                   };
               }
               delete info;
               return v->value ;
           }else return NULL;  
        }
        case GetPriIndex:
        {
            IndexInfoForDriver *info=NULL;
            char name[IDENTIFIER_LENGTH];
            while(dataListIter.hasElement())
            {
                info = (IndexInfoForDriver *) dataListIter.nextElement();
                FieldValue *v = NULL;
                //sprintf(name, "%s_idx1_Primary",info->tableName);
                //if(strcmp(name, info->indexName) != 0){ continue; }
                if( !info->isPrimary ){ continue; }
                for(int i=0;i<6;i++)
                {
                    switch(i)
                    {
                        case 2:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value, table->getName(), v->type, v->length);
                              break;
                          }
                        case 3:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value, info->fieldName, v->type, v->length);
                              break;
                          }
                       case 4:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = table->getFldPos(info->fieldName) ;
                              break;
                          }
                       case 5:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value,info->indexName, v->type, v->length);
                    //          printf("Index name %s\n",info->indexName);
                              break;
                          }
                       default :
                              break;
                   };
              }
              delete info;
              return v->value;
           }
           return NULL;
        }
        case GetCatalogs:
        {
            FieldValue *v = NULL;
            v = bindFields [0];
            if(!isSecondFetch)
            {
                strcpy((char*)v->value,"csql");
                isSecondFetch=true;
                return v->value;
            }
            free(v->value);
            return NULL;
        }
        case GetTableType:
        {
            FieldValue *v = NULL;
            v = bindFields [0];
            if(!isSecondFetch)
            {
                strcpy((char*)v->value,"TABLE");
                isSecondFetch=true;
                return v->value;
            }
            free(v->value);
            return NULL;
        }
        case GetImportKey:
        case GetExportKey:
        {
            ForeignKeyMetadata *info=NULL;
            char name[IDENTIFIER_LENGTH];
            while(dataListIter.hasElement())
            {
                info = (ForeignKeyMetadata *) dataListIter.nextElement();
                FieldValue *v = NULL;
                for(int i=0;i<14;i++)
                {
                    switch(i)
                    {
                        case 2:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value, info->pkTableName, v->type, v->length);
                              break;
                          }
                        case 3:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value, info->pkColName, v->type, v->length);
                              break;
                          }
                        case 6:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value, info->fkTableName, v->type, v->length);
                              break;
                          }
                        case 7:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value, info->fkColName, v->type, v->length);
                              break;
                          }
                       case 8:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = info->keySeq;
                              break;
                          }
                       case 9: 
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = info->updateRule;
                              break;
                          }
                       case 10:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = info->deleteRule;
                              break;
                          }
                       default :
                              break;
                   };
              }
              delete info;
              return v->value;
           }
           return NULL;
        }
        case GetDataType:
        {
            DataTypeInfo *info=NULL;
            char name[IDENTIFIER_LENGTH];
            while(dataListIter.hasElement())
            {
                info = (DataTypeInfo *) dataListIter.nextElement();
                FieldValue *v = NULL;
                for(int i=0;i<19;i++)
                {
                    switch(i)
                    {
                        case 0:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value, info->name, v->type, v->length);
                              break;
                          }
                        case 1:
                          {
                              v = bindFields [i];
                              int type=0;
                              type = AllDataType::convertToCSQLSQLType((DataType)info->type);
                              AllDataType::copyVal(v->value,&type,v->type, v->length);
                              break;
                          }
                        case 2:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value, &info->precision, v->type, v->length);
                              break;
                          }
                        case 3:
                          {
                              v = bindFields [i];
                              if( info->type == typeString || info->type == typeDate || info->type == typeTime || info->type == typeTimeStamp )
                                  AllDataType::copyVal(v->value, (void *)"'", v->type, v->length);
                              else
                                  AllDataType::copyVal(v->value, (void *)"", v->type, v->length);
                              break;
                          }
                       case 4:
                          {
                              v = bindFields [i];
                              if( info->type == typeString || info->type == typeDate || info->type == typeTime || info->type == typeTimeStamp )
                                  AllDataType::copyVal(v->value, (void *)"'", v->type, v->length);
                              else
                                  AllDataType::copyVal(v->value, (void *)"", v->type, v->length);
                              break;
                          }
                       case 5:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value, (void *)"", v->type, v->length);
                              break;
                          }
                       case 6:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = 1;
                              break;
                          }
                       case 7:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = 0;
                              break;
                          }
                       case 8:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = 3;
                              break;
                          }
                       case 9:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = 0;
                              break;
                          }
                       case 10:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = 0;
                              break;
                          }
                       case 11:
                          {
                              v = bindFields [i];
                              if(info->autoIncrement)
                                  (*(short *) v->value) = 1;
                              else
                                  (*(short *) v->value) = 0;
                              break;
                          }
                       case 12:
                          {
                              v = bindFields [i];
                              AllDataType::copyVal(v->value, info->name, v->type, v->length);
                              break;
                          }
                       case 13:
                          {
                              v = bindFields [i];
                              if(info->type == typeFloat)
                                  (*(short *) v->value) = -38;
                              else if(info->type == typeDouble)
                                  (*(short *) v->value) = -308;
                              else
                                  (*(short *) v->value) = 0;
                              break;
                          }
                       case 14:
                          {
                              v = bindFields [i];
                              if(info->type == typeFloat)
                                  (*(short *) v->value) = 38;
                              else if(info->type == typeDouble)
                                  (*(short *) v->value) = 308;
                              else
                                  (*(short *) v->value) = 0;
                              break;
                          }
                       case 15:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) =0; //TODO
                              break;
                          }
                       case 16:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = 0;//TODO
                              break;
                          }
                       case 17:
                          {
                              v = bindFields [i];
                              (*(int *) v->value) = 10;
                              break;
                          }
                       case 18:
                          {
                              v = bindFields [i];
                              (*(short *) v->value) = 0;
                              break;
                          }
                       default :
                              break;
                   };
              }
              delete info;
              return v->value;
           }
           return NULL;
        }
        default:
           break;
     };
     return NULL;
}

ListIterator MetadataStatement::getDataTypeInfoIterator()
{
    List datalist;
    for(int i=0; i<10; i++)
    {
        DataTypeInfo *typeInfo = new DataTypeInfo();       
        datalist.append(typeInfo);
    }
    DataTypeInfo *info = (DataTypeInfo *)datalist.get(1);
    strcpy(info->name,"TINYINT");
    info->type = 4;
    info->precision = 3; 
    info->autoIncrement = true;
    info = (DataTypeInfo *)datalist.get(2);
    strcpy(info->name,"SMALLINT");
    info->type =3 ;
    info->precision = 5; 
    info->autoIncrement = true;
    info =(DataTypeInfo *) datalist.get(3);
    strcpy(info->name,"INT");
    info->type = 0 ;
    info->precision = 10 ; 
    info->autoIncrement = true;
    info =(DataTypeInfo *) datalist.get(4);
    strcpy(info->name,"BIGINT");
    info->type =1 ;
    info->precision = 19; 
    info->autoIncrement = true;
    info =(DataTypeInfo *) datalist.get(5);
    strcpy(info->name,"FLOAT");
    info->type = 11;
    info->precision = 10; 
    info->autoIncrement = false;
    info =(DataTypeInfo *) datalist.get(6);
    strcpy(info->name,"DOUBLE");
    info->type =10 ;
    info->precision = 17; 
    info->autoIncrement = false;
    info =(DataTypeInfo *) datalist.get(7);
    strcpy(info->name,"CHAR");
    info->type =30 ;
    info->precision = 255; 
    info->autoIncrement = false;
    info =(DataTypeInfo *) datalist.get(8);
    strcpy(info->name,"DATE");
    info->type =20 ;
    info->precision = 0; 
    info->autoIncrement = false;
    info =(DataTypeInfo *) datalist.get(9);
    strcpy(info->name,"TIME");
    info->type =21 ;
    info->precision = 0; 
    info->autoIncrement = false;
    info =(DataTypeInfo *) datalist.get(10);
    strcpy(info->name,"TIMESTAMP");
    info->type =22;
    info->precision = 0; 
    info->autoIncrement = false;
    return datalist.getIterator();     
}   

