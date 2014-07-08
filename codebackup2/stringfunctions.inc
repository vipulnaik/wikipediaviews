<?php

function convertpagelisttoarray($pagelistasstring)
{
	if (strlen($pagelistasstring)==0) {
	  print "You didn't list any pages.<br>";
          print "Return to <a href=\"/\">the input page</a>.";
  	  exit;
	  }

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
	return "http://stats.grok.se/" . $language . "/" . $month . "/" . $page;
}

function getpageurl($page,$language)
{
	$page = str_replace(" ","_",$page);
	return "http://" . $language . ".wikipedia.org/wiki/" . $page;
}

?>