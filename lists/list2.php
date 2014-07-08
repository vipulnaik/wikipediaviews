<?php
	include("corecode.inc");
	$pagescreatedsublist = array_slice($pagescreatedcompletelist,50,99);
	printpageviews($pagescreatedsublist);
?>