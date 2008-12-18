package csql.jdbc;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.SQLWarning;
import java.sql.DatabaseMetaData;
import java.sql.Savepoint;
import java.sql.Statement;
import java.sql.PreparedStatement;
import java.sql.CallableStatement;
import java.lang.String;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Map;
import java.util.Properties;

import java.sql.Clob;
import java.sql.NClob;
import java.sql.Blob;
import java.sql.SQLXML;
import java.sql.Struct;
import java.sql.Array;

public final class JdbcSqlConnection extends JSqlError implements Connection, JSqlErrorType
{
    private boolean isClosed;
    private JSqlConnection jniConn;
    private LinkedList stmtList;
    private boolean autoCommit = true; //TODO
    private boolean transRunning = false;
    private int isoLevel = 2; //->READ_COMMITTED
    private boolean readOnly = false;
    public int mode = 1;
    public String hName="localhost";
    public int portNo=5678;
    public JSqlConnection getConnection()
    {
        return jniConn;
    }

    JdbcSqlConnection(int imode,String hostname,int portno, String username, String password) throws SQLException
    {
        if( password == null || username == null ) throw getException(CSQL_AUTHEN_ERR);
        if (username.length() > 64 || password.length() > 64) throw getException(CSQL_AUTHEN_ERR);
        jniConn = new JSqlConnection();
        if(imode==3){
        	hName=hostname;
        	portNo=portno;
        }
        jniConn.alloc(imode,hostname,portNo);
        mode = imode;
        int rv = jniConn.connect(username, password);
        if (rv != 0) 
        {
            jniConn.free();
            throw getException(CSQL_CON_REJECTED);
        }
        isClosed = false;
        rv = jniConn.beginTrans(isoLevel);
        if (rv != 0) 
        {
            throw getException(CSQL_TRANS_NOT_STARTED);
        }
        stmtList = new LinkedList();
    }

    protected void finalize ()
    {
        try
        {
            if(!isClosed)
                close();
        }
        catch(SQLException e)
        {
            System.out.println( e );
        }
    }

    public void close() throws SQLException
    {
        if(isClosed) return;
        if(stmtList.size() > 0)
        {
            Statement stmt;
            ListIterator lstIter = stmtList.listIterator(0);
            while(lstIter.hasNext())
            {
                stmt = (Statement) lstIter.next();
                stmt.close();
                lstIter.remove();
            }
        }
        stmtList = null;

        if( jniConn.rollback() != 0 )
            throw getException(CSQL_TRANS_NOT_ROLLBACK);
        if(jniConn.disconnect() != 0 )
            throw getException(CSQL_NOT_DISCONNECT);

        jniConn.free(); 
        isClosed = true;
    }

    public void commit() throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        if( jniConn.commit() != 0 )
            throw getException(CSQL_TRANS_NOT_COMMIT);
        if (jniConn.beginTrans(isoLevel) != 0)
            throw getException(CSQL_TRANS_NOT_STARTED);
        return;
    }

    public Statement createStatement() throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        JdbcSqlStatement stmt = new JdbcSqlStatement(this);
        stmtList.add(stmt);
        return(stmt);
    }

    public boolean getAutoCommit()
    {
        return(autoCommit);
    }

    public int getTransactionIsolation() throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        int level = TRANSACTION_READ_COMMITTED;
        switch(isoLevel)
        {
            case 1:
                level = TRANSACTION_READ_UNCOMMITTED; break;
            case 2:
                level = TRANSACTION_READ_COMMITTED; break;
            case 3:
                level = TRANSACTION_REPEATABLE_READ; break;
            default:
                throw getException(CSQL_INVALID_ISOLATION);
        }
        return level;
    }

    public boolean isClosed() throws SQLException
    {
        return isClosed;
    }

    public String nativeSQL (String query) throws SQLException
    {
        return query;
    }

    public PreparedStatement prepareStatement(String query) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        JdbcSqlPreparedStatement stmt = new JdbcSqlPreparedStatement(this);
        stmt.prepareInt(query);
        stmtList.add(stmt);
        return(stmt);
    }

    public void rollback() throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        if( jniConn.rollback() != 0 )
            throw getException(CSQL_TRANS_NOT_ROLLBACK);
        if (jniConn.beginTrans(isoLevel) != 0)
            throw getException(CSQL_TRANS_NOT_STARTED);
        return;
    }

    public void setAutoCommit(boolean aCommit) throws SQLException
    {
        //TODO
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        autoCommit = aCommit;
    }

    public void setTransactionIsolation(int level) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        switch(level)
        {
            case TRANSACTION_READ_UNCOMMITTED:
                isoLevel = 1; break;
            case TRANSACTION_READ_COMMITTED:
                isoLevel = 2; break;
            case TRANSACTION_REPEATABLE_READ:
                isoLevel = 3; break;
            case TRANSACTION_SERIALIZABLE:
                throw getException(CSQL_NOT_SUPPORTED);
            case TRANSACTION_NONE:
            default: 
                throw getException(CSQL_INVALID_ISOLATION);
        }
    }

/*    public java.sql.Statement createAutoStatement() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
*/

    //Unsupported Methods
    public void clearWarnings() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Statement createStatement(int resultSetType, int resultSetConcurrency) 
                                     throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Statement createStatement(int resultSetType, int resultSetConcurrency,
        int resultSetHoldability) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public String getCatalog() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public int getHoldability() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public DatabaseMetaData getMetaData() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Map getTypeMap() throws SQLException
    {  
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public SQLWarning getWarnings() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public boolean isReadOnly() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public CallableStatement prepareCall(String query ) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        JdbcSqlCallableStatement stmt = new JdbcSqlCallableStatement(this);
        stmt.prepareProc(query);
        stmtList.add(stmt);
        return(stmt);
    }
    public CallableStatement prepareCall(String query, int resultSetType,
                             int resultSetConcurrency) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public CallableStatement prepareCall(String query, int resultSetType,
        int resultSetConcurrency, int resultSetHoldability) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public PreparedStatement prepareStatement(String query,
        int autoGeneratedKeys) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public PreparedStatement prepareStatement(String query,
        int[] columnIndexes) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public PreparedStatement prepareStatement( String query, int resultSetType, 
                                  int resultSetConcurrency) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public PreparedStatement prepareStatement( String query, int resultSetType,
             int resultSetConcurrency, int resultSetHoldability) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public PreparedStatement prepareStatement(String query,
        String[] columnNames) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void releaseSavepoint(Savepoint savepoint) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void rollback(Savepoint savepoint) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setCatalog(String catalog) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setHoldability(int holdability) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setReadOnly(boolean rOnly) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Savepoint setSavepoint() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Savepoint setSavepoint(String query) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setTypeMap(Map map) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    //Java 1.6 methods
    public Struct createStruct(String typeName, Object[] attributes) 
                                                 throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Array createArrayOf(String typeName, Object[] elements) 
                                                 throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Blob createBlob() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Clob createClob() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public NClob createNClob() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public SQLXML createSQLXML() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Properties getClientInfo() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public String getClientInfo(String name) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setClientInfo(String name , String value) 
    {
        return;
    }
    public void setClientInfo(Properties properties) 
    {
        return;
    }
    public boolean isValid(int timeout) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public boolean isWrapperFor(Class ifact) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Class unwrap(Class iface) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
}
