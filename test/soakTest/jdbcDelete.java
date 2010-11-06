import java.sql.*;
import java.io.*;
import java.util.Calendar;
import java.text.SimpleDateFormat;

public class jdbcDelete
{
    public static final String DATE_FORMAT_NOW = "yyyy-MM-dd HH:mm:ss";
    public static final int TS = 1;
    
    public static String now() {
        Calendar cal = Calendar.getInstance();
        SimpleDateFormat sdf = new SimpleDateFormat(DATE_FORMAT_NOW);
        return sdf.format(cal.getTime());
    }

    public static void main(String[] args)
    {
        try {
            if (args.length != 1) { 
                System.out.println("Usage: java jdbcDelete <opfile>\n");
                return; 
            }
            Class.forName("csql.jdbc.JdbcSqlDriver");
            Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
            Connection adCon = DriverManager.getConnection("jdbc:Adapter", "root", "manager");
            PreparedStatement stmt = null, selStmt= null, delStmt = null, adSelStmt=null, adDelStmt=null;
            selStmt = con.prepareStatement("select f2 from soakTable limit 1;");
            delStmt = con.prepareStatement("delete from soakTable where f2 = ?;");
//            adSelStmt = adCon.prepareStatement("select f2 from soakTable limit 1;");
            adDelStmt = adCon.prepareStatement("delete from soakTable where f2 = ?;");
            ResultSet rs = null, adrs = null; int f2var = 0;
            FileWriter fstream = new FileWriter(args[0], true);
            BufferedWriter out = new BufferedWriter(fstream);
            while (true) {
                try { 
                Thread.sleep(jdbcDelete.TS);
                rs = selStmt.executeQuery();
                if(rs.next()) { f2var = rs.getInt(1); }
                rs.close();
     //           adrs = adSelStmt.executeQuery();
  //              if(adrs.next()) { f2var = adrs.getInt(1); }
  //              adrs.close();
                delStmt.setInt(1,f2var);
                delStmt.execute();
                con.commit();
                adDelStmt.setInt(1,f2var);
                adDelStmt.execute();
                adCon.commit();
                //System.out.println("f2var = "+f2var+" "+jdbcDelete.now());
                out.write("deleted PK: " +f2var + " "+jdbcDelete.now()+"\n");
                out.flush();
              } catch(Exception ex) {
                  System.out.println("Exception: "+ ex);          
                  System.out.println("jdbcDelete fail f2 = "+f2var+" "+jdbcDelete.now());
              }
            } 
        } catch (Exception e) {
            System.out.println("Exception: "+ e);
        }
    }
}
     
