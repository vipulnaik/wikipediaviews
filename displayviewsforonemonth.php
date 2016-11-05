<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice="onemonth";
include("retrieval/pagelistretrieval.inc");
include("retrieval/advancedoptionretrieval.inc");
$month = $mostrecentmonth;
if (!empty($_REQUEST['month'])) {
    $month = $_REQUEST['month'];
  }
$monthlist = array($month);

if ($pagespecificationerror == true or $monthspecificationerror == true) {
  include("inputdisplay/".$pagetypeadvice."dataentry.inc");
} else {
  switch ($displayformat) {
    case 'csv' :
      printpageviewsformonthoryearlistascsv($pagelistasarray,array($month),$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat);
      break;
    case 'htmltable' : 
      include("style/head.inc"); 
      printpageviewsformonthoryearlistashtmltable($pagelistasarray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      $originalmonthlist = $monthlist;
      $displayformat='htmltableautomatic';
      $carryoverfromonemonth=true;
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'csvtransposed' :
      printpageviewsformonthoryearlistascsvtransposed($pagelistasarray,array($month),$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat);
      break;
    case 'countsonlyseparatelines' :
      printpageviewsascountsonlyseparatelines($pagelistasarray,$month,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat);
      break;
  }
}
?>
