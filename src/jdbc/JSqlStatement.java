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

    public native void alloc(int mode);
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
    public native boolean isNull(int pos);
     
    // To retrieve Field values
    public native short getShort( int pos , int type);
    public native int getInt( int pos,int type );
    public native long getLong( int pos,int type );
    public native byte getByte( int pos,int type );  // TINYINT   
    public native float getFloat( int pos, int type );
    public native double getDouble( int pos, int type );
    public native String getString( int pos, int type );
    public native Date getDate( int pos, int type );
    public native Time getTime( int pos, int type );
    public native Timestamp getTimestamp( int pos, int type );
    public native boolean getBoolean( int pos, int type );
   //get value with field name
    public native short getShortS( String fldName );
    public native int getIntS( String fldName  );
    public native long getLongS( String fldName  );
    public native byte getByteS( String fldName  );  // TINYINT   
    public native float getFloatS( String fldName  );
    public native double getDoubleS( String fldName  );
    public native String getStringS( String fldName  );
    public native Date getDateS( String fldName  );
    public native Time getTimeS( String fldName  );
    public native Timestamp getTimestampS( String fldName  );
    public native boolean getBooleanS( String fldName  );

    // ResultSet
    public native int findColumn( String str );
    public native int getNoOfFields();
    public native String getFieldName( int pos );
    public native int[] getProjFldTypeArray();

    // ResultSetMetaData
    public native int getTotalProjFld();
    public native int getProjFldType(int pos);
    public native boolean isFldNullable(int pos);
    public native String getProjFldName(int pos);
    public native String getTableName();
    //ParameterMetaData
    public native String getParamFldName(int param);
    public native int getTotalparam();
    public native int getType(int param);
    public native boolean isNullable(int pos);
    
    //Callable statement.
    public native int executePro();
    public native int preparePro(String statemnt);
    public native long nextSet();
};
