<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice = "multiplemonths";
include("retrieval/pageListRetrieval.inc");
include("retrieval/monthListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");


if ($pagespecificationerror == true or $monthspecificationerror == true) {
  include("inputdisplay/".$pagetypeadvice."dataentry.inc");
} else {
  switch ($displayformat) {
    case 'htmltableautomatic' :
      include("style/head.inc");
      if (count($pageListAsArray) >= count($monthList)) {
        printPageviewsForMonthOrYearListAsHtmlTable($pageListAsArray,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      } else {
        printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageListAsArray,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
      if (count($monthList) > 1) {
        generateGraph($pageListAsArray,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc"); 
      printPageviewsForMonthOrYearListAsHtmlTable($pageListAsArray,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      if (count($monthList) > 1) {
        generateGraph($pageListAsArray,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltabletransposed' :
      include("style/head.inc");
      printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageListAsArray,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      if (count($monthList) > 1) {
        generateGraph($pageListAsArray,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'csv' :
      printPageviewsForMonthOrYearListAsCsv($pageListAsArray,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','month');
      break;
    case 'csvtransposed' :
      printPageviewsForMonthOrYearListAsCsvTransposed($pageListAsArray,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','month');
      break;
    case 'cpi' :
      printPageviewsForMonthOrYearListAsCpi($pageListAsArray,$monthList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','month');
      break;
  }
}
?>
