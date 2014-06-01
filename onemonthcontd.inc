<body>

<p><strong>Continue editing the list of pages.</strong> (more help below, and
more background at the <a href="/about">about page</a>)</p>

<form method="post" name="pagecountinfo" action="displayviewsforonemonth.php">
<textarea name="pagelistasstring" rows="10" cols="100" placeholder="Enter page names here. Each page name should be on a separate line. You may also leave this blank and select a tag from the menu below to display statistics for all pages in our database with that tag."><?php
print $pagelistasstring;
?></textarea>
<br>
<strong>Remember, you can either include a list of pages above or select a tag from the dropdown below. You cannot do both.</strong>
<table>
<?php
$formdata = true;
include("inputdisplay/tagdropdown.inc");
include("inputdisplay/monthdropdown.inc");
include("inputdisplay/languagedropdown.inc");
include("inputdisplay/externalquerylimit.inc");
?>
<tr><td>Enter the format in which you want statistics to be displayed: </td><td>
<select name="displayformat">
  <option value="htmltable" <?php if ($displayformat=="htmltable") {print 'selected="selected"';} ?>>HTML table (best for online viewing)</option>
  <option value="csv" <?php if ($displayformat=="csv") {print 'selected="selected"';} ?>>CSV: Page name and number of views separated by comma; different pages in different lines (easiest to export to Excel)</option>
  <option value="countsonlycsv" <?php if ($displayformat=="countsonlycsv") {print 'selected="selected"';} ?>>Number of views only, separated by commas</option>
  <option value="countsonlyseparatelines" <?php if ($displayformat=="countsonlyseparatelines") {print 'selected="selected"';} ?>>Number of views only, one in each line</option>
</select></td></tr>
<?php
	include("inputdisplay/numericdisplayformat.inc");
?>
</table>
<input type="submit" value="Submit">
</form>

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
</body>
</html>
