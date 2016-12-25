<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/coreCode.inc");
$formdata = true;
$pageTypeAdvice = "multiplemonths";
include("retrieval/languageListRetrieval.inc");
include("retrieval/drilldownListRetrieval.inc");
include("retrieval/pageListRetrieval.inc");
include("retrieval/monthListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");


if ($pageSpecificationError == true or $monthspecificationerror == true) {
   include("inputdisplay/".$pageTypeAdvice."dataentry.inc");
} else {
  switch ($displayFormat) {
    case 'htmltableautomatic' :
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent.$monthUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      if (count($pageList) * count($languageList) * count($drilldownList) >= count($monthList)) {
        $printStatus = printPageviewsForMonthOrYearListAsHtmlTable($pageList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$sort);
      } else {
        $printStatus = printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$sort);
      }
      if (count($monthList) > 1 or count($pageList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent.$monthUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      $printStatus = printPageviewsForMonthOrYearListAsHtmlTable($pageList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$sort);
      if (count($monthList) > 1 or count($pageList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltabletransposed' :
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent.$monthUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      $printStatus = printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'page','month',$sort);
      if (count($monthList) > 1 or count($pageList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
  }
}
?>
