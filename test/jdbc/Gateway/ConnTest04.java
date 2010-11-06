//Try to connect with connectstring "jdbc:gateway" and give incorrect "user" and "password" in properties object. It should fail.
import java.sql.*;
public class ConnTest04
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway", "wrongusertest", "manager");
           if (con != null) System.exit (1);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }
}
