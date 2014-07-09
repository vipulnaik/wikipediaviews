<?php
print '<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >';
print '<title>Wikipedia Views</title>';
include("toggler.inc"); ##included in all public-facing files
print '</head>';
include_once("backend/corecode.inc");
print '<body>';
include("head.inc"); ##included in all public-facing files
$formdata = false;
include("onemonthdataentry.inc");
print '</body>';
print '</html>';
?>
