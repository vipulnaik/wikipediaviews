<?php

## Retrieval file for advanced options

## Corresponding data entry file (in inputdisplay directory):
## advancedoptions.inc

## Included in all the display views files:
## displayviewsforonemonth.php, displayviewsformultiplemonths.php,
## displayviewsformultipleyears.php

##Display format
if ($pagetypeadvice == 'multiplemonths' or $pagetypeadvice == 'multipleyears' or $pagetypeadvice == 'multipletagsandmonths' or $pagetypeadvice == 'multipletagsandyears')
  {
    $displayformat = 'htmltableautomatic';
  }

if ($pagetypeadvice == 'onemonth')
  {
    $displayformat = 'htmltable';
  }

if (!empty($_REQUEST['displayformat']))
  {
    $displayformat = $_REQUEST['displayformat'];
  }

##Query limit
$userSpecifiedQueryLimit = $attemptedExternalQueryLimit;
if (!empty($_REQUEST['userSpecifiedQueryLimit'])) {
  $userSpecifiedQueryLimit = $_REQUEST['userSpecifiedQueryLimit'];
  $attemptedExternalQueryLimit = intval($userSpecifiedQueryLimit);
}

##Purge period
$userspecifiedpurgeperiod = $purgeperiod;
if (!empty($_REQUEST['userspecifiedpurgeperiod']))
  {
    $userspecifiedpurgeperiod = $_REQUEST['userspecifiedpurgeperiod'];
    $purgeperiod = intval($userspecifiedpurgeperiod);
  }

##Normalization
$normalization = 'none';
if (!empty($_REQUEST['normalization']))
  {
    $normalization = $_REQUEST['normalization'];
  }

##Numeric display format
$numericDisplayFormat = 'kmb';
if (!empty($_REQUEST['numericDisplayFormat']))
  {
    $numericDisplayFormat = $_REQUEST['numericDisplayFormat'];
  }

?>
