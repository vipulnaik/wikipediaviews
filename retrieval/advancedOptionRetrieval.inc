<?php

## Retrieval file for advanced options

## Corresponding data entry file (in inputDisplay directory):
## advancedOptions.inc

## Included in all the display views files:
## displayviewsforonemonth.php, displayviewsformultiplemonths.php,
## displayviewsformultipleyears.php

$advancedOptionUrlComponent = '';
##Display format
if ($pageTypeAdvice == 'multiplemonths' or $pageTypeAdvice == 'multipleyears' or $pageTypeAdvice == 'multipletagsandmonths' or $pageTypeAdvice == 'multipletagsandyears') {
  $displayFormat = 'htmltableautomatic';
}

if ($pageTypeAdvice == 'onemonth') {
  $displayFormat = 'htmltable';
}

if (!empty($_REQUEST['displayFormat'])) {
  $displayFormat = $_REQUEST['displayFormat'];
  if (($pageTypeAdvice == 'onemonth' and $displayFormat != 'htmltable') or ($pageTypeAdvice != 'onemonth' and $displayFormat != 'htmltableautomatic')) {
    $advancedOptionUrlComponent .= '&displayFormat='.$displayFormat;
  }
}

##Query limit
$userSpecifiedQueryLimit = $attemptedExternalQueryLimit;
if (!empty($_REQUEST['userSpecifiedQueryLimit'])) {
  $userSpecifiedQueryLimit = $_REQUEST['userSpecifiedQueryLimit'];
  if ($userSpecifiedQueryLimit != $attemptedExternalQueryLimit) {
    $advancedOptionUrlComponent .= '&userSpecifiedQueryLimit='.$userSpecifiedQueryLimit;
  }
  $attemptedExternalQueryLimit = intval($userSpecifiedQueryLimit);
}

##Purge period
$userspecifiedpurgeperiod = $purgeperiod;
if (!empty($_REQUEST['userspecifiedpurgeperiod'])) {
  $userspecifiedpurgeperiod = $_REQUEST['userspecifiedpurgeperiod'];
  if ($userspecifiedpurgeperiod != $purgeperiod) {
    $advancedOptionUrlComponent .= '&userspecifiedpurgeperiod='.$userspecifiedpurgeperiod;
  }
  $purgeperiod = intval($userspecifiedpurgeperiod);
}

##Normalization
$normalization = 'none';
if (!empty($_REQUEST['normalization'])) {
  $normalization = $_REQUEST['normalization'];
  if ($normalization != 'none') {
    $advancedOptionUrlComponent .= '&normalization='.$normalization;
  }
}

##Numeric display format
$numericDisplayFormat = 'kmb';
if (!empty($_REQUEST['numericDisplayFormat'])) {
  $numericDisplayFormat = $_REQUEST['numericDisplayFormat'];
  if ($numericDisplayFormat != 'kmb') {
    $advancedOptionUrlComponent .= '&numericDisplayFormat='.$numericDisplayFormat;
  }
}

##Sort
$sort = 'desc';
if (!empty($_REQUEST['sort'])) {
  $sort = $_REQUEST['sort'];
  if ($sort != 'desc') {
    $advancedOptionUrlComponent .= '&sort='.$sort;
  }
}

?>
