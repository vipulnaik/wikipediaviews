<?php

## Creates the input form for entering a category. No drop down or
## automatic option list. It's a simple text field.

## Included in: alternatePageSpecificationMethods.inc

## Associated retrieval file: retrieval/pageListRetrieval.inc

## Important note: the selection here makes a query to the Wikipedia API, see backend/apiBasedPageListGeneration.inc

print '<tr><td>Alternatively, enter the name of the Wikipedia category whose pages you want to see statistics for. For instance, <a href="http://en.wikipedia.org/wiki/Category:Futurology_journals">Futurology journals</a></td>';
print '<td><input type="text" name="category" placeholder="Category name, without Category: in front"';

if ($formdata == true)
  {
    print ' value="'.$category.'"';
  }
print ' size="70"></input></td></tr>';
?>
