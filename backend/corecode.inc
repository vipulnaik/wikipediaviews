<?php
global $thismonth;
global $mysqli;
global $externalquerycount;
global $externalquerylimit;
global $exceededquerylimitmessage;
$externalquerycount = 0;
$externalquerylimit = 40;
$exceededquerylimitmessage = 'exceeded query limit and timed out';
$mysqli = new mysqli("localhost", "wikipediaviews", "redacted", "wikipediaviews");
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
$select_query = "select monthfull from months where status='present' limit 1";
$result = $mysqli->query($select_query);
$row = $result->fetch_assoc();
$thismonth = $row['monthfull'];
include("stringfunctions.inc");
include("pageviewqueries.inc");
include("displayfunctions.inc");
include("tagmanipulatives.inc");
?>