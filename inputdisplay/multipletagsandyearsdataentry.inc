<?php

##inc file for data entry for multiple tags and years.

##Included from: multipletagsandyears.php, displayviewsformultipletagsandyears.php

##Sends form to: displayviewsformultipetagsandmonths.php

##Includes: tagDropdownSelectMultiple.inc, languageDropdown.inc,
##yearCheckboxList.inc

$pageTypeAdvice = "multipletagsandyears";
print "<br>";
if ($formdata == true)
  {
    print "You may continue editing the list below<br>";
  }
else
  {
    print '<strong>Multiple tags and years: this feature has been added recently, and may run into more problems than other features on the site.</strong><br>';
  }
print '<form method="post" name="pagecountinfo" action="displayviewsfor'.$pageTypeAdvice.'.php">';

include("tagDropdownSelectMultiple.inc");
print '<table><col width=600/><col width=500/>';
include("languageDropdownSelectMultiple.inc");
include("drilldownDropdown.inc");
print '<tr><td><input type="submit" value="Submit"></td></tr>';
print '</table>';
include("advancedOptions.inc");

include("yearCheckboxList.inc");
print '</form>';
?>

</div>
</body>
</html>
