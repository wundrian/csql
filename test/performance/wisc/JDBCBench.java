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
   
	// runQuery 7
       public static int singleTuple(Connection con, boolean flag)throws Exception
	{
		PreparedStatement stmt = null ;
		String stmtStr;
		if(flag)
		{
			String buf = " SELECT * from big1 where unique2=?; ";
			stmtStr =  buf;
		}
		else
		{
			String buf = "SELECT * from big1 where unique2=? ;";
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
				System.out.println("records in Q7= "+ recordCount );
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
                 System.out.println("No. of records returned is wrong for Q1 "+recordCount);
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
public static int aggregate(Connection con, int val)throws Exception
{
	PreparedStatement stmt = null;
	String stmtStr="";
	if(val==1)
	{
		String buf = "SELECT MIN(unique2) from big1;";
		stmtStr = buf;
	}
	else if(val==2)
	{
		String buf = "SELECT MIN(unique2) FROM big1 GROUP BY onepercent;";
		stmtStr = buf;
	}
	else
	{
		String buf = "SELECT SUM(unique2) FROM big1 GROUP BY onepercent;";
		stmtStr = buf;
	}
	    
		stmt = con.prepareStatement(stmtStr);
		int count = 0, recordCount;
		int ret = 0;
		long start = 0,end = 0,curr = 0;
		long tot = 0;
		ResultSet rs;
		
		//for(int i=0;i<100;i++){
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

			if((val==1) && recordCount !=1) 
			{
				System.out.println("No. of records returned is around for Q2" + recordCount);
				return 0;
			}
			if((val==2 || val==3) && recordCount !=100)
			{
				System.out.println("No. of records returned is around for Q2" + recordCount);
				return 0;
			}	
			curr = end - start;
			tot = tot + curr;
			count++;
		//}
		stmt.close();
		return (int)tot/1000;
}


// DML statement
public static int dmlstatement(Connection con, int val)throws Exception
{
	PreparedStatement stmt = null;
	String stmtStr="";
	if(val==1)
	{
		String buf = "insert into big1 values(10010,10010,0,2,0,10,50,688,1950,4950,9950,1,100,'MXXXXXXXXXXXXXXXXXXXXXXXXXGXXXXXXXXXXXXXXXXXXXXXXXXC','GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO');";
		stmtStr = buf;
	}
	else if(val==2)
	{
		String buf = "UPDATE big1 SET unique2=10001 WHERE unique2=10010;";
		stmtStr = buf;
	}
	else
	{
		String buf = "DELETE FROM big1 WHERE unique2=10001;";
		stmtStr = buf;
	}
	    
		stmt = con.prepareStatement(stmtStr);
		int count = 0, recordCount=0;
		int ret = 0;
		long start = 0,end = 0,curr = 0;
		long tot = 0;
		
		
		
		//for(int i=0;i<100;i++){
			start = System.nanoTime();
			ret = stmt.executeUpdate();
			if(ret!=1) return 1;
			recordCount++;
								
			con.commit();
			end = System.nanoTime();

			/*if((val==1) && recordCount !=1) 
			{
				System.out.println("No. of records returned is around for Q2" + recordCount);
				return 0;
			}
			if((val==2 || val==3) && recordCount !=1)
			{
				System.out.println("No. of records returned is around for Q2" + recordCount);
				return 0;
			}	*/
			curr = end - start;
                        tot = tot + curr;
			count++;
	   //}	
		stmt.close();
		return (int)tot/1000;
}

// Joining
public static int joining(Connection con,int val)throws Exception
{
	PreparedStatement stmt = null;
	String stmtStr;
	if(val==9)
	{
		String buf = "SELECT big1.unique2, big2.unique2 FROM big2,big1 WHERE big1.unique2=big2.unique2 AND big2.unique2<1000;";
		stmtStr = buf;
	}
	else if(val==10)
	{
		String buf = "SELECT * FROM big1,bprime WHERE big1.unique2=bprime.unique2;";
		stmtStr = buf;
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
	for(int i=0;i<=100;i++)
	{
		start = System.nanoTime();
		rs = stmt.executeQuery();
		while(rs.next())
		{
                System.out.println("PRABA: "+ recordCount);
			recordCount++;
		}
                System.out.println("PRABA: "+ recordCount);
		rs.close();
		con.commit();
		end=System.nanoTime();
		if(recordCount!=1000)
		{
		System.out.println("No. of records wrong "+recordCount);
		return 0;
		}
		curr = end - start;
		tot = tot + curr;
		count++;
	}
	stmt.close();
	return (int)tot/100/1000;
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
			   System.out.println("No. of records returned is wrong for Q2 " + recordCount);
			
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
          Statement cStmt = con.createStatement();
	  
	  System.out.println("\n\n");
	  System.out.println("**********************************************************\n");
	  System.out.println("NOTE :  Idx1-------Tree(unique1).\n\tIdx2-------Hash(unique2).\n\t Time in microsecs---");
	  System.out.println("\n");
	  System.out.println("Q.No.\tQuery Type\tNoIdx\tIdx1\tIdx2\tWall_Clk");
	  System.out.println("-----\t----------\t-----\t----\t----\t--------");

	  int q1 = onePerSel(con, true);
	  System.out.println("1\t1% Sel\t\tY\t-\t-\t"+q1);

	  int q2 = tenPerSel(con,true);
	  System.out.println("2\t10% Sel\t\tY\t-\t-\t"+q2);

	  int min=1, ming=2,sum=3;// function parameter
	  
	  int q20 = aggregate(con,min);
	  System.out.println("20\tMinAgg No Grps\tY\t-\t-\t"+q20);

	  int q21 = aggregate(con,ming);
	  System.out.println("21\tMinAgg Grps\tY\t-\t-\t"+q21);


	  int q22 = aggregate(con,sum);
	  System.out.println("22\tSumAgg Grps\tY\t-\t-\t"+q22);

	  //create index
	  try{
            if (flag ==1) {
	      cStmt.execute("CREATE INDEX idx4 ON big1(unique2) HASH");
	      cStmt.close();
	      cStmt.execute("CREATE INDEX idx3 ON big1(unique1) TREE");
	      cStmt.close();
            }else if (flag ==2) {
	      cStmt.execute("CREATE INDEX x1 USING HASH ON big1(unique2)");
	      cStmt.execute("CREATE INDEX x2 USING BTREE ON big1(unique1)");
	      cStmt.close();
            }
          }catch(Exception e ){e.printStackTrace(); System.out.println("Error creating index");}

	  int q3 = onePerSel(con,true);
	  System.out.println("3\t1% Sel\t\t-\t-\tY\t"+q3);


	  int q4 = tenPerSel(con,true);
	  System.out.println("4\t10% Sel\t\t-\t-\tY\t"+q4);


	  int q5 = onePerSel(con,false);
	  System.out.println("5\t1% Sel\t\t-\tY\t-\t"+q5);


	  int q6 = tenPerSel(con,false);
	  System.out.println("6\t10% Sel\t\t-\tY\t-\t"+q6);

	  int q7 = singleTuple(con,true);
	  System.out.println("7\t1 Tup Sel\t-\t-\tY\t"+q7);

	   
          //commented query 8 as it is duplicate of query 3
	  //int q8 = onePerSel(con,true);
	  //System.out.println("8\t1% Sel\t\t-\t-\tY\t"+q1);

	  
	  int Q9=1,Q10=2,Q11=3,Q15=4,Q16=5,Q17=6;

	  //int q9 = joining(con,	Q9);
	  //System.out.println("9\tJoin AselB\tY\t-\t-\t"+q9);

          
	  //int q10 = joining(con,Q10);
	  //System.out.println("10\tJoin ABPrime\tY\t-\t-\t"+q10);

	  //int q11 = joining(con,Q11);
	  //System.out.println("11\tJoin CselAselB\tY\t-\t-\t"+q11);
	  
/*
	  // create non-cluster index
	  cStmt.execute("CREATE INDEX idx1 ON small(unique1)UNIQUE");
	  cStmt.close();

	  cStmt.execute("CREATE INDEX idx3 ON big1(unique1)UNIQUE");
	  cStmt.close();

	  cStmt.execute("CREATE INDEX idx5 ON big2(unique1)UNIQUE");
	  cStmt.close();

	  int q15 = joining(con,Q15);
	  System.out.println("15\tJoin AselB\t-\tY\t-\t"+q15);
	  
	  int q16 = joining(con,Q16);
	  System.out.println("16\tJoinABprime\t-\tY\t-\t"+q16);

	  int q17 = joining(con,Q17);
	  System.out.println("17\tJoin CselAselB\t-\tY\t-\t"+q17);


	  int q18 = projection(con,true);
	  System.out.println("18\t1%Proj Sel\t-\tY\tY\t"+q18);

	  int q19 = projection(con,false);
	  System.out.println("19\t100%Proj Sel\t-\tY\tY\t"+q19);*/
	  
	  

	  int q23 = aggregate(con,min);
	  System.out.println("23\tMinAgg No Grps\t-\t-\tY\t"+q23);


	  int q24 = aggregate(con,ming);
	  System.out.println("24\tMinAgg Grps\t-\t-\tY\t"+q24);


	  int q25 = aggregate(con,sum);
	  System.out.println("25\tSumAgg Grps\t-\t-\tY\t"+q25);

	  
	  int in=1,upd=2,del=3;// function parameter
/*
	  int q26 = dmlstatement(con,in);
	  System.out.println("26\tInsert 1 Tup\tY\t-\t-\t"+q26);


	  int q27 = dmlstatement(con,upd);
	  System.out.println("27\tupdate 1 Tup\tY\t-\t-\t"+q27);


	  int q28 = dmlstatement(con,del);
	  System.out.println("28\tdelete 1 Tup\tY\t-\t-\t"+q28);

	  //with indexes 
	  int q29 = dmlstatement(con,in);
	  System.out.println("29\tinsert 1 Tup\t-\tY\tY\t"+q29);

	  
	  int q30 = dmlstatement(con,upd);
	  System.out.println("30\tupdate 1 Tup\t-\tY\tY\t"+q30);

	   
	  int q31 = dmlstatement(con,del);
	  System.out.println("31\tdelete 1 Tup\t-\tY\tY\t"+q31);
*/
	  try{
            if (flag ==1) {
	      cStmt.execute("DROP INDEX idx4;");
	      cStmt.close();
	      cStmt.execute("DROP INDEX idx3;");
	      cStmt.close();
            } else if (flag ==2) {
	      cStmt.execute("DROP INDEX x1 on big1");
	      cStmt.close();
	      cStmt.execute("DROP INDEX x2 on big1");
	      cStmt.close();
            }
          }catch(Exception e ){System.out.println("Error dropping indexes");}
          System.out.println("\n");

	  System.out.println("**********************************************************\n");

	  con.close();
        }
        catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
       
    }
}
