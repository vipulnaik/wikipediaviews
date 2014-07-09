<?php

## This file has the HTML for ways of providing lists of months without
## having to check boxes.

## Included in: multiplemonthsdataentry.inc

## Associated retrieval file: retrieval/monthlistretrieval.inc

if (($formdata == false or ($monthacrossyears==='' and $year==='') or $carryoverfromonemonth==true) and $alternatemonthspecs_recommended==false)
{
print '<a id="displayText4" href="javascript:toggle4();">Show alternative methods for specifying the list of months</a><br>';

print '<div id="toggleText4" style="display: none">';
}
print '<table><col width=600/><col width=500/>';
print '<tr><td><strong>Alternative month specification methods: Use only one method at a time!</strong></td></tr>';
include(__DIR__."/monthdropdown-allyears.inc");
include(__DIR__."/yeardropdown-allmonths.inc");
print '</table>';

if (($formdata == false or ($monthacrossyears==='' and $year==='') or $carryoverfromonemonth==true) and $alternatemonthspecs_recommended==false)
{
print '</div><br>';
}
?>