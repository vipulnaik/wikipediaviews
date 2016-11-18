<?php

function languages_sql() {
  global $mysqli;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $select_query = "select code,name from languages order by (rank is null),rank,code;";
  return $mysqli->query($select_query);
}
?>
