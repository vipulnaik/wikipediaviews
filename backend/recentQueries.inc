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
  print "      <th>Lifetime desktop views (computed so far)</th>\n";
  print "      <th>Tags</th>\n";
  print "    </tr>\n";
  for ($i = 0; $i < $recentQueriesResult -> num_rows; $i++) {
    $row = $recentQueriesResult -> fetch_assoc();
    $language = $row['language'];
    $pagename = $row['pagename'];
    $archivalstatus = $row['archivalstatus'];
    $tagList = getTagListByPageList(array($pagename),array($language));
    $currentDesktopTotalQuery = 'select coalesce(sum(viewcount), 0) as total from viewcountsbymonth where pagename="'.str_replace('"','\"',$pagename).'" and language = "'.$language.'" and drilldown = "desktop";';
    $currentDesktopTotalResult = $mysqli -> query($currentDesktopTotalQuery);
    $viewcount = 0;
    if ($currentDesktopTotalResult -> num_rows > 0) {
      $totalRow = $currentDesktopTotalResult -> fetch_assoc();
      $viewcount = $totalRow['total'];
    }
    if ($viewcount > 100) {
      print "    <tr>\n";
      print '      <td><a href="https://wikipediaviews.org/displayviewsformultiplemonths.php?page='.urlencode($pagename).'&allmonths=allmonths&language='.$language.'&drilldown=all">'.$pagename."</a></td>\n";
      print "      <td><a href=\"".getPageUrl($pagename,$language)."\">$language</a></td>\n";
      print "      <td>$archivalstatus</td>\n";
      print "      <td align=".'"right"'.">$viewcount</td>\n";
      print "      <td>";
      if (array_key_exists($pagename, $tagList) and array_key_exists($language, $tagList[$pagename])) {
        foreach ($tagList[$pagename][$language] as $tag) {
          print "<a href=\"".getAllTimeTagViewsUrl($tag, $language)."\">".$tag."</a> ";
        }
      }
      print "      </td>\n";
      print "    </tr>\n";
    }
  }
  print "</table>";
}
?>
