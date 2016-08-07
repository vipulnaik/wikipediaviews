<?php

##inc file for data entry for multiple tags and years.

##Included from: multipletagsandyears.php, displayviewsformultipletagsandyears.php

##Sends form to: displayviewsformultipetagsandmonths.php

##Includes: tagdropdownselectmultiple.inc, languagedropdown.inc,
##yearcheckboxlist.inc

$pagetypeadvice = "multipletagsandyears";
if ($formdata == true)
  {
    print "You may continue editing the list below<br>";
  }
else
  {
    print '<strong>Multiple tags and years: this feature has been added recently, and may run into more problems than other features on the site.</strong><br>';
  }
print '<form method="post" name="pagecountinfo" action="displayviewsfor'.$pagetypeadvice.'.php">';

include("tagdropdownselectmultiple.inc");
print '<br>';
include("languagedropdown.inc");
include("devicedropdown.inc");
print '<br><br><input type="submit" value="Submit"><br><br>';
include("advancedoptions.inc");

include("yearcheckboxlist.inc");
print '</form>';
?>

</div>
</body>
</html>
