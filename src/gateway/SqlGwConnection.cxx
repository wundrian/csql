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
#include <SqlGwConnection.h>
#include<SqlOdbcConnection.h>
#include <CSql.h>
#include <Network.h>

List SqlGwConnection::cacheList;

SqlGwConnection::~SqlGwConnection()
{
    struct MultiDSN *node=NULL, *prev=NULL;
    node = multi_adapter_head;
    while(node!=NULL){
        if(node->isConnected) node->adapter->disconnect();
        delete node->adapter;
        prev=node;
        node=node->next;
        delete prev;
   }
 /*   if (isAdapterConnected) { 
        adapter->disconnect();
        isAdapterConnected = false;
    } */
    ListIterator it = cacheList.getIterator();
    while(it.hasElement()) delete (CachedTable *) it.nextElement();
    cacheList.reset();
   // if (adapter) { delete adapter; adapter = NULL; }
}

//createAdapters
DbRetVal SqlGwConnection::createAdapters(SqlGwConnection *gwconn)
{
    DbRetVal rv=OK;
    FILE *fp = NULL;
    fp = fopen(Conf::config.getDsConfigFile(),"r");
    if(fp==NULL){
        printError(ErrSysInit,"csqlds.conf file does not exist");
        return ErrNotOpen;
    }

    char dsnname[IDENTIFIER_LENGTH];dsnname[0]='\0';
    char tdb[IDENTIFIER_LENGTH];
    char username[IDENTIFIER_LENGTH];
    char password[IDENTIFIER_LENGTH];

    while(!feof(fp)){
        AbsSqlConnection *adapterCon = new SqlOdbcConnection();
        fscanf(fp,"%s %s %s %s\n",dsnname,username,password,tdb);
        if(strcmp(dsnname,"") == 0){
            printError(ErrSysInternal, "Add entry to csqlds.conf file");
            fclose(fp);
            return ErrNotReady;
        }
        gwconn->setAdapter(adapterCon,dsnname);
    }
    fclose(fp);
    return rv;
}

//Putting different "Adapter" object into List
void SqlGwConnection::setAdapter(AbsSqlConnection *conn, char *dsName)
{
    struct MultiDSN *new_node=new struct MultiDSN;
    struct MultiDSN *link_node=NULL;
    strcpy(new_node->dsn,dsName);
    new_node->adapter=conn;
    new_node->next=NULL;
    new_node->toCommit=false;
    new_node->isConnected=false;
    noOfCon++;
    if(multi_adapter_head == NULL){ multi_adapter_head=new_node; return;}
    link_node=multi_adapter_head;
    while(link_node != NULL) {
        if(link_node->next == NULL) {
            link_node->next = new_node;
            return;
        }
        link_node = link_node->next;
    }
}

//getAdapter
AbsSqlConnection* SqlGwConnection::getAdapterConnection(char *dsName)
{
   struct MultiDSN *node;
   node=multi_adapter_head;
   while(node!=NULL){
       if(strcmp(node->dsn,dsName)==0)
       return node->adapter;
        node=node->next;
   }
   return NULL;
}

DbRetVal SqlGwConnection::connect (char *user, char * pass)
{
   // SqlOdbcConnection *dsnAda=(SqlOdbcConnection*) adapter;
    struct MultiDSN *node=multi_adapter_head;
    isCSqlConnected = false;
    isAdapterConnected = false;
    strcpy(username, user);
    strcpy(password, pass);
    DbRetVal rv = OK;
    if (innerConn) rv = innerConn->connect(user,pass);
    if (rv == OK) isCSqlConnected = true;
    if (rv == ErrNoPrivilege ) return rv;
    // Get the appropriate "Adapter" object based on DSN from the MultiDsn List
    while(node !=NULL ){
       adapter=getAdapterConnection(node->dsn);
       SqlOdbcConnection *dsnAda=(SqlOdbcConnection*) adapter;
       dsnAda->setDsn(node->dsn);
       //Below function will connect to TDB
       if(adapter) rv = adapter->connect(user,pass);
       if(OK == rv) node->isConnected = true;
       node=node->next;
    }
    //if (adapter) rv = adapter->connect(user,pass);
    if (0 == cacheList.size()) rv = populateCachedTableList();
    if (rv == OK) isAdapterConnected = true;
    if (!isAdapterConnected && !isCSqlConnected) return ErrNoConnection;
    return OK;
}

DbRetVal SqlGwConnection::disconnect()
{
    DbRetVal rv = OK;
    if (innerConn && isCSqlConnected) rv =innerConn->disconnect();
    if (rv != OK) return rv;
    struct MultiDSN *node=NULL ;
    node = multi_adapter_head;
    if (isAdapterConnected){
        while(node!=NULL){
            if(node->isConnected) node->adapter->disconnect();
            node=node->next;
        }
    }
   // if (adapter && isAdapterConnected) rv = adapter->disconnect();
    isCSqlConnected = false;
    isAdapterConnected = false;
    return rv;
}
DbRetVal SqlGwConnection::beginTrans(IsolationLevel isoLevel, TransSyncMode smode)
{
    DbRetVal rv = OK;
    if (!isAdapterConnected && !isCSqlConnected) return ErrNoConnection;
    if (innerConn && isCSqlConnected) rv =  innerConn->beginTrans(isoLevel, smode);
    if (rv != OK) return rv;
    struct MultiDSN *node=NULL;
    node = multi_adapter_head;
    if (isAdapterConnected) 
    {
         while(node!=NULL){
            if(node->isConnected) node->adapter->beginTrans(isoLevel);
            node=node->next;
        }
    }
    //mode = smode;
    txnHdlr = CSqlHandler;
    return rv;
}
DbRetVal SqlGwConnection::commit()
{
    struct MultiDSN *node = multi_adapter_head;
    DbRetVal rv = OK;
    
    if (innerConn && isCSqlConnected)
        //(txnHdlr == CSqlHandler || txnHdlr == CSqlAndAdapterHandler))
        rv = innerConn->commit();
    if (rv != OK) return rv;
    //Commit happen in every TDB, those are present in "csqlds.conf" file.
    while(node != NULL){
       // if (adapter &&  (txnHdlr == AdapterHandler || txnHdlr == CSqlAndAdapterHandler))
       if (txnHdlr == AdapterHandler || txnHdlr == CSqlAndAdapterHandler){ 
           if(node->toCommit){
               rv = (node->adapter)->commit();
               node->toCommit=false; 
           }
           
       }
       node=node->next;
    }
    if (!isAdapterConnected && !isCSqlConnected) return ErrNoConnection;
    return rv;
}
DbRetVal SqlGwConnection::rollback()
{
    DbRetVal rv = OK;
    if (innerConn && isCSqlConnected) //(txnHdlr == CSqlHandler || txnHdlr == CSqlAndAdapterHandler))
        rv =  innerConn->rollback();
    if (rv != OK) return rv;
    struct MultiDSN *node=NULL;
    node = multi_adapter_head;
    if (isAdapterConnected && (txnHdlr == AdapterHandler || txnHdlr == CSqlAndAdapterHandler))
    {
         while(node!=NULL){
            if(node->isConnected) node->adapter->rollback();
            node=node->next;
        }
    }
/*
    if (adapter && isAdapterConnected &&
        (txnHdlr == AdapterHandler || txnHdlr == CSqlAndAdapterHandler))
        rv = adapter->rollback();
*/
    if (!isAdapterConnected && !isCSqlConnected) return ErrNoConnection;
    return rv;
}
DbRetVal SqlGwConnection::connectCSqlIfNotConnected()
{
    if (!isCSqlConnected) { 
        DbRetVal rv = innerConn->connect(username, password);
        if (rv != OK) return rv;
        isCSqlConnected = true;
    }
    return OK;
}
DbRetVal SqlGwConnection::connectAdapterIfNotConnected()
{
    if (!isAdapterConnected) { 
        DbRetVal rv = adapter->connect(username, password);
        if (rv != OK) return rv;
        isAdapterConnected = true;
    }
    return OK;
}

bool SqlGwConnection::isTableCached(char *tblName)
{
    if (NULL == tblName)
    {
        printError(ErrBadArg, "tblName passed is NULL\n");
        return ErrBadArg;
    }
    ListIterator iter = cacheList.getIterator();
    CachedTable *node;
    while (iter.hasElement()) {
        node = (CachedTable*)iter.nextElement();
        if (strcmp(node->tableName, tblName) == 0)
        {
           return true;
        }
    }
    return false;
}
DbRetVal SqlGwConnection::populateCachedTableList()
{
    FILE *fp = NULL;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "cache.table file does not exist");
        return ErrSysInit;
    }
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];

    int cmode;
    CachedTable *node;
    while(!feof(fp))
    {
        fscanf(fp, "%d %s %s %s %s %s \n", &cmode, tablename,fieldname,condition,field,dsnName);
        node = new CachedTable();
        strcpy(node->tableName, tablename);
        cacheList.append(node);
    }
    fclose(fp);
    return OK;
}

