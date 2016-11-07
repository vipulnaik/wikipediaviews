<?php

##Dropdown box to select all pages with complete archival status

## Included in: alternatepagespecificationmethods.inc

## Associated retrieval file: retrieval/pageListRetrieval.inc

##Included in advancedoptions.inc

##Default value handcoded in HTML printing, not stored as a separate variable ##BAD PROGRAMMING

##Associated retrieval file: retrieval/pageListRetrieval.inc

print "<tr><td>Select <em>all</em> pages in our database for which we've archived all or most data (limit: ".$pageDisplayLimit.") (<strong>WARNING: CAN BE SLOW</strong>)</td><td>";
print '<select name="archivalStatus">';
print '<option value=""';
if (($formdata == false) or ($formdata == true and $archivalStatus=='')) 
  { 
    print ' selected="selected"';
  }
print '>';
print '-- (not selected) -- </option>';
print '<option value="complete"';
if ($formdata == true and $archivalStatus=='complete') 
  { 
    print ' selected="selected"';
  }
print '>';
print "Pages for which we've archived all month view counts</option>";
print '<option value="mostRecentMonthpending"';
if ($formdata == true and $archivalStatus=='mostRecentMonthpending')
  { 
    print ' selected="selected"';
  }
print '>';
print 'Pages for which only the most recent month is missing</option>';
print '</select></td></tr>';
?>
