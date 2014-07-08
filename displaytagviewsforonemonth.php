<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title></head>

<?php
	include_once("backend/corecode.inc");
        $formdata = true;
	$tag = $_POST['tag'];
	$month = $_POST['month'];
        $language = $_POST['language'];
	$displayformat = $_POST['displayformat'];
        $explanatoryheader = "explanatoryheader";
        $includetotal = "includetotal";
        $pagelistasarray = getpagelistbytag($tag,$language);
        if ($tag=='')
        {
           include("head.inc");
           print "You didn't select a tag!<br>";
           include("tagdisplaycontd.inc");
           exit;
        }
	if ($displayformat=='csv') { printpageviewsascsv($pagelistasarray,$month,$language,$explanatoryheader,$includetotal);}
	elseif ($displayformat=='htmltable') {         
              include("head.inc"); 
              printpageviewsashtmltable($pagelistasarray,$month,$language,$explanatoryheader,$includetotal);
              include("tagdisplaycontd.inc");}
        elseif ($displayformat=='countsonlycsv') {printpageviewsascountsonlycsv($pagelistasarray,$month,$language,$explanatoryheader,$includetotal);}
        elseif ($displayformat=='countsonlyseparatelines') {
              printpageviewsascountsonlyseparatelines($pagelistasarray,$month,$language,$explanatoryheader,$includetotal);}
?>
