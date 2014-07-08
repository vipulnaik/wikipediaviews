<?php
	include(__DIR__."/corecode.inc");
	$currentdate = new DateTime("now");
	print_r($currentdate);
	print "<br>";
	global $mysqli;
	if ($mysqli->connect_errno) {
       	   echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
       	}
	print "View counts by month data: ";
	$viewcountsbymonth_count_query = "select count(*) from viewcountsbymonth;";
	$viewcountsbymonth_count_result = $mysqli->query($viewcountsbymonth_count_query);
	$row = $viewcountsbymonth_count_result->fetch_assoc();
	print $row['count(*)']." entries<br>";
	print "View counts by year data: ";
	$viewcountsbyyear_count_query = "select count(*) from viewcountsbyyear;";
	$viewcountsbyyear_count_result = $mysqli->query($viewcountsbyyear_count_query);
	$row = $viewcountsbyyear_count_result->fetch_assoc();
	print $row['count(*)']." entries<br>";
	print "Queried pages data:<br>";
	$queriedpages_query = "select archivalstatus,count(pagename) from queriedpages group by archivalstatus order by count(pagename) desc;";
	$queriedpages_result = $mysqli->query($queriedpages_query);
	for ($i = 0; $i < $queriedpages_result->num_rows; $i++)
	{
		$row = $queriedpages_result->fetch_assoc();
		print $row['count(pagename)']." ".$row['archivalstatus']." pages<br>";
	}
?>