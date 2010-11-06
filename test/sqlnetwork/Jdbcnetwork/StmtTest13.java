//ExecuteUpdate for SELECT statement it should not return resultset throw exception

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;

/**
 *
 * @author bijaya
 */
public class StmtTest13 
{
     public static void main(String[] args)
     {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678/csql", "root", "manager");
           Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
           PreparedStatement stmt = null, selStmt= null;
           stmt = con.prepareStatement("INSERT INTO T1 VALUES (?, NULL);");
           for (int i =0 ; i< 10 ; i++) {
             stmt.setInt(1, i);
             stmt.executeUpdate();
           }
           stmt.close();
           con.commit();
           selStmt = con.prepareStatement("SELECT * from T1 ;");
           ResultSet rs = null;
           System.out.println("yes");
           int result = selStmt.executeUpdate();
            /* while (rs.next())
             {
                 int f1=rs.getInt(1);
                 if(rs.wasNull()) 
                     System.out.print(" NULL");
                 else 
                     System.out.print(" "+ f1);
                 String f2=rs.getString(2);
                 if(rs.wasNull()) 
                     System.out.println(" NULL");
                 else 
                     System.out.println(" "+ f2);
             }
             rs.close();
            */           
           cStmt.executeUpdate("Drop table T1;");
           con.close();
        }catch(Exception e) {
             System.out.println("Exception in Test: "+e);
             e.printStackTrace();
             System.exit(0);
        }
    }
}
