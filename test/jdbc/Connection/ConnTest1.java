//Test connection default rollback mechanism
//close the connection without committing the transaction

class ConnTest1 
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
		   System.out.println("CREATE TABLE Returned " + rc);
		   
		   PreparedStatement stmt = null;
           stmt = con.prepareStatement("INSERT INTO T1 VALUES (?, ?);");
           for (int i =0 ; i< 10 ; i++) {
             stmt.setInt(1, i);
             stmt.setString(2, String.valueOf(i+100));
             stmt.executeUpdate();
           }
           con.close();

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
