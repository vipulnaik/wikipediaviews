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
</head>
<body>
<ul>
<li><a href="/">Home</a></li>
<li><a href="/multiplemonths.php">Multiple months</a></li>
<li><a href="/multipleyears.php">Multiple years</a></li>
<li><a href="/multipletagsandmonths.php">Multiple tags and months</a></li>
<li><a href="/multipletagsandyears.php">Multiple tags and years</a></li>
<li><a href="/about">About</a></li>
</ul>
<p>This website is <strong>not affiliated with or endorsed by the <a href="https://wikimediafoundation.org">Wikimedia Foundation</a>, the nonprofit that maintains Wikipedia and manages the Wikipedia trademark</strong>.</p>
<p>Note that at a given time, you can access views for only one of these: desktop, mobile web, mobile app, desktop spider, and mobile web spider. However, you can change your selection. <b>Views until December 2015 for desktop include bot pageviews</b>, while those from January 2016 exclude identifiable bots and spiders (but may still end up counting many views by bots and spiders as legitimate human views). Views for mobile web, mobile app, desktop spider, and mobile web spider are available starting July 2015. Mobile web and mobile app views from July 2015 onward exclude identifiable bots, and "desktop spider" and "mobile web spider" are basically all the bots/spiders (excluding Wikipedia's own, which get identified as bots).</p>
<p>There is also a more powerful website available if you're interested in visualizing trends. It's called <a href="http://www.wikipediatrends.com/">Wikipedia Trends</a> and is unaffiliated with Wikipedia Views.</p>
<?php
include_once(__DIR__."/../backend/corecode.inc");
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
