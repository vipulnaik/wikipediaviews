<?php

##Default limit for weighted number of external queries
global $attemptedExternalQueryLimit;
$attemptedExternalQueryLimit = 330;

## Number of days after which we should fetch new data for pageview counts for the current month
global $purgeperiod;
$purgeperiod = 7;

?>