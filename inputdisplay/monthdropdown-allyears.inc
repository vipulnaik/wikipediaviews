<?php

## Displays the list of all 12 months of the year as a dropdown. Statistics will be displayed for the selected month for all years.

## Included in: alternatemonthspecificationoptions.inc, in turn included in multiplemonthsdataentry.inc

## Associated retrieval file: retrieval/monthlistretrieval.inc

print '<tr><td>Enter the month for which you want to view statistics for all years (<strong>non-void selection here supersedes boxes checked below, but conflicts with non-void selection for year</strong>):</td><td><select name="monthacrossyears">';
$monthswithoutyears = monthswithoutyears();
print '<option value="" selected="selected">-- (none selected) --</option>';
for($i=0;$i<12;$i++)
  {
    print '<option value="'.$monthswithoutyears[$i].'"';
    if ($formdata==true and $carryoverfromonemonth == false)
      {
	if ($monthacrossyears == $monthswithoutyears[$i]) 
	  {
	    print ' selected="selected"';
	  }
      }
    print '>month '.$monthswithoutyears[$i].' across all years';
    print "</option>";
  }
print '</select></td></tr>';
?>
