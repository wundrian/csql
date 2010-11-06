//Test 2000 connections in jdbc:gateway://localhost:5678
import java.sql.*;

public class ConnTest09
{
    public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway://localhost:5678", "root", "manager");
           con.close();
           int i;
           for ( i=1; i <2000 ; i++)
           {
               con = DriverManager.getConnection("jdbc:gateway://localhost:5678", "root", "manager");
               con.close();
           }
           if (i !=2000) System.exit(1); else System.exit(0);
       }catch(Exception e) {
               System.out.println("Exception in Test: "+e);
               e.printStackTrace();
               System.exit(1);
       }
    }
}
            
