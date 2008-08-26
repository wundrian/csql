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
#include<Allocator.h>
#include<os.h>
#include<Config.h>

void PageInfo::setPageAsUsed(size_t offset)
{
    isUsed_ = 1;
    hasFreeSpace_ = 1;
    nextPage_ = NULL;
    if (PAGE_SIZE > offset)
        nextPageAfterMerge_ = NULL;
    else
        nextPageAfterMerge_ = ((char*)this)+ offset;
}
void PageInfo::setFirstPageAsUsed()
{
    isUsed_ = 1;
    hasFreeSpace_ = 1;
    nextPageAfterMerge_ = NULL;
    nextPage_ = NULL;
}
