/* 1. Connect to Target DB using connection string "jdbc:adapter".
 *
 * 2. Used correct UserName and Password.
 * 3. Connect to the Target DB and Close the Connection
 * 4. Again Connect and Close.
 * 5. It should pass.
 *
 * Author : Jitendra Lenka
 */

import java.sql.*;
public class ConTest01
{
   public static void main(String[] args)
   {
       try
       {
       	   Class.forName("csql.jdbc.JdbcSqlDriver");
	   Connection con = null;
	   con=DriverManager.getConnection("jdbc:adapter","root","manager");
	   if(con != null) 
	   {  
	     System.out.println("Connect to Target DB");
	   }
	   else 
	   {  
	     System.out.println("Failed to Connect");
             System.exit(1);
	   }
	   con.close();
	   System.out.println("Connection Closed");
	   //-----------------------------
           con=DriverManager.getConnection("jdbc:adapter","root","manager");
	   if(con != null)
	   {
	      System.out.println("Again Connect to Target DB");
	   }
	   else
	   {
	     System.out.println("Failed to Connect to Target DB");
             System.exit(1);
	   }
           con.close();
	   System.out.println("Connection Closed");
	   System.exit(0);       
       }catch(Exception e){
            System.out.println("Exception in Test: " +e);
	    e.getStackTrace();
	    System.exit(1);
       }
   }
}
