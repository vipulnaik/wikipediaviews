<?php

print '<tr><td>Enter the month for which you want to view statistics:</td><td><select name="month">';
$result = presentandpastmonths_sql();
for($i=0;$i<$result->num_rows;$i++)
  {
    $row = $result->fetch_assoc();
    print "<option value=\"".$row['monthfull']."\" ";
    if (($formdata==true and ($month==$row['monthfull'] or ($month=='' and $row['status']=='mostrecent'))) or ($formdata == false and $row['status']=='mostrecent')) 
      {
	print 'selected="selected"';
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
	print "</option>";
  }
print '</select></td></tr>';
?>
