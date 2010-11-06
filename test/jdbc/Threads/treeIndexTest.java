/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.sql.*;
/**
 *
 * @author bijaya
 */

public class  treeIndexTest{

    public static void main(String[] args) {
     try
       {

           int noOfThreads=5;
           int noOfRecords=1000;
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql:", "root", "manager");
           Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE emp (f1 int, f2 char (20));");
           cStmt.execute("create index ind on emp(f1) tree unique;");
           connect[] conth= new connect[10];                            
           System.out.println("Table Insert");
           for(int i=0;i<noOfThreads;i++)
           {
               conth[i] = new connect(i,0,noOfRecords);
           }
           for(int i=0;i<noOfThreads;i++)
           {
              conth[i].th.join();
           }
           System.out.println("Table Select");

           for(int i=0;i<noOfThreads;i++)
           {
               conth[i] = new connect(i,4,noOfRecords);
           }
           for(int i=0;i<noOfThreads;i++)
           {
              conth[i].th.join();
           }
           System.out.println("Table Update");
           for(int i=0;i<noOfThreads;i++)
           {
               conth[i] = new connect(i,2,noOfRecords);
           }
           for(int i=0;i<noOfThreads;i++)
           {
              conth[i].th.join();
           }
           System.out.println("Table delete");
           for(int i=0;i<noOfThreads;i++)
           {
               conth[i] = new connect(i,3,noOfRecords);
           }
           for(int i=0;i<noOfThreads;i++)
           {
              conth[i].th.join();
           }

           System.out.println("Drop Table ");

           cStmt.execute("DROP TABLE emp ;");
           con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
 }


