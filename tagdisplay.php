<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: pages with a given tag</title></head>
<?php
include("head.inc");
?>
<body>

<p><strong>Please select the tag for which you want view count
statistics for the pages with that tag.</strong> (you can add pages to
a particular tag <a href="/taginput.php">here</a>, and more background
is at the <a href="/about">about page</a>)</p>

<form method="post" name="pagecountinfo" action="displaytagviewsforonemonth.php">
<table>
<?php
include("inputdisplay/tagdropdown.inc");
include("inputdisplay/languagedropdown.inc");
include("inputdisplay/monthdropdown.inc");
?>
<tr><td>Enter the format in which you want statistics to be displayed: </td><td>
<select name="displayformat">
  <option value="htmltable">HTML table (best for online viewing)</option>
  <option value="csv">CSV: Page name and number of views separated by comma; different pages in different lines (easiest to export to Excel)</option>
  <option value="countsonlycsv">Number of views only, separated by commas</option>
  <option value="countsonlyseparatelines">Number of views only, one in each line</option>
</select></td></tr>
</table>
<input type="submit" value="Submit">
</form>

</body>
</html>
