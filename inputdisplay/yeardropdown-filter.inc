<?php
print '<tr><td>Enter the year for which you want the bound on views to apply (<strong>This will override the month option above</strong>):</td><td><select name="yearfilter">';
$result = presentandpastyears_sql();
print '<option value="" selected="selected">-- (none selected) --</option>';
for($i=0;$i<$result->num_rows;$i++)
  {
    $row = $result->fetch_assoc();
    print '<option value="'.$row['year'].'"';
    if ($formdata==true)
      {
	if ($yearfilter==$row['year'])
    {
      print ' selected="selected"';
    }
      }
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
