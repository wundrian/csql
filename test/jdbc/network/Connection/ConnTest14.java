//Try to connect with very long connectstring and give correct "user" and "password" in properties object. It should fail but no overflow
import java.sql.*;
public class ConnTest14 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("testlonglonglongconnectstring111111111111111111111111111111111111111111111111111111111111111111111122222222222222222222222222222222222222222222222222222222222222222233333333333333333333333333333333333333333333333333334444444444444444444444444444444444444444444455555555555555555555555555555555555555555555555555555555556666666666666666666666666666666666666666666677777777777777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxlllllllllllllllllllllllllllllllllllaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcccccccccccccccccccccccccccccccccccccccdddddddddddddddddddddddeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeffffffffffffffffffffffffffffffffffffffffffffffffffffff://localhost:5678", "root", "manager");
          if (con != null) System.exit (1);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit (0);
       }
    }
}
