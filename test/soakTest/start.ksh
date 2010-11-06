nohup ./csqlInsert ./csql.out >/dev/null 2>/dev/null  &
#nohup ./odbcInsert ./odbc.out >/dev/null 2>/dev/null &
nohup java jdbcDelete ./jdbc.out >/dev/null 2>/dev/null &
