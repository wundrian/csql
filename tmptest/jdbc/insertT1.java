import java.sql.*;

public class insertT1
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
            boolean rc = stmt.execute( "INSERT INTO t1 (f1, f2) values (2,3)" );
            rc = stmt.execute( "INSERT INTO t1 (f1, f2) values (31,80)" );
            rc = stmt.execute( "INSERT INTO t1 (f1, f2) values (722,9)" );
            con.commit();
            stmt.close();

            // Disconnect from CSQL
            con.close();

        } catch(Exception e) {
            System.out.println("insertT1: " + e );
            e.getStackTrace();
        }
    }
}
