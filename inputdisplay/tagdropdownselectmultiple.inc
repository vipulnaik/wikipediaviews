<?php

## Creates the tag drop down. Scans the database for the list of all tags, then displays them.

## Included in: alternatepagespecificationmethods.inc

## Associated retrieval file: retrieval/pageListRetrieval.inc

## Important caveat: As you can see in the retrieval file, only pages
## that have been completely archived and have the given tag are
## picked. Therefore, most importantly, when $transitionstatus =
## 'begun', many of the tagged pages are missing because the most
## recent month has not been filled in for them.

print '<p>Select the tags that you want to see data for. You can select multiple tags using the Shift and Ctrl keys (the page-tag relationships are defined locally on this site and do not correspond to any relationships on Wikipedia):</p><br><select multiple name="tagList[]" size="10">';
include_once(__DIR__."/../backend/coreCode.inc");
$select_query = "select tag,count(distinct pagename) as numPages,count(distinct language) as numLanguages from pagetags group by tag order by tag;";
$result = $mysqli->query($select_query);
$numrows = $result->num_rows;
for ($i=0;$i < $numrows; $i++) {
  $row = $result->fetch_assoc();
  $currentTag = $row['tag'];
  $numPages = $row['numPages'];
  $numLanguages = $row['numLanguages'];
  print '<option value="'.$currentTag.'"';
  if ($formdata == true) {
    if (in_array($currentTag,$tagList)) {
      print ' selected="selected"';
    }
  }
  print ">$currentTag ($numPages pages across $numLanguages language";
  if ($numLanguages > 1) {
    print "s";
  }
  print ")</option>";
}

print '</select><br>';
?>
