<?php

## Retrieval file for the year list specification

## Corresponding data entry files (in inputdisplay directory):
## yearcheckboxlist.inc

## Only included in displayviewsformultipleyears.php

$originalyearList=array($mostrecentyear);

if (!empty($_REQUEST['year']))
  {  
    $originalyearList = array($_REQUEST['year']);
  }
elseif (!empty($_REQUEST['yearList']))
  {
    $originalyearList = $_REQUEST['yearList'];
  }

$allyears='allyears';
if (!empty($_REQUEST['allyears']))
  {
    $allyears = $_REQUEST['allyears'];
  }
elseif (!empty($_REQUEST['yearList']) or !empty($_REQUEST['year']))
  {
    $allyears = '';
  }

if ($allyears == "allyears")
  {
    $yearList = presentandpastyears_yearList();
  }
 else
   {
     $yearList = $originalyearList;
   }
if (sizeof($yearList) == 0)
  {
    include("style/head.inc");
    print "You didn't select any years. Please do so below.";
    $yearspecificationerror = true;
  }
 
?>
