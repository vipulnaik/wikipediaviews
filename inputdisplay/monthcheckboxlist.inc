<?php

##Full list of months, in the form of a check box. Allows multiple selection.

##Uses the database to retrieve the list of months

##Included in: multiplemonthsdataentry.inc

##Associated retrieval file: retrieval/monthlistretrieval.inc

##Note that the month status (present, mostrecent, past) needs to be updated every month manually
##using the database

print '<strong>Check boxes next to the months that you want to select.</strong><br>';
$result = presentandpastmonths_sql();
print '<input type="checkbox" name="allmonths" value="allmonths"';
if ($formdata == true and $allmonths =="allmonths")
{
  print ' checked="checked"';
}
print '>Check this to simultaneously select all months excluding the current month (note that the month boxes will not automatically appear selected but they are indeed selected). To select the current month as well, check the box for the current month below as well.</input><br>';
for($i=0;$i<$result->num_rows;$i++)
{
  $row = $result->fetch_assoc();
  print '<input type="checkbox" name="monthlist[]" value="'.$row['monthfull'].'"';
  if (($formdata==true and in_array($row['monthfull'],$originalmonthlist)) or ($formdata == false and $row['status']=='mostrecent') or ($formdata == true and sizeof($monthlist) == 0 and $row['status']=='mostrecent')) 
  {
    print ' checked';
  }
  print ">".$row['monthfull']." (".$row['month']." ".$row['year'].")";
  if ($row['status']=='present')
  {
    print " -- current month <strong>(may display outdated cached value)</strong>";
  }
  elseif ($row['status']=='mostrecent')
  {
    print " -- most recent completed month";
  }
  print "</input><br>";
}
?>
