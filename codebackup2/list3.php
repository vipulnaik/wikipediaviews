<?php
	include("corecode.inc");
	$pagescreatedsublist = array_slice($pagescreatedcompletelist,100,sizeof($pagescreatedcompletelist)-1);
	printpageviews($pagescreatedsublist);
?>