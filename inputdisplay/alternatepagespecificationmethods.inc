<?php

## This file has the HTML for ways of providing lists of pages without
## explicitly typing them in. There are many methods, each with its own
## inc file. The decision of whether to show or collapse this is based on
## the form history and an automatically generated recommendation.

## Included in: onemonthdataentry.inc, multiplemonthsdataentry.inc, multipleyearsdataentry.inc

## Associated retrieval file: retrieval/pageListRetrieval.inc

## For the decision to control and collapse, see backend/advice.inc

if ((($formdata == false) or ($tag==='' and $category==='' and $user==='' and $linkingpage==='' and $archivalstatus==='' and $viewbound==0)) and $tags_recommended == false)
  {
    print '<a id="displayText" href="javascript:toggle();">Show alternative methods for specifying the list of pages</a><br>';
    print '<div id="toggleText" style="display: none">';
  }

print '<table><col width=600/><col width=500/>';
print '<tr><td><strong>Alternative page specification methods: Use only one method at a time!</strong></td></tr>';
include(__DIR__."/tagdropdown.inc");
include(__DIR__."/categorynameentry.inc");
include(__DIR__."/creatinguserentry.inc");
include(__DIR__."/linkingpageentry.inc");
if (($formdata == false) or ($archivalstatus==='' and $viewbound==0))
  {
    print '</table>';
    print '<a id="displayText6" href="javascript:toggle6();">Show more advanced and experimental methods for selecting pages</a><br>';
    print '<div id="toggleText6" style="display: none">';
    print '<table><col width=600/><col width=500/>';
  }
include(__DIR__."/archivalstatus.inc");
include(__DIR__."/filterpagesbyviewcounts.inc");
print '</table>';
if (($formdata == false) or ($archivalstatus==='' and $viewbound==0))
  {
    print '</div><br>';
  }

if ((($formdata == false) or ($tag==='' and $category==='' and $user==='' and $linkingpage==='' and $archivalstatus==='' and $viewbound==0)) and $tags_recommended == false)
  {
    print '</div><br>';
  }
?>
