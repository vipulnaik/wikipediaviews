<?php

##Dropdown box to select the numeric display format

##Included in advancedOptions.inc

##Default value handcoded in HTML printing, not stored as a separate variable ##BAD PROGRAMMING

##Associated retrieval file: retrieval/advancedOptionRetrieval.inc

##Relevant execution code in backend/stringFunctions.inc

print '<tr><td>Enter the format in which you want the numbers displayed (<strong>ONLY HTML DISPLAYS</strong>)</td><td>';
print '<select name="numericDisplayFormat">';
print '<option value="kmb"';
if (($formdata == false) or ($formdata == true and $numericDisplayFormat=='kmb')) 
  { 
    print ' selected="selected"';
  }
print '>';
print 'Use K, M, B for numbers when they are bigger than a thousand, million, or billion respectively</option>';
print '<option value="fullprecision"';
if ($formdata == true and $numericDisplayFormat=='fullprecision') 
  { 
    print ' selected="selected"';
  }
print '>';
print 'Full precision (exact integer values)</option>';
print '<option value="log"';
if ($formdata == true and $numericDisplayFormat=='log') 
  { 
    print ' selected="selected"';
  }
print '>';
print 'Logarithms to base 10 (1-digit precision after the decimal)</option>';
print '</select></td></tr>';
?>
