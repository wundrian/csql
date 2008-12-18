//Set Null insert statement without parameterise on cache tables T1 test it by wasNull()
import java.sql.*;
/**
 *
 * @author bijaya
 */
public class GwStmt8 
{
    public static void main(String[] arg)
    {
        try
        {
            Class.forName("csql.jdbc.JdbcSqlDriver");
            Connection con=DriverManager.getConnection("jdbc:gateway","root","manager");
            Statement cStmt=con.createStatement();
            PreparedStatement stmt=null,selStmt=null;
            stmt=con.prepareStatement("INSERT INTO T1(f1,f3,f5,f6,f7,f8,f9) VALUES(?,?,?,?,?,?,?);");
            int ret=0;
            for(int i=0;i<10;i++)
            {
                stmt.setInt(1,i);
                stmt.setByte(2,(byte)(i+2));
                stmt.setFloat(3,(float)1000+i);
                stmt.setString(4, String.valueOf("CSQL"+i));
                stmt.setDate(5,Date.valueOf("2008-03-21"));
                stmt.setTime(6,Time.valueOf("18:00:00"));
                stmt.setTimestamp(7,Timestamp.valueOf("2008-03-21 18:00:00"));
                ret=stmt.executeUpdate();
                if(ret!=1) break;
            }
            con.commit();
            stmt=con.prepareStatement("INSERT INTO T1(f1,f2,f4,f6,f7,f8,f9) values(10,11,101,'CSQL10','2008-03-21','18:00:00','2008-03-21 18:00:00');");
            stmt.executeUpdate();

            stmt.close();
            con.commit();

            selStmt=con.prepareStatement("Select * from T1");
            ResultSet rs=null;
            rs=selStmt.executeQuery();
            while(rs.next())
            {
                
                System.out.print("Tuple value is " + rs.getInt(1)+ " ");
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getShort(2) + " ");
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getByte(3)  + " ");
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getLong(4)  + " ");
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getFloat(5) + " ");
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getString(6) + " "); 
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getDate(7) + " ");   
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getTime(8)  + " ");
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.println(rs.getTimestamp(9) + " ");
                if(rs.wasNull()) System.out.println(" NULL");
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
