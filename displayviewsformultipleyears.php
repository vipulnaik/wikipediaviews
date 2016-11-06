<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice = "multipleyears";
include("retrieval/pageListRetrieval.inc");
include("retrieval/yearListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");

##Clumsy hack below, needs refactoring
if ($pagespecificationerror == true or $yearspecificationerror == true) {
    include("inputdisplay/multipleyearsdataentry.inc");
} else {
  switch ($displayformat) {
    case 'htmltableautomatic' :
      include("style/head.inc");
      if (count($pageListAsArray) >= count($yearList)) {
	printpageviewsformonthoryearListashtmltable($pageListAsArray,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'page','year');
      } else {
	printpageviewsformonthoryearListashtmltabletransposed($pageListAsArray,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'page','year');
      }
      if (count($yearList) > 1) {
        generateGraph($pageListAsArray,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'page','year');
      }
      include("inputdisplay/multipleyearsdataentry.inc");
      break;
    case 'htmltable':
      include("style/head.inc");  
      printpageviewsformonthoryearListashtmltable($pageListAsArray,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'page','year');
      if (count($yearList) > 1) {
        generateGraph($pageListAsArray,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'page','year');
      }
      include("inputdisplay/multipleyearsdataentry.inc");
      break;
    case 'htmltabletransposed':
      include("style/head.inc");
      printpageviewsformonthoryearListashtmltabletransposed($pageListAsArray,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'page','year');
      if (count($yearList) > 1) {
        generateGraph($pageListAsArray,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'page','year');
      }
      include("inputdisplay/multipleyearsdataentry.inc");
      break;
    case 'csv':
      printpageviewsformonthoryearListascsv($pageListAsArray,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','year');
      break;
    case 'csvtransposed':
      printpageviewsformonthoryearListascsvtransposed($pageListAsArray,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','year');
      break;
    case 'cpi':
      printpageviewsformonthoryearListascpi($pageListAsArray,$yearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','year');
      break;
  }
}
?>
