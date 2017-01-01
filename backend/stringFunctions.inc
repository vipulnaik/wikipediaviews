<?php

function nonempty($string) {
  if (strlen($string) > 0) {
    print "String \"$string\" has length ".strlen($string)." which is positive<br>";
    return true;
  } else {
    print "String \"$string\" is empty<br>";
    return false;
  }
}

function convertPageListToArray($pageListAsString) {
  $pageListAsInput = isset($pageListAsString)?$pageListAsString:"";
  $pageList = array_unique(explode("\n", str_replace("\r", "", $pageListAsInput)));
  $newPageList = array();
  foreach($pageList as $page) {
    $newPage = trim($page," \t\n\r\0\x0B");
    if (strlen($newPage) > 0) {
      array_push($newPageList, $newPage);
    }
  }
  return $newPageList;
}

function getDescriptor($drilldown) {
  switch ($drilldown) {
    case "desktop" :
      return "Pageviews";
      break;
    case "mobile-app" :
      return "Pageviews";
      break;
    case "mobile-web" :
      return "Pageviews";
      break;
    case "desktop-spider" :
      return "Pageviews";
      break;
    case "mobile-web-spider" :
      return "Pageviews";
      break;
    case "cumulative-facebook-shares" :
      return "Cumulative Facebook shares";
      break;
  }
}

function getShortDescriptor($drilldown) {
  switch ($drilldown) {
    case "desktop" :
      return "Views";
      break;
    case "mobile-app" :
      return "Views";
      break;
    case "mobile-web" :
      return "Views";
      break;
    case "desktop-spider" :
      return "Views";
      break;
    case "mobile-web-spider" :
      return "Views";
      break;
    case "cumulative-facebook-shares" :
      return "Cumulative shares";
      break;
    default :
      return "Views";
      break;
  }
}

function getPageviewsUrl($page,$month,$language,$drilldown) {
  if ($drilldown == "cumulative-facebook-shares") {
    return getFacebookShareCountUrl($page,$month,$language);
  } else if ($month < 201507 and $drilldown == "desktop") {
    return getSgsPageviewsUrl($page,$month,$language);
  } else {
    return getApiPageviewsUrl($page,$month,$language,$drilldown);
  }
}

function getFacebookShareCountUrl($page, $month, $language) {
  $preEncodingPage = "https://".$language.".wikipedia.org/wiki/".str_replace(" ","_",$page);
  $urlEncodedPage = urlencode($preEncodingPage);
  $fbUrl = "https://graph.facebook.com/v2.8/?id=" . $urlEncodedPage;
  return $fbUrl;
}

function getSgsPageviewsUrl($page,$month,$language) {
  $preEncodingPage = str_replace(" ","_",$page);
  $urlEncodedPage = str_replace("%2F", "/", urlencode($preEncodingPage)); # Don't encode /
  return "http://stats.grok.se/" . $language . "/" . $month . "/" . $urlEncodedPage;
}

function getApiPageviewsUrl($page,$month,$language,$drilldown) {
  $year = intval(substr($month, 0, 4));
  $justMonth = intval(substr($month, 4));
  switch (intval($justMonth)) {
    case 1: $endOfMonth = $year . '0131';
    	    break;
    case 2: if ($year % 4 != 0) 
    	       $endOfMonth = $year.'0228';
	    else 
	       $endOfMonth = $year.'0229';
	    break;
    case 3: $endOfMonth = $year . '0331';
    	    break;
    case 4 : $endOfMonth = $year . '0430';
    	     break;
    case 5 : $endOfMonth = $year . '0531';
    	     break;
    case 6 : $endOfMonth = $year . '0630';
    	     break;
    case 7 : $endOfMonth = $year . '0731';	
    	     break;
    case 8 : $endOfMonth = $year . '0831';
    	     break;
    case 9 : $endOfMonth = $year . '0930';
    	     break;
    case 10: $endOfMonth = $year . '1031';
    	     break;
    case 11: $endOfMonth = $year . '1130';
    	     break;
    case 12: $endOfMonth = $year . '1231';
  }
  $userType = "user";
  switch ($drilldown) {
    case "desktop-spider" :
      $drilldown = "desktop";
      $userType = "spider";
      break;
    case "mobile-web-spider":
      $drilldown = "mobile-web";
      $userType = "spider";
      break;
  }
  if ($page == '[aggregate]') {
    return "https://wikimedia.org/api/rest_v1/metrics/pageviews/aggregate/" . $language . ".wikipedia/" . $drilldown . "/" . $userType . "/daily/" . $month . "0100/" . $endOfMonth . "23?purge" . strval(rand());
  } else {
    return "https://wikimedia.org/api/rest_v1/metrics/pageviews/per-article/" . $language . ".wikipedia/" . $drilldown . "/" . $userType . "/" . str_replace("%2527", "%27", urlencode(str_replace(" ","_",$page))) . "/daily/" . $month . "01/" . $endOfMonth . "?purge" . strval(rand());
  }
}

function getannualpageviewsurl($page,$year,$language,$drilldown="desktop") {
  return "https://wikipediaviews.org/displayviewsformultiplemonths.php?year=".$year."&page=".$page."&language=".$language."&drilldown=".$drilldown;
}

function gettagviewsurl($tag,$month,$language,$drilldown="desktop") {
  return "https://wikipediaviews.org/displayviewsforonemonth.php?month=".$month."&tag=".$tag."&language=".$language."&drilldown=".$drilldown;
}

function getannualtagviewsurl($tag,$year,$language,$drilldown="desktop") {
  return "https://wikipediaviews.org/displayviewsformultipleyears.php?year=".$year."&tag=".$tag."&language=".$language."&drilldown=".$drilldown;
}

function getpageurl($page,$language) {
  $page = str_replace(" ","_",$page);
  return "http://" . $language . ".wikipedia.org/wiki/" . $page;
}

function convertListToQuotedCsvString($listasarray) {
  $listAsQuotedCsvString = '"'.str_replace('"','\"',$listasarray[0]).'"';
  for($i = 1;$i < sizeof($listasarray);$i++)
    {
      $listAsQuotedCsvString .= ',"'.str_replace('"', '\"',$listasarray[$i]).'"';
    }
  return $listAsQuotedCsvString;
}

function numericDisplay($number,$numericDisplayFormat) {
  if ($numericDisplayFormat=='fullprecision')
    {
      return $number;
    }
  if ($numericDisplayFormat=='kmb')
    {
      return numericDisplaykmb($number);
    }
  if ($numericDisplayFormat=='log')
    {
      return numericDisplaylog($number);
    }
  return $number;
}

function numericDisplaykmb($number) {
  $number_int = intval($number);
  if ($number_int < 1000)
    {
      return $number;
    }
  if ($number_int >= 1000 and $number_int < 9950)
    {
      $number_k = round((floatval ($number_int))/1000,1);
      return (strval($number_k)."K");
    }
  if ($number_int >= 9950 and $number_int < 999500)
    {
      $number_k = round((floatval ($number_int))/1000,0);
      return (strval($number_k)."K");
    }
  if ($number_int >= 999500 and $number_int < 9950000)
    {
      $number_m = round((floatval ($number_int))/1000000,1);
      return (strval($number_m)."M");
    }
  if ($number_int >= 9950000 and $number_int < 999500000)
    {
      $number_m = round((floatval ($number_int))/1000000,0);
      return (strval($number_m)."M");
    }
  if ($number_int >= 999500000 and $number_int < 9950000000)
    {
      $number_b = round((floatval ($number_int))/1000000000,1);
      return (strval($number_b)."B");
    }
  if ($number_int >= 9950000000)
    {
      $number_b = round((floatval ($number_int))/1000000000,0);
      return (strval($number_b)."B");
    }
  return $number;
}

function numericDisplaylog($number) {
  if ($number == 0) return "-infinity";
  return round(log($number,10),1);
}

function monthviewtooltip($number) {
  $tooltipstring = $number;
  $tooltipstring .= " views (click to view day-wise breakdown)";
  return $tooltipstring;
}

function yearviewtooltip($number) {
  $tooltipstring = $number;
  $tooltipstring .= " (click to view month-wise breakdown on this site)";
  return $tooltipstring;
}

?>
