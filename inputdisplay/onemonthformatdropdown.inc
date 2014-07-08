<tr><td>Enter the format in which you want statistics to be displayed: </td><td>
<select name="displayformat">
  <option value="htmltable" <?php if ($formdata == true and $displayformat=="htmltable") {print 'selected="selected"';} ?>>HTML table (best for online viewing)</option>
  <option value="csv" <?php if ($formdata == true and $displayformat=="csv") {print 'selected="selected"';} ?>>CSV: Page name and number of views separated by comma; different pages in different lines (easiest to export to Excel)</option>
  <option value="countsonlycsv" <?php if ($formdata == true and $displayformat=="countsonlycsv") {print 'selected="selected"';} ?>>Number of views only, separated by commas</option>
  <option value="countsonlyseparatelines" <?php if ($formdata == true and $displayformat=="countsonlyseparatelines") {print 'selected="selected"';} ?>>Number of views only, one in each line</option>
</select></td></tr>
