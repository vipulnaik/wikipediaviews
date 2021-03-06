<?php

## Retrieval file for page list specification, including direct
## specification (in the text entry area) and indirect specification
## through one of the alternate methods.

## Corresponding data entry files (in inputDisplay directory):
## pageListEntry.inc, alternatepagespecificationoptions.inc

## Included in all the display views files:
## displayviewsforonemonth.php, displayviewsformultiplemonths.php,
## displayviewsformultipleyears.php

##Retrieval of language
$language='en';
if (!empty($_REQUEST['language'])) {
  $language = $_REQUEST['language'];
}

##Retrieval of page list as entered directly

$pageListAsString='';
$pageList = array();
if (!empty($_REQUEST['pageListAsString'])) {
  $pageListAsString = $_REQUEST['pageListAsString'];
}
if (!empty($_REQUEST['page'])) {
  $pageListAsString = $_REQUEST['page'];
}

$category = '';
if (!empty($_REQUEST['category'])) {
    $category = $_REQUEST['category'];
}

$continueString = '';
if (!empty($_REQUEST['continueString'])) {
    $continueString = $_REQUEST['continueString'];
}

$method = 'recursive';
if (!empty($_REQUEST['method'])) {
  $method = $_REQUEST['method'];
}


$user = '';
if (!empty($_REQUEST['user'])) {
    $user = $_REQUEST['user'];
}

$linkingPage = '';
if (!empty($_REQUEST['linkingPage'])) {
    $linkingPage = $_REQUEST['linkingPage'];
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

if (strlen(trim($pageListAsString," \t\n\r\0\x0B"))==0 and $category==='' and $user==='' and $linkingPage==='' and $archivalStatus==='' and $viewbound==0) {
    include(__DIR__."/../style/head.inc");
    print "You didn't list any pages (either directly, or via one of the alternative methods).<br>";
    $pageSpecificationError = true;
}
elseif (strlen(trim($pageListAsString," \t\n\r\0\x0B"))>0 and ($category!='' or $user != '' or $archivalStatus != '' or $viewbound > 0)) {
    include(__DIR__."/../style/head.inc");
    print "You listed page(s) directly <em>and</em> selected an alternative method to list pages. You can only use one of the two methods at a time.";
    $pageSpecificationError = true;
}

elseif (($category != '' and ($user != '' or $linkingPage != '' or $archivalStatus != '' or $viewbound > 0)) or ($user != '' and ($linkingPage != '' or $archivalStatus != '' or $viewbound > 0)) or ($linkingPage != '' and ($archivalStatus != '' or $viewbound > 0)) or ($archivalStatus != '' and $viewbound > 0)) {
    include(__DIR__."/../style/head.inc");
    print "You selected multiple alternate methods. Please modify the form below appropriately.<br>";
    $pageSpecificationError = true;
}

##Now that we're sure that the page list is specified uniquely, we convert it to an array
##named $pageList

if ($pageSpecificationError == false) {
  if (strlen(trim($pageListAsString," \t\n\r\0\x0B"))>0) {
    $pageListAsString_mod = str_replace("http://","",$pageListAsString);
    $pageListAsString_mod = str_replace("https://","",$pageListAsString_mod);
    $pageListAsString_mod = str_replace("en.wikipedia.org/wiki/","",$pageListAsString_mod);
    $pageListAsString_mod = str_replace("_"," ",$pageListAsString_mod);
    $pageList = convertPageListToArray($pageListAsString_mod);
  }
  elseif ($category!='') {
    $pageList = getPageListByWikipediaCategory($category,$language,$method,$continueString);
    if (sizeof($pageList) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the category-language <em>combination</em>.<br>";
      $pageSpecificationError = true;
    }
    sort($pageList);
  } elseif ($user!='') {
    $pageList = getPageListbyCreatingUser($user,$language);
    if (sizeof($pageList) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the user-language <em>combination</em>.<br>";
      $pageSpecificationError = true;
    }
    sort($pageList);
  } elseif ($linkingPage!='') {
    $pageList = getPageListByLinkingPage($linkingPage,$language);
    if (sizeof($pageList) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the linking page-language <em>combination</em>.<br>";
      $pageSpecificationError = true;
    }
    sort($pageList);
  } elseif ($archivalStatus!='') {
    $pageList = getPageListByArchivalStatus($archivalStatus,$language);
    if (sizeof($pageList) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the archival status-language <em>combination</em>.<br>";
      $pageSpecificationError = true;
    }
    sort($pageList);
  } elseif ($viewbound > 0) {
    if (strlen($yearfilter) == 0) {
      $pageList = getpageListbyViewBound($viewbound,$monthfilter,$language,'month');
    } else {
      $pageList = getPageListByViewBound($viewbound,$yearfilter,$language,'year');
      if (sizeof($pageList) == 0) {
        include(__DIR__."/../style/head.inc");
	print "There are no pages for the view bound-filter-language <em>combination</em>.<br>";
	$pageSpecificationError = true;
      }
    }
    sort($pageList);
  }
}
?>
