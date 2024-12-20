<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/coreCode.inc");
$formdata = true;
$pageTypeAdvice = "multipletagsandmonths";
include("retrieval/languageListRetrieval.inc");
include("retrieval/drilldownListRetrieval.inc");
include("retrieval/tagListRetrieval.inc");
include("retrieval/monthListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");

if ($pageSpecificationError == true or $monthSpecificationError == true) {
  include("inputDisplay/".$pageTypeAdvice."dataentry.inc");
} else {
  switch ($displayFormat) {
    case 'htmltableautomatic' :
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$tagUrlComponent.$monthUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      if (count($tagList) * count($languageList) * count($drilldownList) >= count($monthList)) {
        $printStatus = printPageviewsForMonthOrYearListAsHtmlTable($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month',$sort);
      } else {
        $printStatus = printPageviewsForMonthOrYearListAsHtmlTableTransposed($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month',$sort);
      }
      if (count($monthList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month','',$cleanPermalinkUrl);
      }
      include("inputDisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$tagUrlComponent.$monthUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';      
      $printStatus = printPageviewsForMonthOrYearListAsHtmlTable($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month',$sort);
      if (count($monthList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month','',$cleanPermalinkUrl);
      }
      include("inputDisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'htmltabletransposed':
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$tagUrlComponent.$monthUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      $printStatus = printPageviewsForMonthOrYearListAsHtmlTableTransposed($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month',$sort);
      if (count($monthList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month','',$cleanPermalinkUrl);
      }
      include("inputDisplay/multipletagsandmonthsdataentry.inc");
      break;
  }
}
include_once('style/anchorjs.inc');
?>
