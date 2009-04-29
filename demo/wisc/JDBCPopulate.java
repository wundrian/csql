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
	String buf = "insert into big1 values(?,?,0,2,0,10,50,688,1950,4950,9950,1,100,?,'GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO');";
	stmtStr = buf;
	stmt = con.prepareStatement(stmtStr);
	int count = 0;
        int ret =0;
	for(int i=0; i<10000; i++){
            stmt.setInt(1, i);
            stmt.setInt(2, i);
            stmt.setString(3, "Value" + i);
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

	stmtStr = "insert into big2 values(?,?,0,2,0,10,50,688,1950,4950,9950,1,100,'AXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXX','GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO');";
	stmt = con.prepareStatement(stmtStr);
	count = 0;
	for(int i=0; i<10000; i++){
            stmt.setInt(1, i);
            stmt.setInt(2, i);
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

	stmtStr = "insert into small values(?,?,0,2,0,10,50,688,1950,4950,9950,1,100,'AXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXX','GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO');";
	stmt = con.prepareStatement(stmtStr);
	count = 0;
	for(int i=0; i<1000; i++){
            stmt.setInt(1, i);
            stmt.setInt(2, i);
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

public static void main(String[] args) 
{
     try
     {
          Connection con = null;
          Class.forName("csql.jdbc.JdbcSqlDriver");
          con = DriverManager.getConnection("jdbc:csql", "root", "manager");
          con.setAutoCommit(false);
          con.setTransactionIsolation(Connection.TRANSACTION_READ_COMMITTED);
          Statement cStmt = con.createStatement();
	  try { 
	      cStmt.execute("CREATE TABLE small (unique1 INT  NOT NULL , unique2 INT  NOT NULL , two INT  NOT NULL , four INT  NOT NULL , ten INT  NOT NULL , twenty INT  NOT NULL , onepercent INT  NOT NULL , tenpercent INT  NOT NULL , twentypercent INT  NOT NULL , fiftypercent INT  NOT NULL , unique3 INT  NOT NULL , evenonepercent INT  NOT NULL , oddonepercent INT  NOT NULL , stringu1 CHAR (52) NOT NULL , stringu2 CHAR (52) NOT NULL , string4 CHAR (52) NOT NULL );");
	      cStmt.execute("CREATE TABLE big1 (unique1 INT  NOT NULL , unique2 INT  NOT NULL , two INT  NOT NULL , four INT  NOT NULL , ten INT  NOT NULL , twenty INT  NOT NULL , onepercent INT  NOT NULL , tenpercent INT  NOT NULL , twentypercent INT  NOT NULL , fiftypercent INT  NOT NULL , unique3 INT  NOT NULL , evenonepercent INT  NOT NULL , oddonepercent INT  NOT NULL , stringu1 CHAR (52) NOT NULL , stringu2 CHAR (52) NOT NULL , string4 CHAR (52) NOT NULL );");
	      cStmt.execute("CREATE TABLE big2 (unique1 INT  NOT NULL , unique2 INT  NOT NULL , two INT  NOT NULL , four INT  NOT NULL , ten INT  NOT NULL , twenty INT  NOT NULL , onepercent INT  NOT NULL , tenpercent INT  NOT NULL , twentypercent INT  NOT NULL , fiftypercent INT  NOT NULL , unique3 INT  NOT NULL , evenonepercent INT  NOT NULL , oddonepercent INT  NOT NULL , stringu1 CHAR (52) NOT NULL , stringu2 CHAR (52) NOT NULL , string4 CHAR (52) NOT NULL );");
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
