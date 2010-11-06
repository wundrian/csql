//Primaykeyinfo
import java.sql.*;
public class DataMeta4 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
	   Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE t1 (f1 integer, f2 char (20),primary key(f2));");
	   cStmt.execute("CREATE INDEX IDX ON t1 ( f1);");
	   con.commit();
          ResultSet rs = null;
          DatabaseMetaData meta = con.getMetaData();
          rs = meta.getPrimaryKeys(null, null, "t1");

          while (rs.next()) {
              String columnName = rs.getString(4);
              System.out.println("getPrimaryKeys(): columnName=" + columnName);
              short pos=rs.getShort(5);
              System.out.println("getPrimaryKeys(): position = " + pos);
          }
           rs.close();
           cStmt.execute("DROP TABLE t1 ;");
           con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
}
