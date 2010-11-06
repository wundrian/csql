//Test 500 statements in one connection one after other
import java.sql.*;
public class ConnTest3 
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

           PreparedStatement stmt = null;
	   for (int i=0; i <500 ; i++)
	   {      
               stmt = con.prepareStatement("INSERT INTO T1 VALUES (?, ?);");
               stmt.setInt(1, i);
               stmt.setString(2, String.valueOf(i+100));
               ret = stmt.executeUpdate();
               if (ret !=1) break;
               stmt.close();
	       con.commit();
               if (i %100 ==0) 
               {
                   System.out.println("Total statements created "+ i);
                   System.gc();
                   Thread.sleep(500);
               }

	   }

	   cStmt = con.createStatement();
           System.out.println("Listing tuples:");
	   ResultSet rs = cStmt.executeQuery("SELECT * from T1;");
           int count =0;
	   while (rs.next())
	   {
               count++;
	   }
           System.out.println("Total rows selected " + count);
	   rs.close();
	   con.commit();
           cStmt.execute("DROP TABLE T1;");
           con.close();
           if (count !=500) System.exit(1); else System.exit(0);
        }catch(Exception e) {
           System.out.println("Exception in Test: "+e);
           e.printStackTrace();
           System.exit(1);
        }
    }
}
