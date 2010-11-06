//update tuple with SET and WHERE clause having params (UPDATE T1 SET f2=?, f8=? WHERE f1=?AND f9=?)
import java.sql.*;
public class StmtTest7
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
	    selStmt=con.prepareStatement("Select * from T1");
	    ResultSet rs=null;
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
	    ret=0;
	    stmt=con.prepareStatement("UPDATE T1 SET f2=?, f8=? WHERE f1=?AND f9=?;");
	    for(int i=0;i<10;i++)
	    {
		stmt.setShort(1,(short)100);
	        stmt.setTime(2,Time.valueOf("19:38:25"));
		stmt.setInt(3,3);
		stmt.setTimestamp(4,Timestamp.valueOf("2008-03-21 18:00:00"));
		ret=stmt.executeUpdate();
	        if(ret!=1) break;
	    }
	    stmt.close();
	    con.commit();
            selStmt=con.prepareStatement("Select * from T1");
            rs=null;
            rs=selStmt.executeQuery();
	    System.out.println();
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

