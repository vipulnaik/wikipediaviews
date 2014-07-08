<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php
   include("toggler.inc");
?></head>

<?php
	include_once("backend/corecode.inc");
        $formdata = true;
        $pagetypeadvice = "multiplemonths";
        include("retrieval/pagelistretrieval.inc");
        include("retrieval/advancedoptionretrieval.inc");

        $originalyearlist=array($thisyear);
        $allyears='allyears';
	if (!empty($_REQUEST['allyears']) or !empty($_REQUEST['yearlist']))
	{$originalyearlist = $_REQUEST['yearlist'];}
        if (!empty($_REQUEST['allyears']) or !empty($_REQUEST['yearlist']))
        {$allyears = $_REQUEST['allyears'];}
        if ($allyears == "allyears")
        {
          $yearlist = presentandpastyears_yearlist();
        }
        else
        {
          $yearlist = $originalyearlist;
        }
       if (sizeof($yearlist) == 0)
        {
              include("head.inc");
              print "You didn't select any years. Please do so below.";
              include("multipleyearsdataentry.inc");
              exit;
        }


        if ($displayformat=='htmltableautomatic') {
            include("head.inc");
            if (count($pagelistasarray) >= count($yearlist)) {
               printpageviewsforyearlistashtmltable($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
            }
            else {
               printpageviewsforyearlistashtmltabletransposed($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
            }
            include("multipleyearsdataentry.inc");
        }
	if ($displayformat=='csv') { printpageviewsforyearlistascsv($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
	elseif ($displayformat=='htmltable') { 
           include("head.inc");  
           printpageviewsforyearlistashtmltable($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
           include("multipleyearsdataentry.inc");
        }
        elseif ($displayformat=='csvtransposed') {printpageviewsforyearlistascsvtransposed($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
        elseif ($displayformat=='htmltabletransposed') {
           include("head.inc");
           printpageviewsforyearlistashtmltabletransposed($pagelistasarray,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
           include("multipleyearsdataentry.inc");
        }
?>
