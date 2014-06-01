<body>

<p><strong>You may continue editing the list of pages here.</strong> (more help below, and
more background at the <a href="/about">about page</a>)</p>

<form method="post" name="pagecountinfo" action="displayviewsformultipleyears.php">
<textarea name="pagelistasstring" rows="3" cols="100" placeholder="Enter page names here. Each page name should be on a separate line. You may also leave this blank and select a tag from the menu below to display statistics for all pages in our database with that tag."><?php print $pagelistasstring; ?></textarea>
<br>
<strong>Remember, you can either include a list of pages above or select a tag from the dropdown below. You cannot do both.</strong>
<table>
<?php
   include("inputdisplay/tagdropdown.inc");
   include("inputdisplay/languagedropdown.inc");
   include("inputdisplay/externalquerylimit.inc");
?>
<tr><td>Enter the format in which you want statistics to be displayed: </td><td>
<select name="displayformat">
  <option value="htmltable" <?php if ($displayformat=="htmltable") {print 'selected="selected"';} ?>>HTML table (best for online viewing) with rows corresponding to pages and columns corresponding to years</option>
  <option value="csv" <?php if ($displayformat=="csv") {print 'selected="selected"';} ?>>CSV: Page name and number of views separated by comma; each line for a different page</option>
  <option value="htmltabletransposed" <?php if ($displayformat=="htmltabletransposed") {print 'selected="selected"';} ?>>HTML table with rows corresponding to years and columns corresponding to pages (best if few pages, many years)</option>
  <option value="csvtransposed" <?php if ($displayformat=="csvtransposed") {print 'selected="selected"';} ?>>CSV: Year and number of views separated by comma; each line for a different year</option>
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
