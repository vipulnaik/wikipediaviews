<?php
global $thismonth;
$thismonth = "201405";
global $connected;
$connected = false;

function convertpagelisttoarray($pagelistasstring)
{
	if (strlen($pagelistasstring)==0) {
	  print "You didn't list any pages.<br>";
          print "Return to <a href=\"/\">the input page</a>.";
  	  exit;
	  }

	$pagelistasinput = isset($pagelistasstring)?$pagelistasstring:"";
        $pagelistasarray = array_unique(explode("\n", str_replace("\r", "", $pagelistasinput)));
        foreach (array_keys($pagelistasarray, "") as $key) {
          unset($pagelistasarray[$key]);
        }
        if (sizeof($pagelistasarray) > 50) 
        {
              print "Since the number of pages listed exceeded 50, we pruned to the first 50 pages in the list."; 
              $pagelistasarray = array_slice($pagelistasarray,0,49);
        }
	return $pagelistasarray;
}
function connecttodb()
{
    do {
      $connected = mysql_connect(
      "localhost", "wikipediaviews", "ferriporous" );
      sleep(1);
    } while( $connected === false );
}

function getpageviewsurl($page,$month,$language)
{
	$page = str_replace(" ","_",$page);
	return "http://stats.grok.se/" . $language . "/" . $month . "/" . $page;
}

function getpageurl($page,$language)
{
	$page = str_replace(" ","_",$page);
	return "http://" . $language . ".wikipedia.org/wiki/" . $page;
}
function getpageviewsonline($page, $month, $language)
{
	$url = getpageviewsurl($page,$month,$language);
	$html = file_get_contents($url);
	preg_match('/(?<=\bhas been viewed)\s+\K[^\s]+/',$html,$numberofpageviews);
	return $numberofpageviews[0];
}

function getpageviewsfromdb($page,$month,$langage)
{
	global $connected;
	if ($connected === false) {connecttodb();}
	
}
function getpageviews($page,$month,$language)
{
	global $connected;
        if ($month==$thismonth) {return getpageviewsonline($page,$month,$language);}
#	if ($connected === false) {connecttodb();}
	return getpageviewsonline($page,$month,$language);
}

function getpageviewsthismonth($pagename,$language)
{
	global $thismonth;
	return getpageviews($pagename,$thismonth,$language);
}

function printpageviewsascsv($pagelist,$month,$language,$explanatoryheader,$includetotal)
{
if ($explanatoryheader != 'noheader') {print "Page name,Pageviews in month ".$month."<br>";}
$total=0;
foreach($pagelist as $page)
{
	$viewcount = getpageviews($page,$month,$language);
	if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
	$stringtoprint = $page."," . $viewcount ."<br>";
	print $stringtoprint;
}
if ($includetotal=='includetotal') {print "Total,".$total;}
}

function printpageviewsashtmltable($pagelist,$month,$language,$explanatoryheader,$includetotal)
{
print "<table border=\"1\">";
if ($explanatoryheader != 'noheader') {print "<tr><th>Page name</th><th>Pageviews in month ".$month."</th></tr>";}
$total=0;
foreach($pagelist as $page)
{
	$viewcount = getpageviews($page,$month,$language);
	if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
	$stringtoprint = "<tr><td><a href=\"" . getpageurl($page,$language) . "\">" . $page . "</a></td><td><a href=\"" . getpageviewsurl($page,$month,$language) . "\">" . $viewcount . "</a></td></tr>";
	print $stringtoprint;
}
if ($includetotal=='includetotal') {print "<tr><th>Total</th><th>".$total."</th></tr>";}
print "</table>";
}

function printpageviewsascountsonlycsv($pagelist,$month,$language,$explanatoryheader,$includetotal)
{
if ($explanatoryheader != 'noheader') {print "Pageviews in month ".$month.":<br>";}
$total=0;
foreach($pagelist as $page)
{
	$viewcount = getpageviews($page,$month,$language);
	if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
	$stringtoprint = $viewcount.",";
	print $stringtoprint;
}
if ($includetotal=='includetotal') {print "<tr><th>Total</th><th>".$total."</th></tr>";}
}

function printpageviewsascountsonlyseparatelines($pagelist,$month,$language,$explanatoryheader,$includetotal)
{
if ($explanatoryheader != 'noheader') {print "Pageviews in month ".$month.":<br>";}
$total=0;
foreach($pagelist as $page)
{
	$viewcount = getpageviews($page,$month,$language);
	if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
	$stringtoprint = $viewcount."<br>";
	print $stringtoprint;
}
if ($includetotal=='includetotal') {print "<tr><th>Total</th><th>".$total."</th></tr>";}
}

function printpageviewsformonthlistascsv($pagelist,$monthlist,$language,$includetotal)
{
$headerstring = "Page name";
foreach($monthlist as $month)
{
	$headerstring .= ",Pageviews in month ".$month;
}
if ($includetotal=='includetotal') {$headerstring .=",Total";}
$headerstring.="<br>";
print $headerstring;
foreach($pagelist as $page)
{
	$stringtoprint = $page;
	$total = 0;
	foreach($monthlist as $month)
	{
		$viewcount = getpageviews($page,$month,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= ",".$viewcount;
	}
	if ($includetotal=='includetotal') {$stringtoprint .=",".$total;}
	$stringtoprint .="<br>";
	print $stringtoprint;
}
}

function printpageviewsformonthlistashtmltable($pagelist,$monthlist,$language,$includetotal)
{
print "<table border=\"1\">";
$headerstring = "<tr><th>Page name</th>";
foreach($monthlist as $month)
{
	$headerstring .= "<th>Pageviews in month ".$month."</th>";
}
if ($includetotal=='includetotal') {$headerstring .="<th>Total</th>";}
$headerstring.="</tr>";
print $headerstring;
foreach($pagelist as $page)
{
	$total = 0;
	$stringtoprint = "<tr><td><a href=\"".getpageurl($page,$language)."\">".$page."</a></td>";
	foreach($monthlist as $month)
	{
		$viewcount = getpageviews($page,$month,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= "<td><a href=\"".getpageviewsurl($page,$month,$language)."\">".$viewcount."</a></td>";

	}
	if ($includetotal=='includetotal') {$stringtoprint .="<td>".$total."</td>";}
	$stringtoprint .="</tr>";
	print $stringtoprint;
}
}

function printpageviewsformonthlistascsvtransposed($pagelist,$monthlist,$language,$includetotal)
{
$headerstring = "Month";
foreach($pagelist as $page)
{
	$headerstring .= ",Views of page ".$page;
}
if ($includetotal=='includetotal') {$headerstring .=",Total";}
$headerstring.="<br>";
print $headerstring;
foreach($monthlist as $month)
{
	$stringtoprint = $month;
	$total = 0;
	foreach($pagelist as $page)
	{
		$viewcount = getpageviews($page,$month,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= ",".$viewcount;
	}
	if ($includetotal=='includetotal') {$stringtoprint .=",".$total;}
	$stringtoprint .="<br>";
	print $stringtoprint;
}
}

function printpageviewsformonthlistashtmltabletransposed($pagelist,$monthlist,$language,$includetotal)
{
print "<table border=\"1\">";
$headerstring = "<tr><th>Month</th>";
foreach($pagelist as $page)
{
	$headerstring .= "<th>Views of page <a href=\"". getpageurl($page,$language). "\">" . $page."</a></th>";
}
if ($includetotal=='includetotal') {$headerstring .="<th>Total</th>";}
$headerstring.="</tr>";
print $headerstring;
foreach($monthlist as $month)
{
	$stringtoprint = "<tr><td>".$month."</td>";
	$total = 0;
	foreach($pagelist as $page)
	{
		$viewcount = getpageviews($page,$month,$language);
		if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
		$stringtoprint .= "<td><a href=\"".getpageviewsurl($page,$month,$language)."\">".$viewcount."</a></td>";
	}
	if ($includetotal=='includetotal') {$stringtoprint .="<td>".$total."</td>";}
	$stringtoprint .="</tr>";
	print $stringtoprint;
}
}

$pagescreatedcompletelist = array("Room_for_more_funding","Earning_to_give","VillageReach","Schistosomiasis_Control_Initiative","GiveDirectly","Deworm_the_World_Initiative","Good_Ventures","Mulago_Foundation","Jasmine_Social_Investments","Root_Capital","Living_Goods","Peery_Foundation","Stanford_Social_Innovation_Review","Center_for_High_Impact_Philanthropy","Silicon_Valley_Community_Foundation","Millions_Saved","Disease_Control_Priorities_Project","Michael_Clemens","PandoDaily","Chamath_Palihapitiya","Joe_Green_(entrepreneur)","Correlation_Ventures","Floodgate_Fund","Lightbank","FWD.us","Bleeding-heart_libertarianism","Alex_Nowrasteh","Garett_Jones","Ilya_Somin","Michael_Huemer","Anthony_Gregory","The_Problem_of_Political_Authority","Ethical_Intuitionism_(book)","Democracy_and_Political_Ignorance","Libertarianism.org","The_Independent_Review","Cato_Unbound","EconLog","Notre_Dame_Philosophical_Reviews","Demography_(journal)","Population_Association_of_America","Selfish_Reasons_to_Have_More_Kids","Substantial_Presence_Test","Average_is_Over","Exodus:_How_Migration_is_Changing_Our_Word","Immigration_Policy_Center","Thiel_Fellowship","Breakout_Labs","Bridge_International_Academies","Code.org","Internet.org","Facebook_Zero","Google_Free_Zone","Shasta_Ventures","Passion_Capital","Eden_Ventures","Facebook_for_SIM","Coinfloor","Dennard_scaling","Cal_Newport","Art_Carden","Allen_Institute_for_Artificial_Intelligence","Timeline_of_Twitter","Spark_Capital","Jelly_(app)","Spread_Networks","Cycle_Computing","Timeline_of_Google_Search","Timeline_of_machine_translation","Bourgeois_Dignity","Facebook_Paper","Benjamin_Powell","Nanex","Timeline_of_web_search_engines","AlchemyAPI","Cortica","Semantria","Quantum_Artificial_Intelligence_Lab","Giving_Tuesday","Secret_(app)","What_to_Expect_When_No_One's_Expecting","The_Empty_Cradle","Chris_Blattman","Seeing_Like_a_State","Losing_Ground_(book)","The_Energy_Journal","DICE_model","Resource_and_Energy_Economics","The_Tyranny_of_Experts","The_Triple_Package","Thiel_Foundation","Laura_and_John_Arnold_Foundation","Vernon_K._Krieble_Foundation","Moving_Out_of_Poverty","Campbell_Collaboration","The_Last_Mile_(prison_rehabilitation_program)","Draper_Richards_Kaplan_Foundation","Borderless_Economics","KNOMAD","ECB_Survey_of_Professional_Forecasters","Blue_Chip_Economic_Indicators","Consensus_Economics","FocusEconomics","Electronic_Federal_Tax_Payment_System","Economic_Outlook_(OECD_Publication)","OECD_Main_Economic_Indicators","Livingston_Survey","Survey_of_Current_Business","Science_fiction_prototyping","Federal_Reserve_Archival_System_for_Economic_Research","Federal_Reserve_Bulletin","THORPEX","Monthly_Climatic_Data_for_the_World","Best_on_the_Street","Greenbook","THORPEX_Interactive_Grand_Global_Ensemble","North_American_Ensemble_Forecast_System","Potential_predictability","Spyros_Makridakis","Makridakis_Competitions","Western_Blue_Chip_Economic_Forecast","Wall_Street_Journal_Economic_Survey","Business_Review","Student_Adaptation_to_College_Questionnaire","National_Survey_of_Family_Growth","National_Vital_Statistics_System","National_Summer_Learning_Association");

?>