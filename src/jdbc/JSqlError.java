package csql.jdbc;
import java.util.Hashtable;
import java.sql.SQLException;

interface JSqlErrorType
{
    public static String CSQL_NOT_SUPPORTED = "00001";
    public static String CSQL_CON_REJECTED = "00002";
    public static String CSQL_TBL_NOT_FOUND = "00003";
    public static String CSQL_AUTHEN_ERR ="00004";
    public static String CSQL_TRANS_NOT_STARTED ="00005";
    public static String CSQL_TRANS_NOT_ROLLBACK ="00006";
    public static String CSQL_TRANS_NOT_COMMIT ="00007";
    public static String CSQL_NOT_DISCONNECT ="00008";
    public static String CSQL_INVALID_STATE ="00009";
    public static String CSQL_INVALID_ISOLATION ="00010";
    public static String CSQL_PREPARE_ERR ="00011";
    public static String CSQL_EXECUTE_ERR ="00012";
    public static String CSQL_NOT_PREPARED ="00013";
    public static String CSQL_NOT_QUERY ="00014";
    public static String CSQL_NOT_UPDATE ="00015";
    public static String CSQL_INVALID_DATATYPE ="00016";
}
public class JSqlError implements JSqlErrorType
{
    public static Hashtable hashTable;
    static
    {
        hashTable = new Hashtable();
        hashTable.put(CSQL_NOT_SUPPORTED, new SQLException("Feature not supported"));
        hashTable.put(CSQL_AUTHEN_ERR, new SQLException("Authentication error"));
        hashTable.put(CSQL_CON_REJECTED, new SQLException("Connection Rejected"));
        hashTable.put(CSQL_TBL_NOT_FOUND, new SQLException("Table not found"));
        hashTable.put(CSQL_TRANS_NOT_STARTED, new SQLException("Unable to start transaction"));
        hashTable.put(CSQL_TRANS_NOT_ROLLBACK, new SQLException("Unable to rollback transaction"));
        hashTable.put(CSQL_TRANS_NOT_COMMIT, new SQLException("Unable to commit transaction"));
        hashTable.put(CSQL_NOT_DISCONNECT, new SQLException("Unable to disconnect"));
        hashTable.put(CSQL_INVALID_STATE, new SQLException("Invalid state"));
        hashTable.put(CSQL_INVALID_ISOLATION, new SQLException("Invalid isolation level"));
        hashTable.put(CSQL_PREPARE_ERR, new SQLException("Statement Prepare failed"));
        hashTable.put(CSQL_EXECUTE_ERR, new SQLException("Statement execute failed"));
        hashTable.put(CSQL_NOT_PREPARED, new SQLException("Statement not prepared"));
        hashTable.put(CSQL_NOT_QUERY, new SQLException("Statement is not query"));
        hashTable.put(CSQL_NOT_UPDATE, new SQLException("Statement is a query"));
        hashTable.put(CSQL_INVALID_DATATYPE, new SQLException("Invalid data type"));
    }
    public static String getErrorMsg(String err)
    {
        return("CSqlJDBCDriver: "+ err+ " "+ hashTable.get(err));
    }

    public static SQLException getException(String err)
    {
        return((SQLException)hashTable.get(err));
    }
}
