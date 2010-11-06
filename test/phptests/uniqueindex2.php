<html>
<body>
/* Creating table  with 2 fields(int,char)
   Insert some duplicate value in f1 field
   Create unique index on f1 field. It should be failed saying Unique key Violation. 
   check basic INSERT, SELECT */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

$sth = odbc_prepare($conn,"create table t1 (f1 int, f2 char(20));");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(2);
}
echo "Table Created";

$sth = odbc_prepare($conn, "insert into t1 values (10, 'TEN');");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(3);
}
echo "\nRecord Inserted";

$sth = odbc_prepare($conn, "insert into t1 values (10, 'ten');");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Insertion";
  exit(4);
}
echo "\nRecord Inserted\n";

$sth = odbc_prepare($conn, "create index idx1 on t1(f1) unique;");
$res = odbc_execute($sth);
if ($res)
{
  odbc_exec($conn,"DROP TABLE t1;"); 
  echo("Error in Unique Index\nTest Failed");
}

echo "\nUnique key can not be applied if duplicate record is available before\n";


$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  echo "Error in SQL-2";
  exit(5);
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

$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
{
  echo "\nError in Drop Table";
  exit(6);
}
echo "\nTable Dropped\nTest Passed";
odbc_close($conn);
?>

</body>
</html>

