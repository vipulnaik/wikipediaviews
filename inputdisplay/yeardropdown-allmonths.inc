<?php
print '<tr><td>Enter the year for which you want to view statistics for all months (<strong>non-void selection here supersedes boxes checked below</strong>):</td><td><select name="year">';
$result = presentandpastyears_sql();
print '<option value="" selected="selected">-- (none selected) --</option>';
for($i=0;$i<$result->num_rows;$i++)
{
  $row = $result->fetch_assoc();
  print '<option value="'.$row['year'].'"';
  if ($formdata==true and ($year==$row['year'])) {print ' selected="selected"';}
  print '>all months in year '.$row['year'];
  if ($row['status']=='present')
  {
    print " -- current year <strong>(completed months only)</strong>";
  }
  elseif ($row['status']=='mostrecent')
  {
    print " -- most recent completed year";
  }
  print "</option>";
}
print '</select></td></tr>';
?>