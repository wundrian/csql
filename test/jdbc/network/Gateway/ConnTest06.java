//Try to open through jdbc:gateway://localhost:5678 connection , close , then open .  it should pass 

import java.sql.*;
public class ConnTest06
{
    public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con =null;
	   con=DriverManager.getConnection("jdbc:gateway://localhost:5678", "root", "manager");
           if ( con == null )
           System.exit(1);
           con.close();
           
	   //Connection con1=null;
	   con = DriverManager.getConnection("jdbc:gateway://localhost:5678","root","manager");
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

