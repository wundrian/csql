//Cache table t1
//Open a connection and then close it. After that execute INSERT/QUERY/UPDATE statement. It should fail 

import java.sql.*;
/**
 *
 * @Author : Nihar
 */
public class GwStmt3 {
public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway://localhost:5678", "root", "manager");
           Statement cStmt = con.createStatement();
           con.commit();
           con.close();

           //after close the connection,execute "INSERT" statement,it should fail
           try
           {
               cStmt.execute("INSERT INTO t1 VALUES (1, 'FIRST');");
               System.exit(1);
           }
           catch(Exception e)
           {
               System.out.println("insert exception---" + e.getMessage());
           }

           //after close the connection,execute "QUERY" statement,it should fail
           try
           {
               cStmt.executeQuery("SELECT * from t1 where f1 = 1;");
               System.exit(2);
           }
           catch(Exception e)
           {
               System.out.println("query exception---" + e.getMessage());
           }

           //after close the connection,execute "UPDATE" statement,it should fail
           try
           {
               cStmt.executeUpdate("UPDATE t1 SET f2 = 'CHANGED' WHERE f1 = 1;");
               System.exit(3);
           }
           catch(Exception e)
           {
               System.out.println("update exception---" + e.getMessage());
           }

           //cleanup 
           
     }catch(Exception e) {
            System.out.println("Exception in Test: " + e.getMessage());
            e.printStackTrace();
            System.exit(4);
        }
    }
}
