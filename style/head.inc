<!DOCTYPE html>
<html>
<head>
<style>
ul
{
list-style-type:none;
margin:0;
padding:0;
}
li
{
display:inline;
}
</style>
<style>
  td {
  word-break: break-all;
  }
  </style>
</head>
<body>
<ul>
<li><a href="/">Home</a></li>
<li><link href="/multiplemonths.php" rel="prefetch"><a href="/multiplemonths.php">Multiple months</a></li>
<li><link href="/multipleyears.php" rel="prefetch"><a href="/multipleyears.php">Multiple years</a></li>
<li><link href="/multipletagsandmonths.php" rel="prefetch"><a href="/multipletagsandmonths.php">Multiple tags and months</a></li>
<li><link href="/multipletagsandyears.php" rel="prefetch"><a href="/multipletagsandyears.php">Multiple tags and years</a></li>
<li><link href="/about/" rel="prefetch"><a href="/about/">About</a></li>
</ul>
<p>This website is <strong>not affiliated with or endorsed by the <a href="https://wikimediafoundation.org">Wikimedia Foundation</a>, the nonprofit that maintains Wikipedia and manages the Wikipedia trademark</strong>.</p>
<p><b>Views until June 2015 for desktop come from stats.grok.se and include bot pageviews</b>, while those from July 2015 are from the Wikimedia REST API and exclude identifiable bots and spiders (but may still end up counting many views by bots and spiders as legitimate human views). Views for mobile web, mobile app, desktop spider, and mobile web spider are from the Wikimedia REST API and available starting July 2015. Mobile web and mobile app views from July 2015 onward exclude identifiable bots, and "desktop spider" and "mobile web spider" are basically all the bots/spiders (excluding Wikipedia's own, which get identified as bots).</p>
<?php
include_once(__DIR__."/../backend/coreCode.inc");
if ($transitionstatus=='tobegin')
  {
    print "A new month has just begun, but we haven't transitioned to the new month. So the 'current month' and 'most recent completed month' are one month behind expectations. We'll wait for a while for stats.grok.se to archive its own results before we switch the months. Please check back in a few days for the month to be updated.<br><br>";
  }
if ($transitionstatus=='begun')
  {
    print "Although we have updated the current month and most recent month names, our archival still hasn't caught up. You may therefore experience delays with retrieval of pageview data for the just completed month. Also, if you use tags to display pages, you'll only see pages for which the most recent month has been archived.<br><br>";
  }
include_once("analyticstracking.inc");
?>
</body>
</html>
