//Donot Start CSQL Server
//To connect with connectstring "jdbc:gateway" and
//give correct "user" and incorrect "password" in properties object. It should fail.

import java.sql.*;
/**
 *
 * @author bijaya
 */
public class GwTest5 {
 public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway", "root", "wrongpasswdtestxieliang");
           if (con == null) 
           {
               System.out.println("Test Case Passed");
               System.exit(0);
           }
           System.out.println("Test Case Failed");
           con.close();
           System.exit(1);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }

}
