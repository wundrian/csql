
//Irrespective of number set in setFetchSize(), getFetchSize() should return 1

import java.sql.*;
/**
 *
 * @author bijaya
 */
public class TestScript10 {
 public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
            Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
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
           ResultSet rs=cStmt.getResultSet();
           int retval=cStmt.getFetchSize();
           System.out.println("Default Fetch Size "+retval);
           cStmt.setFetchSize(3);   
           retval=cStmt.getFetchSize();
           System.out.println("Default Fetch Size "+retval);
           while (rs.next())
           {
                 System.out.println("Tuple value is " + rs.getInt(1) + " "+
                                                        rs.getShort(2) + " "+
                                                        rs.getByte(3) + " "+
                                                        rs.getLong(4) + " "+
                                                        rs.getFloat(5) + " "+
                                                        rs.getString(6) + " "+
                                                        rs.getDate(7) + " "+
                                                        rs.getTime(8) + " "+
                                                        rs.getTimestamp(9) + " "
                                                        );
           }
           rs.close();
           cStmt.close();

           cStmt.execute("DROP TABLE T1 ;");
           con.close();
        }catch(Exception e) {
             System.out.println("Exception in Test: "+e);
             e.printStackTrace();
             System.exit(0);
        }
    }
}
