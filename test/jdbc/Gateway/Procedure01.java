//Call Procedure through gateway


import java.sql.*;
public class Procedure01 
{         
    public static void main(String[] args) 
    {   
       try
       {     
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:adapter", "root", "manager");
           if ( con == null ) System.exit(1);
           CallableStatement cs=null;
           if(System.getenv("DSN").equals("oracle")){
                cs = con.prepareCall("{ call CsqlRef.InParamSelect(?) }");
           }
           else{
                System.out.println("mysql");
                cs = con.prepareCall("{ call InParamSelect(?) }");
           }
           cs.setInt(1, 15);
           ResultSet rs = cs.executeQuery();
           System.out.println("F1"+"      F2");
           System.out.println("-------------");
           while(rs.next())
           { 
               System.out.println(rs.getInt(1)+"      "+rs.getInt(2));
           } 
           rs.close();
           con.close();
           System.exit(0);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.getStackTrace();
            System.exit(1);
       }
    }
}

