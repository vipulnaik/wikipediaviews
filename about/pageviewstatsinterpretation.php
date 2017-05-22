<!doctype html public "-//W3C//DTD HTML 5 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>About Wikipedia views: Pageview statistics interpretation</title></head>

<body>
<?php
   include(__DIR__."/../style/head.inc");
?>

<p>Statistics are obtained
from <a href="http://stats.grok.se">stats.grok.se</a> and the
Wikimedia REST API. For maximal speed and efficiency, we store the
results of past queries in a local database, and we first check with
our internal database before querying the stats.grok.se server. This
page concentrates on what the statistics mean, building on information
at the <a href="http://stats.grok.se/about">stats.grok.se about
page</a>.</p>

<h4>Time-granularity of data</h4>

<ul>
<li><p><strong>Monthly data comes from daily data</strong>: The pageview
count for a month is the sum of the pageview counts for all days in
the month. For the current month, this includes all days that have
completed (the current day is not included in statistics). There is a
delay of up to 5 hours from the end of the day to the updating of
statistics for the day on stats.grok.se.</p></li>
<li><p><strong>Definition of day</strong>: Days are defined as days using
UTC (Greenwich Mean Time) rather than in terms of the local time in
the jurisdiction where the page was viewed.</p></li>
<li><p><strong>We maintain only monthly data</strong>: The information we
maintain on Wikipedia Views includes only monthly totals, and data
that can be deduced from that. We do not retrieve, store, or process
pageview counts by day. The justification is that our goal is to be a
complementary service as far as possible: we hope to allow easier
comparisons over longer timescales and larger numbers of pages rather
than offer day-by-day comparisons.</p></li>
<li><p><strong>We link to the original source (stats.grok.se or the
Wikimedia REST API) for daily data</strong>: However, we <em>do</em>
link (inline in our output tables) to the stats.grok.se page that
provides the day-by-day information in graphical format. You can also
get the information in a text-based format by clicking on the link to
the JSON format from the graphical format page we link to.<p></li>
<li><p><strong>It is possible to reconstruct hourly data from the raw
dumps</strong>: Finally, it's worth noting that underlying raw dumps
(<a href="https://dumps.wikimedia.org/other/pagecounts-raw/">pagecounts-raw</a>,
<a href="https://dumps.wikimedia.org/other/pagecounts-all-sites/">pagecounts-all-sites</a>,
and <a href="https://dumps.wikimedia.org/other/pageviews/">pageviews</a>)
would allow us to get the data at an hourly granularity, if we so
desired. The sources we query do not serve this information in an
easy-to-use manner, so you'll need to load up the dumps and process
them yourself.</li>
</ul>

<p>For a full timeline of the various dumps and how they evolved,
see <a href="https://meta.wikimedia.org/wiki/Research:Timeline_of_Wikimedia_analytics">timeline
of Wikimedia analytics</a>. Although the page was primarily written by
Issa Rice, its creation was assisted and financially supported by
Vipul Naik, the creator of Wikipedia Views.</p>

<h4>Concept of page and view</h4>

<ul>
<li><p>For stats.grok.se, pageviews are combined for pages that differ
only in minor capitalization. So, all accesses of "Barack obama" and
"Barack Obama" would be combined into a single view count. In
contrast, the Wikimedia REST API is case-sensitive.</p></li>
<li><p>Pageviews for pages that redirect to a given page
are <em>not</em> combined with pageviews of the page redirected to
(this behavior is consistent between stats.grok.se and the REST
API). For instance, the
pages <a href="https://en.wikipedia.org/wiki/Arnold_Foundation">Arnold
Foundation</a>
and <a href="https://en.wikipedia.org/wiki/Laura_and_John_Arnold_Foundation">Laura
and John Arnold Foundation</a> are counted separately, even though the
former redirects to the latter. This is the way the Wikimedia raw data
dumps, stats.grok.se, and this website treat the data.</p></li>
<li><p>Pages may accrue views even when they don't exist. For instance,
if I visit the URL for the
page <a href="https://en.wikipedia.org/wiki/Acefwemwieo">Acefwemwieo</a>,
that is recorded as a pageview. Therefore, we cannot reliably infer
that non-existent pages would get 0 pageviews in a given month. In
particular, non-existent pages that have links pointing to them, or
pages that existed earlier and were then deleted, may record a few
pageviews.</p></li>
<li><p>Internal navigation within a page, for instance, by clicking on
section titles in the table of contents, does not count as additional
views of the page.</p></li>
</ul>

<h4>Investigating anomalous page view numbers</h4>

<p>Use the following diagnostics if the pageview counts you see are anomalously <em>low</em>.</p>

<ul>
<li><p>Check whether you spelled the page correctly, and whether it exists.</p></li>
<li><p>You may have selected a redirecting page name rather than the main
page name. A redirecting page name usually gets some traffic,
typically through internal links, but the traffic is much less in
quantity than for the main page name.</p></li>
<li><p>In some cases, pagenames may contain unusual characters that
confuse the system, either at Wikipedia Views or at stats.grok.se. If
you encounter such issues, please <a href="/about/contact.php">contact
us</a> with the information. We'll look into the issue and attempt to fix it if possible.</p></li>
<li><p>The page may have been created after the month for which you're
viewing statistics, or sometime in the middle of the month, or in the
immediately preceding month (so that it didn't have time to get
indexed by search engines and rise to the top of search rankings).</p></li>
<li><p>The page may have very few pages linking to it, and therefore not
have much direct traffic or good search engine ranking.</p></li>
<li><p>Keep in mind that pageview counts for the current month will be
lower because it's an incomplete month. You need to adjust for the
number of completed days in order to compare with other months.</p></li>
</ul>

<p>Use the following diagnostics if the pageview counts you see are anomalously <em>high</em>.</p>

<ul>
<li><p>Visit the Wikipedia page and see if it's the correct one. It's
highly unlikely, but still possible, that the page name you entered is a
different and more popular one from the one you wanted to know about.</p></li>
<li><p>Click through to stats.grok.se or the Wikimedia REST API to see
the day-by-day pageviews. You may be better able to identify whether
the high traffic was uniform or whether it occurred on a particular
day or few days in the month. You can then use other investigative
tools to determine whether anything happened on those days that
sparked interest in the topic.</p></li>
</ul>

<h4>Interested more in Wikipedia pageviews?</h4>

<p>You might like to read this <a href="https://vipulnaik.com/blog/the-great-decline-in-wikipedia-pageviews-full-version/">blog post on the decline in Wikipedia pageviews over time</a>, written based on data collated by Wikipedia Views. A shorter version was <a href="http://lesswrong.com/r/discussion/lw/lxc/the_great_decline_in_wikipedia_pageviews/">published on LessWrong</a>.</p>

</body>
