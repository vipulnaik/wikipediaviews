<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pageTypeAdvice = "multipletagsandyears";
include("retrieval/tagListRetrieval.inc");
include("retrieval/yearListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");

if ($pageSpecificationError == true) {
    include("inputdisplay/".$pageTypeAdvice."dataentry.inc");
} else {
  switch ($displayformat) {   
    case 'htmltableautomatic' :
      include("style/head.inc");
      if (count($tagList) >= count($yearList)) {
	printpageviewsformonthOrYearListashtmltable($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year',$sort);
      } else {
	printpageviewsformonthOrYearListashtmltabletransposed($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year',$sort);
      }
      if (count($yearList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year');
      }
      include("inputdisplay/multipletagsandyearsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc"); 
      printpageviewsformonthOrYearListashtmltable($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year',$sort);
      if (count($yearList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year');
      }
      include("inputdisplay/multipletagsandyearsdataentry.inc");
      break;
    case 'htmltabletransposed' :
      include("style/head.inc");
      printpageviewsformonthOrYearListashtmltabletransposed($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year',$sort);
      if (count($yearList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,$normalization,'tag','year');
      }
      include("inputdisplay/multipletagsandyearsdataentry.inc");
      break;
    case 'csv' :
      printpageviewsformonthOrYearListascsv($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,'','tag','year');
      break;
    case 'csvtransposed' :
      printpageviewsformonthOrYearListascsvtransposed($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,'','tag','year');
      break;
    case 'cpi' :
      printpageviewsformonthOrYearListascpi($tagList,$languageList,$drilldownList,$yearList,$numericDisplayFormat,'','tag','year');
      break;
  }
}
?>
