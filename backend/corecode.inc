<?php
global $thismonth;
global $mostrecentmonth;
global $thisyear;
global $mysqli;
global $externalquerycount;
global $externalquerylimit;
global $hardquerylimit;
global $unavailablecount;
global $exceededquerylimitmessage;
global $purgeperiod;
global $tags_recommended;
global $alternatemonthspecs_recommended;
global $recentmonthslowdownfactor;
global $carryoverfromonemonth;
global $transitionstatus;
$externalquerycount = 0;
$externalquerylimit = 30;
$hardquerylimit = 100;
$unavailablecount = 0;
$purgeperiod = 7;
$recentmonthslowdownfactor = 4;
$transitionstatus='completed';
$exceededquerylimitmessage = 'exceeded query limit and timed out';
$tags_recommended=false;
$alternatemonthspecs_recommended = false;
$carryoverfromonemonth=false;
$mysqli = new mysqli("localhost", "wikipediaviews", "ferriporous", "wikipediaviews");
if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
$select_query = "select monthfull from months where status='present' limit 1";
$result = $mysqli->query($select_query);
$row = $result->fetch_assoc();
$thismonth = $row['monthfull'];
$select_query = "select monthfull from months where status='mostrecent' limit 1";
$result = $mysqli->query($select_query);
$row = $result->fetch_assoc();
$mostrecentmonth = $row['monthfull'];
$select_query = "select year from years where status='present' limit 1";
$result = $mysqli->query($select_query);
$row = $result->fetch_assoc();
$thisyear = $row['year'];
include("stringfunctions.inc");
include("pageviewqueries.inc");
include("displayfunctions.inc");
include("tagmanipulatives.inc");
include("advice.inc");
?>