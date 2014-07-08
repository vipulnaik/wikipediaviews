<tr><td>Enter the format in which you want statistics to be displayed: </td><td>
<select name="displayformat">
  <option value="htmltableautomatic" <?php if ($formdata == true and $displayformat=="htmltableautomatic") {print 'selected="selected"';} ?>>HTML table with larger in number of pages and months used as rows and smaller used as columns</option>
  <option value="htmltable" <?php if ($formdata == true and $displayformat=="htmltable") {print 'selected="selected"';} ?>>HTML table with rows corresponding to pages and columns corresponding to months</option>
  <option value="csv" <?php if ($formdata == true and $displayformat=="csv") {print 'selected="selected"';} ?>>CSV: Page name and number of views separated by comma; each line for a different page</option>
  <option value="htmltabletransposed" <?php if ($formdata == true and $displayformat=="htmltabletransposed") {print 'selected="selected"';} ?>>HTML table with rows corresponding to months and columns corresponding to pages (best if few pages, many months)</option>
  <option value="csvtransposed" <?php if ($formdata == true and $displayformat=="csvtransposed") {print 'selected="selected"';} ?>>CSV: Month and number of views separated by comma; each line for a different month</option>
</select></td></tr>
