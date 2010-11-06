import java.sql.*;
import java.io.*;
import java.util.Calendar;
import java.text.SimpleDateFormat;

public class jdbcUpdate
{
   public static final String DATE_FORMAT_NOW = "yyyy-MM-dd HH:mm:ss";

    public static String now() {
        Calendar cal = Calendar.getInstance();
        SimpleDateFormat sdf = new SimpleDateFormat(DATE_FORMAT_NOW);
        return sdf.format(cal.getTime());
    }


    public static void main(String[] args)
    {

        try{
            if (args.length != 1) {
                System.out.println("Usage: java jdbcDelete <opfile>\n");
                return;
            }

            Class.forName("csql.jdbc.JdbcSqlDriver");
            Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
            Connection adCon = DriverManager.getConnection("jdbc:Adapter", "root", "manager");

	    PreparedStatement selStmt = null, updStmt = null;
	    PreparedStatement adSelStmt = null, adUpdStmt = null;

            selStmt = con.prepareStatement("select f2 from soakTable limit 1 offset 50;");
            updStmt = con.prepareStatement("update soakTable set f1=? where f2=?;");
//            adSelStmt = adCon.prepareStatement("select f2 from soakTable limit 1 offset 50;");
            adUpdStmt = adCon.prepareStatement("update soakTable set f1=? where f2=?;");
            ResultSet rs = null, adrs=null; int f1var=111, f2var=0, adf2var=0;
            FileWriter fstream = new FileWriter(args[0], true);
            BufferedWriter out = new BufferedWriter(fstream);

            while(true){
              try {
                rs = selStmt.executeQuery();
                if(rs.next()) f2var=rs.getInt(1);
                rs.close();
//                adrs = adSelStmt.executeQuery();
  //              if(adrs.next()) adf2var=adrs.getInt(1);
    //            adrs.close();
                updStmt.setInt(1,f1var);
                updStmt.setInt(2,adf2var);
                updStmt.executeUpdate();
                con.commit();
                adUpdStmt.setInt(1,f1var);
                adUpdStmt.setInt(2,adf2var);
                adUpdStmt.executeUpdate();
            //    System.out.println("Updated value: " +f1var);
                adCon.commit();
                out.write("Updated PK: " + adf2var + " "+jdbcDelete.now()+"\n");
                out.flush();
                Thread.sleep(5000);

              } catch (Exception ex) {
                System.out.println("Exception: "+ ex);
                System.out.println("jdbcUpdate fail f2 = "+f2var+" "+jdbcDelete.now());
              }
        }
        }  
        catch (Exception e) {
           System.out.println("Exception: "+ e);
        }
   }
}
       
