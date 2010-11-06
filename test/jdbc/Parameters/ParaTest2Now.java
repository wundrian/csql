//select tuple with WHERE clause having param for some fields(SELECT * FROM T1 WHERE f1='now' AND f2=? AND f3=?)
import java.sql.*;
public class ParaTest2Now 
{
    public static void main(String[] arg)
    {
	try
	{
	    Class.forName("csql.jdbc.JdbcSqlDriver");
	    Connection con=DriverManager.getConnection("jdbc:csql","root","manager");
	    Statement cStmt=con.createStatement();
//	    cStmt.execute("CREATE TABLE T1 (f1 integer, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);");
	    cStmt.execute("CREATE TABLE T1 (f1 date, f2 int, f3 char(10));");
	    con.commit();
	    PreparedStatement stmt=null,selStmt=null;
            stmt=con.prepareStatement("INSERT INTO T1 values('2008-03-21',0,'Nihar0');");
	    stmt.executeUpdate();
            stmt=con.prepareStatement("INSERT INTO T1 values('now',1,'Nihar1');");
	    stmt.executeUpdate();
            stmt=con.prepareStatement("INSERT INTO T1 values('2008-03-24',2,'Nihar2');");
	    stmt.executeUpdate();
            stmt=con.prepareStatement("INSERT INTO T1 values('now',3,'Nihar3');");
	    stmt.executeUpdate();
            stmt=con.prepareStatement("INSERT INTO T1 values('2008-03-21',4,'Nihar4');");
	    stmt.executeUpdate();
            stmt=con.prepareStatement("INSERT INTO T1 values('now',5,'Nihar5');");
	    stmt.executeUpdate();
	    
	    stmt.close();
	    con.commit();

	    System.out.println("SELECT * FROM T1;\n");
	    selStmt=con.prepareStatement("SELECT * FROM T1;");
	    ResultSet rs=null;
	    rs=selStmt.executeQuery();
	    while(rs.next())
	    {
		System.out.println("Tuple value is " + rs.getDate(1) + " "+
                                                        rs.getInt(2) + " "+
                                                        rs.getString(3) 
                                                        );

	    }

	    System.out.println("\nSELECT * FROM T1 where f1 = 'now';\n");
	    selStmt=con.prepareStatement("SELECT * FROM T1 where f1 = 'now';");
	    rs=null;
	    rs=selStmt.executeQuery();
	    while(rs.next())
	    {
		System.out.println("Tuple value is " + rs.getDate(1) + " "+
                                                        rs.getInt(2) + " "+
                                                        rs.getString(3) 
                                                        );

	    }

	    System.out.println("\nSELECT * FROM T1 where f2 >= ? and f3 <= ?;\n");
	    selStmt=con.prepareStatement("SELECT * FROM T1 where f2 >= ? and f3 <= ?");
	    rs=null;
	    selStmt.setInt(1,1);
            selStmt.setString(2,String.valueOf("Nihar3"));
	    rs=selStmt.executeQuery();
	    while(rs.next())
	    {
		System.out.println("Tuple value is " + rs.getDate(1) + " "+
                                                        rs.getInt(2) + " "+
                                                        rs.getString(3) 
                                                        );

	    }

	    System.out.println("\nSELECT * FROM T1 where f1='now' and f2 >= ? and f3 <= ?;\n");
	    selStmt=con.prepareStatement("SELECT * FROM T1 where f1='now' and f2 >= ? and f3 <= ?");
	    rs=null;
	    selStmt.setInt(1,1);
            selStmt.setString(2,String.valueOf("Nihar3"));
	    rs=selStmt.executeQuery();
	    while(rs.next())
	    {
		System.out.println("Tuple value is " + rs.getDate(1) + " "+
                                                        rs.getInt(2) + " "+
                                                        rs.getString(3) 
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

