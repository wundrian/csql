//Show all tables
import java.sql.*;
public class DataMeta1
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
	   Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE t1 (f1 integer, f2 char (20),primary key(f2));");
           cStmt.execute("CREATE TABLE t2(f1 integer, f2 char (20),primary key(f2));");
           cStmt.execute("CREATE TABLE emp(f1 integer, f2 char (20),primary key(f2));");
           cStmt.execute("CREATE TABLE data(f1 integer, f2 char (20),primary key(f2));");
	   con.commit();
/*
	   ResultSet rs = null;
           rs = cStmt.executeQuery("GetAllTables");
	   while (rs.next())
	   {
	       System.out.println("tables is " + rs.getString(3));
	   }
	   rs.close();
*/
           ResultSet rsColumns = null;
           DatabaseMetaData meta = con.getMetaData();
           rsColumns = meta.getTables(null, null, null, null);
           while (rsColumns.next()) {
              String columnName = rsColumns.getString(3);
              System.out.println("Table name = " + columnName);
           }

           cStmt.execute("DROP TABLE t1 ;");
           cStmt.execute("DROP TABLE t2 ;");
           cStmt.execute("DROP TABLE emp ;");
           cStmt.execute("DROP TABLE data ;");
           con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
}
