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
#include<Debug.h>

void PageInfo::setPageAsFree()
{
    int ret = Mutex::CASGen(&isUsed_, isUsed_, 0);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    ret = Mutex::CASGen(&flags , flags, 0);;
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    ret = Mutex::CASL((long*)&nextPage_, (long)nextPage_, 0);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    ret = Mutex::CASL((long*)&nextPageAfterMerge_, (long)nextPageAfterMerge_, 0);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    return;
}

void PageInfo::setPageAsUsed(size_t offset)
{
    int ret = Mutex::CAS(&isUsed_, isUsed_,1);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    InUse flagToSet=0;
    SETBIT(flagToSet, HAS_SPACE);
    ret = Mutex::CASGen(&flags, flags, flagToSet);;
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    ret = Mutex::CASL((long*)&nextPage_, (long)nextPage_, 0);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    if (PAGE_SIZE > offset) {
        ret = Mutex::CASL((long*)&nextPageAfterMerge_, (long)nextPageAfterMerge_, 0);
        if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    } else {
        ret = Mutex::CASL((long*)&nextPageAfterMerge_, 
                   (long) nextPageAfterMerge_ , 
                   (long)(((char*)this)+ offset));
        if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    }
    return;
}

