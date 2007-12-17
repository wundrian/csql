//Test 100 statements simultaneously in one connection 
import java.sql.*;
public class ConnTest4 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
           Statement cStmt = con.createStatement();
	   int ret =0;
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");

           PreparedStatement stmt[] = new PreparedStatement[1000];;
	   for (int i=0; i <100 ; i++)
	   {      
               stmt[i] = con.prepareStatement("INSERT INTO T1 VALUES (?, ?);");
               if (i %10 ==0) System.out.println("statements prepared "+ i);
	   }
           int count =0;
	   for (int i=0; i <100 ; i++)
	   {      
               stmt[i].setInt(1, i);
               stmt[i].setString(2, String.valueOf(i+100));
               ret = stmt[i].executeUpdate();
               if (ret != 1) break;
               stmt[i].close();
   	       con.commit();
               count++;
	   }
           System.out.println("Total rows inserted "+ count);
	   cStmt = con.createStatement();
           System.out.println("Listing tuples:");
	   ResultSet rs = cStmt.executeQuery("SELECT * from T1;");
	   while (rs.next())
	   {
	       System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
	   }
	   rs.close();
	   con.commit();
           cStmt.execute("DROP TABLE T1;");
           con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
}
