<?php

include_once("globalvariables/passwordfile.inc");

function checksizes($pageortaglist,$monthoryearlist) {
  global $pagedisplaylimit;
  global $celldisplaylimit;
  $numberofpagesortags = count($pageortaglist);
  $numberofmonthsoryears = count($monthoryearlist);
  if ($numberofpagesortags > $pagedisplaylimit)
    {
      print "The number of pages or tags, namely ".$numberofpagesortags.", exceeds ".$pagedisplaylimit.", our hard limit on the number of pages that can be displayed.";
      return 1;
    }
  $numberofcells = $numberofpagesortags * $numberofmonthsoryears;
  if ($numberofcells > $celldisplaylimit)
    {
      print "The total number of cells to display, namely ".$numberofcells.", exceeds ".$celldisplaylimit.", our hard limit on the number of cells that can be displayed.";
      return 2;
    }
  return 0;
}
function totalsandpercentages($pageortaglist,$monthoryearlist,$viewcountarray) {
  $grand_total = 0;
  foreach ($pageortaglist as $pageortag)#Computes page totals and grand total
    {
      $pageortag_total[$pageortag] = 0;
      foreach ($monthoryearlist as $monthoryear)
	{
	  $pageortag_total[$pageortag] += intval($viewcountarray[$pageortag][$monthoryear]);
	  
	}
      $grand_total += $pageortag_total[$pageortag];
    }
  foreach ($monthoryearlist as $monthoryear)#Computes month or year totals
    {
      $monthoryear_total[$monthoryear] = 0;
      foreach ($pageortaglist as $pageortag)
	{
	  $monthoryear_total[$monthoryear] += intval($viewcountarray[$pageortag][$monthoryear]);
	}
    }
  
  foreach ($pageortaglist as $pageortag)#Computes page percentages
    {
      if ($grand_total == 0)
	{
	  $pageortag_percentage[$pageortag] = 'undefined';
	}
      else
	{
	  $pageortag_percentage[$pageortag] = round(100 * floatval($pageortag_total[$pageortag])/floatval($grand_total),1);
	}
    }
  
  foreach ($monthoryearlist as $monthoryear)#Computes month or year percentages
    {
      if ($grand_total == 0)
		{
		  $monthoryear_percentage[$monthoryear] = 'undefined';
		}
      else
	{
	  $monthoryear_percentage[$monthoryear] = round(100.0 * floatval($monthoryear_total[$monthoryear])/floatval($grand_total),1);
	}
    }
  
  return array($grand_total,$pageortag_total,$monthoryear_total,$pageortag_percentage,$monthoryear_percentage);
}

function printmonthviewcount($page,$month,$language,$drilldown,$viewcount,$numericdisplayformat) {
  return '<td align="right"><a href="'.getpageviewsurl($page,$month,$language,$drilldown).'" title="'.monthviewtooltip($viewcount).'">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';
}

function printyearviewcount($page,$year,$language,$drilldown,$viewcount,$numericdisplayformat) {
  return '<td align="right"><a href="'.getannualpageviewsurl($page,$year,$language,$drilldown).'" title="'.yearviewtooltip($viewcount).'">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';
}

function printtagviewcount($tag,$month,$language,$drilldown,$viewcount,$numericdisplayformat) {
  return '<td align="right"><a href="'.gettagviewsurl($tag,$month,$language,$drilldown).'" title="'.$viewcount.' (click for data on individual pages)">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';
}

function printtagviewcountbyyear($tag,$year,$language,$drilldown,$viewcount,$numericdisplayformat) {
  return '<td align="right"><a href="'.getannualtagviewsurl($tag,$year,$language,$drilldown).'" title="'.$viewcount.' (click for data on individual pages)">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';
}

function printpageviewsformonthoryearlistashtmltable($pageortaglist,$monthoryearlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageortagadvice='page',$monthoryearadvice='month') {
  flush();
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageortaglist,$monthoryearlist);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageortagadvice=='page' and $monthoryearadvice=='month') {
    $viewcountarray = viewcountarraybymonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  } elseif ($pageortagadvice=='page' and $monthoryearadvice=='year') {
    $viewcountarray = viewcountarraybyyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  } elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month') {
      $viewcountarray = viewcountarraybytagandmonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  } elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year') {
    $viewcountarray = viewcountarraybytagandyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  }
  $totalsandpercentages_array = totalsandpercentages($pageortaglist,$monthoryearlist,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageortag_total = $totalsandpercentages_array[1];
  $monthoryear_total = $totalsandpercentages_array[2];
  $pageortag_percentage = $totalsandpercentages_array[3];
  $monthoryear_percentage = $totalsandpercentages_array[4];

  #Tag list fetching
  if ($pageortagadvice=='page')
    $taglistbypages = gettaglistbypagelist($pageortaglist,$language);

  #Pre-table warnings

  if ($monthoryearadvice=='year') {
    print "<strong>For speed and consistency reasons, we do <em>not</em> include the current month in totals for the current year</strong><br><br>";
  }
  flush();
  ##Table header row
    
  print '<table border="1">';
  $headerstring = "<tr><th>".ucfirst($pageortagadvice)." name</th>";
  $descriptor = getDescriptor($drilldown);

  foreach($monthoryearlist as $monthoryear) {
    $headerstring .= "<th>".$descriptor." in ".$monthoryearadvice." ".$monthoryear."</th>";
  }
  if ($includetotal=='includetotal' and count($monthoryearlist) > 1) {
    $headerstring .="<th>Total</th>";
  }
  if (count($pageortaglist) > 1) {
    $headerstring.="<th>Percentage</th>";
  }

  #Tag list column printing
  if ($pageortagadvice == 'page')
      $headerstring .= "<th>Tags</th>";
  
  $headerstring .= "</tr>";
  print $headerstring;
  
  ##Data rows
  foreach($pageortaglist as $pageortag) #Prints one row of the table
    {
      if ($pageortagadvice=='page')
	{
	  $pageortag_rowstring = '<tr><td><a href="'.getpageurl($pageortag,$language).'" title = "'.$pageortag.' (read page on Wikipedia)">'.$pageortag.'</a></td>';
	}
      elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
	{
	  $pageortag_rowstring = '<td><a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageortag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageortag.'</a></td>';
	}		       
      elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
	{
	  $pageortag_rowstring = '<td><a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageortag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageortag.'</a></td>';
	}
      foreach($monthoryearlist as $monthoryear) #Computes one cell entry
	{
	  $viewcount = $viewcountarray[$pageortag][$monthoryear];
	  if ($pageortagadvice=='page' and $monthoryearadvice=='month')
	    {
	      $pageortag_rowstring .= printmonthviewcount($pageortag,$monthoryear,$language,$drilldown,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageortagadvice=='page' and $monthoryearadvice=='year')
	    {
	      $pageortag_rowstring .= printyearviewcount($pageortag,$monthoryear,$language,$drilldown,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
	    {
	      $pageortag_rowstring .= printtagviewcount($pageortag,$monthoryear,$language,$drilldown,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
	    {
	      $pageortag_rowstring .= printtagviewcountbyyear($pageortag,$monthoryear,$language,$drilldown,$viewcount,$numericdisplayformat);
	    }

	}
      if ($includetotal=='includetotal' and count($monthoryearlist) > 1) 
	$pageortag_rowstring .='<td align="right"><strong><element title="'.$pageortag_total[$pageortag].'">'.numericdisplay($pageortag_total[$pageortag],$numericdisplayformat).'</element></strong></td>';
      if (count($pageortaglist) > 1) 
	$pageortag_rowstring .= '<td align="right"><strong>'.$pageortag_percentage[$pageortag].'</strong></td>';
      if ($pageortagadvice == 'page')
	{
	  $pageortag_rowstring .= '<td>';
	  $taglistforpage = $taglistbypages[$pageortag];
	  if (count($taglistforpage)==0)
	    $pageortag_rowstring .= "--";
	  foreach ($taglistforpage as $tag)
	    {
	      if ($monthoryearadvice == 'month')
		$pageortag_rowstring .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$tag.'</a> ';
	      else
		$pageortag_rowstring .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$tag.'</a> ';
	    }
	  $pageortag_rowstring .= '</td>';
	}
      $pageortag_rowstring .="</tr>";
      print $pageortag_rowstring;
    }
  if ($includetotal=='includetotal' and count($pageortaglist) > 1)
    {
      $totals_rowstring="<tr><td><strong>Total</strong></td>";
      foreach($monthoryearlist as $monthoryear) #Prints bottom row with totals
	{
	  $totals_rowstring .= '<td align="right"><strong><element title="'.$monthoryear_total[$monthoryear].'">'.numericdisplay($monthoryear_total[$monthoryear],$numericdisplayformat).'</element></strong></td>';
	}
      if (count($monthoryearlist) > 1)
	{ 
	  $totals_rowstring .= '<td align="right"><strong><element title="'.$grand_total.'">'.numericdisplay($grand_total,$numericdisplayformat).'</element></strong></td>';
	}
      $totals_rowstring .= '<td align="right"><strong>100</strong></td>';
      if ($pageortagadvice == 'page')
	$totals_rowstring .= "<td>--</td>";
      $totals_rowstring .= "</tr>";
      print $totals_rowstring;
    }
  if (count($monthoryearlist) > 1)
    {
      $percentages_rowstring = "<tr><td><strong>Percentage</strong></td>";
      foreach($monthoryearlist as $monthoryear)
	{
	  $percentages_rowstring .= '<td align="right"><strong>'.$monthoryear_percentage[$monthoryear].'</strong></td>';
	}
      if ($includetotal == 'includetotal')
	{
	  $percentages_rowstring .= '<td align="right"><strong>100</strong></td>';
	}
      if (count($pageortaglist) > 1)
	{
	  $percentages_rowstring .= '<td align="right">--</td>';
	}
      if ($pageortagadvice == 'page')
	$percentages_rowstring .= "<td>--</td>";
      $percentages_rowstring .= '</tr>';
      print $percentages_rowstring;
    }
  print "</table>";
  flush();
}

function printpageviewsformonthoryearlistashtmltabletransposed($pageortaglist,$monthoryearlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageortagadvice='page',$monthoryearadvice='month') {
  flush();
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageortaglist,$monthoryearlist);
  if ($sizeoverflow > 0)
    return false;

  #Collect all the numbers that need to be printed first
  if ($pageortagadvice=='page' and $monthoryearadvice=='month') {
    $viewcountarray = viewcountarraybymonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  } elseif ($pageortagadvice=='page' and $monthoryearadvice=='year') {
    $viewcountarray = viewcountarraybyyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  } elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month') {
    $viewcountarray = viewcountarraybytagandmonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  } elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year') {
    $viewcountarray = viewcountarraybytagandyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  }
  $totalsandpercentages_array = totalsandpercentages($pageortaglist,$monthoryearlist,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageortag_total = $totalsandpercentages_array[1];
  $monthoryear_total = $totalsandpercentages_array[2];
  $pageortag_percentage = $totalsandpercentages_array[3];
  $monthoryear_percentage = $totalsandpercentages_array[4];

  #Tag list fetching
  if ($pageortagadvice=='page')
     $taglistbypages = gettaglistbypagelist($pageortaglist,$language);

  #Pre-table warnings
    
  if ($monthoryearadvice=='year')
    print "<strong>For speed and consistency reasons, we do <em>not</em> include the current month in totals for the current year</strong><br><br>";

  flush();
  #Table header row
  print '<table border="1">';
  $headerstring = "<tr><th>".ucfirst($monthoryearadvice)."</th>";
  $shortDescriptor = getShortDescriptor($drilldown);
  foreach($pageortaglist as $pageortag) {
    if ($pageortagadvice=='page') {
      $headerstring .= '<th>'.$shortDescriptor.' of page <a href="'. getpageurl($pageortag,$language). '" title="'.$pageortag.' (read page on Wikipedia)">' . $pageortag.'</a></th>';
    } elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month') {
      $headerstring .= '<th>'.$shortDescriptor.' of pages with tag <a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageortag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageortag.'</a></th>';
    } elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year') {
      $headerstring .= '<th>Views of pages with tag <a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageortag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageortag.'</a></th>';
    }
  }
  if ($includetotal=='includetotal' and count($pageortaglist) > 1) {
    $headerstring .="<th>Total</th>";
  }
  if (count($monthoryearlist) > 1) {
    $headerstring.='<td><strong>Percentage</strong></td>';
  }
  $headerstring .= '</tr>';
  print $headerstring;
  
  ##Data rows
  foreach($monthoryearlist as $monthoryear) { #Prints one row of the table
    $monthoryear_rowstring = '<tr><td>'.$monthoryear.'</td>';
    foreach($pageortaglist as $pageortag) { #Computes one cell entry
      $viewcount = $viewcountarray[$pageortag][$monthoryear];
      if ($pageortagadvice=='page' and $monthoryearadvice=='month') {
        $monthoryear_rowstring .= printmonthviewcount($pageortag,$monthoryear,$language,$drilldown,$viewcount,$numericdisplayformat);
      } elseif ($pageortagadvice=='page' and $monthoryearadvice=='year') {
        $monthoryear_rowstring .= printyearviewcount($pageortag,$monthoryear,$language,$drilldown,$viewcount,$numericdisplayformat);
      } elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month') {
        $monthoryear_rowstring .= printtagviewcount($pageortag,$monthoryear,$language,$drilldown,$viewcount,$numericdisplayformat);
      } elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year') {
        $monthoryear_rowstring .= printtagviewcountbyyear($pageortag,$monthoryear,$language,$drilldown,$viewcount,$numericdisplayformat);
      }
    }
    if ($includetotal=='includetotal' and count($pageortaglist) > 1) {
      $monthoryear_rowstring .='<td align="right"><strong><element title="'.$monthoryear_total[$monthoryear].'">'.numericdisplay($monthoryear_total[$monthoryear],$numericdisplayformat).'</element></strong></td>';
    }
    if (count($monthoryearlist) > 1) {
      $monthoryear_rowstring .='<td align="right"><strong>'.$monthoryear_percentage[$monthoryear].'</strong></td></tr>';
    }
    print $monthoryear_rowstring;
  }
    
  ##Totals row
  if ($includetotal=='includetotal' and count($monthoryearlist) > 1) {
    $totals_rowstring="<tr><td><strong>Total</strong></td>";
    foreach($pageortaglist as $pageortag) { #Prints bottom row with totals
      $totals_rowstring .= '<td align="right"><strong><element title="'.$pageortag_total[$pageortag].'">'.numericdisplay($pageortag_total[$pageortag],$numericdisplayformat).'</element></strong></td>';
    }
    if (count($pageortaglist) > 1) { 
      $totals_rowstring .= '<td align="right"><strong><element title="'.$grand_total.'">'.numericdisplay($grand_total,$numericdisplayformat).'</element></strong></td>';
    }
    $totals_rowstring .= '<td align="right"><strong>100</strong></td></tr>';
    print $totals_rowstring;
  }

  ##Percentages row
  if (count($pageortaglist) > 1)
    {
      $percentages_rowstring = "<tr><td><strong>Percentage</strong></td>";
      foreach($pageortaglist as $pageortag)
	{
	  $percentages_rowstring .= '<td align="right"><strong>'.$pageortag_percentage[$pageortag].'</strong></td>';
	}
      if ($includetotal == 'includetotal')
	{
	  $percentages_rowstring .= '<td align="right"><strong>100</strong></td>';
	}
      if (count($monthoryearlist) > 1)
	{
	  $percentages_rowstring .= '<td align="right">--</td></tr>';
	}
      print $percentages_rowstring;
    }

  if ($pageortagadvice == 'page')
    {
      $tags_rowstring = "<tr><td><strong>Tags</strong></td>";
      foreach ($pageortaglist as $pageortag)
	{
	  $tags_rowstring .= '<td>';
	  $taglistforpage = $taglistbypages[$pageortag];
	  if (count($taglistforpage)==0)
	    $tags_rowstring .= "--";
	  foreach ($taglistforpage as $tag)
	    {
	      if ($monthoryearadvice == 'month') 
		$tags_rowstring .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&allmonths=allmonths">'.$tag.'</a> ';
	      else
		$tags_rowstring .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&allyears=allyears">'.$tag.'</a> ';
	    }
	  $tags_rowstring .= '</td>';
	}
      if (count($pageortaglist) > 1)
	$tags_rowstring .= '<td>--</td>';
      if (count($monthoryearlist) > 1)
	$tags_rowstring .= '<td>--</td>';
      $tags_rowstring .= '</tr>';
      print $tags_rowstring;
    }	  
  print "</table>";
  flush();
}

function printpageviewsformonthoryearlistascsv($pageortaglist,$monthoryearlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageortagadvice='page',$monthoryearadvice='month') {
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageortaglist,$monthoryearlist);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageortagadvice=='page' and $monthoryearadvice=='month')
    {
      $viewcountarray = viewcountarraybymonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
    }
  elseif ($pageortagadvice=='page' and $monthoryearadvice=='year')
    {
      $viewcountarray = viewcountarraybyyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
    }
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
    {
      $viewcountarray = viewcountarraybytagandmonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
    }
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
    {
      $viewcountarray = viewcountarraybytagandyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
    }

  $totalsandpercentages_array = totalsandpercentages($pageortaglist,$monthoryearlist,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageortag_total = $totalsandpercentages_array[1];
  $monthoryear_total = $totalsandpercentages_array[2];
  $pageortag_percentage = $totalsandpercentages_array[3];
  $monthoryear_percentage = $totalsandpercentages_array[4];


  $headerstring = ucfirst($pageortagadvice)." name";
  $descriptor = getDescriptor($drilldown);
  foreach($monthoryearlist as $monthoryear) {
    $headerstring .= "|".$descriptor." in ".$monthoryearadvice." ".$monthoryear;
  }
  if ($includetotal=='includetotal' and count($monthoryearlist) > 1) 
    $headerstring .="|Total";
  if (count($pageortaglist) > 1)
    $headerstring .="|Percentage";
  $headerstring.="<br>";
  print $headerstring;
  foreach($pageortaglist as $pageortag)
    {
	$stringtoprint = $pageortag;
	$total = 0;
	foreach($monthoryearlist as $monthoryear)
	  {
	    $viewcount = $viewcountarray[$pageortag][$monthoryear];
	    $stringtoprint .= "|".$viewcount;
	  }
	if ($includetotal=='includetotal' and count($monthoryearlist) > 1) 
	  $stringtoprint .="|".$pageortag_total[$pageortag];
	if (count($pageortaglist) > 1) 
	    $stringtoprint .="|".$pageortag_percentage[$pageortag];
	$stringtoprint .="<br>";
	print $stringtoprint;
    }
  if ($includetotal == 'includetotal' and count($pageortaglist) > 1)
    {
      $totals_rowstring = "Total";
      foreach($monthoryearlist as $monthoryear)
	  $totals_rowstring .= "|".$monthoryear_total[$monthoryear];
      if (count($monthoryearlist) > 1)
	$totals_rowstring .= "|".$grand_total;
      $totals_rowstring .= "|100";
      $totals_rowstring .= "<br>";
      print $totals_rowstring;
    }
  if (count($monthoryearlist) > 1)
    {
      $percentages_rowstring = "Percentage";
      foreach($monthoryearlist as $monthoryear)
	{
	  $percentages_rowstring .= "|".$monthoryear_percentage[$monthoryear];
	}
      $percentages_rowstring .= "|100";
      $percentages_rowstring .= "<br>";
      print $percentages_rowstring;
    }
}

function printpageviewsformonthoryearlistascsvtransposed($pageortaglist,$monthoryearlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageortagadvice='page',$monthoryearadvice='month') {
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageortaglist,$monthoryearlist);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageortagadvice=='page' and $monthoryearadvice=='month')
    $viewcountarray = viewcountarraybymonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  elseif ($pageortagadvice=='page' and $monthoryearadvice=='year')
    $viewcountarray = viewcountarraybyyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);

  $totalsandpercentages_array = totalsandpercentages($pageortaglist,$monthoryearlist,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageortag_total = $totalsandpercentages_array[1];
  $monthoryear_total = $totalsandpercentages_array[2];
  $pageortag_percentage = $totalsandpercentages_array[3];
  $monthoryear_percentage = $totalsandpercentages_array[4];


  $headerstring = ucfirst($monthoryearadvice);
  foreach($pageortaglist as $pageortag)
    $headerstring .= "|Views of ".$pageortagadvice." ".$pageortag;
  if ($includetotal=='includetotal' and count($pageortaglist) > 1) 
    $headerstring .="|Total";
  if (count($monthoryearlist) > 1)
    $headerstring .="|Percentage";
  $headerstring.="<br>";
  print $headerstring;
  foreach($monthoryearlist as $monthoryear)
    {
	$stringtoprint = $monthoryear;
	$total = 0;
	foreach($pageortaglist as $pageortag)
	  {
	    $viewcount = $viewcountarray[$pageortag][$monthoryear];
	    $stringtoprint .= "|".$viewcount;
	  }
	if ($includetotal=='includetotal' and count($pageortaglist) > 1) 
	  $stringtoprint .="|".$monthoryear_total[$monthoryear];
	if (count($monthoryearlist) > 1) 
	  {
	    $stringtoprint .="|".$monthoryear_percentage[$monthoryear];
	  }
	$stringtoprint .="<br>";
	print $stringtoprint;
    }
  if ($includetotal == 'includetotal' and count($monthoryearlist) > 1)
    {
      $totals_rowstring = "Total";
      foreach($pageortaglist as $pageortag)
	$totals_rowstring .= "|".$pageortag_total[$pageortag];
      if (count($pageortaglist) > 1)
	$totals_rowstring .= "|".$grand_total;
      $totals_rowstring .="|100";
      $totals_rowstring .= "<br>";
      print $totals_rowstring;
    }
  if (count($pageortaglist) > 1)
    {
      $percentages_rowstring = "Percentage";
      foreach($pageortaglist as $pageortag)
	{
	  $percentages_rowstring .= "|".$pageortag_percentage[$pageortag];
	}
      $percentages_rowstring .= "|100";
      $percentages_rowstring .= "<br>";
      print $percentages_rowstring;
    }
}

function generateGraph($pageortaglist,$monthoryearlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageortagadvice='page',$monthoryearadvice='month') {
  global $imagesPath;
  global $generateGraphCmdBase;
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageortaglist,$monthoryearlist);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageortagadvice=='page' and $monthoryearadvice=='month')
    $viewcountarray = viewcountarraybymonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  elseif ($pageortagadvice=='page' and $monthoryearadvice=='year')
    $viewcountarray = viewcountarraybyyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);

  $totalsandpercentages_array = totalsandpercentages($pageortaglist,$monthoryearlist,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageortag_total = $totalsandpercentages_array[1];
  $monthoryear_total = $totalsandpercentages_array[2];
  $pageortag_percentage = $totalsandpercentages_array[3];
  $monthoryear_percentage = $totalsandpercentages_array[4];

  $fullOutput = "";

  $headerstring = ucfirst($monthoryearadvice);
  foreach($pageortaglist as $pageortag)
    $headerstring .= "|".$pageortag;
  if ($includetotal=='includetotal' and count($pageortaglist) > 1) 
    $headerstring .="|Total";
  if (count($monthoryearlist) > 1)
    $headerstring .="|Percentage";
  $headerstring .="\n";
  $fullOutput .= $headerstring;
  foreach($monthoryearlist as $monthoryear) {
    $stringtoprint = $monthoryear;
    $total = 0;
    foreach($pageortaglist as $pageortag) {
      $viewcount = $viewcountarray[$pageortag][$monthoryear];
      $stringtoprint .= "|".$viewcount;
    }
    if ($includetotal=='includetotal' and count($pageortaglist) > 1) {
      $stringtoprint .="|".$monthoryear_total[$monthoryear];
    }
    if (count($monthoryearlist) > 1) {
      $stringtoprint .="|".$monthoryear_percentage[$monthoryear];
    }
    $stringtoprint .="\n";
    $fullOutput .= $stringtoprint;
  }
  if ($includetotal == 'includetotal' and count($monthoryearlist) > 1) {
    $totals_rowstring = "Total";
    foreach($pageortaglist as $pageortag)
      $totals_rowstring .= "|".$pageortag_total[$pageortag];
    if (count($pageortaglist) > 1)
      $totals_rowstring .= "|".$grand_total;
    $totals_rowstring .="|100";
    $totals_rowstring .= "\n";
    $fullOutput .= $totals_rowstring;
  }
  if (count($pageortaglist) > 0) {
    $percentages_rowstring = "Percentage";
    foreach($pageortaglist as $pageortag) {
      $percentages_rowstring .= "|".$pageortag_percentage[$pageortag];
    }
    $percentages_rowstring .= "|100";
    $percentages_rowstring .= "\n";
    $fullOutput .= $percentages_rowstring;
  }
  $fileName = strval(rand());
  $filePathBase = $imagesPath . $fileName;
  # print("Going to try writing the following to ".$filePathBase.".csv: <br>".$fullOutput."<br>");
  file_put_contents($filePathBase . ".csv", $fullOutput);
  $cmdToExecute = $generateGraphCmdBase . " " . $filePathBase . ".csv " . $filePathBase . ".png ";
  if ($numericdisplayformat == "log") {
    $cmdToExecute = $cmdToExecute . " --log10";
  }
  # print("Going to try executing ".$cmdToExecute."<br>");
  exec($cmdToExecute);
  print '<img src="/images/'.$fileName.'.png" alt="Graph of pageviews should have loaded here"></img>';
}

function printpageviewsformonthoryearlistascpi($pageortaglist,$monthoryearlist,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageortagadvice='page',$monthoryearadvice='month') {
  global $exceededquerylimitmessage;
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageortaglist,$monthoryearlist);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageortagadvice=='page' and $monthoryearadvice=='month')
    $viewcountarray = viewcountarraybymonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  elseif ($pageortagadvice=='page' and $monthoryearadvice=='year')
    $viewcountarray = viewcountarraybyyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageortaglist,$monthoryearlist,$language,$drilldown,true,$normalization);
  
  #Collect tag information
  if ($pageortagadvice=='page')
    {
      $taglistbypages = gettaglistbypagelist($pageortaglist,$language);
      $tagindices = gettagindices($pageortaglist,$language);
    }
  for ($i = 0; $i < count($pageortaglist); $i++)
    {
      for ($j = 0; $j < count($monthoryearlist); $j++)
	{
	  $viewcount = $viewcountarray[$pageortaglist[$i]][$monthoryearlist[$j]];
	  if ($viewcount != $exceededquerylimitmessage)
	    {
	      print $viewcount; 
	      print " ";
	      print "1,".$i;
	      print " ";
	      print "2,".$j;
	      foreach ($taglistbypages[$pageortaglist[$i]] as $tag)
		{
		  print " 3,".$tagindices[$tag];
		  print " 4,".($tagindices[$tag] * count($monthoryearlist) + $j);
		}
	      print "<br>";
	    }
	}
    }
}

?>
