<?php

include_once("globalvariables/passwordfile.inc");

function checkSizes($pageOrTagList,$monthOrYearList, $drilldownList) {
  global $pageDisplayLimit;
  global $cellDisplayLimit;
  $numberOfPagesOrTags = count($pageOrTagList);
  $numberOfMonthsOrYears = count($monthOrYearList);
  if ($numberofpagesortags > $pageDisplayLimit)
    {
      print "The number of pages or tags, namely ".$numberofpagesortags.", exceeds ".$pageDisplayLimit.", our hard limit on the number of pages that can be displayed.";
      return 1;
    }
  $numberOfCells = $numberOfPagesOrTags * $numberOfMonthsOrYears * count($drilldownList);
  if ($numberOfCells > $cellDisplayLimit) {
    print "The total number of cells to display, namely ".$numberofcells.", exceeds ".$cellDisplayLimit.", our hard limit on the number of cells that can be displayed.";
    return 2;
  }
  return 0;
}

function totalsAndPercentages($pageOrTagList,$monthOrYearList,$drilldownList,$viewcountarray) {
  $grandTotal = 0;
  foreach ($pageOrTagList as $pageOrTag) {
    foreach ($drilldownList as $drilldown) {
      $pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown] = 0;
      foreach ($monthOrYearList as $monthOrYear) {
        $pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown] += intval($viewcountarray[$pageOrTag][$monthOrYear][$drilldown]);
      }
      $grandTotal += $pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown];
    }
  }
  foreach ($monthOrYearList as $monthOrYear) {
    $monthOrYearTotal[$monthOrYear] = 0;
    foreach ($pageOrTagList as $pageOrTag) {
      foreach ($drilldownList as $drilldown) {
        $monthOrYearTotal[$monthOrYear] += intval($viewcountarray[$pageOrTag][$monthOrYear][$drilldown]);
      }
    }
  }
  
  foreach ($pageOrTagList as $pageOrTag) {
    foreach ($drilldownList as $drilldown) {
      if ($grandTotal == 0) {
	$pageOrTagCumDrilldownPercentage[$pageOrTag][$drilldown] = 'undefined';
      } else {
	$pageOrTagCumDrilldownPercentage[$pageOrTag][$drilldown] = round(100 * floatval($pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown])/floatval($grandTotal),1);
      }
    }
  }
  foreach ($monthOrYearList as $monthOrYear) {
    if ($grandTotal == 0) {
      $monthOrYearPercentage[$monthOrYear] = 'undefined';
    } else {
      $monthOrYearPercentage[$monthOrYear] = round(100.0 * floatval($monthOrYearTotal[$monthOrYear])/floatval($grandTotal),1);
    }
  }
  
  return array($grandTotal,$pageOrTagCumDrilldownTotal,$monthOrYearTotal,$pageOrTagCumDrilldownPercentage,$monthOrYearPercentage);
}

function printMonthViewCount($page,$month,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  return '<td align="right"><a href="'.getpageviewsurl($page,$month,$language,$drilldown).'" title="'.monthviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
}

function printYearViewCount($page,$year,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  return '<td align="right"><a href="'.getannualpageviewsurl($page,$year,$language,$drilldown).'" title="'.yearviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
}

function printtagviewcount($tag,$month,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  return '<td align="right"><a href="'.gettagviewsurl($tag,$month,$language,$drilldown).'" title="'.$viewcount.' (click for data on individual pages)">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
}

function printtagviewcountbyyear($tag,$year,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  return '<td align="right"><a href="'.getannualtagviewsurl($tag,$year,$language,$drilldown).'" title="'.$viewcount.' (click for data on individual pages)">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
}

function printPageviewsForMonthOrYearListAsHtmlTable($pageOrTagList,$monthOrYearList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  flush();
  #Check that sizes are workable
  $sizeOverflow = checkSizes($pageOrTagList,$monthOrYearList);
  if ($sizeOverflow > 0) {
    return false;
  }
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
      $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  }
  $totalsAndPercentagesArray = totalsAndPercentages($pageOrTagList,$monthOrYearList,$drilldownList,$viewcountarray);
  $grandTotal = $totalsAndPercentagesArray[0];
  $pageOrTagCumDrilldownTotal = $totalsAndPercentagesArray[1];
  $monthOrYearTotal = $totalsAndPercentagesArray[2];
  $pageOrTagCumDrilldownPercentage = $totalsAndPercentagesArray[3];
  $monthOrYearPercentage = $totalsAndPercentagesArray[4];

  #Tag list fetching
  if ($pageOrTagAdvice=='page') {
    $tagListByPages = getTagListByPageList($pageOrTagList,$language);
  }
  #Pre-table warnings

  if ($monthOrYearAdvice=='year') {
    print "<strong>For speed and consistency reasons, we do <em>not</em> include the current month in totals for the current year</strong><br><br>";
  }
  flush();
  ##Table header row
    
  print '<table border="1">';
  $headerstring = "<tr><th>".ucfirst($pageOrTagAdvice)." name</th>";

  foreach($monthOrYearList as $monthOrYear) {
    $headerstring .= "<th>Count in ".$monthOrYearAdvice." ".$monthOrYear."</th>";
  }
  if ($includetotal=='includetotal' and count($monthOrYearList) > 1) {
    $headerstring .="<th>Total</th>";
  }
  if (count($pageOrTagList) * count($drilldownList) > 1) {
    $headerstring.="<th>Percentage</th>";
  }

  #Tag list column printing
  if ($pageOrTagAdvice == 'page') {
    $headerstring .= "<th>Tags</th>";
  }
  $headerstring .= "</tr>";
  print $headerstring;
  
  ##Data rows
  foreach($pageOrTagList as $pageOrTag) {
    foreach($drilldownList as $drilldown) {
      if ($pageOrTagAdvice=='page') {
        $pageOrTagCumDrilldownRowString = '<tr><td><a href="'.getpageurl($pageOrTag,$language).'" title = "'.$pageOrTag.' (read page on Wikipedia)">'.$pageOrTag.'</a>';
      } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
        $pageOrTagCumDrilldownRowString = '<td><a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>';
      } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
        $pageOrTagCumDrilldownRowString = '<td><a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
      }
      if (count($drilldownList) > 1) {
	$pageOrTagCumDrilldownRowString .= ', drilldown '.$drilldown;
      }
      $pageOrTagCumDrilldownRowString .= '</td>';
      
      foreach($monthOrYearList as $monthOrYear) {
	$viewcount = $viewcountarray[$pageOrTag][$monthOrYear][$drilldown];
	if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
	  $pageOrTagCumDrilldownRowString .= printMonthViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
	} elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
	  $pageOrTagCumDrilldownRowString .= printYearViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
	  $pageOrTagCumDrilldownRowString .= printtagviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
	  $pageOrTagCumDrilldownRowString .= printtagviewcountbyyear($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
	}
      }
      if ($includetotal=='includetotal' and count($monthOrYearList) > 1) {
	$pageOrTagCumDrilldownRowString .='<td align="right"><strong><element title="'.$pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown].'">'.numericDisplay($pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown],$numericDisplayFormat).'</element></strong></td>';
      }
      if (count($pageOrTagList) * count($drilldownList) > 1) {
	$pageOrTagCumDrilldownRowString .= '<td align="right"><strong>'.$pageOrTagCumDrilldownPercentage[$pageOrTag][$drilldown].'</strong></td>';
      }
      if ($pageOrTagAdvice == 'page') {
        $pageOrTagCumDrilldownRowString .= '<td>';
	$tagListForPage = $tagListByPages[$pageOrTag];
	if (count($tagListForPage)==0) {
	  $pageOrTagCumDrilldownRowString .= "--";
        }
	foreach ($tagListForPage as $tag) {
          if ($monthOrYearAdvice == 'month') {
            $pageOrTagCumDrilldownRowString .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$tag.'</a> ';
	  } else {
            $pageOrTagCumDrilldownRowString .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$tag.'</a> ';
	  }
        }
        $pageOrTagCumDrilldownRowString .= '</td>';
      }
      $pageOrTagCumDrilldownRowString .="</tr>";
      print $pageOrTagCumDrilldownRowString;
    }
  }
  if ($includetotal=='includetotal' and count($pageOrTagList) * count($drilldownList) > 1) {
    $totalsRowString="<tr><td><strong>Total</strong></td>";
    foreach($monthOrYearList as $monthOrYear) {
      $totalsRowString .= '<td align="right"><strong><element title="'.$monthOrYearTotal[$monthOrYear].'">'.numericDisplay($monthOrYearTotal[$monthOrYear],$numericDisplayFormat).'</element></strong></td>';
    }
    if (count($monthOrYearList) > 1) {
      $totalsRowString .= '<td align="right"><strong><element title="'.$grandTotal.'">'.numericDisplay($grandTotal,$numericDisplayFormat).'</element></strong></td>';
    }
    $totalsRowString .= '<td align="right"><strong>100</strong></td>';
    if ($pageOrTagAdvice == 'page') {
      $totalsRowString .= "<td>--</td>";
    }
    $totalsRowString .= "</tr>";
    print $totalsRowString;
  }
  if (count($monthOrYearList) > 1) {
    $percentagesRowString = "<tr><td><strong>Percentage</strong></td>";
    foreach($monthOrYearList as $monthOrYear) {
      $percentagesRowString .= '<td align="right"><strong>'.$monthOrYearPercentage[$monthOrYear].'</strong></td>';
    }
    if ($includetotal == 'includetotal') {
      $percentagesRowString .= '<td align="right"><strong>100</strong></td>';
    }
    if (count($pageOrTagList) * count($drilldownList) > 1) {
      $percentagesRowString .= '<td align="right">--</td>';
    }
    if ($pageOrTagAdvice == 'page') {
      $percentagesRowString .= "<td>--</td>";
    }
    $percentagesRowString .= '</tr>';
    print $percentagesRowString;
  }
  print "</table>";
  flush();
}

function printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageOrTagList,$monthOrYearList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  flush();
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;

  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  }
  $totalsAndPercentagesArray = totalsAndPercentages($pageOrTagList,$monthOrYearList,$drilldownList,$viewcountarray);
  $grandTotal = $totalsAndPercentagesArray[0];
  $pageOrTagCumDrilldownTotal = $totalsAndPercentagesArray[1];
  $monthOrYearTotal = $totalsAndPercentagesArray[2];
  $pageOrTagCumDrilldownPercentage = $totalsAndPercentagesArray[3];
  $monthOrYearPercentage = $totalsAndPercentagesArray[4];

  #Tag list fetching
  if ($pageOrTagAdvice=='page') {
     $tagListByPages = getTagListByPageList($pageOrTagList,$language);
  }
  #Pre-table warnings
    
  if ($monthOrYearAdvice=='year') {
    print "<strong>For speed and consistency reasons, we do <em>not</em> include the current month in totals for the current year</strong><br><br>";
  }
  flush();
  #Table header row
  print '<table border="1">';
  $headerstring = "<tr><th>".ucfirst($monthOrYearAdvice)."</th>";
  foreach($pageOrTagList as $pageOrTag) {
    foreach($drilldownList as $drilldown) {
      $shortDescriptor = getShortDescriptor($drilldown);
      if ($pageOrTagAdvice=='page') {
        $headerstring .= '<th>'.$shortDescriptor.' of page <a href="'. getpageurl($pageOrTag,$language). '" title="'.$pageOrTag.' (read page on Wikipedia)">' . $pageOrTag.'</a>';
      } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
        $headerstring .= '<th>'.$shortDescriptor.' of pages with tag <a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>';
      } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
        $headerstring .= '<th>Views of pages with tag <a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
      }
      if (count($drilldownList) > 1) {
        $headerstring .= ", drilldown ".$drilldown;
      }
      $headerstring .= '</th>';
    }
  }
  if ($includetotal=='includetotal' and count($pageOrTagList) * count($drilldownList) > 1) {
    $headerstring .="<th>Total</th>";
  }
  if (count($monthOrYearList) > 1) {
    $headerstring.='<td><strong>Percentage</strong></td>';
  }
  $headerstring .= '</tr>';
  print $headerstring;
  
  ##Data rows
  foreach($monthOrYearList as $monthOrYear) { #Prints one row of the table
    $monthOrYearRowString = '<tr><td>'.$monthOrYear.'</td>';
    foreach($pageOrTagList as $pageOrTag) { #Computes one cell entry
      foreach($drilldownList as $drilldown) {
        $viewcount = $viewcountarray[$pageOrTag][$monthOrYear][$drilldown];
        if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
          $monthOrYearRowString .= printMonthViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
        } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
          $monthOrYearRowString .= printYearViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
          $monthOrYearRowString .= printtagviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
          $monthOrYearRowString .= printtagviewcountbyyear($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
        }
      }
    }
    if ($includetotal=='includetotal' and count($pageOrTagList) * count($drilldownList) > 1) {
      $monthOrYearRowString .='<td align="right"><strong><element title="'.$monthOrYearTotal[$monthOrYear].'">'.numericDisplay($monthOrYearTotal[$monthOrYear],$numericDisplayFormat).'</element></strong></td>';
    }
    if (count($monthOrYearList) > 1) {
      $monthOrYearRowString .='<td align="right"><strong>'.$monthOrYearPercentage[$monthOrYear].'</strong></td></tr>';
    }
    print $monthOrYearRowString;
  }
    
  ##Totals row
  if ($includetotal=='includetotal' and count($monthOrYearList) > 1) {
    $totalsRowString="<tr><td><strong>Total</strong></td>";
    foreach($pageOrTagList as $pageOrTag) { #Prints bottom row with totals
      foreach($drilldownList as $drilldown) {
        $totalsRowString .= '<td align="right"><strong><element title="'.$pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown].'">'.numericDisplay($pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown],$numericDisplayFormat).'</element></strong></td>';
      }
    }
    if (count($pageOrTagList) * count($drilldownList) > 1) { 
      $totalsRowString .= '<td align="right"><strong><element title="'.$grandTotal.'">'.numericDisplay($grandTotal,$numericDisplayFormat).'</element></strong></td>';
    }
    $totalsRowString .= '<td align="right"><strong>100</strong></td></tr>';
    print $totalsRowString;
  }

  ##Percentages row
  if (count($pageOrTagList) * count($drilldownList) > 1) {
    $percentagesRowString = "<tr><td><strong>Percentage</strong></td>";
    foreach($pageOrTagList as $pageOrTag) {
      foreach($drilldownList as $drilldown) {
	$percentagesRowString .= '<td align="right"><strong>'.$pageOrTagCumDrilldownPercentage[$pageOrTag][$drilldown].'</strong></td>';
      }
    }
    if ($includetotal == 'includetotal') {
      $percentagesRowString .= '<td align="right"><strong>100</strong></td>';
    }
    if (count($monthOrYearList) > 1) {
      $percentagesRowString .= '<td align="right">--</td></tr>';
    }
    print $percentagesRowString;
  }

  ##Tags row
  if ($pageOrTagAdvice == 'page') {
    $tagsRowString = "<tr><td><strong>Tags</strong></td>";
    foreach ($pageOrTagList as $pageOrTag) {
      foreach ($drilldownList as $drilldown) {  
	$tagsRowString .= '<td>';
	$tagListForPage = $tagListByPages[$pageOrTag];
	if (count($tagListForPage)==0) {
	  $tagsRowString .= "--";
	}
	foreach ($tagListForPage as $tag) {
	  if ($monthOrYearAdvice == 'month') {
            $tagsRowString .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&allmonths=allmonths">'.$tag.'</a> ';
	  } else {
            $tagsRowString .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&allyears=allyears">'.$tag.'</a> ';
	  }
	}
	$tagsRowString .= '</td>';
      }
    }
    if (count($pageOrTagList) * count($drilldownList) > 1) {
      $tagsRowString .= '<td>--</td>';
    }
    if (count($monthOrYearList) > 1) {
      $tagsRowString .= '<td>--</td>';
    }
    $tagsRowString .= '</tr>';
    print $tagsRowString;
  }	  
  print "</table>";
  flush();
}

function printPageviewsForMonthOrYearListAsCsv($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month')
    {
      $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }
  elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year')
    {
      $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month')
    {
      $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year')
    {
      $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }

  $totalsAndPercentagesArray = totalsAndPercentages($pageOrTagList,$monthOrYearList,$viewcountarray);
  $grandTotal = $totalsAndPercentagesArray[0];
  $pageOrTagTotal = $totalsAndPercentagesArray[1];
  $monthOrYearTotal = $totalsAndPercentagesArray[2];
  $pageOrTagPercentage = $totalsAndPercentagesArray[3];
  $monthOrYearPercentage = $totalsAndPercentagesArray[4];


  $headerstring = ucfirst($pageOrTagAdvice)." name";
  $descriptor = getDescriptor($drilldown);
  foreach($monthOrYearList as $monthOrYear) {
    $headerstring .= "|".$descriptor." in ".$monthOrYearAdvice." ".$monthOrYear;
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
	  $stringtoprint .="|".$pageOrTagTotal[$pageOrTag];
	if (count($pageOrTagList) > 1) 
	    $stringtoprint .="|".$pageOrTagPercentage[$pageOrTag];
	$stringtoprint .="<br>";
	print $stringtoprint;
    }
  if ($includetotal == 'includetotal' and count($pageOrTagList) > 1)
    {
      $totalsRowString = "Total";
      foreach($monthOrYearList as $monthOrYear)
	  $totalsRowString .= "|".$monthOrYearTotal[$monthOrYear];
      if (count($monthOrYearList) > 1)
	$totalsRowString .= "|".$grandTotal;
      $totalsRowString .= "|100";
      $totalsRowString .= "<br>";
      print $totalsRowString;
    }
  if (count($monthOrYearList) > 1)
    {
      $percentagesRowString = "Percentage";
      foreach($monthOrYearList as $monthOrYear)
	{
	  $percentagesRowString .= "|".$monthOrYearPercentage[$monthOrYear];
	}
      $percentagesRowString .= "|100";
      $percentagesRowString .= "<br>";
      print $percentagesRowString;
    }
}

function printPageviewsForMonthOrYearListAsCsvTransposed($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);

  $totalsAndPercentagesArray = totalsAndPercentages($pageOrTagList,$monthOrYearList,$viewcountarray);
  $grandTotal = $totalsAndPercentagesArray[0];
  $pageOrTagTotal = $totalsAndPercentagesArray[1];
  $monthOrYearTotal = $totalsAndPercentagesArray[2];
  $pageOrTagPercentage = $totalsAndPercentagesArray[3];
  $monthOrYearPercentage = $totalsAndPercentagesArray[4];


  $headerstring = ucfirst($monthOrYearAdvice);
  foreach($pageOrTagList as $pageOrTag)
    $headerstring .= "|Views of ".$pageOrTagAdvice." ".$pageOrTag;
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
	  $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
	if (count($monthOrYearList) > 1) 
	  {
	    $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
	  }
	$stringtoprint .="<br>";
	print $stringtoprint;
    }
  if ($includetotal == 'includetotal' and count($monthOrYearList) > 1)
    {
      $totalsRowString = "Total";
      foreach($pageOrTagList as $pageOrTag)
	$totalsRowString .= "|".$pageOrTagTotal[$pageOrTag];
      if (count($pageOrTagList) > 1)
	$totalsRowString .= "|".$grandTotal;
      $totalsRowString .="|100";
      $totalsRowString .= "<br>";
      print $totalsRowString;
    }
  if (count($pageOrTagList) > 1)
    {
      $percentagesRowString = "Percentage";
      foreach($pageOrTagList as $pageOrTag)
	{
	  $percentagesRowString .= "|".$pageOrTagPercentage[$pageOrTag];
	}
      $percentagesRowString .= "|100";
      $percentagesRowString .= "<br>";
      print $percentagesRowString;
    }
}

function generateGraph($pageOrTagList,$monthOrYearList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  global $imagesPath;
  global $generateGraphCmdBase;
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);

  $totalsAndPercentagesArray = totalsAndPercentages($pageOrTagList,$monthOrYearList,$drilldownList,$viewcountarray);
  $grandTotal = $totalsAndPercentagesArray[0];
  $pageOrTagCumDrilldownTotal = $totalsAndPercentagesArray[1];
  $monthOrYearTotal = $totalsAndPercentagesArray[2];
  $pageOrTagCumDrilldownPercentage = $totalsAndPercentagesArray[3];
  $monthOrYearPercentage = $totalsAndPercentagesArray[4];

  $fullOutput = "";

  $headerstring = ucfirst($monthOrYearAdvice);
  foreach($pageOrTagList as $pageOrTag) {
    foreach ($drilldownList as $drilldown) {
      $headerstring .= "|".$pageOrTag." on drilldown ".$drilldown;
    }
  }
  if ($includetotal=='includetotal' and count($pageOrTagList) > 1) {
    $headerstring .="|Total";
  }
  if (count($monthOrYearList) > 1) {
    $headerstring .="|Percentage";
  }
  $headerstring .="\n";
  $fullOutput .= $headerstring;
  foreach($monthOrYearList as $monthOrYear) {
    $stringtoprint = $monthOrYear;
    $total = 0;
    foreach($pageOrTagList as $pageOrTag) {
      foreach($drilldownList as $drilldown) { 
        $viewcount = $viewcountarray[$pageOrTag][$monthOrYear][$drilldown];
        $numericViewCount = 0;
        $numericViewCount = $numericViewCount + $viewcount;
        $stringtoprint .= "|".$numericViewCount;
      }
    }
    if ($includetotal=='includetotal' and count($pageOrTagList) > 1) {
      $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
    }
    if (count($monthOrYearList) > 1) {
      $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
    }
    $stringtoprint .="\n";
    $fullOutput .= $stringtoprint;
  }
  if ($includetotal == 'includetotal' and count($monthOrYearList) > 1) {
    $totalsRowString = "Total";
    foreach($pageOrTagList as $pageOrTag) {
      foreach($drilldownList as $drilldown) {
        $totalsRowString .= "|".$pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown];
      }
    }
    if (count($pageOrTagList) > 1) {
      $totalsRowString .= "|".$grandTotal;
    }
    $totalsRowString .="|100";
    $totalsRowString .= "\n";
    $fullOutput .= $totalsRowString;
  }
  if (count($pageOrTagList) > 0) {
    $percentagesRowString = "Percentage";
    foreach($pageOrTagList as $pageOrTag) {
      foreach($drilldownList as $drilldown) {
        $percentagesRowString .= "|".$pageOrTagCumDrilldownPercentage[$pageOrTag][$drilldown];
      }
    }
    $percentagesRowString .= "|100";
    $percentagesRowString .= "\n";
    $fullOutput .= $percentagesRowString;
  }
  $fileName = strval(rand());
  $filePathBase = $imagesPath . $fileName;
  # print("Going to try writing the following to ".$filePathBase.".csv: <br>".$fullOutput."<br>");
  file_put_contents($filePathBase . ".csv", $fullOutput);
  $cmdToExecute = $generateGraphCmdBase . " " . $filePathBase . ".csv " . $filePathBase . ".png ";
  if ($numericDisplayFormat == "log") {
    $cmdToExecute = $cmdToExecute . " --log10";
  }
  # print("Going to try executing ".$cmdToExecute."<br>");
  exec($cmdToExecute);
  print '<img src="/images/'.$fileName.'.png" alt="Graph of pageviews should have loaded here"></img>';
}

function printPageviewsForMonthOrYearListAsCpi($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  global $exceededQueryLimitMessage;
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  
  #Collect tag information
  if ($pageOrTagAdvice=='page')
    {
      $tagListByPages = getTagListByPageList($pageOrTagList,$language);
      $tagindices = gettagindices($pageOrTagList,$language);
    }
  for ($i = 0; $i < count($pageOrTagList); $i++)
    {
      for ($j = 0; $j < count($monthOrYearList); $j++)
	{
	  $viewcount = $viewcountarray[$pageOrTagList[$i]][$monthOrYearList[$j]];
	  if ($viewcount != $exceededQueryLimitMessage)
	    {
	      print $viewcount; 
	      print " ";
	      print "1,".$i;
	      print " ";
	      print "2,".$j;
	      foreach ($tagListByPages[$pageOrTagList[$i]] as $tag)
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
