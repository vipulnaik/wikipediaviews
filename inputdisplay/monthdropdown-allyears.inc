<tr><td>Enter the month for which you want to view statistics for all years (<strong>non-void selection here supersedes boxes checked below, but conflicts with non-void selection for year</strong>):</td><td><select name="monthacrossyears">
<?php
        include_once(__DIR__."/../backend/corecode.inc");
	$monthswithoutyears = monthswithoutyears();
	print '<option value="" selected="selected">-- (none selected) --</option>';
	for($i=0;$i<12;$i++)
	{
	print '<option value="'.$monthswithoutyears[$i].'"';
	if ($formdata==true and ($monthacrossyears == $monthswithoutyears[$i])) {print ' selected="selected"';}
	print '>month '.$monthswithoutyears[$i].' across all years';
	print "</option>";
	}
?>
</select></td></tr>