<html>
<body>
/*Creating table with 3 INT fields, Create unique index on single field.
   Create possible composite unique indexes in different Combinations
*/
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

$sth = odbc_prepare($conn,"create table t1 (f1 int ,f2 int,f3 int );");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Table Creation";
  exit(2);
}
echo "Table Created";

$sth = odbc_prepare($conn, "create index idx1 on t1(f1) unique;");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in index";
  exit(3);
}
echo "\ncreate index idx1 on t1(f1) unique;";
echo "\nIndex created\n";

$sth = odbc_prepare($conn, "create index idx2 on t1(f1,f2)  unique;");
$res = odbc_execute($sth);
if (!$res)
{
   echo "\ncreate index idx1 on t1(f1) unique;";
   exit(4);
}
echo "\ncreate index idx2 on t1(f1,f2) unique;";
echo "\nComposite key Index created\n";

$sth = odbc_prepare($conn, "create index idx5 on t1(f1,f2,f3) unique;");
$res = odbc_execute($sth);
if (!$res)
{
   echo "\nError in index creation;";
   exit(5);
}
echo "\ncreate index idx5 on t1(f1,f2,f3) unique;";
echo "\nComposite key Index created\n";

$res = odbc_exec($conn, "DROP TABLE t1;");
if (!$res)
{
   echo "\ncError in drop table;";
   exit(6);
}
echo "\nTable Dropped\nTest Passed";
odbc_close($conn);
?>

</body>
</html>

