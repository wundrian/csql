/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author bijaya
 */

import java.sql.*;

public class connect implements Runnable
{
    Connection con;
    PreparedStatement stmt;
    ResultSet rs;
    Thread th;
    int thid;
    int totalrecord;
    int type;
    long timeTaken;
    connect(int i,int ty ,int record)
    {
        System.out.println("thread "+ i);
        thid=i;
        totalrecord=record;
        type=ty;
        timeTaken=0;
        th=new Thread(this);
        th.start();
    }
    public static Connection getDBConn() throws Exception
    {
        Class.forName("csql.jdbc.JdbcSqlDriver"); 
        Connection con = DriverManager.getConnection("jdbc:csql:", "root", "manager");
        return con;
    }
    public void run()
    {
        if(0==type)  insertTest();
        else if(1==type) selectTest();
        else if(2==type) updateTest();
        else if(3==type) deleteTest();
        else selectTest1();
    }

    public void insertTest()
    {
        try{
        //Class.forName("csql.jdbc.JdbcSqlDriver");
        //con = DriverManager.getConnection("jdbc:csql:","root","manager");
        con = getDBConn();
        stmt = con.prepareStatement("insert into emp values (?, 'SECOND');");
        long count = 0, recordCount=0;
        int ret = 0;
        long start = 0,end = 0,curr = 0;
        long tot = 0;
        for(int i=0; i<totalrecord; i++){
               stmt.setInt(1, totalrecord*thid+i);
               start = System.nanoTime();
                try{
                ret = stmt.executeUpdate();
                }catch(Exception e1)
                {
                    try{
                        System.out.println("Retry -1 Exception in Test=1: "+e1);
                        ret = stmt.executeUpdate();
                    }catch(Exception e)
                    {
                        System.out.println("Retry -2 Exception in Test=2: "+e);
                        ret = stmt.executeUpdate();
                    }
                    
                }
                if(ret!=1) break;
                end = System.nanoTime();
                curr = end - start;
                tot = tot + curr;
                count++;
        }
        stmt.close();
        timeTaken = tot;
        long val = tot/totalrecord;
        System.out.println("Thread id "+this.thid+"  Total rec: "+count+" Avgtime  :"+val);
        System.out.println("Total Record Insert: "+count);
        Thread.sleep(1000);
        con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e+"Thread NO"+thid);
            e.printStackTrace();
        }
    }

public void selectTest()
{
        try{
        //Class.forName("csql.jdbc.JdbcSqlDriver");
        //con = DriverManager.getConnection("jdbc:csql:","root","manager");
        con = getDBConn();
        stmt = con.prepareStatement("select * from emp where f1=?");
        Thread.sleep(1000);
        long count = 0, recordCount=0;
        int ret = 0;
        long start = 0,end = 0,curr = 0;
        long tot = 0;
        for(int i=0; i<totalrecord; i++){
            stmt.setInt(1, totalrecord*thid +i);
            start = System.nanoTime();
                try{
                rs = stmt.executeQuery();
                }catch(Exception e1)
                {
                    try{
                        System.out.println("Retry-1"+ e1);
                        rs = stmt.executeQuery();
                    }catch(Exception e)
                    {
                        System.out.println("Retry-2"+ e1);
                        rs = stmt.executeQuery();
                    }
                }
                if(rs.next())
                {
                    recordCount++;
                }

                end = System.nanoTime();
                curr = end - start;
                tot = tot + curr;
                count++;
        }
        stmt.close();
        timeTaken = tot;
        long val = tot/totalrecord;
        System.out.println("Thread id "+this.thid+"Total select "+recordCount+" Avgtime  :"+val);
        System.out.println("Total Record select "+recordCount + " " + tot + " "+ totalrecord);
        con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e+"Thread NO"+thid);
            e.printStackTrace();
        }
    }

public void deleteTest()
{
        
        try{
        //Class.forName("csql.jdbc.JdbcSqlDriver");
        //con = DriverManager.getConnection("jdbc:csql:","root","manager");
        con = getDBConn();
        stmt = con.prepareStatement("delete from emp where f1=?");
        long count = 0, recordCount=0;
        int ret = 0;
        
        Thread.sleep(2000);
        long start = 0,end = 0,curr = 0;
        long tot = 0;
        for(int i=0; i<totalrecord; i++){
            stmt.setInt(1, totalrecord*thid+i);
            start = System.nanoTime();
                try{
                ret = stmt.executeUpdate();
                }catch(Exception e1)
                {
                    try{
                        ret = stmt.executeUpdate();
                    }catch(Exception e)
                    {
                   //     System.out.println("Exception in Test=2: "+e);
                        ret = stmt.executeUpdate();
                    }
                }
                if(ret!=1) break;
                end = System.nanoTime();
                curr = end - start;
                tot = tot + curr;
                count++;
        }
        stmt.close();
        long val = tot/totalrecord;
        System.out.println("Total Record Delete: "+count);
        con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e+"Thread NO"+thid);
            e.printStackTrace();
        }
    }
public void updateTest()
   {
        try{
        //Class.forName("csql.jdbc.JdbcSqlDriver");
        //con = DriverManager.getConnection("jdbc:csql:","root","manager");
        con = getDBConn();
        stmt = con.prepareStatement("update emp set f2='india' where f1=?");
        long count = 0, recordCount=0;
        int ret = 0;

        Thread.sleep(1000);
        long start = 0,end = 0,curr = 0;
        long tot = 0;
        for(int i=0; i<totalrecord; i++){
            stmt.setInt(1, totalrecord*thid+i);
            start = System.nanoTime();
                try{
                ret = stmt.executeUpdate();
                }catch(Exception e1)
                {
                    try{
                        ret = stmt.executeUpdate();
                    }catch(Exception e)
                    {
                        //System.out.println("Exception in Test=2: "+e);
                        ret = stmt.executeUpdate();
                    }
                }
                if(ret!=1) break;
                end = System.nanoTime();
                curr = end - start;
                tot = tot + curr;
                count++;
        }
        stmt.close();
        long val = tot/totalrecord;
        System.out.println("Thread id "+this.thid+"  Total rec Update: "+count+" Avgtime  :"+val);
        System.out.println("Total Record Update: "+count);
        con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e+"Thread NO"+thid);
            e.printStackTrace();
        }
    }

public void selectTest1()
{
        try{
        //Class.forName("csql.jdbc.JdbcSqlDriver");
        //con = DriverManager.getConnection("jdbc:csql:","root","manager");
        con = getDBConn();
        stmt = con.prepareStatement("select * from emp where f1>=? and f1<?");
        Thread.sleep(1000);
        long count = 0, recordCount=0;
        int ret = 0;
        long start = 0,end = 0,curr = 0;
        long tot = 0;
        for(int i=0; i<totalrecord/100; i++){
            stmt.setInt(1, totalrecord*thid +i);
            stmt.setInt(2, totalrecord*thid +i+100);
            start = System.nanoTime();
                try{
                rs = stmt.executeQuery();
                }catch(Exception e1)
                {
                    try{
                        rs = stmt.executeQuery();
                    }catch(Exception e)
                    {
                        rs = stmt.executeQuery();
                    }
                }
                while(rs.next())
                {
                    recordCount++;
                }

                end = System.nanoTime();
                curr = end - start;
                tot = tot + curr;
                count++;
        }
        stmt.close();
        long val = tot/totalrecord;
        System.out.println("Thread id "+this.thid+"Total select "+recordCount+" Avgtime  :"+val);
        System.out.println("Total Record select "+recordCount);
        con.close();
        }catch(Exception e) {
              System.out.println("Exception in Test: "+e+"Thread NO"+thid);
              e.printStackTrace();
        }
     }
     

}
