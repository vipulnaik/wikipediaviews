<?php

function convertpagelisttoarray($pagelistasstring)
{
	$pagelistasinput = isset($pagelistasstring)?$pagelistasstring:"";
        $pagelistasarray = array_unique(explode("\n", str_replace("\r", "", $pagelistasinput)));
        foreach (array_keys($pagelistasarray, "") as $key) {
          unset($pagelistasarray[$key]);
        }
	foreach($pagelistasarray as &$page)
	{
		$page = trim($page," \t\n\r\0\x0B");
        }     
	return $pagelistasarray;
}

function getpageviewsurl($page,$month,$language)
{
	$page = str_replace(" ","_",$page);
	$page = str_replace("'","%27",$page);
	return "http://stats.grok.se/" . $language . "/" . $month . "/" . $page;
}

function getannualpageviewsurl($page,$year,$language)
{
	return "http://wikipediaviews.org/displayviewsformultiplemonths.php?year=".$year."&page=".$page;
}

function getpageurl($page,$language)
{
	$page = str_replace(" ","_",$page);
	return "http://" . $language . ".wikipedia.org/wiki/" . $page;
}

function convertlisttoquotedcsvstring($listasarray)
{
	$listasquotedcsvstring = "'".$listasarray[0]."'";
	for($i = 1;$i < sizeof($listasarray);$i++)
	{
		$listasquotedcsvstring .= ",'".$listasarray[$i]."'";
	}
	return $listasquotedcsvstring;
}

function numericdisplay($number,$numericdisplayformat)
{
	if ($numericdisplayformat=='fullprecision')
	{
		return $number;
	}
	if ($numericdisplayformat=='kmb')
	{
		return numericdisplaykmb($number);
	}
	if ($numericdisplayformat=='log')
	{
		return numericdisplaylog($number);
	}
	return $number;
}
function numericdisplaykmb($number)
{
	$number_int = intval($number);
	if ($number_int < 1000)
	{
		return $number;
	}
	if ($number_int >= 1000 and $number_int < 9950)
	{
		$number_k = round((floatval ($number_int))/1000,1);
		return (strval($number_k)."K");
	}
	if ($number_int >= 10000 and $number_int < 999500)
	{
		$number_k = round((floatval ($number_int))/1000,0);
		return (strval($number_k)."K");
	}
	if ($number_int >= 999500 and $number_int < 9950000)
	{
		$number_m = round((floatval ($number_int))/1000000,1);
		return (strval($number_m)."M");
	}
	if ($number_int >= 9950000 and $number_int < 999500000)
	{
		$number_m = round((floatval ($number_int))/1000000,0);
		return (strval($number_m)."M");
	}
	if ($number_int >= 999500000 and $number_int < 9950000000)
	{
		$number_b = round((floatval ($number_int))/1000000000,1);
		return (strval($number_b)."B");
	}
	if ($number_int >= 9950000000)
	{
		$number_b = round((floatval ($number_int))/1000000000,0);
		return (strval($number_b)."B");
	}
	return $number;
}

function numericdisplaylog($number)
{
	if ($number == 0) return "-infinity";
	return round(log($number,10),1);
}

function monthviewtooltip($number)
{
	$tooltipstring = $number;
	$tooltipstring .= " views (click to view day-wise breakdown on stats.grok.se)";
	return $tooltipstring;
}

function yearviewtooltip($number)
{
	$tooltipstring = $number;
	$tooltipstring .= " (click to view month-wise breakdown on this site)";
	return $tooltipstring;
}

?>