<?php

## This contains the enumeration of all global variables. Global
## variables are persistent throughout the execution of a particular
## PHP script. They include values for parameters that users can alter
## (using the advanced option specifications) and some internal state
## variables controlling the number and type of queries to stats.grok.se

## Database variable (THIS MUST BE AT THE BEGINNING)
global $mysqli;
include_once("passwordFile"); ##This fetches the database,
				  ##username, and password for the MySQL connection, storing it
				  ##in the variable $mysqli
if ($mysqli->connect_errno) 
  {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
  }

## Current point in time variables (not subject to user modification,
## but require periodic manual modification, either in the database or
## in the file). Variables include $thisMonth, $mostRecentMonth,
## $thisyear, $transitionstatus

include_once("pointInTimeVariables.inc");

include_once("adviceVariables.inc");

include_once("advancedOptionVariables.inc");

include_once("nonnegotiables.inc");

include_once("queryStateVariables.inc");

?>
