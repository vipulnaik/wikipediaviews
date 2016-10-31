<?php

function wantedviewcountsquery($pagelist,$monthlist,$language,$device,$viewcountarray) {
  $numberofwantedviewcounts = 0;
  $insert_query = "insert into wantedviewcountsbymonth(pagename,monthfull,language,status) values ";
  foreach ($pagelist as $page) {
    foreach ($monthlist as $month) {
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


function queriedpagelog($page,$language,$archivalstatus) {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select row_id from queriedpages where pagename=\"".$page."\" and language='".$language."' limit 1;";
  $result = $mysqli->query($select_query);
  $page = str_replace('"','\"',$page);
  if ($result->num_rows == 0) {
    $insert_query = "insert into queriedpages(pagename,language,archivalstatus) values (\"".$page."\",'".$language."','".$archivalstatus."');";
    $result = $mysqli->query($insert_query);
  }
  return $result;
}

function getPageviewsOnline($page, $month, $language, $device) {
  global $weightedexternalquerycount;
  global $externalquerycount;
  global $weightedexternalquerylimit;
  global $thismonth;
  global $mostrecentmonth;
  global $recentmonthslowdownfactor;
  global $exceededquerylimitmessage;
  global $cannotRetrieveMessage;
  global $fbToken;
  global $curlOutputDirectory;
  global $tokenExpiredMessage;
  if ($weightedexternalquerycount >= $weightedexternalquerylimit)
      return $exceededquerylimitmessage;
  if ($month == $thismonth or $month == $mostrecentmonth)
      $weightedexternalquerycount = $weightedexternalquerycount + $recentmonthslowdownfactor;
  else
      $weightedexternalquerycount++;
  $url = getPageviewsUrl($page,$month,$language,$device);
  if ($device == "facebook-share") {
    if ($month == $thismonth) {
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
  } else if ($month < 201601 and $device == "desktop") {
    $html = file_get_contents($url);
    preg_match('/(?<=\bhas been viewed)\s+\K[^\s]+/',$html,$numberofpageviews);
    if (count($numberofpageviews) > 0) {
      if (strlen($numberofpageviews[0]) > 0) {
        $externalquerycount++;
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
    $externalquerycount++;
    return $sum;
  } else {
    $weightedexternalquerycount = $weightedexternalquerycount - $recentmonthslowdownfactor;
    return 0;
  }
}

function getpageviewsfromdb($page,$month,$language,$device, $online) {
  global $mysqli;
  global $weightedexternalquerycount;
  global $weightedexternalquerylimit;
  global $externalquerycount;
  global $exceededquerylimitmessage;
  global $cannotRetrieveMessage;
  global $thismonth;
  global $mostrecentmonth;
  global $purgeperiod;
  global $recentmonthslowdownfactor;
  $page = str_replace('"','\"',$page);
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }

  #First looks for existing entries in the database

  $monthCountDb = getMonthCountDbName($device);
  $select_query = "select viewcount,querytime from " .  $monthCountDb . " where pagename=\"".$page."\" and monthfull='".$month."' and language='".$language."' limit 1;";

  $result = $mysqli->query($select_query);
  
  #If there is no entry, fetches it online

  if ($result->num_rows == 0) {
    $viewcount = getPageviewsOnline($page,$month,$language,$device);
    if ($viewcount !== $cannotRetrieveMessage and $viewcount !== $tokenExpiredMessage) {
      $insert_query="insert into ".$monthCountDb."(pagename,monthfull,language,viewcount) values (\"".$page."\",'".$month."','".$language."',".$viewcount.");";
      $success = $mysqli->query($insert_query);
    }
  } else {
    $row = $result->fetch_assoc();
    $viewcount = $row['viewcount'];
      
    #But wait, now we must check that the value is not too outdated

    if ($month == $thismonth) {
      $currentdate = new DateTime("now");
      $dateofretrieval = new DateTime($row['querytime']); 
      $dayspassedasdiff = date_diff($dateofretrieval,$currentdate);
      $dayspassed = intval($dayspassedasdiff -> d);
      if ($dayspassed > $purgeperiod) {
	$viewcount = getPageviewsOnline($page,$month,$language,$device);

        if ($viewcount != $exceededquerylimitmessage and $viewcount != cannotRetrieveMessage) {
          $insert_query="insert into ".$monthCountDb."(pagename,monthfull,language,viewcount) values (\"".$page."\",'".$month."','".$language."',".$viewcount.");";
          $delete_query = "delete from ".$monthCountDb." where pagename=\"".$page."\" and monthfull='".$month."' and language='".$language."';";
          $success = $mysqli->query($delete_query);
          $success = $mysqli->query($insert_query);
        }
      }
    }
  }
  #If a value has been successfully retrieved, removes it from the wanted query list
  if ($viewcount != $exceededquerylimitmessage and $device == "desktop") {
    $delete_query = "delete from wantedviewcountsbymonth where pagename=\"".$page."\" and monthfull='".$month."' and language='".$language."';";
    $success = $mysqli->query($delete_query);
  }
  return $viewcount;
}

function getpageviews($page,$month,$language,$device,$normalization='') {
  global $thismonth;
  global $mysqli;
  global $numberofdays_allmonths;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $log_query = "insert into viewquerylog(pagename,monthfull,language) values (\"".$page."\",'".$month."','".$language."');";
  $result = $mysqli->query($log_query);
  queriedpagelog($page,$language,'partial');
  $viewcount = getpageviewsfromdb($page,$month,$language,$device,true);
  if ($normalization == '')
    return $viewcount;
  elseif ($normalization == 'dailyaverage')
    return intval($viewcount/intval($numberofdays_allmonths[$month]));
}

function getannualpageviewsfromdb($page,$year,$language,$device,$online) {
  global $mysqli;
  global $exceededquerylimitmessage;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  $page = str_replace('"','\"',$page);
  $yearCountDb = getYearCountDbName($device);
  $select_query = "select viewcount from ".$yearCountDb." where pagename=\"".$page."\" and year='".$year."' and language='".$language."' limit 1;";
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
    $increment = getpageviewsfromdb($page,$monthfull,$language,$device,$online);
    if ($increment == $exceededquerylimitmessage) {return $exceededquerylimitmessage;}
    $totalviews += intval($increment);
  }
  $select_query = "select status from years where year='".$year."';";
  $result = $mysqli->query($select_query);
  $row = $result->fetch_assoc();
  if ($row['status'] != 'future') {
    $insert_query = "insert into ".$yearCountDb."(pagename,year,language,viewcount) values(\"".$page."\",'".$year."','".$language."',".$totalviews.");";
    $success = $mysqli->query($insert_query);
  }
  return $totalviews;
}

function getannualpageviews($page,$year,$language,$device) {
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $log_query = "insert into viewquerylogbyyear(pagename,year,language) values (\"".$page."\",'".$year."','".$language."');";
  $result = $mysqli->query($log_query);
  queriedpagelog($page,$language,'partial');
  return getannualpageviewsfromdb($page,$year,$language,$device,true);
}

function viewcountarraybymonth_raw($pagelist,$monthlist,$language,$device,$online=true,$normalization='') {
  global $mysqli;
  global $weightedexternalquerycount;
  global $weightedexternalquerylimit;
  global $exceededquerylimitmessage;
  global $purgeperiod;
  global $thismonth;
  global $unavailablecount;
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }
  if (sizeof($pagelist) == 0 or sizeof($monthlist) == 0) return false;
  foreach($pagelist as $page) {
    foreach($monthlist as $month) {
      $viewcountarray[$page][$month] = 'unavailable';
    }
  }
  $pagelistasquotedcsvstring = convertlisttoquotedcsvstring($pagelist);
  $monthlistasquotedcsvstring = convertlisttoquotedcsvstring($monthlist);
  $monthCountDb = getMonthCountDbName($device);
  $select_query = "select pagename,monthfull,viewcount,querytime from " . $monthCountDb . " where pagename in (".$pagelistasquotedcsvstring.") and monthfull in (".$monthlistasquotedcsvstring.") and language='".$language."';";

  $result = $mysqli->query($select_query);
  for ($i = 0;$i < $result->num_rows;$i++) {
    $row = $result->fetch_assoc();
    if ($row['monthfull'] != $thismonth) {
      $viewcountarray[$row['pagename']][$row['monthfull']] = $row['viewcount'];
    }
    if ($row['monthfull'] == $thismonth) {
      $currentdate = new DateTime("now");
      $dateofretrieval = new DateTime($row['querytime']); 
      $dayspassedasdiff = date_diff($dateofretrieval,$currentdate);
      $dayspassed = intval($dayspassedasdiff->d);
      if ($dayspassed > $purgeperiod) {
	$viewcountarray[$row['pagename']][$row['monthfull']] = 'unavailable';
      } else {
	$viewcountarray[$row['pagename']][$row['monthfull']] = $row['viewcount'];
      }
    }		
  }
  wantedviewcountsquery($pagelist,$monthlist,$language,$device,$viewcountarray);	
  foreach(array_reverse($pagelist) as $page) {
    queriedpagelog($page,$language,'partial');
  }
  foreach($pagelist as $page) {
    foreach($monthlist as $month) {
      if ($viewcountarray[$page][$month] == 'unavailable' and $online == true) {
        $viewcountarray[$page][$month] = getpageviewsfromdb($page,$month,$language,$device,true);
      }
    }
  }
  if ($weightedexternalquerycount < $weightedexternalquerylimit) {
    #print "Successfully completed without timing out :)<br>";
    return $viewcountarray;
  }
  foreach($pagelist as $page) {
    foreach($monthlist as $month) {
      if ($viewcountarray[$page][$month] == $exceededquerylimitmessage) {
	$viewcountarray[$page][$month] = getpageviewsfromdb($page,$month,$language,$device,true);
      }
    }
  }  
  foreach($pagelist as $page) {
    foreach($monthlist as $month) {
      if ($viewcountarray[$page][$month] == $exceededquerylimitmessage) {
        $unavailablecount = $unavailablecount + 1;
      }
    }
  }
  
  return $viewcountarray;
}

function viewcountarraybymonth($pagelist,$monthlist,$language,$device,$online,$normalization='') {
  global $exceededquerylimitmessage;
  global $numberofdays_allmonths;
  $viewcountarray = viewcountarraybymonth_raw($pagelist,$monthlist,$language,$device,$online,$normalization);
  if ($normalization == '')
    return $viewcountarray;
  elseif ($normalization == 'dailyaverage') {
    foreach ($pagelist as $page) {
      foreach ($monthlist as $month) {
	if ($viewcountarray[$page][$month] != $exceededquerylimitmesage) {
	  $viewcountarray[$page][$month] = round($viewcountarray[$page][$month]/intval($numberofdays_allmonths[$month]),1);
        }
      }
    }
  }
  return $viewcountarray;
}

function viewcountarraybyyear($pagelist,$yearlist,$language,$device,$online,$normalization='') {
  global $mysqli;
  global $weightedexternalquerycount;
  global $weightedexternalquerylimit;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  if (sizeof($pagelist) == 0 or sizeof($yearlist) == 0) return false;
  foreach($pagelist as $page)
      foreach($yearlist as $year)
	$viewcountarray[$page][$year] = 'unavailable';
  $pagelistasquotedcsvstring = convertlisttoquotedcsvstring($pagelist);
  $yearlistasquotedcsvstring = convertlisttoquotedcsvstring($yearlist);	
  $yearCountDb = getYearCountDbName($device);
  $select_query = "select pagename,year,viewcount from ".$yearCountDb." where pagename in (".$pagelistasquotedcsvstring.") and year in (".$yearlistasquotedcsvstring.") and language='".$language."';";
  $result = $mysqli->query($select_query);
  for ($i = 0;$i < $result->num_rows;$i++)
    {
      $row = $result->fetch_assoc();
      $viewcountarray[$row['pagename']][$row['year']] = $row['viewcount'];
    }
  foreach(array_reverse($pagelist) as $page)
      queriedpagelog($page,$language,'partial');
  foreach($pagelist as $page)
    foreach($yearlist as $year)
      if ($viewcountarray[$page][$year] == 'unavailable' and $online = true)
	$viewcountarray[$page][$year] = getannualpageviewsfromdb($page,$year,$language,$device,true);

  if ($weightedexternalquerycount < $weightedexternalquerylimit) {
    #print "Successfully completed without timing out :)<br>";
    return $viewcountarray;
  }
  foreach($pagelist as $page)
    foreach($yearlist as $year)
      if ($viewcountarray[$page][$year] == $exceededquerylimitmessage)
	$viewcountarray[$page][$year] = getannualpageviewsfromdb($page,$year,$language,$device,true);    
  return $viewcountarray;	
}

function fillinwantedviewcounts($querylimit, $online) {
  global $mysqli;
  global $weightedexternalquerycount;
  global $weightedexternalquerylimit;
  global $exceededquerylimitmessage;
  if ($mysqli->connect_errno) 
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  $select_query = "select * from wantedviewcountsbymonth where status='wanted' limit ".$querylimit.";";
  #print $select_query;
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
        $count = getpageviewsfromdb($page[$i],$month[$i],$language[$i],"desktop",$online);
        print "Weighted external query count is ".$weightedexternalquerycount." and ";
        print "weighted external query limit is ".$weightedexternalquerylimit."\n";
        print "For page ".$page[$i].", month ".$month[$i].", and language ".$language[$i].", page view count is ".$count."\n";
        if ($count != $exceededquerylimitmessage)
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
