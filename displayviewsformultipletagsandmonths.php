<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice = "multipletagsandmonths";
include("retrieval/tagListRetrieval.inc");
include("retrieval/monthListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");

if ($pagespecificationerror == true or $monthspecificationerror == true) {
  include("inputdisplay/".$pagetypeadvice."dataentry.inc");
} else {
  switch ($displayformat) {
    case 'htmltableautomatic' :
      include("style/head.inc");
      if (count($tagList) * count($drilldownList) >= count($monthList)) {
	printPageviewsForMonthOrYearListAsHtmlTable($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month',$sort);
      } else {
	printPageviewsForMonthOrYearListAsHtmlTableTransposed($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month',$sort);
      }
      if (count($monthList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc"); 
      printPageviewsForMonthOrYearListAsHtmlTable($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month',$sort);
      if (count($monthList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'htmltabletransposed':
      include("style/head.inc");
      printPageviewsForMonthOrYearListAsHtmlTableTransposed($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month',$sort);
      if (count($monthList) > 1 or count($tagList) * count($languageList) * count($drilldownList) > 1) {
        generateGraphs($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'csv':
      printPageviewsFormonthOrYearListAsCsv($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,'','tag','month');
      break;
    case 'csvtransposed':
      printPageviewsForMonthOrYearListAsCsvTransposed($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,'','tag','month');
      break;
    case 'cpi':
      printPageviewsForMonthOrYearListAsCpi($tagList,$languageList,$drilldownList,$monthList,$numericDisplayFormat,'','tag','month');
      break;
  }
}
?>
