<?php

function printRecentQueries($distinctQueryLimit, $totalQueryLimit) {
  global $mysqli;
  $recentQueriesQuery = "select distinct pagename, language, archivalstatus from (select * from queriedpages order by entrytime desc limit $totalQueryLimit) qp1 limit $distinctQueryLimit";
  $recentQueriesResult = $mysqli -> query($recentQueriesQuery);
  print "<p><strong>Recently queried pages</strong></p>";
  print '<table border="1">'."\n";
  print "    <tr>\n";
  print "      <th>Page name</th>\n";
  print "      <th>Language</th>\n";
  print "      <th>Status of fetching view counts</th>\n";
  # print "      <th>Total lifetime desktop views</th>\n";
  print "    </tr>\n";
  for ($i = 0; $i < $recentQueriesResult -> num_rows; $i++) {
    $row = $recentQueriesResult -> fetch_assoc();
    $language = $row['language'];
    $pagename = $row['pagename'];
    $archivalstatus = $row['archivalstatus'];
    print "    <tr>\n";
    print '      <td><a href="https://wikipediaviews.org/displayviewsformultiplemonths.php?page='.urlencode($pagename).'&allmonths=allmonths&language='.$language.'&drilldown=all">'.substr($pagename,0,75)."</a></td>\n";
    print "      <td>$language</td>\n";
    print "      <td>$archivalstatus</td>\n";
    print "    </tr>\n";
  }
  print "</table>";
}
?>
