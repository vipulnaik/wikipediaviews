<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: Add (page,tag) combinations</title></head>
<?php
include("head.inc");
?>
<body>

<p><strong>Please list the Wikipedia page names that you want to add
to the tag. Please include only page names, not full URLs.</strong></p>

<form method="post" name="pagecountinfo" action="tagprocess.php">
<textarea name="pagelistasstring" rows="10" cols="100" placeholder="Enter page names here. Each page name should be on a separate line."></textarea>
<table><col width=700/><col width=500/>
<?php
include("inputdisplay/tagdropdown.inc");
?>
<tr>
<td>Or enter tag name here (nonempty entry here takes precedence over dropdown selection)</td>
<td> <input type="text" name="tagmanual" rows="1" cols = "100" placeholder="Enter tag name here"></textarea></td></tr>
<?php
include("inputdisplay/languagedropdown.inc");
include("inputdisplay/categorynameentry.inc");
include("inputdisplay/creatinguserentry.inc");
?>
<tr><td><input type="checkbox" name="createnew" value="createnew">Check this if you are willing to create a new tag of this name assuming it doesn't already exist</input></td></tr>
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
