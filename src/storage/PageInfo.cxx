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
    //isUsed_ = 0;
    int ret = Mutex::CAS(&isUsed_, isUsed_, 0);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    //hasFreeSpace_ = 0;
    ret = Mutex::CAS(&hasFreeSpace_ , hasFreeSpace_, 0);;
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    //nextPage_ = NULL;
    ret = Mutex::CASL((long*)&nextPage_, (long)nextPage_, 0);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    //nextPageAfterMerge_ = NULL;
    ret = Mutex::CASL((long*)&nextPageAfterMerge_, (long)nextPageAfterMerge_, 0);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    return;
}
void PageInfo::setPageAsUsed(size_t offset)
{
    //isUsed_ = 1;
    int ret = Mutex::CAS(&isUsed_, isUsed_,1);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    //hasFreeSpace_ = 1;
    ret = Mutex::CAS(&hasFreeSpace_ , hasFreeSpace_, 1);;
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    //nextPage_ = NULL;
    ret = Mutex::CASL((long*)&nextPage_, (long)nextPage_, 0);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    if (PAGE_SIZE > offset) {
        //nextPageAfterMerge_ = NULL;
        ret = Mutex::CASL((long*)&nextPageAfterMerge_, (long)nextPageAfterMerge_, 0);
        if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    } else {
        //nextPageAfterMerge_ = ((char*)this)+ offset;
        ret = Mutex::CASL((long*)&nextPageAfterMerge_, 
                   (long) nextPageAfterMerge_ , 
                   (long)(((char*)this)+ offset));
        if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    }
    return;
}
void PageInfo::setFirstPageAsUsed()
{
    //isUsed_ = 1;
    int ret = Mutex::CAS(&isUsed_, 0,1);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    //hasFreeSpace_ = 1;
    ret = Mutex::CAS(&hasFreeSpace_ , hasFreeSpace_, 1);;
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    //nextPageAfterMerge_ = NULL;
    ret = Mutex::CASL((long*)&nextPageAfterMerge_, (long)nextPageAfterMerge_, 0);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    //nextPage_ = NULL;
    ret = Mutex::CASL((long*)&nextPage_, (long)nextPage_, 0);
    if (ret != 0) printError(ErrSysFatal, "Fatal:CAS Failed");
    return;
}
