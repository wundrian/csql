import java.sql.*;
import java.util.Random;
public class JDBCPopulate 
{
   public static Random generator = new Random();
   public static int getRandom(int end)
   {
       double val = generator.nextDouble();
       val *=end;
       return (int)(val);
   }
   
  public static void populate(Connection con)throws Exception
  {
	PreparedStatement stmt = null;
	String stmtStr="";
	String buf = "insert into big1 values(?,?,?,?,?,?,?,?,?,?,?,1,100,?,'GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO')";
	stmtStr = buf;
	stmt = con.prepareStatement(stmtStr);
	int count = 0;
        int ret =0;
	for(int i=0; i<10000; i++){
            stmt.setInt(1, i);
            stmt.setInt(2, i);
            stmt.setInt(3, i%2);
            stmt.setInt(4, i%4);
            stmt.setInt(5, i%10);
            stmt.setInt(6, i%20);
            stmt.setInt(7, i % 100);
            stmt.setInt(8, i % 1000);
            stmt.setInt(9, i % 2000);
            stmt.setInt(10, i % 5000);
            stmt.setInt(11,i);
            stmt.setString(12, "Value" + i);
  	    ret = stmt.executeUpdate();
	    if(ret!=1) {  
                System.out.println("Table population failed");
                return;
            }
   	    if (i % 1000 == 0) con.commit();
	    count++;
        }	
        con.commit();
	stmt.close();
        System.out.println("Records Inserted into big1 table: "+count);

	stmtStr = "insert into big2 values(?,?,?,?,?,?,?,?,?,?,?,1,100,'AXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXX','GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO')";
	stmt = con.prepareStatement(stmtStr);
	count = 0;
	for(int i=0; i<10000; i++){
            stmt.setInt(1, i);
            stmt.setInt(2, i);
            stmt.setInt(3, i%2);
            stmt.setInt(4, i%4);
            stmt.setInt(5, i%10);
            stmt.setInt(6, i%20);
            stmt.setInt(7, i % 100);
            stmt.setInt(8, i % 1000);
            stmt.setInt(9, i % 2000);
            stmt.setInt(10, i % 5000);
            stmt.setInt(11,i);
 
  	    ret = stmt.executeUpdate();
	    if(ret!=1) {  
                System.out.println("Table population failed");
                return;
            }
   	    if (i % 1000 == 0) con.commit();
	    count++;
        }	
        con.commit();
	stmt.close();
        System.out.println("Records Inserted into big2 table: "+count);

	stmtStr = "insert into small values(?,?,?,?,?,?,?,?,?,?,?,1,100,'AXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXX','GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO')";
	stmt = con.prepareStatement(stmtStr);
	count = 0;
	for(int i=0; i<1000; i++){
            stmt.setInt(1, i);
            stmt.setInt(2, i);
            stmt.setInt(3, i%2);
            stmt.setInt(4, i%4);
            stmt.setInt(5, i%10);
            stmt.setInt(6, i%20);
            stmt.setInt(7, i % 100);
            stmt.setInt(8, i % 1000);
            stmt.setInt(9, i % 2000);
            stmt.setInt(10, i % 5000);
            stmt.setInt(11,i);

  	    ret = stmt.executeUpdate();
	    if(ret!=1) {  
                System.out.println("Table population failed");
                return;
            }
   	    if (i % 100 == 0) con.commit();
	    count++;
        }	
        con.commit();
	stmt.close();
        System.out.println("Records Inserted into small table: "+count);

	return;
  }

//*****************************************************
public static void main(String[] args) 

   {
     int flag=1;
     if (args.length == 3)
     { 
         if (args[0].equals("csql")) flag=1;
         else if (args[0].equals("mysql")) flag=2;
         else if (args[0].equals("postgres")) flag=3;
         else if (args[0].equals("oracle")) flag=4;
         else if (args[0].equals("sybase")) flag=5;
     }
     else {
         System.out.println("Usage: java JDBCPopulate <DBNAME> <username> <password>");
         return;
     }
    
     try
     {
          Connection con = null;
          if (flag == 1) {
              Class.forName("csql.jdbc.JdbcSqlDriver");
              con = DriverManager.getConnection("jdbc:csql", args[1], args[2]);
          }else if (flag == 2) {
              Class.forName("com.mysql.jdbc.Driver");
              con = DriverManager.getConnection("jdbc:mysql://localhost/test", args[1], args[2]);
          }else if (flag == 3) {
              Class.forName("org.postgresql.Driver");
              con = DriverManager.getConnection("jdbc:postgresql://localhost:5432/test", args[1], args[2]);
          }else if (flag == 4) {
              Class.forName("oracle.jdbc.driver.OracleDriver");
              con = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:XE", args[1], args[2]);
          }else if (flag == 5) {
              Class.forName("com.sybase.jdbc3.jdbc.SybDataSource");
              con = DriverManager.getConnection("jdbc:sybase:Tds:localhost:4112", args[1], args[2]);
          }
          con.setAutoCommit(false);
          con.setTransactionIsolation(Connection.TRANSACTION_READ_COMMITTED);
          Statement cStmt = con.createStatement();
	  try { 
	      cStmt.execute("CREATE TABLE small (unique1 INT  NOT NULL , unique2 INT  NOT NULL , two INT  NOT NULL , four INT  NOT NULL , ten INT  NOT NULL , twenty INT  NOT NULL , onepercent INT  NOT NULL , tenpercent INT  NOT NULL , twentypercent INT  NOT NULL , fiftypercent INT  NOT NULL , unique3 INT  NOT NULL , evenonepercent INT  NOT NULL , oddonepercent INT  NOT NULL , stringu1 CHAR (52) NOT NULL , stringu2 CHAR (52) NOT NULL , string4 CHAR (52) NOT NULL )");
	
      cStmt.execute("CREATE TABLE big1 (unique1 INT  NOT NULL , unique2 INT  NOT NULL , two INT  NOT NULL , four INT  NOT NULL , ten INT  NOT NULL , twenty INT  NOT NULL , onepercent INT  NOT NULL , tenpercent INT  NOT NULL , twentypercent INT  NOT NULL , fiftypercent INT  NOT NULL , unique3 INT  NOT NULL , evenonepercent INT  NOT NULL , oddonepercent INT  NOT NULL , stringu1 CHAR (52) NOT NULL , stringu2 CHAR (52) NOT NULL , string4 CHAR (52) NOT NULL )");

	      cStmt.execute("CREATE TABLE big2 (unique1 INT  NOT NULL , unique2 INT  NOT NULL , two INT  NOT NULL , four INT  NOT NULL , ten INT  NOT NULL , twenty INT  NOT NULL , onepercent INT  NOT NULL , tenpercent INT  NOT NULL , twentypercent INT  NOT NULL , fiftypercent INT  NOT NULL , unique3 INT  NOT NULL , evenonepercent INT  NOT NULL , oddonepercent INT  NOT NULL , stringu1 CHAR (52) NOT NULL , stringu2 CHAR (52) NOT NULL , string4 CHAR (52) NOT NULL )");
              cStmt.close();
              con.commit();
          }catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}
          populate(con);
	  con.close();
        
      }  catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
       
    }
}
