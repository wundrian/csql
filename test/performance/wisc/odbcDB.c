#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

#include "sql.h"
#include "sqlext.h"

#include "support.h"
#include "odbcDB.h"

static SQLHENV henv;
static SQLHDBC hdbc;
static SQLHSTMT hstmt;

#define InsertTmplt \
     "insert into %s values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"

#define MAXHSTMT     100
#define MAXCOLS      100

extern int verboseOut;
extern int readOnly;

static int longerRun = 1;
#define RPTS 2

int odbcDB::connect (char *dsn)
{
    int rc;
    char errstr[256];

    rc = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&henv);
    if (rc)
        printf ("Unable to allocate an environment handle.\n");

    SQLSetEnvAttr(henv,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);
    rc = SQLAllocHandle(SQL_HANDLE_DBC,henv,&hdbc);
    if (rc)
        printf ("Unable to allocate connection handle.\n");



    SWORD xstat;
    unsigned char outbuf[256];

    rc = SQLConnect (hdbc,
                   (SQLCHAR *) "test", (SQLSMALLINT) strlen ("test"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));

   // connect to mysql
   /*SQLCHAR* outstr;
   SQLSMALLINT outstrlen;
   //SQLSMALLINT SQL_DRIVER_NOPROMPT;
   SQLSMALLINT slen = SQL_NTS;

   SQLDriverConnect(hdbc,NULL,(SQLCHAR*)"DSN=myodbc3;",SQL_NTS,outstr,sizeof(outstr),&outstrlen,SQL_DRIVER_NOPROMPT);*/

    if(!SQL_SUCCEEDED(rc)){
        printf("Unable to connect to driver\n");
        return rc;
    }

    rc = SQLSetConnectOption(hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
    if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
        printf ("Unable to set connection option autocommit %d.\n", rc);
    /* allocate statement handle for use with table creation and population */

    rc = SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    if (rc)
        printf ("Unable to allocate statement handle.\n");

    return (rc);
}


int
odbcDB::populateTable(char* tblName, int numTups, int valRange)
{

    char                buf[1024];
    int                 prime;
    int                 generator;
    int                 seed;
    int                 randInt;
    static SQLINTEGER   intVal1, intVal2, intVal3, intVal4, intVal5, intVal6,
    intVal7, intVal8, intVal9, intVal10, intVal11, intVal12,
    intVal13;
    static SQLINTEGER   cbintVal=4;
    static char         s4Val[64];
    static char         charVal1[64], charVal2[64];
    int                 i;

    SQLRETURN           rc = SQL_SUCCESS;
    static SQLINTEGER   cValLen=0,cValLen2=0,cValLen4=0;
    int fBind = 1;

    if (verboseOut)
        printf ("Populating table %s with %d rows...\n", tblName, numTups);

    /* create a prepared statement */
    sprintf(buf, InsertTmplt, tblName);

    rc = SQLPrepare(hstmt,(SQLCHAR*)buf, SQL_NTS );
    if (rc) {
        printf ("Unable to prepare statement.\n");
        return (rc);
    }

    /* set generator and prime values based upon value range */

    if ( valRange<=1000 ) {
        generator = 279;
        prime = 1009;
    }
    else if ( valRange<=10000 ) {
        generator = 2969;
        prime = 10007;
    }
    else if ( valRange<=100000 ) {
        generator = 21395;
        prime = 100003;
    }
    else if ( valRange<=1000000 ) {
        generator = 2107;
        prime = 1000003;
    }
    else if ( valRange<=10000000 ) {
        generator = 211;
        prime = 10000019;
    }
    else if ( valRange<=100000000 ) {
        generator = 21;
        prime = 100000007;
    }
    else {
        printf ("Too many rows in table.\n");
    }

    seed = generator;

    /* bind the input parameters */

    sprintf(charVal1, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    charVal1[51] = '\0';
    sprintf(charVal2, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    charVal2[51] = '\0';

    if (fBind)
    {
        if (verboseOut)
            printf ("Binding parameters for table load...\n");

        fBind = 0;
        rc = 0;

        rc += SQLBindParameter( hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal1,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal2,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal3,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal4,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal5,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal6,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 7, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal7,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 8, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal8,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 9, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal9,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 10, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal10,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 11, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal11,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 12, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 10, 0, &intVal12,4 , &cbintVal) ;
        rc += SQLBindParameter( hstmt, 13, SQL_PARAM_INPUT, SQL_C_SLONG,\
                               SQL_INTEGER, 38, 0, &intVal13,4 , &cbintVal) ;

        cValLen = SQL_NTS;
        rc += SQLBindParameter( hstmt, 14, SQL_PARAM_INPUT,  SQL_C_CHAR,\
                               SQL_CHAR, 52,0, charVal1, 52, &cValLen) ;
        cValLen2 = SQL_NTS;
        rc += SQLBindParameter( hstmt, 15, SQL_PARAM_INPUT,  SQL_C_CHAR,\
                               SQL_CHAR, 52,0, charVal2, 52, &cValLen2) ;
        cValLen4 = SQL_NTS;
        rc += SQLBindParameter( hstmt, 16, SQL_PARAM_INPUT,  SQL_C_CHAR,\
                               SQL_CHAR, 52,0, s4Val, 52, &cValLen4) ;

        if (rc)
            printf ("Bind Parameters failed.\n");

        if (verboseOut)
            printf ("Completed\n");

    } /* End BindColumns */

    /* insert the numTups rows */

    for (i=0; i<numTups; i++) {
        seed = randNum(seed, valRange, generator, prime);
        randInt = (int) seed - 1;

        /* unique1: range is 0 - valRange-1; order is random */
        intVal1 = randInt;
        /* unique2: range is 0 - valRange-1; order is sequential */
        intVal2 = i;
        /* two: range is 0 - 1; order is random */
        intVal3 = randInt % 2;
        /* four: range is 0 - 3; order is random */
        intVal4 = randInt % 4;
        /* ten: range is 0 - 9; order is random */
        intVal5 = randInt % 10;
        /* twenty: range is 0 - 19; order is random */
        intVal6 = randInt % 20;
        /* onepercent: range is 0 - 99; order is random */
        intVal7 = randInt % 100;
        /* tenpercent: range is 0 - 9; order is random */
        intVal8 = randInt % 10;
        /* twentypercent: range is 0 - 4; order is random */
        intVal9 = randInt % 5;
        /* fiftypercent: range is 0 - 1; order is random */
        intVal10 = randInt % 2;
        /* unique3: range is 0 - valRange-1; order is random */
        intVal11 = randInt;
        /* evenonepercent: range is 0 - 198; order is random */
        intVal12 = (randInt%100) * 2;
        /* oddonepercent: range is 0 - 199; order is random */
        intVal13 = (randInt%100) * 2 + 1;
        /* stringu1: order is random */
        convert(randInt, charVal1);
        cValLen = (int) strlen(charVal1);
        /* stringu2: order is sequential */
        convert(i, charVal2);
        cValLen2 = (int) strlen(charVal2);
        /* string4: order is cyclic */

        switch ( i%4 ) {
        case 0:
            strcpy(s4Val,"AAAAxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
            break;
        case 1:
            strcpy(s4Val,"HHHHxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
            break;
        case 2:
            strcpy(s4Val,"OOOOxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
            break;
        case 3:
            strcpy(s4Val,"VVVVxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
            break;
        }
        cValLen4 = (int) strlen(s4Val);

        /* ODBC Execute prepared statement */

        rc = SQLExecute(hstmt);

        if (rc)
        {
#if 0
            SQLCHAR sqlstate[6], msg[300];
            SQLINTEGER native;
            SQLSMALLINT i, len;
            i = 1;
            while ( SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, i, sqlstate, &native, msg, 290, &len) 
                    != SQL_NO_DATA )
            {
                printf("%s\n", msg);
                i++;
            }
#endif
            printf ("SQLExecute failed. (%d)\n", i);
	    exit(1);
        }

#if 0
    rc = SQLTransact(henv,hdbc,SQL_COMMIT);
    if (rc)
        printf ("Commit failed\n");
#endif
    } /* end for */

    /* commit the transaction */

    rc = SQLTransact(henv,hdbc,SQL_COMMIT);
    if (rc)
        printf ("Commit failed\n");

    /* close the statement (but do not drop) and return */

    rc = SQLFreeStmt(hstmt, SQL_DROP);
    if (rc)
        printf ("Unable to SQL_DROP statement handle.\n");

    rc = SQLAllocStmt(hdbc, &hstmt);
    if (rc)
        printf ("Unable to Alloc statement handle.\n");

    return(rc);
}

static int
fetchSelect(int queryNum, class wiscTimer *wT, SQLHENV henv, SQLHDBC hdbc, SQLHSTMT hstmtI, int verify,
            int resCard, int uniq)
{
    int           i;
    SQLCHAR       colname[32];
    SQLSMALLINT   coltype;
    SQLSMALLINT   bindtype;
    SQLINTEGER    bindsize;
    SQLSMALLINT   colnamelen;
    SQLSMALLINT   nullable;
    SQLUINTEGER   collen[MAXCOLS];
    SQLSMALLINT   scale;
    SQLINTEGER    outlen[MAXCOLS];
    SQLCHAR*      data[MAXCOLS];
    SQLSMALLINT   nresultcols = 0, dispcols = 0;
    SQLRETURN     rc = SQL_SUCCESS;
    int           print = 0;
    int           cnt = 0;
    //    SQLRETURN     rc1 = SQL_SUCCESS;

    for ( i = 0; i < MAXCOLS; i++ )
        data[i] = NULL;

    /* Instantiate the result set */

    rc = SQLNumResultCols(hstmtI, &nresultcols);
    if (rc)
        printf ("SQLNumresult columns failed.\n");

    /* bind each column */

    for (i = 0; i < nresultcols; i++) {

        rc = SQLDescribeCol(hstmtI,
                            (SQLSMALLINT)(i+1),
                            colname,
                            (SQLSMALLINT) sizeof(colname),
                            &colnamelen,
                            &coltype,
                            &collen[i],
                            &scale,
                            &nullable);

        if (rc)
            printf ("Unable to describe the column %d.\n", i+1);

        /* Select a binding type based on the column type */

        switch (coltype) {
        case SQL_VARCHAR:
        case SQL_CHAR:
            bindtype = SQL_C_CHAR;
            bindsize = collen[i] + 1;
            break;

        case SQL_INTEGER:
            bindtype = SQL_C_SLONG;
            bindsize = sizeof (int);
            break;

        case SQL_SMALLINT:
            bindtype = SQL_C_SHORT;
            bindsize = sizeof (short);
            break;

        case SQL_TINYINT:
            bindtype = SQL_C_TINYINT;
            bindsize = sizeof (char);
            break;

        case SQL_REAL:
            bindtype = SQL_C_FLOAT;
            bindsize = sizeof (float);
            break;

        case SQL_FLOAT:
            bindtype = SQL_C_DOUBLE;
            bindsize = sizeof (double);
            break;

#if 0
	    // The schema used for wisconsin benchmark queries does not 
	    // involve this datatype.
        case SQL_NUMERIC:
            bindtype = SQL_C_NUMERIC;
            bindsize = collen[i] + 1;
            break;
#endif

        default:
            printf ("Unknown col type %d\n", coltype);
            bindtype = SQL_C_CHAR;
            bindsize = 80;
            break;
        }

        data[i] = (unsigned char *) ::malloc(bindsize);

        rc = SQLBindCol( hstmtI,
                         (SQLUSMALLINT)(i+1),
                         bindtype,
                         (SQLPOINTER)(data[i]),
                         bindsize,
                         &outlen[i]);

        if (rc)
            printf ("Unable to bind the column %d.\n", i+1);

        //if (print) printf ("%*.*s ",collen[i], collen[i], colname);
    } /* end for each column */

    dispcols = nresultcols;

    /* commit the transaction */

    /* execute the query */
    wT->startTimer();

    rc = SQLExecute(hstmtI);

    if (rc != SQL_SUCCESS)
    {
        printf ("Execute failed. (query=%d hstmt=%p rc=%d)\n", 
                    queryNum, hstmtI, rc);
        return rc;
    }

    /* if specified, verify that the number of actual result
     * rows are the expected number of result rows
     */

    cnt = 0;
    for (;;) {
        rc = SQLFetch(hstmtI);

        if (rc)
            break;

        cnt++;

        if (print) {
            for (i = 0; i < dispcols; i++) {
                if (outlen[i] == SQL_NULL_DATA) {
                    strcpy((char *)data[i], "NULL");
                }
                printf ("%*.*s ", collen[i], collen[i], data[i]);
            }
            printf ("\n");
        }
    }

    //printf ("rc = %d\n", rc);

    rc = SQLTransact(henv, hdbc, SQL_COMMIT);
    if (rc)
        printf ("Unable to commit transaction");

    wT->stopTimer();
    rc = SQLCloseCursor(hstmtI);
    if (rc != SQL_SUCCESS)
    {
        printf ("Close Cursor failed. (query=%d hstmt=%p rc=%d)\n", 
                queryNum, hstmtI, rc);
        return rc;
    }

    if (verify) {
        if (uniq && cnt != 1) {
            printf ("Error: Query %d: uniq specified and cnt = %d\n", queryNum, cnt);
        }
        if ( cnt != resCard) {
            printf ("Error: Query %d: expected %d results, got %d\n", queryNum, resCard, cnt);
        }
    }

    /* free locally allocated memory */

    for ( i = 0 ; i < MAXCOLS; i++ ) {
        if ( data[i] )
            ::free(data[i]);
    }

    return(rc);
}

int
odbcDB::selectionQuery (int queryNum, class wiscTimer *wT, char *form1, char *form2, int tblCard,
                        int resCard, int uniq, int verify, int repeatCnt,
                        int numParams)
{
    int                   range = tblCard - resCard;
    int                   val;
    char                  buf[MAXHSTMT][192];
    int                   i,j,times;
    int                   totalNumQueries;
    SQLHSTMT              hstmtA[MAXHSTMT];
    SQLRETURN             rc = SQL_SUCCESS;

    /* do not perform the operation if the query is not specified by the
     * user */

    if (!isQuery(queryNum)) {
        return(SQL_SUCCESS);
    }
 
    bzero((char *)buf,sizeof(buf));

    /* print the query number */

    if (verboseOut)
        printf ("Query %d:\n", queryNum);

    /* limit the repeat count */

    if ( repeatCnt > 256 ) {
        rc = 1;
        printf ("selectionQuery: repeatCnt too high");
        return rc;
    }

    /* create array[repeatCnt*2] of statement handles */

    totalNumQueries = repeatCnt * 2;
    times = longerRun * RPTS;

    //printf ("Query %d - total %d times %d\n", queryNum, totalNumQueries, times);

    for (i = 0; i < totalNumQueries; i++) {
        rc = SQLAllocStmt(hdbc, &hstmtA[i]);
        if (rc)
            printf ("Unable to allocate statement handle.\n");
    }

    /*
     * Build and compile queries that select desired number of
     * rows (alternating between the two forms).  A total of
     * ten queries are constructed, with column ranges selected
     * at random.
     */

    for (i = 0; i < repeatCnt; i++) {

        val = (int) (drand48() * range);

        switch (numParams) {
        case 0:
            sprintf(buf[2*i], form1);
            break;
        case 1:
            sprintf(buf[2*i], form1, val);
            break;
        case 2:
            sprintf(buf[2*i], form1, val, val+resCard-1);
            break;
        default:
            printf ("selectionQuery: unexpected numParams value\n");
            return(-1);
        }

        /* ODBC prepared statement 2 different statements prepared, each
         * executed repeatCnt number of times with the parameters changed
         * for each iteration */

        rc= SQLPrepare(hstmtA[2*i],(SQLCHAR *) buf[2*i], SQL_NTS );
        if (rc)
        printf ("Unable to prepare statement.\n");
        printf("hstmtA[%d]=%p, buf[%d]=%s\n", 2*i, hstmtA[2*i], 2*i, buf[2*i]);

        val = (int) (drand48() * range);

        switch ( numParams ) {
        case 0:
            sprintf(buf[2*i+1], form2);
            break;
        case 1:
            sprintf(buf[2*i+1], form2, val);
            break;
        case 2:
            sprintf(buf[2*i+1], form2, val, val+resCard-1);
            break;
        default:
            printf ("selectionQuery: unexpected numParams value\n");
            return -1;
        }

        /* ODBC prepared statement #2 */

        rc = SQLPrepare(hstmtA[2*i+1],(SQLCHAR *) buf[2*i+1], SQL_NTS );
        if (rc) {
            printf ("Unable to prepare statement.\n");
            return -1;
        }
    }

    /* commit the transaction */

    /* execute and time queries. */

    /* ODBC version of fetchSelect call, handle freed in fetchSelect */

    for (i = 0; i < totalNumQueries; i++) {

        /* execute each query many a time */

        for (j = 0; j < times; j++) {

            rc = fetchSelect(queryNum, wT, henv, hdbc, hstmtA[i], verify, resCard, uniq);

            if (rc) {
                printf ("fetchSelect failed.\n");
                return(rc);
            }
        }
    }

    return(rc);
}

int
odbcDB::runUpdate(int queryNum, class wiscTimer *wT, char* col,
                 int numBigTblTups, char *Big1TblName, char *Big2TblName)
{
    char*     upd = "update %s set %s = %d where %s = %d";
    char      buf[512];
    int       val1 = numBigTblTups + 1;
    int       val2 = numBigTblTups/2;
    int       i;
    SQLHSTMT  hstmtA[MAXHSTMT];
    SQLRETURN rc = SQL_SUCCESS;

    if (!isQuery(queryNum))
        return 0;

    /* print the query number */

    if (verboseOut)
        printf ("Query %d:\n", queryNum);

    /* prepare the update statements */

    for (i = 0; i < ((10*RPTS)/4); i++, val1++, val2++) {
        rc = 0;

        /* allocate and prepare statement #1 */

        sprintf(buf, upd, Big1TblName, col, val1, col, val2);

        rc += SQLAllocStmt(hdbc, &hstmtA[i*4]);
        rc += SQLPrepare(hstmtA[i*4],(SQLCHAR *)buf, SQL_NTS );

        /* allocate and prepare statement #2 */

        sprintf(buf, upd, Big2TblName, col, val1, col, val2);

        rc += SQLAllocStmt(hdbc, &hstmtA[i*4+1]);
        rc += SQLPrepare(hstmtA[i*4+1],(SQLCHAR *)buf, SQL_NTS );

        /* allocate and prepare statement #3 */

        sprintf(buf, upd, Big1TblName, col, val2, col, val1);

        rc += SQLAllocStmt(hdbc, &hstmtA[i*4+2]);
        rc += SQLPrepare(hstmtA[i*4+2],(SQLCHAR *)buf, SQL_NTS );

        /* allocate and prepare statement #4 */

        sprintf(buf, upd, Big2TblName, col, val2, col, val1);

        rc += SQLAllocStmt(hdbc, &hstmtA[i*4+3]);
        rc += SQLPrepare(hstmtA[i*4+3],(SQLCHAR *)buf, SQL_NTS );

        if (rc)
            printf ("Prepare failed\n");
    }

    /* commit the transaction */

    rc = SQLTransact(henv, hdbc, SQL_COMMIT);
    if (rc)
        printf ("Unable to commit transaction");

    /* Execute and time updates. */

    for (i = 0; i < 10*RPTS; i++) {

        wT->startTimer();

        rc = SQLExecute(hstmtA[i]);
        if (rc)
            printf ("Execute failed (handle[%d]=%p)\n", i, hstmtA[i]);

        rc = SQLTransact(henv,hdbc,SQL_COMMIT);

        wT->stopTimer();

        if (rc)
            printf ("commit failed\n");
    }


    /* Delete compiled commands. */

    for (i=0; i<10*RPTS; i++) {
        rc = SQLFreeStmt(hstmtA[i], SQL_DROP);
        if (rc)
            printf ("Free Stmt failed\n");
    }

    /* commit the transaction and return */

    rc = SQLTransact(henv,hdbc,SQL_COMMIT);
    if (rc)
        printf ("Unable to commit transaction.\n");

    return(rc);
}

int
odbcDB::runDelete(int queryNum, class wiscTimer *wT, int numBigTblTups,
                 char *Big1TblName, char *Big2TblName)
{
    char*                 ins = "delete from %s where unique1=%d";
    char                  buf[512];
    int                   val = numBigTblTups + 1;
    int                   i;
    int                   recordQuery = 1;
    SQLHSTMT              hstmtA[MAXHSTMT];
    SQLRETURN             rc = SQL_SUCCESS;

    /* perform this operation whether specified by user or not, in case
     * it affects subsequent queries; however, do not record it if not
     * specified by user */

    if (!isQuery(queryNum))
        return 0;

    /* print the query number */

    if (verboseOut)
        printf ("Query %d:\n", queryNum);

    /* prepare delete statements */

    for (i = 0; i < 5*RPTS; i++, val++) {

        rc = 0;

        sprintf(buf, ins, Big1TblName, val);

        rc += SQLAllocStmt(hdbc, &hstmtA[i*2]);

        rc += SQLPrepare(hstmtA[i*2],(SQLCHAR *)buf, SQL_NTS );

        sprintf(buf, ins, Big2TblName, val);

        rc += SQLAllocStmt(hdbc, &hstmtA[i*2+1]);

        rc += SQLPrepare(hstmtA[i*2+1],(SQLCHAR *)buf, SQL_NTS );

        if (rc)
            printf ("Allocation and Prepare failed\n");

    } /* end for */

    /* commit the transaction */

    rc = SQLTransact(henv, hdbc, SQL_COMMIT);

    if (rc)
        printf ("Commit failed\n");

    /* execute and time deletes. */

    for (i = 0; i < 10*RPTS; i++) {

        val += i % 2; // incr every other value.
        wT->startTimer();

        rc = SQLExecute(hstmtA[i]);
        if (rc)
            printf ("Execute failed\n");

        /* commit the transaction */

        rc = SQLTransact(henv, hdbc, SQL_COMMIT);

        wT->stopTimer();

        if (rc)
            printf ("Unable to commit transaction\n");

    } /* end for */

    for (i = 0; i < 10*RPTS; i++) {

        rc = SQLFreeStmt(hstmtA[i], SQL_DROP);

        if (rc)
            printf ("Free Stmt failed.\n");
    }


    /* commit the transaction and return */

    rc = SQLTransact(henv, hdbc, SQL_COMMIT);
    if (rc)
        printf ("Unable to commit transaction");

    return(rc);

}

int
odbcDB::runInsert(int queryNum, class wiscTimer *wT, int numBigTblTups,
                 char *Big1TblName, char *Big2TblName)
{
    char*     ins = "insert into %s values (%d, %d, 0, 2, 0, 10, 50,\
688, 1950, 4950, 9950, 1, 100,\
'MxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxC',\
'GxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxA',\
'OxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxO')";
    char                  buf[512];
    int                   val = numBigTblTups + 1;
    int                   i;
    int                   recordQuery = 1;
    SQLHSTMT              hstmtA[MAXHSTMT];
    SQLRETURN             rc = SQL_SUCCESS;

    /* perform this operation whether specified by user or not, in case
     * it affects subsequent queries; however, do not record it if not
     * specified by user */

    if (!isQuery(queryNum))
        return 0;

    /* print the query number */

    if (verboseOut)
        printf ("Query %d:\n", queryNum);

    /* Alloc statement handles, compile insert statements and bind
     * parameters */

    for (i = 0; i < 5*RPTS; i++, val++) {
        rc = 0;

        sprintf(buf, ins, Big1TblName, val, val);

        rc += SQLAllocStmt(hdbc, &hstmtA[i*2]);

        rc += SQLPrepare(hstmtA[i*2],(SQLCHAR *)buf, SQL_NTS );

        sprintf(buf, ins, Big2TblName, val, val);

        rc += SQLAllocStmt(hdbc, &hstmtA[i*2+1]);

        rc += SQLPrepare(hstmtA[i*2+1],(SQLCHAR *)buf, SQL_NTS );

        if (rc)
            printf ("Alloc and prepare failed\n");

    } /* end for */

    /* commit the transaction */

    rc = SQLTransact(henv, hdbc, SQL_COMMIT);
    if (rc)
        printf ("Commit failed\n");

    /* execute the insert statement 10*RPT times */

    for (i = 0; i < 10*RPTS; i++) {

        wT->startTimer();

        rc = SQLExecute(hstmtA[i]);
        if (rc)
            printf ("Execute now\n");

        rc = SQLTransact(henv,hdbc,SQL_COMMIT);

        wT->stopTimer();

        if (rc)
            printf ("Commit failed\n");

    }

    for (i=0; i<10*RPTS; i++) {

        rc = SQLFreeStmt(hstmtA[i], SQL_DROP);
        if (rc)
            printf ("Free Stmt failed\n");
    }

    rc = SQLTransact(henv, hdbc, SQL_COMMIT);
    if (rc)
        printf ("Unable to commit transaction\n");

    return(rc);

}


int odbcDB::disconnect()
{
    int rc;

    if (verboseOut)
        printf ("Disconnecting from the data source...\n");

    rc = SQLTransact(henv,hdbc,SQL_COMMIT);
    if (rc)
        printf ("Unable to commit transaction\n");

    rc = SQLDisconnect(hdbc);
    if (rc)
        printf ("Unable to disconnect\n");

    rc = SQLFreeConnect(hdbc);
    if (rc)
        printf ("Unable to free connection handle");

    rc = SQLFreeEnv(henv);
    if (rc)
        printf ("Unable to free environment handle");

    return rc;
}

static int immedExecute (char* cmd)
{
    SQLRETURN rc;
    SQLHSTMT lhstmt;
    rc = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    if (rc != SQL_SUCCESS)
        printf ("immedExecute: SQLAllocHandle failed with retCode=%d %s:%d\n", rc, __FILE__, __LINE__);

    /* Execute the command */
    rc = SQLPrepare(hstmt, (SQLCHAR *) cmd, SQL_NTS);
    if (rc)
        printf ("Prepare of (%s) failed\n", cmd);
    rc = SQLExecute(hstmt);
    if (rc)
        printf ("Execute of (%s) failed\n", cmd);

    /* Commit the transaction */

    //rc = SQLTransact(henv, hdbc, SQL_COMMIT);
    if (rc)
        printf ("Unable to commit transaction");

    /* Close associated cusssor and drop pending results */
    printf("SQL Statement executed %s\n", (char*)cmd);
    //rc = SQLFreeStmt(hstmt, SQL_CLOSE);
    if (rc)
        printf ("Unable to SQL_CLOSE statement handle.\n");

    return rc;
}

int
odbcDB::emptyTable (char *tblName)
{
    char buf[128];

    sprintf (buf, "delete from %s", tblName);

    return immedExecute (buf);
}

int
odbcDB::createTable (char *tblName)
{
    char buf[1024];

    sprintf (buf, "create table %s "
        "(unique1 integer not null, unique2 integer not null, "
        "two integer not null, four integer not null, "
        "ten integer not null, twenty integer not null, "
        "onepercent integer not null, tenpercent integer not null, "
        "twentypercent integer not null, fiftypercent integer not null, "
        "unique3 integer not null, evenonepercent integer not null, "
        "oddonepercent integer not null, stringu1 char(52) not null, "
        "stringu2 char(52) not null, string4 char(52) not null)",
        tblName);

    return immedExecute (buf);
}

int
odbcDB::dropTable (char *tblName)
{
    char buf[128];

    sprintf (buf, "drop table %s", tblName);

    return immedExecute (buf);
}

int
odbcDB::createIndex (char *idx, char *tblName, char *fld)
{
    char buf[128];

    sprintf (buf, "create index %s on %s (%s)",
             idx, tblName, fld);

    return immedExecute (buf);
}

int
odbcDB::dropIndex (char *idx, char *tblName)
{
    char buf[128];

    sprintf (buf, "drop index %s", idx);

    return immedExecute (buf);
}
