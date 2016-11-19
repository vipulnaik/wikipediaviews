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
      if (count($pageListAsArray) * count($drilldownList) >= count($monthList)) {
        printPageviewsForMonthOrYearListAsHtmlTable($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      } else {
        printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      }
      if (count($monthList) > 1) {
        generateGraphs($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc"); 
      printPageviewsForMonthOrYearListAsHtmlTable($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      if (count($monthList) > 1) {
        generateGraphs($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltabletransposed' :
      include("style/head.inc");
      printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageListAsArray,$languageList,$drilldownList,$monthList,$numericDisplayFormat,$normalization);
      if (count($monthList) > 1) {
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
