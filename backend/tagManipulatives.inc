<?php

function checkTagPresence($tag) {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select tag from pagetags where tag='".$tag."' limit 1;";
  $result = $mysqli->query($select_query);
  return ($result->num_rows > 0);
}

function addPageToTag($page,$language,$tag) {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select tag from pagetags where pagename=\"".$page."\" and language='".$language."' and tag='".$tag."' limit 1;";
  $result = $mysqli->query($select_query);
  if ($result->num_rows==0)
    {
      $insert_query = "insert into pagetags(pagename,language,tag) values (\"".$page."\",'".$language."','".$tag."');";
      $insert_result = $mysqli->query($insert_query);
      queriedpagelog($page,$language,'empty');
    }
}

function getPageListByTag($tag,$language) {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $tagselect_query = "select distinct pagetags.pagename from pagetags join queriedpages where pagetags.pagename = queriedpages.pagename and pagetags.language = queriedpages.language and pagetags.language='".$language."' and pagetags.tag='".$tag."' order by pagetags.pagename asc;";
#print $tagselect_query;
  $result = $mysqli->query($tagselect_query);
  $pageList = array();
  for ($i = 0; $i < $result->num_rows;$i++)
    {
      $row = $result->fetch_assoc();
      $pagename = $row['pagename'];
      array_push($pageList,$pagename);
    }
  return $pageList;
}

function getTagTotal($tag,$monthList,$language='en',$drilldown,$online=true,$normalization='') {
  global $mysqli;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $pageList = getpageListByTag($tag,$language);
  $viewcountarray = viewcountarraybymonth($pageList,$monthList,$language,array($drilldown),$online,$normalization);
  $totalsAndPercentagesArray = totalsAndPercentages($pageList,$monthList,array($drilldown),$viewcountarray);
  return $totalsAndPercentagesArray[2];
}

function getTagTotalByYear($tag,$yearList,$language='en',$drilldown='desktop',$online=true,$normalization='') {
  global $mysqli;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $pageList = getPageListByTag($tag,$language);
  $viewcountarray = viewcountarraybyyear($pageList,$yearList,$language,array($drilldown),$online,$normalization);
  $totalsAndPercentagesArray = totalsAndPercentages($pageList,$yearList,array($drilldown),$viewcountarray);
  return $totalsAndPercentagesArray[2];
}

function viewcountarraybytagandmonth_raw($tagList,$monthList,$language,$drilldownList,$online=true,$normalization='') {
  foreach ($tagList as $tag) {
    foreach ($drilldownList as $drilldown) {
      $tagTotal = getTagTotal($tag,$monthList,$language,$drilldown,$online,$normalization);
      foreach ($monthList as $month) {
        $viewcountarray[$tag][$month][$drilldown] = $tagTotal[$month];
      }
    }
  }
  return $viewcountarray;
}

function viewcountarraybytagandmonth($tagList,$monthList,$language='en',$drilldownList,$online=true,$normalization='') {
  global $exceededQueryLimitMessage;
  global $numberofdays_allmonths;
  $viewcountarray = viewcountarraybytagandmonth_raw($tagList,$monthList,$language,$drilldownList,$online,$normalization);
  if ($normalization == '')
    {
      return $viewcountarray;
    }
  elseif ($normalization == 'dailyaverage') {
    foreach ($tagList as $tag) {
      foreach ($monthList as $month) {
        foreach ($drilldownList as $drilldown) {
	  if ($viewcountarray[$tag][$month][$drilldown] != $exceededquerylimitmesage) {
            $viewcountarray[$tag][$month][$drilldown] = round($viewcountarray[$tag][$month][$drilldown]/intval($numberofdays_allmonths[$month]),1);
          }
	}
      }
    }
  }
  return $viewcountarray;
}

function viewcountarraybytagandyear($tagList,$yearList,$language,$drilldownList,$online=true,$normalization='') {
  foreach ($tagList as $tag) {
    foreach ($drilldownList as $drilldown) {
      $tagTotal = getTagTotalByYear($tag,$yearList,$language,$drilldown,$online,$normalization);
      foreach ($yearList as $year) {
	$viewcountarray[$tag][$year][$drilldown] = $tagTotal[$year];
      }
    }
  }
  return $viewcountarray;
}

function getPageListByTagList($tagList,$language,$connective='or') {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $tagselect_query = "select distinct pagetags.pagename from pagetags join queriedpages where pagetags.pagename = queriedpages.pagename and pagetags.language = queriedpages.language and pagetags.language='".$language."' and queriedpages.archivalStatus='complete'";
  if ($connective=='or')
    {
      $tagListasquotedcsvstring = convertListToQuotedCsvString($tagList);
      $tagselect_query .= "and pagetags.tag in (".$tagListasquotedcsvstring.")";
    }
  $tagselect_query .= "order by pagetags.pagename asc;";
  $result = $mysqli->query($tagselect_query);
  $pageList = array();
  for ($i = 0; $i < $result->num_rows;$i++)
    {
      $row = $result->fetch_assoc();
      $pagename = $row['pagename'];
      array_push($pageList,$pagename);
    }
  return $pageList;
}

function getTagListByPageList($pageList,$language) {
  global $mysqli;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  foreach ($pageList as $page) {
    $tagList[$page] = array();
  }
  $pageListAsQuotedCsvString = convertListToQuotedCsvString($pageList);
  $tagSelectQuery = "select distinct pagename,tag from pagetags where pagename in (".$pageListAsQuotedCsvString.") and language='".$language."' order by pagename, tag;";
  flush();
  $result = $mysqli->query($tagSelectQuery);
  for ($i = 0;$i < $result -> num_rows; $i++) {
    $row = $result -> fetch_assoc();
    array_push($tagList[$row['pagename']],$row['tag']);
  }
  return $tagList;
}

function getTagIndices($pageList,$language) {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $pageListasquotedcsvstring = convertListToQuotedCsvString($pageList);
  $tagselect_query = "select distinct tag from pagetags where pagename in (".$pageListasquotedcsvstring.") and language='".$language."';";
  $result = $mysqli->query($tagselect_query);
  for ($i = 0;$i < $result -> num_rows; $i++)
    {
      $row = $result -> fetch_assoc();
      $tagindices[$row['tag']] = $i;
    }
  return $tagindices;
}

?>
