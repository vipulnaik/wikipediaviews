<?php

## Retrieval file for page list specification, including direct
## specification (in the text entry area) and indirect specification
## through one of the alternate methods.

## Corresponding data entry files (in inputdisplay directory):
## pagelistentry.inc, alternatepagespecificationoptions.inc

## Included in all the display views files:
## displayviewsforonemonth.php, displayviewsformultiplemonths.php,
## displayviewsformultipleyears.php

## Retrieval of language
$languageList = array("en");
if (!empty($_REQUEST['languages'])) {
  $languageList = $_REQUEST['languages'];
}
if (!empty($_REQUEST['languageList'])) {
  $languageList = $_REQUEST['languageList'];
}
if (!empty($_REQUEST['language'])) {
  $sentLanguage = $_REQUEST['language'];
  $languageList = array($sentLanguage);
}


## Retrieval of drilldown
$drilldownList = array("desktop");
if (!empty($_REQUEST['drilldowns'])) {
  $drilldownList = $_REQUEST['drilldowns'];
}
if (!empty($_REQUEST['drilldownList'])) {
  $drilldownList = $_REQUEST['drilldownList'];
}
if (!empty($_REQUEST['drilldown'])) {
  $sentDrilldown = $_REQUEST['drilldown'];
  if ($sentDrilldown == "all") {
    $drilldownList = array("desktop", "mobile-web", "mobile-app", "desktop-spider", "mobile-web-spider");
  } else {
    $drilldownList = array($sentDrilldown);
  }
}


##Retrieval of page list as entered directly

$pageListAsString='';
$pageListAsArray = array();
if (!empty($_REQUEST['pages'])) {
  $pageListAsArray = $_REQUEST['pages'];
}

if (!empty($_REQUEST['pageListAsString'])) {
  $pageListAsString = $_REQUEST['pageListAsString'];
}
if (!empty($_REQUEST['page'])) {
  $pageListAsString = $_REQUEST['page'];
}

##Retrieval of alternate page specification formats
$tag = '';
if (!empty($_REQUEST['tag'])) {
    $tag = $_REQUEST['tag'];
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

$archivalStatus = '';
if (!empty($_REQUEST['archivalStatus'])) {
    $archivalStatus = $_REQUEST['archivalStatus'];
}

$viewbound = 0;
if (!empty($_REQUEST['viewbound'])) {
    $viewbound = intval($_REQUEST['viewbound']);
}

$monthfilter = $thisMonth;
if (!empty($_REQUEST['monthfilter'])) {
    $monthfilter = $_REQUEST['monthfilter'];
}

$yearfilter = '';
if (!empty($_REQUEST['yearfilter'])) {
    $yearfilter = $_REQUEST['yearfilter'];
}


##Figuring out if the page list has been specified in multiple
##ways, or not at all, and displaying the appropriate error message.

if (strlen(trim($pageListAsString," \t\n\r\0\x0B"))==0 and $tag==='' and $category==='' and $user==='' and $linkingpage==='' and $archivalStatus==='' and $viewbound==0 and empty($_REQUEST['pages'])) {
    include(__DIR__."/../style/head.inc");
    print "You didn't list any pages (either directly, or via one of the alternative methods).<br>";
    $pagespecificationerror = true;
}
elseif (strlen(trim($pageListAsString," \t\n\r\0\x0B"))>0 and ($tag!='' or $category!='' or $user != '' or $archivalStatus != '' or $viewbound > 0)) {
    include(__DIR__."/../style/head.inc");
    print "You listed page(s) directly <em>and</em> selected an alternative method to list pages. You can only use one of the two methods at a time.";
    $pagespecificationerror = true;
}

elseif (($tag != '' and ($category != '' or $user != '' or $linkingpage != '' or $archivalStatus != '' or $viewbound > 0)) or ($category != '' and ($user != '' or $linkingpage != '' or $archivalStatus != '' or $viewbound > 0)) or ($user != '' and ($linkingpage != '' or $archivalStatus != '' or $viewbound > 0)) or ($linkingpage != '' and ($archivalStatus != '' or $viewbound > 0)) or ($archivalStatus != '' and $viewbound > 0)) {
    include(__DIR__."/../style/head.inc");
    print "You selected multiple alternate methods. Please modify the form below appropriately.<br>";
    $pagespecificationerror = true;
}

##Now that we're sure that the page list is specified uniquely, we convert it to an array
##named $pageListAsArray

if ($pagespecificationerror == false) {
  if (strlen(trim($pageListAsString," \t\n\r\0\x0B"))>0) {
    $pageListAsString_mod = str_replace("http://","",$pageListAsString);
    $pageListAsString_mod = str_replace("https://","",$pageListAsString_mod);
    $pageListAsString_mod = str_replace("en.wikipedia.org/wiki/","",$pageListAsString_mod);
    $pageListAsString_mod = str_replace("_"," ",$pageListAsString_mod);
    $pageListAsArray = convertPageListToArray($pageListAsString_mod);
  } elseif ($tag!='' and count($languageList) == 1) {
    $pageListAsArray = getPageListByTag($tag,$languageList[0]);
    if (sizeof($pageListAsArray) == 0) {
      include(__DIR__."/../style/head.inc");
      print "Although the tag is valid, there are no pages for the tag-language <em>combination</em>.<br>";
      $pagespecificationerror = true;
    }
  } elseif ($tag!='' and count($languageList) > 1) {
    include(__DIR__."/../style/head.inc");
    print "We do not support multiple pages view for a single tag and multiple languages";
    $pagespecificationerror = true;
  } elseif ($category!='') {
    $pageListAsArray = getPageListByWikipediaCategory($category,$language);
    if (sizeof($pageListAsArray) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the category-language <em>combination</em>.<br>";
      $pagespecificationerror = true;
    }
    sort($pageListAsArray);
  } elseif ($user!='') {
    $pageListAsArray = getPageListByCreatingUser($user,$language);
    if (sizeof($pageListAsArray) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the user-language <em>combination</em>.<br>";
      $pagespecificationerror = true;
    }
    sort($pageListAsArray);
  } elseif ($linkingpage!='') {
    $pageListAsArray = getPageListByLinkingPage($linkingpage,$language);
    if (sizeof($pageListAsArray) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the linking page-language <em>combination</em>.<br>";
      $pagespecificationerror = true;
    }
    sort($pageListAsArray);
  } elseif ($archivalStatus!='') {
    $pageListAsArray = getPageListByArchivalStatus($archivalStatus,$language);
    if (sizeof($pageListAsArray) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the archival status-language <em>combination</em>.<br>";
      $pagespecificationerror = true;
    }
    sort($pageListAsArray);
  } elseif ($viewbound > 0) {
    if (strlen($yearfilter) == 0) {
      $pageListAsArray = getPageListByViewBound($viewbound,$monthfilter,$language,'month');
    } else {
      $pageListAsArray = getPageListByViewBound($viewbound,$yearfilter,$language,'year');
      if (sizeof($pageListAsArray) == 0) {
        include(__DIR__."/../style/head.inc");
	print "There are no pages for the view bound-filter-language <em>combination</em>.<br>";
	$pagespecificationerror = true;
      }
      sort($pageListAsArray);
    }
  }
}
$pageListAsArray = array_map("ucfirst", $pageListAsArray);
?>
