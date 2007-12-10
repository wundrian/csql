package csql.jdbc;
import java.sql.Time;
import java.sql.Date;
import java.sql.Timestamp;
public class JSqlStatement
{
    public long sqlStmtPtr;

    public long getPtr()
    {
        return sqlStmtPtr;
    }
    public void setPtr( long ptr )
    {
        sqlStmtPtr = ptr;
    }

    // Wrappers Below

    public native void alloc();
    public native void free();
    public native void freeStmt();

    // Operations
    public native void setConnectionPtr(long ptr);
    public native int prepare( String statement );
    public native boolean isSelect();
    public native int execute();
    public native long next(); //returns next tuple
    public native long close(); //close the scan

    // Parameters
    public native void setShort( int pos, short value );
    public native void setInt( int pos, int value );
    public native void setLong( int pos, long value );
    public native void setByte( int pos, byte value );  // TINYINT
    public native void setFloat( int pos, float value );
    public native void setDouble( int pos, double value );
    public native void setString( int pos, String value );
    public native void setDate( int pos, Date d );
    public native void setTime( int pos, Time t );
    public native void setTimestamp( int pos, Timestamp tms );
    public native void setBoolean( int pos, boolean value ); //TODO

    public native void setNull( int pos );

    // To retrieve Field values
    public native short getShort( int pos );
    public native int getInt( int pos );
    public native long getLong( int pos );
    public native byte getByte( int pos );  // TINYINT   
    public native float getFloat( int pos );
    public native double getDouble( int pos );
    public native String getString( int pos );
    public native Date getDate( int pos );
    public native Time getTime( int pos );
    public native Timestamp getTimestamp( int pos );
    public native boolean getBoolean( int pos );

    // ResultSet
    public native int findColumn( String str );
    public native int getNoOfFields();
    public native String getFieldName( int pos );

    // ResultSetMetaData

};
