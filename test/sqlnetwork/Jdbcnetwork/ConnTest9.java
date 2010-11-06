// Connect with connectstring "jdbc:csql://localhost:5678/csql" and with very long username and "password" in properties object. It should fail but no overflow
//
import java.sql.*;
public class ConnTest9
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678/csql", "wrongusertiiiiiiiiiisooooooooooooooooooooooooooooooooooooooooooooooooolllllllllllllllllllllllloooooooooooooooonnnnnnnnnnnnnnnnnnnnnggggggggggggggggggggg11111111111111111111111111222222222222222222222222222222233333333333333333333333333444444444444444444444444455555555555555555555555555555556666666666666666666666666666666667777777777777777777777777777777777788888888888888888888888888888888888888899999999999999999999999999999999999999999999999999999999999999999xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiieeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeellllllllllllllllllllllllllllllllllllllllllllllllllllllliiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaannnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnggggggggggggggggggggggggggggggggggghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaatttttttttttttttttttttttttttteeeeeeeeeeeeeeeeeeeeeeeeesssssssssssssssstttttttttttttttttttttttttttttttttttttttttttttt", "manager");
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }
}
