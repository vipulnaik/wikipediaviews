<?php

function checktagpresence($tag)
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select tag from pagetags where tag='".$tag."' limit 1;";
  $result = $mysqli->query($select_query);
  return ($result->num_rows > 0);
}

function addpagetotag($page,$language,$tag)
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select tag from pagetags where pagename='".$page."' and language='".$language."' and tag='".$tag."' limit 1;";
  $result = $mysqli->query($select_query);
  if ($result->num_rows==0)
    {
      $insert_query = "insert into pagetags(pagename,language,tag) values ('".$page."','".$language."','".$tag."');";
      $insert_result = $mysqli->query($insert_query);
      queriedpagelog($page,$language,'empty');
    }
}

function getpagelistbytag($tag,$language)
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
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

function gettagtotal($tag,$monthlist,$language='en',$online=true,$normalization='')
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $pagelist = getpagelistbytag($tag,$language);
  $viewcountarray = viewcountarraybymonth($pagelist,$monthlist,$language,$online,$normalization);
  $totalsandpercentages_array = totalsandpercentages($pagelist,$monthlist,$viewcountarray);
  return $totalsandpercentages_array[2];
}

function viewcountarraybytagandmonth_raw($taglist,$monthlist,$language,$online=true,$normalization='')
{
  foreach ($taglist as $tag)
    {
      $tagtotal = gettagtotal($tag,$monthlist,$language,$online,$normalization);
      foreach ($monthlist as $month)
	{
	  $viewcountarray[$tag][$month] = $tagtotal[$month];
	}
    }
  return $viewcountarray;
}

function viewcountarraybytagandmonth($taglist,$monthlist,$language='en',$online=true,$normalization='')
{
  global $exceededquerylimitmessage;
  global $numberofdays_allmonths;
  $viewcountarray = viewcountarraybytagandmonth_raw($taglist,$monthlist,$language,$online,$normalization);
  if ($normalization == '')
    {
      return $viewcountarray;
    }
  elseif ($normalization == 'dailyaverage')
    {
      foreach ($taglist as $tag)
	{
	  foreach ($monthlist as $month)
	    {
	      if ($viewcountarray[$tag][$month] != $exceededquerylimitmesage)
		{
		  $viewcountarray[$tag][$month] = round($viewcountarray[$tag][$month]/intval($numberofdays_allmonths[$month]),1);
		}
	    }
	}
    }
  return $viewcountarray;
}

function getpagelistbytaglist($taglist,$language,$connective='or')
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $tagselect_query = "select distinct pagetags.pagename from pagetags join queriedpages where pagetags.pagename = queriedpages.pagename and pagetags.language = queriedpages.language and pagetags.language='".$language."' and queriedpages.archivalstatus='complete'";
  if ($connective=='or')
    {
      $taglistasquotedcsvstring = convertlisttoquotedcsvstring($taglist);
      $tagselect_query .= "and pagetags.tag in (".$taglistasquotedcsvstring.")";
    }
  $taglist .= "order by pagetags.pagename asc;";
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
