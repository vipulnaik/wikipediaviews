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
      queriedPageLog($page,$language,'empty');
    }
}

function getPageListByTag($tag,$language) {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $tagselect_query = "select distinct pagetags.pagename from pagetags where pagetags.language='".$language."' and pagetags.tag='".$tag."' order by pagetags.pagename asc;";
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

function getTagTotal($tag,$language,$drilldown,$monthList,$online=true,$normalization='') {
  global $mysqli;
  global $cannotRetrieveMessage;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $pageList = getPageListByTag($tag,$language);
  $retrievableMonthList = [];
  $irretrievableMonthList = [];
  foreach($monthList as $month) {
    if ($drilldown == "desktop" or ($month >= '201507' and $drilldown != "cumulative-facebook-shares") or ($month >= '201610')) {
      array_push($retrievableMonthList, $month);
    } else {
      array_push($irretrievableMonthList, $month);
    }
  }
  $viewcountarray = viewcountarraybymonth($pageList,$retrievableMonthList,$language,array($drilldown),$online,$normalization);
  $tap = totalsAndPercentages($pageList,array($language),array($drilldown),$monthList,$viewcountarray);
  $monthTotal = $tap["monthOrYearTotal"];
  foreach($irretrievableMonthList as $month) {
    $monthTotal[$month] = $cannotRetrieveMessage;
  }
  return $monthTotal;
}

function getTagTotalByYear($tag,$language,$drilldown,$yearList,$online=true,$normalization='') {
  global $mysqli;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $pageList = getPageListByTag($tag,$language);
  $viewcountarray = viewcountarraybyyear($pageList,array($language),array($drilldown),$yearList,$online,$normalization);
  $tap = totalsAndPercentages($pageList,array($language),array($drilldown),$yearList,$viewcountarray);
  return $tap["monthOrYearTotal"];
}

function viewcountarraybytagandmonth_raw($tagList,$languageList,$drilldownList,$monthList,$online=true,$normalization='') {
  foreach ($tagList as $tag) {
    foreach ($languageList as $language) {
      foreach ($drilldownList as $drilldown) {    
        $tagTotal = getTagTotal($tag,$language,$drilldown,$monthList,$online,$normalization);
        foreach ($monthList as $month) {
          $viewcountarray[$tag][$language][$drilldown][$month] = $tagTotal[$month];
        }
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
  $tagSelectQuery = "select distinct pagetags.pagename from pagetags where pagetags.language='".$language."' ";
  if ($connective=='or')
    {
      $tagListAsQuotedCsvString = convertListToQuotedCsvString($tagList);
      $tagselect_query .= "and pagetags.tag in (".$tagListAsQuotedCsvString.")";
    }
  $tagSelectQuery .= "order by pagetags.pagename asc;";
  $result = $mysqli->query($tagSelectQuery);
  $pageList = array();
  for ($i = 0; $i < $result->num_rows;$i++)
    {
      $row = $result->fetch_assoc();
      $pagename = $row['pagename'];
      array_push($pageList,$pagename);
    }
  return $pageList;
}

function getTagListByPageList($pageList,$languageList) {
  global $mysqli;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  foreach ($pageList as $page) {
    foreach ($languageList as $language) {
      $tagList[$page][$language] = array();
    }
  }
  $pageListAsQuotedCsvString = convertListToQuotedCsvString($pageList);
  $languageListAsQuotedCsvString = convertListToQuotedCsvString($languageList);
  $tagSelectQuery = "select distinct pagename,tag from pagetags where pagename in (".$pageListAsQuotedCsvString.") and language in (".$languageListAsQuotedCsvString.") order by pagename, tag;";
  flush();
  $result = $mysqli->query($tagSelectQuery);
  for ($i = 0;$i < $result -> num_rows; $i++) {
    $row = $result -> fetch_assoc();
    array_push($tagList[$row['pagename']][$row['language']],$row['tag']);
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
