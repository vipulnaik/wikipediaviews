<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<meta name="robots" content="noindex">
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/coreCode.inc");
$formdata = true;
$pageTypeAdvice = "multipleyears";
include("retrieval/languageListRetrieval.inc");
include("retrieval/drilldownListRetrieval.inc");
include("retrieval/pageListRetrieval.inc");
include("retrieval/yearListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");

##Clumsy hack below, needs refactoring
if ($pageSpecificationError == true or $yearSpecificationError == true) {
    include("inputDisplay/multipleyearsdataentry.inc");
} else {
  switch ($displayFormat) {
    case 'htmltableautomatic' :
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent.$yearUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';   
      if (count($pageList) * count($languageList) * count($drilldownList) >= count($yearList)) {
	printPageviewsForMonthOrYearListAsHtmlTable($pageList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'page','year',$sort);
      } else {
	printPageviewsFormonthOrYearListAsHtmlTableTransposed($pageList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'page','year',$sort);
      }
      if (count($yearList) > 1 or count($pageList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'page','year',$cleanPermalinkUrl);
      }
      include("inputDisplay/multipleyearsdataentry.inc");
      break;
    case 'htmltable':
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent.$yearUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';   
      printPageviewsForMonthOrYearListAsHtmlTable($pageList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'page','year',$sort);
      if (count($yearList) > 1 or count($pageList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'page','year',$cleanPermalinkUrl);
      }
      include("inputDisplay/multipleyearsdataentry.inc");
      break;
    case 'htmltabletransposed':
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$pageUrlComponent.$yearUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';   
      printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'page','year',$sort);
      if (count($yearList) > 1 or count($pageList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($pageList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'page','year',$cleanPermalinkUrl);
      }
      include("inputDisplay/multipleyearsdataentry.inc");
      break;
  }
}
?>
