/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package csql.jdbc;


import java.io.InputStream;
import java.io.Reader;
import java.math.BigDecimal;
import java.net.URL;
import java.sql.Array;
import java.sql.Blob;
import java.sql.CallableStatement;
import java.sql.Clob;
import java.sql.Date;
import java.sql.NClob;
import java.sql.Ref;
import java.sql.RowId;
import java.sql.SQLException;
import java.sql.SQLXML;
import java.sql.Time;
import java.sql.Timestamp;
import java.util.Calendar;
import java.util.Map;
/**
 *
 * @author bijaya
 */
public final class JdbcSqlCallableStatement  extends JdbcSqlPreparedStatement implements CallableStatement
{
    
    JdbcSqlCallableStatement(JdbcSqlConnection con)
    {
        super(con);
 
    }
    boolean isResultSetused = false;
    //JdbcSqlPreparedStatement.execute()
   public void prepareProc(String query) throws SQLException
   {
        int rv = 0;
        /*if(isPrepared) 
	{
            if(isResultSetused) rs.close();
            jniStmt.freeStmt();
            isPrepared = false;
        }
        rv = jniStmt.prepare(query);
        if( rv != 0 ) // 0 ->OK
        {
            throw getException(CSQL_PREPARE_ERR);
        }*/
        prepareInt(query);
        isPrepared = true;
   }
   public boolean execute() throws SQLException
   {
        if (!isPrepared) throw getException(CSQL_NOT_PREPARED);
       /* rowsAffect = jniStmt.execute();
        if( rowsAffect < 0 )
            throw getException(CSQL_EXECUTE_ERR);
        return true;*/
        return executeInt();
   }
   
    
   public java.sql.ResultSet executeQuery() throws SQLException
   {
       if (!isPrepared) throw getException(CSQL_NOT_PREPARED);
        rowsAffect = jniStmt.execute();
        if( rowsAffect < 0 )
            throw getException(CSQL_EXECUTE_ERR);
       rs.setStmt( this );
       rs.setProjField();
       isResultSetused = true;
       return( rs );
   }
   
   //JdbcSqlPreparedStatement.executeQuery()
   public int executeUpdate() throws SQLException
   {
       if(!execute())
           throw getException(CSQL_NOT_UPDATE);
        return(rowsAffect);
       
   }
   public synchronized Array getArray(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getArray(int) called");
        throw getException(CSQL_NOT_SUPPORTED);
   }
    
   public synchronized Array getArray(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getArray(String) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
    
   public synchronized BigDecimal getBigDecimal(int index, int scale) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getBigDecimal(int, int) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
   public synchronized BigDecimal getBigDecimal(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getBigDecimal(int) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
   public synchronized BigDecimal getBigDecimal(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getBigDecimal(String) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
    
   public synchronized Blob getBlob(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getBlob(int) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
   
   public synchronized Blob getBlob(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getBlob(String) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
  
   public synchronized boolean getBoolean(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getBoolean(int) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
    
   public synchronized boolean getBoolean(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getBoolean(String) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
             
    
   public synchronized byte getByte(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getByte(int) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
       
    
   public synchronized byte getByte(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getByte(String) called");
        throw getException(CSQL_NOT_SUPPORTED);
   }
    
   public synchronized byte[] getBytes(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getBytes(int) called");
         throw getException(CSQL_NOT_SUPPORTED);
   }
         
     
   public synchronized byte[] getBytes(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getBytes(String) called");
         throw getException(CSQL_NOT_SUPPORTED);
   
   }
   
   public synchronized Clob getClob(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getClob(int) called");
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
     
   public synchronized Clob getClob(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getClob(String) called");
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   
   public synchronized Date getDate(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getDate(int) called");
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   public synchronized Date getDate(int index, Calendar cal) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getDate(int, Calendar) called");
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   public synchronized Date getDate(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getDate(String) called");
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   public synchronized Date getDate(String name, Calendar cal) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getDate(String, Calendar) called");
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   public synchronized double getDouble(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getDouble(int) called");
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   public synchronized double getDouble(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getDouble(String) called");
          throw getException(CSQL_NOT_SUPPORTED);
   }

   public synchronized float getFloat(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getFloat(int) called");
            throw getException(CSQL_NOT_SUPPORTED);
   }
      
   public synchronized float getFloat(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getFloat(String) called");
           throw getException(CSQL_NOT_SUPPORTED);
   }
       
   public synchronized int getInt(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getInt(int) called");
            throw getException(CSQL_NOT_SUPPORTED);
   }
        
   public synchronized int getInt(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getInt(String) called");
           throw getException(CSQL_NOT_SUPPORTED);  
   }
         
   public synchronized long getLong(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getLong(int) called");
             throw getException(CSQL_NOT_SUPPORTED); 
   }
   
   public synchronized long getLong(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getLong(String) called");
             throw getException(CSQL_NOT_SUPPORTED);  
   }
           
 
   public synchronized Object getObject(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getObject(int) called");
           throw getException(CSQL_NOT_SUPPORTED);
   }
   
   public synchronized Object getObject(int index, Map<String,Class<?>> map) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getObject(int, Map<String,Class<?>>) called");
             throw getException(CSQL_NOT_SUPPORTED);  
   }
   public synchronized Object getObject(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getObject(String) called");
               throw getException(CSQL_NOT_SUPPORTED);
   }
           
   public synchronized Object getObject(String name, Map<String,Class<?>> map) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getObject(String, Map<String,Class<?>>) called");
              throw getException(CSQL_NOT_SUPPORTED); 
   }
           
   public synchronized Ref  getRef(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getRef(int) called");
       throw getException(CSQL_NOT_SUPPORTED);        
   }
           
   public synchronized Ref getRef(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getRef(String) called");
       throw getException(CSQL_NOT_SUPPORTED);
       
   }
           
   public synchronized short getShort(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getShort(int) called");
                throw getException(CSQL_NOT_SUPPORTED);
   }
   
   public synchronized short getShort(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getShort(String) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
             
   public synchronized String getString(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getString(int) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
         
   public synchronized String getString(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getString(String) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
            
   public synchronized Time getTime(int index) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getTime(int) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
   public synchronized Time getTime(int index, Calendar cal) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getTime(int, Calendar) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
 
             
   public synchronized Time getTime(String name) throws SQLException
   {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getTime(String) called");
       throw getException(CSQL_NOT_SUPPORTED);
   }
//This method returns the value of the specified parameter as a Java java.sql.Time.
    public synchronized Time getTime(String name, Calendar cal) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getTime(String, Calendar) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method returns the value of the specified parameter as a Java java.sql.Time.

    public synchronized Timestamp getTimestamp(int index) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getTimeStamp(int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
        

//This method returns the value of the specified parameter as a Java java.sql.Timestamp.

        
    public synchronized Timestamp getTimestamp(int index, Calendar cal) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getTimeStamp(int, Calendar) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
 
//This method returns the value of the specified parameter as a Java java.sql.Timestamp.

    public synchronized Timestamp getTimestamp(String name) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getTimeStamp(String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method returns the value of the specified parameter as a Java java.sql.Timestamp.

    public synchronized Timestamp getTimestamp(String name, Calendar cal) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getTimeStamp(String, Calendar) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method returns the value of the specified parameter as a Java java.sql.Timestamp.

    public synchronized URL getURL(int index) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getURL(int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method returns the value of the specified parameter as a Java java.net.URL.
   
    public synchronized URL getURL(String name) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getURL(String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized Reader getCharacterStream(String name) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getCharacterStream(String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized Reader getCharacterStream(int pos) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getCharacterStream(int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized Reader getNCharacterStream(String name) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getNCharacterStream(String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized Reader getNCharacterStream(int pos) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getNCharacterStream(int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized String getNString(String name) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getNString(String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized String getNString(int pos) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getNString(int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized SQLXML getSQLXML(String name) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getSQLXML(String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized SQLXML getSQLXML(int pos) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getSQLXML(int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized NClob getNClob(String name) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getNClob(String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
    public synchronized NClob getNClob(int pos) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getNClob(int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
    public synchronized RowId getRowId(String name) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getRowId(String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
    public synchronized RowId getRowId(int pos) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::getRowId(int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
//This method returns the value of the specified parameter as a Java java.net.URL.

    public synchronized void registerOutParameter(int index, int sqlType) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::registerOutParameter(int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
//This method registers the specified parameter as an output parameter of the specified SQL type.

    public synchronized void registerOutParameter(int index, int sqlType, int scale) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::registerOutParameter(int, int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method registers the specified parameter as an output parameter of the specified SQL type and scale.

    public synchronized void registerOutParameter(int index, int sqlType, String typeName) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::registerOutParameter(int, int, String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
//This method registers the specified parameter as an output parameter of the specified SQL type.

    public synchronized void registerOutParameter(String name, int sqlType) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::registerOutParameter(String, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method registers the specified parameter as an output parameter of the specified SQL type.
 
    public synchronized void registerOutParameter(String name, int sqlType, int scale) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::registerOutParameter(String, int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method registers the specified parameter as an output parameter of the specified SQL type.

    public synchronized void registerOutParameter(String name, int sqlType, String typeName) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::registerOutParameter(String, int, String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method registers the specified parameter as an output parameter of the specified SQL type.

    public synchronized void setAsciiStream(String name, InputStream stream, int count) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setAsciiStream(String, InputStream, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java ASCII InputStream value.

    public synchronized void setBigDecimal(String name, BigDecimal value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setBigDecimal called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

    //This method sets the specified parameter from the given Java BigDecimal value.

    public synchronized void setBinaryStream(String name, InputStream stream, int count) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setBinaryStream(String, InputStream, count) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java binary InputStream value.

    public synchronized void setBoolean(String name, boolean value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setBoolean called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java boolean value.

    public synchronized void setByte(String name, byte value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setTimeByte called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java byte value.

    public synchronized void setBytes(String name, byte[] value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setBytes called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java byte array value.

    public synchronized void setCharacterStream(String name, Reader reader, int count) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setCharacterStream called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java character Reader value.

    public synchronized void setDate(String name, Date value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setDate(String, Date) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java java.sql.Date value.

    public synchronized void setDate(String name, Date value, Calendar cal) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setDate(String, Date, Calendar) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java java.sql.Date value.

    public synchronized void setDouble(String name, double value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setDouble(String, double) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java double value.
   
    public synchronized void setFloat(String name, float value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setFloat(String, float) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java float value.
 
    public synchronized void setInt(String name, int value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setInt(String, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java int value.

    public synchronized void setLong(String name, long value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setLong(String, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java long value.

    public synchronized void setNull(String name, int sqlType) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setNull(String, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method populates the specified parameter with a SQL NULL value for the specified type.

    public synchronized void setNull(String name, int sqlType, String typeName) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setNull(String, int, String) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method populates the specified parameter with a SQL NULL value for the specified type.

    public synchronized void setObject(String name, Object value, int sqlType, int scale) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setObject(String, Object, int, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java Object value.

    public synchronized void setObject(String name, Object value, int sqlType) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setObject(String, Object, int) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java Object value.

    public synchronized void setObject(String name, Object value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setObject(String, Object) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java Object value.

    public synchronized void setShort(String name, short value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setShort called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java short value.

    public synchronized void setString(String name, String value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setString called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java String value.

    public synchronized void setTime(String name, Time value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setTime(String, Time) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java java.sql.Time value.

    public synchronized void setTime(String name, Time value, Calendar cal) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setTime(String, Time, Calendar) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

    //This method sets the specified parameter from the given Java java.sql.Time value.
    
    public synchronized void setTimestamp(String name, Timestamp value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setTimeStamp(String, TimeStamp) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java java.sql.Timestamp value.

//new 1.6
    public synchronized void setTimestamp(String name, Timestamp value, Calendar cal) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setTimeStamp(String, TimeStamp, Calendar) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setNClob(String parameterName, Reader reader) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setNClob(String, Reader) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setNClob(String parameterName, Reader reader, long length) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setNClob(String, Reader, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setBlob(String parameterName, InputStream inputStream) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setBlob(String, InputStream) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setBlob(String parameterName, InputStream inputStream, long length) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setBlob(String, InputStream, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setClob(String parameterName, Reader reader) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setClob(String, Reader) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setClob(String parameterName, Reader reader, long length) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setClob(String, Reader, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setNCharacterStream(String parameterName, Reader value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setNCharacterStream(String, Reader) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setNCharacterStream(String parameterName, Reader value, long length) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setNCharacterStream(String, Reader, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setCharacterStream(String parameterName, Reader reader) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setCharacterStream(String, Reader) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setCharacterStream(String parameterName, Reader reader, long length) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setCharacterStream(String, Reader, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setBinaryStream(String parameterName, InputStream x) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setBinaryStream(String, InputStream) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setBinaryStream(String parameterName, InputStream x, long length) throws SQLException	
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setBinaryStream(String, InputStream, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setAsciiStream(String parameterName, InputStream x)throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setAsciiStream(String, InputStream) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
      
    public synchronized void setAsciiStream(String parameterName, InputStream x, long length)throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setAsciiStream(String, InputStream, long) called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void  setClob(String parameterName, Clob x) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setClob called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void  setBlob(String parameterName, Blob x) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setBlob called");
        throw getException(CSQL_NOT_SUPPORTED);
    }

    public synchronized void  setSQLXML(String parameterName, SQLXML x) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setSQLXML called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
    public synchronized void  setNClob(String parameterName,NClob x) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setNClob called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void  setNString(String parameterName,String x) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setNString called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void  setRowId(String parameterName,RowId x) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setRowId called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
//is method sets the specified parameter from the given Java java.sql.Timestamp value.

    public synchronized void setURL(String name, URL value) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::setURL called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
//This method sets the value of the specified parameter to the specified java.net.URL
    
    public synchronized boolean	wasNull() throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlCallableStatement::wasNull called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    //This method tests whether the value of the last parameter that was fetched was actually a SQL NULL value. 
}
