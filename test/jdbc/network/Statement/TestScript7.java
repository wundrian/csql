
//executequery with ins, upd, del statements which will throw exception

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;

/**
 *
 * @author bijaya
 */
public class TestScript7 {
 public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
           Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
           con.commit();
           PreparedStatement stmt = null, selStmt= null;
           stmt = con.prepareStatement("INSERT INTO T1 VALUES (?, ?);");
           for (int i =0 ; i< 10 ; i++) {
             stmt.setInt(1, i);
             stmt.setString(2, String.valueOf(i+100));
             stmt.executeQuery();
           }
           stmt.close();
           con.commit();
           selStmt = con.prepareStatement("SELECT * from T1 ;");
           ResultSet rs = null;
           rs = selStmt.executeQuery();
           while (rs.next())
           {
               System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
           }
           rs.close();
           
           int ret=0;
           stmt = con.prepareStatement("UPDATE T1 SET f2 = ? WHERE f1 = ?;");
           for (int i =0 ; i< 10 ; i +=2) {
             stmt.setString(1, String.valueOf(i+200));
             stmt.setInt(2, i);
             stmt.executeQuery();
             
           }
           stmt.close();
           con.commit();

           System.out.println("After update, listing tuples:");
           
           rs = selStmt.executeQuery();
           while (rs.next())
           {
               System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
           }
           rs.close();
           
           con.commit();
           stmt = con.prepareStatement("DELETE FROM T1 WHERE f1 = ?;");
           for (int i =0 ; i< 10 ; i +=3) {
            stmt.setInt(1, i);
            stmt.executeQuery();
            
           }
           stmt.close();
           con.commit();

           System.out.println("After delete, listing tuples:");
          
           rs = selStmt.executeQuery();
           while (rs.next())
           {
               System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
           }
           rs.close();
         
           con.commit();
           cStmt.execute("DROP TABLE T1 ;");
           con.close();
        }catch(Exception e) {
             System.out.println("Exception in Test: "+e);
             e.printStackTrace();
             System.exit(0);
        }
    }

}
