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
if (!empty($_REQUEST['month']))
  {
    $month = $_REQUEST['month'];
  }
$monthlist = array($month);

if ($pagespecificationerror == true or $monthspecificationerror == true)
  {
    include("inputdisplay/".$pagetypeadvice."dataentry.inc");
  }

elseif ($displayformat=='csv') 
  { 
    printpageviewsascsv($pagelistasarray,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
  }
elseif ($displayformat=='htmltable') 

  {         
    include("style/head.inc"); 
    printpageviewsformonthoryearlistashtmltable($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
    $originalmonthlist = $monthlist;
    $displayformat='htmltableautomatic';
    $carryoverfromonemonth=true;
    include("inputdisplay/multiplemonthsdataentry.inc");
  }

elseif ($displayformat=='countsonlycsv') 
  {
    printpageviewsascountsonlycsv($pagelistasarray,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
  }

elseif ($displayformat=='countsonlyseparatelines') 
  {
    printpageviewsascountsonlyseparatelines($pagelistasarray,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
  }
?>
