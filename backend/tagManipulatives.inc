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
  if ($result->num_rows==0) {
    $insertQuery = "insert into pagetags(pagename,language,tag) values (\"".$page."\",'".$language."','".$tag."');";
    $insertResult = $mysqli->query($insertQuery);
    $clearTagQuery = "delete from viewcountsbytagandmonth where tag=\"".$tag."\" and language='$language';";
    $clearTagResult = $mysqli->query($clearTagQuery);
    queriedPageLog($page,$language,'empty');
  }
}

function refreshTagCountLists() {
  global $mysqli;
  $truncationQuery = "truncate table tagsummary;";
  $truncationResult = $mysqli -> query($truncationQuery);
  $insertionQuery = "insert into tagsummary(tag, language, pagecount) select tag, language, count(*) from pagetags group by tag, language;";
  $insertionResult = $mysqli -> query($insertionQuery);
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
  global $thisMonth;
  global $purgePeriod;
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
  $selectQuery = "select monthfull,viewcount,pagecount,querytime from viewcountsbytagandmonth where tag=\"".$tag."\" and monthfull in (".$retrievableMonthListAsQuotedCsvString.") and language='".$language."' and drilldown='".$drilldown."';";
  $result = $mysqli -> query($selectQuery);
  for ($i = 0; $i < $result -> num_rows; $i++) {
    $row = $result -> fetch_assoc();
    if ($row['pagecount'] == $pagecount) { # Quick sanity check that this is the right tag and no additions were made to it; not foolproof
      if ($row['monthfull'] != $thisMonth) {
        $monthTotal[$row['monthfull']] = $row['viewcount'];
      } else {
        $currentDate = new DateTime("now");
        $dateOfRetrieval = new DateTime($row['querytime']); 
        $daysPassedAsDiff = date_diff($dateOfRetrieval,$currentDate);
        $daysPassed = intval($daysPassedAsDiff->d);
        if ($daysPassed <= $purgePeriod) {
          $monthTotal[$row['monthfull']] = $row['viewcount'];
        }
      }
    }
  }

  # Now add all the months that didn't get filled in, to a query month list
  foreach($retrievableMonthList as $month) {
    if ($monthTotal[$month] == 'unavailable') {    
      array_push($queryMonthList, $month);
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
        $deleteQuery = "delete from viewcountsbytagandmonth where tag=\"".$tag."\" and language='$language' and drilldown='$drilldown' and monthfull='$month'.";
        $deleteResult = $mysqli -> query($deleteQuery);
        $insertQuery = "insert into viewcountsbytagandmonth(tag, language, drilldown, monthfull, viewcount, pagecount) values(\"".$tag."\",'$language','$drilldown','$month',$viewcount,$pagecount)";
        $insertResult = $mysqli -> query($insertQuery);
      }
    }
  } else {
    $pageListAsQuotedCsvString = convertListToQuotedCsvString($pageList);
    $queryMonthListAsQuotedCsvString = convertListToQuotedCsvString($queryMonthList);
    $tagTotalQuery = "select monthfull,coalesce(sum(viewcount),0) as viewcount,count(*) as pagecount from viewcountsbymonth where pagename in (select distinct pagename from pagetags where tag=\"".$tag."\") and monthfull in (".$queryMonthListAsQuotedCsvString.") and language='$language' and drilldown='$drilldown' group by monthfull;";
    $tagTotalResult = $mysqli->query($tagTotalQuery);
    for($i = 0; $i < $tagTotalResult -> num_rows; $i++) {
      $row = $tagTotalResult -> fetch_assoc();
      $viewcount = $row['viewcount'];
      $month = $row['monthfull'];  
      $monthTotal[$row['monthfull']] = $viewcount;
      if ($row['pagecount'] == $pagecount) {
        $deleteQuery = "delete from viewcountsbytagandmonth where tag=\"".$tag."\" and language='$language' and drilldown='$drilldown' and monthfull='$month';";
        $deleteResult = $mysqli -> query($deleteQuery);
        $insertQuery = "insert into viewcountsbytagandmonth(tag, language, drilldown, monthfull, viewcount, pagecount) values(\"".$tag."\",'$language','$drilldown','$month',$viewcount,$pagecount);";
        $insertResult = $mysqli -> query($insertQuery);
      }
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

function viewCountArrayByTagAndMonth($tagList,$languageList,$drilldownList,$monthList,$online=true,$normalization='') {
  global $exceededQueryLimitMessage;
  global $numberofdays_allmonths;
  global $mostRecentMonth;
  $viewCountArray = viewCountArrayByTagAndMonth_raw($tagList,$languageList,$drilldownList,$monthList,$online,$normalization);
  if ($normalization == '') {
    return $viewCountArray;
  }
  elseif ($normalization == 'dailyaverage') {
    foreach ($tagList as $tag) {
      foreach ($languageList as $language) {
        foreach ($drilldownList as $drilldown) {
          foreach ($monthList as $month) {
	    if ($viewCountArray[$tag][$language][$drilldown][$month] != $exceededQueryLimitMessage) {
              $viewCountArray[$tag][$language][$drilldown][$month] = round($viewCountArray[$tag][$language][$drilldown][$month]/intval($numberofdays_allmonths[$month]),1);
            }
	  }
	}
      }
    }
  } elseif ($normalization == 'aggregate') {
    $aggregateViewCountArray = viewCountArrayByMonth(array("[aggregate]"),$languageList,$drilldownList,$monthList, true, '', '');
    # print "<br/><br/>Requested aggregateViewCountArray with languageList $languageList head ".$languageList[0].", drilldownList $drilldownList, head ".$drilldownList[0].", monthList $monthList, head ".$monthList[0]."<br/><br/>";
    $mostRecentAggregateViewCountArray = viewCountArrayByMonth(array("[aggregate]"),$languageList, $drilldownList, array($mostRecentMonth), true, '', '');
    foreach($tagList as $tag) {
      foreach ($languageList as $language) {    
        foreach ($drilldownList as $drilldown) {
          foreach ($monthList as $month) {
            if (($month >= '201507' or ($month >= '200802' and $drilldown == 'desktop')) and $viewCountArray[$tag][$language][$drilldown][$month] !== $exceededQueryLimitMessage and $viewCountArray[$tag][$language][$drilldown][$month] !== $cannotRetrieveMessage) {
              # print ("Scaling value ".$viewCountArray[$tag][$language][$drilldown][$month] .", multiplying by ". $mostRecentAggregateViewCountArray["[aggregate]"][$language][$drilldown][$mostRecentMonth] . ", then dividing by ". $aggregateViewCountArray["[aggregate]"][$language][$drilldown][$month]);
              $viewCountArray[$tag][$language][$drilldown][$month] = intval(($viewCountArray[$tag][$language][$drilldown][$month] * $mostRecentAggregateViewCountArray["[aggregate]"][$language][$drilldown][$mostRecentMonth]) / $aggregateViewCountArray["[aggregate]"][$language][$drilldown][$month]);
            }
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
