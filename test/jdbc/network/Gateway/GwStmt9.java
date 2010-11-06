//Null statement test in Gateway for parameteraze statement on cache table
import java.sql.*;
/**
 *
 * @Author : Nihar
 */
public class GwStmt9 {
public static void main(String[] args) {
        
         try
        {
            Class.forName("csql.jdbc.JdbcSqlDriver");
            Connection con=DriverManager.getConnection("jdbc:gateway://localhost:5678","root","manager");
            Statement cStmt=con.createStatement();
            PreparedStatement stmt=null,selStmt=null;
            stmt=con.prepareStatement("INSERT INTO t1 VALUES(?,?,?,?,?,?,?,?);");
            int ret=0;
            for(int i=0;i<10;i++)
            {
                if(i==2 ) {
                    stmt.setNull(1,java.sql.Types.INTEGER);
                    stmt.setNull(2,java.sql.Types.SMALLINT);
//                    stmt.setNull(3,java.sql.Types.TINYINT);
                    stmt.setNull(3,java.sql.Types.BIGINT);
                    stmt.setNull(4,java.sql.Types.FLOAT);
                    stmt.setNull(5,java.sql.Types.CHAR);
                    stmt.setNull(6,java.sql.Types.DATE);
                    stmt.setNull(7,java.sql.Types.TIME);
                    stmt.setNull(8,java.sql.Types.TIMESTAMP);
                }else{
                stmt.setInt(1,i);
                stmt.setShort(2,(short)(i+1));
//                stmt.setByte(3,(byte)(i+2));
                stmt.setLong(3,(long)i);
                stmt.setFloat(4,(float)1000+i);
                stmt.setString(5, String.valueOf("India"+i));
                stmt.setDate(6,Date.valueOf("2008-03-21"));
                stmt.setTime(7,Time.valueOf("18:00:00"));
                stmt.setTimestamp(8,Timestamp.valueOf("2008-03-21 18:00:00"));
                }
                ret=stmt.executeUpdate();
                if(ret!=1) break;
            }
            stmt.close();
            con.commit();
            selStmt=con.prepareStatement("SELECT * FROM t1 ;");
            ResultSet rs=null;
            rs=selStmt.executeQuery();
            while(rs.next())
            {
                
                System.out.print("Tuple value is " + rs.getInt(1)+ " ");
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getShort(2) + " ");
                if(rs.wasNull()) System.out.print(" NULL");
  //              System.out.print(rs.getByte(3)  + " ");
  //              if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getLong(3)  + " ");
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getFloat(4) + " ");
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getString(5) + " "); 
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getDate(6) + " ");   
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.print(rs.getTime(7)  + " ");
                if(rs.wasNull()) System.out.print(" NULL");
                System.out.println(rs.getTimestamp(8) + " ");
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
