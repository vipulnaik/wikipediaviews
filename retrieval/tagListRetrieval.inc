<?php

## Retrieval file for the month list specification

## Corresponding data entry files (in inputdisplay directory):
## tagDropdownSelectMultiple.inc

## Only included in displayviewsformultipletagsandmonths.php

$tagList = array();
if (!empty($_REQUEST['tagList'])) {
  $tagList = $_REQUEST['tagList'];
} elseif (!empty($_REQUEST['tag'])) {
  $tagList = array($_REQUEST['tag']);
} elseif (!empty($_REQUEST['tags'])) {
  $tagList = $_REQUEST['tags'];
}

if (count($tagList) == 1) {
  $tagUrlComponent = "&tag=".urlencode($tagList[0]);
} else {
  $tagUrlComponent = "";
  for ($i = 0; $i < count($tagList); $i++) {
    $tagUrlComponent .= "&tags[$i]=".urlencode($tagList[$i]);
  }
}

if (count($tagList) == 0) {
  include(__DIR__."/../style/head.inc");
  print "You didn't select any tags. Please do so below.";
  $pageSpecificationError = true;
}
?>
