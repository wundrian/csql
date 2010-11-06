<html>
<body>
/* Creating table with Primary key constraint constraint on the int field
   check basic INSERT, SELECT */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

$sth = odbc_prepare($conn,"create table t1 (f1 int , f2 int, primary key(f1));");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(2);
}
echo "Table Created";

$sth = odbc_prepare($conn, "insert into t1 values (10, 20);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(3);
}
echo "\nRecord Inserted\n";

$res = odbc_exec($conn, "insert into t1 values (10, 30);");

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
echo "\nTable Dropped\nTest Passed\n";
odbc_close($conn);
?>
</body>
</html>

