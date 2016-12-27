<?php

##Input form for user to modify limit on number of external queries

##Included in advancedOptions.inc

##Default value in backend/globalvariables/advancedoptionvariables.inc

##Associated retrieval file: retrieval/advancedOptionRetrieval.inc

print '<tr><td>Enter an upper bound on the weighted number of external queries (1 external query ~ 1 second) (<strong>note: if 0, enter the word zero, else enter the numeric value</strong>)</td>';
print '<td><input type="text" name="userSpecifiedQueryLimit" value = "';
if ($formdata == true) {
  print $userSpecifiedQueryLimit;
} else {
  print $attemptedExternalQueryLimit;
}
print '" size="5"></input></td></tr>';
?>
