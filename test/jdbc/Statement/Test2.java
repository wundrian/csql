//Test DML statement with no parameters on execute and executeUpdate 

class Test2 
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
		   
		   rc = cStmt.execute("CREATE INDEX IDX ON T1 ( f1);");
		   System.out.println("CREATE INDEX Returned " + rc);
		   con.commit();
           rc = cStmt.execute("INSERT INTO T1 VALUES (1, 'FIRST');");
		   System.out.println("INSERT Returned " + rc);

           ret = cStmt.executeUpdate("INSERT INTO T1 VALUES (2, 'SECOND');");
   		   System.out.println("INSERT Returned " + ret);
           con.commit();

		   ResultSet rs = null;
           rs = cStmt.executeQuery("SELECT * from t1 where f1 = 1;");
		   while (rs.next())
		   {
		       System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
		   }
		   rs.close();


           rc = cStmt.execute("SELECT * from t1 where f1 = 2;");
		   System.out.println("execute SELECT Returned " + rc);
		   rs = cStmt.getResultSet();
		   while (rs.next())
		   {
		       System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
		   }
		   rs.close();
		   con.commit();


           int ret=0;
           ret = cStmt.executeUpdate("UPDATE T1 SET f2 = 'CHANGED' WHERE f1 = 1;");
   		   System.out.println("UPDATE Returned " + ret);
           con.commit();



           ret = cStmt.executeUpdate("DELETE FROM T1 WHERE f1 = 2;");
   		   System.out.println("DELETE Returned " + ret);
           con.commit();


           System.out.println("After delete, listing tuples:");
		   rs = cStmt.executeQuery("SELECT * from t1 ;");
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
