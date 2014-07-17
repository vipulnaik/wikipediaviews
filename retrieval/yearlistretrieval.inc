<?php

## Retrieval file for the year list specification

## Corresponding data entry files (in inputdisplay directory):
## yearcheckboxlist.inc

## Only included in displayviewsformultipleyears.php

$originalyearlist=array($mostrecentyear);

if (!empty($_REQUEST['year']))
  {  
    $originalyearlist = array($_REQUEST['year']);
  }
elseif (!empty($_REQUEST['yearlist']))
  {
    $originalyearlist = $_REQUEST['yearlist'];
  }

$allyears='allyears';
if (!empty($_REQUEST['allyears']))
  {
    $allyears = $_REQUEST['allyears'];
  }
elseif (!empty($_REQUEST['yearlist']) or !empty($_REQUEST['year']))
  {
    $allyears = '';
  }

if ($allyears == "allyears")
  {
    $yearlist = presentandpastyears_yearlist();
  }
 else
   {
     $yearlist = $originalyearlist;
   }
if (sizeof($yearlist) == 0)
  {
    include("style/head.inc");
    print "You didn't select any years. Please do so below.";
    $yearspecificationerror = true;
  }
 
?>
