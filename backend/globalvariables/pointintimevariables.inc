<?php

## Current month variable (note that the current month needs to be
## updated through the database once a month)

global $thismonth;
$select_query = "select monthfull from months where status='present' limit 1";
$result = $mysqli->query($select_query);
$row = $result->fetch_assoc();
$thismonth = $row['monthfull'];

## Most recent month variable (note that the most recent month needs to be
## updated through the database once a month)

global $mostrecentmonth;
$select_query = "select monthfull from months where status='mostrecent' limit 1";
$result = $mysqli->query($select_query);
$row = $result->fetch_assoc();
$mostrecentmonth = $row['monthfull'];

## Current year variable (note that the current year needs to be
## updated through the database once a year)

global $thisyear;
$select_query = "select year from years where status='present' limit 1";
$result = $mysqli->query($select_query);
$row = $result->fetch_assoc();
$thisyear = $row['year'];

## Most recent year variable (needs to be updated through the database once a year)

global $mostrecentyear;
$select_query = "select year from years where status='mostrecent' limit 1";
$result = $mysqli->query($select_query);
$row = $result->fetch_assoc();
$mostrecentyear = $row['year'];

## List of number of days for all months

global $numberofdays_allmonths;
$select_query = "select monthfull, numberofdays from months where status!='future';";
$result = $mysqli->query($select_query);
for ($i = 0;$i < $result -> num_rows; $i++)
{
  $row = $result->fetch_assoc();
  $numberofdays_allmonths[$row['monthfull']] = $row['numberofdays']; 
}	

## Transition status: This variable has three states: 'tobegin'
## (indicating that a new month has begun per the calendar but the
## month has not been updated in the database), 'begun' indicating
## that the database has been updated but the archival of data hasn't
## caught up with the new month, and 'completed' indicating that all
## is hunky-dory.

## Used in inputdisplay/head.inc: in case the variable has state 'tobegin' or 'begun',
## a corresponding message is dispayed below the header menu.

global $transitionstatus;
$transitionstatus='completed'; 

?>