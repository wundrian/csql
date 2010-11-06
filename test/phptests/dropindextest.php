<html>
<body>
/* Creating table with 2 fields(say f1 int, f2 char(10)).
   Create index idx1 on f1 field. Drop that index.Again create index with same name. It should be Passed. 
   check basic INSERT, SELECT */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

$sth = odbc_prepare($conn,"create table t1 (f1 int ,f2 char(10));");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Table Creation";
  exit(2);
}
echo "Table Created";

$sth = odbc_prepare($conn, "create index idx1 on t1(f1);");
$res = odbc_execute($sth);
if (!$res)
{
  echo " error in index creation";
  exit(3);
}
echo "\ncreate index idx1 on t1(f1);";
echo "\nIndex created\n";

$sth = odbc_prepare($conn, "drop index idx1;");
$res = odbc_execute($sth);
if (!$res)
{
 odbc_exec($conn, "DROP TABLE t1;");
 echo "\nError in Drop Index\nTest Failed\n";
 exit(4);
}
echo "\ndrop index idx1;";
echo "\nIndex idx1 dropped\n";

$sth = odbc_prepare($conn, "create index idx1 on t1(f1);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in index Creation";  
  exit(5);
}
echo "\ncreate index idx1 on t1(f1);";
echo "\nIndex created\n";

//$sth=odbc_prepare($conn,"DROP TABLE t1");
$res = odbc_exec($conn, "DROP TABLE t1;");
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

