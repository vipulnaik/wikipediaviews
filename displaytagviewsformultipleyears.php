<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title></head>

<?php
	include_once("backend/corecode.inc");
        $formdata = true;
	$tag = $_POST['tag'];
	$yearlist = $_POST['yearlist'];
        $language = $_POST['language'];
	$displayformat = $_POST['displayformat'];
        $includetotal = "includetotal";
        $pagelistasarray = getpagelistbytag($tag,$language);
        if ($tag=='')
        {
           include("head.inc");
           print "You didn't select a tag!<br>";
           include("tagdisplaymultipleyearscontd.inc");
           exit;
        }
        if (sizeof($yearlist) == 0)
        {
              print "You didn't select any years.<br>Return to <a href=\"/multipleyears.php\">the input page</a>.";
              exit;
        }
	if ($displayformat=='csv') { printpageviewsforyearlistascsv($pagelistasarray,$yearlist,$language,$includetotal);}
	elseif ($displayformat=='htmltable') { 
           include("head.inc");  
           printpageviewsforyearlistashtmltable($pagelistasarray,$yearlist,$language,$includetotal);
           include("tagdisplaymultipleyearscontd.inc");
        }
        elseif ($displayformat=='csvtransposed') {printpageviewsforyearlistascsvtransposed($pagelistasarray,$yearlist,$language,$includetotal);}
        elseif ($displayformat=='htmltabletransposed') {
           include("head.inc");
           printpageviewsforyearlistashtmltabletransposed($pagelistasarray,$yearlist,$language,$includetotal);
           include("tagdisplaymultipleyearscontd.inc");
        }
?>
