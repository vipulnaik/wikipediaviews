<?php

function pagemonthadvice($pagelist,$monthlist,$camefromtag=false)
{
	global $unavailablecount;
	global $weightedexternalquerylimit;
	global $weightedexternalquerycount;
	global $externalquerycount;
	global $mysqli;
	global $tags_recommended;
	global $alternatemonthspecs_recommended;
	global $hardquerylimit;
	if (count($pagelist) == 0 or count($monthlist) == 0)
	{
		return true;
	}
	print "<br>";
	if (max(count($pagelist),count($monthlist)) > 10)
	{
		print "Printed data for ".count($pagelist)." page";
		if (count($pagelist) > 1) print "s";
		print " and ".count($monthlist)." month";
		if (count($monthlist) > 1) print "s";
		print "<br>";
		print "The table has a total of ".(count($pagelist) * count($monthlist))." entries<br>";
	}
	if (0 < $unavailablecount)
	{
		print "We made ".$externalquerycount." queries to stats.grok.se, treated as ".$weightedexternalquerycount." weighted queries<br>";
		print "We used ".(count($pagelist) * count($monthlist) - $externalquerycount - $unavailablecount)." entries from within the database<br>";
		print "We were unable to compute ".$unavailablecount." of the entries<br>";
		if ($unavailablecount <= $weightedexternalquerylimit)
		{
			print "<strong>TIP</strong>: If you run the query again, the remaining entries can be computed.<br>";
		}
		elseif ($unavailablecount < $hardquerylimit - 1) 
		{
			print "<strong>TIP</strong>: Increase the upper bound on the number of external queries to ".($unavailablecount + 1)." (or higher) from the current value of ".$weightedexternalquerylimit." in the technical settings and run again to complete.<br>";
		}
		else
		{
			print "<strong>TIP</strong>: You're trying to compute too many entries. Reduce the product of the number of pages and the number of months (by reducing whichever is less critical to your needs), or come back after a few hours while we fill in the data for these pages in the background.<br>";
		}
	}
	if ($unavailablecount == 0 and count($pagelist) == 1 and count($monthlist) == 1)
	{ 

		print "<strong>TIP</strong>: If you're just selecting one page and one month, you might as well use <a href=\"http://stats.grok.se\">stats.grok.se</a> directly. The power of this interface is that you can easily compare multiple pages across multiple months or years. So consider adding more pages or more months to your query.<br>";
	}
	if ($unavailablecount == 0 and count($monthlist) <= 4 and count($pagelist) > 1)
	{
		print "<strong>TIP</strong>: Select more months to compare the magnitudes and trends in views of the pages more reliably.<br>";
	}
	if ($unavailablecount == 0 and count($monthlist) >= 3 and count($monthlist) <= 12)
	{
		print "<strong>TIP</strong>: There's an option below to select <em>all</em> months, and also a drop down option (among alternative month specification methods) to select all months <em>in a given year</em>. These can be useful alternatives to manually checking the boxes for several months.<br>";
		$alternatemonthspecs_recommended = true;
	}
	if ($camefromtag == false)
	{
	$findtags_query = "select tag, count(pagename) from pagetags where pagename in (".convertlisttoquotedcsvstring($pagelist).") group by tag order by count(pagename) desc;";
	$tags_result = $mysqli->query($findtags_query);
	if ($tags_result->num_rows > 0)
	{
		$tags_recommended = true;
		print "<strong>TIP: COMPARE ALL PAGES IN A TAG</strong>: Consider comparing all pages in one of these tags (you can select tags as one of the alternative ways of generating page lists -- remember to clear out the text area where you have entered pages if doing so): ";
		for ($i = 0;$i < $tags_result->num_rows;$i++)
		{
			$row = $tags_result->fetch_assoc();
			print $row['tag']." (contains ";
			if ($row['count(pagename)'] == count($pagelist) and count($pagelist) > 1)
			{
				print "<strong>all</strong> ";
			}
			print $row['count(pagename)']." page";
			if ($row['count(pagename)'] > 1) print "s";
			print " from the list)";
			if ($i < $tags_result->num_rows - 1)
			{
				print ", ";
			}
		}	
	}
	}
}