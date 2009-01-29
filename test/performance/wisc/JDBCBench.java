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
	if(flag)
	{
		String buf = " SELECT * from big1 where unique2=?;";
		stmtStr =  buf;
	}
	else
	{
		String buf = "SELECT * from big1 where unique1=?;";
		stmtStr = buf;
	}
	
	stmt = con.prepareStatement(stmtStr);
	int count=0, recordCount=0;
	int ret =0;
	long start=0, end=0, curr=0;
	long tot=0;
	ResultSet  rs;
	

	for(int i=0; i<=100; i++) {

		stmt.setInt(1,i);
		start = System.nanoTime();
		rs = stmt.executeQuery();
		recordCount=0;
		while(rs.next())
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
	return (int)tot/100/1000;
   }	

   public static int onePerSel(Connection con, boolean flag) throws Exception
   {
          PreparedStatement stmt = null;
          int searchVal = getRandom(9999 - 100);
          int searchValEnd = searchVal+ 99;
          
	
	  String stmtStr;
          if (flag) {
              String buf= "SELECT * from big1 where unique2 between "+ 
                          searchVal + " and "+ searchValEnd+ ";"; 
              stmtStr= buf;
          }else{
              String buf= "SELECT * from big1 where unique1 between "+ 
                          searchVal + " and "+ searchValEnd+ ";"; 
              stmtStr= buf;
          }
          stmt = con.prepareStatement(stmtStr);
          int count =0, recordCount=0;
          int ret =0;
          long start =0, end =0, curr =0;
          long tot =0;
          ResultSet rs;
          for (int i =0 ; i<= 100 ; i++) {
             start = System.nanoTime();
             
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
         return (int)tot/100/1000;
   }
   
// aggregate
public static int aggregate(Connection con, int val, boolean flag)throws Exception
{
	PreparedStatement stmt = null;
	String stmtStr="";
	if(val==1)
	{
            if (flag) {
		String buf = "SELECT MIN(unique2) from big1;";
		stmtStr = buf;
            }else {
		String buf = "SELECT MIN(unique1) from big1;";
		stmtStr = buf;
            }
	}
        else if (val ==2)
        {
            if (flag) {
		String buf = "SELECT SUM(unique2) from big1;";
		stmtStr = buf;
            }else {
		String buf = "SELECT SUM(unique1) from big1;";
		stmtStr = buf;
            }
        }
	else if(val==3)
	{
            if (flag) {
		String buf = "SELECT MIN(unique2) FROM big1 GROUP BY onepercent;";
		stmtStr = buf;
            }else{
		String buf = "SELECT MIN(unique1) FROM big1 GROUP BY onepercent;";
		stmtStr = buf;
            }
	}
	else
	{
            if (flag) {
		String buf = "SELECT SUM(unique2) FROM big1 GROUP BY onepercent;";
		stmtStr = buf;
            }else {
		String buf = "SELECT SUM(unique1) FROM big1 GROUP BY onepercent;";
		stmtStr = buf;
            }
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
		while(rs.next())
		{
			recordCount++;
		}
		
		rs.close();
		con.commit();
		end = System.nanoTime();

		if((val==1 || val ==2) && recordCount !=1) 
		{
			System.out.println("No. of records for Q4-7(" + val +" ): " + recordCount);
			return 0;
		}
		if((val==4 || val==3) && recordCount !=100)
		{
			System.out.println("No. of records for Q4-7("+ val + "): " + recordCount);
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
  public static int dmlstatement(Connection con, int val, boolean flag)throws Exception
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
           if(flag) {
		String buf = "UPDATE big1 SET two=1 WHERE unique2=?;";
		stmtStr = buf;
           }else {
		String buf = "UPDATE big1 SET two=1 WHERE unique1=?;";
		stmtStr = buf;
           }
	}
	else
	{
           if (flag) {
		String buf = "DELETE FROM big1 WHERE unique2=?;";
		stmtStr = buf;
           }else {
		String buf = "DELETE FROM big1 WHERE unique1=?;";
		stmtStr = buf;
           }
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
public static int joining(Connection con,int val, boolean flag)throws Exception
{
	PreparedStatement stmt = null;
	String stmtStr;
	if(val==1)
	{
           if (flag) {
		String buf = "SELECT big1.unique2, big2.unique2 FROM big2,big1 WHERE big1.unique2=big2.unique2 AND big2.unique2=1000;";
		stmtStr = buf;
           }else{
		String buf = "SELECT big1.unique1, big2.unique1 FROM big2,big1 WHERE big1.unique1=big2.unique1 AND big2.unique1=1000;";
		stmtStr = buf;
           }
	}
	else if(val==2)
	{
           if (flag) {
		String buf = "SELECT big1.unique2, big2.unique2 FROM big2,big1 WHERE big1.unique2=big2.unique2 AND big2.unique2>1000;";
		stmtStr = buf;
           }else{
		String buf = "SELECT big1.unique1, big2.unique1 FROM big2,big1 WHERE big1.unique1=big2.unique1 AND big2.unique1>1000;";
		stmtStr = buf;
           }
	}
	else if(val==11)
	{
		String buf = "SELECT * FROM small,big1 WHERE small.unique2=big1.unique2 AND big1.unique2=big2.unique2 AND big1.unique2<1000;";
		stmtStr=buf;
	}
	else if(val==15)
	{
		String buf = "SELECT * FROM big1,big2 WHERE (big1.unique1=big2.unique1) AND (big1.unique2<1000);";
		stmtStr=buf;
	}
	else if(val==16)
	{
		String buf = "SELECT * FROM big1,bprime WHERE big1.unique1=bprime.unique1;";
		stmtStr=buf;
	}
	else
	{
		String buf = "SELECT * FROM small,big1 WHERE (small.unique1=big1.unique1) AND (big1.unique1=big2.unique1) AND (big1.unique1 < 1000);";
		stmtStr=buf;
	}
	
        stmt  = con.prepareStatement(stmtStr);
	int count=0,recordCount=0,ret=0;
	long start=0,end=0,curr=0;
	long tot=0;
	ResultSet rs;
	//for(int i=0;i<=100;i++)
	{
		start = System.nanoTime();
		rs = stmt.executeQuery();
		while(rs.next())
		{
                    //System.out.println("Record: "+ rs.getInt(1)+ " "+ rs.getInt(2));
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
	return (int)tot/1000;
}

// projection
/*public static  int projection(Connection con, boolean flag)throws Exception
{
	PreparedStatement  stmt = null;
	
	String stmtStr;
	if(flag)
	{
	   String buf = "SELECT DISTINCT two,four,ten,twenty,onepercent,string4 from big1;";
	   stmtStr = buf;
        }
	else
	{
	    String buf = "SELECT DISTINCT two,four,ten,twenty,onepercent,tenpercent,twentypercent,fiftypercent,unique3,evenonepercent,oddonepercent,stringu1,stringu2,string4 FROM big1;";
	    stmtStr = buf;
        }		
		stmt = con.prepareStatement(stmtStr);
		int count = 0, recordCount;
		int ret = 0;
		long start = 0, end = 0, curr = 0;
		long tot =0;
		ResultSet rs;
		for(int i=0 ; i<=100 ; i++)
		{
			start = System.nanoTime();
			rs = stmt.executeQuery();
			recordCount = 0;
			while(rs.next())
			{
				recordCount++;
			}

			rs.close();
			con.commit();
			end = System.nanoTime();
			
			if((flag && recordCount !=1000) || (!flag && recordCount !=10000)) 
			{
			   System.out.println("No. of records returned is around for Q2" + recordCount);
			
			  return 0;
		        }

			curr = end - start;
			tot = tot + curr;
			count++;
		}

		stmt.close();
		return (int)tot/100/1000;

}*/
// second query
public static  int tenPerSel(Connection con, boolean flag)throws Exception
{
	PreparedStatement  stmt = null;
	int searchVal = getRandom(9999 - 1000);
	int searchValEnd = searchVal + 999;
	
	String stmtStr;
	if(flag)
	{
	   String buf = "SELECT * from big1 where unique2 between "+ searchVal + " and "+ searchValEnd + ";";
	   stmtStr = buf;
        }
	else
	{
	    String buf = "SELECT * from big1 where unique1 between "+searchVal +" and "+ searchValEnd + ";";
		stmtStr = buf;
        }		
		stmt = con.prepareStatement(stmtStr);
		int count = 0, recordCount;
		int ret = 0;
		long start = 0, end = 0, curr = 0;
		long tot =0;
		ResultSet rs;
		for(int i=0 ; i<=100 ; i++)
		{
			start = System.nanoTime();
			rs = stmt.executeQuery();
			recordCount = 0;
			while(rs.next())
			{
				recordCount++;
			}

			rs.close();
			con.commit();
			end = System.nanoTime();
			
			
			if(recordCount != 1000)
			{
			  System.out.println("No. of records for Q3: " + recordCount);
			  return 0;
		        }

			curr = end - start;
			tot = tot + curr;
			count++;
		}

		stmt.close();
		return (int)tot/100/1000;
  }		


//*****************************************************
public static void main(String[] args) 

   {
     int flag=1;
     if (args.length == 1)
     { 
         if (args[0].equals("csql")) flag=1;
         else if (args[0].equals("mysql")) flag=2;
         else {
             System.out.println("Valid values: csql or mysql");
             return;
         }
     }
     try
     {
          Connection con = null;
          if (flag == 1) {
              Class.forName("csql.jdbc.JdbcSqlDriver");
              con = DriverManager.getConnection("jdbc:csql", "root", "manager");
          }else if (flag == 2) {
              Class.forName("com.mysql.jdbc.Driver");
              con = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "");
          }
          con.setAutoCommit(false);
          con.setTransactionIsolation(Connection.TRANSACTION_READ_UNCOMMITTED);
          Statement cStmt = con.createStatement();
	  
          int timeTaken[][] = new int[15][3];
	  int ins=1,upd=2,del=3;// function parameter
	  int min=1, sum=2, ming=3, sumg=4;// function parameter

          
	  timeTaken[0][0] = singleTuple(con,true);
	  timeTaken[1][0] = onePerSel(con, true);
	  timeTaken[2][0] = tenPerSel(con,true);
	  timeTaken[3][0] = aggregate(con,min, true);
	  timeTaken[4][0] = aggregate(con,sum, true);
	  timeTaken[5][0] = aggregate(con,ming, true);
	  timeTaken[6][0] = aggregate(con,sumg, true);

	  timeTaken[7][0] = dmlstatement(con,ins, true);
	  //timeTaken[8][0] = dmlstatement(con,upd, true);
	  timeTaken[9][0] = dmlstatement(con,del, true);

	  timeTaken[10][0] = joining(con,1, true);
	  //timeTaken[11][0] = joining(con,2, true);
          System.out.println("Finished no index queries");
	  //create index
	  try{
            if (flag ==1) {
	      cStmt.execute("CREATE INDEX idx4 ON big1(unique2) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx3 ON big1(unique1) TREE");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx6 ON big2(unique2) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx5 ON big2(unique1) TREE");
	      cStmt.close();
            }else if (flag ==2) {
	      cStmt.execute("CREATE INDEX mysqlc1 USING HASH ON big1(unique2)");
	      cStmt.execute("CREATE INDEX mysqlc2 USING BTREE ON big1(unique1)");
	      cStmt.execute("CREATE INDEX mysqlc3 USING HASH ON big2(unique2)");
	      cStmt.execute("CREATE INDEX mysqlc4 USING BTREE ON big2(unique1)");
	      cStmt.close();
            }
          }catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}

	  timeTaken[0][1] = singleTuple(con,true);
	  timeTaken[1][1] = onePerSel(con, true);
	  timeTaken[2][1] = tenPerSel(con,true);
	  timeTaken[3][1] = aggregate(con,min, true);
	  timeTaken[4][1] = aggregate(con,sum, true);
	  timeTaken[5][1] = aggregate(con,ming, true);
	  timeTaken[6][1] = aggregate(con,sumg, true);
	  timeTaken[7][1] = dmlstatement(con,ins, true);
	  //timeTaken[8][1] = dmlstatement(con,upd, true);
	  timeTaken[9][1] = dmlstatement(con,del, true);
	  timeTaken[10][1] = joining(con,1, true);
	  //timeTaken[11][1] = joining(con,2, true);
          System.out.println("Finished hash index queries");

	  timeTaken[0][2] = singleTuple(con,false);
	  timeTaken[1][2] = onePerSel(con, false);
	  timeTaken[2][2] = tenPerSel(con,false);
	  timeTaken[3][2] = aggregate(con,min, false);
	  timeTaken[4][2] = aggregate(con,sum, false);
	  timeTaken[5][2] = aggregate(con,ming, false);
	  timeTaken[6][2] = aggregate(con,sumg, false);
	  timeTaken[7][2] = dmlstatement(con,ins, false);
	  //timeTaken[8][2] = dmlstatement(con,upd, false);
	  timeTaken[9][2] = dmlstatement(con,del, false);
	  timeTaken[10][2] = joining(con,1, false);
	  //timeTaken[11][2] = joining(con,2, false);
          System.out.println("Finished tree index queries");

	   
	  int join1=1;
	  //int q18 = projection(con,true);
	  //System.out.println("18\t1%Proj Sel\t-\tY\tY\t"+q18);

	  //int q19 = projection(con,false);
	  //System.out.println("19\t100%Proj Sel\t-\tY\tY\t"+q19);*/
	  
	  try{
            if (flag ==1) {
	      cStmt.execute("DROP INDEX idx4;");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx3;");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx6;");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx5;");
	      cStmt.close();
            } else if (flag ==2) {
	      cStmt.execute("DROP INDEX mysqlc1 on big1");
	      cStmt.close();
	      cStmt.execute("DROP INDEX mysqlc2 on big1");
	      cStmt.close();
	      cStmt.execute("DROP INDEX mysqlc3 on big2");
	      cStmt.close();
	      cStmt.execute("DROP INDEX mysqlc4 on big2");
	      cStmt.close();
            }
          }catch(Exception e ){System.out.println("Error dropping indexes");}
          System.out.println("Wisconsin Benchmark Report:");

	  System.out.println("**********************************************************");
	  System.out.println(" Statement\t NoIndex\t  Hash \t Tree");
	  System.out.println("**********************************************************");
          System.out.println(" 1 Tuple         \t "+timeTaken[0][0] +" \t \t"+ timeTaken[0][1]+ "   \t"+ timeTaken[0][2]); 
          System.out.println(" 1% Sel          \t "+timeTaken[1][0] +" \t \t"+ timeTaken[1][1]+ "   \t"+ timeTaken[1][2]); 
          System.out.println(" 10% Sel         \t "+timeTaken[2][0] +" \t \t"+ timeTaken[2][1]+ "   \t"+ timeTaken[2][2]); 

          System.out.println(" Min All         \t "+timeTaken[3][0] +" \t \t"+ timeTaken[3][1]+ "   \t"+ timeTaken[3][2]); 
          System.out.println(" Sum All         \t "+timeTaken[4][0] +" \t \t"+ timeTaken[4][1]+ "   \t"+ timeTaken[4][2]); 
          System.out.println(" Min Grp(100)    \t "+timeTaken[5][0] +" \t \t"+ timeTaken[5][1]+ "\t"+ timeTaken[5][2]); 
          System.out.println(" Sum Grp(100)    \t "+timeTaken[6][0] +" \t \t"+ timeTaken[6][1]+ "\t"+ timeTaken[6][2]); 

          System.out.println(" Insert 1        \t "+timeTaken[7][0] +" \t \t"+ timeTaken[7][1]+ "   \t"+ timeTaken[7][2]); 
          System.out.println(" Update 1       \t "+timeTaken[8][0] +" \t \t"+ timeTaken[8][1]+ "   \t"+ timeTaken[8][2]); 
          System.out.println(" Delete 1        \t "+timeTaken[9][0] +" \t \t"+ timeTaken[9][1]+ "   \t"+ timeTaken[9][2]); 
          System.out.println(" Join(10K*10K)1  \t "+timeTaken[10][0] +" \t \t"+ timeTaken[10][1]+ "\t"+ timeTaken[10][2]); 
          System.out.println(" Join(10K*10K)1K \t "+timeTaken[11][0] +" \t \t"+ timeTaken[11][1]+ "\t"+ timeTaken[11][2]); 
	  System.out.println("**********************************************************");

	  con.close();
        }
        catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
       
    }
}
