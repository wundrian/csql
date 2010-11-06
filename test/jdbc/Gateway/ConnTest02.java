//To connect with connectstring "jdbc:gateway" and give null properties object. It should fail.
import java.sql.*;
public class ConnTest02
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway", null, null);
           if (con != null) {con.close(); System.exit(1);}
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }
}
