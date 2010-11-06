<html>
<body>
/*Testing  odbc_fetch_array()*/
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
  {echo "Connection Failed";exit(1);}

odbc_exec($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 SMALLINT,f4 BIGINT,f5 FLOAT, f6 DOUBLE,f7 DATE, f8 TIMESTAMP );");
odbc_exec($conn,"INSERT INTO t1(f1,f3,f4) values(10,'ABCD',100001);");
odbc_exec($conn,"INSERT INTO t1(f1,f2,f3) values(20,'BCAD',1);");

$sql = 'SELECT * from t1;';
$result = odbc_exec($conn, $sql);

while ($row = odbc_fetch_array($result)) 
{   
    echo $row["f1"], "\n";
}
//fetch array is not working:remove below 2 lines after it is fixed
odbc_exec($conn,"DROP TABLE t1;");
exit(1);
$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
  {echo "\nError in Drop Table"; exit(2);}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>
