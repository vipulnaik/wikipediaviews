<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice="onemonth";
include("retrieval/pageListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");
$month = $mostRecentMonth;
if (!empty($_REQUEST['month'])) {
    $month = $_REQUEST['month'];
  }
$monthList = array($month);

if ($pagespecificationerror == true or $monthspecificationerror == true) {
  include("inputdisplay/".$pagetypeadvice."dataentry.inc");
} else {
  switch ($displayformat) {
    case 'csv' :
      printPageviewsForMonthOrYearListAsCsv($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat);
      break;
    case 'htmltable' : 
      include("style/head.inc"); 
      printPageviewsForMonthOrYearListAsHtmlTable($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      $originalmonthList = $monthList;
      $displayformat='htmltableautomatic';
      $carryoverfromonemonth=true;
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'csvtransposed' :
      printPageviewsForMonthOrYearListAsCsvTransposed($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat);
      break;
    case 'countsonlyseparatelines' :
      printPageviewsAsCountsOnlySeparateLines($pageListAsArray,$month,$languageList,$drilldownList,$numericDisplayFormat);
      break;
  }
}
?>
