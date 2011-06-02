/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
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
#include<Database.h>
#include<DatabaseManager.h>
#include<DatabaseManagerImpl.h>
#include<os.h>
#include<Table.h>
#include<TableImpl.h>
#include<Transaction.h>
#include<CatalogTables.h>
#include<Index.h>
#include<Lock.h>
#include<Debug.h>
#include<Config.h>
#include<Process.h>

DbRetVal DatabaseManagerImpl::createForeignKey(char *fKName,ForeignKeyInfo *info)
{
   DbRetVal rv = OK;
   int totFkFlds = info->fkFldList.size();
   int totPkFlds = info->pkFldList.size();
   if (totFkFlds==0 && totPkFlds==0) {
        printError(ErrBadCall, "No Field name specified");
        return ErrBadCall;
   }
    void *tptr =NULL;
    void *chunk = NULL;
    void *vcchunk = NULL;
    rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(info->fkTableName, chunk, tptr, vcchunk);
    if (NULL == tptr)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrNotExists, "Table does not exist %s", info->fkTableName);
        return ErrNotExists;
    }
    char **fptr = new char* [totFkFlds];
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.getFieldPtrs(info->fkFldList, tptr, fptr);
    if (OK != rv)
    {
        delete[] fptr;
        systemDatabase_->releaseCheckpointMutex();
        if (rv != ErrBadCall) {
            printError(ErrNotExists, "Field does not exist");
            return ErrNotExists;
        }
    }
    void *tPkptr =NULL;
    void *chunkPk = NULL;
    void *vcchunkPk = NULL;
    CatalogTableTABLE c2Table(systemDatabase_);
    c2Table.getChunkAndTblPtr(info->pkTableName, chunkPk, tPkptr, vcchunkPk);
    if (NULL == tPkptr)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrNotExists, "Table does not exist %s", info->pkTableName);
        return ErrNotExists;
    }
    char **fPkptr = new char* [totPkFlds];
    CatalogTableFIELD c2Field(systemDatabase_);
    rv = c2Field.getFieldPtrs(info->pkFldList, tPkptr, fPkptr);
    if (OK != rv)
    {
        delete[] fptr;
        delete[] fPkptr;
        systemDatabase_->releaseCheckpointMutex();
        if (rv != ErrBadCall) {
            printError(ErrNotExists, "Field does not exist");
            return ErrNotExists;
        }
    }
    //Create New chunkdatanode
    CatalogTableFK cFK(systemDatabase_);
    rv = cFK.insert(fKName, tptr, tPkptr);//TODO
    if (OK != rv)
    {
        delete[] fptr;
        delete[] fPkptr;
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in CFK table");
        return ErrSysInternal;
    }

    CatalogTableFKFIELD cFKField(systemDatabase_);
    rv = cFKField.insert(fKName,fptr,fPkptr,totFkFlds);
    if (OK != rv)
    {
        delete[] fptr;
        delete[] fPkptr;
        cFK.remove(tptr);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in CFKFIELD table");
        return ErrSysInternal;
    }
    systemDatabase_->releaseCheckpointMutex();
    delete[] fptr;    
    delete[] fPkptr;
    return rv;
}

DbRetVal DatabaseManagerImpl::dropForeignKey(void *tptr,bool trylock)
{
    DbRetVal rv = OK;
    if(trylock){
        rv = systemDatabase_->getXCheckpointMutex();
        if (OK != rv)
        {
            printError(ErrSysInternal, "Unable to get database mutex");
            return ErrSysInternal;
        }
    }
    void *fkChunk=NULL;
    CatalogTableFK cFK(systemDatabase_);
    int total = cFK.getNoOfPkTable(tptr);
    //printDebug(DM_TEST,"total fk chunk %d",total);
    for (int i=0;i< total; i++)
    {
         fkChunk = cFK.getFkCTable(tptr);
         if(NULL==fkChunk)
         {
            if(trylock){
                systemDatabase_->releaseCheckpointMutex();
            }
            printError(ErrSysInternal, "Catalog table not finds CFKFIELD table");
            return ErrSysInternal;
         }
         CatalogTableFKFIELD cFKField(systemDatabase_);
         rv = cFKField.remove(fkChunk);
         if (OK != rv)
         {
             if(trylock){
                systemDatabase_->releaseCheckpointMutex();
             }
             printError(ErrSysInternal, "Catalog table updation failed in CFKFIELD table");
             return ErrSysInternal;
         } 
         rv =cFK.remove(fkChunk);
         if (OK != rv)
         {
            if(trylock){
                systemDatabase_->releaseCheckpointMutex();
            }
            printError(ErrSysInternal, "Catalog table updation failed for INDEX table");
            return ErrSysInternal;
         }
    }  
    if(trylock){
        systemDatabase_->releaseCheckpointMutex();
    }
    return rv;
}
