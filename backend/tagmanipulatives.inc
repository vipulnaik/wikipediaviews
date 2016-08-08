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

function gettagtotal($tag,$monthlist,$language='en',$device='desktop',$online=true,$normalization='')
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $pagelist = getpagelistbytag($tag,$language);
  $viewcountarray = viewcountarraybymonth($pagelist,$monthlist,$language,$device,$online,$normalization);
  $totalsandpercentages_array = totalsandpercentages($pagelist,$monthlist,$viewcountarray);
  return $totalsandpercentages_array[2];
}

function gettagtotalbyyear($tag,$yearlist,$language='en',$device='desktop',$online=true,$normalization='')
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $pagelist = getpagelistbytag($tag,$language);
  $viewcountarray = viewcountarraybyyear($pagelist,$yearlist,$language,$device,$online,$normalization);
  $totalsandpercentages_array = totalsandpercentages($pagelist,$yearlist,$viewcountarray);
  return $totalsandpercentages_array[2];
}

function viewcountarraybytagandmonth_raw($taglist,$monthlist,$language,$device,$online=true,$normalization='')
{
  foreach ($taglist as $tag)
    {
      $tagtotal = gettagtotal($tag,$monthlist,$language,$device,$online,$normalization);
      foreach ($monthlist as $month)
	{
	  $viewcountarray[$tag][$month] = $tagtotal[$month];
	}
    }
  return $viewcountarray;
}

function viewcountarraybytagandmonth($taglist,$monthlist,$language='en',$device='desktop',$online=true,$normalization='')
{
  global $exceededquerylimitmessage;
  global $numberofdays_allmonths;
  $viewcountarray = viewcountarraybytagandmonth_raw($taglist,$monthlist,$language,$device,$online,$normalization);
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

function viewcountarraybytagandyear($taglist,$yearlist,$language,$device,$online=true,$normalization='')
{
  foreach ($taglist as $tag)
    {
      $tagtotal = gettagtotalbyyear($tag,$yearlist,$language,$device,$online,$normalization);
      foreach ($yearlist as $year)
	{
	  $viewcountarray[$tag][$year] = $tagtotal[$year];
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
  $tagselect_query .= "order by pagetags.pagename asc;";
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

function gettaglistbypagelist($pagelist,$language)
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  foreach ($pagelist as $page)
    $taglist[$page] = array();
  $pagelistasquotedcsvstring = convertlisttoquotedcsvstring($pagelist);
  $tagselect_query = "select distinct pagename,tag from pagetags where pagename in (".$pagelistasquotedcsvstring.") and language='".$language."';";
  $result = $mysqli->query($tagselect_query);
  for ($i = 0;$i < $result -> num_rows; $i++)
    {
      $row = $result -> fetch_assoc();
      array_push($taglist[$row['pagename']],$row['tag']);      
    }
  return $taglist;
}

function gettagindices($pagelist,$language)
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $pagelistasquotedcsvstring = convertlisttoquotedcsvstring($pagelist);
  $tagselect_query = "select distinct tag from pagetags where pagename in (".$pagelistasquotedcsvstring.") and language='".$language."';";
  $result = $mysqli->query($tagselect_query);
  for ($i = 0;$i < $result -> num_rows; $i++)
    {
      $row = $result -> fetch_assoc();
      $tagindices[$row['tag']] = $i;
    }
  return $tagindices;
}

?>
