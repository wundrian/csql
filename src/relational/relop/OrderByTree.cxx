/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
 *                                                                         *
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
 * ***************************************************************************/
#include<OrderByTree.h>

//Used for float type field and individual order by clause
void OrderByTree::insertSpecialCaseDataNode(void *data)
{
    if(dataNode.size() == 0){ dataNode.append(data); return;}
    ListIterator iter = dataNode.getIterator();
    ListIterator fldIter = orderByList.getIterator();
    iter.reset();
    int ret=0;
    void *insertedData = NULL;
    void *prevIter = iter.getCurrentListNode();
    void *prev = prevIter;
    bool shouldInsertHappenAtMiddle=false;
    OrderByFldDef *oFldDef = NULL;
    int offset=0;
    char *fldData=NULL, *fldInsertData=NULL;
    bool result=false;
    while (iter.hasElement())
    {
        bool shoudInsertHere=false;
        bool isPrevEqual=false;
        offset=0;
        insertedData = iter.nextElement();
        fldIter.reset();
        while (fldIter.hasElement())
        {
            oFldDef = (OrderByFldDef*) fldIter.nextElement();
            fldData = ((char*)data)+offset;
            fldInsertData = ((char*)insertedData)+offset;
            offset += oFldDef->length;
            result=AllDataType::compareVal(fldData, fldInsertData, OpEquals,oFldDef->type, oFldDef->length);
            if(result)
            {
                shoudInsertHere = true;
                isPrevEqual = true;
                continue;
            }
            else
            {
                result=AllDataType::compareVal(fldData, fldInsertData, OpGreaterThan,oFldDef->type, oFldDef->length);
                if(result)
                {
                    if(oFldDef->isDesc)
                    {
                        shoudInsertHere = true;
                        isPrevEqual = false;
                        continue;
                    }
                    else{
                        if(shoudInsertHere && !isPrevEqual) { isPrevEqual = false; continue;}
                        shoudInsertHere=false; break;
                    }
                }else
                {
                  //data<inserted
                    if(!oFldDef->isDesc)
                    {
                        shoudInsertHere = true;
                        isPrevEqual = false;
                        continue;
                    }
                    else{
                        if(shoudInsertHere && !isPrevEqual ) { isPrevEqual = false; continue;}
                        shoudInsertHere=false; break;
                    }
                }
            }
        }//inner while ends here
        if(shoudInsertHere){
            if(shouldInsertHappenAtMiddle)
                dataNode.addAtMiddle(data, prevIter);
            else
                dataNode.addAtBegin(data);
            return;
        }
        prevIter = prev;
        prev = iter.getCurrentListNode();
        shouldInsertHappenAtMiddle=true;
    }
    dataNode.append(data);
}

DbRetVal OrderByTree::insertDataNode(void *data)
{
    if(!fullOrderBy) {
        insertSpecialCaseDataNode(data);
        return OK;
    }
    dataNode.append(data);
    projMap.insert(data);
    return OK;
}

bool OrderByTree::find(void *data)
{
    void *element = projMap.find(data);
    if (element) return true;
    return false;
}

int OrderByTree::compare(void *element1,void *element2,int size)
{
    return os::memcmp(element1,element2,size);
}

ListIterator OrderByTree::getListIterator()
{
    return dataNode.getIterator();
}

void OrderByTree::removeAll()
{
     dataNode.reset();
     if(fullOrderBy) projMap.removeAll();
     return;
}
