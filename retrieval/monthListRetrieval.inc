<?php

## Retrieval file for the month list specification

## Corresponding data entry files (in inputdisplay directory):
## alternatemonthspecificationoptions.inc, monthcheckboxlist.inc,
## monthdropdown.inc

## Only included in displayviewsformultiplemonths.php

if (!empty($_REQUEST['months'])) {
  $monthList = $_REQUEST['months'];
}


$monthacrossyears = '';
if (!empty($_REQUEST['monthacrossyears'])) {
  $monthacrossyears = $_REQUEST['monthacrossyears'];
}

$year = '';
if (!empty($_REQUEST['year'])) {
  $year = $_REQUEST['year'];
}

$allmonths = '';
if (!empty($_REQUEST['allmonths'])) {
  $allmonths = $_REQUEST['allmonths'];
}

$originalmonthList = array($mostRecentMonth);
if (!empty($_REQUEST['monthList'])) {
  $originalmonthList = $_REQUEST['monthList'];
}

if ($allmonths == "allmonths" and (in_array($thisMonth,$originalmonthList) or (!empty($_REQUEST['months']) and in_array($thisMonth, $monthList)))) {
    $monthList = presentandpastmonths_monthList();
} elseif ($allmonths == "allmonths") {
    $monthList = pastmonths_monthList();
} elseif (empty($_REQUEST['months'])) {
    $monthList = $originalmonthList;
}

if ($year != "" and $monthacrossyears != "") {
    include(__DIR__."/../style/head.inc");
    print "You provided multiple alternate methods for selecting the set of months. Please choose only one.";
    $monthspecificationerror = true;
}

elseif ($year != "") {
    $monthList = pastmonthsinyear($year);
}

elseif ($monthacrossyears != "") {
    $monthList = monthacrossallyears($monthacrossyears);
}

if (count($monthList) == 0) {
    include(__DIR__."/../style/head.inc");
    print "You didn't select any months. Please do so below.";
    $monthspecificationerror = true;
}
?>
