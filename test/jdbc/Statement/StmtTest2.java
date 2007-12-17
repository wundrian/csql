//Test DML statement with no parameters on execute and executeUpdate 
import java.sql.*;
public class StmtTest2 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
	   Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
	   cStmt.execute("CREATE INDEX IDX ON T1 ( f1);");
	   con.commit();

           cStmt.execute("INSERT INTO T1 VALUES (1, 'FIRST');");
           cStmt.executeUpdate("INSERT INTO T1 VALUES (2, 'SECOND');");
           con.commit();

	   ResultSet rs = null;
           rs = cStmt.executeQuery("SELECT * from T1 where f1 = 1;");
	   while (rs.next())
	   {
	       System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
	   }
	   rs.close();


           cStmt.execute("SELECT * from T1 where f1 = 2;");
	   rs = cStmt.getResultSet();
	   while (rs.next())
	   {
	       System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
	   }
	   rs.close();
	   con.commit();

           cStmt.executeUpdate("UPDATE T1 SET f2 = 'CHANGED' WHERE f1 = 1;");
           con.commit();



           cStmt.executeUpdate("DELETE FROM T1 WHERE f1 = 2;");
           con.commit();

           System.out.println("After delete, listing tuples:");
	   rs = cStmt.executeQuery("SELECT * from T1 ;");
	   while (rs.next())
	   {
	       System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
	   }
	   rs.close();
	   con.commit();
           cStmt.execute("DROP TABLE T1 ;");
           con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
}
