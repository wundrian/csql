//update tuple with WHERE clause having param for all fields(UPDATE t1 SET f2=100 WHERE f1=?AND f3=?....)
import java.sql.*;
/**
 *
 * @author bijaya
 */
public class GwStmt6 {
     public static void main(String[] arg)
    {
        try
        {
            Class.forName("csql.jdbc.JdbcSqlDriver");
            Connection con=DriverManager.getConnection("jdbc:gateway","root","manager");
            Statement cStmt=con.createStatement();
            PreparedStatement stmt=null,selStmt=null;
            stmt=con.prepareStatement("INSERT INTO t1 VALUES(?,?,?,?,?,?,?,?);");
            int ret=0;
            for(int i=0;i<10;i++)
            {
                stmt.setInt(1,i);
                stmt.setShort(2,(short)(i+1));
//                stmt.setByte(3,(byte)(i+2));
                stmt.setLong(3,(long)i);
                stmt.setFloat(4,(float)1000+i);
                stmt.setString(5, String.valueOf("Cache"+i));
                stmt.setDate(6,Date.valueOf("2008-03-21"));
		if(System.getenv("DSN").equals("oracle"))
                  stmt.setDate(7,Date.valueOf("2009-04-24"));
	 	else
	          stmt.setTime(7,Time.valueOf("18:00:00"));
                stmt.setTimestamp(8,Timestamp.valueOf("2008-03-21 18:00:00"));
                ret=stmt.executeUpdate();
                if(ret!=1) break;
            }
            stmt.close();
            con.commit();
            selStmt=con.prepareStatement("Select * from t1");
            ResultSet rs=null;
            rs=selStmt.executeQuery();
            while(rs.next())
            {
		if(System.getenv("DSN").equals("oracle")){
	           System.out.println("Tuple value is " + rs.getInt(1) + " "+
                                                        rs.getShort(2) + " "+
                                                        rs.getLong(3) + " "+
                                                        rs.getFloat(4) + " "+
                                                        rs.getString(5) + " "+
                                                        rs.getDate(6) + " "+
                                                        rs.getDate(7) + " "+
                                                        rs.getTimestamp(8) + " "
                                                        );
		}
		else{
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
            }
            rs.close();
            con.commit();
            ret=0;
            stmt=con.prepareStatement("UPDATE t1 SET f2=?, f8=? WHERE f1=?AND f9=?;");
            for(int i=0;i<10;i++)
            {
                stmt.setShort(1,(short)100);
		if(System.getenv("DSN").equals("oracle"))
		  stmt.setDate(2,Date.valueOf("2009-09-25"));
		else
	          stmt.setTime(2,Time.valueOf("19:38:25"));
                stmt.setInt(3,3);
                stmt.setTimestamp(4,Timestamp.valueOf("2008-03-21 18:00:00"));
                ret=stmt.executeUpdate();
                if(ret!=1) break;
            }
            stmt.close();
            con.commit();
            selStmt=con.prepareStatement("Select * from t1");
            rs=null;
            rs=selStmt.executeQuery();
            System.out.println();
            while(rs.next())
            {
                if(System.getenv("DSN").equals("oracle")){
                   System.out.println("Tuple value is " + rs.getInt(1) + " "+
                                                        rs.getShort(2) + " "+
                                                        rs.getLong(3) + " "+
                                                        rs.getFloat(4) + " "+
                                                        rs.getString(5) + " "+
                                                        rs.getDate(6) + " "+
                                                        rs.getDate(7) + " "+
                                                        rs.getTimestamp(8) + " "
                                                        );
		}
		else{
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
            }
            rs.close();
            con.commit();
            con.close();
       }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }


}
