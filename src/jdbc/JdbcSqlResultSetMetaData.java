
package csql.jdbc;

import java.sql.SQLException;
import java.sql.ResultSetMetaData;

/**
 *
 * @author bijaya
 */
public final class JdbcSqlResultSetMetaData
extends JSqlError implements ResultSetMetaData, JSqlErrorType
{
    private boolean isClosed;
    JdbcSqlStatement stmt; // This guy creates me
    private boolean shouldDriverHandles;
    private  FieldInfo[] fieldMeta; 
   
    JdbcSqlResultSetMetaData()
    {
        isClosed = false;
        shouldDriverHandles = false;
    }

    void setStmt( JdbcSqlStatement s )
    {
        stmt = s;
        isClosed = false;
    }

    JdbcSqlResultSetMetaData(FieldInfo[] fields)
    {
        isClosed = false;
        shouldDriverHandles = true;
        fieldMeta = fields;
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
        if (shouldDriverHandles){
            return this.fieldMeta.length;
        }
        return( stmt.jniStmt.getTotalProjFld() );
    }
    
    
    public int getColumnIndex (String name) throws SQLException 
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        if(shouldDriverHandles){
            for ( int i=0; i< this.fieldMeta.length; i++)
            {
                if(fieldMeta[i].getColname().equals(name)) 
                    return (i+1);
            }
        }
        return( stmt.jniStmt.findColumn( name ) );//TO DO
    }

    public String getColumnName (int colNum) throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        if(shouldDriverHandles){
            if(this.fieldMeta.length < colNum) 
                return null;
            else 
                return this.fieldMeta[colNum-1].getColname();
        }
        String name= stmt.jniStmt.getProjFldName(colNum);
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
        if(shouldDriverHandles) {
            return false;
        }
        return( true );
    }
    public boolean isDefinitelyWritable (int colNum) throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        if(shouldDriverHandles) {
            return false;
        }
        return( true );
    }

    
    public String getColumnClassName(int colNum) throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        if(shouldDriverHandles) {
            return Util.getClassName(this.fieldMeta[colNum-1].getCsqlType());
        }
        return Util.getClassName(this.stmt.jniStmt.getProjFldType(colNum));
    }
    
    public int getColumnType (int colNum) throws SQLException 
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        if(shouldDriverHandles) {
            return Util.getType(this.fieldMeta[colNum-1].getCsqlType());
        }
        return Util.getType(this.stmt.jniStmt.getProjFldType(colNum));
    }
    public String getColumnTypeName (int colNum) throws SQLException 
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        if(shouldDriverHandles) {
            return Util.getTypeName(this.fieldMeta[colNum-1].getCsqlType());
        }
        return Util.getTypeName(this.stmt.jniStmt.getProjFldType(colNum));
    }
    public boolean isCaseSensitive (int colNum) throws SQLException 
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        return( false );
    }
    
    public int isNullable (int colNum) throws SQLException 
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        if(shouldDriverHandles) {
            if(this.fieldMeta[colNum-1].isNullable())
                 return JdbcSqlResultSetMetaData.columnNoNulls ;
            else
                 return JdbcSqlResultSetMetaData.columnNullable ;
        }
        
        if (this.stmt.jniStmt.isFldNullable(colNum))
            return JdbcSqlResultSetMetaData.columnNoNulls ;
        else
            return JdbcSqlResultSetMetaData.columnNullable ;
    }
    
    public String getTableName (int colNum) throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        if(shouldDriverHandles){
            return "";
        }
        //TODO
        return( null );
    }
    public boolean isSigned (int colNum) throws SQLException
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        return false;
    }
    public int getPrecision (int colNum) throws SQLException //TODO
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        return 0;
    }
    public int getScale (int colNum) throws SQLException //TODO
    {
        if( isClosed ) throw getException( CSQL_INVALID_STATE );
        return 0;
    }
    public String getSchemaName (int colNum) throws SQLException
    {
        return "";
    }
    

    // UN-SUPPORTED API's
    public int getColumnDisplaySize (int colNum) throws SQLException
    {
        return( 1 );
    }
    //TODO:
    public boolean isAutoIncrement (int colNum) throws SQLException
    {
        return( false );
    }
    public boolean isCurrency (int colNum) throws SQLException
    {
        return( false );
    }
    public String getCatalogName (int colNum) throws SQLException
    {
        return "csql";
    }
    public boolean isSearchable (int colNum) throws SQLException
    {
        if(shouldDriverHandles) return false;
        return( true );
    }
    //java 1.6 methods
    public boolean isWrapperFor(Class ifact) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Class unwrap(Class iface) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }

}
