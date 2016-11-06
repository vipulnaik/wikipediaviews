<?php

function getpageListbyviewbound($viewbound,$monthoryearfilter,$language='en',$monthoryearadvice='month')
{
  global $mysqli;
  global $pagedisplaylimit;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  if ($monthoryearadvice=='month')
    $select_query = "select distinct pagename from viewcountsbymonth_all where language='".$language."' and viewcount >=".$viewbound." and monthfull='".$monthoryearfilter."' limit ".$pagedisplaylimit.";";
  else
    $select_query = "select distinct pagename from viewcountsbyyear where language='".$language."' and viewcount >=".$viewbound." and year='".$monthoryearfilter."' limit ".$pagedisplaylimit.";";
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
