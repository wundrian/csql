//Try to connect with connectstring "jdbc:csql" and give very long "user" string and correct "password" in properties object. It should fail but no overflow.
//Author: XieLiang
import java.sql.*;
public class ConnTest15
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql", "wrongusertestxieliangiiiiiiiiiiisooooooooooooooooooooooooooooooooooooooooooooooooolllllllllllllllllllllllloooooooooooooooonnnnnnnnnnnnnnnnnnnnnggggggggggggggggggggg11111111111111111111111111222222222222222222222222222222233333333333333333333333333444444444444444444444444455555555555555555555555555555556666666666666666666666666666666667777777777777777777777777777777777788888888888888888888888888888888888888899999999999999999999999999999999999999999999999999999999999999999xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiieeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeellllllllllllllllllllllllllllllllllllllllllllllllllllllliiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaannnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnggggggggggggggggggggggggggggggggggghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaatttttttttttttttttttttttttttteeeeeeeeeeeeeeeeeeeeeeeeesssssssssssssssstttttttttttttttttttttttttttttttttttttttttttttt", "manager");
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }
}
