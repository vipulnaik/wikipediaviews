<?php

## Creates the tag drop down. Scans the database for the list of all tags, then displays them.

## Included in: alternatePageSpecificationMethods.inc

## Associated retrieval file: retrieval/pageListRetrieval.inc

## Important caveat: As you can see in the retrieval file, only pages
## that have been completely archived and have the given tag are
## picked. Therefore, most importantly, when $transitionstatus =
## 'begun', many of the tagged pages are missing because the most
## recent month has not been filled in for them.

print '<tr><td>Enter the language Wikipedia(s) that you are interested in: </td><td><select multiple name="languageList[]" size="6">';
include_once(__DIR__."/../backend/coreCode.inc");
$result = languages_sql();
$numrows = $result->num_rows;
for ($i=0;$i < $numrows; $i++) {
  $row = $result->fetch_assoc();
  $currentLanguage = $row['code'];
  print '<option value="'.$currentLanguage.'"';
  if (($formdata == true and in_array($currentLanguage,$languageList)) or ($formdata == false and $currentLanguage == 'en')) {
    print ' selected="selected"';
  }
  print '>'.$row['name']." (".$row['code'].") (desktop data since ".$row['datastart'].")</option>"; 
}

print '</select><br>';
?>
