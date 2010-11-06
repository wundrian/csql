<html>
<body>
/*Testing odbc_field_type for find out the type of a field    */
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

$sql = "SELECT * FROM t1"; 
$result = odbc_exec($conn, $sql); 

echo "\nTesting odbc_field_type() for find out column type\n";
for ($col=1; $col<=odbc_num_fields($result); $col++) 
{
 $rs = odbc_field_type($result, $col);
 if (!$rs)
 {
   exit(3);
 }
 printf("Column %d har type  %s\n" ,$col, odbc_field_type($result, $col));
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
