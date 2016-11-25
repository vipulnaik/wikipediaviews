<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pageTypeAdvice="onemonth";
include("retrieval/languageListRetrieval.inc");
include("retrieval/drilldownListRetrieval.inc");
include("retrieval/pageListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");
$month = $mostRecentMonth;
if (!empty($_REQUEST['month'])) {
    $month = $_REQUEST['month'];
  }
$monthList = array($month);

if ($pageSpecificationError == true or $monthspecificationerror == true) {
  include("inputdisplay/".$pageTypeAdvice."dataentry.inc");
} else {
  switch ($displayFormat) {
    case 'csv' :
      printPageviewsForMonthOrYearListAsCsv($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat);
      break;
    case 'htmltable' : 
      include("style/head.inc");
      $permalinkUrl = "http://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent."&month=".$monthList[0].$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      $printStatus = printPageviewsForMonthOrYearListAsHtmlTable($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$sort);
      if (count($monthList) > 1 or count($pageListAsArray) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month');
      }   
      $originalMonthList = $monthList;
      $displayFormat='htmltableautomatic';
      $carryoverfromonemonth=true;
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'csvtransposed' :
      printPageviewsForMonthOrYearListAsCsvTransposed($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat);
      break;
  }
}
?>
