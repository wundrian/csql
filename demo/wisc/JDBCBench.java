import java.sql.*;
import java.util.Random;
public class JDBCBench 
{
   public static Random generator = new Random();
   public static int getRandom(int end)
   {
       double val = generator.nextDouble();
       val *=end;
       return (int)(val);
   }
   
   public static int singleTuple(Connection con, boolean flag)throws Exception
   {
	PreparedStatement stmt = null ;
	String stmtStr;
        if (flag) {
	    String buf = "SELECT unique1, unique2, stringu1, stringu2 from big1 where unique1=?;";
	    stmtStr = buf;
        }else {
	    String buf = "SELECT unique1, unique2, stringu1, stringu2 from big1 where stringu1=?;";
	    stmtStr = buf;
        }
	
	stmt = con.prepareStatement(stmtStr);
	int count=0, recordCount=0;
	int ret =0;
	long start=0, end=0, curr=0;
	long tot=0;
	ResultSet  rs;
        int searchVal[] = {1, 10, 100, 500, 1000, 5000 ,7500, 8000, 9000, 9999};	

	for(int i=0; i<10; i++) {
		start = System.nanoTime();
                if (flag)
                    stmt.setInt(1, searchVal[i]);
                else
                    stmt.setString(1, "Value" +searchVal[i]);
		rs = stmt.executeQuery();
		recordCount=0;
		if(rs.next())
		{
		   recordCount++;
		}
		rs.close();
		con.commit();
		end = System.nanoTime();
	        if(recordCount != 1)
		{
		   System.out.println("No of records for Q1: "+ recordCount );
		   return 0;
		}

		curr = end - start;
		tot = tot + curr;
		count++;
	}

	stmt.close();
	return (int)tot/10/1000;
   }	

   public static int onePerSel(Connection con) throws Exception
   {
          PreparedStatement stmt = null;
	
	  String stmtStr;
          String buf= "SELECT unique1, unique2, stringu1 from big1 where unique1 between ? and ?;"; 
          stmtStr= buf;
          stmt = con.prepareStatement(stmtStr);
          int count =0, recordCount=0;
          int ret =0;
          long start =0, end =0, curr =0;
          long tot =0;
          ResultSet rs;
          int searchVal[] = {1, 5, 10, 50, 100, 500, 1000, 5000 ,7500, 9500};	
          for (int i =0 ; i< 10 ; i++) {
             start = System.nanoTime();
             stmt.setInt(1, searchVal[i]);
             stmt.setInt(2, searchVal[i] +99);
	     rs = stmt.executeQuery();
             recordCount=0;
             while (rs.next())
             {
                 recordCount++;
             }
            
	     rs.close();
             con.commit();
             end = System.nanoTime();
             
	     
	     if (recordCount!= 100) 
             {
                 System.out.println("No. of records for Q2: "+recordCount);
                 return 0;
             }
             curr = end-start;
             tot = tot + curr;
             count++;

         }
         stmt.close();
         return (int)tot/10/1000;
   }
   
// aggregate
public static int aggregate(Connection con, int val)throws Exception
{
	PreparedStatement stmt = null;
	String stmtStr="";
	if(val==1)
	{
	    String buf = "SELECT MIN(unique1) from big1;";
	    stmtStr = buf;
	}
        else if (val ==2)
        {
	    String buf = "SELECT SUM(unique1) from big1;";
	    stmtStr = buf;
        }
	stmt = con.prepareStatement(stmtStr);
	int count = 0, recordCount;
	int ret = 0;
	long start = 0,end = 0,curr = 0;
	long tot = 0;
	ResultSet rs;
		
	for(int i=0;i<10;i++){
		start = System.nanoTime();
		rs = stmt.executeQuery();
		recordCount = 0;
		if(rs.next())
		{
	   	    recordCount++;
		}
		
		rs.close();
		con.commit();
		end = System.nanoTime();

		if(recordCount !=1) 
		{
			System.out.println("No. of records for Q4-7(" + val +" ): " + recordCount);
			return 0;
		}
		curr = end - start;
		tot = tot + curr;
		count++;
	}
	stmt.close();
	return (int)tot/10/1000;
   }


  // DML statement
  public static int dmlstatement(Connection con, int val)throws Exception
  {
	PreparedStatement stmt = null;
	String stmtStr="";
	if(val==1)
	{
		String buf = "insert into big1 values(?,?,0,2,0,10,50,688,1950,4950,9950,1,100,'MXXXXXXXXXXXXXXXXXXXXXXXXXGXXXXXXXXXXXXXXXXXXXXXXXXC','GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO');";
		stmtStr = buf;
	}
	else if(val==2)
	{
	    String buf = "UPDATE big1 SET two=1 WHERE unique1=?;";
	    stmtStr = buf;
	}
	else
	{
	    String buf = "DELETE FROM big1 WHERE unique1=?;";
	    stmtStr = buf;
	}
	    
	stmt = con.prepareStatement(stmtStr);
	int count = 0, recordCount=0;
	int ret = 0;
	long start = 0,end = 0,curr = 0;
	long tot = 0;
	for(int i=0; i<100; i++){
                stmt.setInt(1, 10000+i);
                if (val ==1) stmt.setInt(2, 10000+i);
		start = System.nanoTime();
		ret = stmt.executeUpdate();
		if(ret!=1) return 1;
							
		con.commit();
		end = System.nanoTime();
		curr = end - start;
                tot = tot + curr;
		count++;
        }	
	stmt.close();
	return (int)tot/100/1000;
  }

// Joining
public static int joining(Connection con,int val)throws Exception
{
	PreparedStatement stmt = null;
	String stmtStr= null;
	if(val==1)
	{
	    String buf = "SELECT big1.unique1, big1.unique2, small.unique1, small.stringu1 FROM small,big1 WHERE big1.unique1=small.unique1 AND small.unique1=?;";
	    stmtStr = buf;
	}
	else if(val==2)
	{
	    String buf = "SELECT small.unique1, big1.unique1, big2.unique1, small.stringu1, big1.unique2, big2.unique2 FROM big1, big2, small WHERE small.unique1=big1.unique1 AND big1.unique1=big2.unique1 AND big1.unique1 = ?;";
	    stmtStr=buf;
	}
	
        stmt  = con.prepareStatement(stmtStr);
	int count=0,recordCount=0,ret=0;
	long start=0,end=0,curr=0;
	long tot=0;
	ResultSet rs;
        int searchVal[] = {1, 5, 10, 50, 100, 250, 500, 750, 900, 999};	
	for(int i=0;i<10;i++)
	{
                recordCount =0;
		start = System.nanoTime();
                stmt.setInt(1, searchVal[i]);
		rs = stmt.executeQuery();
		if(rs.next())
		{
                    //System.out.println("Record:"+ rs.getInt(1)+ " "+ rs.getInt(2)+" " +rs.getInt(3)+ " "+ rs.getString(4));
		    recordCount++;
		}
		rs.close();
		con.commit();
		end=System.nanoTime();
		if(recordCount!=1)
		{
		   System.out.println("No. of records Join: "+recordCount);
		   return 0;
		}
		curr = end - start;
		tot = tot + curr;
		count++;
	}
	stmt.close();
	return (int)tot/10/1000;
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
	  
          int timeTaken[][] = new int[15][3];
	  int ins=1,upd=2,del=3;// function parameter
	  int min=1, sum=2;// function parameter

         
	  timeTaken[0][0] = singleTuple(con, true);
	  timeTaken[1][0] = onePerSel(con);
	  timeTaken[2][0] = aggregate(con,min);
	  timeTaken[3][0] = aggregate(con,sum);
	  timeTaken[4][0] = dmlstatement(con,ins);
	  timeTaken[5][0] = dmlstatement(con,upd);
	  timeTaken[6][0] = dmlstatement(con,del);
	  timeTaken[7][0] = joining(con,1);
	  timeTaken[8][0] = joining(con,2);
	  timeTaken[9][0] = singleTuple(con, false);
          System.out.println("Finished no index queries");

	  //create index
	  try{
	      cStmt.execute("CREATE INDEX idx1 ON big1(unique1) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx2 ON big2(unique1) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx3 ON small(unique1) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx4 ON big1(stringu1) HASH");
	      cStmt.close();
              con.commit();
          }catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}
	  timeTaken[0][1] = singleTuple(con, true);
	  timeTaken[1][1] = 0;
	  timeTaken[2][1] = 0;
	  timeTaken[3][1] = 0;
	  timeTaken[4][1] = dmlstatement(con,ins);
	  timeTaken[5][1] = dmlstatement(con,upd);
	  timeTaken[6][1] = dmlstatement(con,del);
	  timeTaken[7][1] = joining(con,1);
	  timeTaken[8][1] = joining(con,2);
	  timeTaken[9][1] = singleTuple(con, false);
          System.out.println("Finished hash index queries");

	  try{
	      cStmt.execute("DROP INDEX idx1");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx2");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx3");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx4");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx5 ON big1(unique1) TREE");
	      cStmt.execute("CREATE INDEX idx6 ON big2(unique1) TREE");
	      cStmt.execute("CREATE INDEX idx7 ON small(unique1) TREE");
	      cStmt.execute("CREATE INDEX idx8 ON big1(stringu1) TREE");
              con.commit();
          }catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}

	  timeTaken[0][2] = singleTuple(con, true);
	  timeTaken[1][2] = onePerSel(con);
	  timeTaken[2][2] = aggregate(con,min);
	  timeTaken[3][2] = 0;
	  timeTaken[4][2] = dmlstatement(con,ins);
	  timeTaken[5][2] = dmlstatement(con,upd);
	  timeTaken[6][2] = dmlstatement(con,del);
	  timeTaken[7][2] = joining(con,1);
	  timeTaken[8][2] = joining(con,2);
	  timeTaken[9][2] = singleTuple(con, false);
          System.out.println("Finished tree index queries");

	   
	 
	  try{
	      cStmt.execute("DROP INDEX idx5;");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx6;");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx7;");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx8;");
	      cStmt.close();
              con.commit();
          }catch(Exception e ){System.out.println("Error dropping indexes");}

          System.out.println("Wisconsin Benchmark Report:");

	  System.out.println("**********************************************************");
	  System.out.println(" Statement       \t NoIndex\tHash \tTree");
	  System.out.println("**********************************************************");
          System.out.println(" SelectInt 1     \t "+timeTaken[0][0] +" \t \t"+ timeTaken[0][1]+ "   \t"+ timeTaken[0][2]); 
          System.out.println(" SelectStr 1     \t "+timeTaken[9][0] +" \t \t"+ timeTaken[9][1]+ "   \t"+ timeTaken[9][2]); 
          System.out.println(" 1% Sel          \t "+timeTaken[1][0] +" \t \t-   \t"+ timeTaken[1][2]); 

          System.out.println(" Min All         \t "+timeTaken[2][0] +" \t \t-   \t"+ timeTaken[2][2]); 
          System.out.println(" Sum All         \t "+timeTaken[3][0] +" \t \t-   \t-"); 
          System.out.println(" Insert 1        \t "+timeTaken[4][0] +" \t \t"+ timeTaken[4][1]+ "   \t"+ timeTaken[4][2]); 
          System.out.println(" Update 1       \t "+timeTaken[5][0] +" \t \t"+ timeTaken[5][1]+ "   \t"+ timeTaken[5][2]); 
          System.out.println(" Delete 1        \t "+timeTaken[6][0] +" \t \t"+ timeTaken[6][1]+ "   \t"+ timeTaken[6][2]); 
          System.out.println(" Join(10K*1K)1  \t "+timeTaken[7][0] +" \t \t"+ timeTaken[7][1]+ "\t"+ timeTaken[7][2]); 
          System.out.println(" Join(10K*10K*1K)1\t "+timeTaken[8][0] +"\t  \t"+ timeTaken[8][1]+ "\t"+ timeTaken[8][2]); 
	  System.out.println("**********************************************************");

	  con.close();
        }
        catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
       
    }
}
