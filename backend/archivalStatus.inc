<?php

function getPageListByArchivalStatus($archivalStatus,$language)
{
  global $mysqli;
  global $pageDisplayLimit;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $select_query = "select distinct pagename from queriedpages where archivalstatus='".$archivalStatus."' and language='".$language."' limit ".$pageDisplayLimit.";";
  #print $select_query;
  $result = $mysqli->query($select_query);
  $pageList = array();
  for ($i = 0; $i < $result->num_rows;$i++)
    {
      $row = $result->fetch_assoc();
      $pagename = $row['pagename'];
      array_push($pageList,$pagename);
    }
  return $pageList;
}

?>
