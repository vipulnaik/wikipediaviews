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
# Assume token can't stay active for more than 61 minutes
if (microtime(true) - floatval($fbTokenStartTime) > 3660) {
  $fbTokenActive = false;
}

global $statsGrokSeActive;
$statsGrokSeActive = "false";

global $statsGrokSeRequested;
$statsGrokSeRequested = "false";

global $wikimediaApiActive;
$wikimediaApiActive = true;

global $backfillIfPossible;
$backfillIfPossible = false;

?>
