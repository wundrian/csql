//Create Connection, setAutocommit(true), create table t1, insert into t1 10 records
//then call rollback(), select and count the number of records. It should be 10
import java.sql.*;
public class ConnTest34 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
           con.setAutoCommit(true);
           Statement cStmt = con.createStatement();
           PreparedStatement stmt = null;
           int ret = 0;
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
     	   cStmt.close();
           for (int i=0; i <10; i++)
           {
                stmt = con.prepareStatement("INSERT INTO T1 VALUES(?,?);");
                stmt.setInt(1,i);
                stmt.setString(2,"test"+i);
                ret = stmt.executeUpdate();
                stmt.close();
                if(ret != 1) 
                {
                    System.out.println("test failed");
                    break;
                }	
           }
           con.rollback();
	   
           int count = 0;
           cStmt = con.createStatement();
           ResultSet rs = cStmt.executeQuery("SELECT * from T1;");
           while(rs.next())
           {
               count++;
           } 
           rs.close();
           cStmt.execute("DROP TABLE T1;");
           cStmt.close();
           con.close();
           if (count == 10) 
               System.exit(0); 
           else 
               System.exit(1);
      }catch(Exception e) {
           System.out.println("Exception in Test: "+e);
           e.printStackTrace();
           System.exit(1);
           }
     }
}

