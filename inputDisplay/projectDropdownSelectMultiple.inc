<?php

## Creates the tag drop down. Scans the database for the list of all tags, then displays them.

## Included in: alternatePageSpecificationMethods.inc

## Associated retrieval file: retrieval/pageListRetrieval.inc

## Important caveat: As you can see in the retrieval file, only pages
## that have been completely archived and have the given tag are
## picked. Therefore, most importantly, when $transitionstatus =
## 'begun', many of the tagged pages are missing because the most
## recent month has not been filled in for them.

print '<tr><td>Enter the project(s) that you are interested in: </td><td><select multiple name="projectList[]" size="6">';
include_once(__DIR__."/../backend/coreCode.inc");
$projectsToPrint = array('wikipedia','wiktionary','wikiquote','wikinews','wikisource','wikibooks','wikijunior','wikiversity','wikivoyage','wikimedia','wikidata','wikispecies');
foreach($projectsToPrint as $projectToPrint) {
  print '<option value="'.$projectToPrint.'"';
  if (($formdata == true and in_array($projectToPrint,$projectList)) or ($formdata == false and $projectToPrint == 'wikipedia')) {
    print ' selected="selected"';
  }
  print '>'.$projectToPrint."</option>"; 
}

print '</select><br>';
?>
