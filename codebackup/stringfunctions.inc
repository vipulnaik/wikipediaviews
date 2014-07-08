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
        if (sizeof($pagelistasarray) > 50) 
        {
              print "Since the number of pages listed exceeded 50, we pruned to the first 50 pages in the list."; 
              $pagelistasarray = array_slice($pagelistasarray,0,49);
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