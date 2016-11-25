<?php

## Retrieval file for the month list specification

## Corresponding data entry files (in inputdisplay directory):
## alternatemonthspecificationoptions.inc, monthcheckboxlist.inc,
## monthdropdown.inc

## Only included in displayviewsformultiplemonths.php

$originalMonthList = array($mostRecentMonth);

if (!empty($_REQUEST['months'])) {
  $originalMonthList = $_REQUEST['months'];
}

if (!empty($_REQUEST['month'])) {
  $requestedMonth = $_REQUEST['month'];
  $originalMonthList = array($requestedMonth);
}

if (!empty($_REQUEST['monthList'])) {
  $originalMonthList = $_REQUEST['monthList'];
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


if ($allmonths == "allmonths" and (in_array($thisMonth,$originalMonthList))) {
  $monthList = presentandpastmonths_monthList();
  $monthUrlComponent = "&allmonths=allmonths-present";
} elseif ($allmonths == "allmonths-present") {
  $monthList = presentandpastmonths_monthList();
  $monthUrlComponent = "&allmonths=allmonths-present";
} elseif ($allmonths == "allmonths") {
  $monthList = pastmonths_monthList();
  $monthUrlComponent = "&allmonths=allmonths";
} else {
  $monthList = $originalMonthList;
  if (count($monthList) == 1) {
    $monthUrlComponent = "&month=".$monthList[0];
  } else {
    $monthUrlComponent = "";
    for ($i = 0; $i < count($monthList); $i++) {
      $monthUrlComponent .= "&months[$i]=".$monthList[$i];
    }
  }
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
