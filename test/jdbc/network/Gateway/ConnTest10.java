//Test 100 statements simultaneously in one connection through jdbc:gateway://localhost:5678 , insert 1 tuple from
//each stmt, and check whether 100 tuples are inserted.
import java.sql.*;
public class ConnTest10
{
    public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway://localhost:5678", "root", "manager");
           Statement cStmt = con.createStatement();
           int ret =0;
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");

           PreparedStatement stmt[] = new PreparedStatement[100];;
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
           count=0;
           while (rs.next())
           {
               count++;
           }
           rs.close();
           con.commit();
           cStmt.execute("DROP TABLE T1;");
           con.close();
           if (count == 100) System.exit(0); else System.exit(1);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
            System.exit(1);
        }
    }
}
   
