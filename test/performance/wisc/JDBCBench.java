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
		String buf = " SELECT unique1, unique2, stringu1, stringu2 from big1 where unique2=?;";
		stmtStr =  buf;
	}
	else
	{
		String buf = "SELECT unique1, unique2, stringu1, stringu2 from big1 where unique1=?;";
		stmtStr = buf;
	}
	
	stmt = con.prepareStatement(stmtStr);
	int count=0, recordCount=0;
	int ret =0;
	long start=0, end=0, curr=0;
	long tot=0;
	ResultSet  rs;
	

	for(int i=1000; i<=1100; i++) {
		start = System.nanoTime();
                stmt.setInt(1, i);
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
	return (int)tot/100/1000;
   }	

   public static int onePerSel(Connection con, boolean flag) throws Exception
   {
          PreparedStatement stmt = null;
	
	  String stmtStr;
          if (flag) {
              String buf= "SELECT unique1, unique2, stringu1 from big1 where unique2 between 1 and 100;"; 
              stmtStr= buf;
          }else{
              String buf= "SELECT unique1, unique2, stringu1 from big1 where unique1 between 1 and 100;"; 
              stmtStr= buf;
          }
          stmt = con.prepareStatement(stmtStr);
          int count =0, recordCount=0;
          int ret =0;
          long start =0, end =0, curr =0;
          long tot =0;
          ResultSet rs;
          for (int i =0 ; i<= 10 ; i++) {
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
         return (int)tot/10/1000;
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
	String stmtStr= null;
	if(val==1)
	{
           if (flag) {
		String buf = "SELECT big1.unique1, big1.unique2, big2.unique2, big2.stringu1  FROM big2,big1 WHERE big1.unique2=big2.unique2 AND big2.unique2=1000;";
		stmtStr = buf;
           }else{
		String buf = "SELECT big1.unique1, big1.unique2, big2.unique1, big2.stringu1 FROM big2,big1 WHERE big1.unique1=big2.unique1 AND big2.unique1=1000;";
		stmtStr = buf;
           }
	}
	else if(val==2)
	{
           if (flag) {
		String buf = "SELECT big1.unique1, big1.unique2, big2.unique2, big2.stringu1 FROM big2,big1 WHERE big1.unique2=big2.unique2 AND big2.unique2<100;";
		stmtStr = buf;
           }else{
		String buf = "SELECT big1.unique1, big1.unique2, big2.unique1, big2.stringu1 FROM big2,big1 WHERE big1.unique1=big2.unique1 AND big2.unique1<100;";
		stmtStr = buf;
           }
	}
	else if(val==3)
	{
           if (flag) {
		String buf = "SELECT small.unique2, big1.unique2, big2.unique2, small.stringu1, big1.unique1, big2.unique1 FROM big1, big2, small WHERE small.unique2=big1.unique2 AND big1.unique2=big2.unique2 AND big1.unique2 = 100;";
		stmtStr=buf;
           }else{
		String buf = "SELECT small.unique1, big1.unique1, big2.unique1, small.stringu1, big1.unique2, big2.unique2 FROM big1, big2, small WHERE small.unique1=big1.unique1 AND big1.unique1=big2.unique1 AND big1.unique1 = 100;";
		stmtStr=buf;
           }
	}
	
        stmt  = con.prepareStatement(stmtStr);
	int count=0,recordCount=0,ret=0;
	long start=0,end=0,curr=0;
	long tot=0;
	ResultSet rs;
	//for(int i=0;i<=10;i++)
	{
		start = System.nanoTime();
		rs = stmt.executeQuery();
		if(rs.next())
		{
                    //System.out.println("Record:"+ rs.getInt(1)+ " "+ rs.getInt(2)+" " +rs.getInt(3)+ " "+ rs.getString(4));
		    recordCount++;
		}
		rs.close();
		con.commit();
		end=System.nanoTime();
		if(val ==1 &&  recordCount!=1)
		{
		   System.out.println("No. of records Join: "+recordCount);
		   return 0;
		}
		if(val ==2 &&  recordCount!=100)
		{
		   System.out.println("Stmt: "+stmtStr);
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
	
	String stmtStr;
	if(flag)
	{
	   String buf = "SELECT unique1, unique2, stringu1 from big1 where unique2 between 1 and 1000;";
	   stmtStr = buf;
        }
	else
	{
	    String buf = "SELECT unique1, unique2, stringu1 from big1 where unique1 between 1 and 1000;";
		stmtStr = buf;
        }		
		stmt = con.prepareStatement(stmtStr);
		int count = 0, recordCount;
		int ret = 0;
		long start = 0, end = 0, curr = 0;
		long tot =0;
		ResultSet rs;
		for(int i=0 ; i<=10 ; i++)
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
		return (int)tot/10/1000;
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
          con.setTransactionIsolation(Connection.TRANSACTION_READ_COMMITTED);
          Statement cStmt = con.createStatement();
	  
          int timeTaken[][] = new int[15][3];
	  int ins=1,upd=2,del=3;// function parameter
	  int min=1, sum=2, ming=3, sumg=4;// function parameter

         
	  timeTaken[0][0] = singleTuple(con,false);
	  timeTaken[1][0] = onePerSel(con, false);
	  timeTaken[2][0] = tenPerSel(con,false);
	  timeTaken[3][0] = aggregate(con,min, false);
	  timeTaken[4][0] = aggregate(con,sum, false);
	  timeTaken[5][0] = aggregate(con,ming, false);
	  timeTaken[6][0] = aggregate(con,sumg, false);
	  timeTaken[7][0] = dmlstatement(con,ins, false);
	  //timeTaken[8][0] = dmlstatement(con,upd, false);
	  timeTaken[9][0] = dmlstatement(con,del, false);
	  timeTaken[10][0] = joining(con,1, false);
	  //timeTaken[11][0] = joining(con,2, false);
	  timeTaken[12][0] = joining(con,3, false);
          System.out.println("Finished no index queries");

	  //create index
	  try{
            if (flag ==1) {
	      cStmt.execute("CREATE INDEX idx1 ON big1(unique1) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx2 ON big2(unique1) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx3 ON small(unique1) HASH");
	      cStmt.close();
              con.commit();
            }else if (flag ==2) {
	      cStmt.execute("CREATE INDEX mysqld1 USING HASH ON big1(unique1)");
	      cStmt.execute("CREATE INDEX mysqld2 USING HASH ON big2(unique1)");
	      cStmt.execute("CREATE INDEX mysqld3 USING HASH ON small(unique1)");
              con.commit();
            }
          }catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}
	  timeTaken[0][1] = singleTuple(con,false);
	  timeTaken[1][1] = 0;
	  timeTaken[2][1] = 0;
	  timeTaken[3][1] = 0;
	  timeTaken[4][1] = 0;
	  timeTaken[5][1] = 0;
	  timeTaken[6][1] = 0;
	  timeTaken[7][1] = dmlstatement(con,ins, false);
	  //timeTaken[8][1] = dmlstatement(con,upd, false);
	  timeTaken[9][1] = dmlstatement(con,del, false);
	  timeTaken[10][1] = joining(con,1, false);
	  //timeTaken[11][1] = joining(con,2, false);
	  timeTaken[12][1] = joining(con,3, false);
          System.out.println("Finished hash index queries");


	  try{
            if (flag ==1) {
	      cStmt.execute("DROP INDEX idx1");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx2");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx3");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx4 ON big1(unique1) TREE");
	      cStmt.execute("CREATE INDEX idx5 ON big2(unique1) TREE");
	      cStmt.execute("CREATE INDEX idx6 ON small(unique1) TREE");
              con.commit();
            }else if (flag ==2) {
	      cStmt.execute("DROP INDEX mysqld1 on big1");
	      cStmt.execute("DROP INDEX mysqld2 on big2");
	      cStmt.execute("DROP INDEX mysqld3 on small");
	      cStmt.execute("CREATE INDEX mysqld4 USING BTREE ON big1(unique1)");
	      cStmt.execute("CREATE INDEX mysqld5 USING BTREE ON big2(unique1)");
	      cStmt.execute("CREATE INDEX mysqld6 USING BTREE ON small(unique1)");
              con.commit();
            }
          }catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}

	  timeTaken[0][2] = singleTuple(con,false);
	  timeTaken[1][2] = onePerSel(con, false);
	  timeTaken[2][2] = tenPerSel(con,false);
	  timeTaken[3][2] = aggregate(con,min, false);
	  timeTaken[4][2] = 0;
	  timeTaken[5][2] = 0;
	  timeTaken[6][2] = 0;
	  timeTaken[7][2] = dmlstatement(con,ins, false);
	  //timeTaken[8][2] = dmlstatement(con,upd, false);
	  timeTaken[9][2] = dmlstatement(con,del, false);
	  timeTaken[10][2] = joining(con,1, false);
	  //timeTaken[11][2] = joining(con,2, false);
	  timeTaken[12][2] = joining(con,3, false);
          System.out.println("Finished tree index queries");

	   
	 
	  try{
            if (flag ==1) {
	      cStmt.execute("DROP INDEX idx4;");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx5;");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx6;");
	      cStmt.close();
              con.commit();
            } else if (flag ==2) {
	      cStmt.execute("DROP INDEX mysqld4 on big1");
	      cStmt.execute("DROP INDEX mysqld5 on big2");
	      cStmt.execute("DROP INDEX mysqld6 on small");
              con.commit();
            }
          }catch(Exception e ){System.out.println("Error dropping indexes");}

          System.out.println("Wisconsin Benchmark Report:");

	  System.out.println("**********************************************************");
	  System.out.println(" Statement       \t NoIndex\tHash \tTree");
	  System.out.println("**********************************************************");
          System.out.println(" 1 Tuple         \t "+timeTaken[0][0] +" \t \t"+ timeTaken[0][1]+ "   \t"+ timeTaken[0][2]); 
          System.out.println(" 1% Sel          \t "+timeTaken[1][0] +" \t \t-   \t"+ timeTaken[1][2]); 
          System.out.println(" 10% Sel         \t "+timeTaken[2][0] +" \t \t-   \t"+ timeTaken[2][2]); 

          System.out.println(" Min All         \t "+timeTaken[3][0] +" \t \t-   \t"+ timeTaken[3][2]); 
          System.out.println(" Sum All         \t "+timeTaken[4][0] +" \t \t-   \t-"); 
          System.out.println(" Min Grp(100)    \t "+timeTaken[5][0] +" \t \t-   \t-");
          System.out.println(" Sum Grp(100)    \t "+timeTaken[6][0] +" \t \t-   \t-");

          System.out.println(" Insert 1        \t "+timeTaken[7][0] +" \t \t"+ timeTaken[7][1]+ "   \t"+ timeTaken[7][2]); 
          System.out.println(" Update 1       \t "+timeTaken[8][0] +" \t \t"+ timeTaken[8][1]+ "   \t"+ timeTaken[8][2]); 
          System.out.println(" Delete 1        \t "+timeTaken[9][0] +" \t \t"+ timeTaken[9][1]+ "   \t"+ timeTaken[9][2]); 
          System.out.println(" Join(10K*10K)1  \t "+timeTaken[10][0] +" \t \t"+ timeTaken[10][1]+ "\t"+ timeTaken[10][2]); 
//          System.out.println(" Join(10K*10K)100 \t "+timeTaken[11][0] +"  \t"+ timeTaken[11][1]+ "\t"+ timeTaken[11][2]); 
          System.out.println(" Join(10K*10K*1K)1\t "+timeTaken[12][0] +"\t  \t"+ timeTaken[12][1]+ "\t"+ timeTaken[12][2]); 
	  System.out.println("**********************************************************");

	  con.close();
        }
        catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
       
    }
}
