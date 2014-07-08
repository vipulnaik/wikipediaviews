<?php

function getpageviewsonline($page, $month, $language)
{
	$url = getpageviewsurl($page,$month,$language);
	$html = file_get_contents($url);
	preg_match('/(?<=\bhas been viewed)\s+\K[^\s]+/',$html,$numberofpageviews);
	return $numberofpageviews[0];
}

function getpageviewsfromdb($page,$month,$language)
{
       global $mysqli;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
	$select_query = "select viewcount from viewcountsbymonth where pagename='".$page."' and monthfull='".$month."' and language='".$language."' limit 1;";
	$result = $mysqli->query($select_query);
	if ($result->num_rows == 0)
	{
	    $viewcount = getpageviewsonline($page,$month,$language);
	    $insert_query="insert into viewcountsbymonth(pagename,monthfull,language,viewcount) values ('".$page."','".$month."','".$language."',".$viewcount.");";
	    $success = $mysqli->query($insert_query);
	    return $viewcount;
	}
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
	#print $log_query;
	$result = $mysqli->query($log_query);

        if ($month==$thismonth) {return getpageviewsonline($page,$month,$language);}
	return getpageviewsfromdb($page,$month,$language);
}

function getannualpageviews($page,$year,$language)
{
	$monthstringlist = array("01","02","03","04","05","06","07","08","09","10","11","12");
	$totalviews = 0;
	foreach ($monthstringlist as $monthwithoutyear)
	{
	   $monthwithyear = $year.$monthwithoutyear;
	   $totalviews += getpageviews($page,$monthwithyear,$language);
	}
	return $totalviews;
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
       $tagselect_query = "select pagename from pagetags where language='".$language."' and tag='".$tag."';";
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
?>