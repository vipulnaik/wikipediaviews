<?php

function pageMonthAdvice($pageList,$languageList,$drilldownList,$monthList,$camefromtag=false) {
  global $unavailableCount;
  global $irretrievableCount;
  global $attemptedExternalQueryLimit;
  global $attemptedExternalQueryCount;
  global $successfulExternalQueryCount;
  global $mysqli;
  global $tags_recommended;
  global $alternatemonthspecs_recommended;
  global $hardquerylimit;
  global $pageDisplayLimit;
  global $cellDisplayLimit;
  global $timeTaken;
  global $graphTimeTaken;
  global $bulkRetrievalTimeTaken;
  if (count($pageList) == 0 or count($monthList) == 0 or count($pageList) > $pageDisplayLimit or count($pageList) * count ($monthList) > $cellDisplayLimit) {
    return true;
  }
  print "<br>";
  print "Time taken for generating the data: ".round($timeTaken,3)." seconds, of which ".round($bulkRetrievalTimeTaken,3)." seconds was for bulk retrieval from the database<br>";
  if (count($monthList) > 1 or count($pageList) > 1 or count($languageList) > 1 or count($drilldownList) > 1) {
    print "Time taken for generating the graphs: ".round($graphTimeTaken,3)." seconds<br>";
  }
  $numCells = count($pageList) * count($languageList) * count($drilldownList) * count($monthList);
  if (max(count($pageList),count($languageList),count($drilldownList),count($monthList)) > 1) {
    print "Printed data for ".count($pageList)." page";
    if (count($pageList) > 1) print "s";
    if (count($languageList) > 1) {
      print ", ".count($languageList)." languages,";
    }
    if (count($drilldownList) > 1) {
      print ", ".count($drilldownList)." drilldowns,";
    }
    print " and ".count($monthList)." month";
    if (count($monthList) > 1) print "s";
    print "<br>";
    print "The table has a total of ".$numCells." entries<br>";
  }
  if ($attemptedExternalQueryCount > 0) {
    print "We attempted ".$attemptedExternalQueryCount." queries to external sources (stats.grok.se, Wikimedia API, Facebook API) out of a limit of ".$attemptedExternalQueryLimit.". Of these, ".$successfulExternalQueryCount." queries were successful<br>";
  }
  $dbEntryCount = $numCells - $successfulExternalQueryCount - $unavailableCount - $irretrievableCount;
  if ($dbEntryCount > 0) {
    print "We used ".$dbEntryCount." entries from within the database<br>";
  }
  if ($unavailableCount > 0) {
    print "We were unable to compute ".$unavailableCount." of the entries and might succeed in computing them later<br>";
  }
  if ($irretrievableCount > 0) {
    print "The number of entries that are irretrievable (i.e., cannot be computed, even if you retry) is ".$irretrievableCount."<br>";
  }
  if ($unavailableCount <= $attemptedExternalQueryLimit and $unavailableCount > 0) {
    print "<strong>TIP</strong>: If you run the query again, the remaining entries can be computed.<br>";
  } elseif ($unavailableCount > 0) {
    print "<strong>TIP</strong>: Increase the upper bound on the number of external queries to ".($unavailableCount)." (or higher) from the current value of ".$attemptedExternalQueryLimit." in the technical settings and run again to complete.<br>";
  } elseif ($unavailableCount > 0) {
    print "<strong>TIP</strong>: You're trying to compute too many entries. Reduce the product of the number of pages and the number of months (by reducing whichever is less critical to your needs), or come back after a few hours while we fill in the data for these pages in the background.<br>";
  }
  if ($unavailableCount == 0 and count($pageList) == 1 and count($monthList) == 1 and count($drilldownList) == 1) { 
      print "<strong>TIP</strong>: The power of this interface is that you can easily compare multiple pages across multiple months or years. So consider adding more pages, months, or drilldowns to your query.<br>";
  }
  if ($unavailableCount == 0 and count($monthList) <= 4 and count($pageList) > 1) {
    print "<strong>TIP</strong>: Select more months to compare the magnitudes and trends in views of the pages more reliably.<br>";
  }
  if ($unavailableCount == 0 and count($monthList) >= 3 and count($monthList) <= 12) {
      print "<strong>TIP</strong>: There's an option below to select <em>all</em> months, and also a drop down option (among alternative month specification methods) to select all months <em>in a given year</em>. These can be useful alternatives to manually checking the boxes for several months.<br>";
      $alternatemonthspecs_recommended = true;
  }
  if ($camefromtag == false)
    {
      $findtags_query = "select tag, count(pagename) from pagetags where pagename in (".convertListToQuotedCsvString($pageList).") group by tag order by count(pagename) desc;";
      $tags_result = $mysqli->query($findtags_query);
      if ($tags_result->num_rows > 0)
	{
	  $tags_recommended = true;
	  print "<strong>TIP: COMPARE ALL PAGES IN A TAG</strong>: Consider comparing all pages in one of these tags (you can select tags as one of the alternative ways of generating page lists -- remember to clear out the text area where you have entered pages if doing so): ";
	  for ($i = 0;$i < $tags_result->num_rows;$i++)
	    {
	      $row = $tags_result->fetch_assoc();
	      print $row['tag']." (contains ";
	      if ($row['count(pagename)'] == count($pageList) and count($pageList) > 1)
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

function pageYearAdvice($pageList,$yearList,$drilldownList,$camefromtag=false) {
  global $unavailableCount;
  global $irretrievableCount;
  global $attemptedExternalQueryLimit;
  global $attemptedExternalQueryCount;
  global $successfulExternalQueryCount;
  global $mysqli;
  global $tags_recommended;
  global $alternatemonthspecs_recommended;
  global $pageDisplayLimit;
  global $cellDisplayLimit;
  global $timeTaken;
  global $graphTimeTaken;
  global $bulkRetrievalTimeTaken;
  if (count($pageList) == 0 or count($yearList) == 0 or count($pageList) > $pageDisplayLimit or count($pageList) * count ($yearList) > $cellDisplayLimit) {
    return true;
  }
  print "<br>";
  print "Time taken for generating the data: ".round($timeTaken,3)." seconds, of which ".round($bulkRetrievalTimeTaken,3)." seconds was for bulk retrieval from the database<br>";
  if (count($yearList) > 1) {
    print "Time taken for generating the graphs: ".round($graphTimeTaken,3)." seconds<br>";
  }
  $numCells = count($pageList) * count($drilldownList) * count($yearList);
  if (max(count($pageList),count($drilldownList),count($yearList)) > 1) {
    print "Printed data for ".count($pageList)." page";
    if (count($pageList) > 1) print "s";
    if (count($drilldownList) > 1) {
      print ", ".count($drilldownList)." drilldowns,";
    }
    print " and ".count($yearList)." year";
    if (count($yearList) > 1) print "s";
    print "<br>";
    print "The table has a total of ".$numCells." entries<br>";
  }
  if ($attemptedExternalQueryCount > 0) {
    print "We attempted ".$attemptedExternalQueryCount." queries to external sources (stats.grok.se, Wikimedia API, Facebook API) out of a limit of ".$attemptedExternalQueryLimit.". Of these, ".$successfulExternalQueryCount." queries were successful<br>";
  }
  if ($camefromtag == false)
    {
      $findtags_query = "select tag, count(pagename) from pagetags where pagename in (".convertListToQuotedCsvString($pageList).") group by tag order by count(pagename) desc;";
      $tags_result = $mysqli->query($findtags_query);
      if ($tags_result->num_rows > 0)
	{
	  $tags_recommended = true;
	  print "<strong>TIP: COMPARE ALL PAGES IN A TAG</strong>: Consider comparing all pages in one of these tags (you can select tags as one of the alternative ways of generating page lists -- remember to clear out the text area where you have entered pages if doing so): ";
	  for ($i = 0;$i < $tags_result->num_rows;$i++)
	    {
	      $row = $tags_result->fetch_assoc();
	      print $row['tag']." (contains ";
	      if ($row['count(pagename)'] == count($pageList) and count($pageList) > 1)
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
