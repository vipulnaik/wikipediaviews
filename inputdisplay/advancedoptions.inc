<?php
print '<a id="displayText2" href="javascript:toggle2();">Show technical settings (for advanced users only)</a><br>';

print '<div id="toggleText2" style="display: none">';
print '<table><col width=600/><col width=500/>';
include(__DIR__."/externalquerylimit.inc");
include(__DIR__."/".$pagetypeadvice."formatdropdown.inc");
include(__DIR__."/purgeperiod.inc");
include(__DIR__."/numericdisplayformat.inc");
print '</table></div><br>';
?>