/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package csql.jdbc;

import java.sql.ParameterMetaData;
import java.sql.SQLException;


/**
 *
 * @author bijaya
 */
public class JdbcSqlParameterMetaData extends JSqlError implements ParameterMetaData , JSqlErrorType
{
    private boolean isClosed;
    JdbcSqlStatement stmt; 
    
    JdbcSqlParameterMetaData()
    {
        isClosed = false ;
    }
    
    public void setStmt(JdbcSqlStatement stmt)
    {
        this.stmt = stmt;
        this.isClosed = false ;
    }
    
    
    
    public String getParameterClassName(int param) throws SQLException
    {
        if(isClosed)
            throw getException( CSQL_INVALID_STATE );
        //String name = this.stmt.jniStmt.getParamFldName(param);
        //int pos =stmt.jniStmt.findColumn(name);
        return Util.getClassName(this.stmt.jniStmt.getType(param));
    }
    public int getParameterCount() throws SQLException
    {
        if(isClosed)
            throw getException( CSQL_INVALID_STATE );
        return (this.stmt.jniStmt.getTotalparam());
    }
     
    public int getParameterMode(int param) throws SQLException
    {
        if(isClosed)
            throw getException( CSQL_INVALID_STATE );
        return parameterModeIn;
    }
    
    public int getParameterType(int param) throws SQLException
    {
        if(isClosed)
            throw getException( CSQL_INVALID_STATE );
        //String name = this.stmt.jniStmt.getParamFldName(param);
        //int pos =stmt.jniStmt.findColumn(name);
        return Util.getType(this.stmt.jniStmt.getType(param));
    }

    public String getParameterTypeName(int param) throws SQLException
    {
        if(isClosed)
            throw getException( CSQL_INVALID_STATE );
        //String name = this.stmt.jniStmt.getParamFldName(param);
        //int pos =stmt.jniStmt.findColumn(name);
        return Util.getTypeName(this.stmt.jniStmt.getType(param));
    }
    
    public int getPrecision(int param) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlParameterMetaData::getPrecision called");
        throw getException( CSQL_NOT_SUPPORTED );
    }
    
    public int getScale(int param) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlParameterMetaData::getScale called");
         throw getException( CSQL_NOT_SUPPORTED );
    }
     
    
    public int isNullable(int param) throws SQLException
    {
        // String name = stmt.jniStmt.getParamFldName(param);
        //int pos =stmt.jniStmt.findColumn(name);
        if(this.stmt.jniStmt.isNullable(param))
            return JdbcSqlParameterMetaData.parameterNoNulls;
        else
            return JdbcSqlParameterMetaData.parameterNullable ;
    }
     
    public boolean isSigned(int param) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlParameterMetaData::isSigned called");
        throw getException( CSQL_NOT_SUPPORTED );
    }
     
    public boolean isWrapperFor(Class ifact) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlParameterMetaData::isWrapperFor called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Class unwrap(Class iface) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("JdbcSqlParameterMetaData::unwrap called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
}
