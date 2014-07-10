<?php

## Retrieval file for the month list specification

## Corresponding data entry files (in inputdisplay directory):
## alternatemonthspecificationoptions.inc, monthcheckboxlist.inc,
## monthdropdown.inc

## Only included in displayviewsformultiplemonths.php

$monthacrossyears = '';
if (!empty($_REQUEST['monthacrossyears']))
{
  $monthacrossyears = $_REQUEST['monthacrossyears'];
}

$year = '';
if (!empty($_REQUEST['year']))
{
  $year = $_REQUEST['year'];
}

$allmonths = '';
if (!empty($_REQUEST['allmonths']))
{
  $allmonths = $_REQUEST['allmonths'];
}

$originalmonthlist = array($mostrecentmonth);
if (!empty($_REQUEST['monthlist']))
{
  $originalmonthlist = $_REQUEST['monthlist'];
}

if ($allmonths == "allmonths" and in_array($thismonth,$originalmonthlist))
{
  $monthlist = presentandpastmonths_monthlist();
}
elseif ($allmonths == "allmonths")
{
  $monthlist = pastmonths_monthlist();
}
else
{
  $monthlist = $originalmonthlist;
}

if ($year != "" and $monthacrossyears != "")
{
  include(__DIR__."/../style/head.inc");
  print "You provided multiple alternate methods for selecting the set of months. Please choose only one.";
  $monthspecificationerror = true;
}

elseif ($year != "")
{
  $monthlist = pastmonthsinyear($year);
}

elseif ($monthacrossyears != "")
{
  $monthlist = monthacrossallyears($monthacrossyears);
}

if (count($monthlist) == 0)
{
  include(__DIR__."/../style/head.inc");
  print "You didn't select any months. Please do so below.";
  $monthspecificationerror = true;
}
?>
