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
      if (count($tagList) >= count($monthlist)) {
	printpageviewsformonthoryearListashtmltable($tagList,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      } else {
	printpageviewsformonthoryearListashtmltabletransposed($tagList,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      if (count($monthlist) > 1) {
        generateGraph($tagList,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc"); 
      printpageviewsformonthoryearListashtmltable($tagList,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      if (count($monthlist) > 1) {
        generateGraph($tagList,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'htmltabletransposed':
      include("style/head.inc");
      printpageviewsformonthoryearListashtmltabletransposed($tagList,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      if (count($monthlist) > 1) {
        generateGraph($tagList,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'csv':
      printpageviewsformonthoryearListascsv($tagList,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');
      break;
    case 'csvtransposed':
      printpageviewsformonthoryearListascsvtransposed($tagList,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');
      break;
    case 'cpi':
      printpageviewsformonthoryearListascpi($tagList,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');
      break;
  }
}
?>
