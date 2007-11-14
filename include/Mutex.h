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
#ifndef MUTEX_H
#define MUTEX_H
#include<os.h>
    #if defined(sparc)
    typedef unsigned char Lock;
    #elif defined (i686)
    typedef unsigned int Lock;
    #endif
class Mutex
{

    #if defined(sparc) || defined(i686)
    Lock lock;
    #else
    pthread_mutex_t mutex_;
    #endif
    public:
    Mutex();
    int init();
    int getLock();
    int tryLock(int tries=5, int waitmsecs=10);
    int releaseLock();
    int destroy();
};

#endif
