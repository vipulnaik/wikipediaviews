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
		$select_query = "select row_id,pagename,language from queriedpages where archivalstatus!='complete' limit 1;";
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
	$yearlist = pastyearlist();
	foreach($monthlist as $month)
	{
	  getpageviewsfromdb($page,$month,$language,true);
	} 
	foreach($yearlist as $year)
	{
	  getannualpageviewsfromdb($page,$year,$language,true);
	}
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
  function onearchivalstep()
  {
	global $externalquerylimit;
	global $externalquerycount;
	$externalquerycount = 0;
	removeduplicates();
	$row = fetchworkingpagerowid();
	if ($row==false) 
	{
		return false;
	}
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
  while ($sleepcounter < 3 and $keepgoing)
  {
	$keepgoing = (onearchivalstep() == false);
	sleep(15);
	$sleepcounter++;
  }
?>
