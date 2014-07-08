<?php
global $thismonth;
$thismonth = "201405";
global $connected;
$connected = false;
global $mysqli;
$mysqli = new mysqli("localhost", "wikipediaviews", "ferriporous", "wikipediaviews");

include("stringfunctions.inc");
include("pageviewqueries.inc");
include("displayfunctions.inc");

?>