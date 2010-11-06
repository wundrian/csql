//Donot Start CSQL Server
//connect through the jdbc:gateway://localhost:5678 URL create Statement and call execute to create a table. it should fail
import java.sql.*;
/**
 *
 * @Author : Nihar
 */
public class GwTest9 {
 public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway://localhost:5678", "root", "manager");
           Statement cStmt = con.createStatement();
           boolean ret ;
           cStmt.execute("CREATE TABLE t2 (f1 integer, f2 char (20));");
           cStmt.close();
           con.close();
       }catch(Exception e)
       {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
            System.out.println("Test Case Passed");
            System.exit(0);

       }
 }

}
