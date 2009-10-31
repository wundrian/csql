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
#include<Table.h>
#include<Index.h>
#include<CatalogTables.h>
#include<Lock.h>

TableDef::~TableDef()
{
    reset();
}
void TableDef::reset()
{
    fldList.removeAll();
    fldCount = 0;
}
int TableDef::addField(const char *name,  DataType type, size_t length,
                 const void *defaultValue, bool notNull, bool autoIn)
{
    if (name == NULL) return (int)ErrBadArg;
    if(strlen(name)>IDENTIFIER_LENGTH)
    {
        printError(ErrBadRange,"Field name should not exceed 64 character");
        return (int)ErrBadRange;
    }
    // The following code checks for duplicates
    FieldIterator iter = getFieldIterator();
    while (iter.hasElement())
    {
        FieldDef *def = iter.nextElement();
        if (! strcmp(def->fldName_, name)) {
            printError(ErrAlready, "Field %s already Exists", name);
            return (int) ErrAlready;
        }
    }

    if (!Util::isIdentifier((char*)name)) { 
        printError(ErrBadArg, "fieldname contains invalid characters");
        return (int) ErrBadArg;
    }
    FieldDef fldDef;
    strcpy(fldDef.fldName_, name);
    fldDef.fldName_[IDENTIFIER_LENGTH] = '\0';
    fldDef.type_ = type;
    fldDef.length_ = AllDataType::size(type, length);
    fldDef.bindVal_=NULL;
    if (defaultValue != NULL)
    {
        fldDef.isDefault_ = true;
        if (typeBinary == type) {
            const char *p = (const char *) defaultValue;
            while (*p != '\0') {
                if (! isxdigit((int)(*p++)) ) {
                    printError(ErrBadArg, "Invalid hexadecimal value");
                    return (int) ErrBadArg;
                }
            }
        } 
        os::memcpy(fldDef.defaultValueBuf_, defaultValue, DEFAULT_VALUE_BUF_LENGTH);
    }
    else
    {
        fldDef.isDefault_ = false;
        os::memset(fldDef.defaultValueBuf_,0, DEFAULT_VALUE_BUF_LENGTH);
    }
    fldDef.isNull_ = notNull;
    fldDef.isAutoIncrement_ = autoIn;
    //os::memset(fldDef.autoVal_,0, DEFAULT_VALUE_BUF_LENGTH);
    switch(type)
    {
        case typeString :
        case typeVarchar:
        case typeBinary :
            fldDef.length_ = os::align(length);
            break;
        default:
            fldDef.length_ = os::align(AllDataType::size(type));
            break;
    }
    fldDef.offset_ = fldList.getTupleSize();
    int ret = fldList.append(fldDef);
    if (0 == ret)  fldCount++;
    return ret;
}

int TableDef::dropField(const char *name)
{
    int ret = fldList.remove(name);
    if (0 == ret) fldCount--;
    return ret;
}

int TableDef::getFieldCount()
{
    return fldCount;
}

size_t TableDef::getTupleSize()
{
    size_t length = 0;
    FieldIterator iter = getFieldIterator();
    while (iter.hasElement())
    {
        FieldDef *def = iter.nextElement();
        if (def->type_ == typeVarchar) length += sizeof (void *);
        else length = length + def->length_;
    }
    return length;
}
 
bool TableDef::isVarcharPresentInSchema(FieldIterator &iter)
{
    while (iter.hasElement())
    {
        FieldDef *fDef = iter.nextElement();
        if (fDef->type_ == typeVarchar) return true;
    }
    return false;
}
