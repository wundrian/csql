
package csql.jdbc;
import java.sql.Connection;
import java.sql.Statement;
import java.sql.SQLException;
import java.sql.ResultSetMetaData;
import java.sql.SQLWarning;

public final class JdbcSqlResultSetMetaData
extends JSqlError implements ResultSetMetaData, JSqlErrorType
{
    private boolean isClosed;
    JdbcSqlStatement stmt; // This guy creates me

    JdbcSqlResultSetMetaData()
    {
        isClosed = false;
    }
    void setStmt( JdbcSqlStatement s )
    {
        stmt = s;
        isClosed = false;
    }

    public void close() throws SQLException
    {
        if( ! isClosed ) 
            isClosed = true;
        return;
    }

    public int getColumnCount () throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        return( stmt.jniStmt.getNoOfFields() );
    }
    public int getColumnIndex (String name) throws SQLException 
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        throw getException( CSQL_NOT_SUPPORTED );
        //return( stmt.jniStmt.findColumn( name ) );
    }

    public String getColumnName (int colNum) throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );

        String name= stmt.jniStmt.getFieldName( colNum-1 );
        return( name );
    }
    public String getColumnLabel (int colNum) throws SQLException
    {
        return getColumnName( colNum );
    }

    public boolean isReadOnly (int colNum) throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        return( false );
    }
    public boolean isWritable (int colNum) throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        return( true );
    }
    public boolean isDefinitelyWritable (int colNum) throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        return( true );
    }

    // TODO
    public String getColumnClassName(int colNum) throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public int getColumnType (int colNum) throws SQLException //TODO
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public String getColumnTypeName (int colNum) throws SQLException //TODO
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public boolean isCaseSensitive (int colNum) throws SQLException //TODO
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        return( false );
    }
    public boolean isSigned (int colNum) throws SQLException //TODO
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public int isNullable (int colNum) throws SQLException //TODO
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public int getPrecision (int colNum) throws SQLException //TODO
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public int getScale (int colNum) throws SQLException //TODO
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public String getSchemaName (int colNum) throws SQLException
    {
        return( null );
    }
    public String getTableName (int colNum) throws SQLException
    {
        return( null );
    }

    // UN-SUPPORTED API's
    public int getColumnDisplaySize (int colNum) throws SQLException
    {
        return( 1 );
    }
    public boolean isAutoIncrement (int colNum) throws SQLException
    {
        return( false );
    }
    public boolean isCurrency (int colNum) throws SQLException
    {
        return( true );
    }
    public String getCatalogName (int colNum) throws SQLException
    {
        return( null );
    }
    public boolean isSearchable (int colNum) throws SQLException
    {
        return( true );
    }
}
