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
  $select_query = "select tag from pagetags where pagename=\"".$page."\" and language='".$language."' and tag='".$tag."' limit 1;";
  $result = $mysqli->query($select_query);
  if ($result->num_rows==0)
    {
      $insert_query = "insert into pagetags(pagename,language,tag) values (\"".$page."\",'".$language."','".$tag."');";
      $insert_result = $mysqli->query($insert_query);
      queriedpagelog($page,$language,'empty');
    }
}

function getpageListbytag($tag,$language)
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $tagselect_query = "select distinct pagetags.pagename from pagetags join queriedpages where pagetags.pagename = queriedpages.pagename and pagetags.language = queriedpages.language and pagetags.language='".$language."' and pagetags.tag='".$tag."' order by pagetags.pagename asc;";
#print $tagselect_query;
  $result = $mysqli->query($tagselect_query);
  $pageList = array();
  for ($i = 0; $i < $result->num_rows;$i++)
    {
      $row = $result->fetch_assoc();
      $pagename = $row['pagename'];
      array_push($pageList,$pagename);
    }
  return $pageList;
}

function gettagtotal($tag,$monthList,$language='en',$drilldown='desktop',$online=true,$normalization='')
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $pageList = getpageListbytag($tag,$language);
  $viewcountarray = viewcountarraybymonth($pageList,$monthList,$language,$drilldown,$online,$normalization);
  $totalsandpercentages_array = totalsandpercentages($pageList,$monthList,$viewcountarray);
  return $totalsandpercentages_array[2];
}

function gettagtotalbyyear($tag,$yearList,$language='en',$drilldown='desktop',$online=true,$normalization='')
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $pageList = getpageListbytag($tag,$language);
  $viewcountarray = viewcountarraybyyear($pageList,$yearList,$language,$drilldown,$online,$normalization);
  $totalsandpercentages_array = totalsandpercentages($pageList,$yearList,$viewcountarray);
  return $totalsandpercentages_array[2];
}

function viewcountarraybytagandmonth_raw($tagList,$monthList,$language,$drilldown,$online=true,$normalization='')
{
  foreach ($tagList as $tag)
    {
      $tagtotal = gettagtotal($tag,$monthList,$language,$drilldown,$online,$normalization);
      foreach ($monthList as $month)
	{
	  $viewcountarray[$tag][$month] = $tagtotal[$month];
	}
    }
  return $viewcountarray;
}

function viewcountarraybytagandmonth($tagList,$monthList,$language='en',$drilldown='desktop',$online=true,$normalization='')
{
  global $exceededquerylimitmessage;
  global $numberofdays_allmonths;
  $viewcountarray = viewcountarraybytagandmonth_raw($tagList,$monthList,$language,$drilldown,$online,$normalization);
  if ($normalization == '')
    {
      return $viewcountarray;
    }
  elseif ($normalization == 'dailyaverage')
    {
      foreach ($tagList as $tag)
	{
	  foreach ($monthList as $month)
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

function viewcountarraybytagandyear($tagList,$yearList,$language,$drilldown,$online=true,$normalization='')
{
  foreach ($tagList as $tag)
    {
      $tagtotal = gettagtotalbyyear($tag,$yearList,$language,$drilldown,$online,$normalization);
      foreach ($yearList as $year)
	{
	  $viewcountarray[$tag][$year] = $tagtotal[$year];
	}
    }
  return $viewcountarray;
}

function getpageListbytagList($tagList,$language,$connective='or')
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $tagselect_query = "select distinct pagetags.pagename from pagetags join queriedpages where pagetags.pagename = queriedpages.pagename and pagetags.language = queriedpages.language and pagetags.language='".$language."' and queriedpages.archivalStatus='complete'";
  if ($connective=='or')
    {
      $tagListasquotedcsvstring = convertlisttoquotedcsvstring($tagList);
      $tagselect_query .= "and pagetags.tag in (".$tagListasquotedcsvstring.")";
    }
  $tagselect_query .= "order by pagetags.pagename asc;";
  $result = $mysqli->query($tagselect_query);
  $pageList = array();
  for ($i = 0; $i < $result->num_rows;$i++)
    {
      $row = $result->fetch_assoc();
      $pagename = $row['pagename'];
      array_push($pageList,$pagename);
    }
  return $pageList;
}

function gettagListbypageList($pageList,$language)
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  foreach ($pageList as $page)
    $tagList[$page] = array();
  $pageListasquotedcsvstring = convertlisttoquotedcsvstring($pageList);
  $tagselect_query = "select distinct pagename,tag from pagetags where pagename in (".$pageListasquotedcsvstring.") and language='".$language."';";
  $result = $mysqli->query($tagselect_query);
  for ($i = 0;$i < $result -> num_rows; $i++)
    {
      $row = $result -> fetch_assoc();
      array_push($tagList[$row['pagename']],$row['tag']);      
    }
  return $tagList;
}

function gettagindices($pageList,$language)
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $pageListasquotedcsvstring = convertlisttoquotedcsvstring($pageList);
  $tagselect_query = "select distinct tag from pagetags where pagename in (".$pageListasquotedcsvstring.") and language='".$language."';";
  $result = $mysqli->query($tagselect_query);
  for ($i = 0;$i < $result -> num_rows; $i++)
    {
      $row = $result -> fetch_assoc();
      $tagindices[$row['tag']] = $i;
    }
  return $tagindices;
}

?>
