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
char ChunkName[MAX_CHUNKS][CHUNK_NAME_LEN]={"UserChunkTableId","LockTableHashBucketId","LockTableMutexId","LockTableId","TransHasTableId","UndoLogTableId","","","","","DatabaseTableId","UserTableId","TableTableId","FieldTableId","AccessTableId","IndexTableId","IndexFieldTableId",""};


DbRetVal CatalogTableTABLE::insert(const char *name, int id, size_t size,
                    int numFlds, void* chunk, void *&tptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(TableTableId);
    DbRetVal rv = OK;
    tptr = tChunk->allocate(systemDatabase_, &rv);
    if (NULL == tptr)
    {
        printError(rv,
                   "Could not allocate memory for for TABLE catalog table");
        return rv;
    }
    TABLE *tableInfo = (TABLE*)tptr;
    strcpy(tableInfo->tblName_, name);
    tableInfo->tblID_ = id;
    tableInfo->length_ = size;
    tableInfo->numFlds_ = numFlds;
    tableInfo->numIndexes_ = 0;
    tableInfo->chunkPtr_ = chunk;
    printDebug(DM_SystemDatabase,"One Row inserted into TABLE %x %s",tptr, name);
    return OK;
}

DbRetVal CatalogTableTABLE::remove(const char *name, void *&chunk, void *&tptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(TableTableId);
    ChunkIterator iter = tChunk->getIterator();

    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
         if (0 == strcmp(((TABLE*)data)->tblName_, name))
         {
             //remove this element and store the tblPtr
             //there will be only one row for this table(Primary key)
             tptr = (void*) data;
             chunk = (Chunk*) ((TABLE*)data)->chunkPtr_;
             break;
         }
    }
    if (NULL != tptr)
    {
        tChunk->free(systemDatabase_, tptr);
        printDebug(DM_SystemDatabase,"One Row deleted from TABLE %x %s",tptr, name);
    }
    else
    {
        printError(ErrNotExists,"Table %s not exists in TABLE catalog table", name);
        return ErrNotExists;
    }
    return OK;
}

DbRetVal CatalogTableTABLE::getChunkAndTblPtr(const char *name,
                                               void *&chunk, void *&tptr)
{
    Chunk *chk = systemDatabase_->getSystemDatabaseChunk(TableTableId);
    ChunkIterator iter = chk->getIterator();;
    while (NULL != (tptr = iter.nextElement()))
    {
         if (strcmp(((TABLE*)tptr)->tblName_, name) == 0)
         {
             //there will be only one row for this table(Primary key)
             chunk = (Chunk*) ((TABLE*)tptr)->chunkPtr_;
             return OK;
         }
    }
    //table not found in TABLE
    return ErrNotFound;
}

List CatalogTableTABLE::getTableList()
{
    List tableList;
    Chunk *chk = systemDatabase_->getSystemDatabaseChunk(TableTableId);
    ChunkIterator iter = chk->getIterator();
    void *tptr;
    while (NULL != (tptr = iter.nextElement()))
    {
         Identifier *elem = new Identifier();
         strcpy(elem->name, ((TABLE*)tptr)->tblName_);
         tableList.append(elem);
    }
    return tableList;
}

DbRetVal CatalogTableFIELD::insert(FieldIterator &iter, int tblID, void *tptr)
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(FieldTableId);
    DbRetVal rv = OK;
    while (iter.hasElement())
    {
        void *fptr = fChunk->allocate(systemDatabase_, &rv);
        if (NULL == fptr)
        {
            printError(rv,
                   "Could not allocate for FIELD catalog table");
            return rv;
        }
        FIELD *fldInfo = (FIELD*)fptr;
        FieldDef fDef = iter.nextElement();
        strcpy(fldInfo->fldName_, fDef.fldName_);
        fldInfo->tblID_ = tblID;
        fldInfo->tblPtr_ = tptr;
        fldInfo->type_ = fDef.type_;
        fldInfo->length_ = fDef.length_;
        fldInfo->offset_ = 0; //TODO
        os::memcpy(fldInfo->defaultValueBuf_, fDef.defaultValueBuf_,
                                        DEFAULT_VALUE_BUF_LENGTH);
        fldInfo->isNull_ = fDef.isNull_;
        fldInfo->isPrimary_ = fDef.isPrimary_;
        fldInfo->isUnique_ = fDef.isUnique_;
        fldInfo->isDefault_ = fDef.isDefault_;
        fldInfo->width_ = 0; //TODO
        fldInfo->scale_ = 0; //TODO
        printDebug(DM_SystemDatabase,"One Row inserted into FIELD %x %s",fldInfo, fDef.fldName_);

    }
    return OK;
}

DbRetVal CatalogTableFIELD::remove(void *tptr)
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(FieldTableId);
    ChunkIterator fIter = fChunk->getIterator();
    void *data = NULL;
    while ((data = fIter.nextElement())!= NULL)
    {
        if (((FIELD*)data)->tblPtr_ == tptr)
        {
            //remove this element
            fChunk->free(systemDatabase_, data);
            printDebug(DM_SystemDatabase,"One Row deleted from FIELD %x",data);
        }
    }
    return OK;
}

void CatalogTableFIELD::getFieldInfo(void* tptr, FieldList &list)
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(FieldTableId);
    ChunkIterator fIter = fChunk->getIterator();;
    void *data = NULL;
    while (NULL != (data = fIter.nextElement()))
    {
        if (((FIELD*)data)->tblPtr_ == tptr)
        {
            //add the information to the field list
            FIELD *fTuple = (FIELD*)data;
            FieldDef fldDef;
            strcpy(fldDef.fldName_, fTuple->fldName_);
            fldDef.fldName_[IDENTIFIER_LENGTH] = '\0';
            fldDef.type_ = fTuple->type_;
            fldDef.length_ = fTuple->length_;
            fldDef.isDefault_ = fTuple->isDefault_;
            os::memcpy(fldDef.defaultValueBuf_, fTuple->defaultValueBuf_,
                                         DEFAULT_VALUE_BUF_LENGTH);
            fldDef.isNull_ = fTuple->isNull_;
            fldDef.isUnique_ = fTuple->isUnique_;
            fldDef.isPrimary_ = fTuple->isPrimary_;
            list.append(fldDef);
        }
    }
    return;
}

DbRetVal CatalogTableFIELD::getFieldPtrs(FieldNameList &fldList,void *tptr, char **&fptr)
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(FieldTableId);
    int i=0;
    char *fName = NULL;
    bool found = false;
    fldList.resetIter();
    void *data = NULL;
    DbRetVal rv =OK;
    while (NULL != (fName = fldList.nextFieldName()))
    {
        ChunkIterator fIter = fChunk->getIterator();
        found = false;
        while (NULL != (data = fIter.nextElement()))
        {
            if (((FIELD*)data)->tblPtr_ == tptr)
            {
                 if(0 == strcmp((char*)((FIELD*)data)->fldName_, fName))
                 {
                     found = true;
                     //if (! ((FIELD*)data)->isNull_) rv = ErrBadCall;
                     fptr[i++] = (char*) data;
                     break;
                 }
            }
        }
        if (!found)
        {
            printError(ErrNotFound,
                   "No entries found in FIELD catalog table for the table specified");
            return ErrNotFound;
        }
    }
    return rv;
}

DbRetVal CatalogTableINDEX::insert(const char *name, void *tptr, int numFlds, bool isUnique,
                          void* chunk, int bucketSize, void *hChunk, void *&tupleptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
    ChunkIterator iter = tChunk->getIterator();

    //Checking for index having same name, proceed further only
    //if no such indexes are 
    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
	    if (0 == strcmp(((INDEX*)data)->indName_, name))
	    {
		    printError(ErrAlready, "Index with name \'%s\' already exists "
				    "on the table \'%s\'.", name, ((TABLE *)tptr)->tblName_);
		    return ErrAlready;
	    }

    }

    DbRetVal rv =OK; 
    tupleptr = tChunk->allocate(systemDatabase_, &rv);
    if (NULL == tupleptr)
    {
        printError(rv,
                   "Could not allocate for INDEX catalog table");
        return rv;
    }
    INDEX *indexInfo = (INDEX*)tupleptr;
    strcpy(indexInfo->indName_, name);
    indexInfo->tblID_ = -1; //Not used currently
    indexInfo->tblPtr_ = tptr;
    indexInfo->numFlds_ = numFlds;
    indexInfo->indexType_ = hashIndex;
    indexInfo->chunkPtr_ = chunk;
    indexInfo->hashNodeChunk_ = hChunk;
    indexInfo->noOfBuckets_ = bucketSize;
    indexInfo->isUnique_ = isUnique;
    indexInfo->fstIndFld_=NULL;
    printDebug(DM_SystemDatabase,"One Row inserted into INDEX %x %s",tupleptr, name);
    return OK;
}

DbRetVal CatalogTableINDEX::remove(const char *name, void *&chunk, void *&hchunk, void *&iptr)
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
    ChunkIterator iter = fChunk->getIterator();

    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
         if (0 == strcmp(((INDEX*)data)->indName_, name))
         {
             //remove this element and store the tuple ptr
             //there will be only one row for this table(Primary key)
             chunk = (Chunk*) ((INDEX*)data)->chunkPtr_;
             hchunk = (Chunk*) ((INDEX*)data)->hashNodeChunk_;
             iptr = (void*) data;
             break;
         }
    }
    if (NULL != iptr)
    {
        fChunk->free(systemDatabase_, iptr);
        printDebug(DM_SystemDatabase,"One Row deleted from INDEX %x %s",iptr, name);
    }
    else
    {
        printError(ErrNotExists,"Index %s not exists in INDEX catalog table", name);
        return ErrNotExists;
    }
    return OK;
}
DbRetVal CatalogTableINDEX::get(const char *name, void *&chunk, void *&hchunk, void *&iptr)
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
    ChunkIterator iter = fChunk->getIterator();

    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
         if (0 == strcmp(((INDEX*)data)->indName_, name))
         {
             //remove this element and store the tuple ptr
             //there will be only one row for this table(Primary key)
             chunk = (Chunk*) ((INDEX*)data)->chunkPtr_;
             hchunk = (Chunk*) ((INDEX*)data)->hashNodeChunk_;
             iptr = (void*) data;
             break;
         }
    }
    if (NULL == iptr)
    {
        printError(ErrNotExists,"Index %s not exists in INDEX catalog table", name);
        return ErrNotExists;
    }
    return OK;
}

int CatalogTableINDEX::getNumIndexes(void *tptr)
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
    ChunkIterator iter = fChunk->getIterator();
    void *iptr = NULL;
    int numIndex =0;
    while (NULL != (iptr = iter.nextElement()))
    {
         if (((INDEX*)iptr)->tblPtr_ == tptr) numIndex++;
    }
    return numIndex;
}

char* CatalogTableINDEX::getIndexName(void *tptr, int position)
{
    if (position == 0) return NULL;
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
    ChunkIterator iter = fChunk->getIterator();
    void *iptr = NULL;
    int numIndex =0;
    int curPos =0;
    while (NULL != (iptr = iter.nextElement()))
    {
         if (((INDEX*)iptr)->tblPtr_ == tptr) curPos++;
         if ( curPos == position ) return ((INDEX*)iptr)->indName_;
    }
    return NULL;

}

void CatalogTableINDEX::getIndexPtrs(void *tptr, char **&array)
{
    void *iptr = NULL;
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
    ChunkIterator iter = fChunk->getIterator();
    int i=0;
    while (NULL != (iptr = iter.nextElement()))
    {
         if (((INDEX*)iptr)->tblPtr_ == tptr)
         {
             array[i++] = (char*) iptr;
         }
    }
    return;
}

ChunkIterator CatalogTableINDEX::getIterator(void *iptr)
{
    INDEX *index = (INDEX*)iptr;
    return ((Chunk*)index->chunkPtr_)->getIterator();
}


int CatalogTableINDEX::getNoOfBuckets(void *iptr)
{
    INDEX *index = (INDEX*)iptr;
    return index->noOfBuckets_;
}

int CatalogTableINDEX::getUnique(void *iptr)
{
    INDEX *index = (INDEX*)iptr;
    return index->isUnique_;
}
char* CatalogTableINDEX::getName(void *iptr)
{
    INDEX *index = (INDEX*)iptr;
    return index->indName_;
}

DbRetVal CatalogTableINDEXFIELD::insert(FieldNameList &fldList, void *indexPtr,
                                         void *tblPtr, char **&fptr)

{
    Chunk *tChunk;
    tChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
    ChunkIterator iter = tChunk->getIterator();	
    INDEXFIELD *fInd=NULL;
    char *fName =NULL;
    void *data = NULL;
    bool isFldInd=false;
    while ((data = iter.nextElement())!= NULL)
    {
        if ((((INDEX*)data)->tblPtr_==tblPtr) && (((INDEX*)indexPtr)->numFlds_ == ((INDEX*)data)->numFlds_) && (data != indexPtr) )
        {
	    fldList.resetIter();
		    while (NULL != (fName = fldList.nextFieldName()))
		    {
			isFldInd=false;
                        fInd=(INDEXFIELD*)((INDEX*)data)->fstIndFld_ ;
			while (fInd)
		    	{
		    	    if (0 == strcmp(((FIELD *) fInd->fieldPtr)->fldName_, fName))
			    {
				isFldInd=true;
				break;
			    }
			    fInd=fInd->next;
                    	}
			if(!isFldInd) break;
		    }
		    if(isFldInd)
		    {
                	printError(ErrAlready, "Index on this field  already exists on table \'%s\' by name \'%s\'", ((TABLE *)tblPtr)->tblName_, ((INDEX *)data)->indName_);
			return ErrAlready;
		    }
            }

    }

    tChunk = systemDatabase_->getSystemDatabaseChunk(IndexFieldTableId);
    fldList.resetIter();
    int i =0;
    while (NULL != (fName = fldList.nextFieldName()))
    {
        DbRetVal rv = OK;
        void *fieldptr = tChunk->allocate(systemDatabase_, &rv);
        if (NULL == fieldptr)
        {
            printError(rv,
                   "Could not allocate for USER catalog table");
            return rv;
        }
        INDEXFIELD *fldInfo = (INDEXFIELD*)fieldptr;
        fldInfo->tablePtr = tblPtr;
        fldInfo->fieldPtr = (FIELD*)fptr[i++];
        fldInfo->indexPtr = indexPtr;
	fldInfo->next=(INDEXFIELD*)((INDEX*)indexPtr)->fstIndFld_;
	((INDEX *)indexPtr)->fstIndFld_=fldInfo;
        printDebug(DM_SystemDatabase,"One Row inserted into INDEXFIELD %x", fldInfo);
    }
    return OK;
}

DbRetVal CatalogTableINDEXFIELD::remove(void *iptr)
{
    Chunk *fChunk;
    fChunk = systemDatabase_->getSystemDatabaseChunk(IndexFieldTableId);
    ChunkIterator fIter = fChunk->getIterator();
    void *data = NULL;
    while ((data = fIter.nextElement())!= NULL)
    {
        if (((INDEXFIELD*)data)->indexPtr == iptr)
        {
            //remove this element
            fChunk->free(systemDatabase_, data);
            printDebug(DM_SystemDatabase,"One Row deleted from INDEXFIELD %x", data);
        }
    }
    return OK;
}

DbRetVal CatalogTableINDEXFIELD::getFieldNameAndType(void *index,
                                                char *&name, DataType &type)
{
    Chunk *ifChunk;
    ifChunk = systemDatabase_->getSystemDatabaseChunk(IndexFieldTableId);
    ChunkIterator ifIter = ifChunk->getIterator();
    void *data = NULL;
    while ((data = ifIter.nextElement())!= NULL)
    {
        if (((INDEXFIELD*)data)->indexPtr == index)
        {
            //store the field name
            name = ((FIELD*)(((INDEXFIELD*)data)->fieldPtr))->fldName_;
            type = ((FIELD*)(((INDEXFIELD*)data)->fieldPtr))->type_;
            return OK;
        }
    }
    printError(ErrNotExists,"Index %x not exists in catalog table", index);
    return ErrNotExists;
}

DbRetVal CatalogTableINDEXFIELD::getFieldInfo(void *index, FieldList &list)
{
    Chunk *ifChunk;
    ifChunk = systemDatabase_->getSystemDatabaseChunk(IndexFieldTableId);
    ChunkIterator ifIter = ifChunk->getIterator();
    void *data = NULL;
    int rowCount =0;
    while ((data = ifIter.nextElement())!= NULL)
    {
        if (((INDEXFIELD*)data)->indexPtr == index)
        {
            //add the information to the field list
            FIELD *fTuple = (FIELD*)(((INDEXFIELD*)data)->fieldPtr);
            FieldDef fldDef;
            strcpy(fldDef.fldName_, fTuple->fldName_);
            fldDef.fldName_[IDENTIFIER_LENGTH] = '\0';
            fldDef.type_ = fTuple->type_;
            fldDef.length_ = fTuple->length_;
            fldDef.isDefault_ = fTuple->isDefault_;
            os::memcpy(fldDef.defaultValueBuf_, fTuple->defaultValueBuf_,
                                         DEFAULT_VALUE_BUF_LENGTH);
            fldDef.isNull_ = fTuple->isNull_;
            fldDef.isUnique_ = fTuple->isUnique_;
            fldDef.isPrimary_ = fTuple->isPrimary_;
            list.append(fldDef);
        }
        rowCount++;
    }
    if (!rowCount) { 
         printError(ErrNotExists,"Index %x not exists in catalog table", index);
         return ErrNotExists;
    }
    return OK;
}

void CatalogTableINDEXFIELD::printAllIndex()
{
    Chunk *chunk=systemDatabase_->getSystemDatabaseChunk(IndexFieldTableId);        
    ChunkIterator ifIter = chunk->getIterator();
    void *data = NULL;
    char indexName[IDENTIFIER_LENGTH] = {'\0'};
    while ((data = ifIter.nextElement())!= NULL)
    {
	if(strcmp(indexName,((INDEX*)(((INDEXFIELD*)data)->indexPtr))->indName_)!=0)
	{
       	    printf("    <Index Name> %s </Index Name> \n",((INDEX*)(((INDEXFIELD*)data)->indexPtr))->indName_);
       	    if(0==((INDEX*)(((INDEXFIELD*)data)->indexPtr))->indexType_)
      	        printf("        <Index Type> Hash Index </Index Type> \n");
       	    else
       	        printf("        <Index Type> Tree Index </Index Type> \n");
       	    printf("        <Table Name> %s </Table Name> \n",((TABLE*)(((INDEXFIELD*)data)->tablePtr))->tblName_);
       	    printf("        <Field Name> %s </Field Name> \n",((FIELD*)(((INDEXFIELD*)data)->fieldPtr))->fldName_);
	}
	else
	{
       	    printf("        <Field Name> %s </Field Name> \n",((FIELD*)(((INDEXFIELD*)data)->fieldPtr))->fldName_);
	}
	strcpy(indexName,((INDEX*)(((INDEXFIELD*)data)->indexPtr))->indName_);
    }
}

DbRetVal CatalogTableUSER::insert(const char *name, const char *pass)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(UserTableId);
    DbRetVal rv = OK;
    USER *usrInfo = (USER*)tChunk->allocate(systemDatabase_, &rv);
    if (NULL == usrInfo)
    {
        printError(rv,
                   "Could not allocate for USER catalog table");
        return rv;
    }
    strcpy(usrInfo->userName_, name);
    strcpy(usrInfo->password_, os::encrypt(pass, "A0"));
    return OK;

}

DbRetVal CatalogTableUSER::authenticate(const char *name, const char *pass,
                                   bool &isAuthenticated, bool &isDba)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(UserTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    while (NULL != (data = iter.nextElement()))
    {
        if (strcmp(((USER*)data)->userName_, name) == 0)
        {
            //verify the password
            char * enpass = os::encrypt(pass,"A0");
            if (0 == strcmp(enpass, ((USER*)data)->password_))
            {
                isAuthenticated = true;
                if (0 == strcmp(((USER*)data)->userName_, DBAUSER))
                    isDba = true; else isDba = false;
                return OK;
            }
        }
    }
    isAuthenticated = false;
    return OK;
}

DbRetVal CatalogTableUSER::remove(const char *name)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(UserTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
        if (strcmp(((USER*)data)->userName_, name) == 0)
        {
            //remove this element
            tChunk->free(systemDatabase_, data);
            return OK;
        }
    }
    printError(ErrNotExists,"User %s not exists in catalog table", name);
    return ErrNotExists;
}

DbRetVal CatalogTableUSER::changePass(const char *name, const char *pass)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(UserTableId);
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    while (NULL != (data = iter.nextElement()))
    {
        if (strcmp(((USER*)data)->userName_, name) == 0)
        {
            //change the password
            strcpy(((USER*)data)->password_, os::encrypt(pass, "A0"));
            return OK;
        }
    }
    printError(ErrNotExists,"User %s not exists in catalog table", name);
    return ErrNotExists;
}
