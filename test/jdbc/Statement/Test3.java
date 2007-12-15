//Test DML statement with rollback

class Test3 
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
           stmt.close();
           con.commit();

           rc = cStmt.execute("UPDATE T1 set f2='2' where f1 = 2;");
		   ret = cStmt.executeUpdate("INSERT INTO T1 values (100, '100');");
           ret = cStmt.executeUpdate("DELETE FROM T1 WHERE f1 = 4;");
           con.rollback();

           System.out.println("After rollback, listing tuples:");
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
