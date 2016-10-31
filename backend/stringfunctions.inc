<?php

function convertpagelisttoarray($pagelistasstring) {
  $pagelistasinput = isset($pagelistasstring)?$pagelistasstring:"";
  $pagelistasarray = array_unique(explode("\n", str_replace("\r", "", $pagelistasinput)));
  foreach (array_keys($pagelistasarray, "") as $key) 
    {
      unset($pagelistasarray[$key]);
    }
  foreach($pagelistasarray as &$page)
    {
      $page = trim($page," \t\n\r\0\x0B");
    }     
  return $pagelistasarray;
}

function getMonthCountDbName($device) {
  switch ($device) {
    case "desktop" :
      return "viewcountsbymonth";
      break;
    case "mobile-app" :
      return "viewcountsbymonth_mobileapp";
      break;
    case "mobile-web" :
      return "viewcountsbymonth_mobileweb";
      break;
    case "desktop-spider" :
      return "viewcountsbymonth_desktop_spider";
      break;
    case "mobile-web-spider" :
      return "viewcountsbymonth_mobileweb_spider";
      break;
    case "facebook-share" :
      return "facebooksharecounts";
      break;
  }
}

function getDescriptor($device) {
  switch ($device) {
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
    case "facebook-share" :
      return "Cumulative Facebook shares";
      break;
  }
}
  
function getPageviewsUrl($page,$month,$language,$device) {
  if ($device == "facebook-share") {
    return getFacebookShareCountUrl($page,$month,$language);
  } else if ($month < 201601 and $device == "desktop") {
    return getSgsPageviewsUrl($page,$month,$language);
  } else {
    return getApiPageviewsUrl($page,$month,$language,$device);
  }
}

function getFacebookShareCountUrl($page, $month, $language) {
  $preEncodingPage = "https://".$language.".wikipedia.org/wiki/".str_replace(" ","_",$page);
  $urlEncodedPage = urlencode($preEncodingPage);
  $fbUrl = "https://graph.facebook.com/v2.8/?id=" . $urlEncodedPage;
  return $fbUrl;
}

function getSgsPageviewsUrl($page,$month,$language) {
  $page = str_replace(" ","_",$page);
  $page = str_replace("'","%27",$page);
  return "http://stats.grok.se/" . $language . "/" . $month . "/" . $page;
}

function getApiPageviewsUrl($page,$month,$language,$device) {
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
  switch ($device) {
    case "desktop-spider" :
      $device = "desktop";
      $userType = "spider";
      break;
    case "mobile-web-spider":
      $device = "mobile-web";
      $userType = "spider";
      break;
  }
  return "https://wikimedia.org/api/rest_v1/metrics/pageviews/per-article/" . $language . ".wikipedia/" . $device . "/" . $userType . "/" . str_replace("%2527", "%27", urlencode(str_replace(" ","_",$page))) . "/daily/" . $month . "01/" . $endOfMonth . "?purge" . strval(rand());
}
function getannualpageviewsurl($page,$year,$language,$device="desktop") {
  return "http://wikipediaviews.org/displayviewsformultiplemonths.php?year=".$year."&page=".$page."&language=".$language."&device=".$device;
}

function gettagviewsurl($tag,$month,$language,$device="desktop") {
  return "http://wikipediaviews.org/displayviewsforonemonth.php?month=".$month."&tag=".$tag."&language=".$language."&device=".$device;
}

function getannualtagviewsurl($tag,$year,$language,$device="desktop") {
  return "http://wikipediaviews.org/displayviewsformultipleyears.php?year=".$year."&tag=".$tag."&language=".$language."&device=".$device;
}

function getpageurl($page,$language) {
  $page = str_replace(" ","_",$page);
  return "http://" . $language . ".wikipedia.org/wiki/" . $page;
}

function convertlisttoquotedcsvstring($listasarray) {
  $listasquotedcsvstring = '"'.str_replace('"','\"',$listasarray[0]).'"';
  for($i = 1;$i < sizeof($listasarray);$i++)
    {
      $listasquotedcsvstring .= ',"'.str_replace('"', '\"',$listasarray[$i]).'"';
    }
  return $listasquotedcsvstring;
}

function numericdisplay($number,$numericdisplayformat) {
  if ($numericdisplayformat=='fullprecision')
    {
      return $number;
    }
  if ($numericdisplayformat=='kmb')
    {
      return numericdisplaykmb($number);
    }
  if ($numericdisplayformat=='log')
    {
      return numericdisplaylog($number);
    }
  return $number;
}

function numericdisplaykmb($number) {
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

function numericdisplaylog($number) {
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
