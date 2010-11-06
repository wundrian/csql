//Open two connections and call setTransactionIsolation(TRANSACTION_UNCOMMITTED ).
//From 1st connection insert tuple and then sleep, from 2nd connection try to select the inserted tuple. 
//Tuple should be seen.
//Author: XieLiang
import java.sql.*;
public class IsoTest2 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con1 = DriverManager.getConnection("jdbc:csql", "root", "manager");
           Connection con2 = DriverManager.getConnection("jdbc:csql", "root", "manager");
	   if ( (con1 == null) || (con2 == null) )
		   System.out.println("test failed!");
	   con1.setTransactionIsolation(Connection.TRANSACTION_READ_UNCOMMITTED);
	   con2.setTransactionIsolation(Connection.TRANSACTION_READ_UNCOMMITTED);
	   con1.setAutoCommit(false);
	   con2.setAutoCommit(false);
	   Statement cStmt = con1.createStatement();
	   cStmt.execute("CREATE TABLE T1(f1 integer,f2 char(20));");
	   PreparedStatement stmt = null;
	   stmt = con1.prepareStatement("INSERT INTO T1 VALUES(?,?);");
	   stmt.setInt(1,1);
	   stmt.setString(2,"test");
	   int ret = 0;
	   ret = stmt.executeUpdate();
	   if (ret != 1) {
               con1.close();
               con2.close();
               System.exit(1);
           }
	      
	   cStmt = con2.createStatement();
	   ResultSet rs = cStmt.executeQuery("SELECT * FROM T1;");
           int count =0;
	   while(rs.next())
	   {
               count++;
	   }	   
	   rs.close();
	   cStmt.execute("DROP TABLE T1;");
           con1.close();
	   con2.close();
           if (count !=1) System.exit(1); else System.exit(0);
        }catch(Exception e) {
            System.out.println(e.getMessage());
            e.getStackTrace();
            System.exit(1);
       }
    }
}
