<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice = "multipletagsandmonths";
include("retrieval/taglistretrieval.inc");
include("retrieval/monthlistretrieval.inc");
include("retrieval/advancedoptionretrieval.inc");

if ($pagespecificationerror == true or $monthspecificationerror == true) {
  include("inputdisplay/".$pagetypeadvice."dataentry.inc");
} else {
  switch ($displayformat) {
    case 'htmltableautomatic' :
      include("style/head.inc");
      if (count($taglist) >= count($monthlist)) {
	printpageviewsformonthoryearlistashtmltable($taglist,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      } else {
	printpageviewsformonthoryearlistashtmltabletransposed($taglist,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      if (count($monthlist) > 1) {
        generateGraph($taglist,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc"); 
      printpageviewsformonthoryearlistashtmltable($taglist,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      if (count($monthlist) > 1) {
        generateGraph($taglist,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'htmltabletransposed':
      include("style/head.inc");
      printpageviewsformonthoryearlistashtmltabletransposed($taglist,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      if (count($monthlist) > 1) {
        generateGraph($taglist,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
      include("inputdisplay/multipletagsandmonthsdataentry.inc");
      break;
    case 'csv':
      printpageviewsformonthoryearlistascsv($taglist,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');
      break;
    case 'csvtransposed':
      printpageviewsformonthoryearlistascsvtransposed($taglist,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');
      break;
    case 'cpi':
      printpageviewsformonthoryearlistascpi($taglist,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');
      break;
  }
}
?>
