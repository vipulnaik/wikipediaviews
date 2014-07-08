<body>

<p>You can modify your form settings and resubmit.</p>

<form method="post" name="pagecountinfo" action="displaytagviewsforonemonth.php">
<table>
<?php
include("inputdisplay/tagdropdown.inc");
include("inputdisplay/monthdropdown.inc");
include("inputdisplay/languagedropdown.inc");
?>
<tr><td>Enter the format in which you want statistics to be displayed: </td><td>
<select name="displayformat">
  <option value="htmltable" <?php if ($displayformat=="htmltable") {print 'selected="selected"';} ?>>HTML table (best for online viewing)</option>
  <option value="csv" <?php if ($displayformat=="csv") {print 'selected="selected"';} ?>>CSV: Page name and number of views separated by comma; different pages in different lines (easiest to export to Excel)</option>
  <option value="countsonlycsv" <?php if ($displayformat=="countsonlycsv") {print 'selected="selected"';} ?>>Number of views only, separated by commas</option>
  <option value="countsonlyseparatelines" <?php if ($displayformat=="countsonlyseparatelines") {print 'selected="selected"';} ?>>Number of views only, one in each line</option>
</select></td></tr>
</table>
<input type="submit" value="Submit">
</form>

</body>
</html>
