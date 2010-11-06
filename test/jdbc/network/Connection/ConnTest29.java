//Create Connection, insert 1 tuple, call rollback. Repeat the steps(connec,insert,rollback) for 10K times.
//Then connect and check whether 0 tuples are present.
import java.sql.*;
public class ConnTest29 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
	   con.setAutoCommit(false);
           Statement cStmt = con.createStatement();
	   PreparedStatement stmt = null;
	   int ret = 0;
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
	   con.commit();
	   con.close();
	   for (int i=0; i <10000; i++)
	   {
	        con = DriverManager.getConnection("jdbc:csql","root","manager");
	        con.setAutoCommit(false);
		stmt = con.prepareStatement("INSERT INTO T1 VALUES(?,?);");
		stmt.setInt(1,1);
	        stmt.setString(2,"xieliangkingsoft");
	        ret = stmt.executeUpdate();
	        if(ret != 1) 
	        {
		   System.out.println("test failed");
	     	   break;
	        }	
		stmt.close();
		con.rollback();
		con.close();
 	   }
	   con = DriverManager.getConnection("jdbc:csql","root","manager");
	   int count = 0;
	   cStmt = con.createStatement();
	   ResultSet rs = cStmt.executeQuery("SELECT * from T1;");
	   while(rs.next())
	   {
		    count++;
	   } 
	   rs.close();
	   System.out.println("Total rows selected " + count);
           cStmt.execute("DROP TABLE T1;");
	   con.commit();
           con.close();
           if (count == 0) System.exit(0); else System.exit(1);
        }catch(Exception e) {
           System.out.println("Exception in Test: "+e);
           e.printStackTrace();
           System.exit(1);
        }
    }
}
