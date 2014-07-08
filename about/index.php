<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>About Wikipedia views</title></head>

<body>
<?php
   include(__DIR__."/../head.inc");
?>
<p><strong>Wikipedia Views</strong> is a minimalistic website intended
for people who're looking for information on how frequently particular
Wikipedia pages or collections of pages get viewed.</p>

<h3>Behind the curtain</h3>

<strong>Wikipedia Views</strong> has been developed
by <a href="http://vipulnaik.com">Vipul Naik</a> using PHP and
MySQL. Special thanks go
to <a href="http://www.stackoverflow.com">Stack Overflow</a> for help
with overcoming some of the coding hurdles that needed to be cleared
to get to functioning code. We rely on statistics
from <a href="http://stats.grok.se">stats.grok.se</a>.</p>

<p>The development was concentrated between April 30, 2014 and May 31,
2014.</p>

<h3>Pageview data fetching and caching</h3>

<ul>

<li><p><strong>How we retrieve and cache data</strong>: Here's how it
works. When you send your list of (page, month, language) combinations
for which you want statistics fetched, we check, for each combination,
if we already have cached data for it in our internal MySQL
database. If we do, we serve the cached data. Otherwise, we fetch the
data by making a HTML page request
to <a href="http://stats.grok.se">stats.grok.se</a> and parsing the
HTML output to extract the number of pageviews, and then cache
it.</p></li>

<li><p><strong>Current month</strong>: Values for the current month
may be cached from earlier queries, but cached values may not be
accurate. In your form, you can specify the number of days after which
you'd like to force a pruge of cached values for the current month
data.</p>

<li><p><strong>Timeout restrictions</strong>: For any individual page
load, our timeout restrictions limit us to about 40 page requests to
stats.grok.se (fetching the pageviews for a given page, month, and
language requires 1 page request). However, it is possible to display
more than 40 pieces of data if some of them have already been
cached. You can specify your own bound on the number of external
queries in your form.</p></li>

</ul>

<h3>User interface features</h3>

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

<h4><a href="/multiplemonths.php">Multiple months display</a></h4>

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

<h4><a href="/multipleyears.php">Multiple years display</a></h4>

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
