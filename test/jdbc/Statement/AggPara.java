//select tuple with WHERE clause having param for some fields in Agggegate 
//SELECT f1,AVG(f5) FROM T1 GROUP BY f1 HAVING AVG(f5)>?;
//SELECT f1,AVG(f5) FROM T1 WHERE f1>? GROUP BY f1 ;
//SELECT f1,AVG(f5) FROM T1 WHERE f1>? GROUP BY f1 HAVING AVG(f5)>?;

import java.sql.*;
public class AggPara
{
    public static void main(String[] arg)
    {
	try
	{
	    Class.forName("csql.jdbc.JdbcSqlDriver");
	    Connection con=DriverManager.getConnection("jdbc:csql","root","manager");
            Statement cStmt=con.createStatement();
	    PreparedStatement selStmt=null;

	    System.out.println("SELECT T1.f1,AVG(T1.f5) FROM T1 GROUP BY T1.f1;");
	    selStmt=con.prepareStatement("SELECT T1.f1,AVG(T1.f5) FROM T1 GROUP BY T1.f1;");
	    ResultSet rs=null;
	    rs=selStmt.executeQuery();
            System.out.println("T1.f1\tAVG(T1.f5)");
	    while(rs.next())
	    {
		System.out.println( rs.getInt(1) + "\t"+
                                    rs.getDouble(2)
                                   );

	    }
	    rs.close();
	    con.commit();

	    System.out.println("SELECT f1,AVG(f5) FROM T1 GROUP BY f1 HAVING AVG(f5)>5000;");
	    selStmt=con.prepareStatement("SELECT f1,AVG(f5) FROM T1 GROUP BY f1 HAVING AVG(f5)>?; ");
	    rs=null;
	    selStmt.setDouble(1,(float)5000);
	    rs=selStmt.executeQuery();
            System.out.println("T1.f1\tAVG(T1.f5)");
	    while(rs.next())
	    {
		System.out.println( rs.getInt(1) + "\t"+
                                    rs.getDouble(2)
                                   );

	    }
	    rs.close();
	    con.commit();

	    System.out.println("SELECT f1,AVG(f5) FROM T1 WHERE f1>200 GROUP BY f1;");
	    selStmt=con.prepareStatement("SELECT f1,AVG(f5) FROM T1 WHERE f1>? GROUP BY f1; ");
	    rs=null;
	    selStmt.setInt(1,(int)200);
	    rs=selStmt.executeQuery();
            System.out.println("T1.f1\tAVG(T1.f5)");
	    while(rs.next())
	    {
		System.out.println( rs.getInt(1) + "\t"+
                                    rs.getDouble(2)
                                   );

	    }
	    rs.close();
	    con.commit();

	    System.out.println("SELECT f1,AVG(f5) FROM T1 WHERE f1> 100 GROUP BY f1 HAVING AVG(f5)>5000;");
	    selStmt=con.prepareStatement("SELECT f1,AVG(f5) FROM T1 WHERE f1>? GROUP BY f1 HAVING AVG(f5)>?;");
	    rs=null;
	    selStmt.setInt(1,100);
	    selStmt.setDouble(2,(float)5000);
	    rs=selStmt.executeQuery();
            System.out.println("T1.f1\tT1.f2\tAVG(T1.f5)");
	    while(rs.next())
	    {
		System.out.println( rs.getInt(1) + "\t"+
                                    rs.getDouble(2)
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

