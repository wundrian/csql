<html>
<body>
/*Testing odbc_error() and odbc_errormsg() for error handeling */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
  {echo "Connection Failed"; exit(1);}

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 SMALLINT,f4 BIGINT,f5 FLOAT, f6 DOUBLE,f7 DATE, f8 TIMESTAMP );");
$res = odbc_execute($sth);
if (!$res)
  {echo "Error in Creation"; exit(2);}
echo "Table Created\n";

$query1 = "INSERT INTO t1(f1,f3,f4) values(10,1,100001);";
odbc_exec($conn,$query1);
if (odbc_error())
{
    echo odbc_errormsg($conn);
}
echo "Record Inserted\n";

$query2 = "INSERT INTO t1(f1,f2,f9) values(20,'BCAD',1);";
odbc_exec($conn,$query2);
if (odbc_error())
{
    echo "\nINSERT INTO t1(f1,f2,f9) values(20,'BCAD',1);\n";
    echo odbc_errormsg($conn);
}
echo "\n";

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
  {echo "Error in SQL-2";exit(3);}
odbc_result_all($rs, 'border = 5');

$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
  {exit("\nError in Drop Table");}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>
