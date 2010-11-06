//Close the connection and then call preparedStatement(). It should fail
import java.sql.*;
public class ConnTest19 
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
	   PreparedStatement pStmt = null;
	   pStmt = con.prepareStatement("create table t1(f1 integer);");
	   if (pStmt != null)
	   	System.exit(1);
        }catch(Exception e) {
            System.out.println(e.getMessage());
            e.getStackTrace();
            if (e.getMessage().equals("Invalid state")) System.exit(0);
            else System.exit(1);

       }
    }
}
