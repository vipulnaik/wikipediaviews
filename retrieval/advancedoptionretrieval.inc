<?php
	##Set defaults
	if ($pagetypeadvice == 'multiplemonths' or $pagetypeadvice == 'multipleyears')
	{
		$displayformat = 'htmltableautomatic';
	}
	if ($pagetypeadvice == 'onemonth')
	{
		$displayformat = 'htmltable';
	}
        $numericdisplayformat = 'kmb';
        $userspecifiedquerylimit = $weightedexternalquerylimit;
        $explanatoryheader="explanatoryheader"; ##Not currently user-updatable
        $includetotal = "includetotal"; ##Not currently user-updatable

	##Retrieve user requests and update defaults if necessary

        if (!empty($_REQUEST['displayformat']))
	{$displayformat = $_REQUEST['displayformat'];}

        if (!empty($_REQUEST['numericdisplayformat']))
        {$numericdisplayformat = $_REQUEST['numericdisplayformat'];}

        if (!empty($_REQUEST['userspecifiedquerylimit']))
        {$userspecifiedquerylimit = $_REQUEST['userspecifiedquerylimit'];}
        if ($userspecifiedquerylimit !== '') {$weightedexternalquerylimit = intval($userspecifiedquerylimit);}

        if (!empty($_REQUEST['purgeperiod']))
        {$purgeperiod = intval($_REQUEST['purgeperiod']);}
?>
