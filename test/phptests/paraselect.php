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
  exit(2);
}
echo "Table Created\n";

$res = odbc_exec($conn,"INSERT INTO t1 values(10,'ABCD',1);");
if (!$res)
{
  exit(3);
}
echo "Table Created\n";

$res = odbc_exec($conn,"INSERT INTO t1 values(20,'PQRS',2);");
if (!$res)
{
  exit(4);
}
echo "Table Created\n";

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  exit(5);
}
odbc_result_all($rs, 'border = 5');

$q = "SELECT * FROM t1 WHERE f1=?;";
$res = odbc_prepare ($conn, $q);
$a = 10;
$res1 = odbc_execute($res, array($a));
if (!$res)
{
  exit(6);
}

   echo "<table><tr>";
   echo "<th>ROLL</th>";
   echo "<th>NAME</th></tr>";
   while (odbc_fetch_row($res))
   {
     $roll=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($res, 1));
     $name=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($res, 2));
     echo "<tr><td>$roll</td>";
     echo "<td>$name</td></tr>\n";
   }
   echo "</table>";


$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
  {exit("\nError in Drop Table");}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>
