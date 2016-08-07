<?php

##inc file for data entry for multiple months.

##Included from: multiplemonths.php, displayviewsforonemonth.php, displayviewsformultiplemonths.php

##Sends form to: displayviewsformultiplemonths.php

##Includes: pagelistentry.inc, languagedropdown.inc, 
##alternatepagespecificationmethods.inc, alternatemonthspecificationmethods.inc,
##advancedoptions.inc, monthcheckboxlist.inc

if ($formdata == true and ($pagespecificationerror == false and $monthspecificationerror == false))
  {
    pagemonthadvice($pagelistasarray,$monthlist,($tag !== ''));
  }
   
$pagetypeadvice = "multiplemonths";
print '<form method="post" name="pagecountinfo" action="displayviewsfor'.$pagetypeadvice.'.php">';
include("pagelistentry.inc");

print '<table><col width=600/><col width=500/>';
include("languagedropdown.inc");
include("devicedropdown.inc");
print '<tr><td><input type="submit" value="Submit"></td></tr>';
print '</table>';

include("alternatepagespecificationmethods.inc");
include("alternatemonthspecificationmethods.inc");
include("advancedoptions.inc");

include("monthcheckboxlist.inc");
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
and <a href="http://en.wikipedia.org/wiki/United_States">United States</a> received in the months from January 2013 to April 2014. Then, you will enter the
following in the text area:</p>

<tt>India<br>China<br>United States</tt>

<p>You will then select all 16 months from "201404 (April 2014)" back
to "201301 (January 2013)" by checking the boxes next to them. Then,
click the "Submit" button.</p>

</div>
</body>
</html>
