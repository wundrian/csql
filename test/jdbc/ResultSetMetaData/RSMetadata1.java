//Test DML statement 
//Test Script for getColumnDisplaySize,getColumnLabel,getColumnName,getColumnType,getColumnTypeName,getColumnClassName,getTableName,isNullable takeing two Field 
import java.sql.*;
public class RSMetadata1 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql", "root", "manager");
	   Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE T1 (f1 integer, f2 char (20));");
 	   cStmt.execute("CREATE INDEX IDX ON T1 ( f1);");
	   con.commit();
	   PreparedStatement stmt = null, selStmt= null;
           stmt = con.prepareStatement("INSERT INTO T1 VALUES (?, ?);");
           for (int j =0 ; j< 10 ; j++) {
             stmt.setInt(1, j);
             stmt.setString(2, String.valueOf(j+100));
             stmt.executeUpdate();
           }
           stmt.close();
           con.commit();
           selStmt = con.prepareStatement("SELECT f2,f1 from T1 ;");
	   ResultSet rs = null;
           rs = selStmt.executeQuery();
  
           System.out.println("SELECT f2,f1 from T1 ;");
           System.out.println();
           ResultSetMetaData rsMetaData = rs.getMetaData();

           int numberOfColumns = rsMetaData.getColumnCount();
           System.out.println("resultSet MetaData column Count=" + numberOfColumns);

           for (int i = 1; i <= numberOfColumns; i++) 
           {

               System.out.println("=============================== ");
               System.out.println("RESULT SET METADATA  ");
               System.out.println("=============================== ");
               System.out.println("column number   = " + i);
               System.out.println("DisplaySize     = "+rsMetaData.getColumnDisplaySize(i));
               System.out.println("ColumnLabel     = "+rsMetaData.getColumnLabel(i));
               System.out.println("ColumnName      = "+rsMetaData.getColumnName(i));
               System.out.println("ColumnType      = "+rsMetaData.getColumnType(i));
               System.out.println("TypeName        = "+rsMetaData.getColumnTypeName(i));
               System.out.println("ClassName       = "+rsMetaData.getColumnClassName(i));
               System.out.println("TableName       = "+rsMetaData.getTableName(i));
               System.out.println("sNullable       = "+rsMetaData.isNullable(i));
               System.out.println("=============================== ");
          }
     	  while (rs.next())
          {
	      System.out.println("Tuple value is " + rs.getInt(2)+ " "+ rs.getString(1));
	  }
   	  rs.close();

           selStmt = con.prepareStatement("SELECT * from T1 ;");
           rs = selStmt.executeQuery();
           System.out.println("SELECT * from T1 ;");
           System.out.println();

           rsMetaData = rs.getMetaData();

           numberOfColumns = rsMetaData.getColumnCount();
           System.out.println("resultSet MetaData column Count=" + numberOfColumns);

           for (int i = 1; i <= numberOfColumns; i++)
           {

               System.out.println("=============================== ");
               System.out.println("RESULT SET METADATA  ");
               System.out.println("=============================== ");
               System.out.println("column number   = " + i);
               System.out.println("DisplaySize     = "+rsMetaData.getColumnDisplaySize(i));
               System.out.println("ColumnLabel     = "+rsMetaData.getColumnLabel(i));
               System.out.println("ColumnName      = "+rsMetaData.getColumnName(i));
               System.out.println("ColumnType      = "+rsMetaData.getColumnType(i));
               System.out.println("TypeName        = "+rsMetaData.getColumnTypeName(i));
               System.out.println("ClassName       = "+rsMetaData.getColumnClassName(i));
               System.out.println("TableName       = "+rsMetaData.getTableName(i));
               System.out.println("sNullable       = "+rsMetaData.isNullable(i));
               System.out.println("=============================== ");
          }
          while (rs.next())
          {
              System.out.println("Tuple value is " + rs.getInt(1)+ " "+ rs.getString(2));
          }
          rs.close();

          cStmt.execute("DROP TABLE T1 ;");
          con.close();
        }catch(Exception e) {
             System.out.println("Exception in Test: "+e);
             e.printStackTrace();
        }
    }
}
