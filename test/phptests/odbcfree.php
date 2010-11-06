<html>
<body>
/*Testing Querry Memory Free with odbc_free_result() */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 SMALLINT,f4 BIGINT,f5 FLOAT, f6 DOUBLE,f7 DATE, f8 TIMESTAMP );");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(2);
}
echo "Table Created\n";

$sql = 'SELECT f3,f5,f7 FROM t1';
$result = odbc_exec($conn, $sql);
echo "\nFreeing query Memory\n";

$freeing = odbc_free_result($result);
if (!$res)
{
  exit(3);
}
echo "Query memory freed\n";

$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
{
  echo "\nError in Drop Table";
  exit(4);
}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>
