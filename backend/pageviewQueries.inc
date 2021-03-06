<?php

function wantedViewCountsQuery($pageList,$languageList,$drilldownList,$monthList,$viewCountArray) {
  $numberOfWantedViewCounts = 0;
  $insertQuery = "insert into wantedviewcountsbymonth(pagename,monthfull,language,drilldown,status) values ";
  foreach ($pageList as $page) {
    foreach ($languageList as $language) {
      foreach ($drilldownList as $drilldown) {
        foreach ($monthList as $month) {
          if ($viewCountArray[$page][$language][$drilldown][$month] == 'unavailable' and $month >= "201507") {
	    if ($numberOfWantedViewCounts > 0) {
              $insertQuery .= ", ";
	    }
	    $numberOfWantedViewCounts++;
	    $insertQuery .= '("'.$page.'"'.",'".$month."','".$language."','".$drilldown."','wanted')";
          }
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
  $select_query = "select row_id from queriedpages where pagename=\"".str_replace('"','\"',$page)."\" and language='".$language."' limit 1;";
  $result = $mysqli->query($select_query);
  $page = str_replace('"','\"',$page);
  if ($result->num_rows == 0) {
    $insertQuery = "insert into queriedpages(pagename,language,archivalstatus) values (\"".str_replace('"','\"',$page)."\",'".$language."','".$archivalStatus."');";
    $result = $mysqli->query($insertQuery);
  }
  return $result;
}

function getClickstreamData($page, $month, $language, $drilldown) {
  global $successfulExternalQueryCount;
  global $attemptedExternalQueryCount;
  global $attemptedExternalQueryLimit;
  global $clickstreamFolder;
  global $cannotRetrieveMessage;
  global $irretrievableCount;
  global $exceededQueryLimitMessage;
  $actualReferrer = substr($drilldown, 9, strlen($drilldown));
  # if (in_array($month, array("201501", "201502", "201602", "201603", "201604", "201608", "201609"))) {
  if (
    ((in_array($month, array("201604", "201608", "201609")) and $language == "en") or ($month >= "201711" and in_array($language, array("en","ja","de","es","ru"))) and in_array($actualReferrer, array("other-search", "other-external", "other-other","other-empty","other-internal","Wikipedia"))) or
    (in_array($language, array("pl","pt","fr","it","zh")) and
    $month >= "201801" and in_array($actualReferrer, array("other-search", "other-external", "other-other","other-empty","other-internal","Wikipedia"))) or
    (in_array($month, array("201501", "201502", "201602", "201603")) and $language == "en" and in_array($actualReferrer, array("other-empty","other-internal","Wikipedia","other-bing","other-facebook","other-google","other-twitter","other-wikipedia","other-yahoo"))) or
    (in_array($month, array("201502", "201602", "201603")) and $language == "en" and $actualReferrer == "other-other")
  ) {
    if ($attemptedExternalQueryCount < $attemptedExternalQueryLimit) {
      $page = str_replace(" ", "_", $page);
      $page = str_replace("(", "\(", $page);
      $page = str_replace(")","\)",$page);
      $grepString = "^$page\t$actualReferrer\t\K.+";
      $sourceFile = $clickstreamFolder.$language.'/'.$month.'.tsv';
      $startingLetter = substr($page, 0, 1);
      if (ctype_alpha($startingLetter) and ctype_upper($startingLetter)) {
        $sourceFile = $clickstreamFolder.$language."/".$month.$startingLetter.'.tsv';
      }
      $grepExpression = 'grep -oP "'.$grepString.'" '.$sourceFile;
      # print "grep expression used = ".$grepExpression;
      $attemptedExternalQueryCount++;
      $successfulExternalQueryCount++;
      $response = shell_exec($grepExpression);
      if ($response == '') {
        return 0;
      } else {
        return trim($response," \t\n\r\0\x0B");
      }
    } else {
      return $exceededQueryLimitMessage;
    }
  } else {
    $irretrievableCount++; 
    return $cannotRetrieveMessage;
  }
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
  global $fbTokenActive;
  global $curlOutputDirectory;
  global $tokenExpiredMessage;
  global $irretrievableCount;
  global $dataStartMap;
  global $statsGrokSeActive;
  global $statsGrokSeRequested;
  global $backfillIfPossible;
  global $mysqli;
  global $currentlyBackfillingFb;
  # print "<br/>fbToken = $fbToken, fbTokenActive = $fbTokenActive<br/><br/>";
  if (count($dataStartMap) == 0) {
    $dataStartMap = dataStartMap();
  }
  $localBackfillIfPossible = $backfillIfPossible;
  if ($month < $mostRecentMonth) {
    $localBackfillIfPossible = true;
  }
  if ($drilldown == "country-total") {
    $irretrievableCount++;
    return $cannotRetrieveMessage;
  }
  if (substr($drilldown, 0, 9) == "referrer:") {
    return getClickstreamData($page, $month, $language, $drilldown);
  } elseif ($month < '201507' and in_array($drilldown, array("mobile-app", "desktop-spider", "mobile-web-spider"))) {
    $irretrievableCount++;
    return $cannotRetrieveMessage;
  } elseif($month < '201507' and $page != "[aggregate]" and $drilldown == "mobile-web") {
    $irretrievableCount++;
    return $cannotRetrieveMessage;
  } elseif ($page != "[aggregate]" and $month.'31' < $dataStartMap[$language]) {
    $irretrievableCount++;
    return $cannotRetrieveMessage;
  } elseif ($attemptedExternalQueryCount >= $attemptedExternalQueryLimit) {
    return $exceededQueryLimitMessage;
  } else {
    $url = getPageviewsUrl($page,$month,$language,$drilldown);
    if ($drilldown == "cumulative-facebook-shares") {
      if (($month == $thisMonth or ($month == $mostRecentMonth and $currentlyBackfillingFb == true)) and $fbTokenActive == true) {
        $attemptedExternalQueryCount++;
        $tmpString = strval(rand());
        $jsonFileFullPath = $curlOutputDirectory.$tmpString.'.json';
        $curlCmd = 'curl -H "Authorization: Bearer '.$fbToken.'" '.$url.' > '.$jsonFileFullPath;
        # print "<br/>Executing curl command $curlCmd<br/><br/>";
        exec($curlCmd);
        $contents = file_get_contents($jsonFileFullPath);
        $json = json_decode($contents,true);
        if ($json["error"]["type"] === "OAuthException") {
          # print "Encountered error:";
          # print_r($json);
          $fbTokenActive = false;
          return $tokenExpiredMessage;
        }
        $shareJson = $json["share"];
        $shareCount = intval($shareJson["share_count"]);
        $successfulExternalQueryCount++;
        return $shareCount;
      } else if ($month == $thisMonth or ($month == $mostRecentMonth and $currentlyBackfillingFb == true)) {
        return $tokenExpiredMessage;
      } else {
        $irretrievableCount++;
        return $cannotRetrieveMessage;
      }
    } else if ($month < '201507' and $drilldown == "desktop" and $page != "[aggregate]") {
      $statsGrokSeRequested = "true";
      if ($statsGrokSeActive == "unknown") {
        $curlCmd = "curl http://stats.grok.se --connect-timeout 5 --max-time 6";
        exec($curlCmd, $output, $curlSuccess);
        if ($curlSuccess == 0) {
          $statsGrokSeActive = "true"; 
        } else {
          $statsGrokSeActive = "false";
        }
      }
      if ($statsGrokSeActive == "true") {
        $attemptedExternalQueryCount++;
        $html = file_get_contents($url);
        preg_match('/(?<=\bhas been viewed)\s+\K[^\s]+/',$html,$numberofpageviews);
        if (count($numberofpageviews) > 0) {
          if (strlen($numberofpageviews[0]) > 0) {
            $successfulExternalQueryCount++;
            return $numberofpageviews[0];
          } else {
            $irretrievalbleCount++;
            return $cannotRetrieveMessage;
          }
        } else {
          $irretrievableCount++;
          return $cannotRetrieveMessage;
        }
      } else {
        $irretrievableCount++;
        return $cannotRetrieveMessage;
      }
    } else if ($month >= '201507' or ($page == "[aggregate]" and in_array($drilldown, array("desktop", "mobile-web")) and ($drilldown == "desktop" or $month >= "201410"))) {
      $longUrl = getLongUrl($page,$month,$language,$drilldown);
      $attemptedExternalQueryCount++;
      # Calculate string of the first date of next month (used as upper limit of
      # query)
      ini_set('user_agent', 'Wikipedia Views (wikipediaviews.org); contact vipulnaik1@gmail.com in case of issues');
      # usleep(20000); ## No need to sleep, the API takes 100 ms to respond so we are anyway safe at 10 req/s
      $lookupString = "views";
      if ($month < "201507") {
        $lookupString = "count";
      }
      if (($page != '[aggregate]') and $localBackfillIfPossible) {
        $lookupPage = str_replace('"','\"',$page);
        $html = file_get_contents($longUrl);
        if (!$html) {
          $successfulExternalQueryCount++;
          return 0; 	  
        }
        $json = json_decode($html, true); 
        $sum = 0;
        foreach($json["items"] as $item) {
          if ($item["timestamp"] == $month . "0100") {
            $sum = intval($item[$lookupString]);
          } else {
            $viewcount = intval($item[$lookupString]);
            $lookupMonth = substr($item["timestamp"],0,6);    
            $insertionQuery = "insert ignore into viewcountsbymonth(pagename,monthfull,language,drilldown,viewcount) values (\"".$lookupPage."\",'".$lookupMonth."','".$language."','".$drilldown."',".$viewcount.");";
	    $mysqli -> query($insertionQuery); 
          }
        }
        $successfulExternalQueryCount++;
        return $sum;	
      } else {
        # print "Fetching contents for url $url";
        $html = file_get_contents($url);
        if (!$html) {
          $successfulExternalQueryCount++;
          return 0;
        }
        $json = json_decode($html,true);
        $sum = 0;
        foreach ($json["items"] as $item) {
          $sum += intval($item[$lookupString]);
        }
        $successfulExternalQueryCount++;
        return $sum;
      }
    } else {
      $irretrievableCount++;
      return $cannotRetrieveMessage;
    }
  }
}

function getPageviewsFromDb($page,$month,$language,$drilldown, $online, $verbose='false') {
  global $mysqli;
  global $attemptedExternalQueryCount;
  global $attemptedExternalQueryLimit;
  global $successfulExternalQueryCount;
  global $exceededQueryLimitMessage;
  global $cannotRetrieveMessage;
  global $thisMonth;
  global $mostRecentMonth;
  global $purgePeriod;
  global $recentMonthSlowdownFactor;
  global $tokenExpiredMessage;
  global $irretrievableCount;
  global $dataStartMap;
  if (count($dataStartMap) == 0) {
    $dataStartMap = dataStartMap();
  }
  # Short circuit computation if we know we cannot retrieve anything
  if (($month < '201507' and in_array($drilldown, array("mobile-web", "mobile-app", "desktop-spider", "mobile-web-spider")) and ($drilldown != "mobile-web" or $page != "[aggregate]" or $month < "201410")) or ($month < '201610' and $drilldown == 'cumulative-facebook-shares')) {
    $irretrievableCount++;
    return $cannotRetrieveMessage;
  } elseif ($page != "[aggregate]" and $month.'31' < $dataStartMap[$language]) {
    $irretrievableCount++;
    return $cannotRetrieveMessage;
  } 
  $lookupPage = str_replace('"','\"',$page);
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }

  #First looks for existing entries in the database

  $selectionStartTime = microtime(true);
  $selectQuery = "select viewcount,querytime from viewcountsbymonth where pagename=\"".$lookupPage."\" and monthfull='".$month."' and language='".$language."' and drilldown='".$drilldown."' limit 1;";
  # print $selectQuery;

  $result = $mysqli->query($selectQuery);
  $selectionEndTime = microtime(true);

  if ($verbose == 'true') {
    $selectionTimeTaken = $selectionEndTime - $selectionStartTime;
    print date("Y-m-d h:i:sa").": Time taken for selection for page $page, month $month, language $language, drilldown $drilldown: ".$selectionTimeTaken."\n";
  }
  #If there is no entry, fetches it online

  if ($result->num_rows == 0) {
    $onlineQueryStartTime = microtime(true);
    $viewcount = getPageviewsOnline($page,$month,$language,$drilldown);
    $onlineQueryEndTime = microtime(true);
    if ($verbose == 'true') {
      $onlineQueryTimeTaken = $onlineQueryEndTime - $onlineQueryStartTime;
      print date("Y-m-d h:i:sa").": Time taken for online query for page $page, month $month, language $language, drilldown $drilldown: ".$onlineQueryTimeTaken."\n";
    }
    if ($viewcount !== $cannotRetrieveMessage and $viewcount !== $tokenExpiredMessage) {
      $insertQueryStartTime = microtime(true);
      $insertQuery="insert into viewcountsbymonth(pagename,monthfull,language,drilldown,viewcount) values (\"".$lookupPage."\",'".$month."','".$language."','".$drilldown."',".$viewcount.");";
      $insertQueryEndTime = microtime(true);
      if ($verbose == 'true') {
        $insertQueryTimeTaken = $insertQueryEndTime - $insertQueryStartTime;
        print date("Y-m-d h:i:sa").": Time taken for insert query for page $page, month $month, language $language, drilldown $drilldown: ".$insertQueryTimeTaken."\n";
      }
      $success = $mysqli->query($insertQuery);
    }
  } else {
    $row = $result->fetch_assoc();
    $viewcount = $row['viewcount'];
      
    #But wait, now we must check that the value is not too outdated

    if ($month == $thisMonth) {
      $currentDate = new DateTime("now");
      $dateOfRetrieval = new DateTime($row['querytime']); 
      $daysPassedAsDiff = date_diff($dateOfRetrieval,$currentDate);
      $daysPassed = intval($daysPassedAsDiff -> d);
      if ($daysPassed > $purgePeriod and ($purgePeriod >=0 or $online == 'true')) {
	$viewcount = getPageviewsOnline($page,$month,$language,$drilldown);
        if ($viewcount != $exceededQueryLimitMessage and $viewcount != cannotRetrieveMessage) {
          $deleteQuery = "delete from viewcountsbymonth where pagename=\"".$lookupPage."\" and monthfull='".$month."' and language='".$language."' and drilldown='".$drilldown."';";
          $insertQuery="insert into viewcountsbymonth(pagename,monthfull,language,drilldown,viewcount) values (\"".$lookupPage."\",'".$month."','".$language."','".$drilldown."',".$viewcount.");";
          $success = $mysqli->query($deleteQuery);
          $success = $mysqli->query($insertQuery);
        }
      }
    }
  }
  #If a value has been successfully retrieved, removes it from the wanted query list
  if ($viewcount != $exceededQueryLimitMessage) {
    $deletionStartTime = microtime(true);
    $delete_query = "delete from wantedviewcountsbymonth where pagename=\"".$page."\" and monthfull='".$month."' and language='".$language."' and drilldown='$drilldown';";
    $success = $mysqli->query($delete_query);
    $deletionEndTime = microtime(true);
    if ($verbose == 'true') {
      $deletionTimeTaken = $deletionEndTime - $deletionStartTime;
      print date("Y-m-d h:i:sa").": Time taken for deletion query $delete_query for page $page, month $month, language $language, drilldown $drilldown: ".$deletionTimeTaken."\n";
    }
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
  $selectQuery = 'select viewcount from viewcountsbyyear where pagename="'.$page.'"'." and year='".$year."' and language='".$language."' and drilldown='".$drilldown."'limit 1;";
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
    $insertQuery = "insert into viewcountsbyyear(pagename,year,language,drilldown,viewcount) values(\"".$page."\",'".$year."','".$language."','".$drilldown."',".$totalviews.");";
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

function viewCountArrayByMonth_raw($pageList,$languageList,$drilldownList,$monthList,$online=true,$normalization='',$shortcutTag='') {
  global $mysqli;
  global $attemptedExternalQueryCount;
  global $attemptedExternalQueryLimit;
  global $exceededQueryLimitMessage;
  global $purgePeriod;
  global $thisMonth;
  global $unavailableCount;
  global $bulkRetrievalTimeTaken;
  global $dataStartMap;
  global $backfillIfPossible;
  $backfillIfPossible = true;
  $dataStartMap = dataStartMap();
  $bulkRetrievalStartTime = microtime(true);
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  if (sizeof($pageList) == 0 or sizeof($monthList) == 0) return false;
  foreach($pageList as $page) {
    foreach($languageList as $language) {
      foreach($drilldownList as $drilldown) {
        foreach($monthList as $month) {
          $viewCountArray[$page][$language][$drilldown][$month] = 'unavailable';
        }
      }
    }
  }
  $pageListAsQuotedCsvString = convertListToQuotedCsvString($pageList);
  $monthListAsQuotedCsvString = convertListToQuotedCsvString($monthList);
  $languageListAsQuotedCsvString = convertListToQuotedCsvString($languageList);
  $drilldownListAsQuotedCsvString = convertListToQuotedCsvString($drilldownList);
  if ($shortcutTag != '') {
    $pageListReferenceQuery = "select distinct pagename from pagetags where tag=\"".$shortcutTag."\" and language='$language'";
  } else {
    $pageListReferenceQuery = $pageListAsQuotedCsvString;
  }
  $selectQuery = "select pagename,monthfull,language,drilldown,viewcount,querytime from viewcountsbymonth where pagename in (".$pageListReferenceQuery.") and monthfull in (".$monthListAsQuotedCsvString.") and language in (".$languageListAsQuotedCsvString.") and drilldown in (".$drilldownListAsQuotedCsvString.");";
  $result = $mysqli->query($selectQuery);
  for ($i = 0;$i < $result->num_rows;$i++) {
    $row = $result->fetch_assoc();
    if ($row['monthfull'] != $thisMonth) {
      $viewCountArray[$row['pagename']][$row['language']][$row['drilldown']][$row['monthfull']] = $row['viewcount'];
    } else {
      $currentdate = new DateTime("now");
      $dateofretrieval = new DateTime($row['querytime']); 
      $dayspassedasdiff = date_diff($dateofretrieval,$currentdate);
      $dayspassed = intval($dayspassedasdiff->d);
      if ($dayspassed > $purgePeriod) {
	$viewCountArray[$row['pagename']][$row['language']][$row['drilldown']][$row['monthfull']] = 'unavailable';
      } else {
	$viewCountArray[$row['pagename']][$row['language']][$row['drilldown']][$row['monthfull']] = $row['viewcount'];
      }
    }		
  }
  $bulkRetrievalEndTime = microtime(true);
  if ($online == true) {
    $bulkRetrievalTimeTaken = $bulkRetrievalEndTime - $bulkRetrievalStartTime;
  }
  wantedViewCountsQuery($pageList,$languageList,$drilldownList,$monthList,$viewCountArray);	
  foreach(array_reverse($pageList) as $page) {
    queriedPageLog($page,$language,'partial');
  }
  foreach($pageList as $page) {
    foreach($languageList as $language) {
      foreach($monthList as $month) {
        foreach($drilldownList as $drilldown) {
          if ($viewCountArray[$page][$language][$drilldown][$month] == 'unavailable' and $online == true) {
            $viewCountArray[$page][$language][$drilldown][$month] = getPageviewsFromDb($page,$month,$language,$drilldown,true);
          }
        }
      }
    }
  }
  if ($attemptedExternalQueryCount < $attemptedExternalQueryLimit) {
    # print "Successfully completed without timing out :)<br>";
    return $viewCountArray;
  }

  foreach($pageList as $page) {
    foreach($languageList as $language) {
      foreach($drilldownList as $drilldown) {
        foreach($monthList as $month) {
          if ($viewCountArray[$page][$language][$drilldown][$month] == $exceededQueryLimitMessage) {
            $unavailableCount++;
          }
        }
      }
    }
  }
  
  return $viewCountArray;
}

function viewCountArrayByMonth($pageList,$languageList,$drilldownList,$monthList,$online,$normalization='',$shortcutTag='') {
  global $exceededQueryLimitMessage;
  global $cannotRetrieveMessage;
  global $numberofdays_allmonths;
  global $mostRecentMonth;
  # print "<br/><br/>Entered viewCountArrayByMonth request with starting page ".$pageList[0].", starting month ".$monthList[0].", and shortcutTag = ".$shortcutTag."<br/><br/>";
  $viewCountArray = viewCountArrayByMonth_raw($pageList,$languageList,$drilldownList,$monthList,$online,$normalization,$shortcutTag);
  if ($normalization == '') {
    return $viewCountArray;
  } elseif ($normalization == 'dailyaverage') {
    foreach ($pageList as $page) {
      foreach ($languageList as $language) {
        foreach ($drilldownList as $drilldown) {
          foreach ($monthList as $month) {
            if ($viewCountArray[$page][$language][$drilldown][$month] !== $exceededQueryLimitMessage and $viewCountArray[$page][$language][$drilldown][$month] !== $cannotRetrieveMessage) {
	      $viewCountArray[$page][$language][$drilldown][$month] = round($viewCountArray[$page][$language][$drilldown][$month]/intval($numberofdays_allmonths[$month]),1);
            }
          }
        }
      }
    }
  } elseif ($normalization == 'aggregate') {
    $aggregateViewCountArray = viewCountArrayByMonth(array("[aggregate]"),$languageList,$drilldownList,$monthList, true, '', $shortcutTag);
    $mostRecentAggregateViewCountArray = viewCountArrayByMonth(array("[aggregate]"),$languageList, $drilldownList, array($mostRecentMonth), true, '', $shortcutTag);
    foreach($pageList as $page) {
      foreach ($languageList as $language) {
        foreach ($drilldownList as $drilldown) {
          foreach ($monthList as $month) {
            if (($month >= '201507' or ($month >= '200802' and $drilldown == 'desktop')) and $viewCountArray[$page][$language][$drilldown][$month] !== $exceededQueryLimitMessage and $viewCountArray[$page][$language][$drilldown][$month] !== $cannotRetrieveMessage) {
              # print ("Scaling value ".$viewCountArray[$page][$language][$drilldown][$month] .", multiplying by ". $mostRecentAggregateViewCountArray["[aggregate]"][$language][$drilldown][$mostRecentMonth] . ", then dividing by ". $aggregateViewCountArray["[aggregate]"][$language][$drilldown][$month]);
              $viewCountArray[$page][$language][$drilldown][$month] = intval(($viewCountArray[$page][$language][$drilldown][$month] * $mostRecentAggregateViewCountArray["[aggregate]"][$language][$drilldown][$mostRecentMonth]) / $aggregateViewCountArray["[aggregate]"][$language][$drilldown][$month]);
            }
          }
        }
      }
    }
  }
  return $viewCountArray;
}

function viewCountArrayByYear($pageList,$languageList,$drilldownList,$yearList,$online,$normalization='') {
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
    foreach($languageList as $language) {
      foreach($drilldownList as $drilldown) { 
        foreach($yearList as $year) { 
          $viewCountArray[$page][$language][$drilldown][$year] = 'unavailable';
        }
      }
    }
  }
  $pageListAsQuotedCsvString = convertListToQuotedCsvString($pageList);
  $languageListAsQuotedCsvString = convertListToQuotedCsvString($languageList);
  $drilldownListAsQuotedCsvString = convertListToQuotedCsvString($drilldownList);
  $yearListAsQuotedCsvString = convertListToQuotedCsvString($yearList);
  $selectQuery = "select pagename,year,language,drilldown,viewcount from viewcountsbyyear where pagename in (".$pageListAsQuotedCsvString.") and year in (".$yearListAsQuotedCsvString.") and language in ('".$languageListAsQuotedCsvString."') and drilldown in (".$drilldownListAsQuotedCsvString.");";
  $result = $mysqli->query($selectQuery);
  for ($i = 0;$i < $result->num_rows;$i++) {
    $row = $result->fetch_assoc();
    $viewCountArray[$row['pagename']][$row['language']][$row['drilldown']][$row['year']] = $row['viewcount'];
  }
  $bulkRetrievalEndTime = microtime(true);
  if ($online == true) {
    $bulkRetrievalTimeTaken = $bulkRetrievalEndTime - $bulkRetrievalStartTime;
  }
  foreach(array_reverse($pageList) as $page) {
      queriedPageLog($page,$language,'partial');
  }
  foreach($pageList as $page) {
    foreach($languageList as $language) {
      foreach($drilldownList as $drilldown) {
        foreach($yearList as $year) { 
          if ($viewCountArray[$page][$language][$drilldown][$year] == 'unavailable' and $online = true) {
	    $viewCountArray[$page][$language][$drilldown][$year] = getAnnualPageviewsFromDb($page,$year,$language,$drilldown,true);
          }
        }
      }
    }
  }
  if ($attemptedExternalQueryCount < $attemptedExternalQueryLimit) {
    #print "Successfully completed without timing out :)<br>";
    return $viewCountArray;
  }
  foreach($pageList as $page) {
    foreach($languageList as $language) {
      foreach($drilldownList as $drilldown) {
        foreach($yearList as $year){
          if ($viewCountArray[$page][$language][$drilldown][$year] == $exceededQueryLimitMessage) {
	    $viewCountArray[$page][$language][$drilldown][$year] = getAnnualPageviewsFromDb($page,$year,$language,$drilldown,true);
          }
        }
      }
    }
  }
  return $viewCountArray;	
}

function fillinWantedViewCounts($queryLimit, $online) {
  global $mysqli;
  global $attemptedExternalQueryCount;
  global $attemptedExternalQueryLimit;
  global $exceededQueryLimitMessage;
  global $tokenExpiredMessage;
  global $cannotRetrieveMessage;
  global $fbTokenActive;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  if ($fbTokenActive == true) {
    $selectQuery = "select * from wantedviewcountsbymonth where status='wanted' and drilldown = 'cumulative-facebook-shares' limit ".$queryLimit.";";
    $result = $mysqli->query($selectQuery);
    print date("Y-m-d h:i:sa").": ".$selectQuery."\n";
  } else {
    print date("Y-m-d h:i:sa").": Skipping Facebook shares checking since it is not active\n";
  }
  if ($fbTokenActive == false or $result -> num_rows == 0) {
    $selectQuery = "select * from wantedviewcountsbymonth where drilldown != 'cumulative-facebook-shares' and status='wanted' limit ".$queryLimit.";";
    $result = $mysqli->query($selectQuery);
    print date("Y-m-d h:i:sa").": ".$selectQuery."\n";
  }
  if ($result ->num_rows == 0) {
    print date("Y-m-d h:i:sa").": Select query response had no rows\n";
    $fixWorkingStatusQuery = "update wantedviewcountsbymonth set status='wanted' where status='working'";
    $mysqli->query($fixWorkingStatusQuery);
    $result = $mysqli->query($selectQuery);
  }
  if ($result -> num_rows == 0) {
    print date("Y-m-d h:i:sa").": Even after changing all working rows to wanted, select query response had no row\n";
    return false;
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
    if ($currentLoad[0] < 0.9) {
      $queryStartTime = microtime(true);
      $count = getPageviewsFromDb($page[$i],$month[$i],$language[$i],$drilldown[$i],$online);
      print "Weighted external query count is ".$attemptedExternalQueryCount." and ";
      print "weighted external query limit is ".$attemptedExternalQueryLimit."\n";
      $queryEndTime = microtime(true);
      $queryTimeTaken = $queryEndTime - $queryStartTime;
      print date("Y-m-d h:i:sa").": For language ".$language[$i].", drilldown ".$drilldown[$i].", month ".$month[$i].", and page ".$page[$i].", page view count is ".$count.", time taken is ".$queryTimeTaken." seconds\n";
      if ($count !== $exceededQueryLimitMessage and $count !== $tokenExpiredMessage) {
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
  return true;
}	


?>
