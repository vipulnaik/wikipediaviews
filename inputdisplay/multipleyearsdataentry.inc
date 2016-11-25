<?php

##inc file for data entry for multiple months.

##Included from: multipleyears.php, displayviewsformultipleyears.php

##Sends form to: displayviewsformultipleyears.php

##Includes: pagelistentry.inc, languagedropdown.inc, 
##alternatepagespecificationmethods.inc, advancedoptions.inc, 
## yearcheckboxlist.inc

if ($formdata == true and ($pageSpecificationError == false and $monthspecificationerror == false)) {
  pageYearAdvice($pageListAsArray,$yearList,$drilldownList,($tag !== ''));
}

$pageTypeAdvice = "multipleyears";
print '<form method="post" name="pagecountinfo" action="displayviewsfor'.$pageTypeAdvice.'.php">';
include("pagelistentry.inc");

print '<table><col width=600/><col width=500/>';
include("languagedropdownselectmultiple.inc");
include("drilldowndropdown.inc");
print '<tr><td><input type="submit" value="Submit"></td></tr>';
print '</table>';

include("alternatepagespecificationmethods.inc");

include("advancedoptions.inc");

include("yearcheckboxlist.inc");
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
on <a href="http://en.wikipedia.org/wiki/India">India</a>, <a href="http://en.wikipedia.org/wiki/China">China</a>,
and <a href="http://en.wikipedia.org/wiki/United_States">United States</a> received in the years 2011, 2012, and 2013. Then, you will enter the
following in the text area:</p>

<tt>India<br>China<br>United States</tt>

<p>You will then select the three years 2013, 2012, and 2011 by
checking the boxes next to them.</p>
</div>
