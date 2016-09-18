<?php

##Dropdown box to select the appropriate display format for a multiple year display

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
print 'HTML table with larger in number of pages and years used as rows and smaller used as columns</option>';
print '<option value="htmltable"';
if ($formdata == true and $displayformat=="htmltable") 
  {
    print ' selected="selected"';
  }
print '>';
print 'HTML table with rows corresponding to pages and columns corresponding to years</option>';

print '<option value="htmltabletransposed"';
if ($formdata == true and $displayformat=="htmltabletransposed") 
  {
    print 'selected="selected"';
  }
print '>';
print 'HTML table with rows corresponding to years and columns corresponding to pages (best if few pages, many years)</option>';

print '<option value="csv"';
if ($formdata == true and $displayformat=="csv") 
  {
    print 'selected="selected"';
  }
print '>';
print 'CSV: Page name and number of views separated by pipe delimiter (|); each line for a different page</option>';

print '<option value="csvtransposed"';
if ($formdata == true and $displayformat=="csvtransposed") 
  {
    print 'selected="selected"';
  }
print '>';
print 'CSV: Year and number of views separated by pipe delimiter (|); each line for a different year</option>';

print '<option value="cpi"';
if ($formdata == true and $displayformat=="cpi") 
  {
    print 'selected="selected"';
  }
print '>';
print 'CPI: Special format (documentation pending)</option>';

print '</select></td></tr>';
?>
