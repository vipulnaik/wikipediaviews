<?php

##Dropdown box to select the appropriate display format for a one month display

##Included in advancedoptions.inc

##Default value handcoded in HTML printing, not stored as a separate variable ##BAD PROGRAMMING

##Associated retrieval file: retrieval/advancedoptionretrieval.inc

##Relevant execution code in backend/displayfunctions.inc

print '<tr><td>Enter the format in which you want statistics to be displayed: </td><td>';
print '<select name="displayformat">';
print '<option value="htmltable"';
if ($formdata == true and $displayformat=="htmltable") 
{
  print 'selected="selected"';
}
print '>';
print 'HTML table (best for online viewing)</option>';
print '<option value="csv"';
if ($formdata == true and $displayformat=="csv") 
{
  print 'selected="selected"';
}
print '>';
print 'CSV: Page name and number of views separated by comma; different pages in different lines (easiest to export to Excel)</option>';
print '<option value="countsonlycsv"';
if ($formdata == true and $displayformat=="countsonlycsv") 
{
  print ' selected="selected"';
}
print '>';
print 'Number of views only, separated by commas</option>';
print '<option value="countsonlyseparatelines"';
if ($formdata == true and $displayformat=="countsonlyseparatelines") 
{
  print ' selected="selected"';
}
print '>';
print 'Number of views only, one in each line</option>';
print '</select></td></tr>';
?>
