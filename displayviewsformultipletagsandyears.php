<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice = "multipletagsandyears";
include("retrieval/taglistretrieval.inc");
include("retrieval/yearlistretrieval.inc");
include("retrieval/advancedoptionretrieval.inc");

if ($pagespecificationerror == true)
  {
    include("inputdisplay/".$pagetypeadvice."dataentry.inc");
  }

if ($displayformat=='htmltableautomatic') 
  {
    include("style/head.inc");
    if (count($taglist) >= count($yearlist)) 
      {
	printpageviewsformonthoryearlistashtmltable($taglist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
      }
    else 
      {
	printpageviewsformonthoryearlistashtmltabletransposed($taglist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
      }
    include("inputdisplay/multipletagsandyearsdataentry.inc");
  }

elseif ($displayformat=='htmltable') 
  { 
    include("style/head.inc"); 
    printpageviewsformonthoryearlistashtmltable($taglist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
    include("inputdisplay/multipletagsandyearsdataentry.inc");
  }

elseif ($displayformat=='htmltabletransposed') 
  {
    include("style/head.inc");
    printpageviewsformonthoryearlistashtmltabletransposed($taglist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization,'tag','year');
    include("inputdisplay/multipletagsandyearsdataentry.inc");
  }

elseif ($displayformat=='csv') 
  printpageviewsformonthoryearlistascsv($taglist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','year');

elseif ($displayformat=='csvtransposed') 
  printpageviewsformonthoryearlistascsvtransposed($taglist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','year');

elseif ($displayformat=='cpi')
  printpageviewsformonthoryearlistascpi($taglist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,'','tag','year');

?>
