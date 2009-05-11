/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <os.h>
#include <SqlLogConnection.h>
#include <CSql.h>

FileSend::FileSend()
{
    char fileName[1024];
    sprintf(fileName, "%s/csql.db.cur", Conf::config.getDbFile());
    fdRedoLog = open(fileName, O_WRONLY|O_CREAT| O_APPEND, 0644);
}

DbRetVal FileSend::prepare(int txnId, int stmtId, int len, char *stmt) 
{
    if (fdRedoLog < 0) return ErrBadArg;
    int datalen = 5 * sizeof(int) + os::align(len); // for len + txnId + msg type + stmtId + len + string
    char *buf = (char*) malloc(datalen);
    char *msg = buf;
    //Note:: msg type is taken as -ve as we need to differentiate between 
    //statement id and logtype during recovery.
    *(int*) msg = -1;
    if (strlen(stmt) > 6 && ( strncasecmp(stmt,"CREATE", 6) == 0 || strncasecmp(stmt,"DROP", 4) == 0 ))
        *(int*)msg = -4; //means prepare and execute the stmt
    msg = msg+sizeof(int);
    *(int *)msg = datalen;
    msg = msg+sizeof(int);
    *(int *)msg = txnId;
    msg = msg+sizeof(int);
    *(int *)msg = stmtId;
    msg = msg+ sizeof(int);
    *(int *)msg = os::align(len);
    msg = msg+ sizeof(int);
    msg[len-1] = '\0';
    strcpy(msg, stmt);
    int ret = os::write(fdRedoLog, buf, datalen);     
    ::free(buf);
    //if (ret == datalen) { printf("log written successfully %d\n", ret); return OK; }
    if (ret == datalen) { return OK; }
    return ErrOS;
};

DbRetVal FileSend::commit(int len, void *data)
{
    if (fdRedoLog < 0) return ErrBadArg;
    char *dat=(char*)data - sizeof(int);
    *(int*)dat = -2; //type 2->commit
    int ret = write(fdRedoLog, dat, len+sizeof(int));     
    //if (ret == len+sizeof(int)) { printf("log written successfully %d\n", ret); return OK; }
    if (ret == len+sizeof(int)) { return OK; }
    return ErrOS;
}
DbRetVal FileSend::free(int txnId, int stmtId)
{
    int buflen =  4 *sizeof(int);
    char *msg = (char *) malloc(buflen);
    char *ptr = msg;
    *(int*)ptr = -3;
    ptr += sizeof(int);
    *(int *)ptr = 3 * sizeof(int); // for len + txnId + stmtId
    ptr += sizeof(int);
    *(int *)ptr = txnId;
    ptr += sizeof(int);
    *(int *)ptr = stmtId;
    printDebug(DM_SqlLog, "stmtID sent = %d\n", *(int *)ptr);
    int ret = write(fdRedoLog, msg, buflen);
    //if (ret == buflen) { printf("log written successfully %d\n", ret); return OK; }
    if (ret == buflen) { return OK; }
    return ErrOS;
}
