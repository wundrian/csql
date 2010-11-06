//execute with select,get result set and close the result set and then call fetch, it should fail
import java.sql.*;
/** 
 *
 * @author praba
 */
public class TestScript12 {
 public static Connection con;
 public static Statement cStmt;
 public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
           cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 integer);");
           con.commit();
           PreparedStatement stmt = null, selStmt= null;
           stmt = con.prepareStatement("INSERT INTO T1 VALUES (?,?);");
           stmt.setInt(1, 1);
           stmt.setInt(2,2);
           stmt.executeUpdate();
           stmt.close();
           con.commit();

           cStmt = con.createStatement();
           cStmt.execute("SELECT * from T1;");
           ResultSet rs=cStmt.getResultSet();
           rs.next();
           System.out.println("Record: " + rs.getInt(1)+ " "+ rs.getInt(2));
           rs.close();
           rs.next();
           System.out.println("Failed:rs.next succedded");
           con.commit();
           con.close();
           System.exit(1);
        }catch(Exception e) {
             System.out.println("Exception in Test: "+e);
             e.printStackTrace();
             try{
             con.close();
             }catch(Exception ex){}
             System.exit(0);
        }
    }
}
