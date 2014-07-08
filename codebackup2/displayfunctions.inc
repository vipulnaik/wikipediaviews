<?php

function printpageviewsascsv($pagelist,$month,$language,$explanatoryheader,$includetotal)
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

function printpageviewsashtmltable($pagelist,$month,$language,$explanatoryheader,$includetotal)
{
print "<table border=\"1\">";
if ($explanatoryheader != 'noheader') {print "<tr><th>Page name</th><th>Pageviews in month ".$month."</th></tr>";}
$total=0;
foreach($pagelist as $page)
{
	$viewcount = getpageviews($page,$month,$language);
	if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
	$stringtoprint = "<tr><td><a href=\"" . getpageurl($page,$language) . "\">" . $page . "</a></td><td><a href=\"" . getpageviewsurl($page,$month,$language) . "\">" . $viewcount . "</a></td></tr>";
	print $stringtoprint;
}
if ($includetotal=='includetotal') {print "<tr><th>Total</th><th>".$total."</th></tr>";}
print "</table>";
}

function printpageviewsascountsonlycsv($pagelist,$month,$language,$explanatoryheader,$includetotal)
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

function printpageviewsascountsonlyseparatelines($pagelist,$month,$language,$explanatoryheader,$includetotal)
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

function printpageviewsformonthlistascsv($pagelist,$monthlist,$language,$includetotal)
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

function printpageviewsformonthlistashtmltable($pagelist,$monthlist,$language,$includetotal)
{
print "<table border=\"1\">";
$headerstring = "<tr><th>Page name</th>";
foreach($monthlist as $month)
{
	$headerstring .= "<th>Pageviews in month ".$month."</th>";
}
if ($includetotal=='includetotal') {$headerstring .="<th>Total</th>";}
$headerstring.="</tr>";
print $headerstring;
foreach($pagelist as $page)
{
	$total = 0;
	$stringtoprint = "<tr><td><a href=\"".getpageurl($page,$language)."\">".$page."</a></td>";
	foreach($monthlist as $month)
	{
		$viewcount = getpageviews($page,$month,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= "<td><a href=\"".getpageviewsurl($page,$month,$language)."\">".$viewcount."</a></td>";

	}
	if ($includetotal=='includetotal') {$stringtoprint .="<td>".$total."</td>";}
	$stringtoprint .="</tr>";
	print $stringtoprint;
}
}

function printpageviewsformonthlistascsvtransposed($pagelist,$monthlist,$language,$includetotal)
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

function printpageviewsformonthlistashtmltabletransposed($pagelist,$monthlist,$language,$includetotal)
{
print "<table border=\"1\">";
$headerstring = "<tr><th>Month</th>";
foreach($pagelist as $page)
{
	$headerstring .= "<th>Views of page <a href=\"". getpageurl($page,$language). "\">" . $page."</a></th>";
}
if ($includetotal=='includetotal') {$headerstring .="<th>Total</th>";}
$headerstring.="</tr>";
print $headerstring;
foreach($monthlist as $month)
{
	$stringtoprint = "<tr><td>".$month."</td>";
	$total = 0;
	foreach($pagelist as $page)
	{
		$viewcount = getpageviews($page,$month,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= "<td><a href=\"".getpageviewsurl($page,$month,$language)."\">".$viewcount."</a></td>";
	}
	if ($includetotal=='includetotal') {$stringtoprint .="<td>".$total."</td>";}
	$stringtoprint .="</tr>";
	print $stringtoprint;
}
}

function printpageviewsforyearlistascsv($pagelist,$yearlist,$language,$includetotal)
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

function printpageviewsforyearlistashtmltable($pagelist,$yearlist,$language,$includetotal)
{
print "<table border=\"1\">";
$headerstring = "<tr><th>Page name</th>";
foreach($yearlist as $year)
{
	$headerstring .= "<th>Pageviews in year ".$year."</th>";
}
if ($includetotal=='includetotal') {$headerstring .="<th>Total</th>";}
$headerstring.="</tr>";
print $headerstring;
foreach($pagelist as $page)
{
	$total = 0;
	$stringtoprint = "<tr><td><a href=\"".getpageurl($page,$language)."\">".$page."</a></td>";
	foreach($yearlist as $year)
	{
		$viewcount = getannualpageviews($page,$year,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= "<td>".$viewcount."</td>";

	}
	if ($includetotal=='includetotal') {$stringtoprint .="<td>".$total."</td>";}
	$stringtoprint .="</tr>";
	print $stringtoprint;
}
}

function printpageviewsforyearlistascsvtransposed($pagelist,$yearlist,$language,$includetotal)
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

function printpageviewsforyearlistashtmltabletransposed($pagelist,$yearlist,$language,$includetotal)
{
print "<table border=\"1\">";
$headerstring = "<tr><th>Year</th>";
foreach($pagelist as $page)
{
	$headerstring .= "<th>Views of page <a href=\"". getpageurl($page,$language). "\">" . $page."</a></th>";
}
if ($includetotal=='includetotal') {$headerstring .="<th>Total</th>";}
$headerstring.="</tr>";
print $headerstring;
foreach($yearlist as $year)
{
	$stringtoprint = "<tr><td>".$year."</td>";
	$total = 0;
	foreach($pagelist as $page)
	{
		$viewcount = getannualpageviews($page,$year,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= "<td>".$viewcount."</td>";
	}
	if ($includetotal=='includetotal') {$stringtoprint .="<td>".$total."</td>";}
	$stringtoprint .="</tr>";
	print $stringtoprint;
}
}

?>
