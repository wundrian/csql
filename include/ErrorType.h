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
#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H
/**
* @class DbRetVal
* Database Return Value.
* This contains all the error codes returned by all the exposed APIs<br>
* <br/>
* @author Prabakaran Thirumalai
*/

enum DbRetVal
{
    OK               =  0, /**< OK. No error. Operation succeded. */
    ErrSysFatal      = -1, 
    ErrSysInit       = -2,
    ErrNoPrivilege   = -3,
    ErrSysInternal   = -4,
    ErrNotExists     = -5,
    ErrNoMemory      = -6,
    ErrNotFound      = -7,
    ErrAlready       = -8,
    ErrOS            = -9,
    ErrNotReady      = -10,
    ErrNotOpen       = -11,
    ErrNoResource    = -12,
    ErrBadRange      = -13,
    ErrBadCall       = -14,
    ErrLockTimeOut   = -15,
    ErrBadArg        = -16,
    ErrNotYet        = -17,
    ErrNoConnection  = -18,
    ErrSyntaxError   = -19,
    ErrInvalidExpr   = -20,
    SplCase          = -100
};
#endif
