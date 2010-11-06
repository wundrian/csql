<html>
<body>
/*Testing Autocommit, Commit and rollback */
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

$sth = odbc_prepare($conn,"CREATE TABLE t1(f1 INT, f2 CHAR(20),f3 SMALLINT,f4 BIGINT);");
$res = odbc_execute($sth);
if (!$res)
{
  echo "Error in Creation";
  exit(2);
}
echo "Table Created\n";

$ss = odbc_autocommit($conn,FALSE);
if (!$ss)
{
  $sth=odbc_prepare($conn,"DROP TABLE t1;");
  $res = odbc_execute($sth);
  exit(3);
}

$query1 = "INSERT INTO t1(f1,f3,f4) values(10,'ABCD',100001);";
$query2 = "INSERT INTO t1(f1,f2,f3) values(20,'BCAD',1);";

$ErrorCount = 0;
//if odbc_exec fails it will increment the $ErrorCount
$result1 = odbc_exec($conn,$query1) or $ErrorCount++;
if (!$result1)
{
  $sth=odbc_prepare($conn,"DROP TABLE t1;");
  $res = odbc_execute($sth);
  exit(4);
}

$result2 = odbc_exec($conn,$query2) or $ErrorCount++;
if (!$result2)
{
  $sth=odbc_prepare($conn,"DROP TABLE t1;");
  $res = odbc_execute($sth);
  exit(5);
}

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  $sth=odbc_prepare($conn,"DROP TABLE t1;");
  $res = odbc_execute($sth);
  exit(6);
}
odbc_result_all($rs, 'border = 2');

//checking for errors, commit if none, rollback else
if($ErrorCount == 0)
{
    $res = odbc_commit($conn);
    if (!$res)
    {
      $sth=odbc_prepare($conn,"DROP TABLE t1;");
      $res = odbc_execute($sth);
      exit(7);
    }
    echo "Transaction successful\n";
}
else
{
    $res = odbc_rollback($conn);
    if (!$res)
    {
      $sth=odbc_prepare($conn,"DROP TABLE t1;");
      $res = odbc_execute($sth);
      exit(8);
    }
    echo "there were errors processing the transaction.\nNo changes were made to the database\n";
}

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
{
  $sth=odbc_prepare($conn,"DROP TABLE t1;");
  $res = odbc_execute($sth);
  exit(9);
}

$rs = odbc_result_all($rs, 'border = 2');
if (!$rs)
{
  $sth=odbc_prepare($conn,"DROP TABLE t1;");
  $res = odbc_execute($sth);
  exit(10);
}

$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
{
  echo "\nError in Drop Table";
  exit(11);
}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);
?>

</body>
</html>
