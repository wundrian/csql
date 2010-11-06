<html>
<body>
/*Parateterised delete*/
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

$res = odbc_exec($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 int);");
if (!$res)
{
  echo "Error in Creation";
  exit(2);
}
echo "Table Created\n";

$res = odbc_exec($conn,"INSERT INTO t1 values(10,'ABCD',1);");
if (!$res)
{
  echo "Error in Creation";
  exit(3);
}
echo "Table Created\n";

$res = odbc_exec($conn,"INSERT INTO t1 values(20,'PQRS',2);");
if (!$res)
{
  echo "Error in Creation";
  exit(4);
}
echo "Table Created\n";

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(5);
}
odbc_result_all($rs, 'border = 5');

$q = "DELETE FROM t1 WHERE f1=?;";
$res = odbc_prepare ($conn, $q);
$a = 10;
$exc = odbc_execute($res, array($a));
if (!$rs)
{
  exit(6);
}

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
  {exit("Error in SQL-2");}
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
