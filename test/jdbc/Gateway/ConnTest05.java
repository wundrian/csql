//To connect with connectstring "jdbc:gateway" and give correct "user" and incorrect "password" in properties object. It should fail.

import java.sql.*;
public class ConnTest05
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway", "root", "wrongpasswdtestxieliang");
           if (con == null) System.exit(0);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }
}
