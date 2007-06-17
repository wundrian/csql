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

public final class JdbcSqlConnection extends JSqlError implements Connection, JSqlErrorType
{
    private boolean isClosed;
    private JSqlConnection conn;
    private LinkedList stmtList;
    private boolean autoCommit = true; //TODO
    private boolean transRunning = false;
    private int isoLevel = 2; //->READ_COMMITTED
    private boolean readOnly = false;

    public JSqlConnection getConnection()
    {
        return conn;
    }

    JdbcSqlConnection(String username, String password) throws SQLException
    {
        if( password == null || username == null ) throw getException(CSQL_AUTHEN_ERR);
        conn = new JSqlConnection();
        conn.alloc();
        int rv = conn.connect(username, password);
        if (rv != 0) 
        {
            conn.free();
            throw getException(CSQL_CON_REJECTED);
        }
        isClosed = false;
        rv = conn.beginTrans(isoLevel);
        if (rv != 0) 
        {
            throw getException(CSQL_TRANS_NOT_STARTED);
        }
        stmtList = new LinkedList();
        System.out.println("stmtList is initialized");
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

        if( conn.rollback() != 0 )
            throw getException(CSQL_TRANS_NOT_ROLLBACK);
        if(conn.disconnect() != 0 )
            throw getException(CSQL_NOT_DISCONNECT);

        conn.free(); 
        isClosed = true;
    }

    public void commit() throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        if( conn.commit() != 0 )
            throw getException(CSQL_TRANS_NOT_COMMIT);
        if (conn.beginTrans(isoLevel) != 0)
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
        if( conn.rollback() != 0 )
            throw getException(CSQL_TRANS_NOT_ROLLBACK);
        if (conn.beginTrans(isoLevel) != 0)
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
        throw getException(CSQL_NOT_SUPPORTED);
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
}
