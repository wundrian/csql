import java.sql.*;
import java.io.*;
import java.util.Calendar;
import java.text.SimpleDateFormat;

public class jdbcSelect1
{
    public static final String DATE_FORMAT_NOW = "yyyy-MM-dd HH:mm:ss";

    public static String now() {
        Calendar cal = Calendar.getInstance();
        SimpleDateFormat sdf = new SimpleDateFormat(DATE_FORMAT_NOW);
        return sdf.format(cal.getTime());
    }

    public static void main(String[] args)
    {
        try {
            if (args.length != 1) {
                System.out.println("Usage: java jdbcSelect1 <opfile>\n");
                return;
            }

            Class.forName("csql.jdbc.JdbcSqlDriver");
            Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
            Connection adCon = DriverManager.getConnection("jdbc:Adapter", "root", "manager");
            PreparedStatement stmt = null, selStmt= null;
            PreparedStatement adStmt = null, adSelStmt= null;
            selStmt=con.prepareStatement("select count(f1) from soakTable;");
            adSelStmt=adCon.prepareStatement("select count(f1) from soakTable;");
            ResultSet rs = null, adrs =null; int f1var=0, f2var=0, f3var=0;
            FileWriter fstream = new FileWriter(args[0], true);
            BufferedWriter out = new BufferedWriter(fstream);

            while(true){
                try { 
                rs= selStmt.executeQuery();
                if(rs.next()){
                    f1var=rs.getInt(1);
                }    
                rs.close();
                adrs=adSelStmt.executeQuery();
                if(adrs.next()){
                    f2var=adrs.getInt(1);
                }    
                adrs.close();
                con.commit();
                adCon.commit();
                out.write("Total Records in CSQL: " +f1var+" "+jdbcDelete.now()+"\n");
                out.write("Total Records in DRDB: " +f2var+" "+jdbcDelete.now()+"\n");
                out.flush();
                Thread.sleep(60000);
              } catch(Exception ex) {
              System.out.println("Exception: "+ ex);
               System.out.println("jdbcSelect1 failed at "+jdbcDelete.now());
            }
        } 
    } catch (Exception e) {
            System.out.println("Exception: "+ e);
        }
   }
}
  


            
