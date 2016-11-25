<?php

function languages_sql() {
  global $mysqli;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $selectQuery = "select code,name,datastart from languages order by (rank is null),rank,code;";
  return $mysqli->query($selectQuery);
}

function dataStartMap() {
  $languageResponse = languages_sql();
  for ($i = 0; $i < $languageResponse -> num_rows; $i++) {
    $languageData = $languageResponse -> fetch_assoc();
    $dataStartMap[$languageData['code']] = $languageData['datastart'];
  }
  return $dataStartMap;
}
?>
