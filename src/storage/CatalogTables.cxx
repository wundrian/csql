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
char ChunkName[MAX_CHUNKS][CHUNK_NAME_LEN]={"UserChunkTableId","LockTableHashBucketId","LockTableMutexId","LockTableId","TransHasTableId","UndoLogTableId","","","","","DatabaseTableId","UserTableId","TableTableId","FieldTableId","AccessTableId","IndexTableId","IndexFieldTableId","ForeignKeyTableId","ForeignKeyFieldTableId"};


DbRetVal CatalogTableTABLE::insert(const char *name, int id, size_t size,
                    int numFlds, void* chunk, void *&tptr, void *vcchunk)
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
    CTABLE *tableInfo = (CTABLE*)tptr;
    strcpy(tableInfo->tblName_, name);
    tableInfo->tblID_ = id;
    tableInfo->length_ = size;
    tableInfo->numFlds_ = numFlds;
    tableInfo->numIndexes_ = 0;
    tableInfo->chunkPtr_ = chunk;
    tableInfo->varcharChunkPtr_ = vcchunk;
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
         if (0 == strcmp(((CTABLE*)data)->tblName_, name))
         {
             //remove this element and store the tblPtr
             //there will be only one row for this table(Primary key)
             tptr = (void*) data;
             chunk = (Chunk*) ((CTABLE*)data)->chunkPtr_;
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
                                    void *&chunk, void *&tptr, void *&vcchunk)
{
    Chunk *chk = systemDatabase_->getSystemDatabaseChunk(TableTableId);
    ChunkIterator iter = chk->getIterator();;
    while (NULL != (tptr = iter.nextElement()))
    {
         if (strcmp(((CTABLE*)tptr)->tblName_, name) == 0)
         {
             //there will be only one row for this table(Primary key)
             chunk = (Chunk*) ((CTABLE*)tptr)->chunkPtr_;
             vcchunk = (Chunk*) ((CTABLE*)tptr)->varcharChunkPtr_;
             return OK;
         }
    }
    //table not found in TABLE
    return ErrNotFound;
}


DbRetVal CatalogTableTABLE::setChunkPtr(const char *name, void *firstPage, void *curPage)
{
    Chunk *chk = systemDatabase_->getSystemDatabaseChunk(TableTableId);
    ChunkIterator iter = chk->getIterator();;
    void *tptr;
    while (NULL != (tptr = iter.nextElement()))
    {
         if (strcmp(((CTABLE*)tptr)->tblName_, name) == 0)
         {
             //there will be only one row for this table(Primary key)
             ((Chunk*)((CTABLE*)tptr)->chunkPtr_)->setFirstPage(firstPage);
             ((Chunk*)((CTABLE*)tptr)->chunkPtr_)->setCurPage(curPage);
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
         strcpy(elem->name, ((CTABLE*)tptr)->tblName_);
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
        CFIELD *fldInfo = (CFIELD*)fptr;
        FieldDef *fDef = iter.nextElement();
        strcpy(fldInfo->fldName_, fDef->fldName_);
        fldInfo->tblID_ = tblID;
        fldInfo->tblPtr_ = tptr;
        fldInfo->type_ = fDef->type_;
        fldInfo->length_ = fDef->length_;
        fldInfo->offset_ = fDef->offset_; 
        os::memcpy(fldInfo->defaultValueBuf_, fDef->defaultValueBuf_,
                                        DEFAULT_VALUE_BUF_LENGTH);
        fldInfo->isNull_ = fDef->isNull_;
        fldInfo->isPrimary_ = fDef->isPrimary_;
        fldInfo->isUnique_ = fDef->isUnique_;
        fldInfo->isDefault_ = fDef->isDefault_;
        fldInfo->isAutoIncrement_= fDef->isAutoIncrement_;
        fldInfo->autoVal_ = 0;
        fldInfo->width_ = 0; //TODO
        fldInfo->scale_ = 0; //TODO
        printDebug(DM_SystemDatabase,"One Row inserted into FIELD %x %s",fldInfo, fDef->fldName_);

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
        if (((CFIELD*)data)->tblPtr_ == tptr)
        {
            //remove this element
            fChunk->free(systemDatabase_, data);
            printDebug(DM_SystemDatabase,"One Row deleted from FIELD %x",data);
        }
    }
    return OK;
}

void *CatalogTableFIELD::getFieldInfo(void* tptr, FieldList &list)
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(FieldTableId);
    ChunkIterator fIter = fChunk->getIterator();;
    void *data = NULL;
    void *ptrToAutoVal;
    while (NULL != (data = fIter.nextElement()))
    {
        if (((CFIELD*)data)->tblPtr_ == tptr)
        {
            //add the information to the field list
            CFIELD *fTuple = (CFIELD*)data;
            FieldDef fldDef;
            strcpy(fldDef.fldName_, fTuple->fldName_);
            fldDef.fldName_[IDENTIFIER_LENGTH] = '\0';
            fldDef.type_ = fTuple->type_;
            fldDef.length_ = fTuple->length_;
            fldDef.offset_ = fTuple->offset_;
            fldDef.isDefault_ = fTuple->isDefault_;
            os::memcpy(fldDef.defaultValueBuf_, fTuple->defaultValueBuf_,
                                         DEFAULT_VALUE_BUF_LENGTH);
            fldDef.isNull_ = fTuple->isNull_;
            fldDef.isUnique_ = fTuple->isUnique_;
            fldDef.isPrimary_ = fTuple->isPrimary_;
            fldDef.isAutoIncrement_= fTuple->isAutoIncrement_;
            if(fTuple->isAutoIncrement_){ 
                ptrToAutoVal = &fTuple->autoVal_;
                //os::memcpy(fldDef.autoVal_, fTuple->autoVal_,);
            }
            list.append(fldDef);
        }
    }
    return ptrToAutoVal;
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
            if (((CFIELD*)data)->tblPtr_ == tptr)
            {
                 if(0 == strcmp((char*)((CFIELD*)data)->fldName_, fName))
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
	    if (0 == strcmp(((CINDEX*)data)->indName_, name))
	    {
		    printError(ErrAlready, "Index with name \'%s\' already exists "
				    "on the table \'%s\'.", name, ((CTABLE *)tptr)->tblName_);
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
    CINDEX *indexInfo = (CINDEX*)tupleptr;
    strcpy(indexInfo->indName_, name);
    indexInfo->tblID_ = -1; //Not used currently
    indexInfo->tblPtr_ = tptr;
    indexInfo->numFlds_ = numFlds;
    if (NULL == hChunk)
        indexInfo->indexType_ = treeIndex;
    else
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
         if (0 == strcmp(((CINDEX*)data)->indName_, name))
         {
             //remove this element and store the tuple ptr
             //there will be only one row for this table(Primary key)
             chunk = (Chunk*) ((CINDEX*)data)->chunkPtr_;
             hchunk = (Chunk*) ((CINDEX*)data)->hashNodeChunk_;
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
         if (0 == strcmp(((CINDEX*)data)->indName_, name))
         {
             //remove this element and store the tuple ptr
             //there will be only one row for this table(Primary key)
             chunk = (Chunk*) ((CINDEX*)data)->chunkPtr_;
             hchunk = (Chunk*) ((CINDEX*)data)->hashNodeChunk_;
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

DbRetVal CatalogTableINDEX::setChunkPtr(const char *name, ObjectType type, void *bChunk, void *firstPage, void *curPage) 
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
    ChunkIterator iter = fChunk->getIterator();

    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
         if (0 == strcmp(((CINDEX*)data)->indName_, name))
         {
             //remove this element and store the tuple ptr
             //there will be only one row for this table(Primary key)
             if (type == hIdx) {
                 ((Chunk*) ((CINDEX*)data)->chunkPtr_)->setFirstPage(bChunk);
                 ((Chunk*) ((CINDEX*)data)->chunkPtr_)->setCurPage(bChunk);
                 ((Chunk*)((CINDEX*)data)->hashNodeChunk_)->setFirstPage(firstPage);
                 ((Chunk*)((CINDEX*)data)->hashNodeChunk_)->setCurPage(curPage);
             } else if (type == tIdx) {
                 ((Chunk*) ((CINDEX*)data)->chunkPtr_)->setFirstPage(firstPage);
                 ((Chunk*) ((CINDEX*)data)->chunkPtr_)->setCurPage(curPage);
                 ((CINDEX*)data)->hashNodeChunk_ = bChunk;                 
             } 
             break;
         }
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
         if (((CINDEX*)iptr)->tblPtr_ == tptr) numIndex++;
    }
    return numIndex;
}

ListIterator CatalogTableINDEXFIELD::getIndexListIterater(char *name)
{
   List indexList;
   Chunk *chunk=systemDatabase_->getSystemDatabaseChunk(IndexFieldTableId);        
   ChunkIterator ifIter = chunk->getIterator();
   void *data = NULL;
   while ((data = ifIter.nextElement())!= NULL)
   {
       IndexInfoForDriver *idxInfo = new IndexInfoForDriver();
       if(strcmp( name,((CTABLE*)(((CINDEXFIELD*)data)->tablePtr))->tblName_) == 0)
       {
           strcpy(idxInfo->indexName ,((CINDEX*)(((CINDEXFIELD*)data)->indexPtr))->indName_);
           strcpy(idxInfo->tableName ,((CTABLE*)(((CINDEXFIELD*)data)->tablePtr))->tblName_);
           strcpy(idxInfo->fieldName ,((CFIELD*)(((CINDEXFIELD*)data)->fieldPtr))->fldName_);
           idxInfo->type = ((CINDEX*)(((CINDEXFIELD*)data)->indexPtr))->indexType_ ;
           idxInfo->isUnique = ((CINDEX*)(((CINDEXFIELD*)data)->indexPtr))->isUnique_; 
           idxInfo->isPrimary = ((CFIELD*)(((CINDEXFIELD*)data)->fieldPtr))->isPrimary_;
       indexList.append(idxInfo);
       }
    }
    return indexList.getIterator();
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
         if (((CINDEX*)iptr)->tblPtr_ == tptr) curPos++;
         if ( curPos == position ) return ((CINDEX*)iptr)->indName_;
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
         if (((CINDEX*)iptr)->tblPtr_ == tptr)
         {
             array[i++] = (char*) iptr;
         }
    }
    return;
}

ChunkIterator CatalogTableINDEX::getIterator(void *iptr)
{
    CINDEX *index = (CINDEX*)iptr;
    return ((Chunk*)index->chunkPtr_)->getIterator();
}


int CatalogTableINDEX::getNoOfBuckets(void *iptr)
{
    CINDEX *index = (CINDEX*)iptr;
    return index->noOfBuckets_;
}

int CatalogTableINDEX::getUnique(void *iptr)
{
    CINDEX *index = (CINDEX*)iptr;
    return index->isUnique_;
}
IndexType CatalogTableINDEX::getType(void *iptr)
{
    CINDEX *index = (CINDEX*)iptr;
    return index->indexType_;
}
char* CatalogTableINDEX::getName(void *iptr)
{
    CINDEX *index = (CINDEX*)iptr;
    return index->indName_;
}
int CatalogTableINDEX::getOffsetOfFirstField(void *iptr)
{
    CINDEX *index = (CINDEX*)iptr;
    return ((CFIELD*)(((CINDEXFIELD*)(index->fstIndFld_))->fieldPtr))->offset_;
}
DbRetVal CatalogTableINDEXFIELD::insert(FieldNameList &fldList, void *indexPtr,
                                         void *tblPtr, char **&fptr)

{
    Chunk *tChunk;
    tChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
    ChunkIterator iter = tChunk->getIterator();	
    CINDEXFIELD *fInd=NULL;
    char *fName =NULL;
    void *data = NULL;
    bool isFldInd=false;
    while ((data = iter.nextElement())!= NULL)
    {
        if ((((CINDEX*)data)->tblPtr_==tblPtr) 
              && (((CINDEX*)indexPtr)->numFlds_ == ((CINDEX*)data)->numFlds_) 
              && (((CINDEX*)indexPtr)->indexType_==((CINDEX*)data)->indexType_) 
              && (data != indexPtr) )
        {
	    fldList.resetIter();
	    while (NULL != (fName = fldList.nextFieldName()))
	    {
		isFldInd=false;
                fInd=(CINDEXFIELD*)((CINDEX*)data)->fstIndFld_ ;
		while (fInd)
	    	{
	    	    if (0 == strcmp(((CFIELD *) fInd->fieldPtr)->fldName_, fName))
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
               	printError(ErrAlready, "Index on this field  already exists on table \'%s\' by name \'%s\'", ((CTABLE *)tblPtr)->tblName_, ((CINDEX *)data)->indName_);
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
        fInd=(CINDEXFIELD*)((CINDEX*)indexPtr)->fstIndFld_;
        while(fInd)
        {
             if (0 == strcmp(((CFIELD *) fInd->fieldPtr)->fldName_, fName))
             {
                 printError(ErrAlready,"Composite Index Can't be created with same Name");
                 fInd=(CINDEXFIELD*)((CINDEX*)indexPtr)->fstIndFld_;
                 CINDEXFIELD *fldI;
                 while(fInd)
                 {   
                     fldI=fInd;
                     fInd=fInd->next;
                     tChunk->free(systemDatabase_,fldI); 
                 }
                 return ErrAlready;
             }
             fInd=fInd->next;
        }
        void *fieldptr = tChunk->allocate(systemDatabase_, &rv);
        if (NULL == fieldptr)
        {
            printError(rv, "Could not allocate for USER catalog table");
            return rv;
        }
        CINDEXFIELD *fldInfo = (CINDEXFIELD*)fieldptr;
        fldInfo->tablePtr = tblPtr;
        fldInfo->fieldPtr = (CFIELD*)fptr[i++];
        fldInfo->indexPtr = indexPtr;
	fldInfo->next=(CINDEXFIELD*)((CINDEX*)indexPtr)->fstIndFld_;
	((CINDEX *)indexPtr)->fstIndFld_=fldInfo;
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
        if (((CINDEXFIELD*)data)->indexPtr == iptr)
        {
            //remove this element
            if(((CFIELD *)((CINDEXFIELD*)data)->fieldPtr)->isUnique_) ((CFIELD *)((CINDEXFIELD*)data)->fieldPtr)->isUnique_ = false;
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
        if (((CINDEXFIELD*)data)->indexPtr == index)
        {
            //store the field name
            name = ((CFIELD*)(((CINDEXFIELD*)data)->fieldPtr))->fldName_;
            type = ((CFIELD*)(((CINDEXFIELD*)data)->fieldPtr))->type_;
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
        if (((CINDEXFIELD*)data)->indexPtr == index)
        {
            //add the information to the field list
            CFIELD *fTuple = (CFIELD*)(((CINDEXFIELD*)data)->fieldPtr);
            FieldDef fldDef;
            strcpy(fldDef.fldName_, fTuple->fldName_);
            fldDef.fldName_[IDENTIFIER_LENGTH] = '\0';
            fldDef.type_ = fTuple->type_;
            fldDef.length_ = fTuple->length_;
            fldDef.offset_ = fTuple->offset_;
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
	if(strcmp(indexName,((CINDEX*)(((CINDEXFIELD*)data)->indexPtr))->indName_)!=0)
	{
       	    printf("    <Index Name> %s </Index Name> \n",((CINDEX*)(((CINDEXFIELD*)data)->indexPtr))->indName_);
       	    if(0==((CINDEX*)(((CINDEXFIELD*)data)->indexPtr))->indexType_)
      	        printf("        <Index Type> Hash Index </Index Type> \n");
       	    else
       	        printf("        <Index Type> Tree Index </Index Type> \n");
       	    printf("        <Table Name> %s </Table Name> \n",((CTABLE*)(((CINDEXFIELD*)data)->tablePtr))->tblName_);
       	    printf("        <Field Name> %s </Field Name> \n",((CFIELD*)(((CINDEXFIELD*)data)->fieldPtr))->fldName_);
	}
	else
	{
       	    printf("        <Field Name> %s </Field Name> \n",((CFIELD*)(((CINDEXFIELD*)data)->fieldPtr))->fldName_);
	}
	strcpy(indexName,((CINDEX*)(((CINDEXFIELD*)data)->indexPtr))->indName_);
    }
}

List CatalogTableUSER::getUserList()
{
    List userList;
    Chunk *chk = systemDatabase_->getSystemDatabaseChunk(UserTableId);
    ChunkIterator iter = chk->getIterator();
    void *tptr;
    while (NULL != (tptr = iter.nextElement()))
    {
         Identifier *elem = new Identifier();
         strcpy(elem->name, ((CUSER*)tptr)->userName_);
         userList.append(elem);
    }
    return userList;

}

DbRetVal CatalogTableUSER::insert(const char *name, const char *pass)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(UserTableId);
    DbRetVal rv = OK;
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
            if (0 == strcmp(((CUSER*)data)->userName_, name))
            {
                    printError(ErrAlready, "User with name \'%s\' already exists ", name);
                    return ErrAlready;
            }
    }

    CUSER *usrInfo = (CUSER*)tChunk->allocate(systemDatabase_, &rv);
    if (NULL == usrInfo)
    {
        printError(rv,
                   "Could not allocate for USER catalog table");
        return rv;
    }
    strcpy(usrInfo->userName_, name);
    strcpy(usrInfo->password_, pass);
    //strcpy(usrInfo->password_, os::encrypt(pass, "A0"));
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
        if (strcmp(((CUSER*)data)->userName_, name) == 0)
        {
            //verify the password
            //char * enpass = os::encrypt(pass,"A0");
            char * enpass = (char*) pass;
            if (0 == strcmp(enpass, ((CUSER*)data)->password_))
            {
                isAuthenticated = true;
                if (0 == strcmp(((CUSER*)data)->userName_, DBAUSER))
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
        if (strcmp(((CUSER*)data)->userName_, name) == 0)
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
        if (strcmp(((CUSER*)data)->userName_, name) == 0)
        {
            //change the password
            strcpy(((CUSER*)data)->password_,pass);// os::encrypt(pass, "A0"));
            return OK;
        }
    }
    printError(ErrNotExists,"User %s not exists in catalog table", name);
    return ErrNotExists;
}

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


