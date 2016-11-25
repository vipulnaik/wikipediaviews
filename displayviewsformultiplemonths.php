<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pageTypeAdvice = "multiplemonths";
include("retrieval/pageListRetrieval.inc");
include("retrieval/monthListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");


if ($pageSpecificationError == true or $monthspecificationerror == true) {
   include("inputdisplay/".$pageTypeAdvice."dataentry.inc");
} else {
  switch ($displayformat) {
    case 'htmltableautomatic' :
      include("style/head.inc");
      $permalinkUrl = "http://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent.$monthUrlComponent.$languageUrlComponent.$drilldownUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      if (count($pageListAsArray) * count($languageList) * count($drilldownList) >= count($monthList)) {
        $printStatus = printPageviewsForMonthOrYearListAsHtmlTable($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$sort);
      } else {
        $printStatus = printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$sort);
      }
      if (count($monthList) > 1 or count($pageListAsArray) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc");
      $permalinkUrl = "http://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent.$monthUrlComponent.$languageUrlComponent.$drilldownUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      $printStatus = printPageviewsForMonthOrYearListAsHtmlTable($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$sort);
      if (count($monthList) > 1 or count($pageListAsArray) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltabletransposed' :
      include("style/head.inc");
      $permalinkUrl = "http://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent.$monthUrlComponent.$languageUrlComponent.$drilldownUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      $printStatus = printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$sort);
      if (count($monthList) > 1 or count($pageListAsArray) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'csv' :
      printPageviewsForMonthOrYearListAsCsv($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,'','page','month');
      break;
    case 'csvtransposed' :
      printPageviewsForMonthOrYearListAsCsvTransposed($pageListAsArray,$monthList,$language,$drilldownList,$numericDisplayFormat,'','page','month');
      break;
    case 'cpi' :
      printPageviewsForMonthOrYearListAsCpi($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,'','page','month');
      break;
  }
}
?>
