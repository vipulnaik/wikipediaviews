<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Experimental pageview count fetcher: results</title></head>

<?php
	include("corecode.inc");
	$pagelistasstring = $_POST['pagelistasstring'];
	$month = $_POST['month'];
        $language = $_POST['language'];
	$displayformat = $_POST['displayformat'];
        $explanatoryheader = $_POST['explanatoryheader'];
        $includetotal = $_POST['includetotal'];
        $pagelistasarray = convertpagelisttoarray($pagelistasstring);
	if ($displayformat=='csv') { printpageviewsascsv($pagelistasarray,$month,$language,$explanatoryheader,$includetotal);}
	elseif ($displayformat=='htmltable') { printpageviewsashtmltable($pagelistasarray,$month,$language,$explanatoryheader,$includetotal);}
        elseif ($displayformat=='countsonlycsv') {printpageviewsascountsonlycsv($pagelistasarray,$month,$language,$explanatoryheader,$includetotal);}
        elseif ($displayformat=='countsonlyseparatelines') {printpageviewsascountsonlyseparatelines($pagelistasarray,$month,$language,$explanatoryheader,$includetotal);}
?>
