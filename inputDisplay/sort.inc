<?php

##Dropdown box to select the numeric display format

##Included in advancedOptions.inc

##Associated retrieval file: retrieval/advancedOptionRetrieval.inc

##Relevant execution code in backend/stringFunctions.inc

print '<tr><td>Enter your sort choice for pages:</td><td>';
print '<select name="sort">';
print '<option value="desc"';
if (($formdata == false) or ($formdata == true and $sort == 'desc')) { 
  print ' selected="selected"';
}
print '>';
print 'Descending order of total views by page</option>';
print '<option value="asc"';
if ($formdata == true and $sort == 'asc') {
  print ' selected="selected"';
}
print '>';
print 'Ascending order of total views by page</option>';
print '<option value="original"';
if ($formdata == true and $sort == 'original') {
  print ' selected="selected"';
}
print '>';
print 'Original sort order for manually entered list; alphabetical otherwise</option>';
print '<option value="alphabetical"';
if ($formdata == true and $sort == 'alphabetical') {
  print ' selected="selected"';
}
print '>';
print 'Alphabetical</option>';

print '</select></td></tr>';
?>
