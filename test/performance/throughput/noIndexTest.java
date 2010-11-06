import java.sql.*;
/**
 *
 * @author bijaya
 */

public class  noIndexTest{

    public static void main(String[] args) {
     try
       {


           int noOfThreads=5;
           int noOfRecords=10000;
           Connection con = connect.getDBConn();
           Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE emp (f1 int, f2 char (20));");
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
           long totalTimeTaken=0;
           for(int i=0;i<noOfThreads;i++)
           {
              totalTimeTaken = totalTimeTaken + conth[i].timeTaken;
           }
           System.out.println("Table Insert " + totalTimeTaken);


           for(int i=0;i<noOfThreads;i++)
           {
               conth[i] = new connect(i,1,noOfRecords);
           }
           for(int i=0;i<noOfThreads;i++)
           {
              conth[i].th.join();
           }
           totalTimeTaken=0;
           for(int i=0;i<noOfThreads;i++)
           {
              totalTimeTaken = totalTimeTaken + conth[i].timeTaken;
           }
           System.out.println("Table Select " + totalTimeTaken);

           /*System.out.println("Table Update");
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
           }*/

           System.out.println("Drop Table ");

           cStmt.execute("DROP TABLE emp ;");
           con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
 }


