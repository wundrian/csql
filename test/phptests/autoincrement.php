<html>
<body>
/*Autoincrement testing */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT auto_increment, f2 CHAR(20));");
$res = odbc_execute($sth);
if (!$res)
{
  exit(2);
}
echo "Table Created";

$sth = odbc_prepare($conn, "INSERT INTO t1(f2) VALUES('One');");
$res = odbc_execute($sth);
if (!$res)
{
  exit(3);
}
echo "\nINSERT INTO t1(f2) VALUES('One');";
echo "\nRecord Inserted";

$sth = odbc_prepare($conn, "INSERT INTO t1(f1,f2) VALUES(5,'Five');");
$res = odbc_execute($sth);
if (!$res)
{
  exit(4);
}
echo "\nINSERT INTO t1(f1,f2) VALUES(5,'Five');";
echo "\nRecord Inserted";

$sth = odbc_prepare($conn, "INSERT INTO t1(f2) VALUES('Six');");
$res = odbc_execute($sth);
if (!$res)
{
  exit(5);
}
echo "\nINSERT INTO t1(f2) VALUES('Six');";
echo "\nRecord Inserted";

$sth = odbc_prepare($conn, "INSERT INTO t1(f1,f2) VALUES(3,'Three');");
$res = odbc_execute($sth);
if (!$res)
{
  exit(6);
}
echo "\nINSERT INTO t1(f1,f2) VALUES(3,'Three');";
echo "\nRecord Inserted";

$sth = odbc_prepare($conn, "INSERT INTO t1(f2) VALUES('Seven');");
$res = odbc_execute($sth);
if (!$res)
{
   exit(7);
}
echo "\nINSERT INTO t1(f2) VALUES('Eight');";
echo "\nRecord Inserted\n";

$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  exit(8);
}
echo "\nselect executed\n";
odbc_result_all($rs);
$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
{
  exit(9);
}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>

