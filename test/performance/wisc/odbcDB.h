#ifndef _odbcDB_H_
#define _odbcDB_H_

#include "db.h"

class odbcDB : DB {
public:

    int createTable (char *);

    int dropTable (char *);

    int createIndex (char *idx, char *tbl, char *fld);

    int dropIndex (char *idx, char *tbl);

    int connect (char *dsn);

    int populateTable(char* tblName, int numTups, int valRange);

    int selectionQuery (int queryNum, class wiscTimer *wt,
              char *form1, char *form2, int tblCard,
              int resCard, int uniq, int verify, int repeatCnt,
              int numParams);

    int runDelete(int queryNum, class wiscTimer *wT, int bigTups,
                 char *big1tbl, char *big2tbl);

    int runInsert(int queryNum, class wiscTimer *wt, int bigTups,
                 char *big1tbl, char *big2tbl);

    int runUpdate(int queryNum, class wiscTimer *wt, char* col, int bigTups,
                 char *big1tbl, char *big2tbl);

    int emptyTable (char *tblName);

    int disconnect ();

};
#endif

