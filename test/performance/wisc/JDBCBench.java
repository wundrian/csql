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
	    String buf = "SELECT unique1, unique2, stringu1, stringu2 from big1 where unique1=?";
	    stmtStr = buf;
        }else {
	    String buf = "SELECT unique1, unique2, stringu1, stringu2 from big1 where stringu1=?";
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
		   System.out.println("No of records for:"+ stmtStr +""+ recordCount );
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
          String buf= "SELECT unique1, unique2, stringu1 from big1 where unique1 between ? and ?"; 
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
                 System.out.println("No. of records for:"+ stmtStr +" "+recordCount);
                 return 0;
             }
             curr = end-start;
             tot = tot + curr;
             count++;

         }
         stmt.close();
         return (int)tot/10/1000;
   }

//Order By
public static int orderby(Connection con) throws Exception
   {
          PreparedStatement stmt = null;
          String stmtStr="";
          String buf= "SELECT two, four, ten, twenty, onepercent, string4 from big1 where unique1 between ? and ? order by unique1";
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
                 System.out.println("No. of records for"+ stmtStr +" "+recordCount);
                 return 0;
             }
             curr = end-start;
             tot = tot + curr;
             count++;

         }
         stmt.close();
         return (int)tot/10/1000;
   }

   
//DISTINCT
public static int distinct(Connection con) throws Exception
   {
          PreparedStatement stmt = null;
          String stmtStr="";
          //String buf = "SELECT DISTINCT two, four, ten, twenty, onepercent, string4 FROM big1;";
          String buf = "SELECT DISTINCT onepercent FROM big1";
          stmtStr=buf;
          stmt = con.prepareStatement(stmtStr);      
          int count =0, recordCount=0;
          int ret =0;
          long start =0, end =0, curr =0;
          long tot =0;
          ResultSet rs;
          for (int i =0 ; i< 10 ; i++) {
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

             if (recordCount!= 100)
             {
                 System.out.println("No. of records for" + stmtStr + " "+recordCount);
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
public static int aggregate(Connection con, int val,boolean flag)throws Exception
{
	PreparedStatement stmt = null;
	String stmtStr="";
        if(val==1 && !flag)
        {
            String buf = "SELECT MIN(unique1) from big1";
            stmtStr = buf;
        }
        else if(val==1 && flag)
        {

            String buf = "SELECT MIN(unique1) from big1 group by onepercent";
            stmtStr = buf;

        }
 	  
        if(val==2 && !flag)
	{
            String buf = "SELECT MAX(unique1) from big1";
	    stmtStr = buf;
	}
        else if(val==2 && flag)
        {

            String buf = "SELECT MAX(unique1) from big1 group by onepercent";
            stmtStr = buf;

        }
        else if(val==3 && !flag)
        {

            String buf = "SELECT SUM(unique1) from big1";
            stmtStr = buf;
        } 
        else if (val==3 && flag)
        {

            String buf = "SELECT SUM(unique1) from big1 group by onepercent";
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
		while(rs.next())
		{
	   	    recordCount++;
		}
		
		rs.close();
		con.commit();
		end = System.nanoTime();

		if(!flag && recordCount !=1) 
		{
                    System.out.println("No. of records for "+ stmtStr + " "+recordCount);
                    return 0;
		}else if (flag && recordCount !=100)
		{
                    System.out.println("No. of records for "+ stmtStr + " "+  recordCount);
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
		String buf = "insert into big1 values(?,?,0,2,0,10,50,688,1950,4950,9950,1,100,'MXXXXXXXXXXXXXXXXXXXXXXXXXGXXXXXXXXXXXXXXXXXXXXXXXXC','GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO')";
		stmtStr = buf;
	}
	else if(val==2)
	{
	    String buf = "UPDATE big1 SET two=1 WHERE unique1=?";
	    stmtStr = buf;
	}
	else
	{
	    String buf = "DELETE FROM big1 WHERE unique1=?";
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
	if(val==1 )
        {
            String buf = "SELECT big1.unique1, big1.unique2, small.unique1, small.stringu1 FROM big1,small WHERE big1.unique2=small.unique1 AND big1.unique1=?";
            stmtStr = buf;
        }
        else if(val==2)
	{
	    String buf = "SELECT small.unique1, big1.unique1, big2.unique1, small.stringu1, big1.unique2, big2.unique2 FROM big1, big2, small WHERE big1.unique2 = small.unique1 AND big1.unique2=big2.unique1 AND big1.unique1 = ?";
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
		while(rs.next())
		{
                  //  System.out.println("Record:"+ rs.getInt(1)+ " "+ rs.getInt(2)+" " +rs.getInt(3)+ " "+ rs.getString(4));
		    recordCount++;
		}
		rs.close();
		con.commit();
		end=System.nanoTime();
		if(recordCount!=1)
		{
		   System.out.println("No. of records in"+ stmtStr +" "+ recordCount);
		   return 0;
		}

		curr = end - start;
		tot = tot + curr;
		count++;
	}
	stmt.close();
	return (int)tot/10/1000;
}

static long joinCondition(Connection con,int val)throws Exception

{
        PreparedStatement stmt = null;
        String stmtStr= null;
        if(val==1 )
        {
           String buf = "SELECT big1.unique1, big1.unique2, small.unique1, small.stringu1 FROM big1,small WHERE big1.unique2=small.unique1 AND big1.unique1 > ? AND big1.unique1 <= ?";
            stmtStr = buf;
        }
        else if(val==2)
        {
            String buf = "SELECT small.unique1, big1.unique1, big2.unique1, small.stringu1, big1.unique2, big2.unique2 FROM big1, big2, small WHERE big1.unique2=small.unique1 AND big1.unique2=big2.unique1 AND big1.unique1 > ? and big1.unique1 <= ?";
            stmtStr=buf;
        }

        stmt  = con.prepareStatement(stmtStr);
        int count=0,recordCount=0,ret=0;
        long  start=0,end=0,curr=0;
        long  tot=0;
        ResultSet rs;
        int searchVal[] = {1, 5, 10, 50, 100, 200, 250, 500, 750, 800};
        for(int i=0;i<10;i++)
        {
                recordCount =0;
                start = System.nanoTime();
                stmt.setInt(1, searchVal[i]);
                stmt.setInt(2, searchVal[i]+100);
                rs = stmt.executeQuery();
                while(rs.next())
                {
                    //System.out.println("Record:"+ rs.getInt(1)+ " "+ rs.getInt(2)+" " +rs.getInt(3)+ " "+ rs.getString(4));
                    recordCount++;
                }
                rs.close();
                con.commit();
                end=System.nanoTime();
                if(recordCount!=100)
                {
                   System.out.println("No. of records in"+ stmtStr +" "+ recordCount);
                   return 0;
                }

                curr = end - start;
                tot = tot + curr;
                count++;
        }
        stmt.close();
        return tot/10/1000;
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
         System.out.println("Usage: java JDBCBench <DBNAME> <username> <password>");
         return;
     }
     try
     {
          Connection con = null;
          if (flag == 1) {
              Class.forName("csql.jdbc.JdbcSqlDriver");
              con = DriverManager.getConnection("jdbc:csql", args[1], args[2]);
          } else if (flag == 2) {
              Class.forName("com.mysql.jdbc.Driver");
              con = DriverManager.getConnection("jdbc:mysql://localhost/test", args[1], args[2]);
          } else if (flag == 3) {
              Class.forName("org.postgresql.Driver");
              con = DriverManager.getConnection("jdbc:postgresql://localhost/test", args[1], args[2]);
          } else if (flag == 4) {
              Class.forName("oracle.jdbc.driver.OracleDriver");
              con = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:XE", args[1], args[2]);
          } else if (flag == 5) {
              Class.forName("com.sybase.jdbc3.jdbc.SybDataSource");
              con = DriverManager.getConnection("jdbc:sybase:Tds:localhost:4112", args[1], args[2]);
          } 
          con.setAutoCommit(false);
          con.setTransactionIsolation(Connection.TRANSACTION_READ_COMMITTED);
          Statement cStmt = con.createStatement();
	  
          long timeTaken[][] = new long[20][3];
	  int ins=1,upd=2,del=3;// function parameter
	  int min=1, max=2,sum=3;// function parameter

         
	  timeTaken[0][0] = singleTuple(con, true);
	  timeTaken[1][0] = singleTuple(con, false);

	  timeTaken[2][0] = onePerSel(con);
	  timeTaken[3][0] = aggregate(con,min,false);
          timeTaken[4][0] = aggregate(con,min,true);
          timeTaken[5][0] = aggregate(con,max,false);
          timeTaken[6][0] = aggregate(con,max,true);

	  timeTaken[7][0] = aggregate(con,sum,false);
          timeTaken[8][0] = aggregate(con,sum,true);
          timeTaken[9][0] = distinct(con);
          timeTaken[10][0] = orderby(con);

	  timeTaken[11][0] = dmlstatement(con,ins);
	  timeTaken[12][0] = dmlstatement(con,upd);
	  timeTaken[13][0] = dmlstatement(con,del);
	  timeTaken[14][0] = joining(con,1);
	  timeTaken[15][0] = joining(con,2);
          timeTaken[16][0] = joinCondition(con,1);
          timeTaken[17][0] = joinCondition(con,2);
          System.out.println("Finished no index queries");
          try{
              if(flag == 1)
              {
                 cStmt.execute("FLUSH CACHE");
                 con.commit();
              }
           }catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}
	  //create index
	  try{
            if (flag ==1) {
	      cStmt.execute("CREATE INDEX idx1 ON big1(unique1) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx2 ON big2(unique1) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx3 ON small(unique1) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx4 ON big1(stringu1) HASH");
	      cStmt.close();
              con.commit();
            }else if (flag ==2) {
	      cStmt.execute("CREATE INDEX mysqld1 USING HASH ON big1(unique1)");
	      cStmt.execute("CREATE INDEX mysqld2 USING HASH ON big2(unique1)");
	      cStmt.execute("CREATE INDEX mysqld3 USING HASH ON small(unique1)");
	      cStmt.execute("CREATE INDEX mysqld4 USING HASH ON big1(stringu1)");
              con.commit();
            } else if (flag == 3) {
          cStmt.execute("CREATE INDEX psqld1 on big1 USING HASH (unique1)");
          cStmt.execute("CREATE INDEX psqld2 on big2 USING HASH (unique1)");
          cStmt.execute("CREATE INDEX psqld3 on small USING HASH (unique1)");
          cStmt.execute("CREATE INDEX psqld4 on big1 USING HASH (stringu1)");
          }
      } 
          catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}
	  timeTaken[0][1] = singleTuple(con, true);
	  timeTaken[1][1] = singleTuple(con, false);
          timeTaken[2][1] = 0;
	  timeTaken[3][1] = 0;
	  timeTaken[4][1] = 0;
          timeTaken[5][1] = 0;
          timeTaken[6][1] = 0;
          timeTaken[7][1] = 0;
          timeTaken[8][1] = 0;
          timeTaken[9][1] = 0;
          timeTaken[10][1] = orderby(con);

	  timeTaken[11][1] = dmlstatement(con,ins);
	  timeTaken[12][1] = dmlstatement(con,upd);
	  timeTaken[13][1] = dmlstatement(con,del);
	  timeTaken[14][1] = joining(con,1);
	  timeTaken[15][1] = joining(con,2);
          timeTaken[16][1] = joinCondition(con,1);
          timeTaken[17][1] = joinCondition(con,2);
          System.out.println("Finished hash index queries");
          
          try{
              if(flag == 1)
              {
                 cStmt.execute("FLUSH CACHE");
                 con.commit();
              }
           }catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}


	  try{
            if (flag ==1) {
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
            }else if (flag ==2) {
	      cStmt.execute("DROP INDEX mysqld1 on big1");
	      cStmt.execute("DROP INDEX mysqld2 on big2");
	      cStmt.execute("DROP INDEX mysqld3 on small");
	      cStmt.execute("DROP INDEX mysqld4 on big1");
	      cStmt.execute("CREATE INDEX mysqld5 USING BTREE ON big1(unique1)");
	      cStmt.execute("CREATE INDEX mysqld6 USING BTREE ON big2(unique1)");
	      cStmt.execute("CREATE INDEX mysqld7 USING BTREE ON small(unique1)");
	      cStmt.execute("CREATE INDEX mysqld8 USING BTREE ON big1(stringu1)");
              con.commit();
            } else if (flag == 3) {
          cStmt.execute("DROP INDEX psqld1");
          cStmt.execute("DROP INDEX psqld2");
          cStmt.execute("DROP INDEX psqld3");
          cStmt.execute("DROP INDEX psqld4");
          cStmt.execute("CREATE INDEX psqld5 on big1 USING BTREE (unique1)");
          cStmt.execute("CREATE INDEX psqld6 on big2 USING BTREE (unique1)");
          cStmt.execute("CREATE INDEX psqld7 on small USING BTREE (unique1)");
          cStmt.execute("CREATE INDEX psqld8 on big1 USING BTREE (stringu1)");
              con.commit();
            }
          }catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}

	  timeTaken[0][2] = singleTuple(con, true);
	  timeTaken[1][2] = singleTuple(con, false);
          timeTaken[2][2] = onePerSel(con);
          timeTaken[3][2] = aggregate(con,min,false);
          timeTaken[4][2] = aggregate(con,min,true);
	  timeTaken[5][2] = aggregate(con,max,false);
          timeTaken[6][2] = aggregate(con,max,true);
          timeTaken[7][2] = 0;
          timeTaken[8][2] = 0;
          timeTaken[9][2] = 0;
          timeTaken[10][2] = orderby(con);
	  timeTaken[11][2] = dmlstatement(con,ins);
	  timeTaken[12][2] = dmlstatement(con,upd);
	  timeTaken[13][2] = dmlstatement(con,del);
	  timeTaken[14][2] = joining(con,1);
          timeTaken[15][2] = joining(con,2);
          timeTaken[16][2] = joinCondition(con,1);
          timeTaken[17][2] = joinCondition(con,2);
          System.out.println("Finished tree index queries");

	   
	 
	  try{
            if (flag ==1) {
	      cStmt.execute("DROP INDEX idx5");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx6");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx7");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx8");
	      cStmt.close();
              con.commit();
            } else if (flag ==2) {
	      cStmt.execute("DROP INDEX mysqld5 on big1");
	      cStmt.execute("DROP INDEX mysqld6 on big2");
	      cStmt.execute("DROP INDEX mysqld7 on small");
	      cStmt.execute("DROP INDEX mysqld8 on big1");
              con.commit();
            } else if (flag ==3) {
	      cStmt.execute("DROP INDEX psqld5");
	      cStmt.execute("DROP INDEX psqld6");
	      cStmt.execute("DROP INDEX psqld7");
	      cStmt.execute("DROP INDEX psqld8");
              con.commit();
            }
          }catch(Exception e ){System.out.println("Error dropping indexes");}

          System.out.println("Wisconsin Benchmark Report:");

	  System.out.println("**********************************************************");
	  System.out.println(" Statement       \t NoIndex\tHash \tTree");
	  System.out.println("**********************************************************");
          System.out.println(" SelectInt 1     \t "+timeTaken[0][0] +" \t \t"+ timeTaken[0][1]+ "   \t"+ timeTaken[0][2]); 
          System.out.println(" SelectStr 1     \t "+timeTaken[1][0] +" \t \t"+ timeTaken[1][1]+ "   \t"+ timeTaken[1][2]); 
          System.out.println(" 1% Sel          \t "+timeTaken[2][0] +" \t \t-   \t"+ timeTaken[2][2]); 

          System.out.println(" Min      1      \t "+timeTaken[3][0] +" \t \t-   \t"+ timeTaken[3][2]);
          System.out.println(" Min_GrBy 1%     \t "+timeTaken[4][0] +" \t \t-   \t-");

          System.out.println(" Max      1      \t "+timeTaken[5][0] +" \t \t-   \t"+ timeTaken[5][2]); 
          System.out.println(" Max_GrBy 1%     \t "+timeTaken[6][0] +" \t \t-   \t-");
          
          System.out.println(" Sum      1      \t "+timeTaken[7][0] +" \t \t-   \t-"); 
          System.out.println(" Sum_GrBy 1%     \t "+timeTaken[8][0] +" \t \t-   \t-");
          
          System.out.println(" Distinct 1%     \t "+timeTaken[9][0] +" \t \t-   \t-");
          System.out.println(" OrderBy 1%      \t "+timeTaken[10][0] +" \t \t"+ timeTaken[10][1]+ "   \t"+ timeTaken[10][2]);

          System.out.println(" Insert 1        \t "+timeTaken[11][0] +" \t \t"+ timeTaken[11][1]+ "   \t"+ timeTaken[11][2]); 
          System.out.println(" Update 1        \t "+timeTaken[12][0] +" \t \t"+ timeTaken[12][1]+ "   \t"+ timeTaken[12][2]); 
          System.out.println(" Delete 1        \t "+timeTaken[13][0] +" \t \t"+ timeTaken[13][1]+ "   \t"+ timeTaken[13][2]); 
          System.out.println(" Join(10K*1K)1   \t "+timeTaken[14][0] +" \t \t"+ timeTaken[14][1]+ "\t"+ timeTaken[14][2]); 
          System.out.println(" Join(10K*10K*1K)1\t "+timeTaken[15][0] +"\t  \t"+ timeTaken[15][1]+ "\t"+ timeTaken[15][2]); 
          
          System.out.println(" Join(10K*1K)100 \t "+timeTaken[16][0]+"\t \t"+ timeTaken[16][1]+ "\t"+ timeTaken[16][2]); 
          System.out.println(" Join(10K*10K*1K)100\t "+timeTaken[17][0] +"\t  \t"+ timeTaken[17][1]+ "\t"+ timeTaken[17][2]); 

	  System.out.println("**********************************************************");
	  con.close();
        }
        catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
       
    }
}
