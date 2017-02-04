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
  $tagSelectQuery = "select distinct pagetags.pagename from pagetags where pagetags.language='".$language."' and pagetags.tag='".$tag."' order by pagetags.pagename asc;";
  $result = $mysqli->query($tagSelectQuery);
  # print "tagSelectQuery = ".$tagSelectQuery."<br>";
  $pageList = array();
  for ($i = 0; $i < $result->num_rows;$i++) {
    $row = $result->fetch_assoc();
    $pagename = $row['pagename'];
    array_push($pageList,$pagename);
  }
  return $pageList;
}

function getTagTotal($tag,$language,$drilldown,$monthList,$online=true,$normalization='') {
  global $mysqli;
  global $cannotRetrieveMessage;
  global $exceededQueryLimitMessage;
  global $attemptedExternalQueryCount;
  global $attemptedExternalQueryLimit;
  global $tagProperQueryLimit;
  global $irretrievableCount; # Number of tag-language-drilldown-month combinations that are irretrievable
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $pageList = getPageListByTag($tag, $language);
  $pagecount = count($pageList);
  $retrievableMonthList = [];
  $irretrievableMonthList = [];
  $queryMonthList = [];
  foreach($monthList as $month) {
    if ($drilldown == "desktop" or ($month >= '201507' and $drilldown != "cumulative-facebook-shares") or ($month >= '201610')) {
      array_push($retrievableMonthList, $month);
    } else {
      array_push($irretrievableMonthList, $month);
    }
  }
  foreach($retrievableMonthList as $month) {
    $monthTotal[$month] = 'unavailable';
  }
  foreach($irretrievableMonthList as $month) {
    $irretrievableCount++;
    $monthTotal[$month] = $cannotRetrieveMessage;
  }
  $retrievableMonthListAsQuotedCsvString = convertListToQuotedCsvString($retrievableMonthList);
  $selectQuery = "select viewcount,pagecount,querytime from viewcountsbytagandmonth where tag=\"".$tag."\" and monthfull in'".$retrievableMonthListAsQuotedCsvString."' and language='".$language."' and drilldown='".$drilldown."' limit 1;";
  $result = $mysqli -> query($selectQuery);
  for ($i = 0; $i < $result -> num_rows; $i++) {
    $row = $result -> fetch_assoc();
    if ($row['pagecount'] == count($pageList)) { # Quick sanity check that this is the right tag and no additions were made to it; not foolproof
      $monthTotal[$row['monthfull']] = $row['viewcount'];
    }
  }

  # Now add all the months that didn't get filled in, to a query month list
  foreach($retrievableMonthList as $month) {
    if ($monthTotal[$month] == 'unavailable') {
      array_push($queryMonthList, $month)
    }
  }

  if ($online == true and $attemptedExternalQueryCount < $attemptedExternalQueryLimit and count($pageList) * count($monthList) < $tagProperQueryLimit) {
    $viewCountArray = viewCountArrayByMonth($pageList,array($language),array($drilldown),$queryMonthList,$online,$normalization);
    $tap = totalsAndPercentages($pageList,array($language),array($drilldown),$queryMonthList,$viewCountArray);
    $pageviewRetrievedMonthTotal = $tap["monthOrYearTotal"];
    foreach($queryMonthList as $month) {
      $viewcount = $pageviewRetrievedMonthTotal[$month];
      $monthTotal[$month] = $viewcount;
      if ($attemptedExternalQueryCount < $attemptedExternalQueryLimit) {
        $deleteQuery = "delete from viewcountsbytagandmonth where tag=\"".$tag."\" and language='$language' and drilldown='$drilldown' and month='$month'";
        $deleteResult = $mysqli -> query($deleteQuery);
        $insertQuery = "insert into viewcountsbytagandmonth(tag, language, drilldown, monthfull, viewcount, pagecount) values(\"".$tag."\",'$language','$drilldown','$month',$viewcount,$pagecount)";
        $insertResult = $mysqli -> query($insertQuery);
      }
    }
  } else {
    $pageListAsQuotedCsvString = convertListToQuotedCsvString($pageList);
    $queryMonthListAsQuotedCsvString = convertListToQuotedCsvString($queryMonthList);
    $tagTotalQuery = "select monthfull,coalesce(sum(viewcount),0) as total from viewcountsbymonth where pagename in (".$pageListAsQuotedCsvString.") and monthfull in (".$queryMonthListAsQuotedCsvString.") and language='$language' and drilldown='$drilldown' group by monthfull;";
    $tagTotalResult = $mysqli->query($tagTotalQuery);
    for($i = 0; $i < $tagTotalResult -> num_rows; $i++) {
      $row = $tagTotalResult -> fetch_assoc();
      $monthTotal[$row['monthfull']] = $row['total'];
    }
  }
  return $monthTotal;
}

function getTagTotalByYear($tag,$language,$drilldown,$yearList,$online=true,$normalization='') {
  global $mysqli;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $pageList = getPageListByTag($tag,$language);
  $viewCountArray = viewCountArrayByYear($pageList,array($language),array($drilldown),$yearList,$online,$normalization);
  $tap = totalsAndPercentages($pageList,array($language),array($drilldown),$yearList,$viewCountArray);
  return $tap["monthOrYearTotal"];
}

function viewCountArrayByTagAndMonth_raw($tagList,$languageList,$drilldownList,$monthList,$online=true,$normalization='') {
  foreach ($tagList as $tag) {
    foreach ($languageList as $language) {
      foreach ($drilldownList as $drilldown) {
        $tagTotal = getTagTotal($tag,$language,$drilldown,$monthList,$online,$normalization);
        foreach ($monthList as $month) {
          $viewCountArray[$tag][$language][$drilldown][$month] = $tagTotal[$month];
        }
      }
    }
  }
  return $viewCountArray;
}

function viewCountArrayByTagAndMonth($tagList,$monthList,$language='en',$drilldownList,$online=true,$normalization='') {
  global $exceededQueryLimitMessage;
  global $numberofdays_allmonths;
  $viewCountArray = viewCountArrayByTagAndMonth_raw($tagList,$monthList,$language,$drilldownList,$online,$normalization);
  if ($normalization == '')
    {
      return $viewCountArray;
    }
  elseif ($normalization == 'dailyaverage') {
    foreach ($tagList as $tag) {
      foreach ($monthList as $month) {
        foreach ($drilldownList as $drilldown) {
	  if ($viewCountArray[$tag][$month][$drilldown] != $exceededQueryLimitMessage) {
            $viewCountArray[$tag][$month][$drilldown] = round($viewCountArray[$tag][$month][$drilldown]/intval($numberofdays_allmonths[$month]),1);
          }
	}
      }
    }
  }
  return $viewCountArray;
}

function viewCountArraybytagandyear($tagList,$languageList,$drilldownList,$yearList,$online=true,$normalization='') {
  foreach ($tagList as $tag) {
    foreach ($languageList as $language) {
      foreach ($drilldownList as $drilldown) {
        $tagTotal = getTagTotalByYear($tag,$language,$drilldown,$yearList,$online,$normalization);
        foreach ($yearList as $year) {
	  $viewCountArray[$tag][$language][$drilldown][$year] = $tagTotal[$year];
        }
      }
    }
  }
  return $viewCountArray;
}

function getPageListByTagList($tagList,$language,$connective='or') {
  global $mysqli;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $tagSelectQuery = "select distinct pagetags.pagename from pagetags where pagetags.language='".$language."' ";
  if ($connective=='or') {
    $tagListAsQuotedCsvString = convertListToQuotedCsvString($tagList);
    $tagSelectQuery .= "and pagetags.tag in (".$tagListAsQuotedCsvString.")";
  }
  $tagSelectQuery .= " order by pagetags.pagename asc;";
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
  $tagSelectQuery = "select distinct pagename,language,tag from pagetags where pagename in (".$pageListAsQuotedCsvString.") and language in (".$languageListAsQuotedCsvString.") order by pagename, tag;";
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
