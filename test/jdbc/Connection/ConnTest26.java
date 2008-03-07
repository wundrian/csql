//Create Connection, call commit() 10K times.
//System should be stable, check this by creating new connection and insert 1 tuple.
//Author: XieLiang
import java.sql.*;
public class ConnTest26 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
	   con.setAutoCommit(false);
           Statement cStmt = con.createStatement();
           int ret = 0;
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
	   for (int i=0; i <10000; i++)
		   con.commit();
	   Connection con2 = DriverManager.getConnection("jdbc:csql","root","manager");
	   int count = 0;
	   cStmt = con2.createStatement();
	   PreparedStatement stmt = null;
	   stmt = con2.prepareStatement("INSERT INTO T1 VALUES (?,?);");
	   stmt.setInt(1,1);
	   stmt.setString(2,"test1");
	   ret = stmt.executeUpdate();
	   if (ret != 1) 
		   System.out.println("test failed!");
	   stmt.close();
	   ResultSet rs = cStmt.executeQuery("SELECT * from T1;");
	   while(rs.next())
	   {
		    count++;
	   } 
	   rs.close();
	   System.out.println("Total rows selected " + count);
           cStmt.execute("DROP TABLE T1;");
	   con2.close();
           con.close();
           if (count ==1 ) System.exit(0); else System.exit(1);
        }catch(Exception e) {
           System.out.println("Exception in Test: "+e);
           e.printStackTrace();
           System.exit(1);
        }
    }
}
