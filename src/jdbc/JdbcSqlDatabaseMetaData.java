/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package csql.jdbc;

import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.ResultSet;
import java.sql.RowIdLifetime;
import java.sql.SQLException;
import java.util.ArrayList;

/**
 *
 * @author bijaya
 */
public class JdbcSqlDatabaseMetaData extends JSqlError implements  DatabaseMetaData, JSqlErrorType 
{
    
    private boolean isClosed;
    private JdbcSqlConnection conn;
    private JdbcSqlStatement stmt;
    JdbcSqlDatabaseMetaData(JdbcSqlConnection con)
    {
        this.conn = con;
        stmt = new JdbcSqlStatement(con);
        isClosed=false;
    }
    
    
    public boolean allProceduresAreCallable() throws SQLException
    {
        if(this.isClosed) 
            throw getException( CSQL_INVALID_STATE );
        return false;
    }

    public boolean allTablesAreSelectable() throws SQLException
    {
        if(this.isClosed)
            throw getException(CSQL_INVALID_STATE );
        return true;
    }

    public boolean autoCommitFailureClosesAllResultSets() throws SQLException
    {
        if(this.isClosed)
            throw getException( CSQL_INVALID_STATE );
        return false;
    }

    public boolean dataDefinitionCausesTransactionCommit() throws SQLException
    {
        if(this.isClosed)
            throw getException( CSQL_INVALID_STATE );
        return false;
    }

    public boolean dataDefinitionIgnoredInTransactions() throws SQLException
    {
        if(this.isClosed)
            throw getException( CSQL_INVALID_STATE );
        return false;
    }

    public boolean deletesAreDetected(int type) throws SQLException
    {
        if(this.isClosed)
            throw getException( CSQL_INVALID_STATE );
        return false;
    }
    public boolean doesMaxRowSizeIncludeBlobs() throws SQLException
    {
        return false;
    }

    public ResultSet getAttributes(String catalog,String schemaPattern,String typeNamePattern,String attributeNamePattern) throws SQLException
    {
         if(isClosed) throw getException(CSQL_INVALID_STATE);
         FieldInfo[] fields = new FieldInfo[21];
	 fields[0] = new FieldInfo("", "TYPE_CAT", 30, 32,false);
	 fields[1] = new FieldInfo("", "TYPE_SCHEM", 30, 32,false);
	 fields[2] = new FieldInfo("", "TYPE_NAME", 30, 32,true);
	 fields[3] = new FieldInfo("", "ATTR_NAME", 30, 32,true);
	 fields[4] = new FieldInfo("", "DATA_TYPE", 3, 32,true);
	 fields[5] = new FieldInfo("", "ATTR_TYPE_NAME", 30, 32,true);
	 fields[6] = new FieldInfo("", "ATTR_SIZE", 0, 32,true);
	 fields[7] = new FieldInfo("", "DECIMAL_DIGITS", 0, 32,true);
	 fields[8] = new FieldInfo("", "NUM_PREC_RADIX", 0, 32,true);
	 fields[9] = new FieldInfo("", "NULLABLE ", 0, 32,true);
	 fields[10] = new FieldInfo("", "REMARKS", 30, 32,true);
	 fields[11] = new FieldInfo("", "ATTR_DEF", 30, 32,true);
	 fields[12] = new FieldInfo("", "SQL_DATA_TYPE", 0, 32,true);
	 fields[13] = new FieldInfo("", "SQL_DATETIME_SUB", 0, 32,true);
	 fields[14] = new FieldInfo("", "CHAR_OCTET_LENGTH", 0, 32,true);
	 fields[15] = new FieldInfo("", "ORDINAL_POSITION", 0, 32,true);
	 fields[16] = new FieldInfo("", "IS_NULLABLE", 30, 32, true);
	 fields[17] = new FieldInfo("", "SCOPE_CATALOG", 30, 32, true);
	 fields[18] = new FieldInfo("", "SCOPE_SCHEMA", 30, 32, true);
	 fields[19] = new FieldInfo("", "SCOPE_TABLE", 30, 32, true);
	 fields[20] = new FieldInfo("", "SOURCE_DATA_TYPE", 3, 32,true);
         ResultSet rs = new JdbcSqlResultSet(fields, null);
         if(rs==null){ throw getException(CSQL_INVALID_STATE);}
         return rs;
    }
    
    public ResultSet getBestRowIdentifier(String catalog, String schema,String table,int scope, boolean nullable) throws SQLException
    {
        //TODO: Check with other database
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[8];
	fields[0] = new FieldInfo("", "SCOPE", 3, 5, true);
	fields[1] = new FieldInfo("", "COLUMN_NAME", 30, 32, true);
	fields[2] = new FieldInfo("", "DATA_TYPE", 3, 32, true);
	fields[3] = new FieldInfo("", "TYPE_NAME", 30, 32, true);
	fields[4] = new FieldInfo("", "COLUMN_SIZE", 0, 10, true);
	fields[5] = new FieldInfo("", "BUFFER_LENGTH", 0, 10, true);
	fields[6] = new FieldInfo("", "DECIMAL_DIGITS", 0, 10, true);
	fields[7] = new FieldInfo("", "PSEUDO_COLUMN", 3, 5, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public String getCatalogSeparator() throws SQLException
    {
        return ".";
    }
    
    public String getCatalogTerm() throws SQLException
    {
        return "database";
    }
      

    public ResultSet getCatalogs() throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        if(stmt!=null) stmt.close();
        ResultSet rs = stmt.executeQuery("getCatalogs");
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }
    
    public ResultSet getClientInfoProperties() throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[4];
	fields[0] = new FieldInfo("", "NAME", 30, 64, true);
	fields[1] = new FieldInfo("", "MAX_LEN", 0, 4, true);
	fields[2] = new FieldInfo("", "DEFAULT_VALUE", 30, 64, true);
	fields[3] = new FieldInfo("", "DESCRIPTION", 30, 64, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;        
    }

      
    public ResultSet getColumnPrivileges(String catalog, String schema, String table, String columnNamePattern) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[8];
	fields[0] = new FieldInfo("", "TABLE_CAT", 30, 64, false);
	fields[1] = new FieldInfo("", "TABLE_SCHEM", 30, 64, false);
	fields[2] = new FieldInfo("", "TABLE_NAME", 30, 64, true);
	fields[3] = new FieldInfo("", "COLUMN_NAME", 30, 64, true);
	fields[4] = new FieldInfo("", "GRANTOR", 30, 77, true);
	fields[5] = new FieldInfo("", "GRANTEE", 30, 77, true);
	fields[6] = new FieldInfo("", "PRIVILEGE", 30, 64, true);
	fields[7] = new FieldInfo("", "IS_GRANTABLE", 30, 3, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;        
    }

    public ResultSet getColumns(String catalog, String schemaPattern, String tableNamePattern, String columnNamePattern) throws SQLException
    {
          if(isClosed) throw getException(CSQL_INVALID_STATE);
          //conn.setAutoCommit(false);
          //Statement stmt = conn.createStatement();   
          if(stmt!=null) stmt.close();  
          ResultSet rs = stmt.executeQuery("describe "+ tableNamePattern);
          if(rs==null){ throw getException(CSQL_INVALID_STATE);}
          return rs;
    }

    public Connection getConnection() throws SQLException
    {
         if(this.isClosed)
            throw getException( CSQL_INVALID_STATE );
         return this.conn;
    }
    
    public ResultSet getCrossReference(String parentCatalog, String parentSchema, String parentTable, String foreignCatalog,     String foreignSchema,    String foreignTable) throws SQLException
    {
        //TODO
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[14];
	fields[0] = new FieldInfo("", "PKTABLE_CAT", 30, 255, false);
	fields[1] = new FieldInfo("", "PKTABLE_SCHEM", 30, 0,false);
	fields[2] = new FieldInfo("", "PKTABLE_NAME", 30, 255, true);
	fields[3] = new FieldInfo("", "PKCOLUMN_NAME", 30, 32, true);
	fields[4] = new FieldInfo("", "FKTABLE_CAT", 30, 255, true);
	fields[5] = new FieldInfo("", "FKTABLE_SCHEM", 30, 0, true);
	fields[6] = new FieldInfo("", "FKTABLE_NAME", 30, 255, true);
	fields[7] = new FieldInfo("", "FKCOLUMN_NAME", 30, 32, true);
	fields[8] = new FieldInfo("", "KEY_SEQ", 3, 2, true);
	fields[9] = new FieldInfo("", "UPDATE_RULE", 3, 2, true);
	fields[10] = new FieldInfo("", "DELETE_RULE", 3, 2, true);
	fields[11] = new FieldInfo("", "FK_NAME", 30, 0, true);
	fields[12] = new FieldInfo("", "PK_NAME", 30, 0, true);
	fields[13] = new FieldInfo("", "DEFERRABILITY", 0, 2, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public int getDatabaseMajorVersion() throws SQLException
    {
        return 2;
    }

    public int getDatabaseMinorVersion() throws SQLException
    {
        return 6;
    }

    public String getDatabaseProductName() throws SQLException
    {
         return "CSQL";
    }

    public String getDatabaseProductVersion() throws SQLException
    {
        return "csql.src.2.6Beta";
    }

    public int getDefaultTransactionIsolation() throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        return java.sql.Connection.TRANSACTION_READ_COMMITTED;
    }
    
    public int getDriverMajorVersion() 
    {
        return 2;
    }
      
    public int getDriverMinorVersion()
    {
        return 6;
    }
     
    public String getDriverName() throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        return "csql.jdbc.JdbcSqlDriver";
    }

    public String getDriverVersion() throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        return "CSQL JDBC 2.6";
    }

    public ResultSet getExportedKeys(String catalog, String schema, String table) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        if(stmt!=null) stmt.close();
        ResultSet rs = stmt.executeQuery("ExportedKey "+ table);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public String getExtraNameCharacters() throws SQLException
    {
        return "";
    }

    public ResultSet getFunctionColumns(String catalog, String schemaPattern, String functionNamePattern, String columnNamePattern) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = {
    			new FieldInfo("", "FUNCTION_CAT", 30, 64, false),
    			new FieldInfo("", "FUNCTION_SCHEM", 30, 64,false),
    			new FieldInfo("", "FUNCTION_NAME", 30, 64, true),
    			new FieldInfo("", "COLUMN_NAME", 30, 64, true),
    			new FieldInfo("", "COLUMN_TYPE", 30, 64, true),
    			new FieldInfo("", "DATA_TYPE", 3, 4, true),
    			new FieldInfo("", "TYPE_NAME", 30, 64, true),
    			new FieldInfo("", "PRECISION", 3, 4, true),
    			new FieldInfo("", "LENGTH", 3, 4, true),
    			new FieldInfo("", "SCALE", 3, 4, true),
    			new FieldInfo("", "RADIX", 3, 4, true),
    			new FieldInfo("", "NULLABLE", 3, 4, true),
    			new FieldInfo("", "REMARKS", 30, 64, true),
    			new FieldInfo("", "CHAR_OCTET_LENGTH", 3, 64, true),
    			new FieldInfo("", "ORDINAL_POSITION", 3, 64, true),
    			new FieldInfo("", "IS_NULLABLE", 30, 3, true),
    			new FieldInfo("", "SPECIFIC_NAME", 30, 64, true)};
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public ResultSet getFunctions(String catalog, String schemaPattern, String functionNamePattern) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[6];
	fields[0] = new FieldInfo("", "FUNCTION_CAT", 30, 64, false);
	fields[1] = new FieldInfo("", "FUNCTION_SCHEM", 30, 64,false);
	fields[2] = new FieldInfo("", "FUNCTION_NAME", 30, 64, true);
	fields[3] = new FieldInfo("", "REMARKS", 30, 32, true);
	fields[4] = new FieldInfo("", "FUNCTION_TYPE", 3, 4, true);
	fields[5] = new FieldInfo("", "SPECIFIC_NAME", 30, 64, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public String getIdentifierQuoteString() throws SQLException
    {
        return "`";
    }

    public ResultSet getImportedKeys(String catalog, String schema, String table) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        if(stmt!=null) stmt.close();
        ResultSet rs = stmt.executeQuery("ImportedKey "+ table);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public ResultSet getIndexInfo(String catalog, String schema, String table,boolean unique, boolean approximate) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        if(stmt!=null) stmt.close();
        ResultSet rs = stmt.executeQuery("describe index "+ table);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public int getJDBCMajorVersion() throws SQLException
    {
        return 3;
    }

    public int getJDBCMinorVersion() throws SQLException
    {
        return 0;
    }

    public int getMaxBinaryLiteralLength() throws SQLException
    {
         return 0;
    }

    public int getMaxCatalogNameLength() throws SQLException
    {
        return 64;
    }

    public int getMaxCharLiteralLength() throws SQLException
    {
         return 0;
    }

      
    public int getMaxColumnNameLength() throws SQLException
    {
        return 64;
    }

    public int getMaxColumnsInGroupBy() throws SQLException
    {
        return 64;
    }

    public int getMaxColumnsInIndex() throws SQLException
    {
        return 16;
    }

    public int getMaxColumnsInOrderBy() throws SQLException
    {
        return 64;
    }
 
 
    public int getMaxColumnsInSelect() throws SQLException
    {
        return 256;
    }

 
    public int getMaxColumnsInTable() throws SQLException
    {
        return 256;
    }

    public int getMaxConnections() throws SQLException
    {
        return 100;
    }

    public int getMaxCursorNameLength() throws SQLException
    {
        return 64;
    }

    public int getMaxIndexLength() throws SQLException
    {
        return 0;
    }

    public int getMaxProcedureNameLength() throws SQLException
    {
       return 64;
    }
 
    public int getMaxRowSize() throws SQLException
    {
       return 2147483639;
    }

    public int getMaxSchemaNameLength() throws SQLException
    {
        return 64;
    }

    public int getMaxStatementLength() throws SQLException
    {
        return 2048;
    }

    public int getMaxStatements() throws SQLException
    {
        return 100;
    }

    public int getMaxTableNameLength() throws SQLException
    {
        return 64;
    }

    public int getMaxTablesInSelect() throws SQLException
    {
        return 32;
    }

    public int getMaxUserNameLength() throws SQLException
    {
        return 64;
    }

    public String getNumericFunctions() throws SQLException
    {
        return "";
    }
    
    public ResultSet getPrimaryKeys(String catalog,    String schema,    String table) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        if(stmt!=null) stmt.close();
        ResultSet rs = stmt.executeQuery("getprimarykey  "+ table);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

     
    public ResultSet getProcedureColumns(String catalog, String schemaPattern, String procedureNamePattern, String columnNamePattern) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[13];
	fields[0] = new FieldInfo("", "PROCEDURE_CAT", 30, 10, false);
	fields[1] = new FieldInfo("", "PROCEDURE_SCHEM", 30, 10, false);
	fields[2] = new FieldInfo("", "PROCEDURE_NAME", 30, 10, true);
	fields[3] = new FieldInfo("", "COLUMN_NAME", 30, 10, true);
	fields[4] = new FieldInfo("", "COLUMN_TYPE", 30, 10, true);
	fields[5] = new FieldInfo("", "DATA_TYPE", 3, 4, true);
	fields[6] = new FieldInfo("", "TYPE_NAME", 30, 10, true);
	fields[7] = new FieldInfo("", "PRECISION", 0, 4, true);
	fields[8] = new FieldInfo("", "LENGTH", 0, 4, true);
	fields[9] = new FieldInfo("", "SCALE", 3, 4, true);
	fields[10] = new FieldInfo("", "RADIX", 3, 4, true);
	fields[11] = new FieldInfo("", "NULLABLE", 3, 4, true);
	fields[12] = new FieldInfo("", "REMARKS", 30, 10, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public String getProcedureTerm() throws SQLException
    {
        return "";
    }

    public ResultSet getProcedures(String catalog,  String schemaPattern,  String procedureNamePattern) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[9];
	fields[0] = new FieldInfo("", "PROCEDURE_CAT", 30, 255,false);
	fields[1] = new FieldInfo("", "PROCEDURE_SCHEM", 30, 255, false);
	fields[2] = new FieldInfo("", "PROCEDURE_NAME", 30, 255, true);
	fields[3] = new FieldInfo("", "reserved1", 30, 0, true);
	fields[4] = new FieldInfo("", "reserved2", 30, 0, true);
	fields[5] = new FieldInfo("", "reserved3", 30, 0, true);
	fields[6] = new FieldInfo("", "REMARKS", 30, 255, true);
	fields[7] = new FieldInfo("", "PROCEDURE_TYPE", 3, 6, true);
	fields[8] = new FieldInfo("", "SPECIFIC_NAME", 30, 255, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
   }

    public int getResultSetHoldability() throws SQLException
    {
        return ResultSet.HOLD_CURSORS_OVER_COMMIT;
    }

     
    public RowIdLifetime getRowIdLifetime() throws SQLException
    {
        return RowIdLifetime.ROWID_UNSUPPORTED;
    }

    public String getSQLKeywords() throws SQLException
    {
        return "SELECT, FROM, AS, WHERE, BETWEEN, IN, AND, OR, NOT, INSERT, INTO, VALUES, DELETE, UPDATE, SET, NULL, CREATE, DROP, TABLE, PRIMARY, INDEX, ON, HASH, TREE, UNIQUE, KEY, DEFAULT, INT, INTEGER, LONG, DOUBLE, REAL, SHORT, SMALLINT, DATE, TIME, TIMESTAMP, BINARY, CHAR, BIGINT, TINYINT, FLOAT, MIN, MAX, SUM, AVG, COUNT, GROUP, ORDER, ASC, DESC, DISTINCT, BY, HAVING, LIMIT, OFFSET, INNER, OUTER, CROSS, LEFT, JOIN, GETALLTABLES, DESCRIBE, GETPRIMARYKEY, AUTO_INCREMENT, SIZE, FOREIGN, REFERENCES, CACHE, UNCACHE, CONDITION, FIELDLIST, PK, DIRECT, DSN, NOSCHEMA, COMPACT, IS, EXPLAIN, PLAN, GETCATALOGS, GETSCHEMAS";
    }

    public int getSQLStateType() throws SQLException
    {
        return 2;
    }

    public String getSchemaTerm() throws SQLException
    {
        return "";
    }

    
    public ResultSet getSchemas() throws SQLException
    { 
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[2];
	fields[0] = new FieldInfo("", "TABLE_SCHEM", 30, 64,true);
	fields[1] = new FieldInfo("", "TABLE_CATALOG", 30, 64, false);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

     
    public ResultSet getSchemas(String catalog,    String schemaPattern) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[2];
	fields[0] = new FieldInfo("", "TABLE_SCHEM", 30, 64,true);
	fields[1] = new FieldInfo("", "TABLE_CATALOG", 30, 64, false);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public String getSearchStringEscape() throws SQLException
    {
       return "";
    }

    public String getStringFunctions() throws SQLException
    {
        return "";
    }

     
    public ResultSet getSuperTables(String catalog,    String schemaPattern,    String tableNamePattern) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[4];
	fields[0] = new FieldInfo("", "TABLE_CAT", 30, 32, false);
	fields[1] = new FieldInfo("", "TABLE_SCHEM", 30, 32,false);
	fields[2] = new FieldInfo("", "TABLE_NAME", 30, 32, true);
	fields[3] = new FieldInfo("", "SUPERTABLE_NAME", 30, 32, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;

    }

    public ResultSet getSuperTypes(String catalog,    String schemaPattern,    String typeNamePattern) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[6];
	fields[0] = new FieldInfo("", "TABLE_CAT", 30, 32, false);
	fields[1] = new FieldInfo("", "TABLE_SCHEM", 30, 32,false);
	fields[2] = new FieldInfo("", "TYPE_NAME", 30, 32, true);
	fields[3] = new FieldInfo("", "SUPERTYPE_CAT", 30, 32, true);
	fields[4] = new FieldInfo("", "SUPERTYPE_SCHEM", 30, 32, true);
	fields[5] = new FieldInfo("", "SUPERTYPE_NAME", 30, 32, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public String getSystemFunctions() throws SQLException
    {
         return "";
    }

    public ResultSet getTablePrivileges(String catalog,    String schemaPattern,    String tableNamePattern) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[7];
        fields[0] = new FieldInfo("", "TABLE_CAT", 30, 64,false);
	fields[1] = new FieldInfo("", "TABLE_SCHEM", 30, 1,false);
	fields[2] = new FieldInfo("", "TABLE_NAME", 30, 64, true);
	fields[3] = new FieldInfo("", "GRANTOR", 30, 77, false);
	fields[4] = new FieldInfo("", "GRANTEE", 30, 77, true);
	fields[5] = new FieldInfo("", "PRIVILEGE", 30, 64, true);
	fields[6] = new FieldInfo("", "IS_GRANTABLE", 30, 3, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public ResultSet getTableTypes() throws SQLException
    {
        //TODO: NAtive call
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        if(stmt!=null) stmt.close();
        ResultSet rs = stmt.executeQuery("GetTableTypes");
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public ResultSet getTables(String catalog,    String schemaPattern,    String tableNamePattern,    String[] types) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
     //conn.setAutoCommit(false);
     //Statement stmt = conn.createStatement();     
        if(stmt != null) stmt.close();  
        ResultSet rs = stmt.executeQuery("GetAllTables");
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

    public String getTimeDateFunctions() throws SQLException
    {
        return "";
    }

    public ResultSet getTypeInfo() throws SQLException
    {   
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        if(stmt!=null) stmt.close();
        ResultSet rs = stmt.executeQuery("GetDataTypes");
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;

    }


    public ResultSet getUDTs(String catalog,    String schemaPattern,    String typeNamePattern,    int[] types) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[6];
	fields[0] = new FieldInfo("", "TYPE_CAT", 30, 32, false);
	fields[1] = new FieldInfo("", "TYPE_SCHEM", 30, 32,false);
	fields[2] = new FieldInfo("", "TYPE_NAME", 30, 32, true);
	fields[3] = new FieldInfo("", "CLASS_NAME", 30, 32, true);
	fields[4] = new FieldInfo("", "DATA_TYPE", 30, 32, true);
        fields[5] = new FieldInfo("", "REMARKS", 30, 32, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }


    public String getURL() throws SQLException
    {
        return conn.getUrl();
    }

    public String getUserName() throws SQLException
    {
        return "root";
    }

    public ResultSet getVersionColumns(String catalog,    String schema,    String table) throws SQLException
    {
        if(isClosed) throw getException(CSQL_INVALID_STATE);
        FieldInfo[] fields = new FieldInfo[8];
	fields[0] = new FieldInfo("", "SCOPE",3, 5,false);
	fields[1] = new FieldInfo("", "COLUMN_NAME", 30, 32, true);
	fields[2] = new FieldInfo("", "DATA_TYPE", 3, 5, true);
	fields[3] = new FieldInfo("", "TYPE_NAME", 30, 16, true);
	fields[4] = new FieldInfo("", "COLUMN_SIZE", 30, 16, true);
	fields[5] = new FieldInfo("", "BUFFER_LENGTH", 30, 16, true);
	fields[6] = new FieldInfo("", "DECIMAL_DIGITS", 30, 16,false);
	fields[7] = new FieldInfo("", "PSEUDO_COLUMN", 3, 5, true);
        ResultSet rs = new JdbcSqlResultSet(fields, null);
        if(rs==null){ throw getException(CSQL_INVALID_STATE);}
        return rs;
    }

     
    public boolean insertsAreDetected(int type) throws SQLException
    {
        return false;
    }

    public boolean isCatalogAtStart() throws SQLException
    {
        return false;
    }


    public boolean isReadOnly() throws SQLException
    {
        return true;
    }

    public boolean locatorsUpdateCopy() throws SQLException
    {
        return false;
    }

    public boolean nullPlusNonNullIsNull() throws SQLException
    {
        return false;
    }

  
    public boolean nullsAreSortedAtEnd() throws SQLException
    {
        return false;
    }

    public boolean nullsAreSortedAtStart() throws SQLException
    {
        return true;
    }

    public boolean nullsAreSortedHigh() throws SQLException
    {
        return true;
    }

    public boolean nullsAreSortedLow() throws SQLException
    {
        return true;
    }

    public boolean othersDeletesAreVisible(int type) throws SQLException
    {
        return false;
    }

    public boolean othersInsertsAreVisible(int type) throws SQLException
    {
        return false;
    }

    public boolean othersUpdatesAreVisible(int type) throws SQLException
    {
        return false;
    }

    public boolean ownDeletesAreVisible(int type) throws SQLException
    {
        return true;
    }

  
    public boolean ownInsertsAreVisible(int type) throws SQLException
    {
        return true;
    }

    public boolean ownUpdatesAreVisible(int type) throws SQLException
    {
        return true;
    }

  
    public boolean storesLowerCaseIdentifiers() throws SQLException
    {
        return true;
    }

    public boolean storesLowerCaseQuotedIdentifiers() throws SQLException
    {
        return false;
    }

    public boolean storesMixedCaseIdentifiers() throws SQLException
    {
        return true;
    }

    public boolean storesMixedCaseQuotedIdentifiers() throws SQLException
    {
        return false;
    }

    public boolean storesUpperCaseIdentifiers() throws SQLException
    {
        return true;
    }

    public boolean storesUpperCaseQuotedIdentifiers() throws SQLException
    {
        return true;
    }

    
    public boolean supportsANSI92EntryLevelSQL() throws SQLException
    {
        return true;
    }

    public boolean supportsANSI92FullSQL() throws SQLException
    {
        return false;
    }

    public boolean supportsANSI92IntermediateSQL() throws SQLException
    {
        return true;
    }

  
    public boolean supportsAlterTableWithAddColumn() throws SQLException
    {
        return false;
    }

    public boolean supportsAlterTableWithDropColumn() throws SQLException
    {
        return false;
    }

    public boolean supportsBatchUpdates() throws SQLException
    {
        return false;
    }

    public boolean supportsCatalogsInDataManipulation() throws SQLException
    {
        return false;
    }

    public boolean supportsCatalogsInIndexDefinitions() throws SQLException
    {
        return false;
    }
   
    public boolean supportsCatalogsInPrivilegeDefinitions() throws SQLException
    {
        return false;
    }

  
    public boolean supportsCatalogsInProcedureCalls() throws SQLException
    {
        return false;
    }

    public boolean supportsCatalogsInTableDefinitions() throws SQLException
    {
        return false;
    }

    public boolean supportsColumnAliasing() throws SQLException
    {
        return true;
    }

    public boolean supportsConvert() throws SQLException
    {
        return false;
    }

    public boolean supportsConvert(int fromType,int toType) throws SQLException
    {
        return false;
    }

    public boolean supportsCoreSQLGrammar() throws SQLException
    {
        return true;
    }

    public boolean supportsCorrelatedSubqueries() throws SQLException
    {
        return false;
    }

    public boolean supportsDataDefinitionAndDataManipulationTransactions() throws SQLException
    {
        return false;
    }

    public boolean supportsDataManipulationTransactionsOnly() throws SQLException
    {
        return true;
    }

    public boolean supportsDifferentTableCorrelationNames() throws SQLException
    {
        return false;
    }

    public boolean supportsExpressionsInOrderBy() throws SQLException
    {
        return false;
    }

    public boolean supportsExtendedSQLGrammar() throws SQLException
    {
        return false;
    }

    public boolean supportsFullOuterJoins() throws SQLException
    {
        return false;
    }

    public boolean supportsGetGeneratedKeys() throws SQLException
    {
        return true;
    }

    public boolean supportsGroupBy() throws SQLException
    {
        return true;
    }

    public boolean supportsGroupByBeyondSelect() throws SQLException
    {
        return true;
    }

    public boolean supportsGroupByUnrelated() throws SQLException
    {
        return false;
    }

    public boolean supportsIntegrityEnhancementFacility() throws SQLException
    {
        //TODO: Check for other database 
        return false;
    }

    public boolean supportsLikeEscapeClause() throws SQLException
    {
        return true;
    }

    public boolean supportsLimitedOuterJoins() throws SQLException
    {
        return false;
    }

    public boolean supportsMinimumSQLGrammar() throws SQLException
    {
        return true;
    }

    public boolean supportsMixedCaseIdentifiers() throws SQLException
    {
        return true;
    }

    public boolean supportsMixedCaseQuotedIdentifiers() throws SQLException
    {
        return true;
    }

    public boolean supportsMultipleOpenResults() throws SQLException
    {
        return true;
    }

    public boolean supportsMultipleResultSets() throws SQLException
    {
        return true;
    }

    public boolean supportsMultipleTransactions() throws SQLException
    {
        return false;
    }

    public boolean supportsNamedParameters() throws SQLException
    {
        return false;
    }

    public boolean supportsNonNullableColumns() throws SQLException
    {
        return true;
    }

    public boolean supportsOpenCursorsAcrossCommit() throws SQLException
    {
          return true;
    }

     
    public boolean supportsOpenCursorsAcrossRollback() throws SQLException
    {
        return true;
    }

    public boolean supportsOpenStatementsAcrossCommit() throws SQLException
    {
        return true;
    }

    public boolean supportsOpenStatementsAcrossRollback() throws SQLException
    {
        return true;
    }

    public boolean supportsOrderByUnrelated() throws SQLException
    {
        return false;
    }

    public boolean supportsOuterJoins() throws SQLException
    {
        return true;
    }

    public boolean supportsPositionedDelete() throws SQLException
    {
        return false;
    }

    public boolean supportsPositionedUpdate() throws SQLException
    {
        return false;
    }

    public boolean supportsResultSetConcurrency(int type,    int concurrency) throws SQLException
    {
        return false;
    }
    public boolean supportsResultSetHoldability(int holdability) throws SQLException
    {
        return false;
    }

    public boolean supportsResultSetType(int type) throws SQLException
    {
        return (type == ResultSet.TYPE_FORWARD_ONLY);
    }

    public boolean supportsSavepoints() throws SQLException
    {
        return false;
    }

    public boolean supportsSchemasInDataManipulation() throws SQLException
    {
        return false;
    }

    public boolean supportsSchemasInIndexDefinitions() throws SQLException
    {
        return false;
    }

    public boolean supportsSchemasInPrivilegeDefinitions() throws SQLException
    {
        return false;
    }

    public boolean supportsSchemasInProcedureCalls() throws SQLException
    {
        return false;
    }

    public boolean supportsSchemasInTableDefinitions() throws SQLException
    {
        return false;
    }

    public boolean supportsSelectForUpdate() throws SQLException
    {
        return false;
    }

    public boolean supportsStatementPooling() throws SQLException
    {
        return false;
    }
     
    public boolean supportsStoredFunctionsUsingCallSyntax() throws SQLException
    {
        return false;
    }

    public boolean supportsStoredProcedures() throws SQLException
    {
        return false;
    }

    public boolean supportsSubqueriesInComparisons() throws SQLException
    {
        return false;
    }

    public boolean supportsSubqueriesInExists() throws SQLException
    {
        return false;
    }

    public boolean supportsSubqueriesInIns() throws SQLException
    {
        return false;
    }

    public boolean supportsSubqueriesInQuantifieds() throws SQLException
    {
        return false;
    }

    public boolean supportsTableCorrelationNames() throws SQLException
    {
        return true;
    }

    public boolean supportsTransactionIsolationLevel(int level) throws SQLException
    {
        return true;
    }

    public boolean supportsTransactions() throws SQLException
    {
        return true;
    }

    public boolean supportsUnion() throws SQLException
    {
        return false;
    }
     public boolean supportsUnionAll() throws SQLException
    {
        return false;
    }

    public boolean updatesAreDetected(int type) throws SQLException
    {
        return false;
    }

    public boolean usesLocalFilePerTable() throws SQLException
    {
        return false;
    }

   
    public boolean usesLocalFiles() throws SQLException
    {
        return false;
    }
 
    public boolean isWrapperFor(Class ifact) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("DatabaseMetadata::isWrapperFor called");
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public Class unwrap(Class iface) throws SQLException
    {
        if (JSqlError.isDebug) System.out.println("DatabaseMetadata::unwrap called");
        throw getException(CSQL_NOT_SUPPORTED);
    }   
    
}
