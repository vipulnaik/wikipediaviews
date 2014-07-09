<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title>
<?php
   include("style/toggler.inc");
?></head>

<?php
	include_once("backend/corecode.inc");
        $formdata = true;
        $pagetypeadvice = "multiplemonths";
        include("retrieval/pagelistretrieval.inc");
        include("retrieval/advancedoptionretrieval.inc");
        include("retrieval/monthlistretrieval.inc");

        if ($displayformat=='htmltableautomatic') {
            include("style/head.inc");
            if (count($pagelistasarray) >= count($monthlist)) {
               printpageviewsformonthlistashtmltable($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
            }
            else {
               printpageviewsformonthlistashtmltabletransposed($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
            }
            include("inputdisplay/multiplemonthsdataentry.inc");
        }
	if ($displayformat=='csv') { printpageviewsformonthlistascsv($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
	elseif ($displayformat=='htmltable') { 
            include("style/head.inc"); 
            printpageviewsformonthlistashtmltable($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
            include("inputdisplay/multiplemonthsdataentry.inc");}
        elseif ($displayformat=='csvtransposed') {printpageviewsformonthlistascsvtransposed($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);}
        elseif ($displayformat=='htmltabletransposed') {
            include("style/head.inc");
            printpageviewsformonthlistashtmltabletransposed($pagelistasarray,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat);
            include("inputdisplay/multiplemonthsdataentry.inc");}
?>
