<?php

## This file has the HTML for advanced options associated with
## Wikipedia Views. There are many methods, each with its own inc
## file. In the current implementation, it is collapsed by default.

## Included in: onemonthdataentry.inc, multiplemonthsdataentry.inc, multipleyearsdataentry.inc

## Associated retrieval file: retrieval/advancedoptionretrieval.inc

## File with default values for the advanced option variables (if
## specified separately): backend/globalvariables/advancedoptionvariables.inc

print '<a id="displayText2" href="javascript:toggle2();">Show technical settings (for advanced users only)</a><br>';

print '<div id="toggleText2" style="display: none">';
print '<table><col width=600/><col width=500/>';
include(__DIR__."/externalquerylimit.inc");
include(__DIR__."/".$pagetypeadvice."formatdropdown.inc");
include(__DIR__."/purgeperiod.inc");
include(__DIR__."/normalization.inc");
include(__DIR__."/numericdisplayformat.inc");
print '</table></div><br>';
?>