<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>About Wikipedia views</title></head>

<body>
<?php
   include(__DIR__."/../style/head.inc");
?>
<p><strong>Wikipedia Views</strong> is a minimalistic website intended
for people who're looking for information on how frequently particular
Wikipedia pages or collections of pages get viewed.</p>

<h3>Table of contents</h3>

<ul>
  <li><p><a href="#behind-the-curtain">Behind the curtain</a></p></li>
  <li><p><a href="#pageview-data-fetching-and-caching">Pageview data fetching and caching</a></p></li>
  <li><p><a href="#user-interface-features">User interface features</a></p><ul>
      <li><p><a href="#multiple-months-display">Multiple months display</a></p></li>
      <li><p><a href="#multiple-years-display">Multiple years display</a></p></li>
    </ul>
  </li>
</ul>

<h3 id="behind-the-curtain">Behind the curtain</h3>

<p><strong>Wikipedia Views</strong> has been developed
by <a href="https://vipulnaik.com">Vipul Naik</a> using PHP and
MySQL. Special thanks go
to <a href="https://www.stackoverflow.com">Stack Overflow</a> for help
with overcoming some of the coding hurdles that needed to be cleared
to get to functioning code.</p>

<p>For desktop data between December 2007 and June 2015 (inclusive) we
rely on statistics
from <a href="http://stats.grok.se">stats.grok.se</a>, which in turn
uses
the <a href="https://wikitech.wikimedia.org/wiki/Analytics/Data/Pagecounts-raw">pagecounts-raw
dump</a> provided hourly by the Wikimedia Foundation. This dump
includes all pageview data for the main domain but excludes mobile and
Wikipedia Zero pageviews.</p>

<p>Desktop, mobile web, mobile app data, desktop spider and mobile web
spider data from July 2015 onward, are from the Wikimedia REST
API. Data before July 2015 for drilldowns other than desktop is not
available through any easily accessible method, and we therefore do
not include it. However, data starting September 2014 can in principle
be reconstructed from the pagecounts-all-sites dump and pageviews dump
released by the Wikimedia Foundation.</p>

<p>Cumulative Facebook like+comment+share counts are available
starting October 2016, but not comprehensively. Only those view counts
are available that were captured in real time from the Facebook API at
the time. For those counts that we did not capture in time, a "cannot
retrieve this data" message will be shown.</p>

<p>Referrer-based drilldowns are based on the <a
href="https://figshare.com/articles/Wikipedia_Clickstream/1305770">Wikipedia
Clickstream</a> dataset (<a
href="https://meta.wikimedia.org/wiki/Research:Wikipedia_clickstream">Wikimedia
Research page</a>), which is available for the months of January and
February 2015, and February, March, April, August, and September
2016. The names of the drilldowns are not the same across months, due
to changes in the way the clickstream dataset was generated. Also,
values of 10 or less are missing and are thus treated as zero. If you
request a referrer drilldown for a month where it does not apply, you
will get "cannot retrieve this data". If you request it for a month
where it does apply but it does not appear in the dataset, we will
return a value of 0; however, the actual value could be any number 10
or less.</p>

<p>The development of the first iteration was concentrated between
April 30, 2014 and July 31, 2014. Subsequent changes were concentrated
in late 2016.</p>

<p>Code is available
at <a href="https://github.com/vipulnaik/wikipediaviews">GitHub</a>.</p>

<p>For more on how to interpret the pageview data, see <a href="pageviewstatsinterpretation.php">here</a>.

<h3 id="pageview-data-fetching-and-caching">Pageview data fetching and caching</h3>

<ul>

<li><p><strong>How we retrieve and cache data</strong>: Here's how it
works. When you send your list of (page, month, language, drilldown)
combinations for which you want statistics fetched, we check, for each
combination, if we already have cached data for it in our internal
MySQL database. If we do, we serve the cached data. Otherwise, we
fetch the data by making a HTTP page request
to <a href="http://stats.grok.se">stats.grok.se</a> or the Wikimedia
REST API and parsing the HTML or JSON output to extract the number of
    pageviews, and then cache it using a MySQL database.</p></li>

<li><p><strong>Cache size</strong>: Our database currently has partial
or complete data for over 400,000 pages, and the main table has over
70 million rows (where each row provides the view count for a
combination of page, month, language, and drilldown). The number of
rows in the table is growing at a rate of between 2 million and 15
million a month; the minimum of 2 million is for filling in data for a
new month for all the pages that have already been queried, and the
higher end arises if we add many new pages to our cache.</p></li>

<li><p><strong>Current month</strong>: Values for the current month
may be cached from earlier queries, but cached values may not be
accurate. In your form, under "Show technical settings (for advanced
users only)" at "Enter the number of days after which ..." you can
specify the number of days after which you'd like to force a purge of
cached values for the current month data.</p>

<li><p><strong>Timeout restrictions</strong>: For any individual page
load, our timeout restrictions limit us to 400 page requests to
stats.grok.se (fetching the pageviews for a given page, month,
language, and drilldown requires 1 page request) and the Wikimedia
API. However, it is possible to display more than 400 pieces of data
if some of them have already been cached. You can specify your own
bound on the number of external queries in your form, under "Show
technical settings (for advanced users only)" at "Enter an upper bound
on the number of external queries ...".</p></li>

</ul>

<h3 id="user-interface-features">User interface features</h3>

<h4><a href="/">Home page (default display)</a></h4>

<p>You can enter the following:</p>

<ul>
<li>A list of page names, one in each line, in the text area.</li>
<li>A <em>single</em> month, selected from the dropdown (default is the most recent completed month).</li>
<li>A single language, chosen by default to be English.</li>
</ul>

<p>You can also select the display format and some other
display-related options. You will then be presented a table (in your
desired format) giving the total numer of pageviews in the selected
month for each of your pages.</p>

<h4 id="multiple-months-display"><a href="/multiplemonths.php">Multiple months display</a></h4>

<p>This is a more sophisticated display intended for cases where you
want to compare data for one or more pages <em>across multiple
months</em>. You enter the following data:</p>

<ul>
<li>A list of pages, entered in a text area, with one page per line.</li>
<li>A list of months for which you want data displayed, selected by checking boxes.</li>
<li>A single language.</li>
</ul>

<p>In addition, it is possible to select display options. You have a
choice between HTML and CSV display, and you can choose whether you
use rows for pages and columns for months, or rows for months and
columns for pages.</p>

<p>Keep in mind that the number of page requests made to stats.grok.se
is the product of the number of pages and the number of months. If
this product exceeds 50, then the operation may time out unless some
of the data for the pages has already been cached.</p>

<h4 id="multiple-years-display"><a href="/multipleyears.php">Multiple years display</a></h4>

<p>Sometimes, you're interested in getting a more big-picture view
than individual monthly data. In these situations, getting pageviews
by <em>year</em> can be more helpful. The multiple years display allows you to enter the following data:</p>

<ul>
<li>A list of pages, entered in a text area, with one page per line.</li>
<li>A list of years for which you want data displayed, selected by
checking boxes. Only years for which complete data for all months is
available are included.</li>
<li>A single language.</li>
</ul>

</body>
</html>
