<?php

## Retrieval file for the month list specification

## Corresponding data entry files (in inputdisplay directory):
## tagdropdownselectmultiple.inc

## Only included in displayviewsformultipletagsandmonths.php

##Retrieval of language
$language='en';
if (!empty($_REQUEST['language'])) {
  $language = $_REQUEST['language'];
}

## Retrieval of drilldown
$drilldownList = array("desktop");
if (!empty($_REQUEST['drilldownList'])) {
  $drilldownList = $_REQUEST['drilldownList'];
}
if (!empty($_REQUEST['drilldown'])) {
  $drilldownList = array($_REQUEST['drilldown']);
}

$tagList = array();
if (!empty($_REQUEST['tagList']))
  {
    $tagList = $_REQUEST['tagList'];
  }

if (count($tagList) == 0)
  {
    include(__DIR__."/../style/head.inc");
    print "You didn't select any tags. Please do so below.";
    $pagespecificationerror = true;
  }
?>
