<html>
<body>
/*Create table and test all DML Operation on the table */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
   echo "Connection Failed";
   exit(1);
}

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20));");
$res = odbc_execute($sth);
if (!$res)
{
   echo "Error in Creation";
   exit(2);
}
echo "Table Created";

$sth = odbc_prepare($conn, "INSERT INTO t1(f1, f2) VALUES(12,'Lakshye');");
$res = odbc_execute($sth);
if (!$res)
{
   echo "Error in Insertion";
   exit(3);
}
echo "\nRecord Inserted";
$sth = odbc_prepare($conn, "INSERT INTO t1(f1, f2) VALUES(13,'CSQL');");
$res = odbc_execute($sth);
if (!$res)
{
   echo "Error in Insertion";
   exit(3);
}
echo "\nRecord Inserted";

$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
   echo "Error in selection";
   exit(4);
}
echo "\nselect executed\n";

echo "<table><tr>";
echo "<th>ROLL</th>";
echo "<th>NAME</th></tr>";
echo "\nfetch started\n";
while (odbc_fetch_row($rs))
{
  $roll=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($rs, 1));
  $name=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($rs, 2));
  echo "<tr><td>$roll</td>";
  echo "<td>$name</td></tr>\n";
}
echo "</table>";

$sth = odbc_prepare($conn, "UPDATE t1 SET f2='TWELVE' WHERE f1=12;");
$res = odbc_execute($sth);
if (!$res)
{
   echo "\nError in Updation\n";
   exit(5);
}
echo "\nRecord Updated\n";

$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
while (odbc_fetch_row($rs))
{
  $roll=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($rs, 1));
  $name=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($rs, 2));
  echo "<tr><td>$roll</td>";
  echo "<td>$name</td></tr>\n";
}
echo "</table>";

$sth = odbc_prepare($conn, "DELETE FROM t1 WHERE f1=13;");
$res = odbc_execute($sth);
if (!$res)
{
   echo "\nError in Deletion\n";
   exit(6);
}
echo "\nRecord Deleted\n";

$sth = 'select * from t1;';
$rs = odbc_exec($conn, $sth);
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
   exit(7);
}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>
</body>
</html>

