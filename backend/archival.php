<?php
  include("corecode.inc");
  global $parity;
  $parity = true;
  function pastmonthlist()
  {
       global $mysqli;
       global $parity;
       $monthlist = array();
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
       $select_query = "select monthfull from months where status='past' or status='mostrecent';";
       $result=$mysqli->query($select_query);
       for ($i = 0;$i < $result->num_rows;$i++)
       {
         $row = $result->fetch_assoc();
	 array_push($monthlist,$row['monthfull']);
       }
       if ($parity == false)
       {
	  $parity = true;
	  return array_reverse($monthlist);
       }
       else
       {
	  $parity = false;
	  return $monthlist;
       }
  }	

  function pastyearlist()
  {
       global $mysqli;
       global $parity;
       $yearlist = array();
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
       $select_query = "select year from years where status='past' or status='pastincomplete' or status='mostrecent';";
       $result=$mysqli->query($select_query);
       for ($i = 0;$i < $result->num_rows;$i++)
       {
         $row = $result->fetch_assoc();
	 array_push($yearlist,$row['year']);
       }
       if ($parity == false)
       {
	  $parity = true;
	  return $yearlist;
       }
       else
       {
	  $parity = false;
	  return array_reverse($yearlist);
       }
  }	

  function fetchworkingpagerowid()
  {
       global $mysqli;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
       $select_query = "select row_id,pagename,language from queriedpages where archivalstatus='partial' limit 1;";
       $result=$mysqli->query($select_query);
       if ($result->num_rows > 0)
       {
         $row = $result->fetch_assoc();
	 return $row;
       }
       else
       {
         $select_query = "select row_id,pagename,language from queriedpages where archivalstatus='empty' limit 1;";
         $result=$mysqli->query($select_query);
         if ($result->num_rows > 0)
         {
         $row = $result->fetch_assoc();
	 return $row;
       	 }
       	 else
       	 {
		$select_query = "select row_id,pagename,language from queriedpages where archivalstatus!='complete' and archivalstatus!='mostrecentmonthpending' limit 1;";
         	$result=$mysqli->query($select_query);
         	if ($result->num_rows > 0)
         	{
			$row = $result->fetch_assoc();
	 		return $row;
       	 	}
       		else
		{
			return false;
		}
	}
      }
   }     

   function fetchcurrentmonthrowids()
   {
       global $mysqli;
       global $externalquerylimit;
       global $recentmonthslowdownfactor;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
       $select_query = "select row_id,pagename,language from queriedpages where archivalstatus='mostrecentmonthpending' limit 5000;";
       print $select_query;
       $result=$mysqli->query($select_query);
       if ($result->num_rows > 0)
         	{
			return $result;
       	 	}
       else
		{
			return false;
		}
   }
   function markinitiation($row)
   {
       global $mysqli;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
  $update_query = "update queriedpages set archivalstatus='filling' where row_id=".$row['row_id'].";";
  $result = $mysqli->query($update_query);
  }

   function fillindata($page,$language)
   {
       $monthlist = pastmonthlist();
	$yearlist = presentandpastyears_yearlist();
	foreach($monthlist as $month)
	{
	  getpageviewsfromdb($page,$month,$language,true);
	} 
	foreach($yearlist as $year)
	{
	  getannualpageviewsfromdb($page,$year,$language,true);
	}
   }

   function fillindatamostrecentmonthonly($page,$language)
   {
	global $mostrecentmonth;
	global $thisyear;
	global $mysqli;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
	getpageviewsfromdb($page,$mostrecentmonth,$language,true);
	print "Filling in of data for current month successful!<br>";
	$delete_query = "delete from viewcountsbyyear where pagename='".$page."' and year='".$thisyear."';";
	$delete_result = $mysqli->query($delete_query);
	getannualpageviewsfromdb($page,$thisyear,$language,true);
	print "Updating current year successful!<br>";
   }

   function marksuspension($row)
   {
       global $mysqli;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
  $update_query = "update queriedpages set archivalstatus='partial' where row_id=".$row['row_id'].";";
  $result = $mysqli->query($update_query);
  }


   function markcompletion($row)
  {
       global $mysqli;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
  $update_query = "update queriedpages set archivalstatus='complete' where row_id=".$row['row_id'].";";
  $result = $mysqli->query($update_query);
  }

  function removeduplicates()
  {
       global $mysqli;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
       $delete_query = "delete from viewcountsbymonth where row_id in (select maxId from dupIDs_viewcountsbymonth);";
       $result=$mysqli->query($delete_query);
       $delete_query = "delete from viewcountsbyyear where row_id in (select maxId from dupIDs_viewcountsbyyear);";
       $result=$mysqli->query($delete_query);
       $delete_query = "delete from queriedpages where row_id in (select maxId from dupIDs_queriedpages);";
       $result=$mysqli->query($delete_query);
  }

  function logforwardlinks($language='en')
  {	   
       global $mysqli;
       if ($mysqli->connect_errno) {
       	  echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
       }
       $select_query = "select pagename,language from queriedpages where language='".$language."' and pagelinks IS NULL limit 1";
       $select_result = $mysqli->query($select_query);
       if ($select_result -> num_rows == 0) return false;
       $row = $select_result -> fetch_assoc();
       $linkingpage = $row['pagename'];
       $pagelist = getpagelistbylinkingpage($linkingpage,$language);
       foreach($pagelist as $page)
       {
		queriedpagelog($page,$language,'empty');
       }
       $update_query = "update queriedpages set pagelinks='entered' where pagename='".$linkingpage."' and language='".$language."';";
       $update_result = $mysqli->query($update_query);
  }
  # function syncqueriedpages()
  # {
  #      global $mysqli;
  #      if ($mysqli->connect_errno) {
  #      	  echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  #      }
  #      $select_query = "select distinct pagename from viewcountsbymonth;";
  #      $select_result = $mysqli->query($select_query);
  #      $allpagelist = array();
  #      for ($i = 0;$i < $select_result->num_rows;$i++)
  #      {
  # 	 $row = $select_result->fetch_assoc();
  # 	 array_push($allpagelist,$row['pagename']);
  #      }
  #      foreach($allpagelist as $page)
  #      {
  # 	 queriedpagelog($page,
  # }
  function onearchivalstep()
  {
	global $externalquerylimit;
	global $externalquerycount;
	fillinwantedviewcounts($externalquerylimit -$externalquerycount);
	removeduplicates();
	$row = fetchworkingpagerowid();
	if ($row==false) 
	{
		print "Only current month pending, fetching pages for that<br>";
		$currentmonthrows = fetchcurrentmonthrowids();
		print "Fetched ".$currentmonthrows -> num_rows." rows<br>";
		if ($currentmonthrows -> num_rows == 0)
		{
			print "Nothing for the current month either. Logging forward links to get more work to do in the next iteration!";
			logforwardlinks();
			return false;
		}
		for ($i = 0;$i < $currentmonthrows->num_rows;$i++)
		{
			$row = $currentmonthrows->fetch_assoc();
			#markinitiation($row);
			#print "Marked initiation of row with pagename '".$row['pagename']."' and language '".$row['language']."'<br>";
			fillindatamostrecentmonthonly($row['pagename'],$row['language']);
			if ($externalquerycount < $externalquerylimit) 
           		   {markcompletion($row);
			   print "Marked completion of row with pagename '".$row['pagename']."' and language '".$row['language']."'<br>";}
		}
		return true;
	}
	print "Fetched row with pagename ".$row['pagename']." and language ".$row['language'];
        markinitiation($row);
	fillindata($row['pagename'],$row['language']);
	if ($externalquerycount < $externalquerylimit) 
           {markcompletion($row);}
        else
           {marksuspension($row);}
	return true;
  }

  $keepgoing = true;
  $sleepcounter = 0;
  global $hardquerylimit;
  $externalquerycount = 0;
  $externalquerylimit = $hardquerylimit;
  while ($sleepcounter < 50 and $externalquerycount < $externalquerylimit)
  {
        if ($sleepcounter > 0)
	 {
	 	sleep(3);
	 }
	print "Entering iteration ".$sleepcounter."<br>";
	onearchivalstep();
	print "Reached external query count ".$externalquerycount."<br>";
	$sleepcounter++;
  }
?>
