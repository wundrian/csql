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
#ifndef RECOVER_H
#define RECOVER_H
#include <AbsSqlStatement.h>
#include <SqlConnection.h>
#include <SqlStatement.h>

class DllExport Recovery
{
    void *stmtBuckets;

    //contains pointer to start address of the mapped redo log file
    //used to traverse till the end of the mapping during redo log processing
    public:
    char *iter;
    Recovery(){ 
        stmtBuckets = NULL;
        iter = NULL;
    }
    void setStmtBucket(void *ptr) { stmtBuckets = ptr; }
    ~Recovery() { 
        //do not free stmtBuckets 
    }

    void addToHashTable(int stmtID, AbsSqlStatement* sHdl, char *stmtstr);
    void removeFromHashTable(int stmtID);
    AbsSqlStatement *getStmtFromHashTable(int stmtId);
    bool isStmtInHashTable(int stmtID);
    void freeAllStmtHandles();
    DbRetVal filterAndWriteStmtLogs();
    DbRetVal readAndPopulateStmts(AbsSqlConnection *conn, bool list = false, bool interactive = false);
    DbRetVal iterateStmtLogs(AbsSqlConnection *conn, void *startAddr, int size, bool list=false, bool interactive = false);

    int applyRedoLogs(char *redoFile, AbsSqlConnection *conn, bool list = false, bool interactive = false);

#if (defined MMDB && defined EMBED)
    DbRetVal recoverCsqlDB(SqlConnection *conn);
    DbRetVal recoverSystemAndUserDB(SqlConnection *conn);
    DbRetVal applySchemaFile(FILE *fp, SqlConnection *conn);
    char getQueryFromSchemaFile(FILE *fp, char *buf);
#endif

private:
    //before calling below 4 handleXXX methods, iter should be set
    DbRetVal handlePrepare( AbsSqlConnection *conn, bool list=false, bool interactive = false);
    DbRetVal handleCommit(AbsSqlConnection *conn, void *startAddr, long size, bool list=false, bool interactive = false);
    DbRetVal handleFree(bool list=false, bool interactive = false);
    DbRetVal handlePrepareAndExecute(AbsSqlConnection *conn, bool list=false, bool interactive = false);
};

#endif
