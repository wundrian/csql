//Test Script for getColumnDisplaySize,getColumnLabel,getColumnName,getColumnType,getColumnTypeName,getColumnClassName,getTableName,isNullable Taking 9 different type of field
import java.sql.*;
public class RSMetadata2
{
    public static void main(String[] arg)
    {
	try
	{
	    Class.forName("csql.jdbc.JdbcSqlDriver");
	    Connection con=DriverManager.getConnection("jdbc:csql://localhost:5678","root","manager");
	    Statement cStmt=con.createStatement();
	    cStmt.execute("CREATE TABLE T1 (f1 integer, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);");
	    con.commit();
	    PreparedStatement stmt=null,selStmt=null;
	    stmt=con.prepareStatement("INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?);");
	    int ret=0;
	    for(int i=0;i<10;i++)
	    {
		stmt.setInt(1,i);
		stmt.setShort(2,(short)(i+1));
		stmt.setByte(3,(byte)(i+2));
        	stmt.setLong(4,(long)i);
		stmt.setFloat(5,(float)1000+i);
		stmt.setString(6, String.valueOf("BIJAYA"+i));
           	stmt.setDate(7,Date.valueOf("2008-03-21"));
           	stmt.setTime(8,Time.valueOf("18:00:00"));
           	stmt.setTimestamp(9,Timestamp.valueOf("2008-03-21 18:00:00"));
		ret=stmt.executeUpdate();
		if(ret!=1) break;
	    }
	    stmt.close();
	    con.commit();
	    selStmt=con.prepareStatement("Select * from T1");
	    ResultSet rs=null;
	    rs=selStmt.executeQuery();
             
           System.out.println("SELECT * from T1 ;");
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



	    while(rs.next())
	    {
		System.out.println("Tuple value is " + rs.getInt(1) + " "+
                                                        rs.getShort(2) + " "+
                                                        rs.getByte(3) + " "+
                                                        rs.getLong(4) + " "+
                                                        rs.getFloat(5) + " "+
                                                        rs.getString(6) + " "+
                                                        rs.getDate(7) + " "+
                                                        rs.getTime(8) + " "+
                                                        rs.getTimestamp(9) + " "
                                                        );

	    }
	    rs.close();
	    con.commit();
	    ret=0;
            selStmt=con.prepareStatement("Select f9,f2,f4,f5,f7,f1,f8,f6,f3 from T1");
            rs=null;
            rs=selStmt.executeQuery();
	    System.out.println();
            
           System.out.println("SELECT f9,f2,f4,f5,f7,f1,f8,f6,f3 from T1 ;");
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

            while(rs.next())
            {
                System.out.println("Tuple value is " + rs.getInt(6) + " "+
                                                        rs.getShort(2) + " "+
                                                        rs.getByte(9) + " "+
                                                        rs.getLong(3) + " "+
                                                        rs.getFloat(4) + " "+
                                                        rs.getString(8) + " "+
                                                        rs.getDate(5) + " "+
                                                        rs.getTime(7) + " "+
                                                        rs.getTimestamp(1) + " "
                                                        );

            }
            rs.close();
            con.commit();
	    cStmt.executeUpdate("Drop table T1;");
	    con.close();
       }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
}

