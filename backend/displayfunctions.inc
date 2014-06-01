<?php

function numericdisplay($number,$numericdisplayformat)
{
	if ($numericdisplayformat=='fullprecision')
	{
		return $number;
	}
	if ($numericdisplayformat=='kmb')
	{
		return numericdisplaykmb($number);
	}
	if ($numericdisplayformat=='log')
	{
		return numericdisplaylog($number);
	}
	return $number;
}
function numericdisplaykmb($number)
{
	$number_int = intval($number);
	if ($number_int < 1000)
	{
		return $number;
	}
	if ($number_int >= 1000 and $number_int < 9950)
	{
		$number_k = round((floatval ($number_int))/1000,1);
		return (strval($number_k)."K");
	}
	if ($number_int >= 10000 and $number_int < 999500)
	{
		$number_k = round((floatval ($number_int))/1000,0);
		return (strval($number_k)."K");
	}
	if ($number_int >= 999500 and $number_int < 9950000)
	{
		$number_m = round((floatval ($number_int))/1000000,1);
		return (strval($number_m)."M");
	}
	if ($number_int >= 9950000 and $number_int < 999500000)
	{
		$number_m = round((floatval ($number_int))/1000000,0);
		return (strval($number_m)."M");
	}
	if ($number_int >= 999500000 and $number_int < 9950000000)
	{
		$number_b = round((floatval ($number_int))/1000000000,1);
		return (strval($number_b)."B");
	}
	if ($number_int >= 9950000000)
	{
		$number_b = round((floatval ($number_int))/1000000000,0);
		return (strval($number_b)."B");
	}
	return $number;
}

function numericdisplaylog($number)
{
	if ($number == 0) return "-infinity";
	return round(log($number,10),1);
}
function printpageviewsformonthlistashtmltable($pagelist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
$viewcountarray = viewcountarraybymonth($pagelist,$monthlist,$language,true,$datanormalization);
print '<html><script type="text/javascript" src="/tablesorter/jquery-latest.js"></script> 
<script type="text/javascript" src="/tablesorter/jquery.tablesorter.js"></script>';
print '<table class="tablesorter" border="1">';
$headerstring = "<thead><tr><th>Page name</th>";
foreach($monthlist as $month)
{
	$headerstring .= "<th>Pageviews in month ".$month."</th>";
}
if ($includetotal=='includetotal' and sizeof($monthlist) > 1) {$headerstring .="<th>Total</th>";}
$headerstring.="</tr></thead><tbody>";
print $headerstring;
foreach($pagelist as $page) #Prints one row of the table
{
	$page_total[$page] = 0;
	$page_rowstring = '<tr><td><a href="'.getpageurl($page,$language).'">'.$page.'</a></td>';
	foreach($monthlist as $month) #Computes one cell entry
	{
		$viewcount = $viewcountarray[$page][$month];
		if ($includetotal=='includetotal') {$page_total[$page] += intval($viewcount);}
		$page_rowstring .= '<td align="right"><a href="'.getpageviewsurl($page,$month,$language).'">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';

	}
	if ($includetotal=='includetotal' and sizeof($monthlist) > 1) {$page_rowstring .='<td align="right"><strong>'.numericdisplay($page_total[$page],$numericdisplayformat).'</strong></td>';}
	$page_rowstring .="</tr>";
	print $page_rowstring;
}
if ($includetotal=='includetotal' and sizeof($pagelist) > 1)
{
$grand_total = 0;
$totals_rowstring="<tr><td><strong>Total</strong></td>";
foreach($monthlist as $month) #Prints bottom row with totals
{
	$month_total[$month] = 0;
	foreach($pagelist as $page)
	{
		$month_total[$month] += intval($viewcountarray[$page][$month]);
 	}
	$totals_rowstring .= '<td align="right"><strong>'.numericdisplay($month_total[$month],$numericdisplayformat).'</strong></td>';
	$grand_total += $month_total[$month];
}
if (sizeof($monthlist) > 1)
{ 
  $totals_rowstring .= '<td align="right"><strong>'.numericdisplay($grand_total,$numericdisplayformat).'</strong></td>';
}
$totals_rowstring .= '</tr>';
print $totals_rowstring;
}
print "</tbody></table>";
}

function printpageviewsformonthlistashtmltabletransposed($pagelist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
$viewcountarray = viewcountarraybymonth($pagelist,$monthlist,$language,true);
print '<table border="1">';
$headerstring = "<tr><th>Month</th>";
foreach($pagelist as $page)
{
	$headerstring .= "<th>Views of page <a href=\"". getpageurl($page,$language). "\">" . $page."</a></th>";
}
if ($includetotal=='includetotal' and sizeof($pagelist) > 1) {$headerstring .="<th>Total</th>";}
$headerstring.="</tr>";
print $headerstring;
foreach($monthlist as $month) #Prints one row of the table
{
	$month_total[$month] = 0;
	$month_rowstring = '<tr><td>'.$month.'</td>';
	foreach($pagelist as $page) #Computes one cell entry
	{
		$viewcount = $viewcountarray[$page][$month];
		if ($includetotal=='includetotal') {$month_total[$month] += intval($viewcount);}
		$month_rowstring .= '<td align="right"><a href="'.getpageviewsurl($page,$month,$language).'">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';

	}
	if ($includetotal=='includetotal' and sizeof($pagelist) > 1) {$month_rowstring .='<td align="right"><strong>'.numericdisplay($month_total[$month],$numericdisplayformat).'</strong></td>';}
	$month_rowstring .="</tr>";
	print $month_rowstring;
}
if ($includetotal=='includetotal' and sizeof($monthlist) > 1)
{
$grand_total = 0;
$totals_rowstring="<tr><td><strong>Total</strong></td>";
foreach($pagelist as $page) #Prints bottom row with totals
{
	$page_total[$page] = 0;
	foreach($monthlist as $month)
	{
		$page_total[$page] += intval($viewcountarray[$page][$month]);
 	}
	$totals_rowstring .= '<td align="right"><strong>'.numericdisplay($page_total[$page],$numericdisplayformat).'</strong></td>';
	$grand_total += $page_total[$page];
}
if (sizeof($pagelist) > 1)
{ 
  $totals_rowstring .= '<td align="right"><strong>'.numericdisplay($grand_total,$numericdisplayformat).'</strong></td>';
}
$totals_rowstring .= '</tr>';
print $totals_rowstring;
}
print "</table>";
}

function printpageviewsforyearlistashtmltable($pagelist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
$viewcountarray = viewcountarraybyyear($pagelist,$yearlist,$language,true);
print '<strong>Remember that views for the current year only include views for <em>completed</em> months, and views for the year of 2007 only include views in the month of December of that year.</strong><br>';
print '<table border="1">';
$headerstring = "<tr><th>Page name</th>";
foreach($yearlist as $year)
{
	$headerstring .= "<th>Pageviews in year ".$year."</th>";
}
if ($includetotal=='includetotal' and sizeof($yearlist) > 1) {$headerstring .="<th>Total</th>";}
$headerstring.="</tr>";
print $headerstring;
foreach($pagelist as $page) #Prints one row of the table
{
	$page_total[$page] = 0;
	$page_rowstring = '<tr><td><a href="'.getpageurl($page,$language).'">'.$page.'</a></td>';
	foreach($yearlist as $year) #Computes one cell entry
	{
		$viewcount = $viewcountarray[$page][$year];
		if ($includetotal=='includetotal') {$page_total[$page] += intval($viewcount);}
		$page_rowstring .= '<td align="right">'.numericdisplay($viewcount,$numericdisplayformat).'</td>';
	}
	if ($includetotal=='includetotal' and sizeof($yearlist) > 1) {$page_rowstring .='<td align="right"><strong>'.numericdisplay($page_total[$page],$numericdisplayformat).'</strong></td>';}
	$page_rowstring .="</tr>";
	print $page_rowstring;
}
if ($includetotal=='includetotal' and sizeof($pagelist) > 1)
{
$grand_total = 0;
$totals_rowstring="<tr><td><strong>Total</strong></td>";
foreach($yearlist as $year) #Prints bottom row with totals
{
	$year_total[$year] = 0;
	foreach($pagelist as $page)
	{
		$year_total[$year] += intval($viewcountarray[$page][$year]);
 	}
	$totals_rowstring .= '<td align="right"><strong>'.numericdisplay($year_total[$year],$numericdisplayformat).'</strong></td>';
	$grand_total += $year_total[$year];
}
if (sizeof($yearlist) > 1)
{ 
  $totals_rowstring .= '<td align="right"><strong>'.numericdisplay($grand_total,$numericdisplayformat).'</strong></td>';
}
$totals_rowstring .= '</tr>';
print $totals_rowstring;
}
print "</table>";
}

function printpageviewsforyearlistashtmltabletransposed($pagelist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$datanormalization='none')
{
$viewcountarray = viewcountarraybyyear($pagelist,$yearlist,$language,true);
print '<table border="1">';
$headerstring = "<tr><th>Year</th>";
foreach($pagelist as $page)
{
	$headerstring .= "<th>Views of page <a href=\"". getpageurl($page,$language). "\">" . $page."</a></th>";
}
if ($includetotal=='includetotal' and sizeof($pagelist) > 1) {$headerstring .="<th>Total</th>";}
$headerstring.="</tr>";
print $headerstring;
foreach($yearlist as $year) #Prints one row of the table
{
	$year_total[$year] = 0;
	$year_rowstring = '<tr><td>'.$year.'</td>';
	foreach($pagelist as $page) #Computes one cell entry
	{
		$viewcount = $viewcountarray[$page][$year];
		if ($includetotal=='includetotal') {$year_total[$year] += intval($viewcount);}
		$year_rowstring .= '<td align="right">'.numericdisplay($viewcount,$numericdisplayformat).'</td>';

	}
	if ($includetotal=='includetotal' and sizeof($pagelist) > 1) {$year_rowstring .='<td align="right"><strong>'.numericdisplay($year_total[$year],$numericdisplayformat).'</strong></td>';}
	$year_rowstring .="</tr>";
	print $year_rowstring;
}
if ($includetotal=='includetotal' and sizeof($yearlist) > 1)
{
$grand_total = 0;
$totals_rowstring="<tr><td><strong>Total</strong></td>";
foreach($pagelist as $page) #Prints bottom row with totals
{
	$page_total[$page] = 0;
	foreach($yearlist as $year)
	{
		$page_total[$page] += intval($viewcountarray[$page][$year]);
 	}
	$totals_rowstring .= '<td align="right"><strong>'.numericdisplay($page_total[$page],$numericdisplayformat).'</strong></td>';
	$grand_total += $page_total[$page];
}
if (sizeof($pagelist) > 1)
{ 
  $totals_rowstring .= '<td align="right"><strong>'.numericdisplay($grand_total,$numericdisplayformat).'</strong></td>';
}
$totals_rowstring .= '</tr>';
print $totals_rowstring;
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
