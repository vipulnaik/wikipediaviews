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

if ($pagespecificationerror == true or $monthspecificationerror == true)
  {
    include("inputdisplay/".$pagetypeadvice."dataentry.inc");
  }

if ($displayformat=='htmltableautomatic') 
  {
    include("style/head.inc");
    if (count($taglist) >= count($monthlist)) 
      {
	printpageviewsformonthoryearlistashtmltable($taglist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
    else 
      {
	printpageviewsformonthoryearlistashtmltabletransposed($taglist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
      }
    include("inputdisplay/multipletagsandmonthsdataentry.inc");
  }

elseif ($displayformat=='htmltable') 
  { 
    include("style/head.inc"); 
    printpageviewsformonthoryearlistashtmltable($taglist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
    include("inputdisplay/multipletagsandmonthsdataentry.inc");
  }

elseif ($displayformat=='htmltabletransposed') 
  {
    include("style/head.inc");
    printpageviewsformonthoryearlistashtmltabletransposed($taglist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','month');
    include("inputdisplay/multipletagsandmonthsdataentry.inc");
  }

elseif ($displayformat=='csv') 
  printpageviewsformonthoryearlistascsv($taglist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');

elseif ($displayformat=='csvtransposed') 
  printpageviewsformonthoryearlistascsvtransposed($taglist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');

elseif ($displayformat=='cpi')
    printpageviewsformonthoryearlistascpi($taglist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','month');

?>
