<?php

##inc file for data entry for multiple tags and months.

##Included from: multipletagsandmonths.php, displayviewsformultipletagsandmonths.php

##Sends form to: displayviewsformultipletagsandmonths.php

## Includes: tagdropdownselectmultiple.inc, languagedropdown.inc,
## alternatemonthspecificationmethods.inc, advancedoptions.inc
## monthcheckboxlist.inc

$pagetypeadvice = "multipletagsandmonths";
print "<br>";
if ($formdata == true and $monthspecificationerror == false) {
  tagMonthAdvice($tagList,$languageList,$drilldownList,$monthList,$printStatus);
}

print '<form method="post" name="pagecountinfo" action="displayviewsfor'.$pagetypeadvice.'.php">';

include("tagdropdownselectmultiple.inc");

print '<table><col width=600/><col width=500/>';
include("languagedropdownselectmultiple.inc");
include("drilldowndropdown.inc");
print '<tr><td><input type="submit" value="Submit"></td></tr>';
print '</table>';
include("alternatemonthspecificationmethods.inc");
include("advancedoptions.inc");

include("monthcheckboxlist.inc");
print '</form>';
?>

</div>
</body>
</html>
