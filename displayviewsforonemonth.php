<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title></head>

<?php
	include_once("backend/corecode.inc");
        $formdata = true;
	$pagelistasstring = $_POST['pagelistasstring'];
	$month = $_POST['month'];
        $language = $_POST['language'];
	$displayformat = $_POST['displayformat'];
        $numericdisplayformat = $_POST['numericdisplayformat'];
        $tag = $_POST['tag'];
        $userspecifiedquerylimit = $_POST['userspecifiedquerylimit'];
        if ($userspecifiedquerylimit != '') {$externalquerylimit = intval($userspecifiedquerylimit);}
        $explanatoryheader = "explanatoryheader";
        $includetotal = "includetotal";
        if (strlen(trim($pagelistasstring," \t\n\r\0\x0B"))==0 and $tag=='')
        {
          include("head.inc");
	  print "You didn't list any pages or select any tags.<br>";
          include("onemonthcontd.inc");
  	  exit;
	}
        if (strlen(trim($pagelistasstring," \t\n\r\0\x0B"))>0 and $tag!='')
        {
          include("head.inc");
	  print "You listed page(s) <em>and</em> selected a tag. You can do only one at a time. Please modify the form below appropriately.<br>";
          include("onemonthcontd.inc");
  	  exit;
	}
        if (strlen(trim($pagelistasstring," \t\n\r\0\x0B"))>0)
        {
        $pagelistasarray = convertpagelisttoarray($pagelistasstring);
        }
        if ($tag!='')
        {
        $pagelistasarray = getpagelistbytag($tag,$language);
        if (sizeof($pagelistasarray) == 0)
          {
           include("head.inc");
           print "Although the tag is valid, there are no pages for the tag-language <em>combination</em>.<br>";
           include("multiplemonthscontd.inc");
           exit;
          }
        }
	if ($displayformat=='csv') { printpageviewsascsv($pagelistasarray,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
	elseif ($displayformat=='htmltable') {         
              include("head.inc"); 
              printpageviewsformonthlistashtmltable($pagelistasarray,array($month),$language,$explanatoryheader,$includetotal,$numericdisplayformat);
              include("onemonthcontd.inc");}
        elseif ($displayformat=='countsonlycsv') {printpageviewsascountsonlycsv($pagelistasarray,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
        elseif ($displayformat=='countsonlyseparatelines') {
              printpageviewsascountsonlyseparatelines($pagelistasarray,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
?>
