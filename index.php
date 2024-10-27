<?php
print '<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >';
print '<title>Wikipedia Views</title>';
include("style/toggler.inc"); ##included in all public-facing files
print '</head>';
# print '<p>The website is down for maintenance right now</p>';
include_once("backend/coreCode.inc");
include("style/head.inc"); ##included in all public-facing files
print '<body>';
$formdata = false;
include("inputDisplay/onemonthdataentry.inc");
include("backend/recentQueries.inc");
# printRecentQueries(1000, 10000);
include_once('style/anchorjs.inc');
print '</body>';
print '</html>';
?>
