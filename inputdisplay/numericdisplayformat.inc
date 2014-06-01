<tr><td>Enter the format in which you want the numbers displayed (for HTML displays only)</td><td>
<select name="numericdisplayformat">
  <option value="kmb"<?php if (($formdata == false) or ($formdata == true and $numericdisplayformat=='kmb')) { print 'selected="selected"';}?>>Use K, M, B for numbers when they are bigger than a thousand, million, or billion respectively</option>
  <option value="fullprecision"<?php if ($formdata == true and $numericdisplayformat=='fullprecision') { print 'selected="selected"';}?>>Full precision (exact integer values)</option>
  <option value="log"<?php if ($formdata == true and $numericdisplayformat=='log') { print 'selected="selected"';}?>>Logarithms to base 10 (1-digit precision after the decimal)</option>
</select></td></tr>
