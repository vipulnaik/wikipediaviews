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
        include("retrieval/monthlistretrieval.inc");

        if ($displayformat=='htmltableautomatic') {
            include("head.inc");
            if (count($pagelistasarray) >= count($monthlist)) {
               printpageviewsformonthlistashtmltable($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
            }
            else {
               printpageviewsformonthlistashtmltabletransposed($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
            }
            include("multiplemonthsdataentry.inc");
        }
	if ($displayformat=='csv') { printpageviewsformonthlistascsv($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
	elseif ($displayformat=='htmltable') { 
            include("head.inc"); 
            printpageviewsformonthlistashtmltable($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
            include("multiplemonthsdataentry.inc");}
        elseif ($displayformat=='csvtransposed') {printpageviewsformonthlistascsvtransposed($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
        elseif ($displayformat=='htmltabletransposed') {
            include("head.inc");
            printpageviewsformonthlistashtmltabletransposed($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
            include("multiplemonthsdataentry.inc");}
?>
