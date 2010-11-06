<html>
<body>
/*Parameterisez update*/
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed ";
  exit(1);
}

$result = odbc_exec($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 int);");
$result = odbc_exec($conn,"INSERT INTO t1 values(10,'ABCD',1);");
$result = odbc_exec($conn,"INSERT INTO t1 values(20,'PQRS',2);");

odbc_free_result($result);
$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(2);
}
odbc_result_all($rs, 'border = 5');
odbc_free_result($rs);

$q = "update t1 set f2=? where f1=?";
$res = odbc_prepare ($conn, $q);
$a = "PPPP"; $b=10;
$exc = odbc_execute($res, array($a, $b));
if (!$rs)
{
  exit(3);
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
