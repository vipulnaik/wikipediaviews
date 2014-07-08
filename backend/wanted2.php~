<?php
  include_once("corecode.inc");
  global $parity;
  global $exceededquerylimitmessage;
  global $externalquerylimit;
  global $externalquerycount;
  $externalquerycount = 0;
  $parity = true;
  $keepgoing = true;
  $sleepcounter = 0;
  while ($sleepcounter < 7 and $externalquerycount < $externalquerylimit and $keepgoing)
  {
	$keepgoing = fillinwantedviewcounts($externalquerylimit - $externalquerycount);
	sleep(7);
	$sleepcounter++;
  }
  print "Reporting success!";
?>
