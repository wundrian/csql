#ifndef _db_H_
#define _db_H_

#include "wiscTimer.h"

class DB {
public:

    virtual int createTable (char *) = 0;

    virtual int dropTable (char *) = 0;

    virtual int createIndex (char *idx, char *tbl, char *fld) = 0;

    virtual int dropIndex (char *idx, char *tbl) = 0;

    virtual int connect (char *dsn) = 0;

    virtual int populateTable(char* tblName, int numTups, int valRange) = 0;

    virtual int selectionQuery(int queryNum, class wiscTimer *wt,
              char *form1, char *form2, int tblCard,
              int resCard, int uniq, int verify, int repeatCnt,
              int numParams) = 0;

    virtual int runDelete (int queryNum, class wiscTimer *wT, int bigTups,
              char *big1tbl, char *big2tbl) = 0;

    virtual int runInsert (int queryNum, class wiscTimer *wT, int bigTups,
              char *big1tbl, char *big2tbl) = 0;

    virtual int runUpdate (int queryNum, class wiscTimer *wT, char* col,
              int big1Tbls, char *big1tbl, char *big2tbl) = 0;

    virtual int emptyTable (char *tblName) = 0;

    virtual int disconnect () = 0;

};

#endif
