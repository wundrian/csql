import java.sql.*;

public class selectT1
{
    public static void main( String argv[] )
    {
        try
        {
            // Load JDBC driver
            Class.forName("csql.jdbc.JdbcSqlDriver");

            // Connect to CSQL
            Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");

            // Insert Tuples
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery( "SELECT * FROM t1" );
            while( rs.next() )
	    {
               System.out.println( rs.getInt(1) + ", " + rs.getInt(2) );
            }
            rs.close();
            con.commit();
            stmt.close();

            // Disconnect from CSQL
            con.close();

        } catch(Exception e) {
            System.out.println("selectT1: " + e );
            e.getStackTrace();
        }
    }
}
