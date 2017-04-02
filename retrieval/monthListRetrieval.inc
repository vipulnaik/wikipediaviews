<?php

## Retrieval file for the month list specification

## Corresponding data entry files (in inputDisplay directory):
## alternatemonthspecificationoptions.inc, monthCheckboxList.inc,
## monthDropdown.inc

## Only included in displayviewsformultiplemonths.php

$originalMonthList = array($mostRecentMonth);

if (!empty($_REQUEST['months'])) {
  $originalMonthList = $_REQUEST['months'];
} elseif (!empty($_REQUEST['month'])) {
  $originalMonthList = array($_REQUEST['month']);
} elseif (!empty($_REQUEST['monthList'])) {
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
} elseif ($allmonths == "allmonths-api" and (in_array($thisMonth, $originalMonthList))) {
  $monthList = presentandpastapimonths_monthList();
  $monthUrlComponent = "&allmonths=allmonths-api-present";
} elseif ($allmonths == "allmonths-api-present") {
  $monthList = presentandpastapimonths_monthList();
  $monthUrlComponent = "&allmonths=allmonths-api-present";
} elseif ($allmonths == "allmonths-api") {
  $monthList = pastapimonths_monthList();
  $monthUrlComponent = "&allmonths=allmonths-api";
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
    $monthSpecificationError = true;
}

elseif ($year != "") {
  $monthUrlComponent = "&year=$year";
  $monthList = pastmonthsinyear($year);
}

elseif ($monthacrossyears != "") {
  $monthUrlComponent = "&monthacrossyears=$monthacrossyears";
  $monthList = monthacrossallyears($monthacrossyears);
}

if (count($monthList) == 0) {
    include(__DIR__."/../style/head.inc");
    print "You didn't select any months. Please do so below.";
    $monthSpecificationError = true;
}
?>
