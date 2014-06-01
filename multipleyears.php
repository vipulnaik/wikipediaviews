<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: simultaneously do multiple years</title></head>
<?php
include("head.inc");
include_once("backend/corecode.inc");
?>

<body>

<p><strong>Please list page names for which you want view count
statistics reported. Please enter one page name per line. Please
include only page names, not full URLs. Alternatively,
you can choose a tag from the dropdown menu below to have statistics
displayed for all pages in our database with that tag.</strong></p>

<p><strong>Then check the list of years
for which you wish to view statistics.</strong> (more help below, and
more background at the <a href="/about">about page</a>)</p>

<form method="post" name="pagecountinfo" action="displayviewsformultipleyears.php">
<textarea name="pagelistasstring" rows="3" cols="100"
placeholder="Enter page names here. Each page name should be on a separate line. You may also leave this blank and select a tag from the menu below to display statistics for all pages in our database with that tag."></textarea>
<br>
<strong>Remember, you can either include a list of pages above or select a tag from the dropdown below. You cannot do both.</strong>
<table>
<?php
   include("inputdisplay/tagdropdown.inc");
   include("inputdisplay/languagedropdown.inc");
   include("inputdisplay/externalquerylimit.inc");
?>
<tr><td>Enter the format in which you want statistics to be displayed: </td>
<td><select name="displayformat">
  <option value="htmltable">HTML table (best for online viewing) with rows corresponding to pages and columns corresponding to years</option>
  <option value="csv">CSV: Page name and number of views separated by comma; each line for a different page</option>
  <option value="htmltabletransposed">HTML table with rows corresponding to years and columns corresponding to pages (best if few pages, many years)</option>
  <option value="csvtransposed">CSV: Year and number of views separated by comma; each line for a different year</option>
</select></td></tr>
<?php
include("inputdisplay/numericdisplayformat.inc");
?>
</table>
<input type="submit" value="Submit"></input><br>
<?php
   include("inputdisplay/yearcheckboxlist.inc");
?>
</form>

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
checking the boxes next to them. If you want to see totals, check the
button next to "Check this to include a total for each row". Then,
click the "Submit" button.</p>

</body>
</html>
