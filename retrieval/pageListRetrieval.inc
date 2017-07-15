<?php

## Retrieval file for page list specification, including direct
## specification (in the text entry area) and indirect specification
## through one of the alternate methods.

## Corresponding data entry files (in inputDisplay directory):
## pageListEntry.inc, alternatepagespecificationoptions.inc

## Included in all the display views files:
## displayviewsforonemonth.php, displayviewsformultiplemonths.php,
## displayviewsformultipleyears.php

##Retrieval of page list as entered directly

$pageListAsString='';
$pageList = array();
if (!empty($_REQUEST['pages'])) {
  $pageList = $_REQUEST['pages'];
  $pageListAsString = join("\n", $pageList);
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
    $pageSpecificationError = true;
}
elseif (strlen(trim($pageListAsString," \t\n\r\0\x0B"))>0 and ($tag!='' or $category!='' or $user != '' or $archivalStatus != '' or $viewbound > 0)) {
    include(__DIR__."/../style/head.inc");
    print "You listed page(s) directly <em>and</em> selected an alternative method to list pages. You can only use one of the two methods at a time.";
    $pageSpecificationError = true;
}

elseif (($tag != '' and ($category != '' or $user != '' or $linkingpage != '' or $archivalStatus != '' or $viewbound > 0)) or ($category != '' and ($user != '' or $linkingpage != '' or $archivalStatus != '' or $viewbound > 0)) or ($user != '' and ($linkingpage != '' or $archivalStatus != '' or $viewbound > 0)) or ($linkingpage != '' and ($archivalStatus != '' or $viewbound > 0)) or ($archivalStatus != '' and $viewbound > 0)) {
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
    $pageListAsString_mod = str_replace("en.m.wikipedia.org/wiki/","",$pageListAsString_mod);
    $pageListAsString_mod = str_replace("_"," ",$pageListAsString_mod);
    $pageList = convertPageListToArray($pageListAsString_mod);
  } elseif ($tag!='' and count($languageList) == 1) {
    $pageList = getPageListByTag($tag,$languageList[0]);
    $pageUrlComponent = "&tag=".urlencode($tag);
    if (sizeof($pageList) == 0) {
      include(__DIR__."/../style/head.inc");
      print "Although the tag is valid, there are no pages for the tag-language <em>combination</em>.<br>";
      $pageSpecificationError = true;
    }
  } elseif ($tag!='' and count($languageList) > 1) {
    include(__DIR__."/../style/head.inc");
    print "We do not support multiple pages view for a single tag and multiple languages";
    $pageSpecificationError = true;
  } elseif ($category!='' and count($languageList) == 1) {
    $pageList = getPageListByWikipediaCategory($category,$languageList[0]);
    $pageUrlComponent = "&category=".$urlencode(category);
    if (sizeof($pageList) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the category-language <em>combination</em>.<br>";
      $pageSpecificationError = true;
    }
    sort($pageList);
  } elseif ($user!='' and count($languageList) == 1) {
    $pageList = getPageListByCreatingUser($user,$languageList[0]);
    $pageUrlComponent = "&user=".urlencode($user);
    if (sizeof($pageList) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the user-language <em>combination</em>.<br>";
      $pageSpecificationError = true;
    }
    sort($pageList);
  } elseif ($linkingpage!='' and count($languageList) == 1) {
    $pageList = getPageListByLinkingPage($linkingpage,$languageList[0]);
    $pageUrlComponent = "&linkingpage=".$linkingpage;
    if (sizeof($pageList) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the linking page-language <em>combination</em>.<br>";
      $pageSpecificationError = true;
    }
    sort($pageList);
  } elseif ($archivalStatus!='') {
    $pageList = getPageListByArchivalStatus($archivalStatus,$language);
    $pageUrlComponent = "&archivalStatus=".$archivalStatus;
    if (sizeof($pageList) == 0) {
      include(__DIR__."/../style/head.inc");
      print "There are no pages for the archival status-language <em>combination</em>.<br>";
      $pageSpecificationError = true;
    }
    sort($pageList);
  } elseif ($viewbound > 0) {
    if (strlen($yearfilter) == 0) {
      $pageList = getPageListByViewBound($viewbound,$monthfilter,$language,'month');
      $pageUrlComponent = "&viewbound=".$viewbound;
    } else {
      $pageList = getPageListByViewBound($viewbound,$yearfilter,$language,'year');
      # Need to add pageUrlComponent
      if (sizeof($pageList) == 0) {
        include(__DIR__."/../style/head.inc");
	print "There are no pages for the view bound-filter-language <em>combination</em>.<br>";
	$pageSpecificationError = true;
      }
      sort($pageList);
    }
  }
}
$pageList = array_map("ucfirst", $pageList);
if ($tag == '' and $category == '' and $user == '' and $linkingpage == '' and $archivalStatus == '' and $viewbound == 0) {
  if (count($pageList) == 1) {
    $pageUrlComponent = "&page=".urlencode($pageList[0]);
  } else {
    $pageUrlComponent = "";
    for ($i = 0; $i < count($pageList); $i++) {
      $pageUrlComponent .= "&pages[$i]=".urlencode($pageList[$i]);
    }
  }
}

?>
