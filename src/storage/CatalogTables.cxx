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

#include "Parser.h"
#include "PredicateImpl.h"

char ChunkName[MAX_CHUNKS][CHUNK_NAME_LEN]={
    "UserChunkTableId",
    "LockTableHashBucketId",
    "LockTableMutexId",
    "LockTableId",
    "TransHasTableId",
    "UndoLogTableId",
    "","","","",
    "DatabaseTableId",
    "UserTableId",
    "TableTableId",
    "FieldTableId",
    "AccessTableId",
    "IndexTableId",
    "IndexFieldTableId",
    "ForeignKeyTableId",
    "ForeignKeyFieldTableId",
        "GrantTableId"
    };


DbRetVal CatalogTableTABLE::insert(const char *name, int id, size_t size,
                    int numFlds, void* chunk, void *&tptr, void *vcchunk, Chunk *grantsPtr, const char *ownerName)
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
    strcpy(tableInfo->owner_, ownerName);
    tableInfo->tblID_ = id;
    tableInfo->length_ = size;
    tableInfo->numFlds_ = numFlds;
    tableInfo->numIndexes_ = 0;
    tableInfo->chunkPtr_ = chunk;
    tableInfo->varcharChunkPtr_ = vcchunk;
    tableInfo->grantsPtr_ = grantsPtr;
    printDebug(DM_SystemDatabase,"One Row inserted into TABLE %x %s",tptr, name);
    return OK;
}

DbRetVal CatalogTableTABLE::renameTable( const char *oldName,const char *newName)
{
     Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(TableTableId);
     ChunkIterator iter = tChunk->getIterator();
     void *data = NULL;
     bool isTableExits = false ;
     CTABLE *oldTable = NULL;
     while ((data = iter.nextElement())!= NULL)
     {
         if (0 == strcmp(((CTABLE*)data)->tblName_, oldName))
         {
             oldTable =(CTABLE*)data;
             isTableExits = true;
         }
         if (0 == strcmp(((CTABLE*)data)->tblName_,newName))
         {
             printError(ErrNotExists,"A Table with name %s already exists", newName);
             return ErrNotExists;
         }
     }
     strcpy(oldTable->tblName_, newName);
     if(!isTableExits){
        printError(ErrNotExists,"Table %s not exists in TABLE catalog table", oldName);
        return ErrNotExists;
     }
 
     tChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
     iter = tChunk->getIterator();
     char tmpName[IDENTIFIER_LENGTH]="";
     sprintf(tmpName, "%s_idx1_Primary", oldName); 
     while ((data = iter.nextElement())!= NULL)
     {
         if(strcmp(((CINDEX*)data)->indName_ ,tmpName)==0) {
                sprintf(((CINDEX*)data)->indName_, "%s_idx1_Primary", newName);
                break;
         }
     }
    return OK;
}

DbRetVal CatalogTableTABLE::renameIndex( const char *oldName,const char *newName)
{
     Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(IndexTableId);
     ChunkIterator iter = tChunk->getIterator();
     void *data = NULL;
     bool isIndexExits = false ;
     CINDEX *oldIndex = NULL;
     while ((data = iter.nextElement())!= NULL)
     {
         if (0 == strcmp(((CINDEX*)data)->indName_, oldName))
         {
             oldIndex=(CINDEX*)data;
             isIndexExits = true;
         }
         if (0 == strcmp(((CINDEX*)data)->indName_,newName))
         {
             printError(ErrNotExists,"A Index with name %s already exists", newName);
             return ErrNotExists;
         }
     }
     if(!isIndexExits){
        printError(ErrNotExists,"Index %s not exists in INDEX catalog table", oldName);
        return ErrNotExists;
     }
     strcpy(oldIndex->indName_, newName);

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

DbRetVal CatalogTableTABLE::getGrantsPtr(const int tblId, Chunk *&grantsPtr) const
{
    Chunk *chk = systemDatabase_->getSystemDatabaseChunk(TableTableId);
    ChunkIterator iter = chk->getIterator();;
    CTABLE *tptr;

    while (NULL != (tptr = (CTABLE*)iter.nextElement()))
    {
        if (tptr->tblID_ == tblId)
        {
            grantsPtr = tptr->grantsPtr_;
            return OK;
        }
    }

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

bool CatalogTableTABLE::isOwner(int tblId, const char* userName)
{
    Chunk *chk = systemDatabase_->getSystemDatabaseChunk(TableTableId);
    ChunkIterator iter = chk->getIterator();;
    void *tptr;
    while (NULL != (tptr = iter.nextElement()))
    {
         if (tblId == ((CTABLE*)tptr)->tblID_)
         {
             return (0 == strcmp(userName, ((CTABLE*)tptr)->owner_));
         }
    }
    return false;
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

DbRetVal CatalogTableFIELD::renameField(const char *tableName, const char *oldName, const char *newName)
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(FieldTableId);
    ChunkIterator iter = fChunk->getIterator();
    void *data = NULL;
    bool isFieldExists=false;
    while ((data = iter.nextElement())!= NULL)
    {
        if ((strcmp(((CFIELD*)data)->fldName_,newName)== 0) && (strcmp(((CTABLE *)((CFIELD*)data)->tblPtr_)->tblName_,tableName) == 0) )
        {
           printError(ErrAlready,
                  "New Field Name '%s' already exists in the table.", newName);
           return ErrAlready;
        }
    }
    iter = fChunk->getIterator();
    while ((data = iter.nextElement())!= NULL)
    {
        if ((strcmp(((CFIELD*)data)->fldName_,oldName)== 0) && (strcmp(((CTABLE *)((CFIELD*)data)->tblPtr_)->tblName_,tableName) == 0) )
        {
           strcpy(((CFIELD*)data)->fldName_,newName);
           isFieldExists = true;
           break;
        }
    }
    if(!isFieldExists){
        printError(ErrNotExists, "Old Field Name '%s' does not exist in table",
                                                                      oldName);
        return ErrNotExists;
    }
    return OK;
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

DbRetVal CatalogTableGRANT::insert(unsigned char priv, int tblId, std::string userName,
            const PredicateImpl *rootPred, List conditionValues)
{
    // are we granting any privileges at all?
    if (!priv)
    {
        printError(ErrSyntaxError, "No privileges selected to grant. Choose at least one.");
        return ErrSyntaxError;
    }
    
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(GrantTableId);
    DbRetVal rv = OK;
    
    ChunkIterator iter = tChunk->getIterator();
    void *data = NULL;
    while ((data = iter.nextElement())!= NULL)
    {
        CGRANT* elem = (CGRANT*)data;
        if (0 == strncmp(elem->userName_, userName.c_str(), IDENTIFIER_LENGTH)
                && elem->tblID_ == tblId)
        {
            if ((elem->privileges | priv) == elem->privileges)
            {
                printError(ErrNoEffect, "Privileges are already granted");
                return OK;
            }
            
            // we're adding privileges
            elem->privileges |= priv;
            return OK;
        }
    }
    
    /* okay, no privileges on this table at all, create a new chunk */
    Chunk *grantsPtr = NULL;
    CatalogTableTABLE tables(systemDatabase_);
    if (OK != tables.getGrantsPtr(tblId, grantsPtr))
    {
        printError(rv, "Unable to find table for id %d", tblId);
        return rv;
    }

    CGRANT* grantInfo = (CGRANT*)tChunk->allocate(systemDatabase_, &rv);
    if (NULL == grantInfo)
    {
        printError(rv, "Could not allocate memory chunk for GRANT catalog table");
        return rv;
    }
    
    strncpy(grantInfo->userName_, userName.c_str(), IDENTIFIER_LENGTH);
    grantInfo->tblID_ = tblId;
    grantInfo->privileges = priv;
    
    if (NULL != rootPred)
    {
        rv = createPredicateChunk(rootPred, conditionValues, grantsPtr, grantInfo->predPtr);
        if (OK != rv)
        {
            tChunk->free(systemDatabase_, grantInfo);
            return rv;
        }
    }
    
    return OK;
}

DbRetVal CatalogTableGRANT::remove(unsigned char priv, int tblId, std::string userName)
{
    Chunk *tChunk = systemDatabase_->getSystemDatabaseChunk(GrantTableId);
    ChunkIterator iter = tChunk->getIterator();
    CGRANT *elem = NULL;
    while ((elem = (CGRANT*)iter.nextElement())!= NULL)
    {
        if (0 == userName.compare(elem->userName_) && elem->tblID_ == tblId)
        {
            // remove all privileges (priv dominates elem->privileges)?
            if (elem->privileges == (elem->privileges & priv)) {
                // TODO free the predPtr if available (via the Chunk
                // that holds it: iterate over table->grantsPtr and
                // check for the unique chunk id)
                tChunk->free(systemDatabase_, elem);
                return OK;
            }
            
            // only remove part of the privileges
            elem->privileges &= ~priv;

            // (userName, tblId) is the PK for this table, we can quit looking
            return OK;
        }
    }
    printError(ErrNotExists,"User %s does not exist in catalog table", userName.c_str());
    return ErrNotExists;
}

unsigned char CatalogTableGRANT::getPrivileges(int tblId, const char* userName)
{
    Chunk* tChunk = systemDatabase_->getSystemDatabaseChunk(GrantTableId);
    ChunkIterator iter = tChunk->getIterator();
    void* data = NULL;
    while ((data = iter.nextElement()) != NULL)
    {
        CGRANT* elem = (CGRANT*)data;
        if (0 == memcmp(elem->userName_, userName, IDENTIFIER_LENGTH)
                && tblId == elem->tblID_)
        {
            return elem->privileges;
        }
    }
    
    return PRIV_NONE;
}

DbRetVal CatalogTableGRANT::getPredicate(int tblId, const char *userName, Predicate *&pred, List &cVals) const
{
    Chunk* tChunk = systemDatabase_->getSystemDatabaseChunk(GrantTableId);
    ChunkIterator iter = tChunk->getIterator();
    CGRANT *elem = NULL;
    while ((elem = (CGRANT*)iter.nextElement()) != NULL)
    {
        if (0 == memcmp(elem->userName_, userName, IDENTIFIER_LENGTH)
                && tblId == elem->tblID_)
        {
            if (NULL != elem->predPtr)
            {
                if (PredicateImpl::SERIALIZED_VERSION != *((char*)elem->predPtr))
                {
                    pred = NULL;
                    return ErrSysInternal;
                }
                pred = PredicateImpl::unserialize(((char*)elem->predPtr) + 1, cVals);
            }
            else
            {
                pred = NULL;
            }

            return OK; // no point in looking further
        }
    }
    
    // we got here because we haven't found any restrictions.
    // at this point user may be owner or not a privileged user. Either way,
    // he got no Predicate we can return, signal this to the caller
    pred = NULL;
    
    return OK;
}

DbRetVal CatalogTableGRANT::createPredicateChunk(const PredicateImpl *rootPred, List conditionValues,
            Chunk *predChunk, void *&dataPtr)
{
    /* first step: calculate total space needed to store ConditionValue list and serialized PredicateImpl tree */
    const size_t arraySize = 1 /*PredicateImpl::SERIALIZED_VERSION */
      + PredicateImpl::SERIALIZED_SIZE * rootPred->treeSize(); /* nodes */
    size_t varSize = 0; /* for parsedString from ConditionValues */
    
    ConditionValMap cValues;
    ListIterator it = conditionValues.getIterator();
    ConditionValue *cValue;
    while (NULL != (cValue = (ConditionValue*)it.nextElement()))
    {
        // no need to copy parsedString, it will be around for the rest of the statement runtime
        // and be copied by PredicateImpl::serialize before that
        cValues.insert(std::make_pair(&cValue->value, *cValue));
        varSize += strlen(cValue->parsedString) + 1;
    }

    /* second: allocate enough memory, take care not to loose the data pointer! */
    DbRetVal rv = OK;
    dataPtr = predChunk->allocate(systemDatabase_, arraySize + varSize, &rv);
    if (OK != rv)
    {
        dataPtr = NULL;
        printError(rv, "Unable to allocate predChunk memory for condition values.");
        return rv;
    }
    
    /* finally, PredicateImpl can take care of serializing itself  (and cValues!) to dataPtr */
    *((char *)dataPtr) = PredicateImpl::SERIALIZED_VERSION;
    rootPred->serialize((char*)dataPtr + 1, cValues, ((char*)dataPtr + arraySize + 1));

    return OK;
}
