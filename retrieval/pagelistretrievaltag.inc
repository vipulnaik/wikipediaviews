<?php

## Retrieval file for page list specification, including direct
## specification (in the text entry area) and indirect specification
## through one of the alternate methods.

## Corresponding data entry files (in inputdisplay directory):
## pagelistentry.inc, alternatepagespecificationoptions.inc

## Included in all the display views files:
## displayviewsforonemonth.php, displayviewsformultiplemonths.php,
## displayviewsformultipleyears.php

##Retrieval of language
$language='en';
if (!empty($_REQUEST['language'])) {
  $language = $_REQUEST['language'];
}

## Retrieval of device
$device='desktop';
if (!empty($_REQUEST['device'])) {
  $device = $_REQUEST['device'];
}


##Retrieval of page list as entered directly

$pagelistasstring='';
$pagelistasarray = array();
if (!empty($_REQUEST['pagelistasstring'])) {
    $pagelistasstring = $_REQUEST['pagelistasstring'];
}
if (!empty($_REQUEST['page'])) {
    $pagelistasstring = $_REQUEST['page'];
}

$category = '';
if (!empty($_REQUEST['category'])) {
    $category = $_REQUEST['category'];
}

$user = '';
if (!empty($_REQUEST['user'])) {
    $user = $_REQUEST['user'];
}

$linkingpage = '';
if (!empty($_REQUEST['linkingpage'])) {
    $linkingpage = $_REQUEST['linkingpage'];
}

$archivalstatus = '';
if (!empty($_REQUEST['archivalstatus'])) {
    $archivalstatus = $_REQUEST['archivalstatus'];
}

$viewbound = 0;
if (!empty($_REQUEST['viewbound'])) {
    $viewbound = intval($_REQUEST['viewbound']);
}

$monthfilter = $thismonth;
if (!empty($_REQUEST['monthfilter'])) {
    $monthfilter = $_REQUEST['monthfilter'];
}

$yearfilter = '';
if (!empty($_REQUEST['yearfilter'])) {
    $yearfilter = $_REQUEST['yearfilter'];
}


##Figuring out if the page list has been specified in multiple
##ways, or not at all, and displaying the appropriate error message.

if (strlen(trim($pagelistasstring," \t\n\r\0\x0B"))==0 and $category==='' and $user==='' and $linkingpage==='' and $archivalstatus==='' and $viewbound==0) {
    include(__DIR__."/../style/head.inc");
    print "You didn't list any pages (either directly, or via one of the alternative methods).<br>";
    $pagespecificationerror = true;
}
elseif (strlen(trim($pagelistasstring," \t\n\r\0\x0B"))>0 and ($category!='' or $user != '' or $archivalstatus != '' or $viewbound > 0)) {
    include(__DIR__."/../style/head.inc");
    print "You listed page(s) directly <em>and</em> selected an alternative method to list pages. You can only use one of the two methods at a time.";
    $pagespecificationerror = true;
}

elseif ((($category != '' and ($user != '' or $linkingpage != '' or $archivalstatus != '' or $viewbound > 0)) or ($user != '' and ($linkingpage != '' or $archivalstatus != '' or $viewbound > 0)) or ($linkingpage != '' and ($archivalstatus != '' or $viewbound > 0)) or ($archivalstatus != '' and $viewbound > 0)) {
    include(__DIR__."/../style/head.inc");
    print "You selected multiple alternate methods. Please modify the form below appropriately.<br>";
    $pagespecificationerror = true;
}

##Now that we're sure that the page list is specified uniquely, we convert it to an array
##named $pagelistasarray

if ($pagespecificationerror == false) {
    if (strlen(trim($pagelistasstring," \t\n\r\0\x0B"))>0)
      {
	$pagelistasstring_mod = str_replace("http://","",$pagelistasstring);
	$pagelistasstring_mod = str_replace("https://","",$pagelistasstring_mod);
	$pagelistasstring_mod = str_replace("en.wikipedia.org/wiki/","",$pagelistasstring_mod);
	$pagelistasstring_mod = str_replace("_"," ",$pagelistasstring_mod);
	$pagelistasarray = convertpagelisttoarray($pagelistasstring_mod);
      }
    elseif ($category!='')
      {
	$pagelistasarray = getpagelistbywikipediacategory($category,$language);
    if (sizeof($pagelistasarray) == 0)
      {
	include(__DIR__."/../style/head.inc");
	print "There are no pages for the category-language <em>combination</em>.<br>";
	$pagespecificationerror = true;
      }
    sort($pagelistasarray);
      }
    elseif ($user!='')
      {
	$pagelistasarray = getpagelistbycreatinguser($user,$language);
	if (sizeof($pagelistasarray) == 0)
	  {
	    include(__DIR__."/../style/head.inc");
	    print "There are no pages for the user-language <em>combination</em>.<br>";
	    $pagespecificationerror = true;
	  }
	sort($pagelistasarray);
      }
    elseif ($linkingpage!='')
      {
	$pagelistasarray = getpagelistbylinkingpage($linkingpage,$language);
    if (sizeof($pagelistasarray) == 0)
      {
	include(__DIR__."/../style/head.inc");
	print "There are no pages for the linking page-language <em>combination</em>.<br>";
	$pagespecificationerror = true;
      }
    sort($pagelistasarray);
      }
    elseif ($archivalstatus!='')
      {
	$pagelistasarray = getpagelistbyarchivalstatus($archivalstatus,$language);
	if (sizeof($pagelistasarray) == 0)
	  {
	    include(__DIR__."/../style/head.inc");
	    print "There are no pages for the archival status-language <em>combination</em>.<br>";
	    $pagespecificationerror = true;
	  }
	sort($pagelistasarray);
      } 
    elseif ($viewbound > 0)
      {
	if (strlen($yearfilter) == 0)
	  $pagelistasarray = getpagelistbyviewbound($viewbound,$monthfilter,$language,'month');
	else
	  $pagelistasarray = getpagelistbyviewbound($viewbound,$yearfilter,$language,'year');
	if (sizeof($pagelistasarray) == 0)
	  {
	    include(__DIR__."/../style/head.inc");
	    print "There are no pages for the view bound-filter-language <em>combination</em>.<br>";
	    $pagespecificationerror = true;
	  }
	sort($pagelistasarray);
      }
}
?>
