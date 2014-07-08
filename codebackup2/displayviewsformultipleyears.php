<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title></head>

<?php
	include("head.inc");
        include("corecode.inc");
	$pagelistasstring = $_POST['pagelistasstring'];
	$yearlist = $_POST['yearlist'];
        $language = $_POST['language'];
	$displayformat = $_POST['displayformat'];
        $includetotal = $_POST['includetotal'];
        $pagelistasarray = convertpagelisttoarray($pagelistasstring);
        if (sizeof($pagelistasarray) == 0)
        {
              print "You didn't list any pages.<br>Return to <a href=\"/multipleyears.php\">the input page</a>.";
              exit;
        }

        if (sizeof($yearlist) == 0)
        {
              print "You didn't select any years.<br>Return to <a href=\"/multipleyears.php\">the input page</a>.";
              exit;
        }
	if ($displayformat=='csv') { printpageviewsforyearlistascsv($pagelistasarray,$yearlist,$language,$includetotal);}
	elseif ($displayformat=='htmltable') { printpageviewsforyearlistashtmltable($pagelistasarray,$yearlist,$language,$includetotal);}
        elseif ($displayformat=='csvtransposed') {printpageviewsforyearlistascsvtransposed($pagelistasarray,$yearlist,$language,$includetotal);}
        elseif ($displayformat=='htmltabletransposed') {printpageviewsforyearlistashtmltabletransposed($pagelistasarray,$yearlist,$language,$includetotal);}
?>
