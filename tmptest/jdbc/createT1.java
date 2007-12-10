import java.sql.*;

public class createT1
{
    public static void main( String argv[] )
    {
        try
        {
            // Load JDBC driver
            Class.forName("csql.jdbc.JdbcSqlDriver");

            // Connect to CSQL
            Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");

            // Create Table
            Statement stmt = con.createStatement();
            boolean rc = stmt.execute( "CREATE TABLE t1 (f1 int, f2 int)" );
            con.commit();
            stmt.close();

            // Disconnect from CSQL
            con.close();

		} catch(Exception e) {
            System.out.println("createT1: " + e );
            e.getStackTrace();
		}
    }
}



