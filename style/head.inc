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
<li><a href="/about">About</a></li>
</ul>
<br>
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
?>
</body>
</html>
