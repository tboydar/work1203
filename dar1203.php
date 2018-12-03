<?php

$data = $_GET['command'];  // http://106.187.54.242/upload/dar1203.php?command=123

$saveF = fopen("dar1203.txt","w");

fwrite($saveF,$data);

fclose($saveF);

print($data);

?>


