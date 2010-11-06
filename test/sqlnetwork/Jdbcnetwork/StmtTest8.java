//NULL Tset "INSERT null values to some fields with and without parameters"
import java.sql.*;
public class StmtTest8
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
	    stmt=con.prepareStatement("INSERT INTO T1(f1,f3,f5,f6,f7,f8,f9) VALUES(?,?,?,?,?,?,?);");
	    int ret=0;
	    for(int i=0;i<10;i++)
	    {
		stmt.setInt(1,i);
		stmt.setByte(2,(byte)(i+2));
		stmt.setFloat(3,(float)1000+i);
		stmt.setString(4, String.valueOf("Nihar"+i));
           	stmt.setDate(5,Date.valueOf("2008-03-21"));
           	stmt.setTime(6,Time.valueOf("18:00:00"));
           	stmt.setTimestamp(7,Timestamp.valueOf("2008-03-21 18:00:00"));
		ret=stmt.executeUpdate();
		if(ret!=1) break;
	    }
	    con.commit();
	    stmt=con.prepareStatement("INSERT INTO T1(f1,f2,f4,f6,f7,f8,f9) values(10,11,101,'Nihar10','2008-03-21','18:00:00','2008-03-21 18:00:00');");
	    stmt.executeUpdate();
	 
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
        
	    cStmt.executeUpdate("Drop table T1;");
	    con.close();
       }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
}

