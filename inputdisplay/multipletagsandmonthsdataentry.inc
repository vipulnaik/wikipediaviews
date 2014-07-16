<?php

##inc file for data entry for multiple months.

##Included from: multipletagsandmonths.php, displayviewsformultipletagsandmonths.php

##Sends form to: displayviewsformultipetagsandmonths.php

##Includes: tagdropdownselectmultiple.inc, languagedropdown.inc,
##alternatemonthspecificationmethods.inc, advancedoptions.inc

$pagetypeadvice = "multipletagsandmonths";
if ($formdata == true)
  {
    print "You may continue editing the list below<br>";
  }
else
  {
    print '<strong>Multiple tags and months: still experimental!</strong><br>';
  }
print '<form method="post" name="pagecountinfo" action="displayviewsfor'.$pagetypeadvice.'.php">';

include("tagdropdownselectmultiple.inc");
print '<br>';
include("languagedropdown.inc");
print '<br><br>';
include("alternatemonthspecificationmethods.inc");
include("advancedoptions.inc");
print '<br><input type="submit" value="Submit"><br>';

include("monthcheckboxlist.inc");
print '</form>';
?>

</div>
</body>
</html>
