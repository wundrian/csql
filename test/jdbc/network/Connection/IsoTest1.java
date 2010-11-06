//Open connection and call setTransactionIsolation (TRANSACTION_SERIALIZABLE ). It should throw unsupported SQL exception.
import java.sql.*;
public class IsoTest1
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
		   if ( con == null )
			   System.out.println("test failed!");
		   con.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE);
		   con.commit();
           con.close();
		   System.out.println("test failed2!");
        }catch(Exception e) {
            System.out.println(e.getMessage());
            e.getStackTrace();
       }
    }
}
