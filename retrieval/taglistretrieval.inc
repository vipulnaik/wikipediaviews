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
$drilldown='desktop';
if (!empty($_REQUEST['drilldown'])) {
  $drilldown = $_REQUEST['drilldown'];
}

$taglist = array();
if (!empty($_REQUEST['taglist']))
  {
    $taglist = $_REQUEST['taglist'];
  }

if (count($taglist) == 0)
  {
    include(__DIR__."/../style/head.inc");
    print "You didn't select any tags. Please do so below.";
    $pagespecificationerror = true;
  }
?>
