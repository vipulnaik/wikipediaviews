<?php
if (($formdata == false or ($tag==='' and $category==='' and $user==='' and $linkingpage==='')) and $tags_recommended == false)
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
print '</table>';

if (($formdata == false or ($tag==='' and $category==='' and $user==='' and $linkingpage==='')) and $tags_recommended == false)
{
print '</div><br>';
}
?>