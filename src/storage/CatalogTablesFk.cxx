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
#include<CatalogTables.h>
#include<Database.h>
#include<Allocator.h>
#include<Field.h>
#include<Debug.h>

DbRetVal CatalogTableFK::insert(char *name, void *tptr, void *tPkptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
       if (0 == strcmp(((CFK*)data)->fkName_, name))
       {
          printError(ErrAlready, "Index with name \'%s\' already exists "
                          "on the table \'%s\'.", name, ((CTABLE *)tptr)->tblName_);
          return ErrAlready;
       }
    }

    DbRetVal rv =OK;
    void *fkptr = tChunk->allocate(systemDatabase_, &rv);
    if (NULL == fkptr)
    {
        printError(rv, "Could not allocate for FK catalog table");
        return rv;
    }
    CFK *fkTblInfo = (CFK*)fkptr;
    strcpy(fkTblInfo->fkName_, name);
    fkTblInfo->fkTblPtr_= tptr;
    fkTblInfo->pkTblPtr_= tPkptr;
    printDebug(DM_SystemDatabase,"One Row inserted into FK %x %s",fkptr, name);
    return OK;
}

DbRetVal CatalogTableFKFIELD::insert(char *cFKName, char **fkFldPtrs, char **pkFldPtrs,int totalFld)
{
    Chunk *tChunk = NULL;
    tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
       if (0 == strcmp(((CFK*)data)->fkName_, cFKName))
       {
            break;
       }
    }
    tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyFieldTableId);
    int i =0;
    DbRetVal rv = OK;
    while (i < totalFld)
    {
        void *fieldptr = tChunk->allocate(systemDatabase_, &rv);
        if (NULL == fieldptr)
        {
            printError(rv, "Could not allocate for USER catalog table");
            return rv;
        }
        CFKFIELD *fldInfo = (CFKFIELD*)fieldptr;
        fldInfo->fkPtr_ = data;
        fldInfo->pfFldPtr_ = (CFIELD*)pkFldPtrs[i];
        fldInfo->fkFldPtr_ = (CFIELD*)fkFldPtrs[i++];
        //printDebug(DM_TEST,"TYPE %d\n",((CFIELD*)fldInfo->pfFldPtr_)->type_);
        //printDebug(DM_TEST,"FK name %s\n",((CFIELD*)fldInfo->fkFldPtr_)->fldName_);
        if(!(((CFIELD*)fldInfo->pfFldPtr_)->isUnique_) || !(((CFIELD*)fldInfo->pfFldPtr_)->isNull_))
        {
             printError(ErrSysInternal,"Parent Table field should have  primary key field ");
             tChunk->free(systemDatabase_,fieldptr);
             return ErrSysInternal;
        }
        if(((CFIELD*)fldInfo->pfFldPtr_)->type_!=((CFIELD*)fldInfo->fkFldPtr_)->type_)
        {
           printError(ErrSysInternal,"Type Missmatch in both PK field and FK field  ");
           tChunk->free(systemDatabase_,fieldptr);
           return ErrSysInternal;
        }
        printDebug(DM_SystemDatabase,"One Row inserted into FKFIELD %x", fldInfo);
    }
    return OK;
}

DbRetVal CatalogTableFK::remove(void *ctptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
        if (data == ctptr)
        {
            tChunk->free(systemDatabase_,data);
            printDebug(DM_SystemDatabase,"One Row deleted from FKFIELD %x", data);
        }
    }
    return OK;
}

DbRetVal CatalogTableFKFIELD::remove(void *cFKfld)
{
    Chunk *fChunk = NULL;
    fChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyFieldTableId);
    ChunkIterator iter = fChunk->getIterator();
    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
       if (((CFKFIELD*)data)->fkPtr_== cFKfld )
       {
          fChunk->free(systemDatabase_, data);
          printDebug(DM_SystemDatabase,"One Row deleted from CFKFIELD %x", data);
       }
    }
    return OK;
}

void *CatalogTableFK::getFkCTable(void *ctptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
        if (((CFK*)data)->fkTblPtr_== ctptr)
        {
            return data;
        }

    }
    return NULL;
}

int CatalogTableFK::getNumFkTable(void *ctptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    int count=0;
    while ((data = iter.nextElement())!= NULL)
    {
        if (((CFK*)data)->pkTblPtr_== ctptr)
        {
            count++;
        }
    }
    return count;
}

bool CatalogTableFK::isFkTable(void *ctptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    int count=0;
    while ((data = iter.nextElement())!= NULL)
    {
        if (((CFK*)data)->fkTblPtr_== ctptr)
        {
            return true;
        }
    }
    return false;
}

int CatalogTableFK::getNoOfFkTable(void *ctptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    int count=0;
    while ((data = iter.nextElement())!= NULL)
    {
        if (((CFK*)data)->pkTblPtr_== ctptr)
        {
            count++;
        }
    }
    return count;
}

int CatalogTableFK::getNoOfPkTable(void *ctptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    int count=0;
    while ((data = iter.nextElement())!= NULL)
    {
        if (((CFK*)data)->fkTblPtr_== ctptr)
        {
            count++;   
        }
    }
    return count;
}

void CatalogTableFK::getPkTableName(void *ctptr,char **&array)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    int i=0;
    while ((data = iter.nextElement())!= NULL)
    {
            if (((CFK*)data)->fkTblPtr_== ctptr)
            {
               array[i++] = ((CTABLE*)((CFK*)data)->pkTblPtr_)->tblName_;
            }
    }
}

void CatalogTableFK::getFkTableName(void *ctptr,char **&array)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    int i=0;
    while ((data = iter.nextElement())!= NULL)
    {
            if (((CFK*)data)->pkTblPtr_== ctptr)
            {
               array[i++] = ((CTABLE*)((CFK*)data)->fkTblPtr_)->tblName_;
            }
    }
}


DbRetVal CatalogTableFK::getPkFkFieldInfo(void *cpkptr, void *cfkptr, FieldNameList &pklist,FieldNameList &fklist)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
        if (((CFK*)data)->pkTblPtr_== cpkptr && ((CFK*)data)->fkTblPtr_ == cfkptr)
        {
           break;
        }
    }
    if(data == NULL)
    {
        printError(ErrNotExists,"Foreign Key field CFK not found");
        return ErrNotExists;
    }
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(ForeignKeyFieldTableId);
    iter = fChunk->getIterator();
    void *fdata=NULL;
    while ((fdata = iter.nextElement())!= NULL)
    {
        if (((CFKFIELD*)fdata)->fkPtr_==data)
        {
            //printDebug(DM_TEST,"PK Field name %s\n",((CFIELD*)((CFKFIELD*)fdata)->pfFldPtr_)->fldName_);
            //printDebug(DM_TEST,"FK Field name %s\n",((CFIELD*)((CFKFIELD*)fdata)->fkFldPtr_)->fldName_);
            pklist.append(((CFIELD*)((CFKFIELD*)fdata)->pfFldPtr_)->fldName_);
            fklist.append(((CFIELD*)((CFKFIELD*)fdata)->fkFldPtr_)->fldName_);
        }
    }
    return OK;
}


