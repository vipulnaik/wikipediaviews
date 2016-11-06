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
      if (count($tagList) >= count($monthList)) {
	printPageviewsForMonthOrYearListAsHtmlTable($tagList,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      } else {
	printPageviewsForMonthOrYearListAsHtmlTableTransposed($tagList,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      if (count($monthList) > 1) {
        generateGraph($tagList,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc"); 
      printPageviewsForMonthOrYearListAsHtmlTable($tagList,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      if (count($monthList) > 1) {
        generateGraph($tagList,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'htmltabletransposed':
      include("style/head.inc");
      printPageviewsForMonthOrYearListAsHtmlTableTransposed($tagList,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      if (count($monthList) > 1) {
        generateGraph($tagList,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'csv':
      printPageviewsFormonthOrYearListAsCsv($tagList,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');
      break;
    case 'csvtransposed':
      printPageviewsForMonthOrYearListAsCsvTransposed($tagList,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');
      break;
    case 'cpi':
      printPageviewsForMonthOrYearListAsCpi($tagList,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');
      break;
  }
}
?>
