//reate a table and index for that table. Then do (INSERT/UPDATE/DELETE/SELECT) with params statement.
import java.sql.*;
public class StmtTest1 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678/csql", "root", "manager");
	   Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
 	   cStmt.execute("CREATE INDEX IDX ON T1 ( f1);");
	   con.commit();
	   PreparedStatement stmt = null, selStmt= null;
           stmt = con.prepareStatement("INSERT INTO T1 VALUES (?, ?);");
           for (int i =0 ; i< 10 ; i++) {
             stmt.setInt(1, i);
             stmt.setString(2, String.valueOf(i+100));
             stmt.executeUpdate();
           }
           stmt.close();
           con.commit();
           selStmt = con.prepareStatement("SELECT * from T1 where f1 = ?;");
	   ResultSet rs = null;
           for (int i =0 ; i< 10 ; i++) {
             selStmt.setInt(1, i);
             rs = selStmt.executeQuery();
     	     while (rs.next())
	     {
		 System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
	     }
   	     rs.close();
           }
           int ret=0;
           stmt = con.prepareStatement("UPDATE T1 SET f2 = ? WHERE f1 = ?;");
           for (int i =0 ; i< 10 ; i +=2) {
             stmt.setString(1, String.valueOf(i+200));
             stmt.setInt(2, i);
             ret = stmt.executeUpdate();
             if (ret != 1) break;
           }
           stmt.close();
           con.commit();

           System.out.println("After update, listing tuples:");
           for (int i =0 ; i< 10 ; i++) {
             selStmt.setInt(1, i);
             rs = selStmt.executeQuery();
	     while (rs.next())
	     {
		 System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
	     }
	     rs.close();
           }
	   con.commit();



           stmt = con.prepareStatement("DELETE FROM T1 WHERE f1 = ?;");
           for (int i =0 ; i< 10 ; i +=3) {
             stmt.setInt(1, i);
             ret = stmt.executeUpdate();
             if (ret !=1) break;
           }
           stmt.close();
           con.commit();

           System.out.println("After delete, listing tuples:");
           for (int i =0 ; i< 10 ; i++) {
             selStmt.setInt(1, i);
             rs = selStmt.executeQuery();
   	     while (rs.next())
 	     {
		 System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
	     }
	     rs.close();
           }
	   con.commit();
           cStmt.execute("DROP TABLE T1 ;");
           con.close();
        }catch(Exception e) {
             System.out.println("Exception in Test: "+e);
             e.printStackTrace();
        }
    }
}
