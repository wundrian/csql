//No CSQL server is running .Connect with connectstring "jdbc:gateway" and give incorrect "user" and "password" in properties object. It should fail.
import java.sql.*;
/**
 *
 * @author bijaya
 */
public class GwTest4 {

     public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway", "wrongusertest", "manager");
           if (con == null)
           {
               System.out.println("Test Case1 Passed");
           }
           System.out.println("Test Case1 Failed");
           System.exit(1);
           Connection con1 = DriverManager.getConnection("jdbc:gateway", "root", "wrongpasswdtestxieliang");
           if (con == null)
           {
               System.out.println("Test Case2 Passed");
               System.exit(0);
           }
           System.out.println("Test Case2 Failed");
           con.close();
           System.exit(1);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }

}
