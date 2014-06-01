<?php
  include("corecode.inc");
  if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $delete_query = "delete from viewcountsbymonth where monthfull='".$thismonth."';";
  $mysqli->query($delete_query);
?>
