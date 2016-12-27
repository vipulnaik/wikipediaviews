<?php

## Retrieval file for the year list specification

## Corresponding data entry files (in inputdisplay directory):
## yearCheckboxList.inc

## Only included in displayviewsformultipleyears.php

$originalYearList=array($mostRecentYear);

if (!empty($_REQUEST['years'])) {
  $originalYearList = $_REQUEST['years'];
} elseif (!empty($_REQUEST['year'])) {  
  $originalYearList = array($_REQUEST['year']);
} elseif (!empty($_REQUEST['yearList'])) {
  $originalYearList = $_REQUEST['yearList'];
}

$allyears='allyears';
if (!empty($_REQUEST['allyears'])) {
  $allyears = $_REQUEST['allyears'];
} elseif (!empty($_REQUEST['yearList']) or !empty($_REQUEST['year'] or !empty($_REQUEST['years']))) {
  $allyears = '';
}

if ($allyears == "allyears") {
  $yearList = presentandpastyears_yearList();
  $yearUrlComponent = '&allyears=allyears';
} else {
  $yearList = $originalYearList;
  if (count($yearList) == 1) {
    $yearUrlComponent = "&year=".$yearList[0];
  } else {
    $yearUrlComponent = "";
    for ($i = 0; $i < count($yearList); $i++) {
      $yearUrlComponent .= "&years[$i]=".$yearList[$i];
    }
  }
}

if (sizeof($yearList) == 0) {
  include("style/head.inc");
  print "You didn't select any years. Please do so below.";
  $yearSpecificationError = true;
}
 
?>
