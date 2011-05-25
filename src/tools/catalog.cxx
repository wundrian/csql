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
#include <os.h>
#include <CSql.h>
#include <DatabaseManagerImpl.h>
#include <Database.h>
#include <TableImpl.h>
#include <CacheTableLoader.h>
#include <TableConfig.h>
#include <SqlFactory.h>
#include <SqlConnection.h>
#include <SqlStatement.h>

void printUsage()
{
   printf("Usage: catalog [-u username] [-p passwd] [-l] [-i] [-d] [-T table] [-I index] [-D <lock|trans|proc|chunk>]\n");
   printf("       l -> list all table with field information\n");
   printf("            list all Index information\n");
   printf("       i -> reinitialize catalog tables. Drops all tables.\n");
   printf("       d -> print db usage statistics\n");
   printf("       T -> list table information\n");
   printf("       I -> list index information\n");
   printf("       D -> print debug information for system tables\n");
   printf("Note: If multiple options are specified, last one will be considered.\n");
   return;
  
}

SqlConnection *sqlconn;
SqlStatement *stmt;

int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    int c = 0, opt = 0;
    char name[IDENTIFIER_LENGTH];
    while ((c = getopt(argc, argv, "u:p:T:I:D:vlicdsS?")) != EOF) 
    {
        switch (c)
        {
            case 'u' : { strcpy(username, argv[optind - 1]); opt=1; break; }
            case 'p' : { strcpy(password, argv[optind - 1]); opt=1; break; }
            case 'T' : { strcpy(name, argv[optind - 1]); opt = 5; break; }
            case 'I' : { strcpy(name, argv[optind - 1]); opt = 6; break; }
            case 'D' : { strcpy(name, argv[optind - 1]); opt = 7; break; }
            case 'l' : { opt = 2; break; } //list all the table with field info
            case 'i' : { opt = 3; break;  }//reinitialize the catalog table
            case 'd' : { opt = 4; break;  }//print db usage statistics
            case 's' : { if(opt == 6) opt=11;
                         else printf("Use -I IndexName -s\n"); 
                         break;  }//print db usage statistics
            case 'S' : { if(opt == 6) opt=12;
                         else printf("Use -I IndexName -S\n"); 
                         break;  }//print db usage statistics
            case '?' : { opt = 10; break; } //print help 
            case 'v' : {
                           if (opt == 5) opt = 15;
                           else if (opt == 6) opt=16;
                           break;
                       }
            default: opt=1; //list all the tables

        }
    }//while options
    if (opt == 10) {
        printUsage();
        return 0;
    }

    //printf("%s %s \n", username, password);
    if (username[0] == '\0' )
    {
        strcpy(username, I_USER);
        strcpy(password, I_PASS);
        opt=1;//if username is not specified, just list all table names
    }
    sqlconn = (SqlConnection*) SqlFactory::createConnection(CSqlDirect);
    DbRetVal rv = sqlconn->connect(username, password);
    if (rv != OK)  {
        printf("Unable to get connection to csql\n");
        delete sqlconn; delete stmt; return 1;
    }
    stmt = (SqlStatement*) SqlFactory::createStatement(CSqlDirect);
    stmt->setSqlConnection(sqlconn);    
    os::signal(SIGCSQL1, SIG_IGN);
    DatabaseManagerImpl *dbMgr = (DatabaseManagerImpl*) 
                                 sqlconn->getConnObject().getDatabaseManager();
    if (dbMgr == NULL) {
        printf("Unable to retrive db manager\n");
        sqlconn->disconnect(); delete stmt; delete sqlconn; return 2;
    }
    List tableList = dbMgr->getAllTableNames();
    ListIterator iter = tableList.getIterator();
    Identifier *elem = NULL;
    int ret =0;
    if (opt == 1) {
        printf("<TableNames>\n");
        int count =0;
        while (iter.hasElement())
        {
            elem = (Identifier*) iter.nextElement();
            count++;
            printf("  <TableName> %s </TableName>\n", elem->name);
        }
        if (count ==0) printf("  <No tables exist></No tables exist>\n");
        printf("</TableNames>\n");
    }
    else if (opt ==2) 
    {
        printf("<Table Information of all tables>\n");
        int count =0;
        while (iter.hasElement())
        {
            elem = (Identifier*) iter.nextElement();
            printf("  <TableInfo> \n");
            printf("    <TableName> %s </TableName>\n", elem->name);
            Table *table = dbMgr->openTable(elem->name);
            if (NULL == table) {
                printError(ErrSysInternal, "Unable to open table %s", elem->name);
                break;
            }
	        FieldInfo *info = new FieldInfo();
            List fNameList = table->getFieldNameList();
            ListIterator fNameIter = fNameList.getIterator();
            count++;
            char fieldName[IDENTIFIER_LENGTH];
            while (fNameIter.hasElement()) {
                 elem = (Identifier*) fNameIter.nextElement();
                 Table::getFieldNameAlone(elem->name, fieldName);
                 table->getFieldInfo((const char*)elem->name, info);
                 printf("      <FieldInfo>\n");
                 printf("        <FieldName> %s </FieldName>\n", fieldName);
                 printf("        <Type> %d </Type>\n", info->type);
                 printf("        <Length> %d </Length>\n", info->length);
                 printf("        <Primary> %d </Primary>\n", info->isPrimary);
                 printf("        <Null> %d </Null>\n", info->isNull);
                 printf("        <Default> %d </Default>\n", info->isDefault);
                 printf("        <DefaultValue> %s </DefaultValue>\n", info->defaultValueBuf);
                 printf("      </FieldInfo>\n");

            }
            delete info;
            dbMgr->closeTable(table);
            printf("  </TableInfo> \n");

        }
        if (count == 0) printf("  <No tables exist></No tables exist>\n");
        printf("</Table Information of all tables>\n");
        printf("<Index Information of all Indexs>\n");
        CatalogTableINDEXFIELD cIndexField(dbMgr->sysDb()); 
	    cIndexField.printAllIndex();
	    printf("</Index Information of all Indexs>\n");
    } else if (opt == 3) {
        if (!dbMgr->isAnyOneRegistered()) {
            printf("<DropTable>\n");
            int count =0; 
            while (iter.hasElement())
            {
                elem = (Identifier*) iter.nextElement();
#ifndef MMDB
                rv=TableConf::config.isTableCached(elem->name);
                if(rv!=OK){
                    printf("  <TableName> %s </TableName>\n", elem->name);
                    dbMgr->dropTable(elem->name);
                }
#else
                printf("  <TableName> %s </TableName>\n", elem->name);
                dbMgr->dropTable(elem->name);
#endif
                count++;
            }
            //TODO::If durability is on, remove chkpt and redo log file
            if (count ==0) printf("  <No tables exist></No tables exist>\n");
            printf("</DropTable>\n");

        } else {
            printf("Catalog not initialized. Found registered process\n");
            ret =1;
        }
    }else if (opt == 4)
    {
        printf("<Database Usage Statistics>\n");
        Database *db = dbMgr->sysDb();
        db->printStatistics();
        dbMgr->printUsageStatistics();
        db = dbMgr->db();
        db->printStatistics();
        printf("</Database Usage Statistics>\n");

    }else if (opt == 5)
    {
        printf("<Table Info> \n");

        TableImpl *table = (TableImpl*) dbMgr->openTable(name);
        if (table != NULL) {
            table->printInfo();
            dbMgr->closeTable(table);
        }else {
           printf("  <Table Not Found> %s </Table Not Found>\n", name);
           ret =1;
        }
        printf("</Table Info> \n");

    }else if (opt == 6)
    {
        printf("<Index Info> \n");
        rv = dbMgr->printIndexInfo(name);
        if (rv != OK)
        {
           printf("  <Index Not Found> %s </Index Not Found>\n", name);
           ret =1;
        }
        printf("<Index Info> \n");
    }else if (opt == 7)
    {
        if (strcmp(name, "lock")  == 0) 
        {
            dbMgr->printDebugLockInfo();
        }
        else if (strcmp(name, "trans")  == 0)
        {
            dbMgr->printDebugTransInfo();
        }
        else if (strcmp(name, "proc")  == 0)
        {
            dbMgr->printDebugProcInfo();
        }
        else if(strcmp(name,"chunk") ==0)
    	{
            dbMgr->printDebugChunkInfo();
	}
        else if(strcmp(name,"mutex") ==0)
    	{
            dbMgr->printDebugMutexInfo();
        }else {
           printUsage();
           ret =1;
        }
    } else if (opt == 11){
        dbMgr->printTreeIndexNodeInfo(name, true);
    } else if (opt == 12){
        dbMgr->printTreeIndexNodeInfo(name,false);
    } else if (opt ==15) {
    } else if (opt ==16) {
        rv = dbMgr->printIndexDebugInfo(name);
        if (rv != OK)
        {
           printf("  <Index Not Found> %s </Index Not Found>\n", name);
           ret =1;
        }
    }
    iter.reset();
    while (iter.hasElement()) delete iter.nextElement();
    tableList.reset();
    sqlconn->disconnect();
    delete stmt; delete sqlconn;
    return ret;
}
