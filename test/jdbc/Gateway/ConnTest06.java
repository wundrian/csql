//Try to open through jdbc:gateway connection , close , then open .  it should pass 

import java.sql.*;
public class ConnTest06
{
    public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway", "root", "manager");
           if ( con == null )
                   System.exit(1);
           con.close();
           con = DriverManager.getConnection("jdbc:gateway","root","manager");
           if ( con == null )
                   System.exit(1);
           con.close();
           System.exit(0);
        }catch(Exception e) {
            System.out.println(e.getMessage());
            e.getStackTrace();
            System.exit(1);
       }
    }
}

