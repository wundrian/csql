// This case inserts records in csql every 200 ms based on the random numbers it finds.

#include <SqlFactory.h>
#include <time.h>
#define TS 1000 
//TS -> micro secs to sleep between transaction

int main(int argc, char **argv)
{
    DbRetVal rv = OK;
    if (argv[1] == NULL) {
        fprintf(stderr, "Usage: csqlInsert <o/p file>\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "a");
    struct timeval timeout;
    struct timeval timeStamp;
    char msgBuf[25];
    AbsSqlConnection *con = SqlFactory::createConnection(CSql);
    AbsSqlConnection *adCon = SqlFactory::createConnection(CSqlAdapter); 
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;
    rv = adCon->connect("root", "manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSql);
    AbsSqlStatement *adStmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(con);
    adStmt->setConnection(adCon);
    char statement[200];
    int rows = 0;
    // insert into table
    strcpy(statement,"INSERT INTO soakTable VALUES(1234,?,654323,'LAKSHYA_CSQL');");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    rv = adStmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    int rnd = 0;
    int i = 0;
    while (1) {
        if (rv == OK) {
           timeout.tv_sec = 0;
           timeout.tv_usec = TS;
           os::select(0, 0, 0, 0, &timeout);
           srand(time(0));
        }
        /*if (i == 0) rnd = rand() % 16645635;
        else if (i == 1) rnd = (rand() / 3) % 16645635;
        else if (i == 2) rnd = (rand() / 7) % 16645635;
        else if (i == 3) rnd = (rand() / 11) % 16645635;
        else if (i == 4) { i = 0; rnd = (rand() / 13) % 16645635; }
        */
        i++;
        rv = con->beginTrans();
        if (rv != OK) continue;
        //stmt->setIntParam(1, rnd);
        stmt->setIntParam(1, i);
        rv = stmt->execute(rows);
        if (rv == ErrUnique) {
            printf("Unique Key Violation Error\n"); 
            con->rollback(); continue;
        } else if (rv != OK) { 
            printError(rv, "Insert failed with ret val %d", rv);
            con->rollback(); continue;
        }
        else con->commit();
        rv = adCon->beginTrans();
        //adStmt->setIntParam(1,rnd);
        adStmt->setIntParam(1,i);
        rv = adStmt->execute(rows);
        if (rv != OK) {
            printError(rv, "Adapter:execute failed with rv = %d");
            adCon->rollback();
            continue;
        }
        else adCon->commit();
        if (i% 10000 == 0) {
            os::gettimeofday(&timeStamp);
            struct tm *tempTm = os::localtime(&timeStamp.tv_sec);
            strftime(msgBuf, 25, "%d/%m/%Y %H:%M:%S", tempTm);
            fprintf(fp, "Inserted PK: %8d %s\n", rnd, msgBuf);
            fflush(fp);
        }
    }
    fclose(fp);
    adStmt->free(); stmt->free(); 
    adCon->disconnect(); con->disconnect();
    delete adStmt; delete adCon;
    delete stmt; delete con;
}
