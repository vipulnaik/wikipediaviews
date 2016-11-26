<?php

# Retrieves the list of drilldowns

## Retrieval of drilldown
$drilldownList = array("desktop");
if (!empty($_REQUEST['drilldowns'])) {
  $drilldownList = $_REQUEST['drilldowns'];
}
if (!empty($_REQUEST['drilldownList'])) {
  $drilldownList = $_REQUEST['drilldownList'];
}
if (!empty($_REQUEST['drilldown'])) {
  $sentDrilldown = $_REQUEST['drilldown'];
  $drilldownUrlComponent = "&drilldown=".$sentDrilldown;
  if ($sentDrilldown == "all") {
    $drilldownList = array("desktop", "mobile-web", "mobile-app", "desktop-spider", "mobile-web-spider");
  } elseif ($sentDrilldown == "referrers") {
    $drilldownList = array("referrer:other-search", "referrer:other-external", "referrer:other-other", "referrer:other-empty", "referrer:other-internal", "referrer:Wikipedia", "referrer:other-bing", "referrer:other-facebook", "referrer:other-google", "referrer:other-twitter", "referrer:other-wikipedia", "referrer:other-yahoo", "referrer:other");
  } elseif ($sentDrilldown == "referrers-new") {
    $drilldownList = array("referrer:other-search", "referrer:other-external", "referrer:other-other", "referrer:other-empty", "referrer:other-internal", "referrer:Wikipedia");
  } elseif ($sentDrilldown == "referrers-old") {
    $drilldownList = array("referrer:other-other", "referrer:other-empty", "referrer:other-internal", "referrer:Wikipedia", "referrer:other-bing", "referrer:other-facebook", "referrer:other-google", "referrer:other-twitter", "referrer:other-wikipedia", "referrer:other-yahoo");
  } else {
    $drilldownList = array($sentDrilldown);
  }
} else {
  if (count($drilldownList) == 1) {
    $drilldownUrlComponent = "&drilldown=".$drilldownList[0];
  } elseif ($drilldownList == array("desktop", "mobile-web", "mobile-app", "desktop-spider", "mobile-web-spider")) {
    $drilldownUrlComponent = "&drilldown=all";
  } else {
    $drilldownUrlComponent = "";
    for ($i = 0; $i < count($drilldownList); $i++) {
      $drilldownUrlComponent .= "&drilldowns[$i]=".$drilldownList[$i];
    }
  }
}

?>
