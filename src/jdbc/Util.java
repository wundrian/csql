/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package csql.jdbc;

import java.sql.Types;

/**
 *
 * @author bijaya
 */
public class Util 
{
     public static int getType(int csqltype)
     {
        switch(csqltype)
        {
            case 0:
                return Types.INTEGER ;
            case 1:
                return Types.BIGINT ;
            case 2:
                return Types.BIGINT ;
            case 3:
                return Types.SMALLINT ;
            case 4:
                return Types.TINYINT ;
                
            case 10:
                return Types.DOUBLE ;
            case 11:
                return Types.FLOAT ;
            case 12:
                return Types.DECIMAL ;
            
            case 20:
                return Types.DATE ;
            case 21:
                return Types.TIME ;
            case 22:
                return Types.TIMESTAMP ;
                
            case 30:
                return Types.CHAR ;
            case 31:
                return Types.BINARY ;
                
            case 100 :
            
            default:
                return Types.OTHER;
        }
    }
   
    public static String getTypeName(int csqltype)
    {
        switch(csqltype)
        {
            case 0:
                return "INT";
            case 1:
                return "BIGINT" ;
            case 2:
                return "BIGINT" ;
            case 3:
                return "SMALLINT" ;
            case 4:
                return "TINYINT" ;
                
            case 10:
                return "DOUBLE" ;
            case 11:
                return "FLOAT" ;
            case 12:
                return "DECIMAL" ;
            
            case 20:
                return "DATE" ;
            case 21:
                return "TIME" ;
            case 22:
                return "TIMESTAMP" ;
                
            case 30:
                return "CHAR" ;
            case 31:
                return "BINARY";
                
            case 100 :
            
            default:
                return "UNKNOWN";
        }
    }
    
    public static String getClassName(int type)
    {
        switch(type)
        {
            case 0:
                return "java.lang.Integer";
            case 1:
                return "java.lang.Long" ;
            case 2:
                return "java.lang.Long" ;
            case 3:
                return "java.lang.Integer" ;
            case 4:
                return "java.lang.Integer" ;
                
            case 10:
                return "java.lang.Double" ;
            case 11:
                return "java.lang.Float" ;
            case 12:
                return  "java.lang.Double";
            
            case 20:
                return "java.sql.Date" ;
            case 21:
                return "java.sql.Time" ;
            case 22:
                return "java.sql.Timestamp" ;
                
            case 30:
                return "java.lang.String" ;
            case 31:
                return "java.lang.String" ;
                
            case 100 :
            
            default:
                return "UNKNOWN";
            
        }
        
    }

}
