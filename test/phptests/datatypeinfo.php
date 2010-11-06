<html>
<body>
/*Testing for get all Datatype info of a database with odbc_gettypeinfo()*/
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
  echo "Connection Failed";
  exit(1);
}

echo "\nDisplaying data type information. ";
$result = odbc_gettypeinfo($conn);
if (!$result)
{
  exit(2);
}
$rs = odbc_result_all($result);
if (!$rs)
{
  exit(3);
}

echo "Test Passed\n";
odbc_close($conn);
?>

</body>
</html>
