import java.sql.*;
public class jdbcSelect
{
    public static void main(String[] args)
    {
        try {
            Class.forName("csql.jdbc.JdbcSqlDriver");
            Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
            PreparedStatement stmt = null, selStmt= null;
            selStmt=con.prepareStatement("select * from t1 limit 50 offset 5;");
            ResultSet rs = null; int f1var=0, f2var=0, f3var=0;
            float f4var=0;
            double f5var=0;
            String f6var="";

            while(true){
                rs=selStmt.executeQuery();
                if(rs.next()){
                    f1var=rs.getInt(1);
                    f2var=rs.getInt(2);
                    f3var=rs.getInt(3);
                    f4var=rs.getFloat(4);
                    f5var=rs.getDouble(5);
                    f6var=rs.getString(6);
                }    
                System.out.println("Selected value: " +f1var +" " +f2var +" " +f3var +" " +f4var +" " +f5var +" " +f6var);
                con.commit();
                Thread.sleep(5000);
            }
        }    
        catch (Exception e) {
            System.out.println("Exception: "+ e);
        }
   }
}
  


            
