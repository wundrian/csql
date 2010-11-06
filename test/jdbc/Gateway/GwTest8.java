//Donot Start CSQL Server
//Test 2000 connections in jdbc:gateway

import java.sql.*;
/**
 *
 * @author bijaya
 */
public class GwTest8 {
    public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway", "root", "manager");
           con.close();
           int i;
           for ( i=1; i <2000 ; i++)
           {
               con = DriverManager.getConnection("jdbc:gateway", "root", "manager");
               if(con==null) break;
               con.close();
           }
           if (i !=2000)
           {
               System.out.println("Test Case Failed");
               System.exit(1);
           }else {
               System.out.println("Test Case Passed");
               System.exit(0);
           }
       }catch(Exception e) {
               System.out.println("Exception in Test: "+e);
               e.printStackTrace();
               System.exit(1);
       }
    }

}
