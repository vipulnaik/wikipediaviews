<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice = "multipletagsandyears";
include("retrieval/tagListRetrieval.inc");
include("retrieval/yearListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");

if ($pagespecificationerror == true) {
    include("inputdisplay/".$pagetypeadvice."dataentry.inc");
} else {
  switch ($displayformat) {   
    case 'htmltableautomatic' :
      include("style/head.inc");
      if (count($tagList) >= count($yearList)) {
	printpageviewsformonthoryearListashtmltable($tagList,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
      } else {
	printpageviewsformonthoryearListashtmltabletransposed($tagList,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
      }
      if (count($yearList) > 1) {
        generateGraph($tagList,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
      }
      include("inputdisplay/multipletagsandyearsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc"); 
      printpageviewsformonthoryearListashtmltable($tagList,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
      if (count($yearList) > 1) {
        generateGraph($tagList,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
      }
      include("inputdisplay/multipletagsandyearsdataentry.inc");
      break;
    case 'htmltabletransposed' :
      include("style/head.inc");
      printpageviewsformonthoryearListashtmltabletransposed($tagList,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
      if (count($yearList) > 1) {
        generateGraph($tagList,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
      }
      include("inputdisplay/multipletagsandyearsdataentry.inc");
      break;
    case 'csv' :
      printpageviewsformonthoryearListascsv($tagList,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','year');
      break;
    case 'csvtransposed' :
      printpageviewsformonthoryearListascsvtransposed($tagList,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','year');
      break;
    case 'cpi' :
      printpageviewsformonthoryearListascpi($tagList,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','year');
      break;
  }
}
?>
