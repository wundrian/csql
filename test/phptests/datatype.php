<html>
<body>
/*Create table and with all types of datatypes,Insert one valid record It Should be Passed */

<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed: " . $conn;
  exit(1);
}

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT,f2 INT);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(2);
}
$sth = odbc_prepare($conn, "INSERT INTO t1 VALUES(12,120);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(3);
}
$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  ecit(4);
}
odbc_result_all($rs, 'border = 5');
odbc_exec($conn,"DROP TABLE t1");


$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(5);
}
$sth = odbc_prepare($conn, "INSERT INTO t1 VALUES(12);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(6);
}
$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(7);
}
odbc_result_all($rs, 'border = 5');
odbc_exec($conn,"DROP TABLE t1");

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 char(20));");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(8);
}
$sth = odbc_prepare($conn, "INSERT INTO t1 VALUES('TWELVE');");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(9);
}
$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(10);
}
odbc_result_all($rs, 'border = 5');
odbc_exec($conn,"DROP TABLE t1");

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 SMALLINT);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(11);
}
$sth = odbc_prepare($conn, "INSERT INTO t1 VALUES(1);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(12);
}
$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(13);
}
odbc_result_all($rs, 'border = 5');
odbc_exec($conn,"DROP TABLE t1");

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 BIGINT);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(14);
}
$sth = odbc_prepare($conn, "INSERT INTO t1 VALUES(10000001);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(15);
}
$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(16);
}
odbc_result_all($rs, 'border = 5');
odbc_exec($conn,"DROP TABLE t1");

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 FLOAT);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(17);
}
$sth = odbc_prepare($conn, "INSERT INTO t1 VALUES(10.01);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(18);
}
$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(19);
}
odbc_result_all($rs, 'border = 5');
odbc_exec($conn,"DROP TABLE t1");

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 DOUBLE);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(20);
}
$sth = odbc_prepare($conn, "INSERT INTO t1 VALUES(100001.100001);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(21);
}
$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(22);
}
odbc_result_all($rs, 'border = 5');
odbc_exec($conn,"DROP TABLE t1");

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 DATE);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(23);
}
$sth = odbc_prepare($conn, "INSERT INTO t1 VALUES('2001-1-1');");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion" ;
  exit(24);
}
$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(25);
}
odbc_result_all($rs, 'border = 5');
odbc_exec($conn,"DROP TABLE t1");

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 TIMESTAMP);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(26);
}
$sth = odbc_prepare($conn, "INSERT INTO t1 VALUES('2001-11-30 01:01:01');");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(27);
}
$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(28);
}
odbc_result_all($rs, 'border = 5');
$res=odbc_exec($conn,"DROP TABLE t1");
if (!$res)
{
  echo "Error in Drop Table";
  exit(29);
}
echo "\nTable Dropped\nTest Passed";
odbc_close($conn);
?>

</body>
</html>

