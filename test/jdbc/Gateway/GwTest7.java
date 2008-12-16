//Donot Start CSQL Server
//Open the connection through jdbc:gateway and then call isClosed(). It should return false.
//Close the connection jdbc:gateway and then call isClosed(). It should return true
import java.sql.*;
/**
 *
 * @author bijaya
 */
public class GwTest7 {

    public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway", "root", "manager");
           if ( con == null )
                   System.exit(1);
           if(con.isClosed()) {
               System.out.println("Test Case Failed");
               System.exit(1);
           }
           con.close();
           if(!con.isClosed())
           {
               System.out.println("Test Case Failed");
               System.exit(1);
           }
           System.out.println("Test Case Passed");
        }catch(Exception e) {
            System.out.println(e.getMessage());
            e.getStackTrace();
            System.exit(1);
       }
    }

}
