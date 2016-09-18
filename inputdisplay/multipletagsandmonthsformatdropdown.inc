<?php

##Dropdown box to select the appropriate display format for a multiple month display

##Included in advancedoptions.inc

##Default value handcoded in HTML printing, not stored as a separate variable ##BAD PROGRAMMING

##Associated retrieval file: retrieval/advancedoptionretrieval.inc

##Relevant execution code in backend/displayfunctions.inc

print '<tr><td>Enter the format in which you want statistics to be displayed: </td><td>';
print '<select name="displayformat">';

print '<option value="htmltableautomatic"';
if ($formdata == true and $displayformat=="htmltableautomatic") 
  {
    print ' selected="selected"';
  }
print '>';
print 'HTML table with larger in number of tags and months used as rows and smaller used as columns</option>';

print '<option value="htmltable"';
if ($formdata == true and $displayformat=="htmltable") 
  {
    print ' selected="selected"';
  }
print '>';
print 'HTML table with rows corresponding to tags and columns corresponding to months</option>';

print '<option value="htmltabletransposed"';
if ($formdata == true and $displayformat=="htmltabletransposed") 
  {
    print ' selected="selected"';
  }
print '>';
print 'HTML table with rows corresponding to months and columns corresponding to tags (best if few tags, many months)</option>';

print '<option value="csv"';
if ($formdata == true and $displayformat=="csv") 
  {
    print ' selected="selected"';
  }
print '>';
print 'CSV: Tag name and number of views separated by comma; each line for a different tag</option>';

print '<option value="csvtransposed"';
if ($formdata == true and $displayformat=="csvtransposed") 
  {
    print ' selected="selected"';
  }
print '>';
print 'CSV: Month and number of views separated by comma; each line for a different month</option>';

print '<option value="cpi"';
if ($formdata == true and $displayformat=="cpi") 
  {
    print 'selected="selected"';
  }
print '>';
print 'CPI: Special format (documentation pending)</option>';

print '</select></td></tr>';
?>
