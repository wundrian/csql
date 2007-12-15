//Test 1000 connections

class ConnTest2 
{
	public static void main(String[] args) 
	{
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
		   Statement cStmt = con.createStatement();
		   int ret =0;
           boolean rc = cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
		   con.close();

	       PreparedStatement stmt = null;
		   for (int i=0; i <10000 ; i++)
		   {
		       con = DriverManager.getConnection("jdbc:csql", "root", "manager");	   
               stmt = con.prepareStatement("INSERT INTO T1 VALUES (?, ?);");
               stmt.setInt(1, i);
               stmt.setString(2, String.valueOf(i+100));
               stmt.executeUpdate();
               stmt.close();
			   con.commit();
			   con.close();
		   }


           con = DriverManager.getConnection("jdbc:csql", "root", "manager");
		   cStmt = con.createStatement();
           System.out.println("Listing tuples:");
		   rs = cStmt.executeQuery("SELECT * from t1;");
		   while (rs.next())
		   {
		       System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
		   }
		   rs.close();
		   con.commit();

           con.close();
           }catch(Exception e) {
               System.out.println("Exception in Test: "+e);
                e.getStackTrace();
           }
	    }
    }
}
