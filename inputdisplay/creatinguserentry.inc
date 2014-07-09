<?php

## Creates the input form for entering a user. No drop down or
## automatic option list. It's a simple text field.

## Included in: alternatepagespecificationmethods.inc

## Associated retrieval file: retrieval/pagelistretrieval.inc

## Important note: the selection here makes a query to the Wikipedia API, see backend/apibasedpagelistgeneration.inc

print '<tr><td>Alternatively, enter the name of a Wikipedia user (such as <a href="http://en.wikipedia.org/wiki/User:Vipul">Vipul</a>) to get all main namespace pages created by that user</td>';
print '<td><input type="text" name="user" placeholder="User name, without User: in front" value="'.$user.'" size="70"></input></td></tr>';
?>