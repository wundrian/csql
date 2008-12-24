//select tuple with WHERE clause having param for some fields(SELECT * FROM T1 WHERE f1=?AND f2=? AND f3=?)
import java.sql.*;
public class StmtTest6
{
    public static void main(String[] arg)
    {
	try
	{
	    Class.forName("csql.jdbc.JdbcSqlDriver");
	    Connection con=DriverManager.getConnection("jdbc:csql://localhost:5678/csql","root","manager");
	    Statement cStmt=con.createStatement();
	    cStmt.execute("CREATE TABLE T1 (f1 integer, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);");
	    con.commit();
	    PreparedStatement stmt=null,selStmt=null;
	    stmt=con.prepareStatement("INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?);");
	    int ret=0;
	    for(int i=0;i<10;i++)
	    {
		stmt.setInt(1,i);
		stmt.setShort(2,(short)(i+1));
		stmt.setByte(3,(byte)(i+2));
        	stmt.setLong(4,(long)i);
		stmt.setFloat(5,(float)1000+i);
		stmt.setString(6, String.valueOf("Nihar"+i));
           	stmt.setDate(7,Date.valueOf("2008-03-21"));
           	stmt.setTime(8,Time.valueOf("18:00:00"));
           	stmt.setTimestamp(9,Timestamp.valueOf("2008-03-21 18:00:00"));
		ret=stmt.executeUpdate();
		if(ret!=1) break;
	    }
	    stmt.close();
	    con.commit();
	    selStmt=con.prepareStatement("SELECT * FROM T1 where f1 = ? and f2 = ? and f3 = ?");
	    ResultSet rs=null;
	    selStmt.setInt(1,2);
	    selStmt.setShort(2,(short)3);
            selStmt.setByte(3,(byte)4);
	    rs=selStmt.executeQuery();
	    while(rs.next())
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
	    con.commit();
	    cStmt.executeUpdate("Drop table T1;");
	    con.close();
       }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
}

