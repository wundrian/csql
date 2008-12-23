//Connect with connectstring "odbc:csql://localhost:5678/csql" and give correct "user" and "password" in properties object. It should fail.
import java.sql.*;
public class ConnTest5
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("odbc:csql://localhost:5678/csql", "root", "manager");
           if (con != null) System.exit(1);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit (0);
       }
    }
}
