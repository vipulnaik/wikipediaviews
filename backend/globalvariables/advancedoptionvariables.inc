<?php

##Default limit for number of external queries
global $externalquerylimit;
$externalquerylimit = 30;

## Number of days after which we should fetch new data for pageview counts for the current month
global $purgeperiod;
$purgeperiod = 7;

?>