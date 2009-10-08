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

class FieldInfo {

        private String tableName;
        private String colname;
        private int length;
        private int csqlType;
        private short colFlag;
        private int colDecimals;
        private int colPosition;
        private boolean nullable;

        FieldInfo(String tableName, String columnName, int csqltype, int length,boolean nullFlag) 
        {
		this.tableName = tableName;
		this.colname = columnName;
		this.length = length;
		this.csqlType = csqltype;
		this.colFlag = 0;
		this.colDecimals = 0;
                this.nullable = nullFlag;
	}

    public int getColDecimals() {
        return colDecimals;
    }

    public short getColFlag() {
        return colFlag;
    }

    public int getColPosition() {
        return colPosition;
    }

    public String getColname() {
        return colname;
    }

    public int getLength() {
        return length;
    }

    public String getTableName() {
        return tableName;
    }

    public int getCsqlType() {
        return csqlType;
    }

    public boolean isNullable() {
        return nullable;
    }
        
        
}
