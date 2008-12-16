//Donot Start Server .Connect only with connectstring "jdbc:"gateway and no username and password. It should fail
import java.sql.*;

/**
 *
 * @author bijaya
 */
public class GwTest3 {
     public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway");
           if (con != null) System.exit(1);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }

}
