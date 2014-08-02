<?php

function totalsandpercentages($pageortaglist,$monthoryearlist,$viewcountarray)
{
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

function printmonthviewcount($page,$month,$language,$viewcount,$numericdisplayformat)
{
  return '<td align="right"><a href="'.getpageviewsurl($page,$month,$language).'" title="'.monthviewtooltip($viewcount).'">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';
}

function printyearviewcount($page,$year,$language,$viewcount,$numericdisplayformat)
{
  return '<td align="right"><a href="'.getannualpageviewsurl($page,$year,$language).'" title="'.yearviewtooltip($viewcount).'">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';
}

function printtagviewcount($tag,$month,$language,$viewcount,$numericdisplayformat)
{
  return '<td align="right"><a href="'.gettagviewsurl($tag,$month,$language).'" title="'.$viewcount.' (click for data on individual pages)">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';
}

function printtagviewcountbyyear($tag,$year,$language,$viewcount,$numericdisplayformat)
{
  return '<td align="right"><a href="'.getannualtagviewsurl($tag,$year,$language).'" title="'.$viewcount.' (click for data on individual pages)">'.numericdisplay($viewcount,$numericdisplayformat).'</a></td>';
}

function printpageviewsformonthoryearlistashtmltable($pageortaglist,$monthoryearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageortagadvice='page',$monthoryearadvice='month')
{
  #Collect all the numbers that need to be printed first
  if ($pageortagadvice=='page' and $monthoryearadvice=='month')
    {
      $viewcountarray = viewcountarraybymonth($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  elseif ($pageortagadvice=='page' and $monthoryearadvice=='year')
    {
      $viewcountarray = viewcountarraybyyear($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
    {
      $viewcountarray = viewcountarraybytagandmonth($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
    {
      $viewcountarray = viewcountarraybytagandyear($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  $totalsandpercentages_array = totalsandpercentages($pageortaglist,$monthoryearlist,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageortag_total = $totalsandpercentages_array[1];
  $monthoryear_total = $totalsandpercentages_array[2];
  $pageortag_percentage = $totalsandpercentages_array[3];
  $monthoryear_percentage = $totalsandpercentages_array[4];
  
  ##Table header row
    
  print '<table border="1">';
  $headerstring = "<tr><th>".ucfirst($pageortagadvice)." name</th>";
  foreach($monthoryearlist as $monthoryear)
    {
      $headerstring .= "<th>Pageviews in ".$monthoryearadvice." ".$monthoryear."</th>";
    }
  if ($includetotal=='includetotal' and count($monthoryearlist) > 1) 
    {
      $headerstring .="<th>Total</th>";
    }
  if (count($pageortaglist) > 1) 
    {
      $headerstring.="<th>Percentage</th>";
    }
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
	  $pageortag_rowstring = '<td><a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageortag.'&language='.$language.'&allmonths=allmonths">'.$pageortag.'</a></td>';
	}		       
      elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
	{
	  $pageortag_rowstring = '<td><a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageortag.'&language='.$language.'&allyears=allyears">'.$pageortag.'</a></td>';
	}
      foreach($monthoryearlist as $monthoryear) #Computes one cell entry
	{
	  $viewcount = $viewcountarray[$pageortag][$monthoryear];
	  if ($pageortagadvice=='page' and $monthoryearadvice=='month')
	    {
	      $pageortag_rowstring .= printmonthviewcount($pageortag,$monthoryear,$language,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageortagadvice=='page' and $monthoryearadvice=='year')
	    {
	      $pageortag_rowstring .= printyearviewcount($pageortag,$monthoryear,$language,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
	    {
	      $pageortag_rowstring .= printtagviewcount($pageortag,$monthoryear,$language,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
	    {
	      $pageortag_rowstring .= printtagviewcountbyyear($pageortag,$monthoryear,$language,$viewcount,$numericdisplayformat);
	    }

	}
      if ($includetotal=='includetotal' and count($monthoryearlist) > 1) 
	{
	  $pageortag_rowstring .='<td align="right"><strong><element title="'.$pageortag_total[$pageortag].'">'.numericdisplay($pageortag_total[$pageortag],$numericdisplayformat).'</element></strong></td>';
	}
      if (count($pageortaglist) > 1) {$pageortag_rowstring .= '<td align="right"><strong>'.$pageortag_percentage[$pageortag].'</strong></td>';}
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
      $totals_rowstring .= '<td align="right"><strong>100</strong></td></tr>';
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
      $percentages_rowstring .= '</tr>';
      print $percentages_rowstring;
    }
  print "</tbody></table>";
}

function printpageviewsformonthoryearlistashtmltabletransposed($pageortaglist,$monthoryearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageortagadvice='page',$monthoryearadvice='month')
{

  #Collect all the numbers that need to be printed first
  if ($pageortagadvice=='page' and $monthoryearadvice=='month')
    {
      $viewcountarray = viewcountarraybymonth($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  elseif ($pageortagadvice=='page' and $monthoryearadvice=='year')
    {
      $viewcountarray = viewcountarraybyyear($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
    {
      $viewcountarray = viewcountarraybytagandmonth($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
    {
      $viewcountarray = viewcountarraybytagandyear($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  $totalsandpercentages_array = totalsandpercentages($pageortaglist,$monthoryearlist,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageortag_total = $totalsandpercentages_array[1];
  $monthoryear_total = $totalsandpercentages_array[2];
  $pageortag_percentage = $totalsandpercentages_array[3];
  $monthoryear_percentage = $totalsandpercentages_array[4];
  
  print '<table border="1">';
  $headerstring = "<tr><th>".ucfirst($monthoryearadvice)."</th>";
  foreach($pageortaglist as $pageortag)
    {
      if ($pageortagadvice=='page')
	{
	  $headerstring .= '<th>Views of page <a href="'. getpageurl($pageortag,$language). '" title="'.$pageortag.' (read page on Wikipedia)">' . $pageortag.'</a></th>';
	}
      elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
	{
	  $headerstring .= '<th>Views of pages with tag <a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageortag.'&language='.$language.'&allmonths=allmonths">'.$pageortag.'</a></th>';
	}
      elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
	{
	  $headerstring .= '<th>Views of pages with tag <a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageortag.'&language='.$language.'&allyears=allyears">'.$pageortag.'</a></th>';
	}

    }
  if ($includetotal=='includetotal' and count($pageortaglist) > 1) 
    {
      $headerstring .="<th>Total</th>";
    }
  if (count($monthoryearlist) > 1) 
    {
      $headerstring.='<td><strong>Percentage</strong></td>';
    }
  $headerstring .= '</tr>';
  print $headerstring;
  
  ##Data rows
  foreach($monthoryearlist as $monthoryear) #Prints one row of the table
    {
      $monthoryear_rowstring = '<tr><td>'.$monthoryear.'</td>';
      foreach($pageortaglist as $pageortag) #Computes one cell entry
	{
	  $viewcount = $viewcountarray[$pageortag][$monthoryear];
	  if ($pageortagadvice=='page' and $monthoryearadvice=='month')
	    {
	      $monthoryear_rowstring .= printmonthviewcount($pageortag,$monthoryear,$language,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageortagadvice=='page' and $monthoryearadvice=='year')
	    {
	      $monthoryear_rowstring .= printyearviewcount($pageortag,$monthoryear,$language,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
	    {
	      $monthoryear_rowstring .= printtagviewcount($pageortag,$monthoryear,$language,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
	    {
	      $monthoryear_rowstring .= printtagviewcountbyyear($pageortag,$monthoryear,$language,$viewcount,$numericdisplayformat);
	    }

	}
      if ($includetotal=='includetotal' and count($pageortaglist) > 1) 
	{
	  $monthoryear_rowstring .='<td align="right"><strong><element title="'.$monthoryear_total[$monthoryear].'">'.numericdisplay($monthoryear_total[$monthoryear],$numericdisplayformat).'</element></strong></td>';
	}
      if (count($monthoryearlist) > 1) 
	{
	  $monthoryear_rowstring .='<td align="right"><strong>'.$monthoryear_percentage[$monthoryear].'</strong></td></tr>';
	}
      print $monthoryear_rowstring;
    }
  if ($includetotal=='includetotal' and count($monthoryearlist) > 1)
    {
      $totals_rowstring="<tr><td><strong>Total</strong></td>";
      foreach($pageortaglist as $pageortag) #Prints bottom row with totals
	{
	  $totals_rowstring .= '<td align="right"><strong><element title="'.$pageortag_total[$pageortag].'">'.numericdisplay($pageortag_total[$pageortag],$numericdisplayformat).'</element></strong></td>';
	}
      if (count($pageortaglist) > 1)
	{ 
	  $totals_rowstring .= '<td align="right"><strong><element title="'.$grand_total.'">'.numericdisplay($grand_total,$numericdisplayformat).'</element></strong></td>';
	}
      $totals_rowstring .= '<td align="right"><strong>100</strong></td></tr>';
      print $totals_rowstring;
    }
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
  print "</table>";
}

function printpageviewsascsv($pagelist,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='')
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


function printpageviewsascountsonlycsv($pagelist,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='')
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

function printpageviewsascountsonlyseparatelines($pagelist,$month,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='')
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

function printpageviewsformonthlistascsv($pagelist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='')
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

function printpageviewsformonthlistascsvtransposed($pagelist,$monthlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='')
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

function printpageviewsformonthoryearlistascpi($pageortaglist,$monthoryearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageortagadvice='page',$monthoryearadvice='month')
{
  #Collect all the numbers that need to be printed first
  if ($pageortagadvice=='page' and $monthoryearadvice=='month')
    {
      $viewcountarray = viewcountarraybymonth($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  elseif ($pageortagadvice=='page' and $monthoryearadvice=='year')
    {
      $viewcountarray = viewcountarraybyyear($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='month')
    {
      $viewcountarray = viewcountarraybytagandmonth($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  elseif ($pageortagadvice=='tag' and $monthoryearadvice=='year')
    {
      $viewcountarray = viewcountarraybytagandyear($pageortaglist,$monthoryearlist,$language,true,$normalization);
    }
  for ($i = 0; $i < count($pageortaglist); $i++)
    {
      for ($j = 0; $j < count($monthoryearlist); $j++)
	{
	  print $viewcountarray[$pageortaglist[$i]][$monthoryearlist[$j]];
	  print " ";
	  print "1,".$i;
	  print " ";
	  print "2,".$j;
	  print "<br>";
	}
    }
}
function printpageviewsforyearlistascsv($pagelist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='')
{
  $headerstring = "Page name";
  foreach($yearlist as $year)
    {
      $headerstring .= ",Pageviews in year ".$year;
    }
  if ($includetotal=='includetotal') {$headerstring .=",Total";}
  $headerstring.="<br>";
  print $headerstring;
  foreach($pagelist as $page)
    {
      $stringtoprint = $page;
      $total = 0;
      foreach($yearlist as $year)
	{
	  $viewcount = getannualpageviews($page,$year,$language);
	  if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
	  $stringtoprint .= ",".$viewcount;
	}
      if ($includetotal=='includetotal') {$stringtoprint .=",".$total;}
      $stringtoprint .="<br>";
      print $stringtoprint;
    }
}

function printpageviewsforyearlistascsvtransposed($pagelist,$yearlist,$language,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='')
{
  $headerstring = "Year";
  foreach($pagelist as $page)
    {
	$headerstring .= ",Views of page ".$page;
    }
  if ($includetotal=='includetotal') {$headerstring .=",Total";}
  $headerstring.="<br>";
  print $headerstring;
  foreach($yearlist as $year)
    {
      $stringtoprint = $year;
      $total = 0;
      foreach($pagelist as $page)
	{
	  $viewcount = getannualpageviews($page,$year,$language);
	  if ($includetotal=='includetotal') {$total = $total + intval($viewcount);}
	  $stringtoprint .= ",".$viewcount;
	}
      if ($includetotal=='includetotal') {$stringtoprint .=",".$total;}
      $stringtoprint .="<br>";
      print $stringtoprint;
    }
}

?>
