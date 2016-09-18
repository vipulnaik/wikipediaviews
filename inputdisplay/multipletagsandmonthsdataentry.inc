<?php

##inc file for data entry for multiple tags and months.

##Included from: multipletagsandmonths.php, displayviewsformultipletagsandmonths.php

##Sends form to: displayviewsformultipletagsandmonths.php

## Includes: tagdropdownselectmultiple.inc, languagedropdown.inc,
## alternatemonthspecificationmethods.inc, advancedoptions.inc
## monthcheckboxlist.inc

$pagetypeadvice = "multipletagsandmonths";
if ($formdata == true)
  {
    print "You may continue editing the list below<br>";
  }
else
  {
    print '<strong>Multiple tags and months: this feature has been added recently, and may run into more problems than other features on the site.</strong><br>';
  }
print '<form method="post" name="pagecountinfo" action="displayviewsfor'.$pagetypeadvice.'.php">';

include("tagdropdownselectmultiple.inc");

print '<table><col width=600/><col width=500/>';
include("languagedropdown.inc");
include("devicedropdown.inc");
print '<tr><td><input type="submit" value="Submit"></td></tr>';
print '</table>';
include("advancedoptions.inc");


include("monthcheckboxlist.inc");
print '</form>';
?>

</div>
</body>
</html>
