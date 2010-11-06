<html>
<body>
/* Creating table with not null constraint constraint on the int field
   check basic INSERT, SELECT */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo"Connection Failed";
  exit(1);
}

$sth = odbc_prepare($conn,"create table t1 (f1 int not null, f2 int);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(2);
}
echo "Table Created\n";

$res = odbc_exec($conn, "insert into t1 values (10, 20);");
echo $res ;
if (!$res)
{
  echo "Error in Insertion";
  exit(3);
}
echo "\nRecord Inserted\n";

$res = odbc_exec($conn,"insert into t1 values (null, 20);");

$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2" ;
  exit(4);
}
echo "\nselect executed\n";
echo "<table><tr>";
echo "<th>F1</th>";
echo "<th>F2</th></tr>";
echo "\nfetch started\n";
while (odbc_fetch_row($rs))
{
  $roll=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($rs, 1));
  $name=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($rs, 2));
  echo "<tr><td>$roll</td>";
  echo "<td>$name</td></tr>\n";
}
echo "</table>";

$sth=odbc_prepare($conn,"DROP TABLE t1");
$res = odbc_execute($sth);
if (!$res)
{
  echo "\nError in Drop Table";
  exit(5);
}
echo "\nTable Dropped\nTest Passed";
odbc_close($conn);
?>

</body>
</html>

