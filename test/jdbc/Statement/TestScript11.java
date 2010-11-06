//execute with select ,close  statement and call getResultSet(). it should not give result set
import java.sql.*;
/** 
 *
 * @author bijaya
 */
public class TestScript11 {
 public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
           Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);");
           con.commit();
           PreparedStatement stmt = null, selStmt= null;
           stmt = con.prepareStatement("INSERT INTO T1 VALUES (?,?,?,?,?,?,?,?,?);");
           stmt.setInt(1, 1);
           stmt.setShort(2,(short)2);
           stmt.setByte(3,(byte)3);
           stmt.setLong(4,(long)4);
           stmt.setFloat(5,(float)5);
           stmt.setString(6, String.valueOf(5));
           stmt.setDate(7,Date.valueOf("2008-03-21"));
           stmt.setTime(8,Time.valueOf("18:00:00"));
           stmt.setTimestamp(9,Timestamp.valueOf("2008-03-21 18:00:00"));
           stmt.executeUpdate();
           stmt.close();
           con.commit();

           cStmt = con.createStatement();
           cStmt.execute("SELECT * from T1;");
           cStmt.close();
           ResultSet rs=cStmt.getResultSet();
           if(rs==null)
           {
                System.out.println("Test case Passed ");
                cStmt = con.createStatement();
                cStmt.execute("DROP TABLE T1 ;");
                con.close();
                System.exit(0);
           }else
           {
               System.out.println("Test case failed");
               cStmt = con.createStatement();
               cStmt.execute("DROP TABLE T1 ;");
               con.close();
               System.exit(1);
           }
          
           
        }catch(Exception e) {
             System.out.println("Exception in Test: "+e);
             e.printStackTrace();
        }
    }
}
