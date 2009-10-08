package csql.jdbc;

import java.util.*;
import java.sql.*;
import javax.sql.*;
import javax.naming.*;
import java.io.*;
import java.lang.*;
import java.lang.Class;

public class JdbcSqlPooledConnection implements javax.sql.PooledConnection
{

   //To store the connection Event Listions Hash manner for faster access
    private Map connectionEventListeners;


   // logical connection for connenction pool
    private Connection logicalConn;


   // Actual or physical connection 
    private JdbcSqlConnection physicalConn;


  //says logical connection open or close
   boolean isclose = true;

   //Constructor
    public JdbcSqlPooledConnection(Connection connection) {
                logicalConn = null;
                physicalConn =(JdbcSqlConnection) connection;
                connectionEventListeners = new HashMap();
        }




   //Pooled connection methods. Here connection event listener is insert into hashed map.
    public synchronized void addConnectionEventListener(ConnectionEventListener conEventListener)
    {
        if(connectionEventListeners != null)
            connectionEventListeners.put(conEventListener,conEventListener);
    }



   //Pooled connection method. Here the connection event listioner is removed from hash map
   public synchronized void removeConnectionEventListener(ConnectionEventListener conEventListener)
   {
       if(connectionEventListeners != null)
            connectionEventListeners.remove(conEventListener);
   }




   //Pooled connection method.
   public synchronized Connection getConnection() throws SQLException 
   {
           if (physicalConn == null) {
               System.out.println("Connection not Exit");
               isclose = true;  
           }

          /* if(isclose != true ||  logicalConn != null){
               isclose  = true;
               logicalConn.rollback();
               eventListentionMethod(true,null);
           }*/ 
       logicalConn = JdbcSqlConnectionWrapper.getInstance(this,physicalConn);
       isclose = false;
       return logicalConn; 
   }
   
  //Pooled connection method.
   public synchronized void close() throws SQLException {
                if (physicalConn != null) {
                        physicalConn.close();
                        physicalConn = null;
                }
                if (connectionEventListeners != null) {
                        connectionEventListeners.clear();
                        connectionEventListeners = null;
                }
   }
   

   public synchronized void eventListentionMethod(boolean isclose,SQLException sqlException) {
       if(connectionEventListeners == null){ return; }
       Iterator iterater = connectionEventListeners.entrySet().iterator();

       ConnectionEvent conEvent = new ConnectionEvent(this,sqlException);
       while (iterater.hasNext()) {
           ConnectionEventListener conEventListener = (ConnectionEventListener) ((Map.Entry)iterater.next()).getValue();
           if (isclose) {
               conEventListener.connectionClosed(conEvent);
           } else {
               conEventListener.connectionErrorOccurred(conEvent);
           }
       }

   } 

   public void addStatementEventListener(StatementEventListener listener) {
   //part of JDBC4
   }
   

   public void removeStatementEventListener(StatementEventListener listener) {
   //part of JDBC4
   }


}
