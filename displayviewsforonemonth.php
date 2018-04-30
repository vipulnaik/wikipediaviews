<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/coreCode.inc");
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

if ($pageSpecificationError == true or $monthSpecificationError == true) {
  include("inputDisplay/".$pageTypeAdvice."dataentry.inc");
} else {
  switch ($displayFormat) {
    case 'htmltable' : 
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent."&month=".$monthList[0].$languageUrlComponent.$projectUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      $printStatus = printPageviewsForMonthOrYearListAsHtmlTable($pageList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$sort,$tag);
      if (count($monthList) > 1 or count($pageList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$tag, $cleanPermalinkUrl);
      }   
      $originalMonthList = $monthList;
      $displayFormat='htmltableautomatic';
      $carryoverfromonemonth=true;
      include("inputDisplay/multiplemonthsdataentry.inc");
      break;
  }
}
?>
