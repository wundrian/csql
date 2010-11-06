<html>
<body>
/*Default value testing */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT default 10, f2 CHAR(20),primary key(f1));");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(2);
}
echo "Table Created";

$sth = odbc_prepare($conn, "INSERT INTO t1(f1,f2) VALUES(1,'One');");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(2);
}
echo "\nINSERT INTO t1(f1,f2) VALUES(1,'One');";
echo "\nRecord Inserted";

$sth = odbc_prepare($conn, "INSERT INTO t1(f2) VALUES('Ten');");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(3);
}
echo "\nINSERT INTO t1(f2) VALUES('Ten');";
echo "\nRecord Inserted\n";

$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(4);
}
echo "\nselect executed\n";
odbc_result_all($rs);

$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
{
   echo "\nError in Drop Table";
   exit(5);
}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>

