
package csql.jdbc;

import java.math.BigDecimal;
import java.net.URL;

import java.sql.Connection;
import java.sql.Statement;
import java.sql.SQLException;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLWarning;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StringBufferInputStream;

import java.sql.Clob;
import java.sql.Blob;
import java.sql.Ref;
import java.sql.Array;
import java.sql.Types;

import java.sql.RowId;
import java.sql.SQLXML;
import java.io.Reader;
import java.sql.NClob;
import java.sql.Wrapper;

public class JdbcSqlResultSet extends JSqlError implements ResultSet, JSqlErrorType
{
    public JdbcSqlStatement stmt; // This guy creates me
    public JdbcSqlResultSetMetaData rsmd;

    public boolean closedFlag;
    long curRow;


    JdbcSqlResultSet()
    {
        rsmd = new JdbcSqlResultSetMetaData();
        closedFlag = false;
        curRow = -1;
    }
    void setStmt( JdbcSqlStatement jdbcStmt )
    {
        stmt = jdbcStmt;
        rsmd.setStmt( jdbcStmt );
        closedFlag = false;
        curRow = -1;
    }
    protected void finalize ()
    {
        try
        {
            if(!closedFlag) close();
        }
        catch(SQLException e)
        {
            System.out.println(e);
        }
    }

    // API's
    public void close() throws SQLException
    {
        if( closedFlag ) return;

        closedFlag = true;
        curRow = -1;
	//rsmd.close(); //commented by praba
        //after close the app can reexecute.
        if (stmt != null) stmt.closeScan();
        return;
    }

    // Move to next tuple
    public boolean next () throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );

        if( 0 == stmt.jniStmt.next() )
        {
            curRow = -2;
            return( false );
        }
        curRow += 1;

        return( true );
    }
    public ResultSetMetaData getMetaData () throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );
        return( rsmd );
    }
    public SQLWarning getWarnings() throws SQLException
    {
        return( null );
    }
    public void clearWarnings() throws SQLException
    {
        return;
    }
    public int findColumn (String colName) throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );

        int colnum = stmt.jniStmt.findColumn( colName );
        return( colnum );
    }
    public int getType() throws SQLException
    {
        return( ResultSet.TYPE_FORWARD_ONLY );
    }
    public int getConcurrency() throws SQLException
    {
        return( ResultSet.CONCUR_READ_ONLY );
    }
    public Statement getStatement() throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );
        return( stmt );
    }
    public boolean isFirst() throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );

        if( curRow == 0 )
            return( true );

        return( false );
    }
    public boolean isBeforeFirst() throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );

        if( curRow == -1 )
            return( true );

        return( false );
    }
    public boolean isAfterLast() throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );

        if( curRow == -2 )
            return( true );

        return( false );
    }

    // Provide data to application
    // SHORT
    public short getShort (int colNum ) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        short out = stmt.jniStmt.getShort( colNum - 1 );
	if( false ) throw new SQLException();
        return out;
    }
    public short getShort (String colName ) throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );
        return( getShort( findColumn( colName ) ) );
    }

    // INTEGER
    public int getInt (int colNum ) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        int out = stmt.jniStmt.getInt( colNum - 1 );
        if( false ) throw new SQLException();
        return out;
    }
    public int getInt (String colName) throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );
        return( getInt( findColumn( colName ) ) );
    }

    // LONG
    public long getLong (int colNum) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        long out = stmt.jniStmt.getLong( colNum-1 );
        if( false ) throw new SQLException();
        return out;
    }
    public long getLong (String colName) throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );
        return( getLong( findColumn( colName ) ) );
    }

    // BYTE
    public byte getByte (int colNum) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        byte out = stmt.jniStmt.getByte( colNum-1 );
        if( false ) throw new SQLException();
        return out;
    }
    public byte getByte (String colName) throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );
        return( getByte( findColumn( colName ) ) );
    }

    // FLOAT
    public float getFloat (int colNum) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        float out = stmt.jniStmt.getFloat( colNum-1 );
        if( false ) throw new SQLException();
        return out;
    }
    public float getFloat (String colName) throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );
        return( getFloat( findColumn( colName ) ) );
    }

    // DOUBLE
    public double getDouble (int colNum) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        double out = stmt.jniStmt.getDouble( colNum-1 );
        if( false ) throw new SQLException();
        return out;
    }
    public double getDouble (String colName) throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );
        return( getDouble( findColumn( colName ) ) );
    }

    // DECIMAL
    public BigDecimal getBigDecimal( int colNum )
       throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        throw getException( CSQL_NOT_SUPPORTED );

        // TODO 
        // BigDecimal out = new BigDecimal( stmt.jniStmt.getBigDecimal( colNum-1 ) ); 
        //return out;
    }
    public BigDecimal getBigDecimal(String colName)
       throws SQLException
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );
        return( getBigDecimal( findColumn( colName ) ) );
    }
    public BigDecimal getBigDecimal (int colNum, int scale)
        throws SQLException
    {
        return( getBigDecimal( colNum ) );
    }
    public BigDecimal getBigDecimal (String colName, int scale)
        throws SQLException
    {
        return( getBigDecimal( colName ) );
    }

    // STRING/VARSTRING
    public String getString(int colNum) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        // Get value
        String out = stmt.jniStmt.getString( colNum-1 );

        return out;
    }
    public String getString (String colName) throws SQLException
    {
        return( getString( findColumn( colName ) ) ); 
    }
    public InputStream getAsciiStream(int colNum) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        String out = stmt.jniStmt.getString( colNum-1 );

        return( new StringBufferInputStream( out ) );
    }
    public java.io.InputStream getAsciiStream (String colName) throws SQLException
    {
        return( getAsciiStream( findColumn( colName ) ) );
    }
    public java.io.Reader getCharacterStream(int colNum)
       throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        InputStream iS = getAsciiStream( colNum );
        if( iS == null )
            return( null );

        return( new InputStreamReader( iS ) );
    }
    public java.io.Reader getCharacterStream(String colName)
       throws SQLException
    {
        return( getCharacterStream( findColumn( colName ) ) );
    }

    // BOOLEAN
    public boolean getBoolean (int colNum) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        boolean out = stmt.jniStmt.getBoolean( colNum-1 );

        return out;
    }
    public boolean getBoolean (String colName) throws SQLException
    {
        return( getBoolean( findColumn( colName ) ) );
    }

    // BINARY/VARBINARY
	public byte [] getBytes(int colNum) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        throw getException( CSQL_NOT_SUPPORTED );
        //byte[] out = stmt.jniStmt.getBytes( colNum-1 );
        //return out;
    }
    public byte[] getBytes (String colName) throws SQLException
    {
        return( getBytes( findColumn( colName ) ) );
    }

    // DATE
    public java.sql.Date getDate (int colNum) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        java.sql.Date out = stmt.jniStmt.getDate( colNum-1 );

        return out;
    }
    public java.sql.Date getDate(int colNum, java.util.Calendar cal)
       throws SQLException
    {
        return( getDate( colNum ) );
    }
    public java.sql.Date getDate (String colNum) throws SQLException
    {
        return( getDate( findColumn( colNum ) ) );
    }
    public java.sql.Date getDate(String colName, java.util.Calendar cal)
       throws SQLException
    {
        return( getDate( colName ) );
    }

    // TIME
    public java.sql.Time getTime (int colNum) throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        // Get value
        java.sql.Time out = stmt.jniStmt.getTime( colNum-1 );

        return out;
    }
    public java.sql.Time getTime(int colNum, java.util.Calendar cal)
       throws SQLException
    {
        return( getTime( colNum ) );
    }
    public java.sql.Time getTime (String colName) throws SQLException
    {
        return( getTime( findColumn( colName ) ) );
    }
    public java.sql.Time getTime(String colName, java.util.Calendar cal)
       throws SQLException
    {
        return( getTime( colName ) );
    }

    // TIMESTAMP
    public java.sql.Timestamp getTimestamp (int colNum)
        throws SQLException
    {
        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        java.sql.Timestamp out = stmt.jniStmt.getTimestamp( colNum-1 );

        return out;
    }
    public java.sql.Timestamp getTimestamp(int colNum,
       java.util.Calendar cal) throws SQLException
    {
        return( getTimestamp( colNum ) );
    }
    public java.sql.Timestamp getTimestamp (String colName)
        throws SQLException
    {
        return( getTimestamp( findColumn( colName ) ) );
    }
    public java.sql.Timestamp getTimestamp(String colName,
       java.util.Calendar cal) throws SQLException
    {
        return( getTimestamp( colName ) );
    }

    public Object getObject(int colNum) throws SQLException
    {
        Object obj = new String("no obj");

        if( closedFlag || curRow < 0 ) throw getException( CSQL_INVALID_STATE );

        switch ( rsmd.getColumnType( colNum ) )
        {
            case Types.DOUBLE:
                obj = new Double( getDouble( colNum ) ); break;
            case Types.FLOAT:
                obj = new Float( getFloat( colNum ) ); break;
            case Types.DECIMAL:
            case Types.NUMERIC:
                obj = getBigDecimal( colNum ); break;

            case Types.BIGINT:
                obj = new Long( getLong( colNum ) ); break;
            case Types.INTEGER:
                obj = new Integer( getInt( colNum ) ); break;
            case Types.SMALLINT: 
                obj = new Short( getShort( colNum ) ); break;
            case Types.TINYINT:
                obj = new Byte( getByte( colNum ) ); break;
            case Types.BIT:
                obj = new Boolean( getBoolean( colNum ) ); break;

            case Types.DATE:
                obj = getDate( colNum ); break;
            case Types.TIME:
                obj = getTime( colNum ); break;
            case Types.TIMESTAMP:
                obj = getTimestamp( colNum ); break;

            case Types.CHAR:
                obj = getString( colNum ); break;
            case Types.VARCHAR:
                obj = getString( colNum ); break;
            case Types.BINARY:
            case Types.VARBINARY:
                obj = getBytes( colNum ); break;

            default: throw getException( CSQL_INVALID_DATATYPE );
        }
        // Return null if value read is null //TODO
        //if( wasNull() )
        //    return( null );

        return( obj );
    }
    public Object getObject (String colName) throws SQLException
    {
        return( getObject( findColumn( colName ) ) );
    }
    public Object getObject(int i, java.util.Map map) throws SQLException
    {
        return( getObject( i ) );
    }
    public Object getObject(String colName, java.util.Map map) 
        throws SQLException
    {
        return( getObject( colName ) );
    }

    public int getRow() throws SQLException
    {
        if( curRow < 0 )
            return( 0 );

        return( (int) curRow + 1 );
    }

    // UN-SUPPORTED API's
    public boolean wasNull () throws SQLException // TODO
    {
        if( closedFlag ) throw getException( CSQL_INVALID_STATE );
        throw getException( CSQL_NOT_SUPPORTED );
        //return( stmt.jniStmt.wasNull() );
    }
    public String getCursorName () throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public boolean absolute( int row ) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void beforeFirst() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void afterLast() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public boolean first() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public boolean last() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public boolean relative( int rows ) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public boolean previous() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void setFetchDirection(int direction) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public int getFetchDirection() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void setFetchSize(int rows) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public int getFetchSize() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
	public InputStream getUnicodeStream(int colNum) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
	public InputStream getBinaryStream(int colNum) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public java.io.InputStream getUnicodeStream (String colName) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public java.io.InputStream getBinaryStream (String colName) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void setMaxRows(int maxRows) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void setMaxFieldSize(int maxFieldSize) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public boolean rowUpdated() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public boolean rowInserted() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public boolean rowDeleted() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNull(int colNum) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBoolean(int colNum, boolean x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateByte(int colNum, byte x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateShort(int colNum, short x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateInt(int colNum, int x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateLong(int colNum, long x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateFloat(int colNum, float x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateDouble(int colNum, double x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBigDecimal(int colNum, BigDecimal x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateString(int colNum, String x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBytes(int colNum, byte x[]) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateDate(int colNum, java.sql.Date x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateTime(int colNum, java.sql.Time x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateTimestamp(int colNum, java.sql.Timestamp x)
       throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateAsciiStream(int colNum,
       java.io.InputStream x, int length) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBinaryStream(int colNum,
       java.io.InputStream x, int length) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateCharacterStream(int colNum,
       java.io.Reader x, int length) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNull(String colName) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBoolean(String colName, boolean x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateByte(String colName, byte x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateShort(String colName, short x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateInt(String colName, int x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateLong(String colName, long x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateFloat(String colName, float x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateDouble(String colName, double x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBigDecimal(String colName, BigDecimal x)
        throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateString(String colName, String x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBytes(String colName, byte x[]) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateDate(String colName, java.sql.Date x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateTime(String colName, java.sql.Time x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateTimestamp(String colName, java.sql.Timestamp x)
      throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateAsciiStream(String colName,
      java.io.InputStream x, int length) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBinaryStream(String colName,
      java.io.InputStream x, int length) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateCharacterStream(String colName,
      java.io.Reader reader, int length) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateObject(int colNum, Object x, int scale)
      throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateObject(int colNum, Object x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void insertRow() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateRow() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void deleteRow() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void refreshRow() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void cancelRowUpdates() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void moveToInsertRow() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void moveToCurrentRow() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public Ref getRef(int i) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public Blob getBlob(int i) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public Clob getClob(int i) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public Array getArray(int i) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public Ref getRef(String colName) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public Blob getBlob(String colName) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public Clob getClob(String colName) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public Array getArray(String colName) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public    boolean isLast() throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateObject(String colName, Object x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public    void updateObject(String colName, Object x, int scale)
                                                    throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public URL getURL(int colNum)
			throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public URL getURL(String colName)
			throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateRef(int colNum, Ref x)
			throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateRef(String colName, Ref x)
			throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBlob(int colNum, Blob x)
			 throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBlob(String colName, Blob x)
			 throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateClob(int colNum, Clob x)
			 throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateClob(String colName, Clob x)
			 throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateArray(int colNum, Array x)
			  throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateArray(String colName, Array x)
			  throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    //java 1.6 methods
    public void updateRowId(int colIndex, RowId x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateRowId(String colLabel, RowId x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateSQLXML(int colIndex, SQLXML x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateSQLXML(String colLabel, SQLXML x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNClob(int colIndex, NClob x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNClob(int colIndex, Reader x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNClob(int colIndex, Reader x, long length)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNClob(String colIndex, NClob x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNClob(String colIndex, Reader x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNClob(String colIndex, Reader x, long length)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNString(int colIndex, String x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNString(String colIndex, String x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNCharacterStream(int colIndex, Reader x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNCharacterStream(int colIndex, Reader x, long length)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNCharacterStream(String colIndex, Reader x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateNCharacterStream(String colIndex, Reader x, long length)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateCharacterStream(int colIndex, Reader x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateCharacterStream(String colIndex, Reader x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateCharacterStream(int colIndex, Reader x, long length)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateCharacterStream(String colIndex, Reader x, long length)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBinaryStream(int colIndex, InputStream x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBinaryStream(String colIndex, InputStream x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBinaryStream(int colIndex, InputStream x, long length)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBinaryStream(String colIndex, InputStream x, long length)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateAsciiStream(int colIndex, InputStream x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateAsciiStream(String colIndex, InputStream x)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateAsciiStream(int colIndex, InputStream x, long length)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateAsciiStream(String colIndex, InputStream x, long length)
                                             throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateClob(int colNum, Reader x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateClob(String colNum, Reader x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateClob(int colNum, Reader x, long length) 
                                                  throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateClob(String colNum, Reader x, long length) 
                                                  throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBlob(int colNum, InputStream x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBlob(String colNum, InputStream x) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBlob(int colNum, InputStream x, long length) 
                                                    throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public void updateBlob(String colNum, InputStream x, long length)
                                                     throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public Reader getNCharacterStream(int colIndex) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public Reader getNCharacterStream(String colLabel) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public NClob getNClob(int colIndex) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public NClob getNClob(String colLabel) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public String getNString(int colIndex) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public String getNString(String colLabel) throws SQLException
    {
        throw getException( CSQL_NOT_SUPPORTED );
    }
    public SQLXML getSQLXML(int colIndex) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public SQLXML getSQLXML(String colLabel) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public boolean isClosed()
    {
        return closedFlag;
    }
    public int getHoldability() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public RowId getRowId(int val) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public RowId getRowId(String val) throws SQLException
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
