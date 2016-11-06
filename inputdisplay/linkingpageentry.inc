<?php 

## Creates the input form for entering a page for which we will look
## at pages linked to from that page. No drop down or automatic option
## list. It's a simple text field.

## Included in: alternatepagespecificationmethods.inc

## Associated retrieval file: retrieval/pageListRetrieval.inc

## Important note: the selection here makes a query to the Wikipedia API, see backend/apibasedpageListgeneration.inc

print '<tr><td>Alternatively, enter the name of a Wikipedia page (such as <a href="http://en.wikipedia.org/wiki/Potential_predictability">Potential predictability</a>) to get all main namespace pages linked from that page</td>';
print '<td><input type="text" name="linkingpage" placeholder="Linking page"';

if ($formdata == true)
  {
    print ' value="'.$linkingpage.'"';
  }

print ' size="70"></input></td></tr>';
?>
