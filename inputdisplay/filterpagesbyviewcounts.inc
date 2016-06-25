<?php

# Experimental interface to filter already cached pages in our database
# that satisfy some constraints on their number of pageviews in a given
# month.

print "<tr><td><strong>HIGHLY EXPERIMENTAL ALTERNATIVE -- PRONE TO BREAKING</strong></td></tr>";
print "<tr><td>Enter the lower bound on the number of pageviews you want</td>";
print '<td><input type="text" name="viewbound" placeholder="Lower bound on view count"';
if ($formdata == true)
  {
    print ' value="'.$viewbound.'"';
  }

print ' size="70"></input></td></tr>';
include("monthdropdown-filter.inc");
include("yeardropdown-filter.inc");
?>
