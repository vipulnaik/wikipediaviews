<?php

##inc file for data entry for multiple tags and months.

##Included from: multipletagsandmonths.php, displayviewsformultipletagsandmonths.php

##Sends form to: displayviewsformultipletagsandmonths.php

## Includes: tagDropdownSelectMultiple.inc, languageDropdown.inc,
## alternateMonthSpecificationMethods.inc, advancedOptions.inc
## monthCheckboxList.inc

$pageTypeAdvice = "multipletagsandmonths";
print "<br>";
if ($formdata == true and $monthSpecificationError == false) {
  tagMonthAdvice($tagList,$languageList,$drilldownList,$monthList,$printStatus);
}

print '<form method="post" name="pagecountinfo" action="displayviewsfor'.$pageTypeAdvice.'.php">';

include("tagDropdownSelectMultiple.inc");

print '<table><col width=600/><col width=500/>';
include("languageDropdownSelectMultiple.inc");
include("drilldownDropdown.inc");
print '<tr><td><input type="submit" value="Submit"></td></tr>';
print '</table>';
include("alternateMonthSpecificationMethods.inc");
include("advancedOptions.inc");

include("monthCheckboxList.inc");
print '</form>';
?>

</div>
</body>
</html>
