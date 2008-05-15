import java.sql.*;
public class gwexample 
{
   public static void main(String[] args) 
   {
       try
       {
          Class.forName("csql.jdbc.JdbcSqlDriver");
          Connection con = DriverManager.getConnection("jdbc:gateway", "root", "manager");
          Statement cStmt = con.createStatement();

          PreparedStatement stmt = null, selStmt= null;
          stmt = con.prepareStatement("INSERT INTO t1 (f1, f2) VALUES (?, ?);");
          int count =0;
          int ret =0;
          for (int i =0 ; i< 10 ; i++) {
             stmt.setInt(1, i);
             stmt.setString(2, String.valueOf(i+100));
             ret = stmt.executeUpdate();
             if (ret != 1) break; //error
             count++;
           }
           stmt.close();
           con.commit();
           System.out.println("Total Rows inserted " + count);

           count =0;
           stmt = con.prepareStatement("UPDATE t1 SET f2 = ? WHERE f1 = ?;");
           for (int i =0 ; i< 10 ; i +=2) {
             stmt.setString(1, String.valueOf(i+200));
             stmt.setInt(2, i);
             ret = stmt.executeUpdate();
             if (ret != 1) break; //error
             count++;
           }
           stmt.close();
           con.commit();
           System.out.println("Total Rows updated " + count);
       
           count =0;
           stmt = con.prepareStatement("DELETE FROM t1 WHERE f1 = ?;");
           for (int i =0 ; i< 10 ; i +=3) {
             stmt.setInt(1, i);
             ret = stmt.executeUpdate();
             if (ret != 1) break; //error
             count++;
           }
           stmt.close();
           con.commit();
           System.out.println("Total Rows deleted " + count);

           count =0;
           selStmt = con.prepareStatement("SELECT * from t1 where f1 = ?;");
           ResultSet rs = null;
           for (int i =0 ; i< 10 ; i++) {
             selStmt.setInt(1, i);
             rs = selStmt.executeQuery();
             while (rs.next())
             {
                System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
                count++;
             }
             rs.close();
           }
           selStmt.close();
           con.commit();
           System.out.println("Total Rows selected " + count);
           con.close();
           }
        catch(Exception e) {
           System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
       
    }
}

