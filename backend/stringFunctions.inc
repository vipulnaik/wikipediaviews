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

function getLongUrl($page,$month,$language,$drilldown,$project="wikipedia") {
  global $mostRecentMonth;
  $monthToEndWith = $mostRecentMonth;
  if ($month > $monthToEndWith) {
    $monthToEndWith = $month;
  }
  $year = intval(substr($monthToEndWith, 0, 4));
  $justMonth = intval(substr($monthToEndWith, 4));
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
  return "https://wikimedia.org/api/rest_v1/metrics/pageviews/per-article/" . $language . "." . $project . "/" . $drilldown . "/" . $userType . "/" . str_replace("%2527", "%27", urlencode(str_replace(" ","_",$page))) . "/monthly/" . "20150701/" . $endOfMonth . "?purge" . strval(rand());
}

function getPageviewsUrl($page,$month,$language,$drilldown,$project='wikipedia') {
  if ($drilldown == "country-total") {
    return getCountryTotalBreakdown($month);
  } else if ($drilldown == "cumulative-facebook-shares") {
    return getFacebookShareCountUrl($page,$month,$language,$project);
  } else if ($month < '201507' and $page == "[aggregate]") {
    return getApiPageviewsUrl($page,$month,$language,$drilldown,$project);  
  } else if ($month < '201507' and $drilldown == "desktop") {
    return getSgsPageviewsUrl($page,$month,$language);
  } else {
    return getApiPageviewsUrl($page,$month,$language,$drilldown,$project);
  }
}

function getFacebookShareCountUrl($page, $month, $language, $project) {
  $preEncodingPage = "https://".$language.".".$project.".org/wiki/".str_replace(" ","_",$page);
  $urlEncodedPage = urlencode($preEncodingPage);
  $fbUrl = "https://graph.facebook.com/v2.8/?id=" . $urlEncodedPage;
  return $fbUrl;
}

function getCountryTotalBreakdown($month) {
  return "https://stats.wikimedia.org/archive/squid_reports/".substr($month,0,4)."-".substr($month,4,6)."/SquidReportPageViewsPerCountryBreakdownHuge.htm";
}

function getSgsPageviewsUrl($page,$month,$language) {
  $preEncodingPage = str_replace(" ","_",$page);
  $urlEncodedPage = str_replace("%2F", "/", urlencode($preEncodingPage)); # Don't encode /
  return "http://stats.grok.se/" . $language . "/" . $month . "/" . $urlEncodedPage;
}

function getApiPageviewsUrl($page,$month,$language,$drilldown,$project='wikipedia') {
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
  if ($page == '[aggregate]' and $month >= "201507") {
    return "https://wikimedia.org/api/rest_v1/metrics/pageviews/aggregate/" . $language . "." . $project . "/" . $drilldown . "/" . $userType . "/daily/" . $month . "0100/" . $endOfMonth . "23?purge" . strval(rand());
  } else if ($page == '[aggregate]' and in_array($drilldown, array("desktop", "mobile-web"))) {
    switch ($drilldown) {
      case "desktop" :
        return "https://wikimedia.org/api/rest_v1/metrics/legacy/pagecounts/aggregate/" . $language . "." . $project . "/desktop-site/daily/" . $month . "0100/" . $endOfMonth . "23?purge" . strval(rand());
	break;
      case "mobile-web" :
        return "https://wikimedia.org/api/rest_v1/metrics/legacy/pagecounts/aggregate/" . $language . "." . $project . "/mobile-site/daily/" . $month . "0100/" . $endOfMonth . "23?purge" . strval(rand());
        break;
    }
  } else {
    return "https://wikimedia.org/api/rest_v1/metrics/pageviews/per-article/" . $language . "." . $project . "/" . $drilldown . "/" . $userType . "/" . str_replace("%2527", "%27", urlencode(str_replace(" ","_",$page))) . "/daily/" . $month . "01/" . $endOfMonth . "?purge" . strval(rand());
  }
}

function getAnnualPageviewsUrl($page,$year,$language,$drilldown="desktop",$project="wikipedia") {
  if ($project != "Wikipedia") {
    return "https://wikipediaviews.org/displayviewsformultiplemonths.php?year=".$year."&page=".urlencode($page)."&language=".$language."&project=".$project."&drilldown=".$drilldown;
  } else {
    return "https://wikipediaviews.org/displayviewsformultiplemonths.php?year=".$year."&page=".urlencode($page)."&language=".$language."&drilldown=".$drilldown;
  }
}

function getTagViewsUrl($tag,$month,$language,$drilldown="desktop",$project="wikipedia") {
  if ($project != "wikipedia") {
    return "https://wikipediaviews.org/displayviewsforonemonth.php?month=".$month."&tag=".urlencode($tag)."&language=".$language."&project=".$project."&drilldown=".$drilldown;
  } else {
    return "https://wikipediaviews.org/displayviewsforonemonth.php?month=".$month."&tag=".urlencode($tag)."&language=".$language."&drilldown=".$drilldown;
  }
}

function getAllTimeTagViewsUrl($tag,$language,$project="wikipedia") {
  if ($project != "wikipedia") {
    return "https://wikipediaviews.org/displayviewsformultiplemonths.php?allmonths=allmonths&tag=".urlencode($tag)."&language=".$language."&project=".$project."&drilldown=all";
  } else {
    return "https://wikipediaviews.org/displayviewsformultiplemonths.php?allmonths=allmonths&tag=".urlencode($tag)."&language=".$language."&drilldown=all";
  }
}

function getAnnualTagViewsUrl($tag,$year,$language,$drilldown="desktop",$project="wikipedia") {
  if ($project != "wikipedia") {
    return "https://wikipediaviews.org/displayviewsformultipleyears.php?year=".$year."&tag=".urlencode($tag)."&language=".$language."&project=".$project."&drilldown=".$drilldown;
  } else {
    return "https://wikipediaviews.org/displayviewsformultipleyears.php?year=".$year."&tag=".urlencode($tag)."&language=".$language."&drilldown=".$drilldown;
  }
}

function getPageUrl($page,$language,$project='wikipedia') {
  $page = str_replace(" ","_",$page);
  return "https://" . $language . "." . $project . ".org/wiki/" . urlencode($page);
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
  if ($numericDisplayFormat=='kmbt')
    {
      return numericDisplayKMBT($number);
    }
  if ($numericDisplayFormat=='log')
    {
      return numericDisplayLog($number);
    }
  return $number;
}

function numericDisplayKMBT($number) {
  $number_int = intval($number);
  if ($number_int < 1000) {
    return $number;
  } elseif ($number_int >= 1000 and $number_int < 9950) {
    $number_k = round((floatval ($number_int))/1000,1);
    return (strval($number_k)."K");
  } elseif ($number_int >= 9950 and $number_int < 999500) {
    $number_k = round((floatval ($number_int))/1000,0);
    return (strval($number_k)."K");
  } elseif ($number_int >= 999500 and $number_int < 9950000) {
    $number_m = round((floatval ($number_int))/1000000,1);
    return (strval($number_m)."M");
  } elseif ($number_int >= 9950000 and $number_int < 999500000) {
    $number_m = round((floatval ($number_int))/1000000,0);
    return (strval($number_m)."M");
  } elseif ($number_int >= 999500000 and $number_int < 9950000000) {
    $number_b = round((floatval ($number_int))/1000000000,1);
    return (strval($number_b)."B");
  } elseif ($number_int >= 9950000000 and $number_int < 995000000000) {
    $number_b = round((floatval ($number_int))/1000000000,0);
    return (strval($number_b)."B");
  } elseif ($number_int >= 995000000000 and $number_int < 9950000000000) {
    $number_t = round((floatval ($number_int))/1000000000000,1);
    return (strval($number_t)."T");
  }
  return $number;
}

function numericDisplayLog($number) {
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
