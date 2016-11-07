<?php

function wantedviewcountsquery($pageList,$monthList,$language,$drilldown,$viewcountarray) {
  $numberofwantedviewcounts = 0;
  $insert_query = "insert into wantedviewcountsbymonth(pagename,monthfull,language,status) values ";
  foreach ($pageList as $page) {
    foreach ($monthList as $month) {
      if ($viewcountarray[$page][$month] == 'unavailable') {
	if ($numberofwantedviewcounts > 0) {
          $insert_query .= ", ";
	}
	$numberofwantedviewcounts++;
	$insert_query .= "(\"".$page."\",'".$month."','".$language."','wanted')";
      }
    }
  }
  $insert_query .= ";";
  if ($numberofwantedviewcounts > 0)
    {
      global $mysqli;
      if ($mysqli->connect_errno) 
	{
	  echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
	}
      $result = $mysqli->query($insert_query);
    }
}


function queriedpagelog($page,$language,$archivalStatus) {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select row_id from queriedpages where pagename=\"".$page."\" and language='".$language."' limit 1;";
  $result = $mysqli->query($select_query);
  $page = str_replace('"','\"',$page);
  if ($result->num_rows == 0) {
    $insert_query = "insert into queriedpages(pagename,language,archivalStatus) values (\"".$page."\",'".$language."','".$archivalStatus."');";
    $result = $mysqli->query($insert_query);
  }
  return $result;
}

function getPageviewsOnline($page, $month, $language, $drilldown) {
  global $weightedExternalQueryCount;
  global $externalQueryCount;
  global $weightedExternalQueryLimit;
  global $thisMonth;
  global $mostRecentMonth;
  global $recentMonthSlowdownFactor;
  global $exceededQueryLimitMessage;
  global $cannotRetrieveMessage;
  global $fbToken;
  global $curlOutputDirectory;
  global $tokenExpiredMessage;
  if ($weightedExternalQueryCount >= $weightedExternalQueryLimit)
      return $exceededQueryLimitMessage;
  if ($month == $thisMonth or $month == $mostRecentMonth)
      $weightedExternalQueryCount = $weightedExternalQueryCount + $recentMonthSlowdownFactor;
  else
      $weightedExternalQueryCount++;
  $url = getPageviewsUrl($page,$month,$language,$drilldown);
  if ($drilldown == "cumulative-facebook-shares") {
    if ($month == $thisMonth) {
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
      return $shareCount;
    } else {
      return $cannotRetrieveMessage;
    }
  } else if ($month < 201507 and $drilldown == "desktop") {
    $html = file_get_contents($url);
    preg_match('/(?<=\bhas been viewed)\s+\K[^\s]+/',$html,$numberofpageviews);
    if (count($numberofpageviews) > 0) {
      if (strlen($numberofpageviews[0]) > 0) {
        $externalQueryCount++;
        return $numberofpageviews[0];
      } else {
        return $cannotRetrieveMessage;
      }
    } else {
      return $cannotRetrieveMessage;
    }
  } else if ($month >= 201507) {
    # Calculate string of the first date of next month (used as upper limit of
    # query)
    ini_set('user_agent', 'Wikipedia Views (wikipediaviews.org); contact vipulnaik1@gmail.com in case of issues');
    usleep(20000);
    $html = file_get_contents($url);
    if (!$html) {
      return 0;
    }
    $json = json_decode($html,true);
    $sum = 0;
    foreach ($json["items"] as $day)
    {
      $sum += intval($day["views"]);
    }
    $externalQueryCount++;
    return $sum;
  } else {
    $weightedExternalQueryCount = $weightedExternalQueryCount - $recentMonthSlowdownFactor;
    return $cannotRetrieveMessage;
  }
}

function getPageviewsFromDb($page,$month,$language,$drilldown, $online) {
  global $mysqli;
  global $weightedExternalQueryCount;
  global $weightedExternalQueryLimit;
  global $externalQueryCount;
  global $exceededQueryLimitMessage;
  global $cannotRetrieveMessage;
  global $thisMonth;
  global $mostRecentMonth;
  global $purgeperiod;
  global $recentMonthSlowdownFactor;
  global $tokenExpiredMessage;
  $page = str_replace('"','\"',$page);
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }

  #First looks for existing entries in the database

  $select_query = "select viewcount,querytime from viewcountsbymonth_all where pagename=\"".$page."\" and monthfull='".$month."' and language='".$language."' and drilldown='".$drilldown."' limit 1;";
  # print $select_query;

  $result = $mysqli->query($select_query);
  
  #If there is no entry, fetches it online

  if ($result->num_rows == 0) {
    $viewcount = getPageviewsOnline($page,$month,$language,$drilldown);
    if ($viewcount !== $cannotRetrieveMessage and $viewcount !== $tokenExpiredMessage) {
      $insert_query="insert into viewcountsbymonth_all(pagename,monthfull,language,drilldown,viewcount) values (\"".$page."\",'".$month."','".$language."','".$drilldown."',".$viewcount.");";
      $success = $mysqli->query($insert_query);
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
          $insert_query="insert into viewcountsbymonth_all(pagename,monthfull,language,drilldown,viewcount) values (\"".$page."\",'".$month."','".$language."','".$drilldown."',".$viewcount.");";
          $delete_query = "delete from viewcountsbymonth_all where pagename=\"".$page."\" and monthfull='".$month."' and language='".$language."' and drilldown='".$drilldown."';";
          $success = $mysqli->query($delete_query);
          $success = $mysqli->query($insert_query);
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

function getpageviews($page,$month,$language,$drilldown,$normalization='') {
  global $thisMonth;
  global $mysqli;
  global $numberofdays_allmonths;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $log_query = "insert into viewquerylog(pagename,monthfull,language) values (\"".$page."\",'".$month."','".$language."');";
  $result = $mysqli->query($log_query);
  queriedpagelog($page,$language,'partial');
  $viewcount = getPageviewsFromDb($page,$month,$language,$drilldown,true);
  if ($normalization == '')
    return $viewcount;
  elseif ($normalization == 'dailyaverage')
    return intval($viewcount/intval($numberofdays_allmonths[$month]));
}

function getannualpageviewsfromdb($page,$year,$language,$drilldown,$online) {
  global $mysqli;
  global $exceededQueryLimitMessage;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $page = str_replace('"','\"',$page);
  $select_query = "select viewcount from viewcountsbyyear_all where pagename=\"".$page."\" and year='".$year."' and language='".$language."' and drilldown='".$drilldown."'limit 1;";
  $result = $mysqli->query($select_query);
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
    $increment = getPageviewsFromDb($page,$monthfull,$language,$drilldown,$online);
    if ($increment == $exceededQueryLimitMessage) {return $exceededQueryLimitMessage;}
    $totalviews += intval($increment);
  }
  $select_query = "select status from years where year='".$year."';";
  $result = $mysqli->query($select_query);
  $row = $result->fetch_assoc();
  if ($row['status'] != 'future') {
    $insert_query = "insert into viewcountsbyyear_all(pagename,year,language,drilldown,viewcount) values(\"".$page."\",'".$year."','".$language."','".$drilldown."',".$totalviews.");";
    $success = $mysqli->query($insert_query);
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
  queriedpagelog($page,$language,'partial');
  return getannualpageviewsfromdb($page,$year,$language,$drilldown,true);
}

function viewcountarraybymonth_raw($pageList,$monthList,$language,$drilldownList,$online=true,$normalization='') {
  global $mysqli;
  global $weightedExternalQueryCount;
  global $weightedExternalQueryLimit;
  global $exceededQueryLimitMessage;
  global $purgeperiod;
  global $thisMonth;
  global $unavailableCount;
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
  $select_query = "select pagename,monthfull,language,drilldown,viewcount,querytime from viewcountsbymonth_all where pagename in (".$pageListAsQuotedCsvString.") and monthfull in (".$monthListAsQuotedCsvString.") and language='".$language."' and drilldown in (".$drilldownListAsQuotedCsvString.");";
  # print $select_query;
  $result = $mysqli->query($select_query);
  for ($i = 0;$i < $result->num_rows;$i++) {
    $row = $result->fetch_assoc();
    if ($row['monthfull'] != $thisMonth) {
      $viewcountarray[$row['pagename']][$row['monthfull']][$row['drilldown']] = $row['viewcount'];
    }
    if ($row['monthfull'] == $thisMonth) {
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
  wantedviewcountsquery($pageList,$monthList,$language,$drilldown,$viewcountarray);	
  foreach(array_reverse($pageList) as $page) {
    queriedpagelog($page,$language,'partial');
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
  if ($weightedExternalQueryCount < $weightedExternalQueryLimit) {
    #print "Successfully completed without timing out :)<br>";
    return $viewcountarray;
  }
  foreach($pageList as $page) {
    foreach($monthList as $month) {
      foreach($drilldownList as $drilldown) {
        if ($viewcountarray[$page][$month][$drilldown] == $exceededQueryLimitMessage) {
	  $viewcountarray[$page][$month][$drilldown] = getPageviewsFromDb($page,$month,$language,$drilldown,true);
        }
      }
    }
  }
  foreach($pageList as $page) {
    foreach($monthList as $month) {
      foreach($drilldownList as $drilldown) {
        if ($viewcountarray[$page][$month] == $exceededQueryLimitMessage) {
          $unavailableCount = $unavailableCount + 1;
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
  global $weightedExternalQueryCount;
  global $weightedExternalQueryLimit;
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
  $select_query = "select pagename,year,language,drilldown,viewcount from viewcountsbyyear_all where pagename in (".$pageListAsQuotedCsvString.") and year in (".$yearListAsQuotedCsvString.") and language='".$language."' and drilldown in ('".$drilldownListAsQuotedCsvString.");";
  $result = $mysqli->query($select_query);
  for ($i = 0;$i < $result->num_rows;$i++)
    {
      $row = $result->fetch_assoc();
      $viewcountarray[$row['pagename']][$row['year']][$row['drilldown']] = $row['viewcount'];
    }
  foreach(array_reverse($pageList) as $page)
      queriedpagelog($page,$language,'partial');
  foreach($pageList as $page) {
    foreach($yearList as $year) {
      foreach($drilldownList as $drilldown) {
        if ($viewcountarray[$page][$year][$drilldown] == 'unavailable' and $online = true) {
	  $viewcountarray[$page][$year][$drilldown] = getannualpageviewsfromdb($page,$year,$language,$drilldown,true);
        }
      }
    }
  }
  if ($weightedExternalQueryCount < $weightedExternalQueryLimit) {
    #print "Successfully completed without timing out :)<br>";
    return $viewcountarray;
  }
  foreach($pageList as $page) {
    foreach($yearList as $year) {
      foreach($drilldownList as $drilldown) {
        if ($viewcountarray[$page][$year][$drilldown] == $exceededQueryLimitMessage) {
	  $viewcountarray[$page][$year][$drilldown] = getannualpageviewsfromdb($page,$year,$language,$drilldown,true);
        }
      }
    }
  }
  return $viewcountarray;	
}

function fillinwantedviewcounts($querylimit, $online) {
  global $mysqli;
  global $weightedExternalQueryCount;
  global $weightedExternalQueryLimit;
  global $exceededQueryLimitMessage;
  if ($mysqli->connect_errno) 
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  $select_query = "select * from wantedviewcountsbymonth where status='wanted' limit ".$querylimit.";";
  # print $select_query;
  $result = $mysqli->query($select_query);
  if ($result ->num_rows == 0) return true;
  $working_query = "update wantedviewcountsbymonth set status='working' where row_id in (";
  $deletion_query = "delete from wantedviewcountsbymonth where row_id in (0";
  for($i=0;$i < $result->num_rows;$i++)
    {
      if ($i > 0) $working_query .= ",";
      $row = $result->fetch_assoc();
      $working_query .= $row['row_id'];
      $page[$i] = $row['pagename'];
      $month[$i] = $row['monthfull'];
      $language[$i] = $row['language'];
      $row_id[$i] = $row['row_id'];
    }
  $working_query .= ");";
  print "Going to execute query to reserve a few pages for lookup: ".$working_query."\n";
  $update_result = $mysqli->query($working_query);
  for($i=0;$i < $result->num_rows;$i++)
    {
      $currentLoad = sys_getloadavg();
      if ($currentLoad[0] < 0.75) {
        $count = getPageviewsFromDb($page[$i],$month[$i],$language[$i],"desktop",$online);
        print "Weighted external query count is ".$weightedExternalQueryCount." and ";
        print "weighted external query limit is ".$weightedExternalQueryLimit."\n";
        print "For page ".$page[$i].", month ".$month[$i].", and language ".$language[$i].", page view count is ".$count."\n";
        if ($count != $exceededQueryLimitMessage)
	  {
	    $deletion_query .= ",".$row_id[$i];
	  }
      } else {
      	exit;
      }
    }
  $deletion_query .= ");";
  print "Running deletion query: ".$deletion_query."\n";
  $deletion_result = $mysqli->query($deletion_query);
  print "Succeeded in running deletion query: ".$deletion_query."\n";
  return false;
}	


?>
