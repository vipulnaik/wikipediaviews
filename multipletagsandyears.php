<?php

print '<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >';
print '<title>Wikipedia Views: simultaneously do multiple tags and months</title>';
include("style/toggler.inc"); ##Included in all public-facing files
print '</head>';
include_once("backend/corecode.inc"); ##Backend code needed for all public-facing files
include("style/head.inc"); ##Included in all public-facing files
print '<body>';
$formdata = false;
include("inputdisplay/multipletagsandyearsdataentry.inc");
print '</body>';
print '</html>';

?>
