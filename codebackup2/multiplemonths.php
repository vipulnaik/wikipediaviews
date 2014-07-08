<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: simultaneously do multiple months</title></head>

<?php
include("head.inc");
?>
<body>

<p><strong>Please list page names for which you want to include
statistics, one on each line. Please include only page names, not full
URLs. Then check the list of months for which you wish to view
statistics.</strong> (more help below, and more background at
the <a href="/about">about page</a>)</p>

<form method="post" name="pagecountinfo" action="displayviewsformultiplemonths.php">
<textarea name="pagelistasstring" rows="3" cols="100" placeholder="Enter page names here. Each page name should be on a separate line."></textarea>
<table>
<tr><td>Enter the format in which you want statistics to be displayed: </td><td>
<select name="displayformat">
  <option value="htmltable">HTML table (best for online viewing) with rows corresponding to pages and columns corresponding to months</option>
  <option value="csv">CSV: Page name and number of views separated by comma; each line for a different page</option>
  <option value="htmltabletransposed">HTML table with rows corresponding to months and columns corresponding to pages (best if few pages, many months)</option>
  <option value="csvtransposed">CSV: Month and number of views separated by comma; each line for a different month</option>
</select></td></tr>
<?php
   include("inputdisplay/languagedropdown.inc");
?>
<tr><td><input type="checkbox" name="includetotal" value="includetotal">Check this to include a total for each row</input></td></tr>
</table>
<input type="submit" value="Submit"></input><br>
<?php
   include("inputdisplay/monthcheckboxlist.inc");
?>
</form>
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

<p>You will then select all 16 months from "201404 (April 2014)" back to "201301 (January 2013)" by checking the boxes next to them.</p>

<p>Since the number of months is much larger than the number of pages,
it makes sense to use rows for months and columns for
pages. Therefore, for the dropdown after "Enter the format in which
you want statistics to be displayed:" select "HTML table with rows
corresponding to months and columns corresponding to pages (best if
few pages, many months)". You may also check the box to display row
totals. Then, click the "Submit" button.</p>

</body>
</html>
