//Close the connection and they call commit(). It should fail.
import java.sql.*;
public class ConnTest17 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
	   if ( con == null )
		   System.exit(1);
           con.close();
	   con.commit();
           System.exit(1);
        }catch(Exception e) {
            System.out.println(e.getMessage());
            e.getStackTrace();
            if (e.getMessage().equals("Invalid state")) System.exit(0);
            else System.exit(1);

       }
    }
}
