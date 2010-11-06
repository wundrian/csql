<html>
<body>
/*Testing  odbc_next_result, var_dump  for find next result*/
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
  {echo "Connection Failed" ; exit(1);}


odbc_exec($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 int);");
odbc_exec($conn,"INSERT INTO t1 values(10,'ABCD',1);");
odbc_exec($conn,"INSERT INTO t1 values(20,'PQRS',2);");

$sql = <<<END_SQL
SELECT * from t1;
END_SQL;

$result = odbc_exec($conn, $sql);

echo "Get First results set\n";
$r1 = odbc_fetch_array($result);
$r2 = odbc_fetch_array($result);
echo "Dump first result set\n";
var_dump($r1, $r2);

echo "Get second results set\n";
var_dump(odbc_next_result($result));

$r1 = odbc_fetch_array($result);
$r2 = odbc_fetch_array($result);
echo "Dump 2nd result set\n";
var_dump($r1, $r2);

$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
  {echo "\nError in Drop Table";exit(2);}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>
