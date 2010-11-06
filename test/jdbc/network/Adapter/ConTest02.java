/* 1.Connect to Target DB using connection string  "jdbc:adapter://localhost:5678". 
 *
 * 2. Used null properties object
 * 3. Coreect username and wrong password
 * 4. Wrong UserName and Correct password
 * 5. Above all three should fail 
 */

import java.sql.*;
public class ConTest02
{
   public static void main(String[] args)
   {
       try
       {
       	   Class.forName("csql.jdbc.JdbcSqlDriver");
	   Connection con = null;
	   con=DriverManager.getConnection("jdbc:adapter://localhost:5678",null,null);
	   if(con != null) 
	   {  
	     System.out.println("Error-1" + con);
	     con.close();
	     System.exit(1);
	   }
	   
          //Correct userName and Wrong Password
	  con=DriverManager.getConnection("jdbc:adapter","root","MANAGER");
	  if(con != null)
	  {
	      System.out.println("Error-2" + con);
	      con.close();
	      System.exit(2);
	  }

	 
	  //wrong userName adn correct password
	  con=DriverManager.getConnection("jdbc:adapter","ROOT","manager");
	  if(con != null)
	  {
	     System.out.println("Error-2" + con);
	     con.close();
	     System.exit(2);
	  }

	 }catch(Exception e){
            System.out.println("Exception in Test: " +e);
	    e.getStackTrace();
	    System.exit(0);
       }
   }
}
