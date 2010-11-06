//ExecuteUpdate Should return no of records updated

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;

/**
 *
 * @author bijaya
 */
public class TestScript3 {
 public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
           Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
           cStmt.execute("CREATE INDEX IDX ON T1 ( f1);");
           con.commit();
           PreparedStatement stmt = null, selStmt= null;
           stmt = con.prepareStatement("INSERT INTO T1 VALUES (?, ?);");
           int ret=0;
           for (int i =0 ; i< 10 ; i++) {
             stmt.setInt(1, i);
             stmt.setString(2, String.valueOf(i+100));
             ret=stmt.executeUpdate();
             if (ret != 1){
                 System.out.println("ExecuteUpdate doesnot return proper values in Insert "+ret);
                 break;
             }
              System.out.println("ExecuteUpdate return proper values in Insert ");
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
           int a=5;
           stmt = con.prepareStatement("UPDATE T1 SET f2 = ? WHERE f1 >5;");
      
             stmt.setString(1, String.valueOf(a+200));
   
             ret = stmt.executeUpdate();
             if (ret != 4){
                 System.out.println("ExecuteUpdate doesnot return proper values for Update "+ret);
             }
             System.out.println("ExecuteUpdate return proper values fro Update "+ret);
          
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

           stmt = con.prepareStatement("DELETE FROM T1 ;");
           
  
             ret = stmt.executeUpdate();
             if (ret !=10) 
             {
                 System.out.println("ExecuteUpdate doesnot return proper vslues for Delete "+ret);
             }
             System.out.println("ExecuteUpdate returns proper vslues for delete "+ret);
         
           stmt.close();
           con.commit();

          
           cStmt.execute("DROP TABLE T1 ;");
           con.close();
        }catch(Exception e) {

             System.out.println("Exception in Test: "+e);
             e.printStackTrace();
        }
    }
}

