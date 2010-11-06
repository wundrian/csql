//Create connection, setAutocommit(false) , create Statement, insert 10 tuples, close the connection. 
//Open another connection and check the number of tuples. It should be Zero.
import java.sql.*;
public class ConnTest22 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
           con.setAutoCommit(false);
	   Statement cStmt = con.createStatement();
           
	   int ret = 0;
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
           PreparedStatement stmt = null;
           stmt = con.prepareStatement("INSERT INTO T1 VALUES (?, ?);");
	       for (int i=0; i <10 ; i++)
	       {      
               stmt.setInt(1, i);
               stmt.setString(2, String.valueOf(i));
               ret = stmt.executeUpdate();
               if (ret !=1) break;
	       }
           stmt.close();
	   con.close();
	   con = DriverManager.getConnection("jdbc:csql","root","manager");
	   int count = 0;
	   cStmt = con.createStatement();
	   ResultSet rs = cStmt.executeQuery("SELECT * from T1;");
	   while(rs.next())
	   {
		    count++;
	   } 
	   rs.close();
           cStmt.execute("DROP TABLE T1;");
           con.close();
           if (count == 0) System.exit(0); else System.exit(1);
        }catch(Exception e) {
           System.out.println("Exception in Test: "+e);
           e.printStackTrace();
           System.exit(1);
        }
    }
}
