<?php

##Dropdown box to select the numeric display format

##Included in advancedOptions.inc

##Default value handcoded in HTML printing, not stored as a separate variable ##BAD PROGRAMMING

##Associated retrieval file: retrieval/advancedOptionRetrieval.inc

##Relevant execution code in backend/stringFunctions.inc

print '<tr><td>Enter your normalization choice (<strong>ONLY HTML MONTH DISPLAYS</strong>)</td><td>';
print '<select name="normalization">';
print '<option value="none"';
if (($formdata == false) or ($formdata == true and $normalization=='none')) 
  { 
    print ' selected="selected"';
  }
print '>';
print 'Totals (no normalization)</option>';
print '<option value="dailyaverage"';
if ($formdata == true and $normalization=='dailyaverage') 
  { 
    print ' selected="selected"';
  }
print '>';
print 'Daily average (for days in the month where statistics are available)</option>';
print '<option value="aggregate"';
if ($formdata == true and $normalization=='aggregate') 
  { 
    print ' selected="selected"';
  }
print '>';
print 'Aggregate for language, drilldown, and month (scaled to aggreate for language and drilldown for most recent month)</option>';
print '</select></td>';
print '</tr>';
?>
