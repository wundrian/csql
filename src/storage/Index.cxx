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
#include<Index.h>
#include<Allocator.h>
#include<Database.h>
#include<Debug.h>

HashIndex* Index::hIdx = NULL;
TreeIndex* Index::tIdx = NULL;
long Index::usageCount = 0;

Index* Index::getIndex(IndexType type)
{
    if (type == hashIndex) 
    {
        if (NULL == hIdx) hIdx = new HashIndex();
        return hIdx;
    }else if (type == treeIndex) {
        if (NULL == tIdx) tIdx = new TreeIndex();
        return tIdx;
    }
    return NULL;
}
void Index::destroy() 
{
     usageCount--;
     if(!usageCount) {
        if(!hIdx) { delete hIdx; hIdx=NULL; }
        if(!tIdx) { delete tIdx; tIdx=NULL; }
     }
}

