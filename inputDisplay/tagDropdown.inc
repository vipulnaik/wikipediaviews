<?php

## Creates the tag drop down. Scans the database for the list of all tags, then displays them.

## Included in: alternatePageSpecificationMethods.inc

## Associated retrieval file: retrieval/pageListRetrieval.inc

## Important caveat: As you can see in the retrieval file, only pages
## that have been completely archived and have the given tag are
## picked. Therefore, most importantly, when $transitionstatus =
## 'begun', many of the tagged pages are missing because the most
## recent month has not been filled in for them.

print '<tr><td>Select the tag that you want to work with (the page-tag relationships are defined locally on this site and do not correspond to any relationships on Wikipedia):</td><td><select name="tag">';
include_once(__DIR__."/../backend/coreCode.inc");
$selectQuery = "select tag,sum(pagecount) as numPages,count(*) as numLanguages from tagsummary group by tag order by tag;";
# $selectQuery = "select tag,count(*) as numPages,count(distinct language) as numLanguages from pagetags group by tag order by tag;";
$result = $mysqli->query($selectQuery);
$numrows = $result->num_rows;
print '<option value="" selected="selected">-- (none selected) --</option>';

for ($i=0;$i < $numrows; $i++) {
  $row = $result->fetch_assoc();
  $currentTag = $row['tag'];
  $numPages = $row['numPages'];
  $numLanguages = $row['numLanguages'];
  print '<option value="'.$currentTag.'"';
  if ($formdata == true and $tag == $currentTag) {
    print ' selected="selected"';
  }
  print ">$currentTag ($numPages pages across $numLanguages language";
  if ($numLanguages > 1) {
    print "s";
  }
  print ")</option>";
}

print '</select></td></tr>';
?>
