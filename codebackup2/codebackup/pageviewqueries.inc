<?php

function getpageviewsonline($page, $month, $language)
{
	$url = getpageviewsurl($page,$month,$language);
	$html = file_get_contents($url);
	preg_match('/(?<=\bhas been viewed)\s+\K[^\s]+/',$html,$numberofpageviews);
	return $numberofpageviews[0];
}

function getpageviewsfromdb($page,$month,$langage)
{
	global $connected;
	if ($connected === false) {connecttodb();}
	
}
function getpageviews($page,$month,$language)
{
	global $connected;
        if ($month==$thismonth) {return getpageviewsonline($page,$month,$language);}
#	if ($connected === false) {connecttodb();}
	return getpageviewsonline($page,$month,$language);
}

function getpageviewsthismonth($pagename,$language)
{
	global $thismonth;
	return getpageviews($pagename,$thismonth,$language);
}

?>