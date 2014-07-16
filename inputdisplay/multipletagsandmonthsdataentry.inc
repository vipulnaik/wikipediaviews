<?php

##inc file for data entry for multiple months.

##Included from: multipletagsandmonths.php, displayviewsformultipletagsandmonths.php

##Sends form to: displayviewsformultipetagsandmonths.php

##Includes: (fillin)

$pagetypeadvice = "multipletagsandmonths";
print '<form method="post" name="pagecountinfo" action="displayviewsfor'.$pagetypeadvice.'.php">';

include("tagdropdownselectmultiple.inc");
include("alternatemonthspecificationmethods.inc");
include("advancedoptions.inc");
print '<br><input type="submit" value="Submit"><br>';

include("monthcheckboxlist.inc");
print '</form>';
?>

</div>
</body>
</html>
