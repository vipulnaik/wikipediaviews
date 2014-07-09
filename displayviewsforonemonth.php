<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php
   include("style/toggler.inc");
?></head>

<?php
	include_once("backend/corecode.inc");
        $formdata = true;
        $pagetypeadvice="onemonth";
        include("retrieval/pagelistretrieval.inc");
        include("retrieval/advancedoptionretrieval.inc");

        $month = $mostrecentmonth;
        if (!empty($_REQUEST['month']))
        {$month = $_REQUEST['month'];}
        $monthlist = array($month);

	if ($displayformat=='csv') { printpageviewsascsv($pagelistasarray,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
	elseif ($displayformat=='htmltable') {         
              include("style/head.inc"); 
              printpageviewsformonthlistashtmltable($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
              $originalmonthlist = $monthlist;
              $displayformat='htmltableautomatic';
              $carryoverfromonemonth=true;
              include("inputdisplay/multiplemonthsdataentry.inc");}
        elseif ($displayformat=='countsonlycsv') {printpageviewsascountsonlycsv($pagelistasarray,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
        elseif ($displayformat=='countsonlyseparatelines') {
              printpageviewsascountsonlyseparatelines($pagelistasarray,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
?>
