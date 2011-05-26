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

DbRetVal CatalogTableINDEX::insert(const char *name, void *tptr, int numFlds, bool isUnique,
                          void* chunk, int bucketSize, void *hChunk, void *&tupleptr)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
    ChunkIterator iter = tChunk->getIterator();

    //Checking for index having same name, proceed further only
    //if no such indexes exists
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
    if (0 == bucketSize) indexInfo->indexType_ = trieIndex;
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
