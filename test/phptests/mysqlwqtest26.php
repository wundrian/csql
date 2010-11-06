<html>
<body>
<?php
/*Performance Test for all parameterised DML*/

$conn=odbc_connect('mycsql','root','');
if (!$conn)
  {exit("Connection Failed: " . $conn);}
echo "Connection Passed\n";

$sth = odbc_prepare($conn,"CREATE TABLE t1 (f1 BIGINT, f2 char(196), primary key (f1));");
$res = odbc_execute($sth);
if (!$res)
  {exit("Error in Creation");}
echo "Table Created\n";

 $timecount = 0;
 $min = 1;
 $max = 0;
 $time_start = 0;
 $time_end = 0;
 $time = 0;
 $count =0;
 $q = "INSERT INTO t1(f1,f2) values(?,?);";
 $b = "ABCDEFGHIJKLMNOPQRSTUVWXYZ9876543210";
 $res = odbc_prepare ($conn, $q);
 for ($i = 0; $i <100; $i++)
 {
   $time_start = microtime();
   $a = $i; 
   odbc_execute($res, array($a, $b));
   $time_end = microtime();
   $time = $time_end - $time_start;
   $timecount = $timecount + $time ;
   if ($min > $time)
      {$min = $time;} 
   if ($max < $time)
      {$max = $time;} 
   $count++;
 }
 printf("\nInsert :%6d  MIN :%4f  MAX :%4f AVG :%4f microsec\n",$count,$min,$max,$timecount/$count);

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
  {exit("Error in SQL-2");}
odbc_result_all($rs, 'border = 2');

 $timecount = 0;
 $min = 1;
 $max = 0;
 $time_start = 0;
 $time_end = 0;
 $time = 0;
 $count =0;
 $q = "SELECT * FROM t1 WHERE f1=?;";
 $res = odbc_prepare ($conn, $q);
 for ($i = 0; $i <100; $i++)
 {
   $time_start = microtime();
   $a = $i; 
   $rs=odbc_execute($res, array($a));

   echo "<table><tr>";
   echo "<th>ROLL</th>";
   echo "<th>NAME</th></tr>";
   while (odbc_fetch_row($rs))
   {
     $roll=odbc_result($rs, 1);
     $name=odbc_result($rs, 2);
     echo "<tr><td>$roll</td>";
     echo "<td>$name</td></tr>\n";
   }
   echo "</table>";

   $time_end = microtime();
   $time = $time_end - $time_start;
   $timecount = $timecount + $time ;
   if ($min > $time)
      {$min = $time;} 
   if ($max < $time)
      {$max = $time;} 
   $count++;
 }
 printf("\nSelect :%6d  MIN :%4f  MAX :%4f AVG :%4f microsec\n",$count,$min,$max,$timecount/$count);

 $timecount = 0;
 $min = 1;
 $max = 0;
 $time_start = 0;
 $time_end = 0;
 $time = 0;
 $count =0;
 $q = "update t1 set f2=? where f1=?;";
 $res = odbc_prepare ($conn, $q);
 for ($i = 0; $i <100; $i++)
 {
   $time_start = microtime();
   $a = "LAKSHYA_CSQL"; 
   $b = $i;
   odbc_execute($res, array($a, $b));
   $time_end = microtime();
   $time = $time_end - $time_start;
   $timecount = $timecount + $time ;
   if ($min > $time)
      {$min = $time;} 
   if ($max < $time)
      {$max = $time;} 
   $count++;
 }
 printf("\nUpdate :%6d  MIN :%4f  MAX :%4f AVG :%4f microsec\n",$count,$min,$max,$timecount/$count);

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
  {exit("Error in SQL-2");}
odbc_result_all($rs, 'border = 2');

 $timecount = 0;
 $min = 1;
 $max = 0;
 $time_start = 0;
 $time_end = 0;
 $time = 0;
 $count =0;
 $q = "DELETE FROM t1 WHERE f1=?;";
 $res = odbc_prepare ($conn, $q);
 for ($i = 0; $i <100; $i++)
 {
   $time_start = microtime();
   $a = $i; 
   $rs = odbc_execute($res, array($a));
   $time_end = microtime();
   $time = $time_end - $time_start;
   $timecount = $timecount + $time ;
   if ($min > $time)
      {$min = $time;} 
   if ($max < $time)
      {$max = $time;} 
   $count++;
 }
 printf("\nDelete :%6d  MIN :%4f  MAX :%4f AVG :%4f microsec\n",$count,$min,$max,$timecount/$count);

$sth = 'SELECT * FROM t1;';
$rs = odbc_exec($conn, $sth);
if (!$rs)
  {exit("Error in SQL-2");}
odbc_result_all($rs, 'border = 2');

$sth=odbc_prepare($conn,"DROP TABLE t1;");
$res = odbc_execute($sth);
if (!$res)
  {exit("\nError in Drop Table");}
echo "\nTable Dropped \nTest Passed";
odbc_close($conn);

?>
</body>
</html>
