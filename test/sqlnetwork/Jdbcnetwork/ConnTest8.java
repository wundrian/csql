//Connect with "jdbc:csql:5678:localhost:csql" and give correct "user" and "password" in properties object. It should fail
import java.sql.*;
public class ConnTest8 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql:5678:localhost:csql", "root", "manager");
           if (con != null) {con.close(); System.exit(1);}
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }
}
