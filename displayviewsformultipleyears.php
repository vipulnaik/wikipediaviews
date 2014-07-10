<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php

include("style/toggler.inc");
print '</head>';
include_once("backend/corecode.inc");
$formdata = true;
$pagetypeadvice = "multipleyears";
include("retrieval/pagelistretrieval.inc");
include("retrieval/yearlistretrieval.inc");
include("retrieval/advancedoptionretrieval.inc");

##Clumsy hack below, needs refactoring
if ($pagespecificationerror == true or $yearspecificationerror == true)
{
   include("inputdisplay/multipleyearsdataentry.inc");
}
elseif ($displayformat=='htmltableautomatic') 
{
  include("style/head.inc");
  if (count($pagelistasarray) >= count($yearlist)) 
  {
    printpageviewsforyearlistashtmltable($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
  }
  else 
  {
    printpageviewsforyearlistashtmltabletransposed($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
  }
  include("inputdisplay/multipleyearsdataentry.inc");
}
elseif ($displayformat=='csv') 
{ 
  printpageviewsforyearlistascsv($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
}
elseif ($displayformat=='htmltable') 
{ 
  include("style/head.inc");  
  printpageviewsforyearlistashtmltable($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
  include("inputdisplay/multipleyearsdataentry.inc");
}
elseif ($displayformat=='csvtransposed') 
{
  printpageviewsforyearlistascsvtransposed($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
}
elseif ($displayformat=='htmltabletransposed') 
{
  include("style/head.inc");
  printpageviewsforyearlistashtmltabletransposed($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
  include("inputdisplay/multipleyearsdataentry.inc");
}
?>
