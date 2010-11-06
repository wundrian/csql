//Chache table t1
//CREATE TABLE t1 (f1 integer, f2 smallint, f3 tinyint,f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);
//insert 9 tuples with params for all fields (INSERT INTO t1 values (?,?,?,?,?,?,?,?,?))
//select tuple with WHERE clause having param for each fields(SELECT * FROM t1 WHERE f1=?, SELECT * from T1 where f2=?)
import java.sql.*;
/**
 *
 * @Author : Nihar
 */
public class GwStmt4 {
    public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway://localhost:5678", "root", "manager");
           Statement cStmt = con.createStatement();
           PreparedStatement stmt = null, selStmt= null;
           stmt = con.prepareStatement("INSERT INTO t1 VALUES (?,?,?,?,?,?,?,?);");
           stmt.setInt(1, 1);
           stmt.setShort(2,(short)2);
           //stmt.setByte(3,(byte)3);
           stmt.setLong(3,(long)4);
           stmt.setFloat(4,(float)5);
           stmt.setString(5, String.valueOf(5));
           stmt.setDate(6,Date.valueOf("2008-03-21"));
           stmt.setTime(7,Time.valueOf("18:00:00"));
           stmt.setTimestamp(8,Timestamp.valueOf("2008-03-21 18:00:00"));
           stmt.executeUpdate();
           stmt.close();
           con.commit();

           selStmt = con.prepareStatement("SELECT * from t1 where f1 = ?;");
           ResultSet rs = null;

           selStmt.setInt(1, 1);
           rs = selStmt.executeQuery();
           while (rs.next())
           {
                 System.out.println("Tuple value is " + rs.getInt(1) + " "+
                                                        rs.getShort(2) + " "+
                                                        rs.getLong(3) + " "+
                                                        rs.getFloat(4) + " "+
                                                        rs.getString(5) + " "+
                                                        rs.getDate(6) + " "+
                                                        rs.getTime(7) + " "+
                                                        rs.getTimestamp(8) + " "
                                                        );
           }
           rs.close();
           selStmt.close();
           con.close();
        }catch(Exception e) {
             System.out.println("Exception in Test: "+e);
             e.printStackTrace();
        }
    }
       
}
