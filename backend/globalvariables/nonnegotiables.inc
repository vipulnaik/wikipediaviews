<?php

##These are variables that set parameters for the query execution process, but they 
##are non-negotiable, i.e., users can neither see nor change them.

## Background query limit (applicable to archival queries)
global $backgroundQueryLimit;
$backgroundQueryLimit = 100;

## Message to display in a cell that could not be computed because the query limit was exceeded
global $exceededQueryLimitMessage;
$exceededQueryLimitMessage = 'exceeded query limit and timed out';

global $cannotRetrieveMessage;
$cannotRetrieveMessage = 'cannot retrieve this data';

global $tokenExpiredMessage;
$tokenExpiredMessage = 'authentication token expired';

## Maximum number of pages we are allowed to display
global $pageDisplayLimit;
$pageDisplayLimit = 25000;

global $cellDisplayLimit;
$cellDisplayLimit = 1000000;

global $tagProperQueryLimit;
$tagProperQueryLimit = 5000;
?>