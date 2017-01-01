<?php

function getPageListByViewBound($viewbound,$monthOrYearfilter,$language='en',$monthOrYearAdvice='month')
{
  global $mysqli;
  global $pageDisplayLimit;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  if ($monthOrYearAdvice=='month')
    $select_query = "select distinct pagename from viewcountsbymonth where language='".$language."' and viewcount >=".$viewbound." and monthfull='".$monthOrYearfilter."' limit ".$pageDisplayLimit.";";
  else
    $select_query = "select distinct pagename from viewcountsbyyear where language='".$language."' and viewcount >=".$viewbound." and year='".$monthOrYearfilter."' limit ".$pageDisplayLimit.";";
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
