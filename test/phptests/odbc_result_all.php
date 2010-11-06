<html>
<body>
/* odbc_result_all() test for display the conditional select result in formated manner. It is more advance than odbc_result() */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 SMALLINT,primary key(f1,f3));");
$res = odbc_execute($sth);
if (!$res)
{
  exit(2);
}
echo "Table Created\n";

$sth = odbc_prepare($conn,"INSERT INTO t1 VALUES(200,'NP',2);");
$res = odbc_execute($sth);
if (!$res)
{
  exit(3);
}
echo "Record Inserted\n";

$sth = odbc_prepare($conn,"INSERT INTO t1 VALUES(100,'PP',1);");
$res = odbc_execute($sth);
if (!$res)
{
  exit(4);
}
echo "Record Inserted\n";

$sth = odbc_prepare($conn,"INSERT INTO t1 VALUES(300,'RP',3);");
$res = odbc_execute($sth);
if (!$res)
{
  exit(5);
}
echo "Record Inserted\n";

$sth = 'SELECT * FROM t1 where f1<=200;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  exit(6);
}
odbc_result_all($rs, 'border = 5');

$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
{
  echo "\nError in Drop Table";
  exit(7);
}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>
