<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice = "multiplemonths";
include("retrieval/pagelistretrieval.inc");
include("retrieval/monthlistretrieval.inc");
include("retrieval/advancedoptionretrieval.inc");


if ($pagespecificationerror == true or $monthspecificationerror == true) {
  include("inputdisplay/".$pagetypeadvice."dataentry.inc");
} else {
  switch ($displayformat) {
    case 'htmltableautomatic' :
      include("style/head.inc");
      if (count($pagelistasarray) >= count($monthlist)) {
        printpageviewsformonthoryearlistashtmltable($pagelistasarray,$monthlist,$language,$device,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      } else {
        printpageviewsformonthoryearlistashtmltabletransposed($pagelistasarray,$monthlist,$language,$device,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltable' :
      include("style/head.inc"); 
      printpageviewsformonthoryearlistashtmltable($pagelistasarray,$monthlist,$language,$device,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'htmltabletransposed' :
      include("style/head.inc");
      printpageviewsformonthoryearlistashtmltabletransposed($pagelistasarray,$monthlist,$language,$device,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'csv' :
      printpageviewsformonthoryearlistascsv($pagelistasarray,$monthlist,$language,$device,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','month');
      break;
    case 'csvtransposed' :
      printpageviewsformonthoryearlistascsvtransposed($pagelistasarray,$monthlist,$language,$device,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','month');
      break;
    case 'cpi' :
      printpageviewsformonthoryearlistascpi($pagelistasarray,$monthlist,$language,$device,$explanatoryheader,$includetotal,$numericdisplayformat,'','page','month');
      break;
  }
}
?>
