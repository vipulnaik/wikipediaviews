<?php
global $thismonth;
$thismonth = "201405";
global $connected;
$connected = false;

function connecttodb()
{
    do {
      $connected = mysql_connect(
      "localhost", "wikipediaviews", "ferriporous" );
      sleep(1);
    } while( $connected === false );
}

include("stringfunctions.inc");
include("pageviewqueries.inc");
include("displayfunctions.inc");

?>