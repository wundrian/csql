//Columns information
import java.sql.*;
public class DataMeta2 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
	   Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE t1 (f1 integer, f2 char (20),primary key(f2));");
	   con.commit();
           ResultSet rsColumns = null;
           DatabaseMetaData meta = con.getMetaData();
           rsColumns = meta.getColumns(null, null, "t1", null);
           while (rsColumns.next()) {
              String columnName = rsColumns.getString(4);
              System.out.println("column name=" + columnName);
              int columnType = rsColumns.getInt(5);
              System.out.println("type:" + columnType);
              int size = rsColumns.getInt(7);
              System.out.println("size:" + size);
              int nullable = rsColumns.getInt(11);
              if (nullable == DatabaseMetaData.columnNullable) 
              {
                System.out.println("nullable true");
              } else {
                System.out.println("nullable false");
              }
              int position = rsColumns.getInt(17);
              System.out.println("position:" + position);
      
        }

           cStmt.execute("DROP TABLE t1 ;");
           con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
}
