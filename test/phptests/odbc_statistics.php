<html>
<body>
/*Testing  odbc_statistics()*/
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed ";
  exit(1);
}

odbc_exec($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 SMALLINT,f4 BIGINT);");
odbc_exec($conn,"INSERT INTO t1(f1,f3,f4) values(10,'ABCD',100001);");
odbc_exec($conn,"INSERT INTO t1(f1,f2,f3) values(20,'BCAD',1);");

$result = odbc_statistics($conn,"test","","t1",0,0);
odbc_result_all($result);
if (!$conn)
{
  exit(2);
}

$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
  {exit("\nError in Drop Table");}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>
