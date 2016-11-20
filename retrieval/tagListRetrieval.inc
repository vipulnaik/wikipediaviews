<?php

## Retrieval file for the month list specification

## Corresponding data entry files (in inputdisplay directory):
## tagdropdownselectmultiple.inc

## Only included in displayviewsformultipletagsandmonths.php

## Retrieval of language
$languageList = array("en");
if (!empty($_REQUEST['languages'])) {
  $languageList = $_REQUEST['languages'];
}
if (!empty($_REQUEST['languageList'])) {
  $languageList = $_REQUEST['languageList'];
}
if (!empty($_REQUEST['language'])) {
  $sentLanguage = $_REQUEST['language'];
  $languageList = array($sentLanguage);
}

## Retrieval of drilldown
$drilldownList = array("desktop");
if (!empty($_REQUEST['drilldownList'])) {
  $drilldownList = $_REQUEST['drilldownList'];
}
if (!empty($_REQUEST['drilldown'])) {
  $sentDrilldown = $_REQUEST['drilldown'];
  if ($sentDrilldown == "all") {
    $drilldownList = array("desktop", "mobile-web", "mobile-app", "desktop-spider", "mobile-web-spider");
  } else {
    $drilldownList = array($sentDrilldown);
  }
}

$tagList = array();
if (!empty($_REQUEST['tagList'])) {
  $tagList = $_REQUEST['tagList'];
}
if (!empty($_REQUEST['tag'])) {
  $tagList = array($_REQUEST['tag']);
}

if (count($tagList) == 0)
  {
    include(__DIR__."/../style/head.inc");
    print "You didn't select any tags. Please do so below.";
    $pagespecificationerror = true;
  }
?>
