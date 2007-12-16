import java.sql.*;
public class JDBCExecTest 
{
   public static void main(String[] args) 
   {
       try
       {
          Class.forName("csql.jdbc.JdbcSqlDriver");
          Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
          Statement cStmt = con.createStatement();
          cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (194));");
          System.out.println("Table t1 created");
          cStmt.execute("CREATE INDEX IDX ON T1 (f1) ;");
          System.out.println("Primary Index created on T1 (f1) ");
          cStmt.close();
          con.commit();

          Statement stmt = con.createStatement();
          String sql = "INSERT INTO T1 (f1, f2) VALUES (1, 'DummyValue');";
          int count =0;
          int ret =0;
          long start =0, end =0, curr =0;
          long min =100000, max =0, tot =0;
          for (int i =0 ; i<= 100 ; i++) {
             start = System.nanoTime();
             ret = stmt.executeUpdate(sql);
             if (ret != 1) break; //error
             end = System.nanoTime();
             if (i ==0) continue;
             curr = end-start;
             tot = tot + curr;
             if (min > curr) min = curr;
             if (max < curr) max = curr;
             count++;

           }
           con.commit();
           System.out.println("Total Rows inserted  " + count );
           System.out.println(" Min:" + min+ " Max: "+max+" Avg: "+ tot/100 );

           count=0;
           start=0; end=0; curr=0;
           min=100000; max=0;tot =0;
           sql = "SELECT * from T1 where f1 = 6;";
           ResultSet rs = null;
           int intVal =0;
           String strVal = null;
           for (int i =0 ; i<= 100 ; i++) {
             start = System.nanoTime();
             rs = stmt.executeQuery(sql);
             if (rs.next())
             {
                ;
             }
             rs.close();
             end = System.nanoTime();
             if (i ==0) continue;
             curr = end-start;
             tot = tot + curr;
             if (min > curr) min = curr;
             if (max < curr) max = curr;
             count++;
           }
           con.commit();
           System.out.println("Total Rows selected " + count);
           System.out.println(" Min:" + min+ " Max: "+max+" Avg: "+ tot/100 );


           cStmt.execute("DROP TABLE T1;");
           System.out.println("Dropped table T1");
           cStmt.close();

           con.close();
           }
        catch(Exception e) {
           System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
       
    }
}

