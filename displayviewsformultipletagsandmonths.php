<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice = "multipletagsandmonths";
include("retrieval/monthlistretrieval.inc");
include("retrieval/advancedoptionretrieval.inc");

if ($displayformat=='htmltableautomatic') 
  {
    include("style/head.inc");
    if (count($pagelistasarray) >= count($monthlist)) 
      {
	printpageviewsformonthoryearlistashtmltable($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
    else 
      {
	printpageviewsformonthoryearlistashtmltabletransposed($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
      }
    include("inputdisplay/multiplemonthsdataentry.inc");
  }

elseif ($displayformat=='csv') 
  { 
    printpageviewsformonthlistascsv($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
  }

elseif ($displayformat=='htmltable') 
  { 
    include("style/head.inc"); 
    printpageviewsformonthoryearlistashtmltable($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
    include("inputdisplay/multiplemonthsdataentry.inc");
  }

elseif ($displayformat=='csvtransposed') 
  {
    printpageviewsformonthlistascsvtransposed($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
  }

elseif ($displayformat=='htmltabletransposed') 
  {
    include("style/head.inc");
    printpageviewsformonthoryearlistashtmltabletransposed($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization);
    include("inputdisplay/multiplemonthsdataentry.inc");
  }
?>
