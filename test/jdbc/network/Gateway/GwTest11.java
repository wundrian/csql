
//donot run csql server
//Create a table and index for that table. Then do (INSERT/UPDATE/DELETE/SELECT) with no params statement. 
import java.sql.*;
/**
 *
 * @Author : Nihar
 */
public class GwTest11 {
 public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway://localhost:5678", "root", "manager");
           Statement cStmt = con.createStatement();
           con.commit();

           cStmt.execute("INSERT INTO t1 VALUES (1, 'FIRST');");
           cStmt.executeUpdate("INSERT INTO t1 VALUES (2, 'SECOND');");
           con.commit();

           ResultSet rs = null;
           rs = cStmt.executeQuery("SELECT * from t1 where f1 = 1;");
           while (rs.next())
           {
               System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
           }
           rs.close();


           cStmt.execute("SELECT * from t1 where f1 = 2;");
           rs = cStmt.getResultSet();
           while (rs.next())
           {
               System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
           }
           rs.close();
           con.commit();

           cStmt.executeUpdate("UPDATE t1 SET f2 = 'CHANGED' WHERE f1 = 1;");
           con.commit();



           cStmt.executeUpdate("DELETE FROM t1 WHERE f1 = 2;");
           con.commit();

           System.out.println("After delete, listing tuples:");
           rs = cStmt.executeQuery("SELECT * from t1 ;");
           while (rs.next())
           {
               System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
           }
           rs.close();
           con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
 
}
