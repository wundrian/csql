<html>
<body>
/* Testing odbc_num_rows() for display number of rows */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

//$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),primary key(f1));");
$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 SMALLINT,f4 BIGINT,f5 FLOAT, f6 DOUBLE,f7 DATE, f8 TIMESTAMP );");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(2);
}
echo "Table Created\n";

$sth = odbc_prepare($conn,"INSERT INTO t1 VALUES(20,'Twenty',2,10000001,10.01,10000001.000001,'2001-1-1','2001-11-30 01:01:01');");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(3);
}
echo "Record Inserted\n";

$sth = odbc_prepare($conn,"INSERT INTO t1 VALUES(30,'Thirty',3,20000002,20.02,20000002.000002,'2002-2-2','2002-22-30 02:02:02');");
$res = odbc_execute($sth);
if (!$res)
{
    echo "Error in Creation";
    exit(4);
}
echo "Record Inserted\n";

$sql = 'SELECT * FROM t1;';
$result = odbc_exec($conn, $sql);
echo "Number of rows = ";
$a=odbc_num_rows($result);
if (!$a)
{
    odbc_exec($conn,"DROP TABLE t1;");
    exit(5);
}
echo $a;

$sql = "SELECT f3,f5,f7 FROM t1";
$result = odbc_exec($conn, $sql);
echo "\n<table> \n";
while (odbc_fetch_row($result)) 
{
   $a=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($result,1));
   $b=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($result,2));
   $c=preg_replace('/[\x00-\x09\x0B-\x19\x7F]/', '',odbc_result($result,3));
   echo "<tr>";
   echo "<td>$a</td><td>$b</td><td>$c</td></tr>";
   echo "\n";
}
echo "</table>";
$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
{
   echo "\nError in Drop Table";
   exit(6);
}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>
