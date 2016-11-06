<?php

include_once("globalvariables/passwordfile.inc");

function checksizes($pageOrTagList,$monthOrYearList) {
  global $pagedisplaylimit;
  global $celldisplaylimit;
  $numberofpagesortags = count($pageOrTagList);
  $numberofmonthsoryears = count($monthOrYearList);
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
function totalsandpercentages($pageOrTagList,$monthOrYearList,$viewcountarray) {
  $grand_total = 0;
  foreach ($pageOrTagList as $pageOrTag)#Computes page totals and grand total
    {
      $pageOrTag_total[$pageOrTag] = 0;
      foreach ($monthOrYearList as $monthOrYear)
	{
	  $pageOrTag_total[$pageOrTag] += intval($viewcountarray[$pageOrTag][$monthOrYear]);
	  
	}
      $grand_total += $pageOrTag_total[$pageOrTag];
    }
  foreach ($monthOrYearList as $monthOrYear)#Computes month or year totals
    {
      $monthOrYear_total[$monthOrYear] = 0;
      foreach ($pageOrTagList as $pageOrTag)
	{
	  $monthOrYear_total[$monthOrYear] += intval($viewcountarray[$pageOrTag][$monthOrYear]);
	}
    }
  
  foreach ($pageOrTagList as $pageOrTag)#Computes page percentages
    {
      if ($grand_total == 0)
	{
	  $pageOrTag_percentage[$pageOrTag] = 'undefined';
	}
      else
	{
	  $pageOrTag_percentage[$pageOrTag] = round(100 * floatval($pageOrTag_total[$pageOrTag])/floatval($grand_total),1);
	}
    }
  
  foreach ($monthOrYearList as $monthOrYear)#Computes month or year percentages
    {
      if ($grand_total == 0)
		{
		  $monthOrYear_percentage[$monthOrYear] = 'undefined';
		}
      else
	{
	  $monthOrYear_percentage[$monthOrYear] = round(100.0 * floatval($monthOrYear_total[$monthOrYear])/floatval($grand_total),1);
	}
    }
  
  return array($grand_total,$pageOrTag_total,$monthOrYear_total,$pageOrTag_percentage,$monthOrYear_percentage);
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

function printPageviewsForMonthOrYearListAsHtmlTable($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageOrTagadvice='page',$monthOrYearadvice='month') {
  flush();
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagadvice=='page' and $monthOrYearadvice=='month') {
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  } elseif ($pageOrTagadvice=='page' and $monthOrYearadvice=='year') {
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  } elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='month') {
      $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  } elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='year') {
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  }
  $totalsandpercentages_array = totalsandpercentages($pageOrTagList,$monthOrYearList,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageOrTag_total = $totalsandpercentages_array[1];
  $monthOrYear_total = $totalsandpercentages_array[2];
  $pageOrTag_percentage = $totalsandpercentages_array[3];
  $monthOrYear_percentage = $totalsandpercentages_array[4];

  #Tag list fetching
  if ($pageOrTagadvice=='page')
    $tagListbypages = gettagListbypageList($pageOrTagList,$language);

  #Pre-table warnings

  if ($monthOrYearadvice=='year') {
    print "<strong>For speed and consistency reasons, we do <em>not</em> include the current month in totals for the current year</strong><br><br>";
  }
  flush();
  ##Table header row
    
  print '<table border="1">';
  $headerstring = "<tr><th>".ucfirst($pageOrTagadvice)." name</th>";
  $descriptor = getDescriptor($drilldown);

  foreach($monthOrYearList as $monthOrYear) {
    $headerstring .= "<th>".$descriptor." in ".$monthOrYearadvice." ".$monthOrYear."</th>";
  }
  if ($includetotal=='includetotal' and count($monthOrYearList) > 1) {
    $headerstring .="<th>Total</th>";
  }
  if (count($pageOrTagList) > 1) {
    $headerstring.="<th>Percentage</th>";
  }

  #Tag list column printing
  if ($pageOrTagadvice == 'page')
      $headerstring .= "<th>Tags</th>";
  
  $headerstring .= "</tr>";
  print $headerstring;
  
  ##Data rows
  foreach($pageOrTagList as $pageOrTag) #Prints one row of the table
    {
      if ($pageOrTagadvice=='page')
	{
	  $pageOrTag_rowstring = '<tr><td><a href="'.getpageurl($pageOrTag,$language).'" title = "'.$pageOrTag.' (read page on Wikipedia)">'.$pageOrTag.'</a></td>';
	}
      elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='month')
	{
	  $pageOrTag_rowstring = '<td><a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a></td>';
	}		       
      elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='year')
	{
	  $pageOrTag_rowstring = '<td><a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a></td>';
	}
      foreach($monthOrYearList as $monthOrYear) #Computes one cell entry
	{
	  $viewcount = $viewcountarray[$pageOrTag][$monthOrYear];
	  if ($pageOrTagadvice=='page' and $monthOrYearadvice=='month')
	    {
	      $pageOrTag_rowstring .= printmonthviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageOrTagadvice=='page' and $monthOrYearadvice=='year')
	    {
	      $pageOrTag_rowstring .= printyearviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='month')
	    {
	      $pageOrTag_rowstring .= printtagviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericdisplayformat);
	    }
	  elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='year')
	    {
	      $pageOrTag_rowstring .= printtagviewcountbyyear($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericdisplayformat);
	    }

	}
      if ($includetotal=='includetotal' and count($monthOrYearList) > 1) 
	$pageOrTag_rowstring .='<td align="right"><strong><element title="'.$pageOrTag_total[$pageOrTag].'">'.numericdisplay($pageOrTag_total[$pageOrTag],$numericdisplayformat).'</element></strong></td>';
      if (count($pageOrTagList) > 1) 
	$pageOrTag_rowstring .= '<td align="right"><strong>'.$pageOrTag_percentage[$pageOrTag].'</strong></td>';
      if ($pageOrTagadvice == 'page')
	{
	  $pageOrTag_rowstring .= '<td>';
	  $tagListforpage = $tagListbypages[$pageOrTag];
	  if (count($tagListforpage)==0)
	    $pageOrTag_rowstring .= "--";
	  foreach ($tagListforpage as $tag)
	    {
	      if ($monthOrYearadvice == 'month')
		$pageOrTag_rowstring .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$tag.'</a> ';
	      else
		$pageOrTag_rowstring .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$tag.'</a> ';
	    }
	  $pageOrTag_rowstring .= '</td>';
	}
      $pageOrTag_rowstring .="</tr>";
      print $pageOrTag_rowstring;
    }
  if ($includetotal=='includetotal' and count($pageOrTagList) > 1)
    {
      $totals_rowstring="<tr><td><strong>Total</strong></td>";
      foreach($monthOrYearList as $monthOrYear) #Prints bottom row with totals
	{
	  $totals_rowstring .= '<td align="right"><strong><element title="'.$monthOrYear_total[$monthOrYear].'">'.numericdisplay($monthOrYear_total[$monthOrYear],$numericdisplayformat).'</element></strong></td>';
	}
      if (count($monthOrYearList) > 1)
	{ 
	  $totals_rowstring .= '<td align="right"><strong><element title="'.$grand_total.'">'.numericdisplay($grand_total,$numericdisplayformat).'</element></strong></td>';
	}
      $totals_rowstring .= '<td align="right"><strong>100</strong></td>';
      if ($pageOrTagadvice == 'page')
	$totals_rowstring .= "<td>--</td>";
      $totals_rowstring .= "</tr>";
      print $totals_rowstring;
    }
  if (count($monthOrYearList) > 1)
    {
      $percentages_rowstring = "<tr><td><strong>Percentage</strong></td>";
      foreach($monthOrYearList as $monthOrYear)
	{
	  $percentages_rowstring .= '<td align="right"><strong>'.$monthOrYear_percentage[$monthOrYear].'</strong></td>';
	}
      if ($includetotal == 'includetotal')
	{
	  $percentages_rowstring .= '<td align="right"><strong>100</strong></td>';
	}
      if (count($pageOrTagList) > 1)
	{
	  $percentages_rowstring .= '<td align="right">--</td>';
	}
      if ($pageOrTagadvice == 'page')
	$percentages_rowstring .= "<td>--</td>";
      $percentages_rowstring .= '</tr>';
      print $percentages_rowstring;
    }
  print "</table>";
  flush();
}

function printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageOrTagadvice='page',$monthOrYearadvice='month') {
  flush();
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;

  #Collect all the numbers that need to be printed first
  if ($pageOrTagadvice=='page' and $monthOrYearadvice=='month') {
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  } elseif ($pageOrTagadvice=='page' and $monthOrYearadvice=='year') {
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  } elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='month') {
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  } elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='year') {
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  }
  $totalsandpercentages_array = totalsandpercentages($pageOrTagList,$monthOrYearList,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageOrTag_total = $totalsandpercentages_array[1];
  $monthOrYear_total = $totalsandpercentages_array[2];
  $pageOrTag_percentage = $totalsandpercentages_array[3];
  $monthOrYear_percentage = $totalsandpercentages_array[4];

  #Tag list fetching
  if ($pageOrTagadvice=='page')
     $tagListbypages = gettagListbypageList($pageOrTagList,$language);

  #Pre-table warnings
    
  if ($monthOrYearadvice=='year')
    print "<strong>For speed and consistency reasons, we do <em>not</em> include the current month in totals for the current year</strong><br><br>";

  flush();
  #Table header row
  print '<table border="1">';
  $headerstring = "<tr><th>".ucfirst($monthOrYearadvice)."</th>";
  $shortDescriptor = getShortDescriptor($drilldown);
  foreach($pageOrTagList as $pageOrTag) {
    if ($pageOrTagadvice=='page') {
      $headerstring .= '<th>'.$shortDescriptor.' of page <a href="'. getpageurl($pageOrTag,$language). '" title="'.$pageOrTag.' (read page on Wikipedia)">' . $pageOrTag.'</a></th>';
    } elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='month') {
      $headerstring .= '<th>'.$shortDescriptor.' of pages with tag <a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a></th>';
    } elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='year') {
      $headerstring .= '<th>Views of pages with tag <a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a></th>';
    }
  }
  if ($includetotal=='includetotal' and count($pageOrTagList) > 1) {
    $headerstring .="<th>Total</th>";
  }
  if (count($monthOrYearList) > 1) {
    $headerstring.='<td><strong>Percentage</strong></td>';
  }
  $headerstring .= '</tr>';
  print $headerstring;
  
  ##Data rows
  foreach($monthOrYearList as $monthOrYear) { #Prints one row of the table
    $monthOrYear_rowstring = '<tr><td>'.$monthOrYear.'</td>';
    foreach($pageOrTagList as $pageOrTag) { #Computes one cell entry
      $viewcount = $viewcountarray[$pageOrTag][$monthOrYear];
      if ($pageOrTagadvice=='page' and $monthOrYearadvice=='month') {
        $monthOrYear_rowstring .= printmonthviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericdisplayformat);
      } elseif ($pageOrTagadvice=='page' and $monthOrYearadvice=='year') {
        $monthOrYear_rowstring .= printyearviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericdisplayformat);
      } elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='month') {
        $monthOrYear_rowstring .= printtagviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericdisplayformat);
      } elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='year') {
        $monthOrYear_rowstring .= printtagviewcountbyyear($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericdisplayformat);
      }
    }
    if ($includetotal=='includetotal' and count($pageOrTagList) > 1) {
      $monthOrYear_rowstring .='<td align="right"><strong><element title="'.$monthOrYear_total[$monthOrYear].'">'.numericdisplay($monthOrYear_total[$monthOrYear],$numericdisplayformat).'</element></strong></td>';
    }
    if (count($monthOrYearList) > 1) {
      $monthOrYear_rowstring .='<td align="right"><strong>'.$monthOrYear_percentage[$monthOrYear].'</strong></td></tr>';
    }
    print $monthOrYear_rowstring;
  }
    
  ##Totals row
  if ($includetotal=='includetotal' and count($monthOrYearList) > 1) {
    $totals_rowstring="<tr><td><strong>Total</strong></td>";
    foreach($pageOrTagList as $pageOrTag) { #Prints bottom row with totals
      $totals_rowstring .= '<td align="right"><strong><element title="'.$pageOrTag_total[$pageOrTag].'">'.numericdisplay($pageOrTag_total[$pageOrTag],$numericdisplayformat).'</element></strong></td>';
    }
    if (count($pageOrTagList) > 1) { 
      $totals_rowstring .= '<td align="right"><strong><element title="'.$grand_total.'">'.numericdisplay($grand_total,$numericdisplayformat).'</element></strong></td>';
    }
    $totals_rowstring .= '<td align="right"><strong>100</strong></td></tr>';
    print $totals_rowstring;
  }

  ##Percentages row
  if (count($pageOrTagList) > 1)
    {
      $percentages_rowstring = "<tr><td><strong>Percentage</strong></td>";
      foreach($pageOrTagList as $pageOrTag)
	{
	  $percentages_rowstring .= '<td align="right"><strong>'.$pageOrTag_percentage[$pageOrTag].'</strong></td>';
	}
      if ($includetotal == 'includetotal')
	{
	  $percentages_rowstring .= '<td align="right"><strong>100</strong></td>';
	}
      if (count($monthOrYearList) > 1)
	{
	  $percentages_rowstring .= '<td align="right">--</td></tr>';
	}
      print $percentages_rowstring;
    }

  if ($pageOrTagadvice == 'page')
    {
      $tags_rowstring = "<tr><td><strong>Tags</strong></td>";
      foreach ($pageOrTagList as $pageOrTag)
	{
	  $tags_rowstring .= '<td>';
	  $tagListforpage = $tagListbypages[$pageOrTag];
	  if (count($tagListforpage)==0)
	    $tags_rowstring .= "--";
	  foreach ($tagListforpage as $tag)
	    {
	      if ($monthOrYearadvice == 'month') 
		$tags_rowstring .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&allmonths=allmonths">'.$tag.'</a> ';
	      else
		$tags_rowstring .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&allyears=allyears">'.$tag.'</a> ';
	    }
	  $tags_rowstring .= '</td>';
	}
      if (count($pageOrTagList) > 1)
	$tags_rowstring .= '<td>--</td>';
      if (count($monthOrYearList) > 1)
	$tags_rowstring .= '<td>--</td>';
      $tags_rowstring .= '</tr>';
      print $tags_rowstring;
    }	  
  print "</table>";
  flush();
}

function printPageviewsForMonthOrYearListAsCsv($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageOrTagadvice='page',$monthOrYearadvice='month') {
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagadvice=='page' and $monthOrYearadvice=='month')
    {
      $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }
  elseif ($pageOrTagadvice=='page' and $monthOrYearadvice=='year')
    {
      $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }
  elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='month')
    {
      $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }
  elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='year')
    {
      $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }

  $totalsandpercentages_array = totalsandpercentages($pageOrTagList,$monthOrYearList,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageOrTag_total = $totalsandpercentages_array[1];
  $monthOrYear_total = $totalsandpercentages_array[2];
  $pageOrTag_percentage = $totalsandpercentages_array[3];
  $monthOrYear_percentage = $totalsandpercentages_array[4];


  $headerstring = ucfirst($pageOrTagadvice)." name";
  $descriptor = getDescriptor($drilldown);
  foreach($monthOrYearList as $monthOrYear) {
    $headerstring .= "|".$descriptor." in ".$monthOrYearadvice." ".$monthOrYear;
  }
  if ($includetotal=='includetotal' and count($monthOrYearList) > 1) 
    $headerstring .="|Total";
  if (count($pageOrTagList) > 1)
    $headerstring .="|Percentage";
  $headerstring.="<br>";
  print $headerstring;
  foreach($pageOrTagList as $pageOrTag)
    {
	$stringtoprint = $pageOrTag;
	$total = 0;
	foreach($monthOrYearList as $monthOrYear)
	  {
	    $viewcount = $viewcountarray[$pageOrTag][$monthOrYear];
	    $stringtoprint .= "|".$viewcount;
	  }
	if ($includetotal=='includetotal' and count($monthOrYearList) > 1) 
	  $stringtoprint .="|".$pageOrTag_total[$pageOrTag];
	if (count($pageOrTagList) > 1) 
	    $stringtoprint .="|".$pageOrTag_percentage[$pageOrTag];
	$stringtoprint .="<br>";
	print $stringtoprint;
    }
  if ($includetotal == 'includetotal' and count($pageOrTagList) > 1)
    {
      $totals_rowstring = "Total";
      foreach($monthOrYearList as $monthOrYear)
	  $totals_rowstring .= "|".$monthOrYear_total[$monthOrYear];
      if (count($monthOrYearList) > 1)
	$totals_rowstring .= "|".$grand_total;
      $totals_rowstring .= "|100";
      $totals_rowstring .= "<br>";
      print $totals_rowstring;
    }
  if (count($monthOrYearList) > 1)
    {
      $percentages_rowstring = "Percentage";
      foreach($monthOrYearList as $monthOrYear)
	{
	  $percentages_rowstring .= "|".$monthOrYear_percentage[$monthOrYear];
	}
      $percentages_rowstring .= "|100";
      $percentages_rowstring .= "<br>";
      print $percentages_rowstring;
    }
}

function printPageviewsForMonthOrYearListAsCsvTransposed($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageOrTagadvice='page',$monthOrYearadvice='month') {
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagadvice=='page' and $monthOrYearadvice=='month')
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagadvice=='page' and $monthOrYearadvice=='year')
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);

  $totalsandpercentages_array = totalsandpercentages($pageOrTagList,$monthOrYearList,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageOrTag_total = $totalsandpercentages_array[1];
  $monthOrYear_total = $totalsandpercentages_array[2];
  $pageOrTag_percentage = $totalsandpercentages_array[3];
  $monthOrYear_percentage = $totalsandpercentages_array[4];


  $headerstring = ucfirst($monthOrYearadvice);
  foreach($pageOrTagList as $pageOrTag)
    $headerstring .= "|Views of ".$pageOrTagadvice." ".$pageOrTag;
  if ($includetotal=='includetotal' and count($pageOrTagList) > 1) 
    $headerstring .="|Total";
  if (count($monthOrYearList) > 1)
    $headerstring .="|Percentage";
  $headerstring.="<br>";
  print $headerstring;
  foreach($monthOrYearList as $monthOrYear)
    {
	$stringtoprint = $monthOrYear;
	$total = 0;
	foreach($pageOrTagList as $pageOrTag)
	  {
	    $viewcount = $viewcountarray[$pageOrTag][$monthOrYear];
	    $stringtoprint .= "|".$viewcount;
	  }
	if ($includetotal=='includetotal' and count($pageOrTagList) > 1) 
	  $stringtoprint .="|".$monthOrYear_total[$monthOrYear];
	if (count($monthOrYearList) > 1) 
	  {
	    $stringtoprint .="|".$monthOrYear_percentage[$monthOrYear];
	  }
	$stringtoprint .="<br>";
	print $stringtoprint;
    }
  if ($includetotal == 'includetotal' and count($monthOrYearList) > 1)
    {
      $totals_rowstring = "Total";
      foreach($pageOrTagList as $pageOrTag)
	$totals_rowstring .= "|".$pageOrTag_total[$pageOrTag];
      if (count($pageOrTagList) > 1)
	$totals_rowstring .= "|".$grand_total;
      $totals_rowstring .="|100";
      $totals_rowstring .= "<br>";
      print $totals_rowstring;
    }
  if (count($pageOrTagList) > 1)
    {
      $percentages_rowstring = "Percentage";
      foreach($pageOrTagList as $pageOrTag)
	{
	  $percentages_rowstring .= "|".$pageOrTag_percentage[$pageOrTag];
	}
      $percentages_rowstring .= "|100";
      $percentages_rowstring .= "<br>";
      print $percentages_rowstring;
    }
}

function generateGraph($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageOrTagadvice='page',$monthOrYearadvice='month') {
  global $imagesPath;
  global $generateGraphCmdBase;
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagadvice=='page' and $monthOrYearadvice=='month')
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagadvice=='page' and $monthOrYearadvice=='year')
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);

  $totalsandpercentages_array = totalsandpercentages($pageOrTagList,$monthOrYearList,$viewcountarray);
  $grand_total = $totalsandpercentages_array[0];
  $pageOrTag_total = $totalsandpercentages_array[1];
  $monthOrYear_total = $totalsandpercentages_array[2];
  $pageOrTag_percentage = $totalsandpercentages_array[3];
  $monthOrYear_percentage = $totalsandpercentages_array[4];

  $fullOutput = "";

  $headerstring = ucfirst($monthOrYearadvice);
  foreach($pageOrTagList as $pageOrTag)
    $headerstring .= "|".$pageOrTag;
  if ($includetotal=='includetotal' and count($pageOrTagList) > 1) 
    $headerstring .="|Total";
  if (count($monthOrYearList) > 1)
    $headerstring .="|Percentage";
  $headerstring .="\n";
  $fullOutput .= $headerstring;
  foreach($monthOrYearList as $monthOrYear) {
    $stringtoprint = $monthOrYear;
    $total = 0;
    foreach($pageOrTagList as $pageOrTag) {
      $viewcount = $viewcountarray[$pageOrTag][$monthOrYear];
      $numericViewCount = 0;
      $numericViewCount = $numericViewCount + $viewcount;
      $stringtoprint .= "|".$numericViewCount;
    }
    if ($includetotal=='includetotal' and count($pageOrTagList) > 1) {
      $stringtoprint .="|".$monthOrYear_total[$monthOrYear];
    }
    if (count($monthOrYearList) > 1) {
      $stringtoprint .="|".$monthOrYear_percentage[$monthOrYear];
    }
    $stringtoprint .="\n";
    $fullOutput .= $stringtoprint;
  }
  if ($includetotal == 'includetotal' and count($monthOrYearList) > 1) {
    $totals_rowstring = "Total";
    foreach($pageOrTagList as $pageOrTag)
      $totals_rowstring .= "|".$pageOrTag_total[$pageOrTag];
    if (count($pageOrTagList) > 1)
      $totals_rowstring .= "|".$grand_total;
    $totals_rowstring .="|100";
    $totals_rowstring .= "\n";
    $fullOutput .= $totals_rowstring;
  }
  if (count($pageOrTagList) > 0) {
    $percentages_rowstring = "Percentage";
    foreach($pageOrTagList as $pageOrTag) {
      $percentages_rowstring .= "|".$pageOrTag_percentage[$pageOrTag];
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

function printPageviewsForMonthOrYearListAsCpi($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericdisplayformat,$normalization='',$pageOrTagadvice='page',$monthOrYearadvice='month') {
  global $exceededquerylimitmessage;
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagadvice=='page' and $monthOrYearadvice=='month')
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagadvice=='page' and $monthOrYearadvice=='year')
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagadvice=='tag' and $monthOrYearadvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  
  #Collect tag information
  if ($pageOrTagadvice=='page')
    {
      $tagListbypages = gettagListbypageList($pageOrTagList,$language);
      $tagindices = gettagindices($pageOrTagList,$language);
    }
  for ($i = 0; $i < count($pageOrTagList); $i++)
    {
      for ($j = 0; $j < count($monthOrYearList); $j++)
	{
	  $viewcount = $viewcountarray[$pageOrTagList[$i]][$monthOrYearList[$j]];
	  if ($viewcount != $exceededquerylimitmessage)
	    {
	      print $viewcount; 
	      print " ";
	      print "1,".$i;
	      print " ";
	      print "2,".$j;
	      foreach ($tagListbypages[$pageOrTagList[$i]] as $tag)
		{
		  print " 3,".$tagindices[$tag];
		  print " 4,".($tagindices[$tag] * count($monthOrYearList) + $j);
		}
	      print "<br>";
	    }
	}
    }
}

?>
