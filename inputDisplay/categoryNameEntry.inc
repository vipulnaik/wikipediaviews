<?php

## Creates the input form for entering a category. No drop down or
## automatic option list. It's a simple text field.

## Included in: alternatePageSpecificationMethods.inc

## Associated retrieval file: retrieval/pageListRetrieval.inc

## Important note: the selection here makes a query to the Wikipedia API, see backend/apiBasedPageListGeneration.inc

print '<tr><td>Alternatively, enter the name of the Wikipedia category whose pages you want to see statistics for (for instance, <a href="http://en.wikipedia.org/wiki/Category:Futurology_journals">Futurology journals</a>):</td>';
print '<td><input type="text" name="category" placeholder="Category name, without Category: in front"';

if ($formdata == true) {
  print ' value="'.$category.'"';
}
print ' size="70"></input></td></tr>';

print '<tr><td>Enter the continuation string if you do not want to start from the beginning of the category:</td>';

print '<td><input type="text" name="continueString" placeholder="Continue string for category"';
if ($formdata == true) {
  print ' value="'.$continueString.'"';
}
print ' size="70"></input></td></tr>';

?>
