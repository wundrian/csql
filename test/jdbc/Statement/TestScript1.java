// Run csqlserver ,Create table. At the time of insertion , Insert some record with Null Value
//Check null inserted or not
// Test For setNull()
import java.sql.*;
/**
 *
 * @author bijaya
 */
public class TestScript1 {

    public static void main(String[] args) {
        
         try
        {
            Class.forName("csql.jdbc.JdbcSqlDriver");
            Connection con=DriverManager.getConnection("jdbc:csql","root","manager");
            Statement cStmt=con.createStatement();
            cStmt.execute("CREATE TABLE T1 (f1 integer, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);");
            con.commit();
            PreparedStatement stmt=null,selStmt=null;
            stmt=con.prepareStatement("INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?);");
            int ret=0;
            for(int i=0;i<10;i++)
            {
                if(i==2 ) {
                    stmt.setNull(1,java.sql.Types.INTEGER);
                    stmt.setNull(2,java.sql.Types.SMALLINT);
                    stmt.setNull(3,java.sql.Types.TINYINT);
                    stmt.setNull(4,java.sql.Types.BIGINT);
                    stmt.setNull(5,java.sql.Types.FLOAT);
                    stmt.setNull(6,java.sql.Types.CHAR);
                    stmt.setNull(7,java.sql.Types.DATE);
                    stmt.setNull(8,java.sql.Types.TIME);
                    stmt.setNull(9,java.sql.Types.TIMESTAMP);
                }else{
                stmt.setInt(1,i);
                stmt.setShort(2,(short)(i+1));
                stmt.setByte(3,(byte)(i+2));
                stmt.setLong(4,(long)i);
                stmt.setFloat(5,(float)1000+i);
                stmt.setString(6, String.valueOf("India"+i));
                stmt.setDate(7,Date.valueOf("2008-03-21"));
                stmt.setTime(8,Time.valueOf("18:00:00"));
                stmt.setTimestamp(9,Timestamp.valueOf("2008-03-21 18:00:00"));
                }
                ret=stmt.executeUpdate();
                if(ret!=1) break;
            }
            stmt.close();
            con.commit();
            selStmt=con.prepareStatement("SELECT * FROM T1 ;");
            ResultSet rs=null;
            selStmt.setInt(1,2);
            selStmt.setShort(2,(short)3);
            selStmt.setByte(3,(byte)4);
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
            cStmt.executeUpdate("Drop table T1;");
            con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
            System.exit(1);
        }

    }
}
