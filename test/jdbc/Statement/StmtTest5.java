import java.sql.*;
public class StmtTest5 
{
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

           selStmt = con.prepareStatement("SELECT * from T1 where f1 = ?;");
           ResultSet rs = null;

           selStmt.setInt(1, 1);
           rs = selStmt.executeQuery();
    	   while (rs.next())
           {
    	         System.out.println("Tuple value is " + rs.getInt(1));
           }
           rs.close();
           selStmt.close();

           cStmt.execute("DROP TABLE T1 ;");
           con.close();
        }catch(Exception e) {
             System.out.println("Exception in Test: "+e);
             e.printStackTrace();
        }
    }
}
