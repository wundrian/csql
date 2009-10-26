/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H
/**
* @class DbRetVal
* Database Return Value.
* This contains all the error codes returned by all the exposed APIs<br>
* <br/>
* 
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
    ErrUnique        = -21,
    ErrNullViolation = -22,
    ErrPeerResponse  = -23,
    ErrPeerTimeOut   = -24,
    ErrPeerExecFailed= -25,
    ErrNoEffect      = -26,
    ErrNotCached     = -27,
    ErrSyntax        = -28,
    ErrNotPrepared   = -29,
    ErrNotEmpty      = -30,
    ErrReadOnlyCache = -31,
    ErrNoPeer        = -32,
    ErrAutoIncUpdate = -33,
    ErrForeignKeyInsert=-34,
    ErrForeignKeyDelete=-35,
    ErrNullValues      =-36, //used in evaluate on null values 
//  add new error type here
    ErrNote          = -97,
    ErrUnknown       = -98,
    ErrWarning       = -99,
    SplCase          = -100
};
#endif
