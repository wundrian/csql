// Connect with "jdbc:csql://localhost:5678" and give correct "user" and "password" in properties object. It should pass as for csql default database is csql
import java.sql.*;
public class ConnTest11
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
           if (con == null) System.exit(1);
           con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit (1);
       }
    }
}
