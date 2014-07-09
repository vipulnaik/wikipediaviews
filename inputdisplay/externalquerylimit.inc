<?php

##Input form for user to modify limit on number of external queries

##Included in advancedoptions.inc

##Default value in backend/globalvariables/advancedoptionvariables.inc

##Associated retrieval file: retrieval/advancedoptionretrieval.inc

print '<tr><td>Enter an upper bound on the number of external queries (1 external query ~ 1 second)</td>';
print '<td><input type="text" name="userspecifiedquerylimit" value = '.$externalquerylimit.' size="5"></input></td></tr>';
?>