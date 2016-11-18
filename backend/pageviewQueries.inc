<?php

function wantedViewCountsQuery($pageList,$monthList,$language,$drilldownList,$viewcountarray) {
  $numberOfWantedViewCounts = 0;
  $insertQuery = "insert into wantedviewcountsbymonth(pagename,monthfull,language,drilldown,status) values ";
  foreach ($pageList as $page) {
    foreach ($monthList as $month) {
      foreach ($drilldownList as $drilldown) {
        if ($viewcountarray[$page][$month][$drilldown] == 'unavailable' and ($drilldown == "desktop" or $month >= "201507")) {
	  if ($numberOfWantedViewCounts > 0) {
            $insertQuery .= ", ";
	  }
	  $numberOfWantedViewCounts++;
	  $insertQuery .= '("'.$page.'"'.",'".$month."','".$language."','".$drilldown."','wanted')";
        }
      }
    }
  }
  $insertQuery .= ";";
  if ($numberOfWantedViewCounts > 0) {
    global $mysqli;
    if ($mysqli->connect_errno) {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
    $result = $mysqli->query($insertQuery);
  }
}


function queriedPageLog($page,$language,$archivalStatus) {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select row_id from queriedpages where pagename=\"".$page."\" and language='".$language."' limit 1;";
  $result = $mysqli->query($select_query);
  $page = str_replace('"','\"',$page);
  if ($result->num_rows == 0) {
    $insertQuery = "insert into queriedpages(pagename,language,archivalStatus) values (\"".$page."\",'".$language."','".$archivalStatus."');";
    $result = $mysqli->query($insertQuery);
  }
  return $result;
}

function getPageviewsOnline($page, $month, $language, $drilldown) {
  global $attemptedExternalQueryCount;
  global $successfulExternalQueryCount;
  global $attemptedExternalQueryLimit;
  global $thisMonth;
  global $mostRecentMonth;
  global $exceededQueryLimitMessage;
  global $cannotRetrieveMessage;
  global $fbToken;
  global $curlOutputDirectory;
  global $tokenExpiredMessage;
  global $irretrievableCount;
  if ($month < 201507 and in_array($drilldown, array("mobile-web", "mobile-app", "desktop-spider", "mobile-web-spider"))) {
    $irretrievableCount++;
    return $cannotRetrieveMessage;
  } elseif ($attemptedExternalQueryCount >= $attemptedExternalQueryLimit) {
    return $exceededQueryLimitMessage;
  } else {
    $url = getPageviewsUrl($page,$month,$language,$drilldown);
    if ($drilldown == "cumulative-facebook-shares") {
      if ($month == $thisMonth) {
        $attemptedExternalQueryCount++;
        $tmpString = strval(rand());
        $jsonFileFullPath = $curlOutputDirectory.$tmpString.'.json';
        $curlCmd = 'curl -H "Authorization: Bearer '.$fbToken.'" '.$url.' > '.$jsonFileFullPath;
        exec($curlCmd);
        $contents = file_get_contents($jsonFileFullPath);
        $json = json_decode($contents,true);
        if ($json["error"]["type"] === "OAuthException") {
          return $tokenExpiredMessage;
        }
        $shareJson = $json["share"];
        $shareCount = intval($shareJson["share_count"]);
        $successfulExternalQueryCount++;
        return $shareCount;
      } else {
        $irretrievableCount++;
        return $cannotRetrieveMessage;
      }
    } else if ($month < 201507 and $drilldown == "desktop") {
      $attemptedExternalQueryCount++;
      $html = file_get_contents($url);
      preg_match('/(?<=\bhas been viewed)\s+\K[^\s]+/',$html,$numberofpageviews);
      if (count($numberofpageviews) > 0) {
        if (strlen($numberofpageviews[0]) > 0) {
          $successfulExternalQueryCount++;
          return $numberofpageviews[0];
        } else {
          return $exceededQueryLimitMessage;
        }
      } else {
        return $exceededQueryLimitMessage;
      }
    } else if ($month >= 201507) {
      $attemptedExternalQueryCount++;
      # Calculate string of the first date of next month (used as upper limit of
      # query)
      ini_set('user_agent', 'Wikipedia Views (wikipediaviews.org); contact vipulnaik1@gmail.com in case of issues');
      usleep(20000);
      $html = file_get_contents($url);
      if (!$html) {
        $successfulExternalQueryCount++;
        return 0;
      }
      $json = json_decode($html,true);
      $sum = 0;
      foreach ($json["items"] as $day) {
        $sum += intval($day["views"]);
      }
      $successfulExternalQueryCount++;
      return $sum;
    } else {
      $irretrievableCount++;
      return $cannotRetrieveMessage;
    }
  }
}

function getPageviewsFromDb($page,$month,$language,$drilldown, $online) {
  global $mysqli;
  global $attemptedExternalQueryCount;
  global $attemptedExternalQueryLimit;
  global $successfulExternalQueryCount;
  global $exceededQueryLimitMessage;
  global $cannotRetrieveMessage;
  global $thisMonth;
  global $mostRecentMonth;
  global $purgeperiod;
  global $recentMonthSlowdownFactor;
  global $tokenExpiredMessage;
  global $irretrievableCount;
  # Short circuit computation if we know we cannot retrieve anything
  if (($month < 201507 and in_array($drilldown, array("mobile-web", "mobile-app", "desktop-spider", "mobile-web-spider"))) or ($month < 201610 and $drilldown == 'cumulative-facebook-shares')) {
    $irretrievableCount++;
    return $cannotRetrieveMessage;
  }
  $lookupPage = str_replace('"','\"',$page);
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }

  #First looks for existing entries in the database

  $selectQuery = "select viewcount,querytime from viewcountsbymonth_all where pagename=\"".$lookupPage."\" and monthfull='".$month."' and language='".$language."' and drilldown='".$drilldown."' limit 1;";
  # print $selectQuery;

  $result = $mysqli->query($selectQuery);
  
  #If there is no entry, fetches it online

  if ($result->num_rows == 0) {
    $viewcount = getPageviewsOnline($page,$month,$language,$drilldown);
    if ($viewcount !== $cannotRetrieveMessage and $viewcount !== $tokenExpiredMessage) {
      $insertQuery="insert into viewcountsbymonth_all(pagename,monthfull,language,drilldown,viewcount) values (\"".$lookupPage."\",'".$month."','".$language."','".$drilldown."',".$viewcount.");";
      $success = $mysqli->query($insertQuery);
    }
  } else {
    $row = $result->fetch_assoc();
    $viewcount = $row['viewcount'];
      
    #But wait, now we must check that the value is not too outdated

    if ($month == $thisMonth) {
      $currentdate = new DateTime("now");
      $dateofretrieval = new DateTime($row['querytime']); 
      $dayspassedasdiff = date_diff($dateofretrieval,$currentdate);
      $dayspassed = intval($dayspassedasdiff -> d);
      if ($dayspassed > $purgeperiod) {
	$viewcount = getPageviewsOnline($page,$month,$language,$drilldown);

        if ($viewcount != $exceededQueryLimitMessage and $viewcount != cannotRetrieveMessage) {
          $deleteQuery = "delete from viewcountsbymonth_all where pagename=\"".$lookupPage."\" and monthfull='".$month."' and language='".$language."' and drilldown='".$drilldown."';";
          $insertQuery="insert into viewcountsbymonth_all(pagename,monthfull,language,drilldown,viewcount) values (\"".$lookupPage."\",'".$month."','".$language."','".$drilldown."',".$viewcount.");";
          $success = $mysqli->query($deleteQuery);
          $success = $mysqli->query($insertQuery);
        }
      }
    }
  }
  #If a value has been successfully retrieved, removes it from the wanted query list
  if ($viewcount != $exceededQueryLimitMessage and $drilldown == "desktop") {
    $delete_query = "delete from wantedviewcountsbymonth where pagename=\"".$page."\" and monthfull='".$month."' and language='".$language."';";
    $success = $mysqli->query($delete_query);
  }
  return $viewcount;
}

function getAnnualPageviewsFromDb($page,$year,$language,$drilldown,$online) {
  global $mysqli;
  global $exceededQueryLimitMessage;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $page = str_replace('"','\"',$page);
  $selectQuery = 'select viewcount from viewcountsbyyear_all where pagename="'.$page.'"'." and year='".$year."' and language='".$language."' and drilldown='".$drilldown."'limit 1;";
  $result = $mysqli->query($selectQuery);
  if ($result->num_rows == 1) {
    $row = $result->fetch_assoc();
    return $row['viewcount'];
  }
  $select_query = "select monthfull from months where status!='present' and status!='future' and year='".$year."';";
  $result = $mysqli->query($select_query);
  $totalviews = 0;
  for($i=0;$i < $result->num_rows;$i++) {
    $row = $result->fetch_assoc();
    $monthfull = $row['monthfull'];
    flush();
    $increment = getPageviewsFromDb($page,$monthfull,$language,$drilldown,$online);
    if ($increment == $exceededQueryLimitMessage) {return $exceededQueryLimitMessage;}
    $totalviews += intval($increment);
  }
  $select_query = "select status from years where year='".$year."';";
  $result = $mysqli->query($select_query);
  $row = $result->fetch_assoc();
  if ($row['status'] != 'future') {
    $insertQuery = "insert into viewcountsbyyear_all(pagename,year,language,drilldown,viewcount) values(\"".$page."\",'".$year."','".$language."','".$drilldown."',".$totalviews.");";
    $success = $mysqli->query($insertQuery);
  }
  return $totalviews;
}

function getannualpageviews($page,$year,$language,$drilldown) {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $log_query = "insert into viewquerylogbyyear(pagename,year,language) values (\"".$page."\",'".$year."','".$language."');";
  $result = $mysqli->query($log_query);
  queriedPageLog($page,$language,'partial');
  return getAnnualPageviewsFromDb($page,$year,$language,$drilldown,true);
}

function viewcountarraybymonth_raw($pageList,$monthList,$language,$drilldownList,$online=true,$normalization='') {
  global $mysqli;
  global $attemptedExternalQueryCount;
  global $attemptedExternalQueryLimit;
  global $exceededQueryLimitMessage;
  global $purgeperiod;
  global $thisMonth;
  global $unavailableCount;
  global $bulkRetrievalTimeTaken;
  $bulkRetrievalStartTime = microtime(true);
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  if (sizeof($pageList) == 0 or sizeof($monthList) == 0) return false;
  foreach($pageList as $page) {
    foreach($monthList as $month) {
      foreach($drilldownList as $drilldown) {
        $viewcountarray[$page][$month][$drilldown] = 'unavailable';
      }
    }
  }
  $pageListAsQuotedCsvString = convertListToQuotedCsvString($pageList);
  $monthListAsQuotedCsvString = convertListToQuotedCsvString($monthList);
  $drilldownListAsQuotedCsvString = convertListToQuotedCsvString($drilldownList);
  $selectQuery = "select pagename,monthfull,language,drilldown,viewcount,querytime from viewcountsbymonth_all where pagename in (".$pageListAsQuotedCsvString.") and monthfull in (".$monthListAsQuotedCsvString.") and language='".$language."' and drilldown in (".$drilldownListAsQuotedCsvString.");";
  $result = $mysqli->query($selectQuery);
  for ($i = 0;$i < $result->num_rows;$i++) {
    $row = $result->fetch_assoc();
    if ($row['monthfull'] != $thisMonth) {
      $viewcountarray[$row['pagename']][$row['monthfull']][$row['drilldown']] = $row['viewcount'];
    } else {
      $currentdate = new DateTime("now");
      $dateofretrieval = new DateTime($row['querytime']); 
      $dayspassedasdiff = date_diff($dateofretrieval,$currentdate);
      $dayspassed = intval($dayspassedasdiff->d);
      if ($dayspassed > $purgeperiod) {
	$viewcountarray[$row['pagename']][$row['monthfull']][$row['drilldown']] = 'unavailable';
      } else {
	$viewcountarray[$row['pagename']][$row['monthfull']][$row['drilldown']] = $row['viewcount'];
      }
    }		
  }
  $bulkRetrievalEndTime = microtime(true);
  if ($online == true) {
    $bulkRetrievalTimeTaken = $bulkRetrievalEndTime - $bulkRetrievalStartTime;
  }
  wantedViewCountsQuery($pageList,$monthList,$language,$drilldownList,$viewcountarray);	
  foreach(array_reverse($pageList) as $page) {
    queriedPageLog($page,$language,'partial');
  }
  foreach($pageList as $page) {
    foreach($monthList as $month) {
      foreach($drilldownList as $drilldown) {
        if ($viewcountarray[$page][$month][$drilldown] == 'unavailable' and $online == true) {
          $viewcountarray[$page][$month][$drilldown] = getPageviewsFromDb($page,$month,$language,$drilldown,true);
        }
      }
    }
  }
  if ($attemptedExternalQueryCount < $attemptedExternalQueryLimit) {
    # print "Successfully completed without timing out :)<br>";
    return $viewcountarray;
  }

  foreach($pageList as $page) {
    foreach($monthList as $month) {
      foreach($drilldownList as $drilldown) {
        if ($viewcountarray[$page][$month][$drilldown] == $exceededQueryLimitMessage) {
          $unavailableCount++;
        }
      }
    }
  }
  
  return $viewcountarray;
}

function viewcountarraybymonth($pageList,$monthList,$language,$drilldownList,$online,$normalization='') {
  global $exceededQueryLimitMessage;
  global $numberofdays_allmonths;
  $viewcountarray = viewcountarraybymonth_raw($pageList,$monthList,$language,$drilldownList,$online,$normalization);
  if ($normalization == '')
    return $viewcountarray;
  elseif ($normalization == 'dailyaverage') {
    foreach ($pageList as $page) {
      foreach ($monthList as $month) {
        foreach ($drilldownList as $drilldown) {
          if ($viewcountarray[$page][$month][$drilldown] != $exceededQueryLimitMessage) {
	    $viewcountarray[$page][$month][$drilldown] = round($viewcountarray[$page][$month][$drilldown]/intval($numberofdays_allmonths[$month]),1);
          }
        }
      }
    }
  }
  return $viewcountarray;
}

function viewcountarraybyyear($pageList,$yearList,$language,$drilldownList,$online,$normalization='') {
  global $mysqli;
  global $attemptedExternalQueryCount;
  global $attemptedExternalQueryLimit;
  global $bulkRetrievalTimeTaken;
  $bulkRetrievalStartTime = microtime(true);
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  if (sizeof($pageList) == 0 or sizeof($yearList) == 0) return false;
  foreach($pageList as $page) {
    foreach($yearList as $year) {
      foreach($drilldownList as $drilldown) { 
        $viewcountarray[$page][$year][$drilldown] = 'unavailable';
      }
    }
  }
  $pageListAsQuotedCsvString = convertListToQuotedCsvString($pageList);
  $yearListAsQuotedCsvString = convertListToQuotedCsvString($yearList);
  $drilldownListAsQuotedCsvString = convertListToQuotedCsvString($drilldownList);
  $selectQuery = "select pagename,year,language,drilldown,viewcount from viewcountsbyyear_all where pagename in (".$pageListAsQuotedCsvString.") and year in (".$yearListAsQuotedCsvString.") and language='".$language."' and drilldown in (".$drilldownListAsQuotedCsvString.");";
  $result = $mysqli->query($selectQuery);
  for ($i = 0;$i < $result->num_rows;$i++) {
    $row = $result->fetch_assoc();
    $viewcountarray[$row['pagename']][$row['year']][$row['drilldown']] = $row['viewcount'];
  }
  $bulkRetrievalEndTime = microtime(true);
  if ($online == true) {
    $bulkRetrievalTimeTaken = $bulkRetrievalEndTime - $bulkRetrievalStartTime;
  }
  foreach(array_reverse($pageList) as $page) {
      queriedPageLog($page,$language,'partial');
  }
  foreach($pageList as $page) {
    foreach($yearList as $year) {
      foreach($drilldownList as $drilldown) {
        if ($viewcountarray[$page][$year][$drilldown] == 'unavailable' and $online = true) {
	  $viewcountarray[$page][$year][$drilldown] = getAnnualPageviewsFromDb($page,$year,$language,$drilldown,true);
        }
      }
    }
  }
  if ($attemptedExternalQueryCount < $attemptedExternalQueryLimit) {
    #print "Successfully completed without timing out :)<br>";
    return $viewcountarray;
  }
  foreach($pageList as $page) {
    foreach($yearList as $year) {
      foreach($drilldownList as $drilldown) {
        if ($viewcountarray[$page][$year][$drilldown] == $exceededQueryLimitMessage) {
	  $viewcountarray[$page][$year][$drilldown] = getAnnualPageviewsFromDb($page,$year,$language,$drilldown,true);
        }
      }
    }
  }
  return $viewcountarray;	
}

function fillinWantedViewCounts($queryLimit, $online) {
  global $mysqli;
  global $attemptedExternalQueryCount;
  global $attemptedExternalQueryLimit;
  global $exceededQueryLimitMessage;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $selectQuery = "select * from wantedviewcountsbymonth where status='wanted' limit ".$queryLimit.";";
  # print $selectQuery;
  $result = $mysqli->query($selectQuery);
  if ($result ->num_rows == 0) {
    return true;
  }
  $workingQuery = "update wantedviewcountsbymonth set status='working' where row_id in (";
  $deletionQuery = "delete from wantedviewcountsbymonth where row_id in (0";
  for($i=0;$i < $result->num_rows;$i++) {
    if ($i > 0) $workingQuery .= ",";
    $row = $result->fetch_assoc();
    $workingQuery .= $row['row_id'];
    $page[$i] = $row['pagename'];
    $month[$i] = $row['monthfull'];
    $language[$i] = $row['language'];
    $drilldown[$i] = $row['drilldown']; 
    $row_id[$i] = $row['row_id'];
  }
  $workingQuery .= ");";
  print "Going to execute query to reserve a few pages for lookup: ".$workingQuery."\n";
  $updateResult = $mysqli->query($workingQuery);
  for($i=0;$i < $result->num_rows;$i++) {
    $currentLoad = sys_getloadavg();
    if ($currentLoad[0] < 1.0) {
      $count = getPageviewsFromDb($page[$i],$month[$i],$language[$i],"desktop",$online);
      print "Weighted external query count is ".$attemptedExternalQueryCount." and ";
      print "weighted external query limit is ".$attemptedExternalQueryLimit."\n";
      print "For page ".$page[$i].", month ".$month[$i].", and language ".$language[$i].", page view count is ".$count."\n";
      if ($count != $exceededQueryLimitMessage) {
	 $deletionQuery .= ",".$row_id[$i];
      }
    } else {
      print "Exiting because system appears overloaded!";
      exit;
    }
  }
  $deletionQuery .= ");";
  print "Running deletion query: ".$deletionQuery."\n";
  $deletionResult = $mysqli->query($deletionQuery);
  print "Succeeded in running deletion query: ".$deletionQuery."\n";
  return false;
}	


?>
