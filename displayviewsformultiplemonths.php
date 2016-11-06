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
      if (count($pageListAsArray) >= count($monthlist)) {
        printpageviewsformonthoryearListashtmltable($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      } else {
        printpageviewsformonthoryearListashtmltabletransposed($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
      if (count($monthlist) > 1) {
        generateGraph($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc"); 
      printpageviewsformonthoryearListashtmltable($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      if (count($monthlist) > 1) {
        generateGraph($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltabletransposed' :
      include("style/head.inc");
      printpageviewsformonthoryearListashtmltabletransposed($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      if (count($monthlist) > 1) {
        generateGraph($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'csv' :
      printpageviewsformonthoryearListascsv($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','month');
      break;
    case 'csvtransposed' :
      printpageviewsformonthoryearListascsvtransposed($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','month');
      break;
    case 'cpi' :
      printpageviewsformonthoryearListascpi($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','month');
      break;
  }
}
?>
