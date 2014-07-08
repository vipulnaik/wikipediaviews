<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title></head>

<?php
	include_once("backend/corecode.inc");
        $formdata = true;
	$tag = $_POST['tag'];
	$monthlist = $_POST['monthlist'];
        $language = $_POST['language'];
	$displayformat = $_POST['displayformat'];
        $includetotal = "includetotal";
        $pagelistasarray = getpagelistbytag($tag,$language);
        if ($tag=='')
        {
           include("head.inc");
           print "You didn't select a tag!<br>";
           include("tagdisplaymultiplemonthscontd.inc");
           exit;
        }
        if (sizeof($monthlist) == 0)
        {
              include("head.inc");
              print "You didn't select any months.<br>Return to <a href=\"/tagdisplaymultiplemonths.php\">the input page</a>.";
              include("tagdisplaymultiplemonthscontd.inc");
              exit;
        }
	if ($displayformat=='csv') { printpageviewsformonthlistascsv($pagelistasarray,$monthlist,$language,$includetotal);}
	elseif ($displayformat=='htmltable') { 
            include("head.inc"); 
            printpageviewsformonthlistashtmltable($pagelistasarray,$monthlist,$language,$includetotal);
            include("tagdisplaymultiplemonthscontd.inc");}
        elseif ($displayformat=='csvtransposed') {printpageviewsformonthlistascsvtransposed($pagelistasarray,$monthlist,$language,$includetotal);}
        elseif ($displayformat=='htmltabletransposed') {
            include("head.inc");
            printpageviewsformonthlistashtmltabletransposed($pagelistasarray,$monthlist,$language,$includetotal);
            include("tagdisplaymultiplemonthscontd.inc");}
?>
