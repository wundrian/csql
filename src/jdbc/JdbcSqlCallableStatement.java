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
        if(isPrepared) 
	{
            if(isResultSetused) rs.close();
            jniStmt.freeStmt();
            isPrepared = false;
        }
        rv = jniStmt.preparePro(query);
        if( rv != 0 ) // 0 ->OK
        {
            throw getException(CSQL_PREPARE_ERR);
        }
        isPrepared = true;
   }
   public boolean execute() throws SQLException
   {
        if (!isPrepared) throw getException(CSQL_NOT_PREPARED);
        rowsAffect = jniStmt.executePro();
        if( rowsAffect < 0 )
            throw getException(CSQL_EXECUTE_ERR);
        return true;
   }
   
   //JdbcSqlPreparedStatement.executeQuery()
    
   public java.sql.ResultSet executeQuery() throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
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
        throw getException(CSQL_NOT_SUPPORTED);
   }
    
   public synchronized Array getArray(String name) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
    
   public synchronized BigDecimal getBigDecimal(int index, int scale) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
   public synchronized BigDecimal getBigDecimal(int index) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
   public synchronized BigDecimal getBigDecimal(String name) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
    
   public synchronized Blob getBlob(int index) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
   
   public synchronized Blob getBlob(String name) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
  
   public synchronized boolean getBoolean(int index) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
    
   public synchronized boolean getBoolean(String name) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
             
    
   public synchronized byte getByte(int index) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
       
    
   public synchronized byte getByte(String name) throws SQLException
   {
        throw getException(CSQL_NOT_SUPPORTED);
   }
    
   public synchronized byte[] getBytes(int index) throws SQLException
   {
         throw getException(CSQL_NOT_SUPPORTED);
   }
         
     
   public synchronized byte[] getBytes(String name) throws SQLException
   {
         throw getException(CSQL_NOT_SUPPORTED);
   
   }
   
   public synchronized Clob getClob(int index) throws SQLException
   {
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
     
   public synchronized Clob getClob(String name) throws SQLException
   {
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   
   public synchronized Date getDate(int index) throws SQLException
   {
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   public synchronized Date getDate(int index, Calendar cal) throws SQLException
   {
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   public synchronized Date getDate(String name) throws SQLException
   {
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   public synchronized Date getDate(String name, Calendar cal) throws SQLException
   {
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   public synchronized double getDouble(int index) throws SQLException
   {
         throw getException(CSQL_NOT_SUPPORTED);
   }
     
   public synchronized double getDouble(String name) throws SQLException
   {
          throw getException(CSQL_NOT_SUPPORTED);
   }
     
      

   public synchronized float getFloat(int index) throws SQLException
   {
            throw getException(CSQL_NOT_SUPPORTED);
   }
      
   public synchronized float getFloat(String name) throws SQLException
   {
           throw getException(CSQL_NOT_SUPPORTED);
   }
       
   public synchronized int getInt(int index) throws SQLException
   {
            throw getException(CSQL_NOT_SUPPORTED);
   }
        
   public synchronized int getInt(String name) throws SQLException
   {
           throw getException(CSQL_NOT_SUPPORTED);  
   }
         
   public synchronized long getLong(int index) throws SQLException
   {
             throw getException(CSQL_NOT_SUPPORTED); 
   }
   
   public synchronized long getLong(String name) throws SQLException
   {
             throw getException(CSQL_NOT_SUPPORTED);  
   }
           
 
   public synchronized Object getObject(int index) throws SQLException
   {
           throw getException(CSQL_NOT_SUPPORTED);
   }
   
   public synchronized Object getObject(int index, Map<String,Class<?>> map) throws SQLException
   {
             throw getException(CSQL_NOT_SUPPORTED);  
   }
   public synchronized Object getObject(String name) throws SQLException
   {
               throw getException(CSQL_NOT_SUPPORTED);
   }
           
   public synchronized Object getObject(String name, Map<String,Class<?>> map) throws SQLException
   {
              throw getException(CSQL_NOT_SUPPORTED); 
   }
           
   public synchronized Ref  getRef(int index) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);        
   }
           
   public synchronized Ref getRef(String name) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
       
   }
           
   public synchronized short getShort(int index) throws SQLException
   {
                throw getException(CSQL_NOT_SUPPORTED);
   }
   
   public synchronized short getShort(String name) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
 
             
   public synchronized String getString(int index) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
         
   public synchronized String getString(String name) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }

            
   public synchronized Time getTime(int index) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
   
   public synchronized Time getTime(int index, Calendar cal) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
 
             
   public synchronized Time getTime(String name) throws SQLException
   {
       throw getException(CSQL_NOT_SUPPORTED);
   }
//This method returns the value of the specified parameter as a Java java.sql.Time.
    public synchronized Time getTime(String name, Calendar cal) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method returns the value of the specified parameter as a Java java.sql.Time.

    public synchronized Timestamp getTimestamp(int index) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
        

//This method returns the value of the specified parameter as a Java java.sql.Timestamp.

        
    public synchronized Timestamp getTimestamp(int index, Calendar cal) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
 
//This method returns the value of the specified parameter as a Java java.sql.Timestamp.

    public synchronized Timestamp getTimestamp(String name) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method returns the value of the specified parameter as a Java java.sql.Timestamp.

    public synchronized Timestamp getTimestamp(String name, Calendar cal) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method returns the value of the specified parameter as a Java java.sql.Timestamp.

    public synchronized URL getURL(int index) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method returns the value of the specified parameter as a Java java.net.URL.
   
    public synchronized URL getURL(String name) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized Reader getCharacterStream(String name) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized Reader getCharacterStream(int pos) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized Reader getNCharacterStream(String name) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized Reader getNCharacterStream(int pos) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized String getNString(String name) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized String getNString(int pos) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized SQLXML getSQLXML(String name) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized SQLXML getSQLXML(int pos) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized NClob getNClob(String name) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
    public synchronized NClob getNClob(int pos) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
    public synchronized RowId getRowId(String name) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
    public synchronized RowId getRowId(int pos) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
//This method returns the value of the specified parameter as a Java java.net.URL.

    public synchronized void registerOutParameter(int index, int sqlType) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
//This method registers the specified parameter as an output parameter of the specified SQL type.

    public synchronized void registerOutParameter(int index, int sqlType, int scale) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method registers the specified parameter as an output parameter of the specified SQL type and scale.

    public synchronized void registerOutParameter(int index, int sqlType, String typeName) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
//This method registers the specified parameter as an output parameter of the specified SQL type.

    public synchronized void registerOutParameter(String name, int sqlType) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method registers the specified parameter as an output parameter of the specified SQL type.
 
    public synchronized void registerOutParameter(String name, int sqlType, int scale) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method registers the specified parameter as an output parameter of the specified SQL type.

    public synchronized void registerOutParameter(String name, int sqlType, String typeName) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method registers the specified parameter as an output parameter of the specified SQL type.

    public synchronized void setAsciiStream(String name, InputStream stream, int count) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java ASCII InputStream value.

    public synchronized void setBigDecimal(String name, BigDecimal value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

    //This method sets the specified parameter from the given Java BigDecimal value.

    public synchronized void setBinaryStream(String name, InputStream stream, int count) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java binary InputStream value.

    public synchronized void setBoolean(String name, boolean value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java boolean value.

    public synchronized void setByte(String name, byte value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java byte value.

    public synchronized void setBytes(String name, byte[] value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java byte array value.

    public synchronized void setCharacterStream(String name, Reader reader, int count) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java character Reader value.

    public synchronized void setDate(String name, Date value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java java.sql.Date value.

    public synchronized void setDate(String name, Date value, Calendar cal) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java java.sql.Date value.

    public synchronized void setDouble(String name, double value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java double value.
   
    public synchronized void setFloat(String name, float value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java float value.
 
    public synchronized void setInt(String name, int value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java int value.

    public synchronized void setLong(String name, long value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java long value.

    public synchronized void setNull(String name, int sqlType) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method populates the specified parameter with a SQL NULL value for the specified type.

    public synchronized void setNull(String name, int sqlType, String typeName) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method populates the specified parameter with a SQL NULL value for the specified type.

    public synchronized void setObject(String name, Object value, int sqlType, int scale) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java Object value.

    public synchronized void setObject(String name, Object value, int sqlType) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java Object value.

    public synchronized void setObject(String name, Object value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java Object value.

    public synchronized void setShort(String name, short value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java short value.

    public synchronized void setString(String name, String value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java String value.

    public synchronized void setTime(String name, Time value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java java.sql.Time value.

    public synchronized void setTime(String name, Time value, Calendar cal) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

    //This method sets the specified parameter from the given Java java.sql.Time value.
    
    public synchronized void setTimestamp(String name, Timestamp value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

//This method sets the specified parameter from the given Java java.sql.Timestamp value.

//new 1.6
    public synchronized void setTimestamp(String name, Timestamp value, Calendar cal) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setNClob(String parameterName, Reader reader) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setNClob(String parameterName, Reader reader, long length) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setBlob(String parameterName, InputStream inputStream) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setBlob(String parameterName, InputStream inputStream, long length) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setClob(String parameterName, Reader reader) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setClob(String parameterName, Reader reader, long length) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setNCharacterStream(String parameterName, Reader value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setNCharacterStream(String parameterName, Reader value, long length) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setCharacterStream(String parameterName, Reader reader) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setCharacterStream(String parameterName, Reader reader, long length) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setBinaryStream(String parameterName, InputStream x) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setBinaryStream(String parameterName, InputStream x, long length) throws SQLException	
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void setAsciiStream(String parameterName, InputStream x)throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
      
    public synchronized void setAsciiStream(String parameterName, InputStream x, long length)throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void  setClob(String parameterName, Clob x) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void  setBlob(String parameterName, Blob x) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void  setSQLXML(String parameterName, SQLXML x) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
    public synchronized void  setNClob(String parameterName,NClob x) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void  setNString(String parameterName,String x) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public synchronized void  setRowId(String parameterName,RowId x) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    
//is method sets the specified parameter from the given Java java.sql.Timestamp value.

    public synchronized void setURL(String name, URL value) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
//This method sets the value of the specified parameter to the specified java.net.URL
    
    public synchronized boolean	wasNull() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    //This method tests whether the value of the last parameter that was fetched was actually a SQL NULL value. 
             
             
             
             
             
             
             
             
             
             
             
             
}
