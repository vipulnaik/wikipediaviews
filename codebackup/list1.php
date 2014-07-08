<?php
	include("corecode.inc");
	$pagescreatedsublist = array_slice($pagescreatedcompletelist,0,49);
	printpageviews($pagescreatedsublist);
?>