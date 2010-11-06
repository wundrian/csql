<html>
<body>
/*Parateterised Insert*/
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

odbc_exec($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 int);");
odbc_exec($conn,"INSERT INTO t1 values(10,'ABCD',1);");
odbc_exec($conn,"INSERT INTO t1 values(20,'PQRS',2);");

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(2);
}
odbc_result_all($rs, 'border = 5');

$q = "INSERT INTO t1(f1,f2) values(?,?);";
$res = odbc_prepare ($conn, $q);
$a = 30; $b = "PPPP";
$exc = odbc_execute($res, array($a, $b));
if (!$rs)
{
  exit(3);
}

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
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
