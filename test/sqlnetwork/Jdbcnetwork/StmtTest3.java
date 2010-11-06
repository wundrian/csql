//Open a connection and then close it. After that execute INSERT/QUERY/UPDATE statement. It should fail [StmtTest3.java]
import java.sql.*;
public class StmtTest3 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678/csql", "root", "manager");
           Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
           cStmt.execute("CREATE INDEX IDX ON T1 ( f1);");
           con.commit();
           con.close();

           //after close the connection,execute "INSERT" statement,it should fail
           try
           {
               cStmt.execute("INSERT INTO T1 VALUES (1, 'FIRST');");
               System.exit(1);
           }
           catch(Exception e)
           {
               System.out.println("insert exception---" + e.getMessage());
           }

           //after close the connection,execute "QUERY" statement,it should fail
           try
           {
               cStmt.executeQuery("SELECT * from T1 where f1 = 1;");
               System.exit(2);
           }
           catch(Exception e)
           {
               System.out.println("query exception---" + e.getMessage());
           }

           //after close the connection,execute "UPDATE" statement,it should fail
           try
           {
               cStmt.executeUpdate("UPDATE T1 SET f2 = 'CHANGED' WHERE f1 = 1;");
               System.exit(3);
           }
           catch(Exception e)
           {
               System.out.println("update exception---" + e.getMessage()); 
           }

           //cleanup 
           cStmt.close();
           Connection con1 = DriverManager.getConnection("jdbc:csql", "root", "manager");
           Statement cStmt1 = con1.createStatement();
           cStmt1.execute("DROP TABLE T1 ;");
           cStmt1.close();
           con1.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: " + e.getMessage());
            e.printStackTrace();
            System.exit(4);
        }
    }
}
