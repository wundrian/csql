//Test 5000 connections
import java.sql.*;

public class ConnTest2 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
	   Statement cStmt = con.createStatement();
	   int ret =0;
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
	   con.close();
           int count =0;
           PreparedStatement stmt = null;
           for (int i=0; i <5000 ; i++)
	   {
	       con = DriverManager.getConnection("jdbc:csql", "root", "manager");	   
               con.setAutoCommit(false);
               stmt = con.prepareStatement("INSERT INTO T1 VALUES (?, ?);");
               stmt.setInt(1, i);
               stmt.setString(2, String.valueOf(i+100));
               ret = stmt.executeUpdate();
               if (ret != 1) break;
               count++;
               stmt.close();
	       con.commit();
	       con.close();
               if (i%100 ==0)  {System.out.println("Total Connections made "+ i); System.gc(); Thread.sleep(500);}
	   }
           System.out.println("Total Rows inserted "+ count);


           con = DriverManager.getConnection("jdbc:csql", "root", "manager");
	   cStmt = con.createStatement();
           System.out.println("Listing tuples:");
	   ResultSet rs = cStmt.executeQuery("SELECT * from T1;");
           count =0;
	   while (rs.next())
  	   {
               count++;
	   }
	   rs.close();
	   con.commit();
           System.out.println("Total rows selected " + count);
           cStmt.execute("DROP TABLE T1;");
           con.close();
           if (count !=5000) System.exit(1); else System.exit(0);
           }catch(Exception e) {
               System.out.println("Exception in Test: "+e);
               e.printStackTrace();
               System.exit(1);
           }
    }
}
