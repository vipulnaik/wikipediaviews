<?php

## Creates the tag drop down. Scans the database for the list of all tags, then displays them.

## Included in: alternatepagespecificationmethods.inc

## Associated retrieval file: retrieval/pagelistretrieval.inc

## Important caveat: As you can see in the retrieval file, only pages
## that have been completely archived and have the given tag are
## picked. Therefore, most importantly, when $transitionstatus =
## 'begun', many of the tagged pages are missing because the most
## recent month has not been filled in for them.

print '<tr><td>Select the tag that you want to work with (the page-tag relationships are defined locally on this site and do not correspond to any relationships on Wikipedia):</td><td><select name="tag">';
include_once(__DIR__."/../backend/corecode.inc");
$select_query = "select distinct tag from pagetags order by tag;";
$result = $mysqli->query($select_query);
$numrows = $result->num_rows;
print '<option value="" selected="selected">-- (none selected) --</option>';

for ($i=0;$i < $numrows; $i++)
  {
    $row = $result->fetch_assoc();
    $tag_current = $row['tag'];
    print '<option value="'.$tag_current.'"';
    if ($formdata == true and $tag == $tag_current) 
      {
	print ' selected="selected"';
      }
    print '>'.$tag_current.'</option>';
  }

print '</select></td></tr>';
?>
