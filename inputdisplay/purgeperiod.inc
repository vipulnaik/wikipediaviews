<?php

##Input form for user to modify the number of days after which a new 
##value for the current month will be forcibly retrieved

##Included in advancedoptions.inc

##Default value in backend/globalvariables/advancedoptionvariables.inc

##Associated retrieval file: retrieval/advancedoptionretrieval.inc

print '<tr><td>Enter the number of days after which you want to force a purge of view count data for the current month (relevant <em>only</em> if you request data for the current month) (<strong>note: if 0, enter the word zero, else enter the numeric value</strong>)</td>';
print '<td><input type="text" name="userspecifiedpurgeperiod" value = "';
if ($formdata == true)
{
  print $userspecifiedpurgeperiod;
}
else
{
  print $purgeperiod;
}
print '" size="3" align="right"></input>';
?>