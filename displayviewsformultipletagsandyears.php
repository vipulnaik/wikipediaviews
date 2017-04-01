<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/coreCode.inc");
$formdata = true;
$pageTypeAdvice = "multipletagsandyears";
include("retrieval/languageListRetrieval.inc");
include("retrieval/drilldownListRetrieval.inc");
include("retrieval/tagListRetrieval.inc");
include("retrieval/yearListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");

if ($pageSpecificationError == true) {
    include("inputDisplay/".$pageTypeAdvice."dataentry.inc");
} else {
  switch ($displayFormat) {   
    case 'htmltableautomatic' :
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$tagUrlComponent.$yearUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      if (count($tagList) * count($languageList) * count($drilldownList) >= count($yearList)) {
	printpageviewsformonthOrYearListashtmltable($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year',$sort);
      } else {
	printpageviewsformonthOrYearListashtmltabletransposed($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year',$sort);
      }
      if (count($yearList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year');
      }
      include("inputDisplay/multipletagsandyearsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$tagUrlComponent.$yearUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      printpageviewsformonthOrYearListashtmltable($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year',$sort);
      if (count($yearList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year',$cleanPermalinkUrl);
      }
      include("inputDisplay/multipletagsandyearsdataentry.inc");
      break;
    case 'htmltabletransposed' :
      include("style/head.inc");
      $permalinkUrl = "https://wikipediaviews.org/displayviewsfor".$pageTypeAdvice.".php?".$tagUrlComponent.$yearUrlComponent.$languageUrlComponent.$drilldownUrlComponent.$advancedOptionUrlComponent;
      $cleanPermalinkUrl = str_replace("?&", "?", $permalinkUrl);
      print 'Permalink URL: <a href="'.$cleanPermalinkUrl.'">'.$cleanPermalinkUrl.'</a><br/><br/>';
      printpageviewsformonthOrYearListashtmltabletransposed($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year',$sort);
      if (count($yearList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year',$cleanPermalinkUrl);
      }
      include("inputDisplay/multipletagsandyearsdataentry.inc");
      break;
  }
}
?>
