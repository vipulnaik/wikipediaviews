<tr><td>Enter the format in which you want statistics to be displayed: </td><td>
<select name="displayformat">
  <option value="htmltableautomatic" <?php if ($formdata == true and $displayformat=="htmltableautomatic") {print 'selected="selected"';} ?>>HTML table with larger in number of pages and years used as rows and smaller used as columns</option>
  <option value="htmltable" <?php if ($formdata == true and $displayformat=="htmltable") {print 'selected="selected"';} ?>>HTML table (best for online viewing) with rows corresponding to pages and columns corresponding to years</option>
  <option value="csv" <?php if ($formdata == true and $displayformat=="csv") {print 'selected="selected"';} ?>>CSV: Page name and number of views separated by comma; each line for a different page</option>
  <option value="htmltabletransposed" <?php if ($formdata == true and $displayformat=="htmltabletransposed") {print 'selected="selected"';} ?>>HTML table with rows corresponding to years and columns corresponding to pages (best if few pages, many years)</option>
  <option value="csvtransposed" <?php if ($formdata == true and $displayformat=="csvtransposed") {print 'selected="selected"';} ?>>CSV: Year and number of views separated by comma; each line for a different year</option>
</select></td></tr>
