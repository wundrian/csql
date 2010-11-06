//Try to connect with connectstring "jdbc:csql" and give correct "user" and "password" in properties object. It should pass.
import java.sql.*;
public class ConnTest1
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
  	  if ( con == null ) System.exit(1);
           con.close();
           System.exit(0);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.getStackTrace();
            System.exit(1);
       }
    }
}
