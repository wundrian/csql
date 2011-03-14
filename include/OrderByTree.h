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
#ifndef ORDERBYTREE_H 
#define ORDERBYTREE_H 
#include<os.h>
#include<Util.h>
#include<DataType.h>
#include<HeapAllocator.h>

class DllExport OrderByFldDef
{
    public:
    char fldName[IDENTIFIER_LENGTH];
    DataType type;
    int length;
    void *bindBuf;
    bool isDesc;
    bool alreadyBinded;
    bool isNull;
    int fldPos;
    OrderByFldDef()
    {
        strcpy(fldName, "");
        type=typeUnknown;
        length=0;
        bindBuf=NULL;
        isDesc= false;
        alreadyBinded=false;
        isNull = false;
        fldPos=0;
    }
};

enum OrderByType
{
    Asc=0,
    Desc,
    UnKnown,
};
class DllExport OrderByTree
{
    OrderByType type;
    int keySize;
    bool isDistinct;
    List dataNode;
    List orderByList;
    bool fullOrderBy;
    HashMap projMap; //used in distinct projection

    public:
    OrderByTree(){ isDistinct =false; fullOrderBy = false; keySize=0; type = UnKnown; dataNode.reset();}
    DbRetVal insertDataNode(void *data);
    bool find(void *data);

    //Used for float type field and individual order by clause
    void insertSpecialCaseDataNode(void *data); 

    void setKeySize(int size){ keySize = size; projMap.setKeySize(size);}
    int getKeySize(){return keySize;}
    void setDistinct(bool dist){ isDistinct = dist;}
    bool getDistinct(){return isDistinct;}
    void setOrderByType(OrderByType oType){ type = oType;}
    OrderByType getOrderByType(){ return type; }
    int compare(void *element1,void *element2,int size);
    ListIterator getListIterator();
    void setOrderByList(List oList) { orderByList = oList; }
    void setFullOrderBy() {fullOrderBy = true; } 
    void setOrdIntNoNull() { projMap.setGrpIntNoNull(); }
    void removeAll();
};

#endif
