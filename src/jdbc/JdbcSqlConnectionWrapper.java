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

public class JdbcSqlConnectionWrapper extends JSqlError implements Connection, JSqlErrorType
{
    private Connection actualCon = null;
    private JdbcSqlPooledConnection poolcon = null;
    boolean isClosed=false;
    public JdbcSqlConnectionWrapper( JdbcSqlPooledConnection cpc,JdbcSqlConnection csqlc)
    {
        this.poolcon = cpc ;
        this.actualCon = csqlc ;    
        isClosed=false;
    }
    static JdbcSqlConnectionWrapper getInstance(JdbcSqlPooledConnection cpc,JdbcSqlConnection phyCon) 
    {
	return new JdbcSqlConnectionWrapper(cpc, phyCon);
    }
    
    public void close() throws SQLException
    {
        if(isClosed) return;
        isClosed = true;
        this.poolcon.eventListentionMethod(isClosed,null);
    }

    public void commit() throws SQLException
    {
          this.actualCon.commit();
    }

    public Statement createStatement() throws SQLException
    {
          return this.actualCon.createStatement();
    }
    public boolean getAutoCommit() throws SQLException
    {
          return this.actualCon.getAutoCommit();
    }

    public int getTransactionIsolation() throws SQLException
    {
                
          return this.actualCon.getTransactionIsolation();
    }

    public boolean isClosed() throws SQLException
    {
        return this.actualCon.isClosed();
    }

    public String nativeSQL (String query) throws SQLException
    {
        return query;
    }

    public PreparedStatement prepareStatement(String query) throws SQLException
    {
              return this.actualCon.prepareStatement(query);
    }

    public void rollback() throws SQLException
    {
            this.actualCon.rollback();
    }

    public void setAutoCommit(boolean aCommit) throws SQLException
    {
            this.actualCon.setAutoCommit(aCommit);
    }

    public void setTransactionIsolation(int level) throws SQLException
    {
        this.actualCon.setTransactionIsolation(level);
    }

/*    public java.sql.Statement createAutoStatement() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
*/

    //Unsupported Methods
    public void clearWarnings() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::clearWarnings called");

        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Statement createStatement(int resultSetType, int resultSetConcurrency) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::createStatement(int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Statement createStatement(int resultSetType, int resultSetConcurrency, int resultSetHoldability) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::createStatement(int, int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public String getCatalog() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::getCatalog called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public int getHoldability() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::getHoldability called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public DatabaseMetaData getMetaData() throws SQLException
    {
        return this.actualCon.getMetaData();
    }
    public Map getTypeMap() throws SQLException
    {  
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::getTypeMap called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public SQLWarning getWarnings() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::getWarnings called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public boolean isReadOnly() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::isReadOnly called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public CallableStatement prepareCall(String query ) throws SQLException
    {
        return this.actualCon.prepareCall( query);
    }
    public CallableStatement prepareCall(String query, int resultSetType,
                             int resultSetConcurrency) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::prepareCall(String, int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public CallableStatement prepareCall(String query, int resultSetType,
        int resultSetConcurrency, int resultSetHoldability) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::prepareCall(String, int, int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public PreparedStatement prepareStatement(String query, int autoGeneratedKeys) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::prepareStatement(String, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public PreparedStatement prepareStatement(String query, int[] columnIndexes) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::prepareStatement(String, int[]) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public PreparedStatement prepareStatement( String query, int resultSetType, 
                                  int resultSetConcurrency) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::prepareStatement(String, int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public PreparedStatement prepareStatement( String query, int resultSetType, int resultSetConcurrency, int resultSetHoldability) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::prepareStatement(String, int, int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public PreparedStatement prepareStatement(String query, String[] columnNames) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::prepareStatement(String, String[]) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void releaseSavepoint(Savepoint savepoint) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::releaseSavepoint called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void rollback(Savepoint savepoint) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::rollback called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setCatalog(String catalog) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::setCatalog called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setHoldability(int holdability) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::setHoldability called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setReadOnly(boolean rOnly) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::setReadOnly called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Savepoint setSavepoint() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::setSavepoint called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Savepoint setSavepoint(String query) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::setSavepoint(String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setTypeMap(Map map) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::setTypeMpa called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    //Java 1.6 methods
    public Struct createStruct(String typeName, Object[] attributes) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::createStruct called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Array createArrayOf(String typeName, Object[] elements) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::createArrayOf called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Blob createBlob() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::createBlob called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Clob createClob() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::createClob called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public NClob createNClob() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::createNClob called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public SQLXML createSQLXML() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::createSQLXML called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Properties getClientInfo() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::getClientInfo called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public String getClientInfo(String name) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::getClientInfo(String) called");
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
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::isValid called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public boolean isWrapperFor(Class ifact) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::isWrapperFor called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Class unwrap(Class iface) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlConnectionWrapper::unwrap called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
}
