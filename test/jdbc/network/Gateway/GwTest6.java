//Donot Start CSQL Server
//Open through "jdbc:gateway://localhost:5678", close and then again open through "jdbc:gateway://localhost:5678". It should pass.
import java.sql.*;
/**
 *
 * @Author : Nihar
 */
public class GwTest6 {
    public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway://localhost:5678", "root", "manager");
           if ( con == null )
                   System.exit(1);
           System.out.println("Connection 1 done");
           con.close();
           con = DriverManager.getConnection("jdbc:gateway://localhost:5678","root","manager");
           if ( con == null )
                   System.exit(1);
           System.out.println("connection second time done");
           con.close();
           System.exit(0);
        }catch(Exception e) {
            System.out.println(e.getMessage());
            e.getStackTrace();
            System.exit(1);
       }
    }

}
