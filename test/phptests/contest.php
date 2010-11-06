<html>
<body>
//Connection Testing
<?php
$conn=odbc_connect('mycsql','root','manager');
if (!$conn)
{
   echo "Connection Failed";
   exit(1);
}
echo "Connection Passed";
?>
</body>
</html>
