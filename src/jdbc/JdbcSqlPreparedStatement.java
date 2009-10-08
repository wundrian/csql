package csql.jdbc;
import java.io.InputStream;
import java.io.Reader;
import java.math.BigDecimal;
import java.util.Calendar;
import java.net.URL;

import java.sql.Connection;
import java.sql.Statement;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Blob;
import java.sql.Clob;
import java.sql.ResultSetMetaData;
import java.sql.ParameterMetaData;
import java.sql.SQLException;
import java.sql.Ref;
import java.sql.Array;
import java.sql.SQLXML;
import java.sql.RowId;

import java.sql.NClob;
public class JdbcSqlPreparedStatement extends JdbcSqlStatement
                   implements PreparedStatement
{
    public JdbcSqlParameterMetaData pmtd;
    JdbcSqlPreparedStatement(Connection con)
    {
        super(con);
    }
    public void clearParameters() throws SQLException
    {
        //TODO
        return;
    }
    public boolean execute() throws SQLException
    {
        return executeInt();
    }
    public ResultSet executeQuery() throws SQLException
    {
        if(!executeInt())
            throw getException(CSQL_NOT_QUERY);
        //Praba changed this
        rs.setStmt( this );
        if( isFirstExecute) { 
            rs.setProjField();
            isFirstExecute = false;
        }
        return( rs );
        //return null;
    }
    public int executeUpdate() throws SQLException
    {
        if(executeInt())
            throw getException(CSQL_NOT_UPDATE);
        return(rowsAffect);
    }
    public ResultSetMetaData getMetaData() throws SQLException
    {
        //TODO
        return null;
    }

    public ParameterMetaData getParameterMetaData() throws SQLException
    {
        pmtd = new JdbcSqlParameterMetaData();
        pmtd.setStmt(this);
        return pmtd;
    }
    public void setByte(int param, byte value) throws SQLException
    {
        jniStmt.setByte(param, value);
        return;
    }
    public void setDate(int param, java.sql.Date value) throws SQLException
    {
        jniStmt.setDate(param, value);
        return;
    }
    public void setDouble(int param, double value) throws SQLException
    {
        jniStmt.setDouble(param, value);
        return;
    }
    public void setFloat(int param, float value) throws SQLException
    {
        jniStmt.setFloat(param, value);
        return;
    }
    public void setInt(int param, int value) throws SQLException
    {
        jniStmt.setInt(param, value);
        return;
    }
    public void setLong(int param, long value) throws SQLException
    {
        jniStmt.setLong(param, value);
        return;
    }
    public void setNull (int param, int sqlType) throws SQLException
    {
        jniStmt.setNull(param);
        return;
    }
    public void setObject(int param, Object obj) throws SQLException
    {
        if(obj instanceof Double)
            setDouble(param, ((Double)obj).doubleValue() );
        else if(obj instanceof Float)
            setFloat(param, ((Float)obj).floatValue() );
        else if(obj instanceof Long)
            setLong(param, ((Long)obj).longValue() );
        else if(obj instanceof Integer)
            setInt(param, ((Integer)obj).intValue() );
        else if(obj instanceof Short)
            setShort(param, ((Short)obj).shortValue() );
        else if(obj instanceof Byte)
            setByte(param, ((Byte)obj).byteValue() );
        else if(obj instanceof java.sql.Date )
            setDate(param, ((java.sql.Date) obj));
        else if(obj instanceof java.sql.Time )
            setTime(param, ((java.sql.Time) obj));
        else if(obj instanceof java.sql.Timestamp )
            setTimestamp(param, ((java.sql.Timestamp) obj));
        else if(obj instanceof String )
            setString(param, ((String) obj));
        else
            throw getException(CSQL_INVALID_DATATYPE);

        return;
    }
    public void setShort(int param, short value) throws SQLException
    {
        jniStmt.setShort(param, value);
        return;
    }
    public void setString(int param, String value) throws SQLException
    {
        jniStmt.setString(param, value);
        return;
    }
    public void setTime(int param, java.sql.Time value) throws SQLException
    {
        jniStmt.setTime(param, value);
        return;
    }
    public void setTimestamp(int param, java.sql.Timestamp value) throws SQLException
    {
        jniStmt.setTimestamp(param, value);
        return;
    }




    //Unsupported APIs
    public void addBatch() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::addBatch called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setArray (int i, Array value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setArray called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setAsciiStream(int parameterIndex, InputStream value, int length) 
                                           throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setAsciiStream called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void	setBigDecimal(int parameterIndex, BigDecimal value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setBigDecimal called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setBinaryStream(int parameterIndex, InputStream value, int length) 
                                           throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setBinaryStream called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setBlob(int i, Blob value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setBlob called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setBoolean (int param, boolean value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setBoolean called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setBytes(int param, byte value[]) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setBytes called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setCharacterStream(int param, Reader reader, int length) 
                                            throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setCharacterStream called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setClob (int i, Clob value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setClob called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setDate(int param, java.sql.Date value, Calendar cal) 
                                    throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setDate called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setNull (int param, int sqlType, String typeName)
        throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setNull called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setObject (int param, Object value, int targetSqlType)
        throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setObject(int, Object, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setObject (int param, Object value, int targetSqlType, int scale) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setObject(int, Object, int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setRef(int i, Ref value)  throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setRef called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setTime(int param, java.sql.Time value, Calendar cal) 
                                             throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setTime called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setTimestamp(int param, java.sql.Timestamp value, 
                               Calendar cal) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setTimeStamp called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setUnicodeStream (int param, InputStream value, int length) 
                                                       throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setUnicodeStream called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setURL(int parameterName, URL value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setURL called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    //java 1.6 methods
    public void setBlob(int  paramIndex, InputStream value ) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setBlob(int, InputStream) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setBlob(int  paramIndex, InputStream value, long length ) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setBlob(int, InputStream, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setClob(int  paramIndex, Reader value ) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setClob(int, Reader) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setClob(int  paramIndex, Reader value, long length ) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setClob(int, Reader, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setNCharacterStream(int  paramIndex, Reader value) 
                                                     throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setNCharacterStream(int, Reader) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setNCharacterStream(int  paramIndex,Reader value,long length)
                                                           throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setNCharacterStream(int, Reader, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setNClob(int  paramIndex, NClob value) 
                                                  throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setNClob(int, NClob) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setNClob(int  paramIndex, Reader value) 
                                                  throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setNClob(int, Reader) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setNClob(int  paramIndex, Reader value, long length) 
                                                  throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setNClob(int, Reader, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setNString(int  paramIndex, String value) 
                                                  throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setNString called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setCharacterStream(int param, Reader reader) 
                                            throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setCharacterStream(int, Reader) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setCharacterStream(int param, Reader reader, long length) 
                                            throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setCharacterStream(int, Reader, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setBinaryStream(int parameterIndex, InputStream value) 
                                           throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setBinaryStream(int, InputStream) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setBinaryStream(int parameterIndex, InputStream value, long length) 
                                           throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setBinaryStream(int, InputStream, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setAsciiStream(int parameterIndex, InputStream value) 
                                           throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setAsciiStream(int, InputStream) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setAsciiStream(int parameterIndex, InputStream value, long length) 
                                           throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setAsciiStream(int, InputStream, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setSQLXML(int paramIndex, SQLXML xmlObj) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setSQLXML called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setRowId(int paramIndex, RowId x) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlPreparedStatement::setRowId called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
}
