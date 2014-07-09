<?php
        $year = '';
        $monthacrossyears = '';
        if (!empty($_REQUEST['monthacrossyears']))
        {$monthacrossyears = $_REQUEST['monthacrossyears'];}
	if (!empty($_REQUEST['allmonths']) or !empty($_REQUEST['monthlist']))
	{$originalmonthlist = $_REQUEST['monthlist'];}
        if (!empty($_REQUEST['allmonths']) or !empty($_REQUEST['monthlist']))
        {$allmonths = $_REQUEST['allmonths'];}
        if (!empty($_REQUEST['year']))
        {$year = $_REQUEST['year'];}
        if ($allmonths == "allmonths" and in_array($thismonth,$originalmonthlist))
        {
            $monthlist = presentandpastmonths_monthlist();
        }
        else if ($allmonths == "allmonths")
        {
            $monthlist = pastmonths_monthlist();
        }
        else
        {
          $monthlist = $originalmonthlist;
        }

        if ($year != "" and $monthacrossyears != "")
        {
              include("head.inc");
              print "You provided multiple alternate methods for selecting the set of months. Please choose only one.";
              include(__DIR__."/../inputdisplay/multiplemonthsdataentry.inc");
              exit;
        }

        if ($year != "")
        {
           $monthlist = pastmonthsinyear($year);
        }
        if ($monthacrossyears != "")
        {
           $monthlist = monthacrossallyears($monthacrossyears);
        }
        if (sizeof($monthlist) == 0)
        {
              include("head.inc");
              print "You didn't select any months. Please do so below.";
              include(__DIR__."/../inputdisplay/multiplemonthsdataentry.inc");
              exit;
        }
?>