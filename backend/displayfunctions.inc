<?php

function totalsandpercentages($pagelist,$monthoryearlist,$viewcountarray)
{
	$grand_total = 0;
	foreach ($pagelist as $page)#Computes page totals and grand total
	{
		$page_total[$page] = 0;
		foreach ($monthoryearlist as $monthoryear)
		{
			$page_total[$page] += intval($viewcountarray[$page][$monthoryear]);

		}
		$grand_total += $page_total[$page];
	}
	foreach ($monthoryearlist as $monthoryear)#Computes month or year totals
	{
		$monthoryear_total[$monthoryear] = 0;
		foreach ($pagelist as $page)
		{
			$monthoryear_total[$monthoryear] += intval($viewcountarray[$page][$monthoryear]);
		}
	}

	foreach ($pagelist as $page)#Computes page percentages
	{
		if ($grand_total == 0)
		{
			$page_percentage[$page] = 'undefined';
		}
		else
		{
			$page_percentage[$page] = round(100 * floatval($page_total[$page])/floatval($grand_total),1);
		}
	}
	
	foreach ($monthoryearlist as $monthoryear)#Computes month or year percentages
	{
		if ($grand_total == 0)
		{
			$monthoryear_percentage[$monthoryear] = 'undefined';
		}
		else
		{
			$monthoryear_percentage[$monthoryear] = round(100.0 * floatval($monthoryear_total[$monthoryear])/floatval($grand_total),1);
		}
	}

	return array($grand_total,$page_total,$monthoryear_total,$page_percentage,$monthoryear_percentage);
}

function printmonthviewcount($page,$month,$language,$viewcount,$numericdisplayformat)
{
	return '<td align="right"><a href="'.getpageviewsurl($page,$month,$language).'" title="'.monthviewtooltip($viewcount).'">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';
}

function printyearviewcount($page,$year,$language,$viewcount,$numericdisplayformat)
{
	return '<td align="right"><a href="'.getannualpageviewsurl($page,$year,$language).'" title="'.yearviewtooltip($viewcount).'">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';
}

function printpageviewsformonthlistashtmltable($pagelist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
##Collect all the numbers that need to be printed first
$viewcountarray = viewcountarraybymonth($pagelist,$monthlist,$language,true,$datanormalization);
$totalsandpercentages_array = totalsandpercentages($pagelist,$monthlist,$viewcountarray);
$grand_total = $totalsandpercentages_array[0];
$page_total = $totalsandpercentages_array[1];
$month_total = $totalsandpercentages_array[2];
$page_percentage = $totalsandpercentages_array[3];
$month_percentage = $totalsandpercentages_array[4];

##Table header row

print '<html><script type="text/javascript" src="/tablesorter/jquery-latest.js"></script> 
<script type="text/javascript" src="/tablesorter/jquery.tablesorter.js"></script>';
print '<table class="tablesorter" border="1">';
$headerstring = "<thead><tr><th>Page name</th>";
foreach($monthlist as $month)
{
	$headerstring .= "<th>Pageviews in month ".$month."</th>";
}
if ($includetotal=='includetotal' and count($monthlist) > 1) {$headerstring .="<th>Total</th>";}
if (count($pagelist) > 1) {$headerstring.="<th>Percentage</th>";}
$headerstring .= "</tr></thead><tbody>";
print $headerstring;

##Data rows
foreach($pagelist as $page) #Prints one row of the table
{
	$page_rowstring = '<tr><td><a href="'.getpageurl($page,$language).'" title = "'.$page.' (read page on Wikipedia)">'.$page.'</a></td>';
	foreach($monthlist as $month) #Computes one cell entry
	{
		$viewcount = $viewcountarray[$page][$month];
		$page_rowstring .= printmonthviewcount($page,$month,$language,$viewcount,$numericdisplayformat);
	}
	if ($includetotal=='includetotal' and count($monthlist) > 1) {$page_rowstring .='<td align="right"><strong><element title="'.$page_total[$page].'">'.numericdisplay($page_total[$page],$numericdisplayformat).'</element></strong></td>';}
	if (count($pagelist) > 1) {$page_rowstring .= '<td align="right"><strong>'.$page_percentage[$page].'</strong></td>';}
	$page_rowstring .="</tr>";
	print $page_rowstring;
}
if ($includetotal=='includetotal' and count($pagelist) > 1)
{
$totals_rowstring="<tr><td><strong>Total</strong></td>";
foreach($monthlist as $month) #Prints bottom row with totals
{
	$totals_rowstring .= '<td align="right"><strong><element title="'.$month_total[$month].'">'.numericdisplay($month_total[$month],$numericdisplayformat).'</element></strong></td>';
}
if (count($monthlist) > 1)
{ 
  $totals_rowstring .= '<td align="right"><strong><element title="'.$grand_total.'">'.numericdisplay($grand_total,$numericdisplayformat).'</element></strong></td>';
}
$totals_rowstring .= '<td align="right"><strong>100</strong></td></tr>';
print $totals_rowstring;
}
if (count($monthlist) > 1)
{
$percentages_rowstring = "<tr><td><strong>Percentage</strong></td>";
foreach($monthlist as $month)
{
	$percentages_rowstring .= '<td align="right"><strong>'.$month_percentage[$month].'</strong></td>';
}
if ($includetotal == 'includetotal')
{
	$percentages_rowstring .= '<td align="right"><strong>100</strong></td>';
}
if (count($pagelist) > 1)
{
	$percentages_rowstring .= '<td align="right">--</td>';
}
$percentages_rowstring .= '</tr>';
print $percentages_rowstring;
}
print "</tbody></table>";
}

function printpageviewsformonthlistashtmltabletransposed($pagelist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
##Collect all the numbers that need to be printed first
$viewcountarray = viewcountarraybymonth($pagelist,$monthlist,$language,true,$datanormalization);
$totalsandpercentages_array = totalsandpercentages($pagelist,$monthlist,$viewcountarray);
$grand_total = $totalsandpercentages_array[0];
$page_total = $totalsandpercentages_array[1];
$month_total = $totalsandpercentages_array[2];
$page_percentage = $totalsandpercentages_array[3];
$month_percentage = $totalsandpercentages_array[4];

##Header row
print '<table border="1">';
$headerstring = "<tr><th>Month</th>";
foreach($pagelist as $page)
{
	$headerstring .= '<th>Views of page <a href="'. getpageurl($page,$language). '" title="'.$page.' (read page on Wikipedia)">' . $page.'</a></th>';
}
if ($includetotal=='includetotal' and count($pagelist) > 1) {$headerstring .="<th>Total</th>";}
if (count($monthlist) > 1) {$headerstring.='<td><strong>Percentage</strong></td>';}
$headerstring .= '</tr>';
print $headerstring;

##Data rows
foreach($monthlist as $month) #Prints one row of the table
{
	$month_rowstring = '<tr><td>'.$month.'</td>';
	foreach($pagelist as $page) #Computes one cell entry
	{
		$viewcount = $viewcountarray[$page][$month];
		$month_rowstring .= printmonthviewcount($page,$month,$language,$viewcount,$numericdisplayformat);
	}
	if ($includetotal=='includetotal' and count($pagelist) > 1) {$month_rowstring .='<td align="right"><strong><element title="'.$month_total[$month].'">'.numericdisplay($month_total[$month],$numericdisplayformat).'</element></strong></td>';}
	if (count($monthlist) > 1) {$month_rowstring .='<td align="right"><strong>'.$month_percentage[$month].'</strong></td></tr>';}
	print $month_rowstring;
}
if ($includetotal=='includetotal' and count($monthlist) > 1)
{
$totals_rowstring="<tr><td><strong>Total</strong></td>";
foreach($pagelist as $page) #Prints bottom row with totals
{
	$totals_rowstring .= '<td align="right"><strong><element title="'.$page_total[$page].'">'.numericdisplay($page_total[$page],$numericdisplayformat).'</element></strong></td>';
}
if (count($pagelist) > 1)
{ 
  $totals_rowstring .= '<td align="right"><strong><element title="'.$grand_total.'">'.numericdisplay($grand_total,$numericdisplayformat).'</element></strong></td>';
}
$totals_rowstring .= '<td align="right"><strong>100</strong></td></tr>';
print $totals_rowstring;
}
if (count($pagelist) > 1)
{
$percentages_rowstring = "<tr><td><strong>Percentage</strong></td>";
foreach($pagelist as $page)
{
	$percentages_rowstring .= '<td align="right"><strong>'.$page_percentage[$page].'</strong></td>';
}
if ($includetotal == 'includetotal')
{
	$percentages_rowstring .= '<td align="right"><strong>100</strong></td>';
}
if (count($monthlist) > 1)
{
	$percentages_rowstring .= '<td align="right">--</td></tr>';
}
print $percentages_rowstring;
}
print "</table>";
}

function printpageviewsforyearlistashtmltable($pagelist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
##Collect all the numbers that need to be printed first
$viewcountarray = viewcountarraybyyear($pagelist,$yearlist,$language,true,$datanormalization);
$totalsandpercentages_array = totalsandpercentages($pagelist,$yearlist,$viewcountarray);
$grand_total = $totalsandpercentages_array[0];
$page_total = $totalsandpercentages_array[1];
$year_total = $totalsandpercentages_array[2];
$page_percentage = $totalsandpercentages_array[3];
$year_percentage = $totalsandpercentages_array[4];

##Header row
print '<strong>Remember that views for the current year only include views for <em>completed</em> months, and views for the year of 2007 only include views in the month of December of that year.</strong><br>';
print '<html><script type="text/javascript" src="/tablesorter/jquery-latest.js"></script> 
<script type="text/javascript" src="/tablesorter/jquery.tablesorter.js"></script>';
print '<table class="tablesorter" border="1">';
$headerstring = "<thead><tr><th>Page name</th>";
foreach($yearlist as $year)
{
	$headerstring .= "<th>Pageviews in year ".$year."</th>";
}
if ($includetotal=='includetotal' and count($yearlist) > 1) {$headerstring .="<th>Total</th>";}
if (count($pagelist) > 1) {$headerstring.="<th>Percentage</th>";}
$headerstring .= "</tr></thead><tbody>";
print $headerstring;

##Data rows
foreach($pagelist as $page) #Prints one row of the table
{
	$page_rowstring = '<tr><td><a href="'.getpageurl($page,$language).'">'.$page.'</a></td>';
	foreach($yearlist as $year) #Computes one cell entry
	{
		$viewcount = $viewcountarray[$page][$year];
		$page_rowstring .= printyearviewcount($page,$year,$language,$viewcount,$numericdisplayformat);
	}
	if ($includetotal=='includetotal' and count($yearlist) > 1) {$page_rowstring .='<td align="right"><strong><element title="'.$page_total[$page].'">'.numericdisplay($page_total[$page],$numericdisplayformat).'</element></strong></td>';}
	if (count($pagelist) > 1) {$page_rowstring .= '<td align="right"><strong>'.$page_percentage[$page].'</strong></td>';}
	$page_rowstring .="</tr>";
	print $page_rowstring;
}
if ($includetotal=='includetotal' and count($pagelist) > 1)
{
$totals_rowstring="<tr><td><strong>Total</strong></td>";
foreach($yearlist as $year) #Prints bottom row with totals
{
	$totals_rowstring .= '<td align="right"><strong><element title="'.$year_total[$year].'">'.numericdisplay($year_total[$year],$numericdisplayformat).'</element></strong></td>';
}
if (count($yearlist) > 1)
{ 
  $totals_rowstring .= '<td align="right"><strong><element title="'.$grand_total.'">'.numericdisplay($grand_total,$numericdisplayformat).'</element></strong></td>';
}
$totals_rowstring .= '<td align="right"><strong>100</strong></td></tr>';
print $totals_rowstring;
}
if (count($yearlist) > 1)
{
$percentages_rowstring = "<tr><td><strong>Percentage</strong></td>";
foreach($yearlist as $year)
{
	$percentages_rowstring .= '<td align="right"><strong>'.$year_percentage[$year].'</strong></td>';
}
if ($includetotal == 'includetotal')
{
	$percentages_rowstring .= '<td align="right"><strong>100</strong></td>';
}
if (count($pagelist) > 1)
{
	$percentages_rowstring .= '<td align="right">--</td>';
}
$percentages_rowstring .= '</tr>';
print $percentages_rowstring;
}
print "</tbody></table>";
}

function printpageviewsforyearlistashtmltabletransposed($pagelist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
##Collect all the numbers that need to be printed first
$viewcountarray = viewcountarraybyyear($pagelist,$yearlist,$language,true,$datanormalization);
$totalsandpercentages_array = totalsandpercentages($pagelist,$yearlist,$viewcountarray);
$grand_total = $totalsandpercentages_array[0];
$page_total = $totalsandpercentages_array[1];
$year_total = $totalsandpercentages_array[2];
$page_percentage = $totalsandpercentages_array[3];
$year_percentage = $totalsandpercentages_array[4];

##Table header row
print '<strong>Remember that views for the current year only include views for <em>completed</em> months, and views for the year of 2007 only include views in the month of December of that year.</strong><br>';
print '<table border="1">';
$headerstring = "<tr><th>Year</th>";
foreach($pagelist as $page)
{
	$headerstring .= "<th>Views of page <a href=\"". getpageurl($page,$language). "\">" . $page."</a></th>";
}
if ($includetotal=='includetotal' and count($pagelist) > 1) {$headerstring .="<th>Total</th>";}
if (count($yearlist) > 1) {$headerstring.='<td><strong>Percentage</strong></td>';}
$headerstring .= '</tr>';
print $headerstring;

##Data rows
foreach($yearlist as $year) #Prints one row of the table
{
	$year_rowstring = '<tr><td>'.$year.'</td>';
	foreach($pagelist as $page) #Computes one cell entry
	{
		$viewcount = $viewcountarray[$page][$year];
		$year_rowstring .= printyearviewcount($page,$year,$language,$viewcount,$numericdisplayformat);
	}
	if ($includetotal=='includetotal' and count($pagelist) > 1) {$year_rowstring .='<td align="right"><strong><element title="'.$year_total[$year].'">'.numericdisplay($year_total[$year],$numericdisplayformat).'</element></strong></td>';}
	if (count($yearlist) > 1) {$year_rowstring .='<td align="right"><strong>'.$year_percentage[$year].'</strong></td></tr>';}
	print $year_rowstring;
}
if ($includetotal=='includetotal' and count($yearlist) > 1)
{
$totals_rowstring="<tr><td><strong>Total</strong></td>";
foreach($pagelist as $page) #Prints bottom row with totals
{
	$totals_rowstring .= '<td align="right"><strong><element title="'.$page_total[$page].'">'.numericdisplay($page_total[$page],$numericdisplayformat).'</element></strong></td>';
}
if (count($pagelist) > 1)
{ 
  $totals_rowstring .= '<td align="right"><strong><element title="'.$grand_total.'">'.numericdisplay($grand_total,$numericdisplayformat).'</element></strong></td>';
}
$totals_rowstring .= '<td align="right"><strong>100</strong></td></tr>';
print $totals_rowstring;
}
if (count($pagelist) > 1)
{
$percentages_rowstring = "<tr><td><strong>Percentage</strong></td>";
foreach($pagelist as $page)
{
	$percentages_rowstring .= '<td align="right"><strong>'.$page_percentage[$page].'</strong></td>';
}
if ($includetotal == 'includetotal')
{
	$percentages_rowstring .= '<td align="right"><strong>100</strong></td>';
}
if (count($yearlist) > 1)
{
	$percentages_rowstring .= '<td align="right">--</td></tr>';
}
print $percentages_rowstring;
}
print "</table>";
}


function printpageviewsascsv($pagelist,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
if ($explanatoryheader != 'noheader') {print "Page name,Pageviews in month ".$month."<br>";}
$total=0;
foreach($pagelist as $page)
{
	$viewcount = getpageviews($page,$month,$language);
	if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
	$stringtoprint = $page."," . $viewcount ."<br>";
	print $stringtoprint;
}
if ($includetotal=='includetotal') {print "Total,".$total;}
}


function printpageviewsascountsonlycsv($pagelist,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
if ($explanatoryheader != 'noheader') {print "Pageviews in month ".$month.":<br>";}
$total=0;
foreach($pagelist as $page)
{
	$viewcount = getpageviews($page,$month,$language);
	if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
	$stringtoprint = $viewcount.",";
	print $stringtoprint;
}
if ($includetotal=='includetotal') {print "<tr><th>Total</th><th>".$total."</th></tr>";}
}

function printpageviewsascountsonlyseparatelines($pagelist,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
if ($explanatoryheader != 'noheader') {print "Pageviews in month ".$month.":<br>";}
$total=0;
foreach($pagelist as $page)
{
	$viewcount = getpageviews($page,$month,$language);
	if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
	$stringtoprint = $viewcount."<br>";
	print $stringtoprint;
}
if ($includetotal=='includetotal') {print "<tr><th>Total</th><th>".$total."</th></tr>";}
}

function printpageviewsformonthlistascsv($pagelist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
$headerstring = "Page name";
foreach($monthlist as $month)
{
	$headerstring .= ",Pageviews in month ".$month;
}
if ($includetotal=='includetotal') {$headerstring .=",Total";}
$headerstring.="<br>";
print $headerstring;
foreach($pagelist as $page)
{
	$stringtoprint = $page;
	$total = 0;
	foreach($monthlist as $month)
	{
		$viewcount = getpageviews($page,$month,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= ",".$viewcount;
	}
	if ($includetotal=='includetotal') {$stringtoprint .=",".$total;}
	$stringtoprint .="<br>";
	print $stringtoprint;
}
}

function printpageviewsformonthlistascsvtransposed($pagelist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
$headerstring = "Month";
foreach($pagelist as $page)
{
	$headerstring .= ",Views of page ".$page;
}
if ($includetotal=='includetotal') {$headerstring .=",Total";}
$headerstring.="<br>";
print $headerstring;
foreach($monthlist as $month)
{
	$stringtoprint = $month;
	$total = 0;
	foreach($pagelist as $page)
	{
		$viewcount = getpageviews($page,$month,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= ",".$viewcount;
	}
	if ($includetotal=='includetotal') {$stringtoprint .=",".$total;}
	$stringtoprint .="<br>";
	print $stringtoprint;
}
}

function printpageviewsforyearlistascsv($pagelist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
$headerstring = "Page name";
foreach($yearlist as $year)
{
	$headerstring .= ",Pageviews in year ".$year;
}
if ($includetotal=='includetotal') {$headerstring .=",Total";}
$headerstring.="<br>";
print $headerstring;
foreach($pagelist as $page)
{
	$stringtoprint = $page;
	$total = 0;
	foreach($yearlist as $year)
	{
		$viewcount = getannualpageviews($page,$year,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= ",".$viewcount;
	}
	if ($includetotal=='includetotal') {$stringtoprint .=",".$total;}
	$stringtoprint .="<br>";
	print $stringtoprint;
}
}

function printpageviewsforyearlistascsvtransposed($pagelist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
$headerstring = "Year";
foreach($pagelist as $page)
{
	$headerstring .= ",Views of page ".$page;
}
if ($includetotal=='includetotal') {$headerstring .=",Total";}
$headerstring.="<br>";
print $headerstring;
foreach($yearlist as $year)
{
	$stringtoprint = $year;
	$total = 0;
	foreach($pagelist as $page)
	{
		$viewcount = getannualpageviews($page,$year,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= ",".$viewcount;
	}
	if ($includetotal=='includetotal') {$stringtoprint .=",".$total;}
	$stringtoprint .="<br>";
	print $stringtoprint;
}
}

?>
