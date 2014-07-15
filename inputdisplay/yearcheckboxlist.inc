<?php

##Full list of years, in the form of a check box. Allows multiple selection.

##Uses the database to retrieve the list of years

##Included in: multipleyearsdataentry.inc

##Associated retrieval file: direct retrieval in displayviewsformultipleyears.php

##Note that the year status (present, mostrecent, past) needs to be updated every year manually
##using the database

print '<strong>Check boxes next to the years that you want to select.</strong><br>';
$result = presentandpastyears_sql();
print '<input type="checkbox" name="allyears" value="allyears"';
if ($formdata == false or ($formdata == true and $allyears =="allyears"))
  {
    print ' checked="checked"';
  }
print '>Check this to simultaneously select all years (although the year boxes will not appear checked, checking this box means all years will be selected)</input><br>';
for($i=0;$i<$result->num_rows;$i++)
  {
    $row = $result->fetch_assoc();
    print '<input type="checkbox" name="yearlist[]" value="'.$row['year'].'"';
    if (($formdata==true and in_array($row['year'],$originalyearlist)) or ($formdata == false and $row['status']=='mostrecent') or ($formdata == true and sizeof($yearlist) == 0 and $row['status']=='mostrecent')) 
      {
	print ' checked';
      }
    print ">".$row['year'];
    if ($row['status']=='present')
      {
	print " -- current year <strong>(for speed and consistency reasons, we exclude the current month from statistics for the current year)</strong>";
      }
    elseif ($row['status']=='mostrecent')
      {
    print " -- most recent completed year";
      }
    elseif ($row['status']=='pastincomplete')
      {
	print " -- we have data for only the month of December for this year";
      }
    print "</input><br>";
  }
?>

