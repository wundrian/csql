//select tuple with WHERE clause having param for some fields in Inner Join(SELECT T1.f1,T2.f1,T1.f2,T2.f2,T1.f3,T2.f3 FROM T1 INNER JOIN T2 ON T1.f1>=2 AND T1.f2>=4 AND T2.f3=6)
import java.sql.*;
public class InnerJoinPara 
{
    public static void main(String[] arg)
    {
	try
	{
	    Class.forName("csql.jdbc.JdbcSqlDriver");
	    Connection con=DriverManager.getConnection("jdbc:csql","root","manager");
	    Statement cStmt=con.createStatement();
	    cStmt.execute("CREATE TABLE T1 (f1 integer, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);");
	    cStmt.execute("CREATE TABLE T2 (f1 integer, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);");
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
	    System.out.println("SELECT * FROM T1;");
	    selStmt=con.prepareStatement("SELECT * FROM T1;");
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

	    stmt=con.prepareStatement("INSERT INTO T2 VALUES(?,?,?,?,?,?,?,?,?);");
	    ret=0;
	    for(int i=0;i<10;i+=2)
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

	    System.out.println("SELECT * FROM T2;");
	    selStmt=con.prepareStatement("SELECT * FROM T2;");
	    rs=null;
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

	    System.out.println("SELECT T1.f1,T2.f1,T1.f2,T2.f2,T1.f3,T2.f3 FROM T1 INNER JOIN T2 ON T1.f1>=2 AND T1.f2>=4 AND T2.f3=6");
	    selStmt=con.prepareStatement("SELECT T1.f1,T2.f1,T1.f2,T2.f2,T1.f3,T2.f3 FROM T1 INNER JOIN T2 ON T1.f1>=? AND T1.f2>=? AND T2.f3=?");
	    rs=null;
	    selStmt.setInt(1,2);
	    selStmt.setShort(2,(short)4);
            selStmt.setByte(3,(byte)6);
	    rs=selStmt.executeQuery();
            System.out.println("T1.f1\tT2.f1\tT1.f2\tT2.f2\tT1.f3\tT2.f3");
	    while(rs.next())
	    {
		System.out.println( rs.getInt(1) + "\t"+
				    rs.getInt(2) + "\t"+
                                    rs.getShort(3) + "\t"+
                                    rs.getShort(4) + "\t"+
                                    rs.getByte(5) + "\t"+
                                    rs.getByte(6) 
                                   );

	    }
	    rs.close();
	    con.commit();

	    cStmt.executeUpdate("Drop table T1;");
	    cStmt.executeUpdate("Drop table T2;");
	    con.close();
       }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
}

