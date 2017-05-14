<?php

function printRecentQueries($distinctQueryLimit, $totalQueryLimit) {
  global $mysqli;
  $recentQueriesQuery = "select distinct pagename, language from (select * from queriedpages order by entrytime desc limit $totalQueryLimit) qp1 limit $distinctQueryLimit";
  $recentQueriesResult = $mysqli -> query($recentQueriesQuery);
  print "<p><strong>Recently queried pages</strong></p>";
  for ($i = 0; $i < $recentQueriesResult -> num_rows; $i++) {
    $row = $recentQueriesResult -> fetch_assoc();
    $language = $row['language'];
    $pagename = $row['pagename'];
    print '<li><p><a href="https://wikipediaviews.org/displayviewsformultiplemonths.php?page='.urlencode($pagename).'&allmonths=allmonths&language='.$language.'&drilldown=all">'.$pagename.' ('.$language.')</a></p></li>';
  }
  print '</ul>';
}
?>
