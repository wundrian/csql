
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "support.h"
#include "db.h"

#include "odbcDB.h"

#define MAX_QUERIES 33

/* variables used for timing */

int verboseOut = 0;     /* verboseOut flag */

int verify = 0;      /* Flag set to 1 if "-v" is specified, verify means
                        count all the tuples and print out a message if they
                        don't match the expected value
                      */

int modify = 0;      /* Flag to indicate whether or not to run the modification
                        queries. If set, tables are deleted on exit
                      */

int build = 0;       /* Flag set to 1 if "-b" is
                        specified, build means to populate
                        the tables with the data and run
                        the modification tests.
                      */

int readOnly = 0;    /* Flag to indicate whether or not we are set for read-only
                        transactions.
                      */

long numSmallTblTups = 1000;        /* # of rows for the small table */

long numBigTblTups = 10000;         /* # of rows for the big tables */

extern unsigned int querySelection;        /* Query specification, 1 bit per query */

/* Table names */
#define SMALLTBLNAME  "small"
#define BIG1TBLNAME   "big1"
#define BIG2TBLNAME   "big2"
#define BPRIMETBLNAME "bprime"

#define NUMTABLES 4

static char *tableNames[NUMTABLES] = {
     SMALLTBLNAME, BIG1TBLNAME, BIG2TBLNAME, BPRIMETBLNAME,
};

void
usage(char *prog)
{
    char  *progname;

    // Get base name of program
    progname = strrchr(prog, '/');

    if (progname == 0)
        progname = prog;
    else
        progname++;

    /* Print the usage message */

    fprintf(stderr,
            "Usage:\t%s [-?] [-c <string>] [-v] [-verify] [-b] [-m] [-q <query_spec>]\n"
            "  -?                  Same as -h.\n"
            "  -v                  Verbose trace messages\n"
            "  -q <query_spec>     Specifies a comma-separated list of query numbers or\n"
            "                      ranges (e.g., -q 1,3,5-7,10-14,25). If not specified,\n"
            "                      ALL 32 queries are selected.\n"
            "  -b                  Build data store.\n"
            "  -m                  Run modify transactions (deletes data when done).\n"
            "  -verify             Enables verification.\n"
            "  -readonly           Set Queries to use readonly transactions.\n",
            progname
           );
}

int populateDatabase (class DB *db, int empty)
{
    int rc = 0;
    int i;

    srand48(12345678);

    if (empty)
        for (i=0; i<NUMTABLES; i++)
            db->emptyTable (tableNames[i]);

    rc += db->populateTable(SMALLTBLNAME, numSmallTblTups, numSmallTblTups);

    rc += db->populateTable(BPRIMETBLNAME, numBigTblTups/10, numBigTblTups);

    rc += db->populateTable(BIG1TBLNAME, numBigTblTups, numBigTblTups);

    rc += db->populateTable(BIG2TBLNAME, numBigTblTups, numBigTblTups);

    return rc;
}

void
get_args(int argc, char **argv)
{
    int i = 1;

    while (i < argc) {

        if (!strcmp(argv[i], "-?")) {
            usage(argv[0]);
            exit(1);
        }
        else if ( !strcmp("-verify", argv[i]) ) {
            verify = 1;
            if (verboseOut)
                printf ("Verification enabled.\n");
            i += 1;
        }
        else if (!strcmp("-q", argv[i])) {
            if (i + 1 >= argc) {
                usage(argv[0]);
                exit(1);
            }
            if (setQueries(argv[i+1])) {
                usage(argv[0]);
                exit(1);
            }
            i += 2;
        }
        else if ( !strcmp("-b", argv[i]) ) {
            build = 1;
            if (verboseOut)
                printf ("Data store build enabled.\n");
            i += 1;
        }
        else if (!strcmp("-v", argv[i])) {
            verboseOut = 1;
            printf ("Verbose Tracing Enabled.\n");
            i += 1;
        }
        else if (!strcmp("-readonly", argv[i])) {
            readOnly = 1;
            if (verboseOut)
                printf ("Readonly transaction set for Queries.\n");
            i += 1;
        }
        else if (!strcmp("-m", argv[i])) {
            modify = 1;
            if (verboseOut)
                printf ("Modification queries enabled.\n");
            i += 1;
        }
        else {
            usage(argv[0]);
            exit(1);
        }
    }
}

int
main(int argc, char *argv[])
{
    int   i, rc;
    char  *connect_string = 0;
    char  queryBuf1[512];
    char  queryBuf2[512];
    class wiscTimer *timer[MAX_QUERIES];
    class DB *db = 0;


    /* parse the command line arguments */

    get_args(argc, argv);

    for (i=0; i<MAX_QUERIES; i++)
        timer[i] = new wiscTimer();

    class odbcDB *odbcdb = new odbcDB;
    db = (class DB *) odbcdb;

    if (!db) {
        fprintf (stderr, "Runtime error - Test not specified at compile time.\n");
        exit (2);
    }

    rc = db->connect (connect_string);

    if (rc) {
        printf ("ERROR in connection\n");
        exit(1);
    }

    //printf ("build = %d\n", build);

    if (build) {
        /* Delete and recreate the tables */

        for (i=0; i<NUMTABLES; i++) {
            db->dropTable (tableNames[i]);
            rc = db->createTable (tableNames[i]);
            if (rc)
            {
               printf("Create Tables failed"); exit(1);
            }
        }

        populateDatabase (db, 0);

        if (verboseOut)
            printf ("Database Population Complete.\n");

    }
    else {
        /* Drop indexes so Non-Indexed Queries */
        db->dropIndex ("idx1", "small");
        db->dropIndex ("idx2", "small");
        db->dropIndex ("idx3", "big1");
        db->dropIndex ("idx4", "big1");
        db->dropIndex ("idx5", "big2");
        db->dropIndex ("idx6", "big2");
    }

    /* execute the non-indexed queries */

    if (verboseOut)
        printf ("Running Non-Indexed Queries...\n");

    /* query 1 - 1% selection on large table, no index */

    rc = db->selectionQuery(1, timer[1],
                       "select * from big1 where unique2 between %d and %d",
                       "select * from big2 where unique2 between %d and %d",
                       numBigTblTups, numBigTblTups/100, 0, verify, 2, 2);
    if (rc)
        printf ("Query 1 failed\n");

    /* query 2 - 10% selection on large table, no index */

    rc = db->selectionQuery(2, timer[2],
                       "select * from big1 where unique2 between %d and %d",
                       "select * from big2 where unique2 between %d and %d",
                        numBigTblTups, numBigTblTups/10, 0, verify, 5, 2);
    if (rc)
        printf ("Query 2 failed\n");

    /* query 9 - one join with range-selected input, no index */

    sprintf(queryBuf1,
            "select * from big1, big2 where big1.unique2 = big2.unique2 and big2.unique2 < %d",
            numBigTblTups/10);
    sprintf(queryBuf2,
            "select * from big1, big2 where big1.unique2 = big2.unique2 and big1.unique2 < %d",
            numBigTblTups/10);

    rc = db->selectionQuery(9, timer[9], queryBuf1, queryBuf2,
                       numBigTblTups, numBigTblTups/10, 0, verify, 2, 0);
    if (rc)
        printf ("Query 9 failed\n");

    /* query 10 - single join, no index */

    rc = db->selectionQuery(10, timer[10],
                       "select * from big1, bprime where big1.unique2 = bprime.unique2",
                       "select * from big2, bprime where big2.unique2 = bprime.unique2",
                       numBigTblTups, numBigTblTups/10, 0, verify, 2, 0);
    if (rc)
        printf ("Query 10 failed\n");

    // query 11 - two joins with filtered input, no index 
/*
    sprintf(queryBuf1, "select * from small, big1, big2 "
            "where  big1.unique2 = big2.unique2 and "
            "small.unique2 = big1.unique2 and "
            "big1.unique2 < %d", numBigTblTups/10);

    sprintf(queryBuf2, "select * from small, big2, big1 "
            "where  big2.unique2 = big1.unique2 and "
            "small.unique2 = big2.unique2 and "
            "big2.unique2 < %d", numBigTblTups/10);

    rc = db->selectionQuery(11, timer[11], queryBuf1, queryBuf2,
            numBigTblTups, numBigTblTups/10, 0, verify, 2, 0);
    if (rc)
        printf ("Query 11 failed\n");
*/
    /* query 18 - projection, 1% */

    rc = db->selectionQuery (18, timer[18],
        "select distinct two, four, ten, twenty, onepercent, string4 from big1",
        "select distinct two, four, ten, twenty, onepercent, string4 from big2",
        numBigTblTups, 400, 0, verify, 2, 0);

    if (rc)
        printf ("Query 18 failed\n");

    /* query 19 - projection, 100% */

    rc = db->selectionQuery (19, timer[19],
        "select distinct two, four, ten, twenty, onepercent, tenpercent, twentypercent, fiftypercent, unique3, "
            "evenonepercent, oddonepercent, stringu1, stringu2, string4 from big1",
        "select distinct two, four, ten, twenty, onepercent, tenpercent, twentypercent, fiftypercent, unique3, "
            "evenonepercent, oddonepercent, stringu1, stringu2, string4 from big2",
        numBigTblTups, numBigTblTups, 0, verify, 2, 0);

    if (rc)
        printf ("Query 19 failed");

    // query 20 - min. agg., no grouping 

    rc = db->selectionQuery (20, timer[20],
        "select min(unique2) from big1",
        "select min(unique2) from big2",
        numBigTblTups, 1, 0, verify, 2, 0);

    if (rc)
        printf ("Query 20 failed\n");

    // query 21 - min. agg., 100 groups 
/*
    rc = db->selectionQuery (21, timer[21],
        "select min(unique2) from big1 group by onepercent",
        "select min(unique2) from big2 group by onepercent",
        numBigTblTups, 100, 0, verify, 2, 0);

    if (rc)
        printf ("Query 21 failed\n");

    // query 22 - sum agg., 100 groups 

    rc = db->selectionQuery (22, timer[22],
        "select sum(unique2) from big1 group by onepercent",
        "select sum(unique2) from big2 group by onepercent",
        numBigTblTups, 100, 0, verify, 2, 0);

    if (rc)
        printf ("Query 22 failed\n");
*/
    if (modify) {
        // query 26 - insert one row, no index 

        rc = db->runInsert(26, timer[26], numBigTblTups, BIG1TBLNAME, BIG2TBLNAME);

        if (rc)
            printf ("Query 26, Insert failed\n");

        // query 27 - delete one row, no index 

        rc = db->runDelete(27, timer[27], numBigTblTups, BIG1TBLNAME, BIG2TBLNAME);
        if (rc)
            printf ("Query 27, Delete failed\n");

        // query 28 - update key attribute, no index 
        rc = db->runUpdate(28, timer[28], "unique2", numBigTblTups,
                          BIG1TBLNAME, BIG2TBLNAME);
        if (rc)
            printf ("Query 28, Update failed\n");

        // Now destroy and recreate database.

        if (populateDatabase (db, 1))
            printf ("repopulation of database failed.\n");
    }

    // Use statement handle allocated to create tables * as handle for creating indices
     

     //build indexes 

    if (verboseOut)
        printf ("Creating indices...\n");

    db->createIndex ("idx1", "small", "unique1");
    db->createIndex ("idx2", "small", "unique2");
    db->createIndex ("idx3", "big1", "unique1");
    db->createIndex ("idx4", "big1", "unique2");
    db->createIndex ("idx5", "big2", "unique1");
    db->createIndex ("idx6", "big2", "unique2");

    if (verboseOut)
        printf ("Index Creation Completed\n");

    /* indexed queries */

    if (verboseOut)
        printf ("Executing Indexed Queries...\n");

    /* query 3 - 1% selection on big table, index */

    rc = db->selectionQuery (3, timer[3],
                       "select * from big1 where unique2 between %d and %d",
                       "select * from big2 where unique2 between %d and %d",
                       numBigTblTups, numBigTblTups/100, 0, verify, 5, 2);
    if (rc)
        printf ("Query 3 failed\n");

    /* query 4 - 10% selection on big table, index */

    rc = db->selectionQuery (4, timer[4],
                       "select * from big1 where unique2 between %d and %d",
                       "select * from big2 where unique2 between %d and %d",
                       numBigTblTups, numBigTblTups/10, 0, verify, 5, 2);
    if (rc)
        printf ("Query 4 failed\n");

    /* query 5 - 1% selection on big table, index */

    rc = db->selectionQuery (5, timer[5],
                       "select * from big1 where unique1 between %d and %d",
                       "select * from big2 where unique1 between %d and %d",
                       numBigTblTups, numBigTblTups/100, 0, verify, 5, 2);
    if (rc)
        printf ("Query 5 failed\n");

    /* query 6 - 10% selection on big table, index */

    rc = db->selectionQuery (6, timer[6],
                       "select * from big1 where unique1 between %d and %d",
                       "select * from big2 where unique1 between %d and %d",
                       numBigTblTups, numBigTblTups/10, 0, verify, 5, 2);
    if (rc)
        printf ("Query 6 failed\n");

    /* query 7 - 1 row selection on big table, index */

    rc = db->selectionQuery (7, timer[7],
                       "select * from big1 where unique2 = %d",
                       "select * from big2 where unique2 = %d",
                       numBigTblTups, 1, 1, verify, 5, 1);
    if (rc)
        printf ("Query 7 failed\n");

    /* query 8 - 1% selection on big table, index */

    rc = db->selectionQuery (8, timer[8],
                       "select * from big1 where unique2 between %d and %d",
                       "select * from big2 where unique2 between %d and %d",
                       numBigTblTups, numBigTblTups/100, 0, verify, 5, 2);
    if (rc)
        printf ("Query 8 failed\n");

    /* query 12 - one join with filtered input, with index */

    sprintf(queryBuf1,
        "select * from big1, big2 where big1.unique2 = big2.unique2 and big2.unique2 < %d",
        numBigTblTups/10);

    sprintf(queryBuf2,
        "select * from big2, big1 where big2.unique2 = big1.unique2 and big1.unique2 < %d",
        numBigTblTups/10);

    rc = db->selectionQuery (12, timer[12], queryBuf1, queryBuf2, numBigTblTups,
                       numBigTblTups/10, 0, verify, 2, 0);
    if (rc)
        printf ("Query 12 failed\n");

    /* query 13 - one join, index */

    rc = db->selectionQuery (13, timer[13],
                       "select * from big1, bprime where big1.unique2 = bprime.unique2",
                       "select * from big2, bprime where big2.unique2 = bprime.unique2",
                       numBigTblTups, numBigTblTups/10, 0, verify, 2, 0);
    if (rc)
        printf ("Query 13 failed\n");

    // query 14 - two joins with filtered input, index 
/*
    sprintf(queryBuf1,
            "select * from small, big1, big2 where  big1.unique2 = big2.unique2 and "
            "small.unique2 = big1.unique2 and big1.unique2 < %d",
            numBigTblTups/10);

    sprintf(queryBuf2,
            "select * from small, big2, big1 where  big2.unique2 = big1.unique2 and "
            "small.unique2 = big2.unique2 and big2.unique2 < %d",
            numBigTblTups/10);

    rc = db->selectionQuery (14, timer[14], queryBuf1, queryBuf2, numBigTblTups,
                       numBigTblTups/10, 0, verify, 2, 0);
    if (rc)
        printf ("Query 14 failed\n");
*/

    // query 15 - one join with filtered input, no index 

    sprintf(queryBuf1,
       "select * from big1, big2 where big1.unique1 = big2.unique1 and big2.unique1 < %d",
       numBigTblTups/10);

    sprintf(queryBuf2,
       "select * from big2, big1 where big2.unique1 = big1.unique1 and big1.unique1 < %d",
       numBigTblTups/10);

    rc = db->selectionQuery (15, timer[15], queryBuf1, queryBuf2, numBigTblTups,
                       numBigTblTups/10, 0, verify, 2, 0);
    if (rc)
        printf ("Query 15 failed\n");

    /* query 16 - one join, index */

    rc = db->selectionQuery (16, timer[16],
                       "select * from big1, bprime where big1.unique1 = bprime.unique1",
                       "select * from big2, bprime where big2.unique1 = bprime.unique1",
                       numBigTblTups, numBigTblTups/10, 0, verify, 2, 0);
    if (rc)
        printf ("Query 16 failed\n");

    // query 17 - two joins with filtered input, index 
/*
    sprintf(queryBuf1,
            "select * from small, big1, big2 where big1.unique1 = big2.unique1 and "
            "small.unique1 = big1.unique1 and big1.unique1 < %d",
            numBigTblTups/10);

    sprintf(queryBuf2,
            "select * from small, big2, big1 where big2.unique1 = big1.unique1 and "
            "small.unique1 = big2.unique1 and big2.unique1 < %d",
            numBigTblTups/10);

    rc = db->selectionQuery (17, timer[17], queryBuf1, queryBuf2, numBigTblTups,
                       numBigTblTups/10, 0, verify, 2, 0);
    if (rc)
        printf ("Query 17 failed\n");
*/

    // query 23 - min. agg., no grouping 

    rc = db->selectionQuery (23, timer[23],
           "select min(unique2) from big1",
           "select min(unique2) from big2",
           numBigTblTups, 1, 0, verify, 2, 0);

    if (rc)
        printf ("Query 23 failed\n");
/*
    // query 24 - min. agg., 100 groups 
    rc = db->selectionQuery (24, timer[24],
        "select min(unique2) from big1 group by onepercent",
        "select min(unique2) from big2 group by onepercent",
        numBigTblTups, 100, 0, verify, 2, 0);
    if (rc)
        printf ("Query 24 failed\n");

    // query 25 - sum agg., 100 groups 

    rc = db->selectionQuery (25, timer[25],
                       "select avg(unique2) from big1",
                       "select avg(unique2) from big2",
                       numBigTblTups, 100, 0, verify, 2, 0);
    if (rc)
        printf ("Query 25 failed\n");
*/
    if (modify) {
        // query 29 - insert one row, index 
        rc = db->runInsert (29, timer[29], numBigTblTups,
                          BIG1TBLNAME, BIG2TBLNAME);
        if (rc)
            printf ("Query 29 failed\n");

        // query 30 - delete one row 

        rc = db->runDelete(30, timer[30], numBigTblTups,
                          BIG1TBLNAME, BIG2TBLNAME);
        if (rc)
            printf ("Query 30 failed\n");

        // query 31 - update key attribute 

        rc = db->runUpdate(31, timer[31], "unique2", numBigTblTups,
                          BIG1TBLNAME, BIG2TBLNAME);
        if (rc)
            printf ("Query 31 failed\n");

        // query 32 - update non-clustered key attribute 

        rc = db->runUpdate(32, timer[32], "unique1", numBigTblTups,
                          BIG1TBLNAME, BIG2TBLNAME);
        if (rc)
            printf ("Query 32 failed\n");

        for (i=0; i<NUMTABLES; i++) {
            db->dropTable (tableNames[i]);
        }
    }
    db->disconnect();



    printf("\nQuery Type          No Index       Index1       Index2   Query Numbers\n");
    printf("1%%    Sel       %12.6lf %12.6lf %12.6lf   1,3,5\n",
             timer[1]->avgTime(wiscWallTime),
             timer[3]->avgTime(wiscWallTime),
             timer[5]->avgTime(wiscWallTime));

    printf("10%%   Sel       %12.6lf %12.6lf %12.6lf   2,4,6\n",
             timer[2]->avgTime(wiscWallTime),
             timer[4]->avgTime(wiscWallTime),
             timer[6]->avgTime(wiscWallTime));

    printf("1 Tup Sel              -     %12.6lf         -      7\n",
             timer[7]->avgTime(wiscWallTime));

    printf("1%%    Sel              -     %12.6lf         -      8\n",
             timer[8]->avgTime(wiscWallTime));

    printf("JoinAselB       %12.6lf %12.6lf %12.6lf   9,12,15\n",
             timer[9]->avgTime(wiscWallTime),
             timer[12]->avgTime(wiscWallTime),
             timer[15]->avgTime(wiscWallTime));

    printf("JoinABprime     %12.6lf %12.6lf %12.6lf   10,13,16\n",
             timer[10]->avgTime(wiscWallTime),
             timer[13]->avgTime(wiscWallTime),
             timer[16]->avgTime(wiscWallTime));

    printf("JoinCselAselB   %12.6lf %12.6lf %12.6lf   11,14,17\n",
             timer[11]->avgTime(wiscWallTime),
             timer[14]->avgTime(wiscWallTime),
             timer[17]->avgTime(wiscWallTime));

    printf("MinAgg No Grps  %12.6lf %12.6lf         -      20,23\n",
             timer[20]->avgTime(wiscWallTime),
             timer[23]->avgTime(wiscWallTime));

    printf("MinAgg 100 Grps %12.6lf %12.6lf         -      21,24\n",
             timer[21]->avgTime(wiscWallTime),
             timer[24]->avgTime(wiscWallTime));

    printf("SumAgg 100 Grps %12.6lf %12.6lf         -      22,25\n",
             timer[22]->avgTime(wiscWallTime),
             timer[25]->avgTime(wiscWallTime));

    printf("Delete 1 Tup    %12.6lf        -     %12.6lf   27,30\n",
             timer[27]->avgTime(wiscWallTime),
             timer[30]->avgTime(wiscWallTime));

    printf("Update 1 Tup    %12.6lf %12.6lf %12.6lf   28,31,32\n",
             timer[28]->avgTime(wiscWallTime),
             timer[31]->avgTime(wiscWallTime),
             timer[32]->avgTime(wiscWallTime));

    printf("Insert 1 Tup    %12.6lf        -     %12.6lf   26,29\n",
             timer[26]->avgTime(wiscWallTime),
             timer[29]->avgTime(wiscWallTime));

    printf("1%%   Prj No Dup %12.6lf        -             -      18\n",
             timer[18]->avgTime(wiscWallTime));

    printf("100%% Prj No Dup %12.6lf        -             -      19\n",
             timer[19]->avgTime(wiscWallTime));

    printf("\nBenchmark Results by Query - (times are in millisecs):\n");

    printf ("\nQuery       Wall-clk       Resource           User         System\n");


    for (i=0; i<MAX_QUERIES; i++) {
        if (timer[i]->numIters() != 0) {
            printf ("%2d    %14f %14f %14f %14f\n", i,
                    timer[i]->avgTime (wiscWallTime),
                    timer[i]->avgTime (wiscResTime),
                    timer[i]->avgTime (wiscUserTime),
                    timer[i]->avgTime (wiscSysTime));
        }
        delete timer[i];
        timer[i] = 0;
    }

    printf ("\n");

    delete db;

    exit (0);
}
