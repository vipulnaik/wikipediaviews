<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice="onemonth";
include("retrieval/pageListRetrieval.inc");
include("retrieval/advancedOptionRetrieval.inc");
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
      printpageviewsformonthoryearListascsv($pageListAsArray,array($month),$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat);
      break;
    case 'htmltable' : 
      include("style/head.inc"); 
      printpageviewsformonthoryearListashtmltable($pageListAsArray,$monthlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      $originalmonthlist = $monthlist;
      $displayformat='htmltableautomatic';
      $carryoverfromonemonth=true;
      include("inputdisplay/multiplemonthsdataentry.inc");
      break;
    case 'csvtransposed' :
      printpageviewsformonthoryearListascsvtransposed($pageListAsArray,array($month),$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat);
      break;
    case 'countsonlyseparatelines' :
      printpageviewsascountsonlyseparatelines($pageListAsArray,$month,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat);
      break;
  }
}
?>
