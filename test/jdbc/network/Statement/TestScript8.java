
//execute with ins,upd,del and getUpdateCount(). getResultSet() should return null.

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

/**
 *
 * @author bijaya
 */
public class TestScript8 {
 public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
           Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
           
           con.commit();
           for(int i=0;i<10;i++){
               cStmt.execute("INSERT INTO T1 VALUES (1, 'FIRST');");
           }
           ResultSet rs = null;
           rs=cStmt.getResultSet();
           if(rs==null)
               System.out.println(" Not return a result set for insert statement");
           else
               System.out.println(" Test Case Failed");
           con.commit();

           rs = null;
           rs = cStmt.executeQuery("SELECT * from T1 ;");
           while (rs.next())
           {
               System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
           }
           rs.close();

           cStmt.executeUpdate("UPDATE T1 SET f2 = 'CHANGED' WHERE f1 <4;");
           int cout=cStmt.getUpdateCount();
           System.out.println("Total update: "+cout);
           rs=cStmt.getResultSet();
           if(rs==null)
               System.out.println(" Not return a result set for update statement");
           else
               System.out.println(" Test Case Failed");
           con.commit();
           cStmt.execute("SELECT * from T1 ;");
           rs = cStmt.getResultSet();
           while (rs.next())
           {
               System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
           }
           rs.close();
           con.commit();

           cStmt.executeUpdate("DELETE FROM T1 WHERE f1 <5;");
           cout=cStmt.getUpdateCount();
           System.out.println("Total delete: "+cout);
           rs=cStmt.getResultSet();
           if(rs==null)
               System.out.println(" Not return a result set for delete statement");
           else
               System.out.println(" Test Case Failed");
           con.commit();
         
           System.out.println("After delete, listing tuples:");
           rs = cStmt.executeQuery("SELECT * from T1 ;");
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
        }
    }

}
