<?php

$pagetypeadvice = "onemonth";
include("inputdisplay/pagelistentry.inc");

print '<table><col width=600/><col width=500/>';
include("inputdisplay/monthdropdown.inc");
include("inputdisplay/languagedropdown.inc");
print '<tr><td><input type="submit" value="Submit"></td></tr>';
print '</table>';

include("inputdisplay/alternatepagespecificationmethods.inc");

include("inputdisplay/advancedoptions.inc");

print '</form>';
?>

<a id="displayText3" href="javascript:toggle3();">Show more help</a><br><br>

<div id="toggleText3" style="display: none">
<p><strong>More on page names</strong>: The <em>page name</em> is the
name that appears at the top of the Wikipedia page. For instance,
<tt>Albert Einstein</tt> is the page name for the English Wikipedia page with
URL <a href="http://en.wikipedia.org/wiki/Albert_Einstein">http://en.wikipedia.org/wiki/Albert_Einstein</a>.</p>

<p><strong>Sample usage</strong>: Suppose you want to compare the web
traffic that the English Wikipedia pages
on <a href="http://en.wikipedia.org/wiki/Timeline_of_Facebook">Timeline
of
Facebook</a>, <a href="http://en.wikipedia.org/wiki/Timeline_of_Twitter">Timeline
of Twitter</a>,
and <a href="http://en.wikipedia.org/wiki/Timeline_of_Google_Search">Timeline
of Google Search</a> received in March 2014. Then, you will enter the
following in the text area:</p>

<tt>Timeline of Facebook<br>Timeline of Twitter<br>Timeline of Google Search</tt>

<p>You will then select the month "201403 (March 2014)" from the
dropdown in front of "Enter the month for which you want to view
statistics" and then you will click the "Submit" button.</p>
</div>