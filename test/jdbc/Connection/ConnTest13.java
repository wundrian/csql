//Try to connect with connectstring "jdbc:csql" and give correct "user" and incorrect "password" in properties object. It should fail.
//Author: XieLiang
import java.sql.*;
public class ConnTest13
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql", "root", "wrongpasswdtestxieliang");
           if (con != null) System.exit(1);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }
}
