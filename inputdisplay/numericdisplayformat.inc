<?php

##Dropdown box to select the numeric display format

##Included in advancedoptions.inc

##Default value handcoded in HTML printing, not stored as a separate variable ##BAD PROGRAMMING

##Associated retrieval file: retrieval/advancedoptionretrieval.inc

##Relevant execution code in backend/stringfunctions.inc

print '<tr><td>Enter the format in which you want the numbers displayed (for HTML displays only)</td><td>';
print '<select name="numericdisplayformat">';
print '<option value="kmb"';
if (($formdata == false) or ($formdata == true and $numericdisplayformat=='kmb')) 
  { 
    print ' selected="selected"';
  }
print '>';
print 'Use K, M, B for numbers when they are bigger than a thousand, million, or billion respectively</option>';
print '<option value="fullprecision"';
if ($formdata == true and $numericdisplayformat=='fullprecision') 
  { 
    print ' selected="selected"';
  }
print '>';
print 'Full precision (exact integer values)</option>';
print '<option value="log"';
if ($formdata == true and $numericdisplayformat=='log') 
  { 
    print ' selected="selected"';
  }
print '>';
print 'Logarithms to base 10 (1-digit precision after the decimal)</option>';
print '</select></td></tr>';
?>
