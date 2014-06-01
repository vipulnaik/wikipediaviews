<?php

function queriedpagelog($page,$language,$archivalstatus)
{
       global $mysqli;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
	$select_query = "select row_id from queriedpages where pagename='".$page."' and language='".$language."' limit 1;";
	$result = $mysqli->query($select_query);
	if ($result->num_rows == 0)
	{
		$insert_query = "insert into queriedpages(pagename,language,archivalstatus) values ('".$page."','".$language."','".$archivalstatus."');";
		$result = $mysqli->query($insert_query);
	}
	return $result;
}
function getpageviewsonline($page, $month, $language)
{
	$url = getpageviewsurl($page,$month,$language);
	$html = file_get_contents($url);
	preg_match('/(?<=\bhas been viewed)\s+\K[^\s]+/',$html,$numberofpageviews);
	return $numberofpageviews[0];
}

function getpageviewsfromdb($page,$month,$language,$online)
{
       global $mysqli;
       global $externalquerycount;
       global $externalquerylimit;
       global $exceededquerylimitmessage;
       global $thismonth;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;}
	$select_query = "select viewcount from viewcountsbymonth where pagename='".$page."' and monthfull='".$month."' and language='".$language."' limit 1;";
	$result = $mysqli->query($select_query);
	if ($result->num_rows == 0 and $online == true and $externalquerycount < $externalquerylimit)
	{
	    $viewcount = getpageviewsonline($page,$month,$language);
	    $insert_query="insert into viewcountsbymonth(pagename,monthfull,language,viewcount) values ('".$page."','".$month."','".$language."',".$viewcount.");";
	    $success = $mysqli->query($insert_query);
	    $externalquerycount++;
	    return $viewcount;
	}
	if ($result->num_rows == 0) {return $exceededquerylimitmessage;}
	$row = $result->fetch_assoc();
	return $row['viewcount'];
}
function getpageviews($page,$month,$language)
{
	global $thismonth;
        global $mysqli;
        if ($mysqli->connect_errno) {
        echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
        }
	$log_query = "insert into viewquerylog(pagename,monthfull,language) values ('".$page."','".$month."','".$language."');";
	$result = $mysqli->query($log_query);
	queriedpagelog($page,$language,'partial');
	return getpageviewsfromdb($page,$month,$language,true);
}

function getannualpageviewsfromdb($page,$year,$language,$online)
{
	global $mysqli;
	global $exceededquerylimitmessage;
        if ($mysqli->connect_errno) {
        echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
        }
	$select_query = "select viewcount from viewcountsbyyear where pagename='".$page."' and year='".$year."' and language='".$language."' limit 1;";
	$result = $mysqli->query($select_query);
	if ($result->num_rows == 1)
	{
	   $row = $result->fetch_assoc();
	   return $row['viewcount'];
	}
	$select_query = "select monthfull from months where status!='present' and status!='future' and year='".$year."';";
	$result = $mysqli->query($select_query);
	$totalviews = 0;
	for($i=0;$i < $result->num_rows;$i++)
	{
	  $row = $result->fetch_assoc();
	  $monthfull = $row['monthfull'];
	  $increment = getpageviewsfromdb($page,$monthfull,$language,$online);
	  if ($increment == $exceededquerylimitmessage) {return $exceededquerylimitmessage;}
	  $totalviews += intval($increment);
        }
	$select_query = "select status from years where year='".$year."';";
	$result = $mysqli->query($select_query);
	$row = $result->fetch_assoc();
	if ($row['status'] != 'future')
	{
	$insert_query = "insert into viewcountsbyyear(pagename,year,language,viewcount) values('".$page."','".$year."','".$language."',".$totalviews.");";
	$success = $mysqli->query($insert_query);
	}
	return $totalviews;
}

function getannualpageviews($page,$year,$language)
{
        global $mysqli;
        if ($mysqli->connect_errno) {
        echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
        }
	$log_query = "insert into viewquerylogbyyear(pagename,year,language) values ('".$page."','".$year."','".$language."');";
	$result = $mysqli->query($log_query);
	queriedpagelog($page,$language,'partial');
	return getannualpageviewsfromdb($page,$year,$language,true);
}

function getpageviewsthismonth($page,$language)
{
	global $thismonth;
	return getpageviews($page,$thismonth,$language);
}

function getpagelistbytag($tag,$language)
{
       global $mysqli;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
       $tagselect_query = "select pagetags.pagename from pagetags join queriedpages where pagetags.pagename = queriedpages.pagename and pagetags.language = queriedpages.language and pagetags.language='".$language."' and pagetags.tag='".$tag."' and queriedpages.archivalstatus='complete' order by pagetags.pagename asc;";
       #print $tagselect_query;
       $result = $mysqli->query($tagselect_query);
       $pagelist = array();
       for ($i = 0; $i < $result->num_rows;$i++)
       {
          $row = $result->fetch_assoc();
	  $pagename = $row['pagename'];
	  array_push($pagelist,$pagename);
       }
       return $pagelist;
}

function viewcountarraybymonth_modular($pagelist,$monthlist,$language,$online,$datanormalization='none')
{
	foreach($pagelist as $page)
	{
		foreach($monthlist as $month)
		{
			$viewcountarray[$page][$month] = getpageviews($page,$month,$language);
	        }
        }
	return $viewcountarray;
}

function viewcountarraybymonth($pagelist,$monthlist,$language,$online,$datanormalization='none')
{
	global $mysqli;
	global $externalquerycount;
	global $externalquerylimit;
	global $exceededquerylimitmessage;
        if ($mysqli->connect_errno) {
        echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
        }
	if (sizeof($pagelist) == 0 or sizeof($monthlist) == 0) return false;
	foreach($pagelist as $page)
	{
		foreach($monthlist as $month)
		{
			$viewcountarray[$page][$month] = 'unavailable';
	        }
        }
	$pagelistasquotedcsvstring = convertlisttoquotedcsvstring($pagelist);
	$monthlistasquotedcsvstring = convertlisttoquotedcsvstring($monthlist);	
	$select_query = "select pagename,monthfull,viewcount from viewcountsbymonth where pagename in (".$pagelistasquotedcsvstring.") and monthfull in (".$monthlistasquotedcsvstring.") and language='".$language."';";
	$result = $mysqli->query($select_query);
	for ($i = 0;$i < $result->num_rows;$i++)
	{
		$row = $result->fetch_assoc();
		$viewcountarray[$row['pagename']][$row['monthfull']] = $row['viewcount'];
	}
	foreach(array_reverse($pagelist) as $page)
	{
		queriedpagelog($page,$language,'partial');
	}
	foreach($pagelist as $page)
	{
		foreach($monthlist as $month)
		{
			
			if ($viewcountarray[$page][$month] == 'unavailable' and $online == true)
			{
				$viewcountarray[$page][$month] = getpageviewsfromdb($page,$month,$language,true);
			}
	        }
        }
	if ($externalquerycount < $externalquerylimit)
	{
		#print "Successfully completed without timing out :)<br>";
		return $viewcountarray;
	}
	foreach($pagelist as $page)
	{
		foreach($monthlist as $month)
		{
			if ($viewcountarray[$page][$month] == $exceededquerylimitmessage)
			{
				$viewcountarray[$page][$month] = getpageviewsfromdb($page,$month,$language,true);
			}
	        }
        }

	return $viewcountarray;
}

function viewcountarraybyyear_modular($pagelist,$yearlist,$language,$online,$datanormalization='none')
{
	foreach($pagelist as $page)
	{
		foreach($yearlist as $year)
		{
			$viewcountarray[$page][$year] = getannualpageviews($page,$year,$language);
	        }
        }
	return $viewcountarray;
}

function viewcountarraybyyear($pagelist,$yearlist,$language,$online,$datanormalization='none')
{
	global $mysqli;
	global $externalquerycount;
	global $externalquerylimit;
        if ($mysqli->connect_errno) {
        echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
        }
	if (sizeof($pagelist) == 0 or sizeof($yearlist) == 0) return false;
	foreach($pagelist as $page)
	{
		foreach($yearlist as $year)
		{
			$viewcountarray[$page][$year] = 'unavailable';
	        }
        }
	$pagelistasquotedcsvstring = convertlisttoquotedcsvstring($pagelist);
	$yearlistasquotedcsvstring = convertlisttoquotedcsvstring($yearlist);	
	$select_query = "select pagename,year,viewcount from viewcountsbyyear where pagename in (".$pagelistasquotedcsvstring.") and year in (".$yearlistasquotedcsvstring.") and language='".$language."';";
	$result = $mysqli->query($select_query);
	for ($i = 0;$i < $result->num_rows;$i++)
	{
		$row = $result->fetch_assoc();
		$viewcountarray[$row['pagename']][$row['year']] = $row['viewcount'];
	}
	foreach(array_reverse($pagelist) as $page)
	{
		queriedpagelog($page,$language,'partial');
	}
	foreach($pagelist as $page)
	{
		foreach($yearlist as $year)
		{
			if ($viewcountarray[$page][$year] == 'unavailable' and $online = true)
			{
				$viewcountarray[$page][$year] = getannualpageviewsfromdb($page,$year,$language,true);
			}
	        }
        }
	if ($externalquerycount < $externalquerylimit)
	{
		#print "Successfully completed without timing out :)<br>";
		return $viewcountarray;
	}
	foreach($pagelist as $page)
	{
		foreach($yearlist as $year)
		{
			if ($viewcountarray[$page][$year] == $exceededquerylimitmessage)
			{
				$viewcountarray[$page][$year] = getannualpageviewsfromdb($page,$year,$language,true);
			}
	        }
        }
	return $viewcountarray;	
}

function presentandpastmonths_sql()
{
        global $mysqli;
        if ($mysqli->connect_errno) {
        echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
	}
	$select_query = "select monthfull,month,year,status from months where status!='future'";
	return $mysqli->query($select_query);
}	

function pastmonths_sql()
{
        global $mysqli;
        if ($mysqli->connect_errno) {
        echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
	}
	$select_query = "select monthfull,month,year,status from months where status!='future' and status!='present'";
	return $mysqli->query($select_query);
}	

function presentandpastyears_sql()
{
        global $mysqli;
        if ($mysqli->connect_errno) {
        echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
	}
	$select_query = "select year,status from years where status!='future'";
	return $mysqli->query($select_query);
}	

function presentandpastyears_yearlist()
{
       $sql_result = presentandpastyears_sql();
       $yearlist = array();
       for ($i = 0;$i < $sql_result->num_rows;$i++)
       {
         $row = $sql_result->fetch_assoc();
	 array_push($yearlist,$row['year']);
       }
       return $yearlist;
}

function presentandpastmonths_monthlist()
{
       $sql_result = presentandpastmonths_sql();
       $monthlist = array();
       for ($i = 0;$i < $sql_result->num_rows;$i++)
       {
         $row = $sql_result->fetch_assoc();
	 array_push($monthlist,$row['monthfull']);
       }
       return $monthlist;
}

function pastmonths_monthlist()
{
       $sql_result = pastmonths_sql();
       $monthlist = array();
       for ($i = 0;$i < $sql_result->num_rows;$i++)
       {
         $row = $sql_result->fetch_assoc();
	 array_push($monthlist,$row['monthfull']);
       }
       return $monthlist;
}

?>
