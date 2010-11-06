//Index Information 
import java.sql.*;
public class DataMeta3 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", "root", "manager");
	   Statement cStmt = con.createStatement();
           cStmt.execute("CREATE TABLE t1 (f1 integer, f2 char (20),primary key(f2));");
	   cStmt.execute("CREATE INDEX IDX ON t1 ( f1);");
	   con.commit();

          ResultSet indexInformation = null;
          DatabaseMetaData meta = con.getMetaData();
          indexInformation = meta.getIndexInfo(null, null, "t1", true, true);
          System.out.println("================= INDEXINFO ================");
          while (indexInformation.next()) {
          String dbCatalog = indexInformation.getString(1);
          String dbSchema = indexInformation.getString(2);
          String dbTableName = indexInformation.getString(3);
          //boolean dbNoneUnique = indexInformation.getBoolean(4);
          String dbIndexName = indexInformation.getString(6);
      	  short dbType = indexInformation.getShort(7);
          short dbOrdinalPosition = indexInformation.getShort(8);
          String dbColumnName = indexInformation.getString(9);
          System.out.println("index name=" + dbIndexName);
          System.out.println("table=" + dbTableName);
          System.out.println("column=" + dbColumnName);
          System.out.println("catalog=" + dbCatalog);
          System.out.println("schema=" + dbSchema);
          //System.out.println("nonUnique=" + dbNoneUnique);
          System.out.println("type=" + dbType);
          System.out.println("ordinalPosition=" + dbOrdinalPosition);
	  System.out.println("================= @#####@ ================");
        }
           cStmt.execute("DROP TABLE t1 ;");
           con.close();
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }
}
