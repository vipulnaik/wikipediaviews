<?php

global $carryoverfromonemonth;
$carryoverfromonemonth=false;

global $successfulExternalQueryCount;
$successfulExternalQueryCount = 0;

global $attemptedExternalQueryCount;
$attemptedExternalQueryCount = 0;

global $unavailableCount;
$unavailableCount = 0;

global $irretrievableCount;
$irretrievableCount = 0;

# Time taken for overall data generation
global $timeTaken;
global $bulkRetrievalTimeTaken;
global $graphTimeTaken;

global $pageSpecificationError;
$pageSpecificationError = false;

global $monthSpecificationError;
$monthSpecificationError = false;

global $yearSpecificationError;
$yearSpecificationError = false;

global $fbTokenActive;
$fbTokenActive = true;

global $statsGrokSeActive;
$statsGrokSeActive = "unknown";

global $wikimediaApiActive;
$wikimediaApiActive = true;

?>
