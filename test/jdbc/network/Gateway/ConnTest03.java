//To connect with connectstring "jdbc:gateway://localhost:5678" and give empty properties object. It should fail.

import java.sql.*;
public class ConnTest03 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway://localhost:5678");
           if (con != null) System.exit(1);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }
}
